#!/usr/bin/env python3
import time

from openpilot.common.constants import CV

from openpilot.starpilot.common.experimental_state import (
  CCStatus,
  is_manual_cc_status,
  restore_persisted_cc_state,
)


class ConditionalChillMode:
  CCM_STOP_MODEL_TIME = 7.0
  CHILL_ENTRY_CONFIRM_TIME = 0.35
  CHILL_EXIT_BUFFER_TIME = 0.35
  CHILL_MIN_DWELL_TIME = 1.2

  STABLE_LEAD_MIN_MODEL_PROB = 0.9
  STABLE_LEAD_MAX_BRAKE = 0.2
  STABLE_LEAD_MIN_SPEED = 1.5
  STABLE_LEAD_MAX_DISTANCE = 90.0
  STABLE_LEAD_MAX_DISTANCE_TIME = 4.5
  STABLE_LEAD_MAX_CLOSING_SPEED = 0.75
  STABLE_LEAD_MAX_CLOSING_RATIO = 0.03

  ADJACENT_LEAD_VETO_MIN_SPEED = 1.0
  ADJACENT_LEAD_VETO_MAX_DISTANCE = 65.0
  ADJACENT_LEAD_VETO_MAX_DISTANCE_TIME = 3.5

  LOW_SPEED_STOP_SCENE_MAX_SPEED = 18 * CV.MPH_TO_MS

  def __init__(self, StarPilotPlanner, detector):
    self.starpilot_planner = StarPilotPlanner
    self.detector = detector
    self.params = self.starpilot_planner.params
    self.params_memory = self.starpilot_planner.params_memory

    self.experimental_mode = True
    self.status_value = CCStatus["OFF"]
    self._active_auto_status = CCStatus["OFF"]
    self._candidate_since = 0.0
    self._soft_exit_since = 0.0
    self._chill_hold_until = 0.0
    self._prev_cc_status = None

  def update(self, v_ego, v_cruise, sm, starpilot_toggles):
    now = time.monotonic()
    safe_mode = self.params.get_bool("SafeMode")

    self.status_value = CCStatus["OFF"] if safe_mode else restore_persisted_cc_state(self.params, self.params_memory)

    if is_manual_cc_status(self.status_value):
      self._reset_timers()
      self.experimental_mode = self.status_value == CCStatus["USER_EXPERIMENTAL"]
      self._write_status(self.status_value)
      return

    self._refresh_detector(v_ego, sm)

    if safe_mode or self._has_hard_veto(v_ego, sm):
      self._reset_timers()
      self.experimental_mode = False if safe_mode else True
      self.status_value = CCStatus["OFF"]
      self._write_status(CCStatus["OFF"])
      return

    auto_status = self._get_chill_status(v_ego, v_cruise, sm, starpilot_toggles)
    chill_candidate = auto_status != CCStatus["OFF"]

    if chill_candidate:
      if self._candidate_since == 0.0:
        self._candidate_since = now
      self._soft_exit_since = 0.0

      if not self.experimental_mode or (now - self._candidate_since) >= self.CHILL_ENTRY_CONFIRM_TIME:
        self.experimental_mode = False
        self._active_auto_status = auto_status
        self._chill_hold_until = max(self._chill_hold_until, now + self.CHILL_MIN_DWELL_TIME)
      self.status_value = self._active_auto_status if not self.experimental_mode else CCStatus["OFF"]
    else:
      self._candidate_since = 0.0
      if not self.experimental_mode:
        if self._soft_exit_since == 0.0:
          self._soft_exit_since = now

        hold_active = now < self._chill_hold_until
        exit_buffer_active = (now - self._soft_exit_since) < self.CHILL_EXIT_BUFFER_TIME
        if hold_active or exit_buffer_active:
          self.status_value = self._active_auto_status
        else:
          self.experimental_mode = True
          self._active_auto_status = CCStatus["OFF"]
          self.status_value = CCStatus["OFF"]
      else:
        self._soft_exit_since = 0.0
        self.status_value = CCStatus["OFF"]

    self._write_status(self.status_value if not self.experimental_mode else CCStatus["OFF"])

  def _reset_timers(self):
    self._active_auto_status = CCStatus["OFF"]
    self._candidate_since = 0.0
    self._soft_exit_since = 0.0
    self._chill_hold_until = 0.0

  def _refresh_detector(self, v_ego, sm):
    detector_toggles = type("DetectorToggles", (), {
      "conditional_curves": True,
      "conditional_curves_lead": True,
      "conditional_lead": True,
      "conditional_slower_lead": True,
      "conditional_stopped_lead": True,
    })()
    self.detector.curve_detection(v_ego, detector_toggles)
    self.detector.slow_lead(detector_toggles, v_ego)
    self.detector.stop_sign_and_light(v_ego, sm, self.CCM_STOP_MODEL_TIME)

  def _has_hard_veto(self, v_ego, sm):
    if sm["carState"].standstill:
      return True

    if sm["carState"].leftBlinker or sm["carState"].rightBlinker:
      return True

    if sm["starpilotCarState"].trafficModeEnabled:
      return True

    if self.starpilot_planner.starpilot_vcruise.slc.experimental_mode:
      return True

    if self.detector.curve_detected or self.detector.slow_lead_detected or self.detector.stop_light_detected:
      return True

    if self.starpilot_planner.starpilot_vcruise.stop_sign_confirmed or self.starpilot_planner.starpilot_vcruise.forcing_stop:
      return True

    if self._adjacent_lead_ambiguous(sm, v_ego):
      return True

    return self._low_speed_stop_scene(v_ego)

  def _low_speed_stop_scene(self, v_ego):
    if v_ego >= self.LOW_SPEED_STOP_SCENE_MAX_SPEED:
      return False

    if self.starpilot_planner.raw_model_stopped or self.starpilot_planner.model_stopped or self.detector.stop_light_model_detected:
      return True

    lead = self.starpilot_planner.lead_one
    if not getattr(lead, "status", False):
      return False

    lead_distance = float(getattr(lead, "dRel", float("inf")))
    lead_speed = float(getattr(lead, "vLead", float("inf")))
    lead_distance_limit = max(40.0, v_ego * self.STABLE_LEAD_MAX_DISTANCE_TIME)
    return lead_distance < lead_distance_limit and lead_speed < max(6.0, v_ego + 0.5)

  def _get_chill_status(self, v_ego, v_cruise, sm, starpilot_toggles):
    lead = self.starpilot_planner.lead_one
    lead_status = bool(getattr(lead, "status", False))
    tracking_lead = bool(getattr(self.starpilot_planner, "tracking_lead", False))
    set_speed_error = max(0.0, v_cruise - v_ego)

    if (not lead_status and not tracking_lead and
        v_ego >= starpilot_toggles.conditional_chill_speed and
        set_speed_error >= starpilot_toggles.conditional_chill_speed_margin):
      return CCStatus["SPEED"]

    if not starpilot_toggles.conditional_chill_lead:
      return CCStatus["OFF"]

    if v_ego < starpilot_toggles.conditional_chill_speed_lead or not lead_status or not tracking_lead:
      return CCStatus["OFF"]

    lead_distance = float(getattr(lead, "dRel", float("inf")))
    lead_speed = float(getattr(lead, "vLead", 0.0))
    lead_brake = max(0.0, -float(getattr(lead, "aLeadK", 0.0)))
    lead_prob = float(getattr(lead, "modelProb", 0.0))
    closing_speed = max(0.0, v_ego - lead_speed)
    max_closing_speed = max(self.STABLE_LEAD_MAX_CLOSING_SPEED, self.STABLE_LEAD_MAX_CLOSING_RATIO * v_ego)
    max_distance = min(self.STABLE_LEAD_MAX_DISTANCE, max(35.0, v_ego * self.STABLE_LEAD_MAX_DISTANCE_TIME))
    lead_confident = bool(getattr(lead, "radar", False)) or lead_prob >= self.STABLE_LEAD_MIN_MODEL_PROB

    if not lead_confident:
      return CCStatus["OFF"]

    if lead_distance >= max_distance or lead_speed <= self.STABLE_LEAD_MIN_SPEED:
      return CCStatus["OFF"]

    if lead_brake > self.STABLE_LEAD_MAX_BRAKE or closing_speed > max_closing_speed:
      return CCStatus["OFF"]

    return CCStatus["LEAD"]

  def _adjacent_lead_ambiguous(self, sm, v_ego):
    radar_state = self._get_sm_service(sm, "starpilotRadarState")
    if radar_state is None:
      return False

    max_distance = min(self.ADJACENT_LEAD_VETO_MAX_DISTANCE, max(25.0, v_ego * self.ADJACENT_LEAD_VETO_MAX_DISTANCE_TIME))
    for lead in (getattr(radar_state, "leadLeft", None), getattr(radar_state, "leadRight", None)):
      if lead is None or not getattr(lead, "status", False):
        continue

      if float(getattr(lead, "dRel", float("inf"))) < max_distance and float(getattr(lead, "vLead", 0.0)) > self.ADJACENT_LEAD_VETO_MIN_SPEED:
        return True

    return False

  @staticmethod
  def _get_sm_service(sm, key):
    if isinstance(sm, dict):
      return sm.get(key)

    try:
      return sm[key]
    except (KeyError, IndexError, TypeError, AttributeError):
      return None

  def _write_status(self, status_value):
    if status_value != self._prev_cc_status:
      self.params_memory.put_int("CCStatus", status_value)
      self._prev_cc_status = status_value
