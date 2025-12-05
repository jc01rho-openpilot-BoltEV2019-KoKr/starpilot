import math
import numpy as np
from collections import deque

from cereal import log
from openpilot.common.filter_simple import FirstOrderFilter
from openpilot.selfdrive.car.interfaces import FRICTION_THRESHOLD
from openpilot.selfdrive.controls.lib.drive_helpers import MIN_SPEED, get_friction
from openpilot.selfdrive.controls.lib.latcontrol import LatControl
from openpilot.selfdrive.controls.lib.pid import PIDController
from openpilot.selfdrive.controls.lib.vehicle_model import ACCELERATION_DUE_TO_GRAVITY

# At higher speeds (25+mph) we can assume:
# Lateral acceleration achieved by a specific car correlates to
# torque applied to the steering rack. It does not correlate to
# wheel slip, or to speed.

# This controller applies torque to achieve desired lateral
# accelerations. To compensate for the low speed effects the
# proportional gain is increased at low speeds by the PID controller.
# Additionally, there is friction in the steering wheel that needs
# to be overcome to move it at all, this is compensated for too.

# Enhanced PID gains for better lane centering
KP = 0.9
KI = 0.45
KD = 0.08

# Speed interpolation for adaptive gains - smoother transitions
INTERP_SPEEDS = [1, 1.5, 2.0, 3.0, 5, 7.5, 10, 15, 25, 35]
KP_INTERP = [270, 135, 75, 35, 13, 6.5, 4.0, 2.3, 1.2, KP]

LP_FILTER_CUTOFF_HZ = 1.2
LAT_ACCEL_REQUEST_BUFFER_SECONDS = 1.0
VERSION = 1  # Version bump for adaptive lane centering

# Adaptive lane centering parameters
ERROR_SMOOTHING_FACTOR = 0.15  # Exponential smoothing for error (0-1, lower = smoother)
MIN_ERROR_THRESHOLD = 0.02  # Ignore very small errors to reduce jitter
LANE_CENTER_BOOST_SPEED = [5, 15, 30, 45]  # m/s
LANE_CENTER_BOOST_FACTOR = [1.3, 1.15, 1.0, 0.95]  # Boost factor at different speeds


