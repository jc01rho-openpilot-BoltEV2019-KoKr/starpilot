#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import math
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Any
from urllib.parse import urlparse

import numpy as np

from openpilot.tools.lib.logreader import LogReader, ReadMode, parse_direct, parse_indirect
from openpilot.tools.lib.route import SegmentRange


ACTIVE_DEADBAND = 0.08
SOURCE_SWITCH_SCORE = 1.5
DEFAULT_BOOKMARK_BEFORE = 12.0
DEFAULT_BOOKMARK_AFTER = 3.0


@dataclass
class LongitudinalSample:
  segment: int
  time_s: float
  mono_time: int
  long_active: bool = False
  v_ego: float = 0.0
  a_ego: float = 0.0
  gas_pressed: bool = False
  brake_pressed: bool = False
  plan_accel: float = 0.0
  command_accel: float = 0.0
  output_accel: float = 0.0
  p_term: float = 0.0
  i_term: float = 0.0
  f_term: float = 0.0
  long_state: str = "unknown"
  source: str = "unknown"
  should_stop: bool = False
  allow_throttle: bool = True
  allow_brake: bool = True
  has_lead: bool = False
  lead_status: bool = False
  lead_distance: float | None = None
  lead_relative_velocity: float = 0.0
  lead_velocity: float = 0.0
  lead_acceleration: float = 0.0
  lead_probability: float = 0.0
  lead_radar: bool = False
  lead_track_id: int = -1
  lead_two_status: bool = False
  lead_two_distance: float | None = None
  experimental_mode: bool = False
  forcing_stop: bool = False
  red_light: bool = False
  tracking_lead: bool = False
  curve_controller_active: bool = False
  cruise_target: float = 0.0
  desired_follow_distance: float = 0.0
  personality: str = "unknown"


@dataclass
class Finding:
  kind: str
  severity: str
  score: float
  evidence: list[str] = field(default_factory=list)


@dataclass
class WindowReport:
  label: str
  segment: int
  event_time_s: float
  start_time_s: float
  end_time_s: float
  sample_count: int
  summary: dict[str, Any]
  findings: list[Finding]


@dataclass
class SegmentData:
  segment: int
  source: str
  samples: list[LongitudinalSample]
  bookmarks: list[float]
  car_params: dict[str, Any] | None
  settings: dict[str, Any]
  software: dict[str, Any] | None


def safe_float(value: Any, default: float = 0.0) -> float:
  try:
    result = float(value)
  except (TypeError, ValueError):
    return default
  return result if math.isfinite(result) else default


def safe_attr(obj: Any, name: str, default: Any = None) -> Any:
  if obj is None:
    return default
  try:
    return getattr(obj, name)
  except (AttributeError, RuntimeError):
    return default


def state_changes(values: list[Any]) -> int:
  return sum(current != previous for previous, current in zip(values, values[1:], strict=False))


def threshold_sign_changes(values: list[float], deadband: float = ACTIVE_DEADBAND) -> int:
  signs: list[int] = []
  for value in values:
    sign = 1 if value > deadband else -1 if value < -deadband else 0
    if sign and (not signs or sign != signs[-1]):
      signs.append(sign)
  return max(0, len(signs) - 1)


def direction_reversals(values: list[float], minimum_step: float = 0.06) -> int:
  directions: list[int] = []
  for previous, current in zip(values, values[1:], strict=False):
    delta = current - previous
    direction = 1 if delta > minimum_step else -1 if delta < -minimum_step else 0
    if direction and (not directions or direction != directions[-1]):
      directions.append(direction)
  return max(0, len(directions) - 1)


def maximum_rate(values: list[float], times: list[float]) -> float:
  rates = [
    abs((current - previous) / max(time - previous_time, 1e-3))
    for previous, current, previous_time, time in zip(values, values[1:], times, times[1:], strict=False)
    if 0.0 < time - previous_time < 0.5
  ]
  return max(rates, default=0.0)


def percentile(values: list[float], quantile: float, default: float = 0.0) -> float:
  return float(np.percentile(values, quantile)) if values else default


def severity_for(kind: str, score: float) -> str:
  if kind == "unsafe_stop_release" and score >= 4.0:
    return "critical"
  if kind == "late_lead_response" and score >= 5.0:
    return "high"
  if score >= 7.0:
    return "high"
  if score >= 3.0:
    return "medium"
  return "low"


