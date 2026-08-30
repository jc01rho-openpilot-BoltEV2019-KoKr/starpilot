import math

from cereal import log
from opendbc.car.subaru.values import CAR as SUBARU_CAR
from openpilot.selfdrive.controls.lib.latcontrol import LatControl

# TODO This is speed dependent
STEER_ANGLE_SATURATION_THRESHOLD = 2.5  # Degrees
FORD_ANGLE_CATCH_UP_HORIZON = 1.25  # Seconds
FORD_ANGLE_RATE_FILTER_TIME_CONSTANT = 0.15  # Seconds

_ASCENT_ANGLE_TRACKING_GAIN = 0.25
_ASCENT_ANGLE_TRACKING_MAX_CORRECTION = 8.0
_ASCENT_ANGLE_TRACKING_MIN_SPEED = 5.0


def _ascent_angle_tracking_target(target_angle: float, steering_angle: float,
                                  v_ego: float, steering_pressed: bool) -> float:
  if steering_pressed or v_ego < _ASCENT_ANGLE_TRACKING_MIN_SPEED:
    return target_angle

  correction = (target_angle - steering_angle) * _ASCENT_ANGLE_TRACKING_GAIN
  correction = max(-_ASCENT_ANGLE_TRACKING_MAX_CORRECTION,
                   min(_ASCENT_ANGLE_TRACKING_MAX_CORRECTION, correction))
  return target_angle + correction


def _ford_angle_tracking_saturated(angle_error: float, steering_rate: float) -> bool:
  """Only call a Ford angle request saturated when the EPS is not on track to catch it."""
  catching_up = angle_error * steering_rate > 0.0
  catching_up &= abs(angle_error) <= abs(steering_rate) * FORD_ANGLE_CATCH_UP_HORIZON
  return abs(angle_error) > STEER_ANGLE_SATURATION_THRESHOLD and not catching_up


class LatControlAngle(LatControl):
  def __init__(self, CP, CI, dt):
    super().__init__(CP, CI, dt)
    self.sat_check_min_speed = 5.
    self.use_steer_limited_by_safety = CP.brand in ("tesla", "hyundai")
    self.is_ascent = CP.carFingerprint == SUBARU_CAR.SUBARU_ASCENT_2023
    self.is_ford = CP.brand == "ford"
    self.measured_angle_last = None
    self.measured_angle_rate = 0.0

  def _update_measured_angle_rate(self, steering_angle: float, reset: bool) -> float:
    if reset or self.measured_angle_last is None:
      self.measured_angle_rate = 0.0
    else:
      raw_rate = (steering_angle - self.measured_angle_last) / self.dt
      alpha = self.dt / (FORD_ANGLE_RATE_FILTER_TIME_CONSTANT + self.dt)
      self.measured_angle_rate += alpha * (raw_rate - self.measured_angle_rate)
    self.measured_angle_last = steering_angle
    return self.measured_angle_rate

  def update(self, active, CS, VM, params, steer_limited_by_safety, desired_curvature, curvature_limited, lat_delay, calibrated_pose, model_data, starpilot_toggles):
    angle_log = log.ControlsState.LateralAngleState.new_message()

    if not active:
      angle_log.active = False
      angle_steers_des = float(CS.steeringAngleDeg)
    else:
      angle_log.active = True
      angle_steers_des = math.degrees(VM.get_steer_from_curvature(-desired_curvature, CS.vEgo, params.roll))
      angle_steers_des += params.angleOffsetDeg

      if self.is_ascent:
        angle_steers_des = _ascent_angle_tracking_target(
          angle_steers_des,
          CS.steeringAngleDeg,
          CS.vEgo,
          bool(getattr(CS, "steeringPressed", False)),
        )

    ford_angle_mode = self.is_ford and getattr(starpilot_toggles, "ford_lateral_mode", -1) == 2
    measured_angle_rate = self._update_measured_angle_rate(
      float(CS.steeringAngleDeg), not active or bool(CS.steeringPressed) or not ford_angle_mode)

    if self.use_steer_limited_by_safety:
      # these cars' carcontrollers calculate max lateral accel and jerk, so we can rely on carOutput for saturation
      angle_control_saturated = steer_limited_by_safety
    else:
      # for cars which use a method of limiting torque such as a torque signal (Nissan and Toyota)
      # or relying on EPS (Ford Q3), carOutput does not capture maxing out torque  # TODO: this can be improved
      angle_error = angle_steers_des - CS.steeringAngleDeg
      if ford_angle_mode:
        angle_control_saturated = _ford_angle_tracking_saturated(angle_error, measured_angle_rate)
      else:
        angle_control_saturated = abs(angle_error) > STEER_ANGLE_SATURATION_THRESHOLD
    angle_log.saturated = bool(self._check_saturation(angle_control_saturated, CS, False, curvature_limited))
    angle_log.steeringAngleDeg = float(CS.steeringAngleDeg)
    angle_log.steeringAngleDesiredDeg = angle_steers_des
    return 0, float(angle_steers_des), angle_log
