import numpy as np

from opendbc.car.gm.values import CAR, GMFlags
from openpilot.common.realtime import DT_CTRL
from openpilot.starpilot.common.testing_grounds import testing_ground


clip = np.clip
interp = np.interp

BOLT_ACC_PEDAL_REGEN_LIMIT_BP = [0.0, 1.5, 4.0, 8.0, 15.0, 30.0]
BOLT_ACC_PEDAL_REGEN_LIMIT_V = [-0.93, -1.28, -1.98, -2.58, -2.86, -2.95]
NEGATIVE_TARGET_CREEP_GUARD_SPEED = 0.35
NEGATIVE_TARGET_CREEP_GUARD_DECEL = 0.40
GM_TRUCK_TARGET_FILTER_MIN_SPEED = 12.0
GM_TRUCK_TARGET_FILTER_UP_TAU = 0.10
GM_TRUCK_TARGET_FILTER_DOWN_TAU = 0.06
GM_TRUCK_TARGET_FILTER_BRAKE_BYPASS = -0.65
GM_TRUCK_TARGET_FILTER_DROP_BYPASS = 0.45


def get_bolt_acc_pedal_friction_bias(output_accel, a_target, v_ego):
  if output_accel >= -0.05 or a_target >= -0.80 or v_ego <= 5.0:
    return 0.0

  authority_gap = max(0.0, abs(a_target) - abs(output_accel))
  if authority_gap <= 0.25:
    return 0.0

  speed_factor = interp(v_ego, [5.0, 10.0, 15.0, 25.0], [0.0, 0.55, 0.85, 1.0])
  max_bias = interp(abs(a_target), [0.8, 1.4, 2.2, 3.5], [0.0, 0.14, 0.42, 0.70])
  return float(min(authority_gap * 0.30, max_bias) * speed_factor)


def get_bolt_acc_pedal_friction_floor(a_target, v_ego, pedal_regen_limit):
  if v_ego <= 5.0 or a_target >= (pedal_regen_limit - 0.05):
    return None

  friction_request = max(0.0, pedal_regen_limit - a_target)
  if friction_request <= 0.10:
    return None

  speed_factor = interp(v_ego, [5.0, 8.0, 12.0, 18.0, 25.0], [0.0, 0.45, 0.75, 0.90, 1.0])
  demand_factor = interp(friction_request, [0.10, 0.25, 0.50, 0.90, 1.30], [0.0, 0.22, 0.50, 0.78, 1.0])
  floor_fraction = float(clip(speed_factor * demand_factor, 0.0, 1.0))

  return float(pedal_regen_limit - (friction_request * floor_fraction))


def get_bolt_acc_pedal_feedforward_gain(feedforward_gain, a_target, v_ego, pedal_regen_limit, last_output_accel):
  effective_gain = feedforward_gain
  if a_target >= 0.0:
    return effective_gain

  restore = 0.0

  if a_target < pedal_regen_limit:
    friction_gap = pedal_regen_limit - a_target
    restore = float(interp(friction_gap, [0.0, 0.25, 0.75], [0.0, 0.6, 1.0]))

  if v_ego > 5.0 and a_target < -1.10:
    authority_gap = max(0.0, abs(a_target) - abs(min(last_output_accel, 0.0)))
    target_restore = float(interp(abs(a_target), [1.1, 1.6, 2.2, 3.0], [0.0, 0.25, 0.55, 1.0]))
    gap_restore = float(interp(authority_gap, [0.2, 0.6, 1.0, 1.6], [0.0, 0.25, 0.60, 1.0]))
    speed_factor = float(interp(v_ego, [5.0, 8.0, 12.0, 18.0], [0.0, 0.35, 0.75, 1.0]))
    restore = max(restore, max(target_restore, gap_restore) * speed_factor)

  return float(feedforward_gain + ((1.0 - feedforward_gain) * clip(restore, 0.0, 1.0)))


