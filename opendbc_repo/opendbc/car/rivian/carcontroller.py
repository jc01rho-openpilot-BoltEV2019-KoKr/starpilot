import numpy as np
from opendbc.can import CANPacker
from opendbc.car import Bus, structs
from opendbc.car.lateral import apply_driver_steer_torque_limits
from opendbc.car.interfaces import CarControllerBase
from opendbc.car.rivian.ext_controller import HIGH_ANGLE_CAP_FRAC, HIGH_ANGLE_THRESHOLD_DEG, ExternalController
from opendbc.car.rivian.riviancan import (create_acm_status, create_adas_status, create_angle_steering,
                                          create_lka_steering, create_longitudinal, create_wheel_touch)
from opendbc.car.rivian.toi_controller import TOI_MAX_ANGLE_DEG, ToiController
from opendbc.car.rivian.values import CarControllerParams, RivianFlags

GearShifter = structs.CarState.GearShifter
LateralControlMode = structs.CarControl.Actuators.LateralControlMode


def get_longitudinal_accel(requested_accel: float, gas_pressed: bool, long_active: bool = False,
                           v_ego: float = 0.0) -> float:
  # Keep Rivian's command stream continuous when Panda's gas safety check becomes active.
  if gas_pressed:
    return 0.0

  accel = requested_accel
  if long_active:
    accel += float(np.interp(v_ego, CarControllerParams.ACCEL_FF_DRAG_BP, CarControllerParams.ACCEL_FF_DRAG_V))
  return float(np.clip(accel, CarControllerParams.ACCEL_MIN, CarControllerParams.ACCEL_MAX))


