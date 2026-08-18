"""Rivian Gen 1 hybrid steering for the Extreme harness."""

import math
from collections import deque

import numpy as np

from opendbc.car import rate_limit
from opendbc.car.common.filter_simple import FirstOrderFilter
from opendbc.car.lateral import apply_driver_steer_torque_limits, get_max_angle_delta_vm, get_max_angle_vm
from opendbc.car.rivian.toi_controller import TOI_MAX_ANGLE_DEG, TOI_REARM_ANGLE_DEG, ToiController
from opendbc.car.rivian.values import CAR, CarControllerParams as CCP, RivianFlags
from opendbc.car.vehicle_model import VehicleModel

# Limits observed in the Gen 1 EPAS firmware. Margins keep commands inside the
# firmware's absolute-angle and sliding-window rate checks.
EPAS_FW_MAX_ANGLE_BP = [0.0, 2.78, 5.56, 8.33, 12.50, 16.67, 22.22, 27.78]
EPAS_FW_MAX_ANGLE_V = [500, 500, 250, 150, 85, 56, 40, 25]
EPAS_FW_RATE_BP = [5.56, 8.33, 12.50, 16.67]
EPAS_FW_RATE_V = [4.50, 1.50, 0.60, 0.18]
EPAS_FW_ANGLE_MARGIN = 0.98
EPAS_FW_RATE_MARGIN = 0.94
PANDA_STEP_MARGIN = 0.9

MIN_TORQUE_FRAMES = 50
HANDOFF_EXIT_DEG = 15.0
UNWIND_HANDOFF_RATE = 40.0
HANDOFF_MAX_ANGLE_DEG = 25.0
DRIVER_HANDS_OFF_EXIT_FRAMES = 100
EAC_RECOVER_FRAMES = 15

EAC_REARM_RELEASE_FRAMES = 25

# The wheel's inertia loads the torsion bar while the column is swinging. Reject
# those transients so they cannot be mistaken for a driver override.
TORSION_RATE_WINDOW = 25
TORSION_MAX_RATE_SWING = 90.0
DRIVER_OVERRIDE_TORQUE = 6.0
DRIVER_OVERRIDE_FRAMES = 5

# Sustained light torsion bridges capacitive-sensor dropouts while the driver's
# hands slide on the wheel. This only delays recovery from a driver override.
PRESENCE_LPF_RC = 0.032
PRESENCE_TORQUE_THRESHOLD = 1.5
PRESENCE_MIN_FRAMES = 30
PRESENCE_HOLD_FRAMES = 100

# Above this angle the rack spends most of its time saturated. Keeping a small
# amount of headroom helps the torque controller recover as geometry unwinds.
HIGH_ANGLE_THRESHOLD_DEG = 90
HIGH_ANGLE_CAP_FRAC = 0.95

# A live angle->torque selection cannot release the EPAS angle servo before the
# rate-limited torque channel is ready to carry the curve. Ramp torque under the
# still-active angle command, then release angle once sufficient hold torque is
# available. These values come from AdventurePilot's road-tested handoff.
TORQUE_PREARM_EXIT_FRAC = 0.85
TORQUE_PREARM_MIN_HOLD = 20
TORQUE_PREARM_MAX_FRAMES = 150
TORQUE_PREARM_STALL_FRAMES = 12
TORQUE_PREARM_ABORT_LOCKOUT = 50

# The torque controller is deliberately frozen while angle steering is active,
# so angle saturation needs its own debounced envelope check for the stock
# "turn exceeds steering limit" warning.
ANGLE_SAT_MIN_LAT_ACCEL = 1.0
ANGLE_SAT_FRAMES = 30


def apply_rivian_steer_angle_limits_vm(apply_angle: float, apply_angle_last: float, v_ego_raw: float, steering_angle: float,
                                       lat_active: bool, limits, VM: VehicleModel) -> float:
  """Apply Rivian's jerk, accel, and safety constraints to its angle channel."""
  v_ego_raw = max(v_ego_raw, 1)

  # When the speed-scheduled angle envelope shrinks, Rivian must unwind toward
  # it through the jerk limit instead of snapping directly to the new bound.
  max_angle = get_max_angle_vm(v_ego_raw, VM, limits)
  new_apply_angle = np.clip(apply_angle, -max_angle, max_angle)

  max_angle_delta = get_max_angle_delta_vm(v_ego_raw, VM, limits)
  max_angle_delta = min(max_angle_delta, limits.ANGLE_LIMITS.MAX_ANGLE_RATE)
  new_apply_angle = rate_limit(new_apply_angle, apply_angle_last, -max_angle_delta, max_angle_delta)

  if not lat_active:
    new_apply_angle = steering_angle

  return float(np.clip(new_apply_angle, -limits.ANGLE_LIMITS.STEER_ANGLE_MAX, limits.ANGLE_LIMITS.STEER_ANGLE_MAX))