def analyze_samples(samples: list[LongitudinalSample], label: str, event_time_s: float) -> WindowReport:
  if not samples:
    raise ValueError("Cannot analyze an empty longitudinal window")

  active_samples = [sample for sample in samples if sample.long_active]
  relevant = active_samples if active_samples else samples
  times = [sample.time_s for sample in relevant]
  plans = [sample.plan_accel for sample in relevant]
  commands = [sample.command_accel for sample in relevant]
  actual = [sample.a_ego for sample in relevant]
  integrals = [sample.i_term for sample in relevant]
  sources = [sample.source for sample in relevant]
  lead_statuses = [sample.lead_status for sample in relevant]
  experiment_states = [sample.experimental_mode for sample in relevant]
  stop_states = [sample.should_stop for sample in relevant]
  tracking_states = [sample.tracking_lead for sample in relevant]

  plan_sign_flips = threshold_sign_changes(plans)
  command_sign_flips = threshold_sign_changes(commands)
  plan_reversals = direction_reversals(plans)
  command_reversals = direction_reversals(commands)
  source_switches = state_changes(sources)
  lead_status_flips = state_changes(lead_statuses)
  experimental_flips = state_changes(experiment_states)
  stop_flips = state_changes(stop_states)
  tracking_flips = state_changes(tracking_states)

  lead_track_ids = [sample.lead_track_id for sample in relevant if sample.lead_status and sample.lead_track_id >= 0]
  lead_track_switches = state_changes(lead_track_ids)
  lead_velocity_jumps = sum(
    abs(current.lead_velocity - previous.lead_velocity) > 1.25
    for previous, current in zip(relevant, relevant[1:], strict=False)
    if previous.lead_status and current.lead_status and 0.0 < current.time_s - previous.time_s < 0.5
  )
  lead_distance_jumps = sum(
    abs((current.lead_distance or 0.0) - (previous.lead_distance or 0.0)) > 6.0
    for previous, current in zip(relevant, relevant[1:], strict=False)
    if previous.lead_status and current.lead_status and 0.0 < current.time_s - previous.time_s < 0.5
  )

  stale_positive_i = [sample for sample in relevant if sample.plan_accel < -0.08 and sample.i_term > 0.08]
  stale_negative_i = [
    sample for sample in relevant
    if sample.plan_accel > -0.05 and sample.i_term < -0.08 and sample.command_accel < sample.plan_accel - 0.10
  ]
  opposite_commands = [
    sample for sample in relevant
    if abs(sample.plan_accel) > 0.10 and abs(sample.command_accel) > 0.10 and sample.plan_accel * sample.command_accel < 0.0
  ]
  interface_adjustments = [abs(sample.output_accel - sample.command_accel) for sample in relevant]
  response_errors = [abs(sample.a_ego - sample.output_accel) for sample in relevant]

  late_response_shortfalls: list[float] = []
  minimum_ttc: float | None = None
  for sample in relevant:
    if not sample.lead_status or sample.lead_distance is None:
      continue
    closing_speed = max(-sample.lead_relative_velocity, sample.v_ego - sample.lead_velocity, 0.0)
    if closing_speed < 1.5:
      continue
    ttc = sample.lead_distance / max(closing_speed, 0.1)
    minimum_ttc = ttc if minimum_ttc is None else min(minimum_ttc, ttc)
    if ttc >= 4.0:
      continue
    usable_gap = max(sample.lead_distance - 4.0, 1.0)
    required_accel = -(closing_speed ** 2) / (2.0 * usable_gap)
    late_response_shortfalls.append(max(0.0, sample.command_accel - required_accel))

  unsafe_stop_release = [
    sample for sample in relevant
    if (sample.should_stop and sample.command_accel > 0.10) or (
      sample.lead_status and sample.lead_distance is not None and sample.lead_distance < 12.0 and
      sample.lead_velocity < 0.5 and sample.v_ego < 5.0 and sample.command_accel > 0.15
    )
  ]

  max_plan_jerk = maximum_rate(plans, times)
  max_command_jerk = maximum_rate(commands, times)
  controller_gap_p95 = percentile([abs(command - plan) for command, plan in zip(commands, plans, strict=True)], 95)
  response_gap_p95 = percentile(response_errors, 95)
  interface_gap_p95 = percentile(interface_adjustments, 95)
  stale_i_ratio = (len(stale_positive_i) + len(stale_negative_i)) / max(len(relevant), 1)
  opposite_ratio = len(opposite_commands) / max(len(relevant), 1)
  late_shortfall = max(late_response_shortfalls, default=0.0)

  category_scores = {
    "unsafe_stop_release": len(unsafe_stop_release) * 1.5,
    "late_lead_response": late_shortfall * 2.0 + (1.0 if minimum_ttc is not None and minimum_ttc < 3.0 else 0.0),
    "mode_arbitration": experimental_flips * 3.0 + stop_flips * 2.0 + tracking_flips,
    "lead_instability": (
      source_switches * SOURCE_SWITCH_SCORE + lead_status_flips + lead_track_switches * 2.0 +
      lead_velocity_jumps * 0.75 + lead_distance_jumps
    ),
    "controller_integrator": stale_i_ratio * 12.0 + opposite_ratio * 10.0 + max(0.0, controller_gap_p95 - 0.20) * 3.0,
    "planner_chatter": (
      plan_sign_flips * 1.5 + plan_reversals * 0.65 + command_sign_flips * 0.6 +
      max(0.0, max_plan_jerk - 1.5) * 0.35
    ),
    "vehicle_response": max(0.0, response_gap_p95 - 0.35) * 2.5 + max(0.0, interface_gap_p95 - 0.10) * 4.0,
  }

  evidence = {
    "unsafe_stop_release": [
      f"{len(unsafe_stop_release)} samples commanded positive acceleration while a stop hold or close stopped lead was active",
    ],
    "late_lead_response": [
      f"minimum TTC={minimum_ttc:.2f}s" if minimum_ttc is not None else "no closing lead TTC available",
      f"maximum kinematic decel shortfall={late_shortfall:.2f} m/s^2",
    ],
    "mode_arbitration": [
      f"experimental flips={experimental_flips}, shouldStop flips={stop_flips}, trackingLead flips={tracking_flips}",
    ],
    "lead_instability": [
      f"source switches={source_switches}, lead status flips={lead_status_flips}, radar track switches={lead_track_switches}",
      f"lead velocity jumps={lead_velocity_jumps}, lead distance jumps={lead_distance_jumps}",
    ],
    "controller_integrator": [
      f"stale-I samples={len(stale_positive_i) + len(stale_negative_i)}/{len(relevant)}, opposite command samples={len(opposite_commands)}",
      f"planner-to-command gap p95={controller_gap_p95:.2f} m/s^2, I range={min(integrals):+.2f}..{max(integrals):+.2f}",
    ],
    "planner_chatter": [
      f"plan sign flips={plan_sign_flips}, direction reversals={plan_reversals}, max plan jerk={max_plan_jerk:.2f} m/s^3",
      f"command sign flips={command_sign_flips}, direction reversals={command_reversals}, max command jerk={max_command_jerk:.2f} m/s^3",
    ],
    "vehicle_response": [
      f"command-to-applied gap p95={interface_gap_p95:.2f} m/s^2",
      f"applied-to-measured acceleration gap p95={response_gap_p95:.2f} m/s^2",
    ],
  }

  findings = [
    Finding(kind=kind, severity=severity_for(kind, score), score=round(score, 3), evidence=evidence[kind])
    for kind, score in category_scores.items()
    if score >= 1.0
  ]
  findings.sort(key=lambda finding: finding.score, reverse=True)

  lead_samples = [sample for sample in relevant if sample.lead_status and sample.lead_distance is not None]
  summary = {
    "activeSamples": len(active_samples),
    "speedRangeMps": [round(min(sample.v_ego for sample in relevant), 3), round(max(sample.v_ego for sample in relevant), 3)],
    "planAccelRange": [round(min(plans), 3), round(max(plans), 3)],
    "commandAccelRange": [round(min(commands), 3), round(max(commands), 3)],
    "actualAccelRange": [round(min(actual), 3), round(max(actual), 3)],
    "leadDistanceRange": None if not lead_samples else [
      round(min(sample.lead_distance for sample in lead_samples if sample.lead_distance is not None), 3),
      round(max(sample.lead_distance for sample in lead_samples if sample.lead_distance is not None), 3),
    ],
    "sources": sorted(set(sources)),
    "personalities": sorted({sample.personality for sample in relevant}),
    "minimumTtc": None if minimum_ttc is None else round(minimum_ttc, 3),
    "maxPlanJerk": round(max_plan_jerk, 3),
    "maxCommandJerk": round(max_command_jerk, 3),
  }
  return WindowReport(
    label=label,
    segment=samples[0].segment,
    event_time_s=round(event_time_s, 3),
    start_time_s=round(samples[0].time_s, 3),
    end_time_s=round(samples[-1].time_s, 3),
    sample_count=len(relevant),
    summary=summary,
    findings=findings,
  )


