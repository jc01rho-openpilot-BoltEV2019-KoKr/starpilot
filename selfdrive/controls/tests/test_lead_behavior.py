from openpilot.selfdrive.controls.lib.lead_behavior import (
  get_tracked_lead_catchup_bias,
  is_radarless_matched_follow_window,
  should_track_lead,
  should_disable_far_lead_throttle,
)


def test_tracked_lead_catchup_bias_for_hanging_gap():
  bias = get_tracked_lead_catchup_bias(31.4, 78.7, 38.0, 0.1)
  assert bias > 10.0


def test_tracked_lead_catchup_bias_ignores_near_desired_gap():
  bias = get_tracked_lead_catchup_bias(31.4, 50.0, 38.0, 0.1)
  assert bias == 0.0


def test_tracked_lead_catchup_bias_ignores_very_far_gap():
  bias = get_tracked_lead_catchup_bias(31.4, 110.0, 38.0, 0.1)
  assert bias == 0.0


def test_tracked_lead_catchup_bias_applies_to_two_second_highway_gap():
  bias = get_tracked_lead_catchup_bias(30.4, 63.0, 40.0, 0.4)
  assert bias > 14.0


def test_tracked_lead_catchup_bias_reduces_for_laterally_offset_lead():
  centered = get_tracked_lead_catchup_bias(34.0, 103.0, 73.0, 1.9, y_rel=0.2)
  offset = get_tracked_lead_catchup_bias(34.0, 103.0, 73.0, 1.9, y_rel=1.95)
  assert centered > 0.0
  assert offset == 0.0


def test_tracked_lead_catchup_bias_fades_before_very_far_gap_cutoff():
  near_upper = get_tracked_lead_catchup_bias(34.0, 103.0, 73.0, 1.9)
  smaller_gap = get_tracked_lead_catchup_bias(34.0, 96.0, 73.0, 1.9)
  assert near_upper > 0.0
  assert near_upper < smaller_gap


def test_tracked_lead_catchup_bias_stays_off_once_at_set_speed():
  bias = get_tracked_lead_catchup_bias(31.4, 78.7, 38.0, 0.1, v_cruise=31.4)
  assert bias == 0.0


def test_disable_far_lead_throttle_rejects_two_second_plus_gap():
  should_disable = should_disable_far_lead_throttle(31.4, 78.7, 38.0, 0.1, False)
  assert not should_disable


def test_disable_far_lead_throttle_keeps_mild_coast_near_target_gap():
  should_disable = should_disable_far_lead_throttle(31.4, 52.0, 38.0, 0.5, False)
  assert should_disable


def test_disable_far_lead_throttle_rejects_fast_closing():
  should_disable = should_disable_far_lead_throttle(31.4, 52.0, 38.0, 3.5, False)
  assert not should_disable


def test_disable_far_lead_throttle_rejects_route_like_highway_stab_case():
  should_disable = should_disable_far_lead_throttle(34.69, 68.5, 63.0, 2.31, False)
  assert not should_disable


def test_disable_far_lead_throttle_rejects_large_gap_near_pace_matched_case():
  should_disable = should_disable_far_lead_throttle(32.43, 72.4, 56.0, 1.30, False)
  assert not should_disable


def test_should_track_lead_keeps_radar_leads_on_model_horizon():
  assert should_track_lead(True, 95.0, 100.0, 6.0, 30.0, v_lead=25.0, radar=True)


def test_should_track_lead_rejects_far_vision_only_highway_lead():
  assert not should_track_lead(True, 82.0, 140.0, 6.0, 29.0, v_lead=25.0, radar=False)


def test_should_track_lead_accepts_closer_vision_only_highway_lead():
  assert should_track_lead(True, 56.0, 140.0, 6.0, 29.0, v_lead=25.0, radar=False)


def test_should_track_lead_accepts_fast_closing_vision_lead_early():
  assert should_track_lead(True, 90.0, 140.0, 6.0, 20.0, v_lead=0.0, radar=False)


def test_radarless_matched_follow_window_accepts_pace_matched_highway_follow():
  assert is_radarless_matched_follow_window(31.0, 48.0, 30.4, 1.45, radar=False, lead_brake=0.05, lead_prob=0.95)


def test_radarless_matched_follow_window_rejects_large_relative_speed():
  assert not is_radarless_matched_follow_window(31.0, 48.0, 27.5, 1.45, radar=False, lead_brake=0.05, lead_prob=0.95)


def test_radarless_matched_follow_window_rejects_far_headway():
  assert not is_radarless_matched_follow_window(31.0, 82.0, 30.4, 1.45, radar=False, lead_brake=0.05, lead_prob=0.95)


def test_radarless_matched_follow_window_rejects_low_confidence_lead():
  assert not is_radarless_matched_follow_window(31.0, 48.0, 30.4, 1.45, radar=False, lead_brake=0.05, lead_prob=0.55)


def test_radarless_matched_follow_window_keeps_default_low_speed_guard():
  assert not is_radarless_matched_follow_window(14.4, 25.4, 16.2, 1.25, radar=False, lead_brake=0.0, lead_prob=1.0)


def test_radarless_matched_follow_window_accepts_lower_speed_when_requested():
  assert is_radarless_matched_follow_window(14.4, 25.4, 16.2, 1.25, radar=False, lead_brake=0.0, lead_prob=1.0, min_speed=12.0)
