import threading

from openpilot.selfdrive.ui.lib.ui_param_cache import UIParamCache
from openpilot.selfdrive.ui import ui_state as ui_state_module


def test_raylib_ui_uses_read_through_param_cache():
  assert isinstance(ui_state_module.ui_state.ui_params, UIParamCache)
  assert ui_state_module.ui_state.ui_params is not ui_state_module.ui_state.params


def test_usbgpu_poll_does_not_block_ui_thread(monkeypatch):
  started = threading.Event()
  release = threading.Event()

  def poll():
    started.set()
    release.wait(timeout=1.0)
    return True

  monkeypatch.setattr(ui_state_module, "chestnut_present", poll)
  state = object.__new__(ui_state_module.UIState)
  state.usbgpu = False
  state._usbgpu_update_time = 0.0
  state._usbgpu_poll_thread = None

  state._schedule_usbgpu_poll(now=1.0, force=True)
  assert started.wait(timeout=0.2)
  polling_thread = state._usbgpu_poll_thread
  state._schedule_usbgpu_poll(now=2.0, force=True)
  assert state._usbgpu_poll_thread is polling_thread

  release.set()
  polling_thread.join(timeout=1.0)
  assert state.usbgpu is True
