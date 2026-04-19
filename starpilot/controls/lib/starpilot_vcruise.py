#!/usr/bin/env python3
from openpilot.common.constants import CV
from openpilot.common.realtime import DT_MDL
from openpilot.selfdrive.road_speed_limiter import SpeedLimiter
from openpilot.starpilot.common.starpilot_variables import CITY_SPEED_LIMIT, CRUISING_SPEED, PLANNER_TIME
from openpilot.starpilot.controls.lib.curve_speed_controller import CurveSpeedController
from openpilot.starpilot.controls.lib.speed_limit_controller import SpeedLimitController

CSC_MIN_SPEED = CITY_SPEED_LIMIT * CV.MPH_TO_MS
OVERRIDE_FORCE_STOP_TIMER = 10
CAMERA_SPEED_FACTOR = 0.9


class StarPilotVCruise:
  def __init__(self, StarPilotPlanner):
    self.starpilot_planner = StarPilotPlanner

    self.csc = CurveSpeedController(self)
    self.slc = SpeedLimitController(self)

    self.speed_limiter = SpeedLimiter.instance()
    self.current_road_limit_ms = 0.0
    self.v_cruise_kph_limit = 0
    self.slowing_down = False
    self.last_nda_limit_speed = 0.0
    self.last_nda_left_dist = 0.0

    self.forcing_stop = False
    self.override_force_stop = False
    self.override_force_standstill = False

    self.override_force_stop_timer = 0
    self.force_stop_timer = 0.0
    self.tracked_model_length = 0.0

  def update(self, controls_enabled, now, time_validated, v_cruise, v_ego, sm, starpilot_toggles):
    long_control_active = sm["carControl"].longActive

    force_stop = self.starpilot_planner.starpilot_cem.stop_light_detected and controls_enabled and starpilot_toggles.force_stops
    force_stop &= self.starpilot_planner.model_stopped
    force_stop &= self.override_force_stop_timer <= 0

    self.force_stop_timer = self.force_stop_timer + DT_MDL if force_stop else 0

    force_stop_enabled = self.force_stop_timer >= 1

    self.override_force_stop |= sm["carState"].gasPressed
    self.override_force_stop |= sm["starpilotCarState"].accelPressed
    self.override_force_stop &= force_stop_enabled

    if self.override_force_stop:
      self.override_force_stop_timer = OVERRIDE_FORCE_STOP_TIMER
    elif self.override_force_stop_timer > 0:
      self.override_force_stop_timer -= DT_MDL

    force_standstill_enabled = controls_enabled and starpilot_toggles.force_standstill and sm["carState"].standstill
    if force_standstill_enabled:
      self.override_force_standstill |= sm["carState"].gasPressed
      self.override_force_standstill |= sm["starpilotCarState"].accelPressed
    else:
      self.override_force_standstill = False

    v_cruise_cluster = max(sm["carState"].vCruiseCluster * CV.KPH_TO_MS, v_cruise)
    v_cruise_diff = v_cruise_cluster - v_cruise

    v_ego_cluster = max(sm["carState"].vEgoCluster, v_ego)
    v_ego_diff = v_ego_cluster - v_ego

    # FrogsGoMoo's Curve Speed Controller
    if long_control_active and v_ego > CRUISING_SPEED and self.starpilot_planner.road_curvature_detected and starpilot_toggles.curve_speed_controller:
      self.csc.update_target(v_ego)

      self.csc_controlling_speed = True

      self.csc_target = self.csc.target
    else:
      self.csc.log_data(v_ego, sm)

      self.csc_controlling_speed = False
      self.csc.target_set = False

      self.csc_target = v_cruise

    # Pfeiferj's Speed Limit Controller
    self.slc.starpilot_toggles = starpilot_toggles

    if starpilot_toggles.speed_limit_controller:
      self.slc.update_limits(sm["starpilotCarState"].dashboardSpeedLimit, now, time_validated, v_cruise, v_ego, sm)
      self.slc.update_override(v_cruise, v_cruise_diff, v_ego, v_ego_diff, sm)

      self.slc_offset = self.slc.offset
      self.slc_target = self.slc.target
    elif starpilot_toggles.show_speed_limits:
      self.slc.update_limits(sm["starpilotCarState"].dashboardSpeedLimit, now, time_validated, v_cruise, v_ego, sm, display_only=True)

      self.slc_offset = 0
      self.slc_target = self.slc.target
    else:
      self.slc_offset = 0
      self.slc_target = 0

    # NDA speed limiter - direct SpeedLimiter.get_max_speed() call, independent of SLC
    v_cruise_kph = v_cruise * CV.MS_TO_KPH
    apply_limit_speed, road_limit_speed, left_dist, first_started, limit_log = self.speed_limiter.get_max_speed(
      sm["carState"], v_cruise_kph
    )
    self.current_road_limit_ms = max(float(self.speed_limiter.get_road_limit_speed() or 0.0), 0.0) * CV.KPH_TO_MS
    self.last_nda_limit_speed = float(road_limit_speed)
    self.last_nda_left_dist = float(left_dist)

    if apply_limit_speed >= 20:
      self.v_cruise_kph_limit = min(apply_limit_speed, v_cruise_kph)
      self.slowing_down = True
    else:
      self.slowing_down = False
      self.v_cruise_kph_limit = v_cruise_kph

    if force_standstill_enabled and not self.override_force_standstill:
      self.forcing_stop = True
      self.tracked_model_length = 0.0
      v_cruise = 0.0

    elif force_stop_enabled and not self.override_force_stop:
      self.forcing_stop |= not sm["carState"].standstill

      self.tracked_model_length = max(self.tracked_model_length - (v_ego * DT_MDL), 0)
      v_cruise = min((self.tracked_model_length // PLANNER_TIME), v_cruise)

    else:
      self.forcing_stop = False

      self.tracked_model_length = self.starpilot_planner.model_length

      targets = [self.csc_target, v_cruise]
      if starpilot_toggles.speed_limit_controller:
        targets.append(max(self.slc.overridden_speed, self.slc_target + self.slc_offset) - v_ego_diff)

      v_cruise = min([target if target >= CSC_MIN_SPEED else v_cruise for target in targets])

      if self.v_cruise_kph_limit > 0:
        v_cruise = min(v_cruise, self.v_cruise_kph_limit * CV.KPH_TO_MS)

    return v_cruise
