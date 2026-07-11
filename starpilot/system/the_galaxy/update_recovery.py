import os
import stat

from datetime import datetime
from pathlib import Path


SHALLOW_LOCK_NAME = "shallow.lock"
MIN_STALE_LOCK_AGE_SECONDS = 30.0


def _git_directory(repo_path):
  repo = Path(repo_path).resolve()
  dot_git = repo / ".git"

  if dot_git.is_dir():
    return dot_git.resolve()

  try:
    marker = dot_git.read_text(encoding="utf-8", errors="replace").strip()
  except OSError:
    return None

  prefix = "gitdir:"
  if not marker.lower().startswith(prefix):
    return None

  git_dir = Path(marker[len(prefix):].strip())
  if not git_dir.is_absolute():
    git_dir = dot_git.parent / git_dir
  try:
    return git_dir.resolve()
  except OSError:
    return None


def _path_is_within(path, root):
  try:
    return os.path.commonpath((str(Path(path).resolve()), str(Path(root).resolve()))) == str(Path(root).resolve())
  except (OSError, ValueError):
    return False


def _read_process_tokens(proc_dir):
  try:
    return [token.decode("utf-8", errors="replace") for token in (proc_dir / "cmdline").read_bytes().split(b"\0") if token]
  except OSError:
    return []


def _process_is_git(proc_dir, tokens):
  try:
    command_name = (proc_dir / "comm").read_text(encoding="utf-8", errors="replace").strip().lower()
  except OSError:
    command_name = ""

  executable_name = Path(tokens[0]).name.lower() if tokens else ""
  return command_name == "git" or command_name.startswith("git-") or executable_name == "git" or executable_name.startswith("git-")


def _process_uses_repo(proc_dir, tokens, repo_path, git_dir):
  try:
    cwd = Path(os.readlink(proc_dir / "cwd"))
  except OSError:
    cwd = None

  if cwd is not None and (_path_is_within(cwd, repo_path) or _path_is_within(cwd, git_dir)):
    return True

  for index, token in enumerate(tokens):
    candidate = ""
    if token == "-C" and index + 1 < len(tokens):
      candidate = tokens[index + 1]
    elif token.startswith("--git-dir="):
      candidate = token.split("=", 1)[1]
    if not candidate:
      continue

    candidate_path = Path(candidate)
    if not candidate_path.is_absolute() and cwd is not None:
      candidate_path = cwd / candidate_path
    if _path_is_within(candidate_path, repo_path) or _path_is_within(candidate_path, git_dir):
      return True

  return False


def _active_repo_git_processes(repo_path, git_dir, proc_root=Path("/proc")):
  active_pids = []
  try:
    process_dirs = [entry for entry in Path(proc_root).iterdir() if entry.name.isdigit()]
  except OSError:
    return active_pids

  for proc_dir in process_dirs:
    tokens = _read_process_tokens(proc_dir)
    if not _process_is_git(proc_dir, tokens):
      continue
    if _process_uses_repo(proc_dir, tokens, repo_path, git_dir):
      active_pids.append(int(proc_dir.name))

  return sorted(active_pids)


def inspect_interrupted_update(repo_path, *, is_onroad, update_running, updater_state, now=None, proc_root=Path("/proc")):
  repo = Path(repo_path).resolve()
  git_dir = _git_directory(repo)
  if git_dir is None:
    return {
      "detected": False,
      "canRecover": False,
      "reason": "Git repository metadata could not be located.",
    }

  lock_path = git_dir / SHALLOW_LOCK_NAME
  try:
    lock_stat = lock_path.lstat()
  except FileNotFoundError:
    return {
      "detected": False,
      "canRecover": False,
      "reason": "No interrupted update lock detected.",
    }
  except OSError as exception:
    return {
      "detected": True,
      "canRecover": False,
      "reason": f"Unable to inspect the interrupted update lock: {exception}",
    }

  status = {
    "detected": True,
    "canRecover": False,
    "reason": "",
    "ageSeconds": max(0, int((datetime.now().timestamp() if now is None else float(now)) - lock_stat.st_mtime)),
    "_lockPath": lock_path,
    "_lockDevice": lock_stat.st_dev,
    "_lockInode": lock_stat.st_ino,
  }

  if not stat.S_ISREG(lock_stat.st_mode):
    status["reason"] = "The update lock is not a regular file and cannot be recovered automatically."
    return status
  if is_onroad:
    status["reason"] = "Interrupted updates can only be recovered while parked."
    return status
  if update_running:
    status["reason"] = "Galaxy reports that an update action is still running."
    return status

  normalized_updater_state = str(updater_state or "").strip().lower()
  if normalized_updater_state != "idle":
    label = normalized_updater_state or "unknown"
    status["reason"] = f"The system updater is currently {label}."
    return status

  active_pids = _active_repo_git_processes(repo, git_dir, proc_root=proc_root)
  if active_pids:
    status["reason"] = "A Git update process is still active for this repository."
    status["activeGitProcessCount"] = len(active_pids)
    return status

  if status["ageSeconds"] < MIN_STALE_LOCK_AGE_SECONDS:
    remaining = max(1, int(MIN_STALE_LOCK_AGE_SECONDS - status["ageSeconds"]))
    status["reason"] = f"Waiting {remaining} more seconds before this lock can be treated as abandoned."
    return status

  status["canRecover"] = True
  status["reason"] = "An abandoned update lock can be recovered safely."
  return status


def public_recovery_status(status):
  return {key: value for key, value in status.items() if not key.startswith("_")}


def recover_interrupted_update(repo_path, *, is_onroad, update_running, updater_state, now=None, proc_root=Path("/proc")):
  status = inspect_interrupted_update(
    repo_path,
    is_onroad=is_onroad,
    update_running=update_running,
    updater_state=updater_state,
    now=now,
    proc_root=proc_root,
  )
  if not status.get("canRecover"):
    return False, public_recovery_status(status)

  lock_path = status["_lockPath"]
  try:
    current_stat = lock_path.lstat()
  except FileNotFoundError:
    return True, {
      "detected": False,
      "canRecover": False,
      "reason": "The interrupted update lock was already cleared.",
    }
  except OSError as exception:
    status["canRecover"] = False
    status["reason"] = f"Unable to recheck the interrupted update lock: {exception}"
    return False, public_recovery_status(status)

  if not stat.S_ISREG(current_stat.st_mode) or current_stat.st_dev != status["_lockDevice"] or current_stat.st_ino != status["_lockInode"]:
    status["canRecover"] = False
    status["reason"] = "The update lock changed while it was being checked. Retry after current update activity stops."
    return False, public_recovery_status(status)

  try:
    lock_path.unlink()
  except OSError as exception:
    status["canRecover"] = False
    status["reason"] = f"Unable to clear the interrupted update lock: {exception}"
    return False, public_recovery_status(status)

  return True, {
    "detected": False,
    "canRecover": False,
    "reason": "Interrupted update lock cleared.",
  }