class LongControlVehicleTuning:
  def __init__(self, CP):
    self.is_gm_pedal_long = bool(
      CP.brand == "gm" and CP.enableGasInterceptorDEPRECATED and (CP.flags & GMFlags.PEDAL_LONG.value)
    )
    self.is_volt = bool(
      CP.brand == "gm" and str(CP.carFingerprint).startswith("CHEVROLET_VOLT")
    )
    self.is_gm_stock_truck = bool(
      CP.brand == "gm" and
      getattr(CP, "carFingerprint", None) in (CAR.CHEVROLET_SILVERADO, CAR.CHEVROLET_SILVERADO_CC) and
      not CP.enableGasInterceptorDEPRECATED
    )
    self.is_bolt_acc_pedal_friction_car = bool(
      CP.brand == "gm" and
      CP.enableGasInterceptorDEPRECATED and
      getattr(CP, "carFingerprint", None) == CAR.CHEVROLET_BOLT_ACC_2022_2023_PEDAL and
      (CP.flags & GMFlags.PEDAL_LONG.value)
    )
    self.reset()

  def reset(self):
    self.last_a_target = 0.0
    self.integrator_hold_frames = 0
    self.gm_truck_filtered_a_target = 0.0
    self.gm_truck_target_filter_initialized = False

  def shape_gm_truck_accel_target(self, a_target, v_ego, should_stop):
    if not self.is_gm_stock_truck:
      return a_target

    bypass_filter = (
      v_ego < GM_TRUCK_TARGET_FILTER_MIN_SPEED or
      should_stop or
      a_target <= GM_TRUCK_TARGET_FILTER_BRAKE_BYPASS or
      (self.gm_truck_target_filter_initialized and
       a_target < self.gm_truck_filtered_a_target - GM_TRUCK_TARGET_FILTER_DROP_BYPASS)
    )
    if not self.gm_truck_target_filter_initialized or bypass_filter:
      self.gm_truck_filtered_a_target = float(a_target)
      self.gm_truck_target_filter_initialized = True
      return float(a_target)

    tau = GM_TRUCK_TARGET_FILTER_DOWN_TAU if a_target < self.gm_truck_filtered_a_target else GM_TRUCK_TARGET_FILTER_UP_TAU
    alpha = DT_CTRL / (tau + DT_CTRL)
    self.gm_truck_filtered_a_target += alpha * (float(a_target) - self.gm_truck_filtered_a_target)
    return self.gm_truck_filtered_a_target

  def get_integrator_freeze(self, last_output_accel, a_target, error, v_ego, accel_limits):
    volt_test_tune_handoff = self.is_volt and testing_ground.use_2

    if not self.is_gm_pedal_long and not volt_test_tune_handoff:
      self.last_a_target = a_target
      self.integrator_hold_frames = 0
      return False

    if self.is_gm_pedal_long:
      handoff_threshold = interp(v_ego, [0.0, 4.0, 12.0, 25.0], [0.35, 0.45, 0.55, 0.70])
      hold_frames = int(round(interp(v_ego, [0.0, 4.0, 12.0, 25.0], [25.0, 20.0, 14.0, 10.0])))
    else:
      handoff_threshold = interp(v_ego, [0.0, 4.0, 12.0, 25.0], [0.24, 0.30, 0.38, 0.48])
      hold_frames = int(round(interp(v_ego, [0.0, 4.0, 12.0, 25.0], [12.0, 10.0, 8.0, 6.0])))

    if abs(a_target - self.last_a_target) > handoff_threshold:
      self.integrator_hold_frames = max(self.integrator_hold_frames, hold_frames)
    self.last_a_target = a_target

    if self.integrator_hold_frames > 0:
      self.integrator_hold_frames -= 1

    sat_buffer = 0.03
    at_neg_sat = last_output_accel <= (accel_limits[0] + sat_buffer)
    at_pos_sat = last_output_accel >= (accel_limits[1] - sat_buffer)
    sat_pushing_lower = at_neg_sat and error < -0.05
    sat_pushing_upper = at_pos_sat and error > 0.05

    return self.integrator_hold_frames > 0 or sat_pushing_lower or sat_pushing_upper

  def shape_volt_test_tune_integrator(self, pid, error, v_ego):
    if not (self.is_volt and testing_ground.use_2):
      return

    if pid.i * error < 0.0 and abs(error) > 0.05:
      bleed = interp(v_ego, [0.0, 4.0, 12.0, 25.0], [0.82, 0.86, 0.90, 0.94])
      pid.i *= bleed

  def trim_gm_truck_positive_hold_integrator(self, pid, last_output_accel, a_target, error, CS):
    if not self.is_gm_stock_truck or pid.i <= 0.0:
      return
    if last_output_accel <= 0.10:
      return
    light_accel_threshold = float(interp(CS.vEgo, [8.0, 15.0, 25.0], [0.03, 0.06, 0.10]))
    if a_target > light_accel_threshold:
      return
    if CS.vEgo <= NEGATIVE_TARGET_CREEP_GUARD_SPEED and a_target > -NEGATIVE_TARGET_CREEP_GUARD_DECEL:
      return

    authority_mismatch = last_output_accel - max(a_target, 0.0)
    if authority_mismatch <= 0.08 and error > -0.08:
      return

    target_factor = float(interp(a_target, [-0.30, -0.10, -0.02, light_accel_threshold], [0.20, 0.35, 0.60, 0.98]))
    if error < -0.20:
      target_factor *= 0.75
    pid.i *= target_factor

  def trim_gm_truck_negative_hold_integrator(self, pid, last_output_accel, a_target, error, CS):
    if not self.is_gm_stock_truck or pid.i >= -0.02:
      return
    if CS.vEgo < 12.0 or a_target <= -0.85:
      return
    if error <= 0.04:
      return

    authority_mismatch = float(a_target) - float(last_output_accel)
    if authority_mismatch <= 0.10:
      return

    release = float(interp(
      max(authority_mismatch, error),
      [0.10, 0.25, 0.50],
      [0.0008, 0.0020, 0.0040],
    ))
    pid.i = min(0.0, pid.i + release)

  def apply_pedal_long_brake_bias(self, output_accel, a_target, CS):
    if not self.is_gm_pedal_long:
      return output_accel
    if output_accel >= -0.05 or a_target >= -0.80:
      return output_accel
    if CS.vEgo <= 5.0:
      return output_accel

    authority_gap = max(0.0, abs(a_target) - abs(output_accel))
    if self.is_bolt_acc_pedal_friction_car:
      pedal_regen_limit = float(interp(CS.vEgo, BOLT_ACC_PEDAL_REGEN_LIMIT_BP, BOLT_ACC_PEDAL_REGEN_LIMIT_V))
      bias = get_bolt_acc_pedal_friction_bias(output_accel, a_target, CS.vEgo)
      floor = get_bolt_acc_pedal_friction_floor(a_target, CS.vEgo, pedal_regen_limit)
      if floor is not None:
        bias = max(bias, output_accel - floor)
      return output_accel - float(max(bias, 0.0))

    if authority_gap <= 0.40:
      return output_accel

    speed_factor = interp(CS.vEgo, [5.0, 12.0, 25.0], [0.0, 0.7, 1.0])
    max_bias = interp(abs(a_target), [0.8, 2.0, 3.5], [0.0, 0.10, 0.20])
    bias = min(authority_gap * 0.12, max_bias) * speed_factor
    return output_accel - float(bias)

  def get_longitudinal_feedforward(self, feedforward_gain, last_output_accel, a_target, v_ego):
    feedforward = a_target * feedforward_gain
    if not self.is_bolt_acc_pedal_friction_car or a_target >= 0.0:
      return feedforward

    pedal_regen_limit = float(interp(v_ego, BOLT_ACC_PEDAL_REGEN_LIMIT_BP, BOLT_ACC_PEDAL_REGEN_LIMIT_V))
    effective_gain = get_bolt_acc_pedal_feedforward_gain(
      feedforward_gain, a_target, v_ego, pedal_regen_limit, last_output_accel,
    )
    return a_target * effective_gain
