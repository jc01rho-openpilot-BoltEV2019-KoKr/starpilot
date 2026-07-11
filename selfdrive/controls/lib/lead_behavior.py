#!/usr/bin/env python3
from openpilot.common.constants import CV


HIGHWAY_LEAD_BEHAVIOR_MIN_SPEED = 45. * CV.MPH_TO_MS
VISION_LEAD_TRACK_MIN_DISTANCE = 25.0
VISION_LEAD_TRACK_BASE_TIME_GAP = 1.75
VISION_LEAD_TRACK_CLOSING_GAIN = 0.20
VISION_LEAD_TRACK_CLOSING_CAP = 2.50
TRACKED_LEAD_CATCHUP_BIAS_MIN_HEADWAY_MARGIN = 0.35
TRACKED_LEAD_CATCHUP_BIAS_FULL_HEADWAY_MARGIN = 0.65
TRACKED_LEAD_CATCHUP_BIAS_MIN_FADE_START_MARGIN = 0.75
TRACKED_LEAD_CATCHUP_BIAS_MIN_FADE_END_MARGIN = 1.05
TRACKED_LEAD_CATCHUP_BIAS_ABSOLUTE_FADE_START = 2.75
TRACKED_LEAD_CATCHUP_BIAS_ABSOLUTE_FADE_END = 3.10
TRACKED_LEAD_CATCHUP_BIAS_FULL_LATERAL_OFFSET = 0.90
TRACKED_LEAD_CATCHUP_BIAS_MAX_LATERAL_OFFSET = 1.60
TRACKED_LEAD_CATCHUP_BIAS_GAIN = 0.65
TRACKED_LEAD_CATCHUP_BIAS_SPEED_FACTOR = 0.75
RADARLESS_MATCHED_FOLLOW_MIN_SPEED = 22.0
RADARLESS_MATCHED_FOLLOW_MAX_REL_SPEED = 2.0
RADARLESS_MATCHED_FOLLOW_MIN_HEADWAY = 0.95
RADARLESS_MATCHED_FOLLOW_HEADWAY_BELOW_TARGET = 0.35
RADARLESS_MATCHED_FOLLOW_HEADWAY_ABOVE_TARGET = 0.90
RADARLESS_MATCHED_FOLLOW_MAX_LEAD_BRAKE = 0.35
RADARLESS_MATCHED_FOLLOW_MIN_MODEL_PROB = 0.70


def should_track_lead(lead_status: bool, lead_distance: float, model_length: float, stop_distance: float,
                      v_ego: float, *, v_lead: float | None = None, radar: bool = False) -> bool:
  if not lead_status:
    return False

  tracking_buffer = max(float(stop_distance), 4.0)
  model_limit = float(model_length) + tracking_buffer
  if radar:
    return float(lead_distance) < model_limit

  closing_speed = max(0.0, float(v_ego) - float(v_lead if v_lead is not None else v_ego))
  vision_time_gap = VISION_LEAD_TRACK_BASE_TIME_GAP + min(closing_speed * VISION_LEAD_TRACK_CLOSING_GAIN,
                                                          VISION_LEAD_TRACK_CLOSING_CAP)
  vision_limit = max(VISION_LEAD_TRACK_MIN_DISTANCE, float(v_ego) * vision_time_gap + tracking_buffer)
  return float(lead_distance) < min(model_limit, vision_limit)


def is_radarless_matched_follow_window(v_ego: float, lead_distance: float, v_lead: float, t_follow: float, *,
                                       radar: bool = False, lead_brake: float = 0.0,
                                       lead_prob: float = 0.0,
                                       min_speed: float = RADARLESS_MATCHED_FOLLOW_MIN_SPEED) -> bool:
  if radar or float(t_follow) <= 0.0 or float(v_ego) < float(min_speed):
    return False
  if float(lead_prob) < RADARLESS_MATCHED_FOLLOW_MIN_MODEL_PROB:
    return False
  if float(lead_brake) > RADARLESS_MATCHED_FOLLOW_MAX_LEAD_BRAKE:
    return False

  relative_speed = float(v_ego) - float(v_lead)
  if abs(relative_speed) > RADARLESS_MATCHED_FOLLOW_MAX_REL_SPEED:
    return False

  actual_headway = float(lead_distance) / max(float(v_ego), 1e-3)
  min_headway = max(RADARLESS_MATCHED_FOLLOW_MIN_HEADWAY,
                    float(t_follow) - RADARLESS_MATCHED_FOLLOW_HEADWAY_BELOW_TARGET)
  max_headway = float(t_follow) + RADARLESS_MATCHED_FOLLOW_HEADWAY_ABOVE_TARGET
  return min_headway <= actual_headway <= max_headway