class _RateBudget:
  WINDOW_USER_FRAMES = 16
  WINDOW_TIME_S = 0.16

  def __init__(self):
    self.history = deque([0.0] * self.WINDOW_USER_FRAMES, maxlen=self.WINDOW_USER_FRAMES)

  def push(self, sent_angle: float) -> None:
    self.history.append(round(sent_angle * 10) / 10)

  def bounds(self, threshold_dps: float, margin: float) -> tuple[float, float]:
    cmd_oldest = self.history[0]
    budget = threshold_dps * self.WINDOW_TIME_S * margin
    return cmd_oldest - budget, cmd_oldest + budget


def get_safety_CP():
  from opendbc.car.rivian.interface import CarInterface
  return CarInterface.get_non_essential_params(CAR.RIVIAN_R1_GEN1)


class ExternalController:
  """Hybrid Gen 1 steering: EPAS angle control with cooperative torque fallback."""

  def __init__(self, CP):
    self.VM = VehicleModel(CP)
    self.VM_safety = VehicleModel(get_safety_CP())
    self.gen2 = bool(CP.flags & RivianFlags.GEN2)

    self.wheel_touch_cnt = 0
    self.torsion_cnt = 0
    self.torsion_sign = 0
    self.driver_override_cnt = 0
    self.rate_hist = deque([0.0] * TORSION_RATE_WINDOW, maxlen=TORSION_RATE_WINDOW)
    self.hands_on = False
    self.torsion_lpf = FirstOrderFilter(0.0, PRESENCE_LPF_RC, 0.01)
    self.presence_cnt = 0
    self.presence_sign = 0
    self.presence_hold = 0
    self.hands_off_frames = 0

    self.torque_active = False
    self.torque_active_frames = 0
    # Handback protections depend on why torque mode was entered. Driver
    # recovery gets the release timer; both driver and Galaxy recovery get the
    # low-angle gate.
    self.driver_override_recovery = False
    self.galaxy_torque_recovery = False
    self.lat_active_last = False
    self.eac_dead_frames = 0
    self.eac_rearm_release_frames = 0
    self.eac_rearm_attempted = False

    # Galaxy can switch an angle-capable truck to torque while driving. The
    # prearm state makes that transition make-before-break.
    self.force_torque = False
    self.torque_prearm = False
    self.prearm_frames = 0
    self.prearm_torque_peak = 0
    self.prearm_stall_frames = 0
    self.prearm_abort_lockout = 0
    self.prearm_last_outcome = ""
    self.prearm_last_hold = 0
    self.prearm_last_frames = 0
    self.prearm_last_peak = 0

    self.apply_angle_last = 0.0
    self.angle_active = False
    self.angle_saturated = False
    self.angle_sat_frames = 0
    self.rate_budget = _RateBudget()
    self.roll = 0.0
    self.angle_offset_deg = 0.0

    self.apply_torque_last = 0
    self.torque_cmd = 0
    self.toi_controller = ToiController()
    self.toi_act_cmd = False

  def update(self, CS, lat_active: bool, actuators) -> None:
    self._update_hands_on(CS)
    desired_angle = math.degrees(self.VM.get_steer_from_curvature(
      -float(actuators.curvature), CS.out.vEgo, self.roll)) + self.angle_offset_deg
    self._update_torque_active(CS, lat_active, desired_angle, actuators)
    desired_lat_accel = float(actuators.curvature) * CS.out.vEgo ** 2
    self._update_angle(CS, lat_active, desired_angle, desired_lat_accel)
    self._update_torque(CS, actuators)

  def _update_wheel_touched(self, wheel_touched: bool, minimum_count: int) -> bool:
    self.wheel_touch_cnt += 1 if wheel_touched else -1
    self.wheel_touch_cnt = int(np.clip(self.wheel_touch_cnt, 0, minimum_count * 2 + 1))
    return self.wheel_touch_cnt > minimum_count

  def _update_torsion(self, torque: float, steering_rate: float, threshold: float, minimum_count: int) -> bool:
    self.rate_hist.append(steering_rate)
    if max(self.rate_hist) - min(self.rate_hist) > TORSION_MAX_RATE_SWING:
      self.torsion_cnt = 0
      return False

    abs_torque = abs(torque)
    pressed = abs_torque > threshold
    sign = int(np.sign(torque))
    if pressed and self.torsion_sign and sign != self.torsion_sign:
      self.torsion_cnt = 0
    else:
      self.torsion_cnt += max(1, math.ceil(abs_torque / threshold)) if pressed else -1
      self.torsion_cnt = int(np.clip(self.torsion_cnt, 0, minimum_count * 2 + 1))
    if pressed:
      self.torsion_sign = sign
    return self.torsion_cnt > minimum_count

  def _update_torsion_presence(self, torque: float) -> bool:
    filtered = self.torsion_lpf.update(torque)
    sign = 1 if filtered > PRESENCE_TORQUE_THRESHOLD else -1 if filtered < -PRESENCE_TORQUE_THRESHOLD else 0
    self.presence_cnt = self.presence_cnt + 1 if sign != 0 and sign == self.presence_sign else int(sign != 0)
    self.presence_sign = sign
    if self.presence_cnt >= PRESENCE_MIN_FRAMES:
      self.presence_hold = PRESENCE_HOLD_FRAMES
    elif self.presence_hold > 0:
      self.presence_hold -= 1
    return self.presence_hold > 0

  def _update_hands_on(self, CS) -> None:
    wheel_touch = False
    if not self.gen2:
      calibration = CS.sccm_wheel_touch["SETME_X52"]
      capacitive = CS.sccm_wheel_touch["SCCM_WheelTouch_CapacitiveValue"] > calibration * 0.9
      wheel_touch = self._update_wheel_touched(capacitive, 25)
    torsion = self._update_torsion(CS.out.steeringTorque, CS.out.steeringRateDeg, 4.0, 9)
    # Keep rejecting ordinary inertial torsion, but do not mask a sustained,
    # high-effort driver override just because the wheel is already moving fast.
    strong_override = abs(CS.out.steeringTorque) >= DRIVER_OVERRIDE_TORQUE and CS.out.steeringPressed
    self.driver_override_cnt += 1 if strong_override else -1
    self.driver_override_cnt = int(np.clip(self.driver_override_cnt, 0, DRIVER_OVERRIDE_FRAMES))
    presence = self._update_torsion_presence(CS.out.steeringTorque)
    self.hands_on = wheel_touch or torsion or self.driver_override_cnt >= DRIVER_OVERRIDE_FRAMES or CS.hands_on_level > 1
    self.hands_off_frames = 0 if self.hands_on or presence else self.hands_off_frames + 1

  def _reset_prearm(self) -> None:
    self.torque_prearm = False
    self.prearm_frames = 0
    self.prearm_torque_peak = 0
    self.prearm_stall_frames = 0

  def _end_prearm(self, outcome: str, hold_target: int) -> None:
    self.prearm_last_outcome = outcome
    self.prearm_last_hold = hold_target
    self.prearm_last_frames = self.prearm_frames
    self.prearm_last_peak = self.prearm_torque_peak
    self._reset_prearm()

  def _update_torque_active(self, CS, lat_active: bool, desired_angle: float, actuators) -> None:
    self.torque_active_frames = self.torque_active_frames + 1 if self.torque_active else 0
    epas_ready = CS.eac_status == 1 and CS.eac_error_code == 0
    eac_active = CS.eac_status == 2
    epas_inhibited = CS.eac_status == 0 and CS.eac_error_code == 0
    gap = abs(desired_angle - CS.out.steeringAngleDeg)

    if not lat_active:
      self.torque_active = False
      self.driver_override_recovery = False
      self.galaxy_torque_recovery = False
      self.eac_dead_frames = 0
      self.eac_rearm_release_frames = 0
      self.eac_rearm_attempted = False
      self.prearm_abort_lockout = 0
      self._reset_prearm()
      self.lat_active_last = False
      return

    if self.force_torque:
      # A stale angle-recovery count must not trigger after switching modes.
      self.eac_dead_frames = 0
      self.eac_rearm_release_frames = 0
      self.eac_rearm_attempted = False
      self.driver_override_recovery = False
      self.lat_active_last = True

      if self.torque_active:
        self.galaxy_torque_recovery = True
        self._reset_prearm()
        return

      if self.prearm_abort_lockout > 0:
        self.prearm_abort_lockout -= 1
        self._reset_prearm()
        return

      steer_max = round(float(np.interp(CS.out.vEgoRaw, CCP.STEER_MAX_LOOKUP[0], CCP.STEER_MAX_LOOKUP[1])))
      hold_target = abs(int(round(float(actuators.torque) * steer_max)))
      epas_holding = eac_active
      driver_took_over = self.hands_on and CS.out.steeringPressed
      if not epas_holding or driver_took_over or hold_target < TORQUE_PREARM_MIN_HOLD:
        self.torque_active = True
        self.galaxy_torque_recovery = True
        self._reset_prearm()
        return

      # Keep angle active while the independently rate-limited torque channel
      # ramps underneath it. Progress is evaluated from the prior frame.
      self.torque_prearm = True
      self.prearm_frames += 1
      if abs(self.apply_torque_last) > self.prearm_torque_peak:
        self.prearm_torque_peak = abs(self.apply_torque_last)
        self.prearm_stall_frames = 0
      else:
        self.prearm_stall_frames += 1

      reached = abs(self.apply_torque_last) >= TORQUE_PREARM_EXIT_FRAC * hold_target
      stalled = self.prearm_stall_frames >= TORQUE_PREARM_STALL_FRAMES
      if reached:
        self.torque_active = True
        self.galaxy_torque_recovery = True
        self._end_prearm("reached", hold_target)
      elif self.prearm_frames >= TORQUE_PREARM_MAX_FRAMES:
        if stalled:
          self._end_prearm("abort", hold_target)
          self.prearm_abort_lockout = TORQUE_PREARM_ABORT_LOCKOUT
        else:
          self.torque_active = True
          self.galaxy_torque_recovery = True
          self._end_prearm("backstop", hold_target)
      return

    # Cancelling a force request during prearm immediately returns to the
    # already-active angle channel. A completed torque handoff uses the normal
    # cooperative release logic below to return to angle safely.
    self.prearm_abort_lockout = 0
    self._reset_prearm()
    if not self.torque_active:
      self.galaxy_torque_recovery = False

    if (self.torque_active and epas_inhibited and
        not self.hands_on and not CS.out.steeringPressed):
      self.eac_rearm_release_frames = min(self.eac_rearm_release_frames + 1, EAC_REARM_RELEASE_FRAMES)
    else:
      self.eac_rearm_release_frames = 0

    if self.hands_on and CS.out.steeringPressed:
      self.torque_active = True
      self.driver_override_recovery = True
      self.galaxy_torque_recovery = False
      self.eac_rearm_attempted = False
    elif self.eac_dead_frames >= EAC_RECOVER_FRAMES:
      self.torque_active = True
      self.driver_override_recovery = False
      self.galaxy_torque_recovery = False
    elif not self.lat_active_last and not epas_ready:
      self.torque_active = True
      self.driver_override_recovery = False
      self.galaxy_torque_recovery = False
      self.eac_rearm_attempted = False
    elif self.torque_active and self.torque_active_frames >= MIN_TORQUE_FRAMES and not self.hands_on:
      fw_max = float(np.interp(CS.out.vEgoRaw, EPAS_FW_MAX_ANGLE_BP, EPAS_FW_MAX_ANGLE_V)) * EPAS_FW_ANGLE_MARGIN
      in_envelope = abs(CS.out.steeringAngleDeg) < fw_max
      threshold_dps = float(np.interp(CS.out.vEgoRaw, EPAS_FW_RATE_BP, EPAS_FW_RATE_V)) * 100.0
      lower, upper = self.rate_budget.bounds(threshold_dps, EPAS_FW_RATE_MARGIN)
      rate_settled = lower <= CS.out.steeringAngleDeg <= upper and abs(CS.out.steeringRateDeg) < UNWIND_HANDOFF_RATE

      rearm_ready = (epas_inhibited and not self.eac_rearm_attempted and
                     self.eac_rearm_release_frames >= EAC_REARM_RELEASE_FRAMES and
                     not CS.out.steeringPressed and not CS.out.steerFaultTemporary and
                     not CS.out.steerFaultPermanent)
      handoff_angle_ready = (not (self.driver_override_recovery or self.galaxy_torque_recovery) or
                             abs(CS.out.steeringAngleDeg) < HANDOFF_MAX_ANGLE_DEG)
      driver_handoff_ready = (not self.driver_override_recovery or
                              self.hands_off_frames >= DRIVER_HANDS_OFF_EXIT_FRAMES)
      if ((epas_ready or rearm_ready) and in_envelope and rate_settled and
          gap < HANDOFF_EXIT_DEG and handoff_angle_ready and driver_handoff_ready):
        self.torque_active = False
        self.driver_override_recovery = False
        self.galaxy_torque_recovery = False
        self.eac_rearm_attempted = rearm_ready

    if eac_active:
      self.eac_rearm_attempted = False

    if not self.torque_active and not eac_active:
      self.eac_dead_frames += 1
    else:
      self.eac_dead_frames = 0
    self.lat_active_last = True

  def _update_angle(self, CS, lat_active: bool, desired_angle: float, desired_lat_accel: float) -> None:
    self.angle_active = lat_active and not self.torque_active
    v_lookahead = max(CS.out.vEgoRaw + max(CS.out.aEgo, 0.0), 1.0)
    apply_angle = apply_rivian_steer_angle_limits_vm(desired_angle, self.apply_angle_last, v_lookahead,
                                                     CS.out.steeringAngleDeg, self.angle_active, CCP, self.VM_safety)

    saturated = False
    if self.angle_active:
      fw_max = float(np.interp(CS.out.vEgoRaw, EPAS_FW_MAX_ANGLE_BP, EPAS_FW_MAX_ANGLE_V)) * EPAS_FW_ANGLE_MARGIN
      safety_max = get_max_angle_vm(max(CS.out.vEgoRaw, 1.0), self.VM_safety, CCP)
      deliverable_angle = min(fw_max, safety_max)
      saturated = abs(desired_lat_accel) > ANGLE_SAT_MIN_LAT_ACCEL and abs(desired_angle) > deliverable_angle
      apply_angle = float(np.clip(apply_angle, -fw_max, fw_max))
      threshold_dps = float(np.interp(CS.out.vEgoRaw, EPAS_FW_RATE_BP, EPAS_FW_RATE_V)) * 100.0
      lower, upper = self.rate_budget.bounds(threshold_dps, EPAS_FW_RATE_MARGIN)
      apply_angle = float(np.clip(apply_angle, lower, upper))
      step = get_max_angle_delta_vm(max(CS.out.vEgoRaw, 1.0), self.VM_safety, CCP) * PANDA_STEP_MARGIN
      apply_angle = float(np.clip(apply_angle, self.apply_angle_last - step, self.apply_angle_last + step))

    self.angle_sat_frames = self.angle_sat_frames + 1 if saturated else 0
    self.angle_saturated = self.angle_sat_frames >= ANGLE_SAT_FRAMES
    self.apply_angle_last = apply_angle
    self.rate_budget.push(apply_angle)

  def _update_torque(self, CS, actuators) -> None:
    torque_requested = self.torque_active or self.torque_prearm
    self.toi_act_cmd, torque_allowed = self.toi_controller.update(
      torque_requested,
      abs(CS.out.steeringAngleDeg) >= TOI_MAX_ANGLE_DEG,
      bool(getattr(CS, "toi_fault", False)),
      bool(getattr(CS, "toi_active", False)),
      bool(getattr(CS, "toi_unavailable", False)),
      prearming=self.torque_prearm,
      high_angle_rearm=abs(CS.out.steeringAngleDeg) <= TOI_REARM_ANGLE_DEG,
      hold_high_angle_release=self.driver_override_recovery,
    )

    if not torque_requested:
      self.apply_torque_last = 0
      self.torque_cmd = 0
      return

    if not torque_allowed:
      # The EPAS has either not acknowledged the request yet or is completing a
      # high-angle release. Reset the limiter to the torque actually sent.
      self.apply_torque_last = 0
      self.torque_cmd = 0
      return

    steer_max = round(float(np.interp(CS.out.vEgoRaw, CCP.STEER_MAX_LOOKUP[0], CCP.STEER_MAX_LOOKUP[1])))
    requested_torque = int(round(float(actuators.torque) * steer_max))
    torque_cmd = apply_driver_steer_torque_limits(requested_torque, self.apply_torque_last,
                                                  CS.out.steeringTorque, CCP, steer_max)

    if abs(CS.out.steeringAngleDeg) > HIGH_ANGLE_THRESHOLD_DEG:
      cap = int(round(steer_max * HIGH_ANGLE_CAP_FRAC))
      torque_cmd = int(np.clip(torque_cmd, -cap, cap))

    self.apply_torque_last = torque_cmd
    self.torque_cmd = torque_cmd