def parse_settings(serialized: str) -> dict[str, Any]:
  if not serialized:
    return {}
  try:
    settings = json.loads(serialized)
  except (TypeError, json.JSONDecodeError):
    return {}
  if not isinstance(settings, dict):
    return {}

  exact_keys = {
    "acceleration_profile",
    "custom_accel_profile",
    "deceleration_profile",
    "longitudinalActuatorDelay",
    "startAccel",
    "stopAccel",
    "stoppingDecelRate",
    "taco_tune",
    "truck_tuning",
  }
  return {
    key: value for key, value in sorted(settings.items())
    if key in exact_keys or key.endswith("_follow") or (
      key.startswith(("aggressive_jerk_", "relaxed_jerk_", "standard_jerk_")) and not key.endswith("_via")
    )
  }


def snapshot_car_params(CP: Any) -> dict[str, Any]:
  tuning = safe_attr(CP, "longitudinalTuning")
  return {
    "brand": str(safe_attr(CP, "brand", "unknown")),
    "carFingerprint": str(safe_attr(CP, "carFingerprint", "unknown")),
    "openpilotLongitudinalControl": bool(safe_attr(CP, "openpilotLongitudinalControl", False)),
    "longitudinalActuatorDelay": safe_float(safe_attr(CP, "longitudinalActuatorDelay", 0.0)),
    "kpBP": list(safe_attr(tuning, "kpBP", [])),
    "kpV": list(safe_attr(tuning, "kpV", [])),
    "kiBP": list(safe_attr(tuning, "kiBP", [])),
    "kiV": list(safe_attr(tuning, "kiV", [])),
    "kf": safe_float(safe_attr(tuning, "kfDEPRECATED", 0.0)),
  }


