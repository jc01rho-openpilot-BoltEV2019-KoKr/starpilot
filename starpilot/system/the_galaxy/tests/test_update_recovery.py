import importlib.util
import os

from pathlib import Path


def _load_update_recovery_module():
  module_path = Path(__file__).resolve().parents[1] / "update_recovery.py"
  spec = importlib.util.spec_from_file_location("update_recovery_under_test", module_path)
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


update_recovery = _load_update_recovery_module()


def _make_repo(tmp_path, *, lock_age=60.0, now=1_000.0):
  repo_path = tmp_path / "openpilot"
  git_dir = repo_path / ".git"
  git_dir.mkdir(parents=True)
  lock_path = git_dir / update_recovery.SHALLOW_LOCK_NAME
  lock_path.write_text("", encoding="utf-8")
  os.utime(lock_path, (now - lock_age, now - lock_age))
  proc_root = tmp_path / "proc"
  proc_root.mkdir()
  return repo_path, lock_path, proc_root


def _inspect(repo_path, proc_root, *, now=1_000.0, is_onroad=False, update_running=False, updater_state="idle"):
  return update_recovery.inspect_interrupted_update(
    repo_path,
    is_onroad=is_onroad,
    update_running=update_running,
    updater_state=updater_state,
    now=now,
    proc_root=proc_root,
  )


def test_missing_lock_does_not_offer_recovery(tmp_path):
  repo_path = tmp_path / "openpilot"
  (repo_path / ".git").mkdir(parents=True)
  proc_root = tmp_path / "proc"
  proc_root.mkdir()

  status = _inspect(repo_path, proc_root)

  assert status["detected"] is False
  assert status["canRecover"] is False


def test_recent_lock_waits_before_recovery(tmp_path):
  repo_path, _, proc_root = _make_repo(tmp_path, lock_age=10.0)

  status = _inspect(repo_path, proc_root)

  assert status["detected"] is True
  assert status["canRecover"] is False
  assert "Waiting" in status["reason"]


def test_recovery_is_blocked_onroad_or_while_updater_is_busy(tmp_path):
  repo_path, _, proc_root = _make_repo(tmp_path)

  onroad_status = _inspect(repo_path, proc_root, is_onroad=True)
  updater_status = _inspect(repo_path, proc_root, updater_state="downloading...")
  galaxy_status = _inspect(repo_path, proc_root, update_running=True)

  assert onroad_status["canRecover"] is False
  assert "parked" in onroad_status["reason"]
  assert updater_status["canRecover"] is False
  assert "downloading" in updater_status["reason"]
  assert galaxy_status["canRecover"] is False
  assert "still running" in galaxy_status["reason"]


def test_active_repo_git_process_blocks_recovery(tmp_path):
  repo_path, _, proc_root = _make_repo(tmp_path)
  process_dir = proc_root / "123"
  process_dir.mkdir()
  (process_dir / "comm").write_text("git\n", encoding="utf-8")
  (process_dir / "cmdline").write_bytes(b"/usr/bin/git\0fetch\0origin\0")
  (process_dir / "cwd").symlink_to(repo_path)

  status = _inspect(repo_path, proc_root)

  assert status["canRecover"] is False
  assert status["activeGitProcessCount"] == 1
  assert "still active" in status["reason"]


def test_non_repo_git_process_does_not_block_recovery(tmp_path):
  repo_path, _, proc_root = _make_repo(tmp_path)
  other_repo = tmp_path / "other"
  other_repo.mkdir()
  process_dir = proc_root / "123"
  process_dir.mkdir()
  (process_dir / "comm").write_text("git\n", encoding="utf-8")
  (process_dir / "cmdline").write_bytes(b"/usr/bin/git\0fetch\0origin\0")
  (process_dir / "cwd").symlink_to(other_repo)

  status = _inspect(repo_path, proc_root)

  assert status["canRecover"] is True


def test_symlink_lock_is_never_removed(tmp_path):
  repo_path = tmp_path / "openpilot"
  git_dir = repo_path / ".git"
  git_dir.mkdir(parents=True)
  target_path = tmp_path / "target"
  target_path.write_text("keep", encoding="utf-8")
  (git_dir / update_recovery.SHALLOW_LOCK_NAME).symlink_to(target_path)
  proc_root = tmp_path / "proc"
  proc_root.mkdir()

  recovered, status = update_recovery.recover_interrupted_update(
    repo_path,
    is_onroad=False,
    update_running=False,
    updater_state="idle",
    now=1_000.0,
    proc_root=proc_root,
  )

  assert recovered is False
  assert status["canRecover"] is False
  assert target_path.read_text(encoding="utf-8") == "keep"


def test_safe_recovery_removes_only_stale_shallow_lock(tmp_path):
  repo_path, lock_path, proc_root = _make_repo(tmp_path)
  keep_path = repo_path / ".git" / "index.lock"
  keep_path.write_text("keep", encoding="utf-8")

  recovered, status = update_recovery.recover_interrupted_update(
    repo_path,
    is_onroad=False,
    update_running=False,
    updater_state="idle",
    now=1_000.0,
    proc_root=proc_root,
  )

  assert recovered is True
  assert status["detected"] is False
  assert not lock_path.exists()
  assert keep_path.read_text(encoding="utf-8") == "keep"


def test_public_status_does_not_expose_lock_path_or_inode(tmp_path):
  repo_path, _, proc_root = _make_repo(tmp_path)

  status = _inspect(repo_path, proc_root)
  public_status = update_recovery.public_recovery_status(status)

  assert public_status["canRecover"] is True
  assert all(not key.startswith("_") for key in public_status)