def get_tracked_lead_catchup_bias(v_ego: float, lead_distance: float, desired_gap: float, closing_speed: float,
                                  v_cruise: float | None = None, y_rel: float | None = None) -> float:
  gap_error = lead_distance - desired_gap
  actual_hw = lead_distance / max(v_ego, 1e-3)
  desired_hw = desired_gap / max(v_ego, 1e-3)
  headway_margin = actual_hw - desired_hw

  if v_ego <= HIGHWAY_LEAD_BEHAVIOR_MIN_SPEED:
    return 0.0
  if v_cruise is not None and v_ego >= v_cruise:
    return 0.0
  if gap_error <= 0.0:
    return 0.0

  # Encourage ACC to treat a tracked lead as the active constraint when we're
  # hanging far above the requested time gap, but don't override cruise for a
  # truly distant lead or one we're already closing on decisively.
  if headway_margin <= TRACKED_LEAD_CATCHUP_BIAS_MIN_HEADWAY_MARGIN:
    return 0.0
  fade_start_margin = max(TRACKED_LEAD_CATCHUP_BIAS_MIN_FADE_START_MARGIN,
                          TRACKED_LEAD_CATCHUP_BIAS_ABSOLUTE_FADE_START - desired_hw)
  fade_end_margin = max(TRACKED_LEAD_CATCHUP_BIAS_MIN_FADE_END_MARGIN,
                        TRACKED_LEAD_CATCHUP_BIAS_ABSOLUTE_FADE_END - desired_hw)
  if headway_margin >= fade_end_margin:
    return 0.0
  if closing_speed > max(2.5, 0.12 * v_ego):
    return 0.0

  entry_factor = min(1.0, max(0.0, (headway_margin - TRACKED_LEAD_CATCHUP_BIAS_MIN_HEADWAY_MARGIN) /
                                     max(TRACKED_LEAD_CATCHUP_BIAS_FULL_HEADWAY_MARGIN - TRACKED_LEAD_CATCHUP_BIAS_MIN_HEADWAY_MARGIN, 1e-3)))
  exit_factor = 1.0
  if headway_margin > fade_start_margin:
    exit_factor = min(1.0, max(0.0, (fade_end_margin - headway_margin) / max(fade_end_margin - fade_start_margin, 1e-3)))

  lateral_factor = 1.0
  if y_rel is not None:
    lateral_offset = abs(float(y_rel))
    if lateral_offset >= TRACKED_LEAD_CATCHUP_BIAS_MAX_LATERAL_OFFSET:
      return 0.0
    if lateral_offset > TRACKED_LEAD_CATCHUP_BIAS_FULL_LATERAL_OFFSET:
      lateral_factor = min(1.0, max(0.0, (TRACKED_LEAD_CATCHUP_BIAS_MAX_LATERAL_OFFSET - lateral_offset) /
                                           max(TRACKED_LEAD_CATCHUP_BIAS_MAX_LATERAL_OFFSET - TRACKED_LEAD_CATCHUP_BIAS_FULL_LATERAL_OFFSET, 1e-3)))

  bias_cap = max(14.0, TRACKED_LEAD_CATCHUP_BIAS_SPEED_FACTOR * v_ego)
  return min(gap_error * TRACKED_LEAD_CATCHUP_BIAS_GAIN, bias_cap) * entry_factor * exit_factor * lateral_factor


def should_disable_far_lead_throttle(v_ego: float, lead_distance: float, desired_gap: float,
                                     closing_speed: float, following_lead: bool) -> bool:
  actual_hw = lead_distance / max(v_ego, 1e-3)
  desired_hw = desired_gap / max(v_ego, 1e-3)

  if following_lead or v_ego <= HIGHWAY_LEAD_BEHAVIOR_MIN_SPEED:
    return False

  # Don't coast if we're already materially above the requested headway.
  if actual_hw > max(desired_hw + 0.15, 1.75):
    return False

  coast_window_open = lead_distance > desired_gap + max(4.0, 0.15 * v_ego)
  coast_window_far = lead_distance < desired_gap + max(12.0, 0.60 * v_ego)
  gentle_closing = 0.35 < closing_speed < max(1.35, 0.05 * v_ego)
  ttc = lead_distance / max(closing_speed, 1e-3) if closing_speed > 0.1 else 1e6

  return coast_window_open and coast_window_far and gentle_closing and ttc > 7.5 and lead_distance > desired_gap + 7.0