def snapshot_software(init_data: Any) -> dict[str, Any]:
  return {
    "version": str(safe_attr(init_data, "version", "unknown")),
    "gitCommit": str(safe_attr(init_data, "gitCommit", "unknown")),
    "gitSrcCommit": str(safe_attr(init_data, "gitSrcCommit", "")),
    "gitBranch": str(safe_attr(init_data, "gitBranch", "unknown")),
    "gitRemote": str(safe_attr(init_data, "gitRemote", "unknown")),
    "dirty": bool(safe_attr(init_data, "dirty", False)),
  }


def make_sample(segment: int, segment_start_ns: int, mono_time: int, latest: dict[str, Any]) -> LongitudinalSample | None:
  required = ("carState", "carControl", "controlsState", "radarState", "starpilotPlan", "longitudinalPlan")
  if not all(service in latest for service in required):
    return None

  car_state = latest["carState"]
  car_control = latest["carControl"]
  controls_state = latest["controlsState"]
  radar_state = latest["radarState"]
  starpilot_plan = latest["starpilotPlan"]
  long_plan = latest["longitudinalPlan"]
  car_output = latest.get("carOutput")
  selfdrive_state = latest.get("selfdriveState")
  lead = radar_state.leadOne
  lead_two = radar_state.leadTwo
  command_accel = safe_float(safe_attr(safe_attr(car_control, "actuators"), "accel", 0.0))
  output_accel = safe_float(safe_attr(safe_attr(car_output, "actuatorsOutput"), "accel", command_accel), command_accel)
  lead_status = bool(safe_attr(lead, "status", False))
  lead_two_status = bool(safe_attr(lead_two, "status", False))

  return LongitudinalSample(
    segment=segment,
    time_s=(mono_time - segment_start_ns) / 1e9,
    mono_time=mono_time,
    long_active=bool(safe_attr(car_control, "longActive", False)),
    v_ego=safe_float(safe_attr(car_state, "vEgo", 0.0)),
    a_ego=safe_float(safe_attr(car_state, "aEgo", 0.0)),
    gas_pressed=bool(safe_attr(car_state, "gasPressed", False)),
    brake_pressed=bool(safe_attr(car_state, "brakePressed", False)),
    plan_accel=safe_float(safe_attr(long_plan, "aTarget", 0.0)),
    command_accel=command_accel,
    output_accel=output_accel,
    p_term=safe_float(safe_attr(controls_state, "upAccelCmd", 0.0)),
    i_term=safe_float(safe_attr(controls_state, "uiAccelCmd", 0.0)),
    f_term=safe_float(safe_attr(controls_state, "ufAccelCmd", 0.0)),
    long_state=str(safe_attr(controls_state, "longControlState", "unknown")),
    source=str(safe_attr(long_plan, "longitudinalPlanSource", "unknown")),
    should_stop=bool(safe_attr(long_plan, "shouldStop", False)),
    allow_throttle=bool(safe_attr(long_plan, "allowThrottle", True)),
    allow_brake=bool(safe_attr(long_plan, "allowBrake", True)),
    has_lead=bool(safe_attr(long_plan, "hasLead", False)),
    lead_status=lead_status,
    lead_distance=safe_float(safe_attr(lead, "dRel", 0.0)) if lead_status else None,
    lead_relative_velocity=safe_float(safe_attr(lead, "vRel", 0.0)),
    lead_velocity=safe_float(safe_attr(lead, "vLead", 0.0)),
    lead_acceleration=safe_float(safe_attr(lead, "aLeadK", 0.0)),
    lead_probability=safe_float(safe_attr(lead, "modelProb", 0.0)),
    lead_radar=bool(safe_attr(lead, "radar", False)),
    lead_track_id=int(safe_attr(lead, "radarTrackId", -1)),
    lead_two_status=lead_two_status,
    lead_two_distance=safe_float(safe_attr(lead_two, "dRel", 0.0)) if lead_two_status else None,
    experimental_mode=bool(safe_attr(starpilot_plan, "experimentalMode", False)),
    forcing_stop=bool(safe_attr(starpilot_plan, "forcingStop", False)),
    red_light=bool(safe_attr(starpilot_plan, "redLight", False)),
    tracking_lead=bool(safe_attr(starpilot_plan, "trackingLead", False)),
    curve_controller_active=bool(safe_attr(starpilot_plan, "cscControllingSpeed", False)),
    cruise_target=safe_float(safe_attr(starpilot_plan, "vCruise", 0.0)),
    desired_follow_distance=safe_float(safe_attr(starpilot_plan, "desiredFollowDistance", 0.0)),
    personality=str(safe_attr(selfdrive_state, "personality", "unknown")),
  )


