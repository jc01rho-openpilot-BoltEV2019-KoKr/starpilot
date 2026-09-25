import subprocess
import threading
import time
from collections.abc import Callable
from pathlib import Path

NATIVE_STACK_KEEP = 3
GDB_TIMEOUT_S = 20.0
# gdb stops the process while it walks the stacks, so a capture must never be able to hold
# a kill off indefinitely.
MAX_KILL_DEFER_S = 30.0

GDB_COMMAND = (
  "gdb",
  "-p",
  "{pid}",
  "-batch",
  "-nx",
  "-q",
  "-ex",
  "set pagination off",
  "-ex",
  "set confirm off",
  "-ex",
  "set auto-load off",
  "-ex",
  "thread apply all bt 30",
)


def _run(cmd: list[str], timeout: float) -> str:
  try:
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout)
    return f"<exit {result.returncode}>\n{result.stdout}{result.stderr}"
  except subprocess.TimeoutExpired:
    return f"<timed out after {timeout:.0f}s>"
  except OSError as e:
    return f"<failed to run {cmd[0]}: {e}>"


def _read(path: Path) -> str:
  try:
    return path.read_text(errors="replace").strip()
  except OSError as e:
    return f"<read failed: {e}>"


def _dump_seq(path: Path) -> int:
  try:
    return int(path.stem.rsplit("_", 1)[1])
  except (IndexError, ValueError):
    return -1


def rotate_native_stacks(dump_dir: Path, name: str, keep: int = NATIVE_STACK_KEEP) -> None:
  dumps = sorted(dump_dir.glob(f"{name}_native_stack_*.log"), key=_dump_seq)
  for stale in dumps[:-keep] if keep > 0 else dumps:
    try:
      stale.unlink()
    except OSError:
      pass


def capture_native_stack(
  name: str, pid: int, dt: float, dump_dir: Path, proc_root: Path = Path("/proc"), run: Callable[[list[str], float], str] = _run
) -> Path | None:
  """Write kernel and native user stacks of every thread of a stalled process.

  Kernel stacks are read first because gdb stops the process while it attaches.
  """
  task_dir = proc_root / str(pid) / "task"
  try:
    tids = sorted(task_dir.iterdir(), key=lambda p: int(p.name))
  except (OSError, ValueError):
    return None

  lines = [
    f"name={name}",
    f"pid={pid}",
    f"watchdog_dt={dt:.3f}",
    f"wall_time={time.strftime('%Y-%m-%dT%H:%M:%S%z')}",
    "",
    "== kernel stacks ==",
  ]
  for tid in tids:
    lines.extend(
      [
        f"-- tid {tid.name} comm={_read(tid / 'comm')} wchan={_read(tid / 'wchan')} --",
        _read(tid / "stack"),
      ]
    )

  gdb_cmd = [part.format(pid=pid) for part in GDB_COMMAND]
  lines.extend(["", "== gdb thread apply all bt ==", run(gdb_cmd, GDB_TIMEOUT_S)])

  path = dump_dir / f"{name}_native_stack_{pid}_{time.time_ns()}.log"
  try:
    path.write_text("\n".join(lines) + "\n")
  except OSError:
    return None
  rotate_native_stacks(dump_dir, name)
  return path


class NativeStackWatch:
  """Capture one native stack per stalled pid before the watchdog kills it.

  The capture runs in the background at `capture_dt`, ahead of the kill, because by the
  time the watchdog fires the process is SIGKILLed and /proc/<pid> is already gone.
  """

  def __init__(self, capture_dt: float, capture: Callable[[int, float], object], clock: Callable[[], float] = time.monotonic):
    self.capture_dt = capture_dt
    self._capture = capture
    self._clock = clock
    self._pid: int | None = None
    self._thread: threading.Thread | None = None
    self._started_at = 0.0
    self._capture_seconds = 0.0

  def _run_capture(self, pid: int, dt: float) -> None:
    start = self._clock()
    try:
      self._capture(pid, dt)
    finally:
      self._capture_seconds = self._clock() - start

  def maybe_capture(self, pid: int, dt: float) -> bool:
    if pid != self._pid:
      self._pid, self._thread, self._capture_seconds = pid, None, 0.0
    if self._thread is not None or dt < self.capture_dt:
      return False

    self._started_at = self._clock()
    self._thread = threading.Thread(name=f"native_stack_{pid}", target=self._run_capture, args=(pid, dt), daemon=True)
    self._thread.start()
    return True

  def defer_kill(self, pid: int, dt: float, max_dt: float) -> bool:
    """Hold the kill while gdb has the process stopped, then allow the paused time back."""
    if pid != self._pid or self._thread is None:
      return False
    if self._clock() - self._started_at > MAX_KILL_DEFER_S:
      return False
    if self._thread.is_alive():
      return True
    return dt <= max_dt + self._capture_seconds
