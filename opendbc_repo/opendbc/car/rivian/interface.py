from opendbc.car import get_safety_config, structs
from opendbc.car.interfaces import CarInterfaceBase
from opendbc.car.rivian.carcontroller import CarController
from opendbc.car.rivian.carstate import CarState
from opendbc.car.rivian.radar_interface import RadarInterface
from opendbc.car.rivian.values import RivianFlags, RivianSafetyFlags


class CarInterface(CarInterfaceBase):
  CarState = CarState
  CarController = CarController
  RadarInterface = RadarInterface

  @staticmethod
  def _apply_angle_caps(ret: structs.CarParams) -> None:
    """Enable capabilities that are safe only with the xnor Extreme angle box."""
    ret.flags |= RivianFlags.ANGLE_HARNESS.value
    ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.ANGLE_CONTROL.value
    ret.steerActuatorDelay = 0.1
    ret.lateralSmoothSeconds = 0.4
    ret.steerAtStandstill = True

  @staticmethod
  def _get_params(ret: structs.CarParams, candidate, fingerprint, car_fw, alpha_long, is_release, docs) -> structs.CarParams:
    ret.brand = "rivian"

    ret.safetyConfigs = [get_safety_config(structs.CarParams.SafetyModel.rivian)]

    # Gen 2 (2025+) does not publish SCCM_WheelTouch on the powertrain bus.
    if 0x321 not in fingerprint[0]:
      ret.flags |= RivianFlags.GEN2.value

    angle_harness = 0x1310 in fingerprint[1]
    longitudinal_harness = 0x131A in fingerprint[1]

    if angle_harness:
      CarInterface._apply_angle_caps(ret)

    if longitudinal_harness:
      ret.flags |= RivianFlags.LONGITUDINAL_HARNESS.value

    # A base comma harness and the xnor longitudinal harness are valid torque
    # configurations. Angle-only caps remain gated to the detected Extreme box.
    if not angle_harness:
      ret.steerActuatorDelay = 0.15
      ret.lateralSmoothSeconds = 0.0
      ret.steerAtStandstill = False
    ret.steerLimitTimer = 0.4
    CarInterfaceBase.configure_torque_tune(candidate, ret.lateralTuning)

    ret.steerControlType = structs.CarParams.SteerControlType.torque
    ret.radarUnavailable = not longitudinal_harness
    ret.enableBsm = longitudinal_harness

    ret.alphaLongitudinalAvailable = longitudinal_harness
    if alpha_long and ret.alphaLongitudinalAvailable:
      ret.openpilotLongitudinalControl = True
      ret.safetyConfigs[0].safetyParam |= RivianSafetyFlags.LONG_CONTROL.value

    # AdventurePilot road data measured roughly 0.26-0.38 s command-to-aEgo
    # lag. 0.3 s puts the planner near the center of the observed plant delay.
    ret.longitudinalActuatorDelay = 0.3
    ret.vEgoStopping = 0.25
    ret.stopAccel = -0.2
    ret.longitudinalTuning.kiBP = [0.]
    ret.longitudinalTuning.kiV = [0.2]

    return ret