def analyze_segment(identifier: str, segment: int, mode: ReadMode) -> SegmentData:
  reader = LogReader(identifier, default_mode=mode, sort_by_time=True)
  source = ",".join(Path(urlparse(path).path).name or path.rsplit("/", 1)[-1] for path in reader.logreader_identifiers)
  latest: dict[str, Any] = {}
  samples: list[LongitudinalSample] = []
  bookmark_mono_times: list[int] = []
  car_params = None
  settings: dict[str, Any] = {}
  software = None
  segment_start_ns: int | None = None

  for msg in reader:
    mono_time = int(msg.logMonoTime)
    which = msg.which()
    if segment_start_ns is None and which in ("carState", "longitudinalPlan"):
      segment_start_ns = mono_time

    if which in ("userBookmark", "bookmarkButton"):
      if not bookmark_mono_times or (mono_time - bookmark_mono_times[-1]) / 1e9 > 0.5:
        bookmark_mono_times.append(mono_time)
      continue
    if which == "carParams" and car_params is None:
      car_params = snapshot_car_params(msg.carParams)
    if which == "initData" and software is None:
      software = snapshot_software(msg.initData)
    if which in (
      "carState", "carControl", "carOutput", "controlsState", "radarState", "selfdriveState", "starpilotPlan", "longitudinalPlan",
    ):
      latest[which] = getattr(msg, which)
    if which == "starpilotPlan":
      settings = parse_settings(str(safe_attr(msg.starpilotPlan, "starpilotToggles", ""))) or settings
    if which == "longitudinalPlan" and segment_start_ns is not None:
      sample = make_sample(segment, segment_start_ns, mono_time, latest)
      if sample is not None:
        samples.append(sample)

  bookmarks = [] if segment_start_ns is None else [
    (mono_time - segment_start_ns) / 1e9 for mono_time in bookmark_mono_times
  ]

  return SegmentData(
    segment=segment,
    source=source,
    samples=samples,
    bookmarks=bookmarks,
    car_params=car_params,
    settings=settings,
    software=software,
  )


