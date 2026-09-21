"""Every finalized update must force a rebuild on the next boot.

launch_chffrplus.sh skips ./build.py when a `prebuilt` marker is present, and the marker
is tracked in this fork, so the `git reset --hard` inside finalize restores it. Compiled
artifacts (e.g. msgq_repo/msgq/visionipc/visionipc_pyx.so) would then stay stale after an
update that changed C++ sources. Finalize drops the marker so the swapped-in tree builds
once; build.py never recreates it, so this costs one build per update, not per boot.

updated.py imports the whole device stack, so the module is loaded in isolation with only
the names finalize_update actually uses.
"""
import subprocess
import sys
import types
from pathlib import Path

import pytest

UPDATED_PATH = Path(__file__).parents[3] / "system" / "updated" / "updated.py"


def _load_finalize_update(tmp_path):
  """Exec updated.py's finalize helpers against a temp staging root."""
  source = UPDATED_PATH.read_text()

  def extract(start_marker: str, end_marker: str) -> str:
    start = source.index(start_marker)
    return source[start:source.index(end_marker, start)]

  namespace: dict = {
    "os": __import__("os"),
    "shutil": __import__("shutil"),
    "time": __import__("time"),
    "subprocess": subprocess,
    "Path": Path,
    "cloudlog": types.SimpleNamespace(
      info=lambda *_a, **_k: None,
      event=lambda *_a, **_k: None,
      exception=lambda *_a, **_k: None,
    ),
    "OVERLAY_MERGED": str(tmp_path / "merged"),
    "FINALIZED": str(tmp_path / "finalized"),
  }

  exec(extract("def run(", "def run_with_offroad_abort("), namespace)  # noqa: S102
  exec(extract("def set_consistent_flag(", "def parse_release_notes("), namespace)  # noqa: S102
  exec(extract("def finalize_update(", "def handle_agnos_update("), namespace)  # noqa: S102
  return namespace["finalize_update"]


def _git_repo_with_tracked_prebuilt(path: Path, *, with_prebuilt: bool = True) -> None:
  path.mkdir(parents=True, exist_ok=True)
  subprocess.check_call(["git", "init", "-q"], cwd=path)
  subprocess.check_call(["git", "config", "user.email", "t@t"], cwd=path)
  subprocess.check_call(["git", "config", "user.name", "t"], cwd=path)
  if with_prebuilt:
    (path / "prebuilt").touch()
  (path / "README").write_text("x")
  subprocess.check_call(["git", "add", "-A"], cwd=path)
  subprocess.check_call(["git", "commit", "-qm", "init"], cwd=path)


@pytest.fixture
def staging(tmp_path):
  _git_repo_with_tracked_prebuilt(tmp_path / "merged")
  return _load_finalize_update(tmp_path), tmp_path / "finalized"


def test_finalize_removes_the_prebuilt_marker(staging):
  finalize_update, finalized = staging

  finalize_update()

  assert finalized.is_dir()
  assert not (finalized / "prebuilt").exists()


def test_finalize_still_marks_the_update_consistent(staging):
  finalize_update, finalized = staging

  finalize_update()

  assert (finalized / ".overlay_consistent").is_file()


def test_finalize_keeps_the_rest_of_the_tree(staging):
  finalize_update, finalized = staging

  finalize_update()

  assert (finalized / "README").read_text() == "x"


def test_finalize_succeeds_when_no_prebuilt_marker_exists(tmp_path):
  _git_repo_with_tracked_prebuilt(tmp_path / "merged", with_prebuilt=False)
  finalize_update = _load_finalize_update(tmp_path)
  finalized = tmp_path / "finalized"

  finalize_update()

  assert not (finalized / "prebuilt").exists()
  assert (finalized / ".overlay_consistent").is_file()


def test_updated_module_still_defines_finalize_update():
  assert "def finalize_update(" in UPDATED_PATH.read_text()
  assert sys.version_info >= (3, 10)
