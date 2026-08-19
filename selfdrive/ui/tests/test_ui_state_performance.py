import time
from types import SimpleNamespace

from openpilot.selfdrive.ui.lib.ui_param_cache import UIParamCache
from openpilot.selfdrive.ui import ui_state as ui_state_module


def test_raylib_ui_uses_read_through_param_cache():
  assert isinstance(ui_state_module.ui_state.ui_params, UIParamCache)
  assert ui_state_module.ui_state.ui_params is not ui_state_module.ui_state.params


def test_usbgpu_presence_comes_from_device_state_and_persists_onroad():
  state = object.__new__(ui_state_module.UIState)
  state.usbgpu = False
  state.started = True

  state._update_usbgpu_presence(True)
  assert state.usbgpu

  state._update_usbgpu_presence(False)
  assert state.usbgpu

  state.started = False
  state._update_usbgpu_presence(False)
  assert not state.usbgpu


def test_ui_update_reports_subphases(monkeypatch):
  phases = []
  calls = []
  state = object.__new__(ui_state_module.UIState)
  state.prime_state = SimpleNamespace(start=lambda: calls.append("prime"))
  state.sm = SimpleNamespace(update=lambda timeout: calls.append(("submaster", timeout)))
  def update_state(progress_hook):
    progress_hook("ui.update.before_state_params")
    calls.append("state")
    progress_hook("ui.update.after_state_params")

  state._update_state = update_state
  state._update_status = lambda progress_hook: calls.append("status")
  state._param_update_time = time.monotonic()
  monkeypatch.setattr(ui_state_module, "device", SimpleNamespace(update=lambda: calls.append("device")))

  state.update(progress_hook=phases.append)

  assert calls == ["prime", ("submaster", 0), "state", "status", "device"]
  assert phases == [
    "ui.update.before_prime_state",
    "ui.update.before_submaster",
    "ui.update.before_state",
    "ui.update.before_state_params",
    "ui.update.after_state_params",
    "ui.update.before_status",
    "ui.update.before_params",
    "ui.update.before_device",
    "ui.update.after_device",
  ]


def test_ui_update_reports_offroad_callback(monkeypatch):
  phases = []
  callback_calls = []
  state = object.__new__(ui_state_module.UIState)
  state.started = False
  state._started_prev = True
  state._engaged_prev = False
  state.status = ui_state_module.UIStatus.DISENGAGED
  state.sm = SimpleNamespace(frame=2)
  state._offroad_transition_callbacks = [lambda: callback_calls.append("offroad")]
  state._engaged_transition_callbacks = []

  state._update_status(phases.append)

  assert callback_calls == ["offroad"]
  assert phases == [
    "ui.update.before_offroad_callback.<lambda>",
    "ui.update.after_offroad_callback.<lambda>",
  ]
