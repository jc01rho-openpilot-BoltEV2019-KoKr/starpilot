from types import SimpleNamespace

from openpilot.starpilot.common import starpilot_variables as spv


def test_legacy_volt_stock_acc_models_share_sng_and_auto_hold_scope():
  assert spv.LEGACY_VOLT_STOCK_ACC_CARS == {
    "CHEVROLET_VOLT",
    "CHEVROLET_VOLT_2019",
    "CHEVROLET_VOLT_ASCM",
    "CHEVROLET_VOLT_CAMERA",
  }


def test_get_starpilot_toggles_uses_last_non_empty_broadcast(monkeypatch):
  params = SimpleNamespace(get_bool=lambda _key: False)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  monkeypatch.delattr(spv.get_starpilot_toggles, "_last_toggles_text", raising=False)

  payload = '{"always_on_lateral": true, "vision_speed_limit_detection": true}'
  sm_with_toggles = {"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}
  sm_without_toggles = {"starpilotPlan": SimpleNamespace(starpilotToggles="")}

  first = spv.get_starpilot_toggles(sm_with_toggles)
  second = spv.get_starpilot_toggles(sm_without_toggles)

  assert first.always_on_lateral is True
  assert second.always_on_lateral is True
  assert second.vision_speed_limit_detection is True


class _FakeParams:
  def __init__(self, floats=None):
    self.floats = dict(floats or {})

  def get_float(self, key):
    return float(self.floats.get(key, 0.0))

  def put_float(self, key, value):
    self.floats[key] = float(value)

  def remove(self, key):
    self.floats.pop(key, None)


def test_sync_stock_param_does_not_stomp_existing_custom_value_when_stock_missing():
  params = _FakeParams({"SteerDelay": 0.35, "SteerDelayStock": 0.0})
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = params

  variables._sync_stock_param("SteerDelay", "SteerDelayStock", 0.10)

  assert params.get_float("SteerDelay") == 0.35
  assert params.get_float("SteerDelayStock") == 0.10