class LatControlTorque(LatControl):
  def __init__(self, CP, CI, dt):
    super().__init__(CP, CI, dt)
    self.torque_params = CP.lateralTuning.torque
    self.torque_from_lateral_accel = CI.torque_from_lateral_accel()
    self.lateral_accel_from_torque = CI.lateral_accel_from_torque()
    self.pid = PIDController([INTERP_SPEEDS, KP_INTERP], KI, KD, rate=1/self.dt)
    self.update_limits()
    self.steering_angle_deadzone_deg = self.torque_params.steeringAngleDeadzoneDeg
    self.lat_accel_request_buffer_len = int(LAT_ACCEL_REQUEST_BUFFER_SECONDS / self.dt)
    self.lat_accel_request_buffer = deque([0.] * self.lat_accel_request_buffer_len , maxlen=self.lat_accel_request_buffer_len)
    self.previous_measurement = 0.0
    self.measurement_rate_filter = FirstOrderFilter(0.0, 1 / (2 * np.pi * LP_FILTER_CUTOFF_HZ), self.dt)

    # Adaptive lane centering state
    self.smoothed_error = 0.0
    self.previous_output_torque = 0.0
    self.lane_centering_active = False

  def update_live_torque_params(self, latAccelFactor, latAccelOffset, friction):
    self.torque_params.latAccelFactor = latAccelFactor
    self.torque_params.latAccelOffset = latAccelOffset
    self.torque_params.friction = friction
    self.update_limits()

  def update_limits(self):
    self.pid.set_limits(self.lateral_accel_from_torque(self.steer_max, self.torque_params),
                        self.lateral_accel_from_torque(-self.steer_max, self.torque_params))

  def get_adaptive_correction(self, error, v_ego):
    """Apply adaptive lane centering correction based on speed and error magnitude"""
    # Speed-dependent boost factor for lane centering
    boost_factor = np.interp(v_ego, LANE_CENTER_BOOST_SPEED, LANE_CENTER_BOOST_FACTOR)

    # Apply exponential smoothing to error for smoother corrections
    alpha = ERROR_SMOOTHING_FACTOR
    self.smoothed_error = alpha * error + (1 - alpha) * self.smoothed_error

    # Apply minimum error threshold to reduce micro-corrections
    if abs(self.smoothed_error) < MIN_ERROR_THRESHOLD:
      corrected_error = 0.0
    else:
      # Smooth error correction with boost factor
      corrected_error = self.smoothed_error * boost_factor

    return corrected_error

  def smooth_output(self, output_torque, v_ego):
    """Apply output smoothing to prevent jerky steering"""
    # Rate limit the torque change based on speed
    max_rate = np.interp(v_ego, [5, 15, 30], [0.15, 0.10, 0.08])  # Lower rate at high speed

    delta = output_torque - self.previous_output_torque
    if abs(delta) > max_rate:
      output_torque = self.previous_output_torque + np.sign(delta) * max_rate

    self.previous_output_torque = output_torque
    return output_torque

  def update(self, active, CS, VM, params, steer_limited_by_safety, desired_curvature, curvature_limited, lat_delay, llk, model_data, frogpilot_toggles):
    pid_log = log.ControlsState.LateralTorqueState.new_message()
    pid_log.version = VERSION
    if not active:
      output_torque = 0.0
      pid_log.active = False
      # Reset smoothing state when inactive
      self.smoothed_error = 0.0
      self.previous_output_torque = 0.0
      self.lane_centering_active = False
    else:
      measured_curvature = -VM.calc_curvature(math.radians(CS.steeringAngleDeg - params.angleOffsetDeg), CS.vEgo, params.roll)
      roll_compensation = params.roll * ACCELERATION_DUE_TO_GRAVITY
      curvature_deadzone = abs(VM.calc_curvature(math.radians(self.steering_angle_deadzone_deg), CS.vEgo, 0.0))
      lateral_accel_deadzone = curvature_deadzone * CS.vEgo ** 2

      delay_frames = int(np.clip(lat_delay / self.dt, 1, self.lat_accel_request_buffer_len))
      expected_lateral_accel = self.lat_accel_request_buffer[-delay_frames]
      future_desired_lateral_accel = desired_curvature * CS.vEgo ** 2
      self.lat_accel_request_buffer.append(future_desired_lateral_accel)
      gravity_adjusted_future_lateral_accel = future_desired_lateral_accel - roll_compensation

      # Smoother lateral jerk calculation
      desired_lateral_jerk = (future_desired_lateral_accel - expected_lateral_accel) / lat_delay

      measurement = measured_curvature * CS.vEgo ** 2
      measurement_rate = self.measurement_rate_filter.update((measurement - self.previous_measurement) / self.dt)
      self.previous_measurement = measurement

      setpoint = lat_delay * desired_lateral_jerk + expected_lateral_accel
      raw_error = setpoint - measurement

      # Apply adaptive lane centering correction
      error = self.get_adaptive_correction(raw_error, CS.vEgo)

      # Detect if we're actively centering in lane
      self.lane_centering_active = abs(desired_curvature) < 0.001 and CS.vEgo > 5

      pid_log.error = float(error)
      ff = gravity_adjusted_future_lateral_accel
      ff -= self.torque_params.latAccelOffset

      # Enhanced friction compensation with adaptive scaling
      friction_scale = 1.0 if self.lane_centering_active else 0.9
      ff += get_friction(error, lateral_accel_deadzone, FRICTION_THRESHOLD, self.torque_params) * friction_scale

      # Improved integrator freeze conditions
      # Freeze when: safety limited, driver steering, very low speed, or high lateral acceleration (in curve)
      in_sharp_curve = abs(measurement) > 2.5
      freeze_integrator = steer_limited_by_safety or CS.steeringPressed or CS.vEgo < 3 or in_sharp_curve

      output_lataccel = self.pid.update(pid_log.error,
                                       -measurement_rate,
                                        feedforward=ff,
                                        speed=CS.vEgo,
                                        freeze_integrator=freeze_integrator)
      output_torque = self.torque_from_lateral_accel(output_lataccel, self.torque_params)

      # Apply output smoothing for smoother steering
      output_torque = self.smooth_output(output_torque, CS.vEgo)

      pid_log.active = True
      pid_log.p = float(self.pid.p)
      pid_log.i = float(self.pid.i)
      pid_log.d = float(self.pid.d)
      pid_log.f = float(self.pid.f)
      pid_log.output = float(-output_torque)
      pid_log.actualLateralAccel = float(measurement)
      pid_log.desiredLateralAccel = float(setpoint)
      pid_log.desiredLateralJerk = float(desired_lateral_jerk)
      pid_log.saturated = bool(self._check_saturation(self.steer_max - abs(output_torque) < 1e-3, CS, steer_limited_by_safety, curvature_limited))

    # TODO left is positive in this convention
    return -output_torque, 0.0, pid_log

