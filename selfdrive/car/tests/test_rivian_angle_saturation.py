import importlib.util
from pathlib import Path
import sys
from types import ModuleType, SimpleNamespace


MODULE_PATH = Path(__file__).resolve().parents[1] / "car_specific.py"


class FakeEvents:
  def __init__(self):
    self.names = []

  def add(self, event):
    self.names.append(event)


def load_car_specific(monkeypatch):
  messaging = ModuleType("cereal.messaging")
  messaging.SubMaster = object
  monkeypatch.setitem(sys.modules, "cereal.messaging", messaging)

  events = ModuleType("openpilot.selfdrive.selfdrived.events")
  events.Events = FakeEvents
  monkeypatch.setitem(sys.modules, "openpilot.selfdrive.selfdrived.events", events)

  spec = importlib.util.spec_from_file_location("rivian_car_specific_under_test", MODULE_PATH)
  assert spec is not None and spec.loader is not None
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def test_angle_saturation_raises_stock_take_control_event(monkeypatch):
  module = load_car_specific(monkeypatch)
  handler = module.CarSpecificEvents(SimpleNamespace(brand="rivian", flags=1))
  handler.rivian_status_params = SimpleNamespace(get_bool=lambda key: key == "RivianAngleSaturated")
  handler.rivian_angle_params = handler.rivian_status_params
  handler.create_common_events = lambda *args, **kwargs: FakeEvents()

  events = None
  for _ in range(5):
    events = handler.update(SimpleNamespace(), SimpleNamespace(), SimpleNamespace())

  assert module.EventName.steerSaturated in events.names


def test_saturation_bridge_is_inert_without_angle_harness(monkeypatch):
  module = load_car_specific(monkeypatch)
  handler = module.CarSpecificEvents(SimpleNamespace(brand="rivian", flags=0))
  handler.create_common_events = lambda *args, **kwargs: FakeEvents()

  events = handler.update(SimpleNamespace(), SimpleNamespace(), SimpleNamespace())

  assert module.EventName.steerSaturated not in events.names


def test_toi_recovery_timeout_raises_temporary_steering_event(monkeypatch):
  module = load_car_specific(monkeypatch)
  handler = module.CarSpecificEvents(SimpleNamespace(brand="rivian", flags=0))
  handler.rivian_status_params = SimpleNamespace(get_bool=lambda key: key == "RivianToiRecoveryFailed")
  handler.create_common_events = lambda *args, **kwargs: FakeEvents()

  events = None
  for _ in range(5):
    events = handler.update(SimpleNamespace(), SimpleNamespace(), SimpleNamespace())

  assert module.EventName.steerTempUnavailable in events.names
