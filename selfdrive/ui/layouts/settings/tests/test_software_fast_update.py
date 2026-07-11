import threading

import pytest

from openpilot.selfdrive.ui.layouts.settings import software


@pytest.fixture(autouse=True)
def fast_update_env(mocker):
  import pyray as rl
  from openpilot.system.ui.lib.application import gui_app as real_gui_app
  mocker.patch.object(real_gui_app, "font", return_value=rl.Font())
  mocker.patch.object(real_gui_app, "texture", return_value=mocker.MagicMock())
  mocker.patch.object(real_gui_app, "push_widget")

  mocker.patch.object(software, "ui_state")
  software.ui_state.is_onroad.return_value = False
  software.ui_state.is_offroad.return_value = True

  mocker.patch.object(software, "HARDWARE")
  mocker.patch.object(software, "time")

  software._set_fast_update_state(stage=software.FastUpdateStage.IDLE, status="", error="")


@pytest.fixture
def sync_thread(mocker):
  """Make Thread run the target synchronously so tests are deterministic."""
  def _sync_thread(target, daemon=True):
    target()
    return mocker.MagicMock()
  mocker.patch.object(threading, "Thread", _sync_thread)


def test_fast_update_stages(mocker, sync_thread):
  """Fast update transitions through all stages on success (no submodules)."""
  mocker.patch.object(software, "subprocess")
  software.subprocess.run.side_effect = [
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # pkill
    mocker.MagicMock(returncode=0, stdout="main\n", stderr=""),     # rev-parse branch
    mocker.MagicMock(returncode=0, stdout="abc123\n", stderr=""),   # rev-parse HEAD
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # fetch
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # reset --hard
  ]
  mocker.patch.object(software.Path, "is_file", return_value=False)

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.REBOOTING
  assert state.error == ""
  assert state.status == "Update applied, rebooting..."


def test_fast_update_with_submodules(mocker, sync_thread):
  """Fast update runs submodule step when .gitmodules exists."""
  mocker.patch.object(software, "subprocess")
  software.subprocess.run.side_effect = [
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # pkill
    mocker.MagicMock(returncode=0, stdout="main\n", stderr=""),     # rev-parse branch
    mocker.MagicMock(returncode=0, stdout="abc123\n", stderr=""),   # rev-parse HEAD
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # fetch
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # reset --hard
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # submodule update
  ]
  mocker.patch.object(software.Path, "is_file", return_value=True)

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.REBOOTING


def test_fast_update_error_stores_full_message(mocker, sync_thread):
  """Error message is not truncated to 200 chars."""
  long_error = "x" * 500
  mocker.patch.object(software, "subprocess")
  software.subprocess.run.side_effect = [
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # pkill
    RuntimeError(long_error),                                # rev-parse fails
  ]

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.ERROR
  assert len(state.error) == 500


def test_fast_update_blocks_while_onroad(mocker):
  """Fast update is rejected when car is onroad."""
  software.ui_state.is_onroad.return_value = True

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.IDLE


def test_fast_update_error_clears_on_tap(mocker):
  """Tapping download button in ERROR state clears back to IDLE."""
  software._set_fast_update_state(stage=software.FastUpdateStage.ERROR, error="some error", status="")

  layout = software.SoftwareLayout()
  layout._on_download_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.IDLE
  assert state.error == ""
  assert state.status == ""


def test_fast_update_blocks_duplicate_long_press(mocker):
  """Long-press while fast update is active does nothing."""
  from openpilot.system.ui.lib.application import gui_app as real_gui_app
  software._set_fast_update_state(stage=software.FastUpdateStage.FETCHING, status="busy", error="")

  layout = software.SoftwareLayout()
  layout._on_long_press_fast_update()

  # Confirm dialog should NOT have been pushed
  assert real_gui_app.push_widget.call_count == 0


def test_fast_update_duplicate_execution_blocked(mocker):
  """A second _execute_fast_update while one is running is a no-op."""
  software._fast_update_lock.acquire(blocking=False)
  software._set_fast_update_state(stage=software.FastUpdateStage.FETCHING, status="busy", error="")

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  # State should be unchanged (not reset to PREPARING)
  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.FETCHING

  software._fast_update_lock.release()


def test_fast_update_lock_released_on_error(mocker, sync_thread):
  """Lock is released when the worker fails, allowing a retry."""
  mocker.patch.object(software, "subprocess")
  software.subprocess.run.side_effect = [
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # pkill
    RuntimeError("boom"),                                     # rev-parse fails
  ]

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  state = software._get_fast_update_state()
  assert state.stage == software.FastUpdateStage.ERROR

  # Lock should be released
  assert software._fast_update_lock.acquire(blocking=False)
  software._fast_update_lock.release()


def test_fast_update_stages_progress_through_states(mocker, sync_thread):
  """Verify each stage is set during execution by inspecting state after each call."""
  stages_seen = []

  mocker.patch.object(software, "subprocess")

  # Slow down writes so we can observe intermediate state
  original_set = software._set_fast_update_state
  def tracking_set(**kwargs):
    if "stage" in kwargs:
      stages_seen.append(kwargs["stage"])
    return original_set(**kwargs)
  mocker.patch.object(software, "_set_fast_update_state", tracking_set)

  software.subprocess.run.side_effect = [
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # pkill
    mocker.MagicMock(returncode=0, stdout="main\n", stderr=""),     # rev-parse branch
    mocker.MagicMock(returncode=0, stdout="abc123\n", stderr=""),   # rev-parse HEAD
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # fetch
    mocker.MagicMock(returncode=0, stdout="", stderr=""),           # reset --hard
  ]

  layout = software.SoftwareLayout()
  layout._execute_fast_update()

  assert software.FastUpdateStage.PREPARING in stages_seen
  assert software.FastUpdateStage.FETCHING in stages_seen
  assert software.FastUpdateStage.APPLYING in stages_seen
  assert software.FastUpdateStage.REBOOTING in stages_seen
  assert software.FastUpdateStage.ERROR not in stages_seen
