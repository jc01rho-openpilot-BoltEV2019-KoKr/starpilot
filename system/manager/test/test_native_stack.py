import threading
from pathlib import Path

from openpilot.system.manager import native_stack
from openpilot.system.manager.native_stack import NativeStackWatch, capture_native_stack, rotate_native_stacks


def _fake_proc(root: Path, pid: int, threads: dict[int, tuple[str, str, str]]) -> Path:
  for tid, (comm, wchan, stack) in threads.items():
    task = root / str(pid) / "task" / str(tid)
    task.mkdir(parents=True)
    (task / "comm").write_text(comm + "\n")
    (task / "wchan").write_text(wchan)
    (task / "stack").write_text(stack)
  return root


def test_capture_reads_kernel_stacks_before_attaching_gdb(tmp_path):
  proc = _fake_proc(
    tmp_path / "proc", 4242, {4242: ("ui", "pipe_wait", "[<0>] pipe_wait+0x6c/0xb0\n"), 4250: ("ZMQbg/IO/0", "SyS_epoll_wait", "[<0>] ep_poll+0x2a0\n")}
  )
  dump_dir = tmp_path / "log"
  dump_dir.mkdir()
  calls = []

  def fake_gdb(cmd, timeout):
    stacks_read_before_gdb = not list(dump_dir.glob("ui_native_stack_*.log"))
    calls.append((cmd, timeout, stacks_read_before_gdb))
    return "Thread 1 (LWP 4242):\n#0 read ()\n"

  path = capture_native_stack("ui", 4242, 6.2, dump_dir, proc_root=proc, run=fake_gdb)

  text = path.read_text()
  assert "tid 4242 comm=ui wchan=pipe_wait" in text
  assert "pipe_wait+0x6c/0xb0" in text
  assert "tid 4250 comm=ZMQbg/IO/0 wchan=SyS_epoll_wait" in text
  assert "#0 read ()" in text
  assert text.index("== kernel stacks ==") < text.index("== gdb thread apply all bt ==")
  ((cmd, timeout, _),) = calls
  assert cmd[:3] == ["gdb", "-p", "4242"] and "-batch" in cmd
  assert "sudo" not in cmd
  assert timeout == native_stack.GDB_TIMEOUT_S


def test_capture_of_a_process_that_already_exited_writes_nothing(tmp_path):
  dump_dir = tmp_path / "log"
  dump_dir.mkdir()

  assert capture_native_stack("ui", 999, 6.0, dump_dir, proc_root=tmp_path / "proc", run=lambda *_: "") is None
  assert list(dump_dir.iterdir()) == []


def test_only_the_three_newest_native_stacks_are_kept(tmp_path):
  for seq in (5, 1, 4, 2, 3):
    (tmp_path / f"ui_native_stack_100_{seq}.log").write_text("x")
  (tmp_path / "ui_watchdog_dump_100_1.log").write_text("keep")
  (tmp_path / "camerad_native_stack_1_1.log").write_text("keep")

  rotate_native_stacks(tmp_path, "ui")

  assert sorted(p.name for p in tmp_path.glob("ui_native_stack_*.log")) == [
    "ui_native_stack_100_3.log",
    "ui_native_stack_100_4.log",
    "ui_native_stack_100_5.log",
  ]
  assert (tmp_path / "ui_watchdog_dump_100_1.log").exists()
  assert (tmp_path / "camerad_native_stack_1_1.log").exists()


def test_capture_rotation_keeps_the_newest_three_across_captures(tmp_path):
  proc = _fake_proc(tmp_path / "proc", 7, {7: ("ui", "pipe_wait", "stack")})
  dump_dir = tmp_path / "log"
  dump_dir.mkdir()

  paths = [capture_native_stack("ui", 7, 6.0, dump_dir, proc_root=proc, run=lambda *_: "bt") for _ in range(5)]

  assert sorted(dump_dir.glob("ui_native_stack_*.log")) == sorted(paths[-3:])


class _Clock:
  def __init__(self):
    self.now = 100.0

  def __call__(self):
    return self.now


def _watch_with_gate(capture_dt=6.0):
  gate = threading.Event()
  captured = []
  clock = _Clock()

  def capture(pid, dt):
    captured.append((pid, dt))
    gate.wait(timeout=5)
    clock.now += 3.5

  return NativeStackWatch(capture_dt, capture, clock=clock), gate, captured, clock


def test_capture_starts_once_per_pid_after_the_threshold():
  watch, gate, captured, _ = _watch_with_gate()

  assert not watch.maybe_capture(10, 5.9)
  assert watch.maybe_capture(10, 6.1)
  assert not watch.maybe_capture(10, 7.5)
  gate.set()
  watch._thread.join(timeout=5)

  assert captured == [(10, 6.1)]
  assert watch.maybe_capture(11, 6.1), "a restarted process gets its own capture"


def test_kill_waits_for_the_capture_then_returns_the_time_gdb_held_the_process():
  watch, gate, _, _ = _watch_with_gate()
  watch.maybe_capture(10, 6.1)

  assert watch.defer_kill(10, 10.5, 10), "must not SIGKILL while gdb is still attached"
  gate.set()
  watch._thread.join(timeout=5)

  assert watch.defer_kill(10, 13.0, 10), "the 3.5s gdb held the process is given back"
  assert not watch.defer_kill(10, 13.6, 10)
  assert not watch.defer_kill(11, 10.5, 10), "a pid without a capture is killed normally"


def test_a_hung_capture_cannot_postpone_the_kill_forever():
  watch, gate, _, clock = _watch_with_gate()
  watch.maybe_capture(10, 6.1)

  clock.now += native_stack.MAX_KILL_DEFER_S + 0.1
  assert not watch.defer_kill(10, 40.0, 10)
  gate.set()
  watch._thread.join(timeout=5)