def point_anomaly_scores(samples: list[LongitudinalSample]) -> list[tuple[float, float]]:
  scores: list[tuple[float, float]] = []
  for previous, current in zip(samples, samples[1:], strict=False):
    if not current.long_active:
      continue
    score = 0.0
    score += max(0.0, abs(current.plan_accel - previous.plan_accel) - 0.12) * 4.0
    score += max(0.0, abs(current.command_accel - previous.command_accel) - 0.15) * 3.0
    score += SOURCE_SWITCH_SCORE if current.source != previous.source else 0.0
    score += 1.0 if current.lead_status != previous.lead_status else 0.0
    score += 2.0 if current.experimental_mode != previous.experimental_mode else 0.0
    score += 1.5 if current.should_stop != previous.should_stop else 0.0
    if current.plan_accel < -0.08 and current.i_term > 0.08:
      score += 1.0
    if current.plan_accel > -0.05 and current.i_term < -0.08 and current.command_accel < current.plan_accel - 0.10:
      score += 1.0
    if score >= 1.0:
      scores.append((current.time_s, score))
  return scores


def anomaly_episode_times(samples: list[LongitudinalSample], limit: int) -> list[float]:
  points = point_anomaly_scores(samples)
  if not points:
    return []

  episodes: list[list[tuple[float, float]]] = [[points[0]]]
  for point in points[1:]:
    if point[0] - episodes[-1][-1][0] <= 1.5:
      episodes[-1].append(point)
    else:
      episodes.append([point])

  ranked = sorted(
    ((max(episode, key=lambda item: item[1])[0], sum(item[1] for item in episode)) for episode in episodes),
    key=lambda item: item[1],
    reverse=True,
  )
  return [time_s for time_s, _ in ranked[:limit]]


def window_samples(samples: list[LongitudinalSample], event_time_s: float, before: float, after: float) -> list[LongitudinalSample]:
  return [sample for sample in samples if event_time_s - before <= sample.time_s <= event_time_s + after]


def resolve_segments(identifier: str, mode: ReadMode) -> tuple[str, list[tuple[int, str]]]:
  if parse_direct(identifier) is not None:
    return identifier, [(0, identifier)]

  normalized = parse_indirect(identifier)
  segment_range = SegmentRange(normalized)
  route = segment_range.route_name
  requests = [(segment, f"{route}/{segment}") for segment in segment_range.seg_idxs]
  return route, requests


def analyze_route(identifier: str, mode: ReadMode, before: float, after: float, top: int) -> dict[str, Any]:
  route, segment_requests = resolve_segments(identifier, mode)
  segments = [analyze_segment(request, segment, mode) for segment, request in segment_requests]
  bookmark_reports: list[WindowReport] = []
  anomaly_reports: list[WindowReport] = []

  for segment_data in segments:
    for bookmark_number, bookmark_time in enumerate(segment_data.bookmarks, start=1):
      samples = window_samples(segment_data.samples, bookmark_time, before, after)
      if samples:
        bookmark_reports.append(analyze_samples(samples, f"bookmark {bookmark_number}", bookmark_time))

    episode_times = anomaly_episode_times(segment_data.samples, top)
    for episode_number, event_time in enumerate(episode_times, start=1):
      if any(bookmark - before <= event_time <= bookmark + after for bookmark in segment_data.bookmarks):
        continue
      samples = window_samples(segment_data.samples, event_time, min(before, 5.0), min(after, 2.0))
      if samples:
        anomaly_reports.append(analyze_samples(samples, f"route anomaly {episode_number}", event_time))

  anomaly_reports.sort(key=lambda report: report.findings[0].score if report.findings else 0.0, reverse=True)
  reports = bookmark_reports + anomaly_reports[:top]
  reports.sort(key=lambda report: (report.segment, report.event_time_s, report.label))
  car_params = next((segment.car_params for segment in segments if segment.car_params), None)
  settings = next((segment.settings for segment in reversed(segments) if segment.settings), {})
  software = next((segment.software for segment in segments if segment.software), None)
  return {
    "route": route,
    "carParams": car_params,
    "settings": settings,
    "software": software,
    "segments": [
      {
        "segment": segment.segment,
        "source": segment.source,
        "samples": len(segment.samples),
        "bookmarks": segment.bookmarks,
      }
      for segment in segments
    ],
    "reports": [asdict(report) for report in reports],
  }


