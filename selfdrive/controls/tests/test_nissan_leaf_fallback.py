import cereal.messaging as messaging

from cereal import car, custom
from opendbc.car.nissan.values import CAR as NISSAN_CAR

from openpilot.selfdrive.car.cruise_state import should_cancel_stock_cruise
from openpilot.selfdrive.controls.controlsd import Controls


class FakeFallbackParams:
  def __init__(self, fallback_cp, fallback_fpcp):
    self.values = {
      "CarParams": fallback_cp.to_bytes(),
      "StarPilotCarParams": fallback_fpcp.to_bytes(),
    }

  def get_bool(self, key):
    return key in ("ControlsReady", "EcuDisableFailed")

  def get(self, key):
    return self.values[key]


def test_leaf_ecu_disable_fallback_reloads_read_only_car_params():
  initial_cp = car.CarParams.new_message()
  initial_cp.carFingerprint = NISSAN_CAR.NISSAN_LEAF
  initial_cp.openpilotLongitudinalControl = True
  initial_cp.pcmCruise = False
  initial_fpcp = custom.StarPilotCarParams.new_message()
  initial_fpcp.safetyConfigs = [custom.StarPilotCarParams.SafetyConfig.new_message(safetyParam=2)]

  fallback_cp = car.CarParams.new_message()
  fallback_cp.carFingerprint = NISSAN_CAR.NISSAN_LEAF
  fallback_cp.openpilotLongitudinalControl = False
  fallback_cp.pcmCruise = True
  fallback_fpcp = custom.StarPilotCarParams.new_message()
  fallback_fpcp.safetyConfigs = [custom.StarPilotCarParams.SafetyConfig.new_message(safetyParam=0)]

  initial_cp_reader = messaging.log_from_bytes(initial_cp.to_bytes(), car.CarParams)
  controls = Controls.__new__(Controls)
  controls.CP = initial_cp_reader
  controls.FPCP = messaging.log_from_bytes(initial_fpcp.to_bytes(), custom.StarPilotCarParams)
  controls.params = FakeFallbackParams(fallback_cp, fallback_fpcp)
  controls.ecu_disable_failed = False
  controls.ecu_disable_failed_checked = False

  controls.update_ecu_disable_failed()

  assert controls.ecu_disable_failed
  assert controls.ecu_disable_failed_checked
  assert not controls.CP.openpilotLongitudinalControl
  assert controls.CP.pcmCruise
  assert controls.FPCP.safetyConfigs[0].safetyParam == 0
  assert initial_cp_reader.openpilotLongitudinalControl
  assert not initial_cp_reader.pcmCruise
  assert not should_cancel_stock_cruise(controls.CP, cruise_enabled=True, controls_enabled=True)
