"""The torque bar opens a GL scissor; an exception must not leave it open.

An unbalanced scissor corrupts every later frame, which matters now that a failing widget
no longer takes the UI process down with it. The onroad view pulls in the whole device UI
tree (compiled msgq bindings, jwt, ...), so the module is loaded with those stubbed out -
the same pattern test_onroad_render_layers.py uses.
"""
import importlib
import sys
from types import ModuleType, SimpleNamespace

import pytest


def _load_starpilot_onroad_view(monkeypatch):
  def stub_module(name, **attributes):
    module = ModuleType(name)
    for key, value in attributes.items():
      setattr(module, key, value)
    monkeypatch.setitem(sys.modules, name, module)

  # The compiled msgq bindings in a source checkout are device-only.
  ipc = ModuleType("msgq.ipc_pyx")
  for name in ("Context", "Poller", "SubSocket", "PubSocket", "SocketEventHandle",
               "toggle_fake_events", "set_fake_prefix", "get_fake_prefix",
               "delete_fake_prefix", "wait_for_one_event"):
    setattr(ipc, name, object)
  ipc.MultiplePublishersError = type("MultiplePublishersError", (Exception,), {})
  ipc.IpcError = type("IpcError", (Exception,), {})
  monkeypatch.setitem(sys.modules, "msgq.ipc_pyx", ipc)
  stub_module(
    "msgq.visionipc",
    VisionStreamType=SimpleNamespace(VISION_STREAM_ROAD=0, VISION_STREAM_DRIVER=1, VISION_STREAM_WIDE_ROAD=2),
    VisionIpcClient=object,
    VisionIpcServer=object,
    VisionBuf=object,
    get_endpoint_name=lambda *_args: "",
  )

  class AugmentedRoadView:
    pass

  dummy_widget = type("DummyWidget", (), {})
  color = SimpleNamespace(r=0, g=0, b=0, a=255)

  stub_module("openpilot.selfdrive.ui.onroad.augmented_road_view", AugmentedRoadView=AugmentedRoadView)
  stub_module(
    "openpilot.selfdrive.ui.onroad.starpilot.starpilot_border",
    render_behind=lambda *_args: None,
    render_overlay=lambda *_args: None,
    render_background_effects=lambda *_args: None,
  )
  stub_module(
    "openpilot.selfdrive.ui.onroad.starpilot.path",
    render_adjacent_lanes=lambda *_args: None,
    render_path_edges=lambda *_args: None,
  )
  stub_module("openpilot.selfdrive.ui.ui_state", ui_state=SimpleNamespace())
  stub_module("openpilot.selfdrive.ui.onroad.starpilot.torque_bar", TorqueBar=dummy_widget)
  stub_module("openpilot.selfdrive.ui.onroad.starpilot.widget_layout_manager", WidgetLayoutManager=dummy_widget)
  stub_module(
    "openpilot.selfdrive.ui.onroad.starpilot.widgets",
    SetSpeedWidget=dummy_widget,
    SpeedLimitWidget=dummy_widget,
    PedalIconsWidget=dummy_widget,
    AetherGaugeWidget=dummy_widget,
    PersonalityButtonWidget=dummy_widget,
    DriverMonitorWidget=dummy_widget,
    SteeringWheelWidget=dummy_widget,
    StoppedTimerWidget=dummy_widget,
    ModelSourceWidget=dummy_widget,
  )
  stub_module(
    "openpilot.selfdrive.ui.onroad.starpilot.stopping_point",
    render_stopping_point=lambda *_args: None,
  )
  stub_module(
    "openpilot.selfdrive.ui.onroad.starpilot.pause_indicators",
    render_lateral_paused=lambda *_args: None,
    render_longitudinal_paused=lambda *_args: None,
  )
  stub_module("openpilot.selfdrive.ui.onroad.starpilot.weather_icon", render_weather_icon=lambda *_args: None)
  stub_module(
    "openpilot.selfdrive.ui.lib.starpilot_status",
    get_screen_edge_color=lambda *_args: color,
    ENGAGED_COLOR=color,
    EXPERIMENTAL_COLOR=color,
    TRAFFIC_COLOR=color,
  )
  stub_module(
    "openpilot.system.ui.lib.application",
    MousePos=object,
    MouseEvent=object,
    MAX_TOUCH_SLOTS=2,
    gui_app=SimpleNamespace(font=lambda *_args: None, show_touches=False, mouse_events=[]),
    FontWeight=SimpleNamespace(BOLD=0, MEDIUM=1),
  )
  stub_module(
    "openpilot.system.ui.lib.text_measure",
    draw_text_with_shadow=lambda *_args: None,
    measure_text_cached=lambda *_args: SimpleNamespace(x=0, y=0),
  )

  module_name = "openpilot.selfdrive.ui.onroad.starpilot.starpilot_onroad_view"
  monkeypatch.delitem(sys.modules, module_name, raising=False)
  return importlib.import_module(module_name)


def _view_with_scissor_recorder(monkeypatch, scissor_calls, torque_bar, *, enabled=True):
  module = _load_starpilot_onroad_view(monkeypatch)
  monkeypatch.setattr(module.rl, "begin_scissor_mode", lambda *_args: scissor_calls.append("begin"))
  monkeypatch.setattr(module.rl, "end_scissor_mode", lambda: scissor_calls.append("end"))

  view = object.__new__(module.StarPilotOnroadView)
  view._params = SimpleNamespace(get_bool=lambda *_args, **_kwargs: enabled)
  view._content_rect = SimpleNamespace(x=0.0, y=0.0, width=100.0, height=50.0)
  view._torque_bar = torque_bar
  return view


def test_torque_bar_closes_scissor_mode_when_the_widget_raises(monkeypatch):
  scissor_calls: list[str] = []

  class FailingTorqueBar:
    def render(self, _rect):
      raise RuntimeError("torque bar blew up")

  view = _view_with_scissor_recorder(monkeypatch, scissor_calls, FailingTorqueBar())

  with pytest.raises(RuntimeError):
    view._render_torque_bar()

  assert scissor_calls == ["begin", "end"]


def test_torque_bar_closes_scissor_mode_on_success(monkeypatch):
  scissor_calls: list[str] = []
  rendered = []

  class TorqueBar:
    def render(self, _rect):
      rendered.append("torque")

  view = _view_with_scissor_recorder(monkeypatch, scissor_calls, TorqueBar())

  view._render_torque_bar()

  assert rendered == ["torque"]
  assert scissor_calls == ["begin", "end"]


def test_torque_bar_opens_no_scissor_when_disabled(monkeypatch):
  scissor_calls: list[str] = []
  view = _view_with_scissor_recorder(monkeypatch, scissor_calls, None, enabled=False)

  view._render_torque_bar()

  assert scissor_calls == []