def print_report(payload: dict[str, Any]) -> None:
  print(f"route={payload['route']}")
  software = payload.get("software")
  if software:
    source_commit = software["gitSrcCommit"] or software["gitCommit"]
    print(
      f"software={source_commit[:10]} branch={software['gitBranch']} version={software['version']} "
      + f"dirty={software['dirty']}"
    )
  car_params = payload.get("carParams")
  if car_params:
    vehicle_line = f"vehicle={car_params['carFingerprint']} brand={car_params['brand']}"
    delay_line = f"longDelay={car_params['longitudinalActuatorDelay']:.3f}s openpilotLong={car_params['openpilotLongitudinalControl']}"
    print(f"{vehicle_line} {delay_line}")
    print(f"longTune kp={car_params['kpV']} ki={car_params['kiV']} kf={car_params['kf']}")
  else:
    print("vehicle=unknown (carParams unavailable in selected segments)")

  for segment in payload["segments"]:
    segment_line = f"segment={segment['segment']} source={segment['source']} samples={segment['samples']}"
    print(f"{segment_line} bookmarks={len(segment['bookmarks'])}")

  settings = payload.get("settings", {})
  if settings:
    print("settings=" + json.dumps(settings, sort_keys=True))

  reports = payload["reports"]
  if not reports:
    print("No bookmark windows or route-wide anomalies were found.")
    return

  for report in reports:
    primary = report["findings"][0] if report["findings"] else None
    primary_text = "no deterministic fault" if primary is None else f"{primary['kind']} ({primary['severity']}, score={primary['score']:.2f})"
    event_line = f"\nseg {report['segment']} {report['label']} @{report['event_time_s']:.2f}s: {primary_text}"
    window_line = f"  window={report['start_time_s']:.2f}..{report['end_time_s']:.2f}s samples={report['sample_count']}"
    accel_line = (
      f"speed={report['summary']['speedRangeMps']}m/s plan={report['summary']['planAccelRange']} "
      + f"cmd={report['summary']['commandAccelRange']} actual={report['summary']['actualAccelRange']}"
    )
    lead_line = (
      f"  leadRange={report['summary']['leadDistanceRange']}m sources={report['summary']['sources']} "
      + f"personalities={report['summary']['personalities']}"
    )
    print(event_line)
    print(f"{window_line} {accel_line}")
    minimum_ttc = report["summary"]["minimumTtc"]
    print(f"{lead_line} minTTC={'n/a' if minimum_ttc is None else f'{minimum_ttc}s'}")
    for finding in report["findings"][:3]:
      print(f"  {finding['kind']}: {finding['severity']} score={finding['score']:.2f}")
      for item in finding["evidence"]:
        print(f"    {item}")


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Diagnose longitudinal behavior around route bookmarks and automatically detected anomalies.")
  parser.add_argument("routes", nargs="+", help="Comma/Konik route, segment range, Connect URL, or local log file")
  parser.add_argument("--mode", choices=("auto", "qlog", "rlog"), default="auto")
  parser.add_argument("--before", type=float, default=DEFAULT_BOOKMARK_BEFORE, help="Seconds before each bookmark to inspect")
  parser.add_argument("--after", type=float, default=DEFAULT_BOOKMARK_AFTER, help="Seconds after each bookmark to inspect")
  parser.add_argument("--top", type=int, default=5, help="Maximum route-wide anomaly episodes across the route")
  parser.add_argument("--json-out", type=Path, help="Optional JSON report path")
  return parser.parse_args()


def main() -> None:
  args = parse_args()
  mode = {"auto": ReadMode.AUTO, "qlog": ReadMode.QLOG, "rlog": ReadMode.RLOG}[args.mode]
  payloads = [analyze_route(route, mode, args.before, args.after, args.top) for route in args.routes]
  for index, payload in enumerate(payloads):
    if index:
      print("\n" + "=" * 80 + "\n")
    print_report(payload)

  if args.json_out:
    args.json_out.parent.mkdir(parents=True, exist_ok=True)
    args.json_out.write_text(json.dumps(payloads, indent=2, sort_keys=True) + "\n", encoding="utf-8")


if __name__ == "__main__":
  main()