class CarController(CarControllerBase):
  def __init__(self, dbc_names, CP):
    super().__init__(dbc_names, CP)
    self.apply_torque_last = 0
    self.packer = CANPacker(dbc_names[Bus.pt])

    self.cancel_frames = 0
    self.toi_controller = ToiController()
    self.angle_harness = bool(CP.flags & RivianFlags.ANGLE_HARNESS)
    self.ext_controller = ExternalController(CP) if self.angle_harness else None
    self.angle_saturation_last = None
    self.angle_saturation_params = None
    self.toi_recovery_failed_last = None
    self.toi_recovery_params = None
    try:
      # Keep opendbc importable standalone while exposing controller-only state
      # to selfdrived's existing car-specific warning bridge.
      from openpilot.common.params import Params
      status_params = Params(memory=True)
      self.toi_recovery_params = status_params
      if self.angle_harness:
        self.angle_saturation_params = status_params
    except Exception:
      pass

  def _publish_angle_saturation(self) -> None:
    params = getattr(self, "angle_saturation_params", None)
    if params is None:
      return

    saturated = bool(self.ext_controller.angle_saturated)
    if saturated != getattr(self, "angle_saturation_last", None):
      put_bool = getattr(params, "put_bool_nonblocking", None) or params.put_bool
      put_bool("RivianAngleSaturated", saturated)
      self.angle_saturation_last = saturated

  def _publish_toi_recovery_failed(self) -> None:
    params = getattr(self, "toi_recovery_params", None)
    if params is None:
      return

    toi_controller = self.ext_controller.toi_controller if self.angle_harness else self.toi_controller
    failed = bool(toi_controller.recovery_failed)
    if failed != getattr(self, "toi_recovery_failed_last", None):
      put_bool = getattr(params, "put_bool_nonblocking", None) or params.put_bool
      put_bool("RivianToiRecoveryFailed", failed)
      self.toi_recovery_failed_last = failed

  def update_live_params(self, roll, angle_offset_deg, stiffness_factor, steer_ratio):
    if self.ext_controller is not None:
      self.ext_controller.roll = roll
      self.ext_controller.angle_offset_deg = angle_offset_deg
      self.ext_controller.VM.update_params(max(stiffness_factor, 0.1), max(steer_ratio, 0.1))

  def update(self, CC, CS, now_nanos, starpilot_toggles):
    actuators = CC.actuators
    can_sends = []

    lat_active = CC.latActive and CS.out.gearShifter == GearShifter.drive
    apply_torque = 0
    torque_request = False
    steer_max = round(float(np.interp(CS.out.vEgoRaw, CarControllerParams.STEER_MAX_LOOKUP[0],
                                      CarControllerParams.STEER_MAX_LOOKUP[1])))
    if self.angle_harness:
      # The Panda permission is capability-gated at fingerprint time; this
      # runtime setting only selects which already-safe channel is active.
      self.ext_controller.force_torque = not bool(getattr(starpilot_toggles, "rivian_angle_control", False))
      self.ext_controller.update(CS, lat_active, actuators)
      self._publish_angle_saturation()
      apply_torque = self.ext_controller.torque_cmd
      torque_request = self.ext_controller.toi_act_cmd
    else:
      torque_request, torque_allowed = self.toi_controller.update(
        lat_active,
        abs(CS.out.steeringAngleDeg) >= TOI_MAX_ANGLE_DEG,
        bool(getattr(CS, "toi_fault", False)),
        bool(getattr(CS, "toi_active", False)),
        bool(getattr(CS, "toi_unavailable", False)),
      )

      if lat_active and torque_allowed:
        new_torque = int(round(CC.actuators.torque * steer_max))
        apply_torque = apply_driver_steer_torque_limits(new_torque, self.apply_torque_last,
                                                        CS.out.steeringTorque, CarControllerParams, steer_max)
        if abs(CS.out.steeringAngleDeg) > HIGH_ANGLE_THRESHOLD_DEG:
          cap = int(round(steer_max * HIGH_ANGLE_CAP_FRAC))
          apply_torque = int(np.clip(apply_torque, -cap, cap))

    self.apply_torque_last = apply_torque
    self._publish_toi_recovery_failed()
    can_sends.append(create_lka_steering(self.packer, self.frame, CS.acm_lka_hba_cmd,
                                         apply_torque, CC.enabled, torque_request))

    if self.angle_harness:
      can_sends.append(create_angle_steering(self.packer, self.frame, self.ext_controller.apply_angle_last,
                                             self.ext_controller.angle_active))
      feature_status = (1 if self.ext_controller.torque_active else 2) if lat_active else 0
      can_sends.append(create_acm_status(self.packer, self.frame, feature_status))

    if self.frame % 5 == 0 and not (self.CP.flags & RivianFlags.GEN2):
      can_sends.append(create_wheel_touch(self.packer, CS.sccm_wheel_touch, lat_active if self.angle_harness else CC.enabled))

    # Longitudinal control
    if self.CP.openpilotLongitudinalControl:
      accel = get_longitudinal_accel(actuators.accel, CS.out.gasPressed, CC.longActive, CS.out.vEgo)
      can_sends.append(create_longitudinal(self.packer, self.frame, accel, CC.enabled))
    else:
      interface_status = None
      if CC.cruiseControl.cancel:
        # if there is a noEntry, we need to send a status of "available" before the ACM will accept "unavailable"
        # send "available" right away as the VDM itself takes a few frames to acknowledge
        interface_status = 1 if self.cancel_frames < 5 else 0
        self.cancel_frames += 1
      else:
        self.cancel_frames = 0

      for msg in CS.vdm_adas_status:
        can_sends.append(create_adas_status(self.packer, msg, interface_status))

    new_actuators = actuators.as_builder()
    # Always report the actual applied torque. In angle mode this is zero, which
    # deliberately freezes the torque PID integrator instead of letting it wind
    # up and dump saturated torque into the first cooperative handoff.
    new_actuators.torque = apply_torque / steer_max
    new_actuators.torqueOutputCan = apply_torque
    lateral_mode = LateralControlMode.inactive
    if self.angle_harness:
      new_actuators.steeringAngleDeg = self.ext_controller.apply_angle_last
      if lat_active and self.ext_controller.toi_controller.recovering:
        lateral_mode = LateralControlMode.torqueRecovering
      elif lat_active and (self.ext_controller.torque_active or self.ext_controller.torque_prearm):
        lateral_mode = LateralControlMode.torque
      elif lat_active and self.ext_controller.angle_active:
        lateral_mode = LateralControlMode.angle
    elif lat_active:
      lateral_mode = LateralControlMode.torqueRecovering if self.toi_controller.recovering else LateralControlMode.torque
    new_actuators.lateralControlMode = lateral_mode

    self.frame += 1
    return new_actuators, can_sends
