from dataclasses import replace

import pytest

from openpilot.tools.longitudinal.analyze_route_longitudinal import (
  LongitudinalSample,
  analyze_samples,
  anomaly_episode_times,
  parse_settings,
  threshold_sign_changes,
)


def make_samples(count: int = 20, **overrides) -> list[LongitudinalSample]:
  base = LongitudinalSample(
    segment=4,
    time_s=0.0,
    mono_time=0,
    long_active=True,
    v_ego=20.0,
    a_ego=0.1,
    plan_accel=0.1,
    command_accel=0.1,
    output_accel=0.1,
    source="cruise",
  )
  return [
    replace(base, time_s=index * 0.05, mono_time=index * 50_000_000, **overrides)
    for index in range(count)
  ]


def primary_kind(samples: list[LongitudinalSample]) -> str | None:
  report = analyze_samples(samples, "test", samples[-1].time_s)
  return report.findings[0].kind if report.findings else None


def test_threshold_sign_changes_ignores_zero_crossing_noise():
  assert threshold_sign_changes([0.2, 0.03, -0.02, 0.1, -0.2]) == 1


def test_planner_chatter_is_identified_from_repeated_target_reversals():
  samples = make_samples()
  for index, sample in enumerate(samples):
    accel = 0.45 if index % 2 == 0 else -0.45
    samples[index] = replace(sample, plan_accel=accel, command_accel=accel, output_accel=accel, a_ego=accel * 0.8)

  assert primary_kind(samples) == "planner_chatter"


def test_controller_integrator_is_identified_when_command_opposes_plan():
  samples = make_samples(plan_accel=0.25, command_accel=-0.25, output_accel=-0.25, a_ego=-0.2, i_term=-0.40)

  assert primary_kind(samples) == "controller_integrator"


def test_lead_instability_is_identified_from_source_and_track_churn():
  samples = make_samples(12, lead_status=True, lead_distance=45.0, lead_velocity=18.0, source="lead0", lead_track_id=10)
  for index, sample in enumerate(samples):
    samples[index] = replace(
      sample,
      source="lead0" if index % 2 == 0 else "lead1",
      lead_track_id=10 if index % 2 == 0 else 11,
      lead_velocity=18.0 if index % 2 == 0 else 20.0,
    )

  assert primary_kind(samples) == "lead_instability"


def test_unsafe_stop_release_is_critical():
  samples = make_samples(
    6,
    v_ego=2.0,
    plan_accel=0.3,
    command_accel=0.4,
    output_accel=0.4,
    a_ego=0.2,
    should_stop=True,
    lead_status=True,
    lead_distance=7.0,
    lead_velocity=0.0,
  )

  report = analyze_samples(samples, "test", samples[-1].time_s)

  assert report.findings[0].kind == "unsafe_stop_release"
  assert report.findings[0].severity == "critical"


def test_late_lead_response_is_identified_from_ttc_and_decel_shortfall():
  samples = make_samples(
    10,
    v_ego=20.0,
    plan_accel=0.0,
    command_accel=0.0,
    output_accel=0.0,
    a_ego=0.0,
    lead_status=True,
    lead_distance=18.0,
    lead_relative_velocity=-8.0,
    lead_velocity=12.0,
  )

  assert primary_kind(samples) == "late_lead_response"


def test_normal_steady_follow_has_no_deterministic_finding():
  samples = make_samples(
    lead_status=True,
    lead_distance=40.0,
    lead_relative_velocity=0.0,
    lead_velocity=20.0,
    source="lead0",
  )

  report = analyze_samples(samples, "test", samples[-1].time_s)

  assert report.findings == []


def test_anomaly_episodes_group_nearby_points():
  samples = make_samples(80)
  samples[10] = replace(samples[10], plan_accel=-0.5)
  samples[11] = replace(samples[11], plan_accel=0.5)
  samples[60] = replace(samples[60], plan_accel=-0.5)

  episodes = anomaly_episode_times(samples, limit=5)

  assert len(episodes) == 2
  assert episodes[0] == pytest.approx(0.55)


def test_parse_settings_keeps_only_longitudinal_context():
  settings = parse_settings('{"standard_follow": [1.5, 1.2], "acceleration_profile": "eco", "LaneWidth": 3.5}')

  assert settings == {"acceleration_profile": "eco", "standard_follow": [1.5, 1.2]}
