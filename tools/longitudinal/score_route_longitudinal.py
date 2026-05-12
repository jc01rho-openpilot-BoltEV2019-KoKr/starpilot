#!/usr/bin/env python3
import argparse
import json
import math
import os
from collections import defaultdict
from dataclasses import asdict, dataclass
from pathlib import Path
from types import SimpleNamespace

import numpy as np

os.environ["DEBUG"] = "0"
os.environ.setdefault("FILEREADER_CACHE", "1")

from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.controls.lib import longitudinal_planner as longitudinal_planner_mod
from openpilot.selfdrive.controls.lib.longitudinal_planner import LongitudinalPlanner
from openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.long_mpc import STOP_DISTANCE
from openpilot.tools.lib.logreader import LogReader
from openpilot.tools.lib.url_file import hash_256


for level_name in ("info", "warning", "error", "exception", "event"):
  if hasattr(cloudlog, level_name):
    setattr(cloudlog, level_name, lambda *args, **kwargs: None)


NEAR_SPEED_HIGHWAY_MIN_SPEED = 22.0
NEAR_SPEED_LEAD_DELTA = 1.5
BRAKE_STAB_START = -0.35
BRAKE_STAB_END = -0.10
BRAKE_STAB_MAX_DURATION = 1.0
VISION_SLOW_LEAD_MIN_DELTA = 3.0
VISION_SLOW_LEAD_MIN_DIST = 35.0
VISION_SLOW_LEAD_MAX_DIST = 120.0
VISION_SLOW_LEAD_MIN_MODEL_PROB = 0.9
SLOW_LEAD_DECEL_TRIGGER = -0.2
REQUIRED_SERVICES = {
  "carControl",
  "carState",
  "controlsState",
  "liveParameters",
  "radarState",
  "selfdriveState",
  "starpilotPlan",
}
COMMA_DATA_CACHE_ROOT = Path("/tmp/comma_download_cache")
ROUTE_CACHE_REBUILD_ROOT = Path("/tmp/starpilot_route_cache")
MAX_CACHED_ROUTE_SEGMENTS = 255
MAX_CONSECUTIVE_CACHE_MISSES = 4


@dataclass
class RouteMetrics:
  route: str
  replayed_samples: int = 0
  near_speed_samples: int = 0
  highway_follow_samples: int = 0
  vision_slow_lead_samples: int = 0
  brake_stab_count: int = 0
  false_far_lead_brake_count: int = 0
  highway_accel_std: float = 0.0
  highway_rms_jerk: float = 0.0
  near_speed_accel_std: float = 0.0
  near_speed_rms_jerk: float = 0.0
  slower_lead_event_count: int = 0
  slower_lead_mean_response_delay: float | None = None
  slower_lead_worst_response_delay: float | None = None
  slower_lead_min_a_target: float | None = None
  slower_lead_min_ttc: float | None = None
  slower_lead_min_gap: float | None = None


def configure_planner_profile(profile: str) -> None:
  if profile == "current":
    return

  if profile == "legacy_panic_bypass":
    longitudinal_planner_mod.UNCERT_PANIC_MIN_CLOSING_SPEED = 0.5
    longitudinal_planner_mod.UNCERT_PANIC_MIN_CLOSING_SPEED_GAIN = 0.0
    longitudinal_planner_mod.UNCERT_PANIC_MAX_GAP_BUFFER_MIN = 1e6
    longitudinal_planner_mod.UNCERT_PANIC_MAX_GAP_BUFFER_GAIN = 0.0
    return

  raise ValueError(f"Unsupported planner profile: {profile}")


def default_toggles() -> SimpleNamespace:
  return SimpleNamespace(
    taco_tune=False,
    classic_model=False,
    tinygrad_model=True,
    model_version="v11",
    stop_distance=float(STOP_DISTANCE),
    vEgoStopping=0.5,
  )


def parse_toggles(serialized: str, previous: SimpleNamespace | None) -> SimpleNamespace:
  if not serialized:
    return previous if previous is not None else default_toggles()

  payload = vars(default_toggles())
  try:
    payload.update(json.loads(serialized))
  except Exception:
    return previous if previous is not None else default_toggles()
  return SimpleNamespace(**payload)


def finite_min(current: float | None, value: float | None) -> float | None:
  if value is None or not math.isfinite(value):
    return current
  if current is None:
    return value
  return min(current, value)


def finite_mean(values: list[float]) -> float | None:
  if not values:
    return None
  return float(np.mean(values))


def finite_max(values: list[float]) -> float | None:
  if not values:
    return None
  return float(np.max(values))


def is_near_speed_follow(v_ego: float, lead_status: bool, v_lead: float) -> bool:
  return lead_status and v_ego > NEAR_SPEED_HIGHWAY_MIN_SPEED and abs(v_ego - v_lead) <= NEAR_SPEED_LEAD_DELTA


def is_highway_follow(v_ego: float, lead_status: bool) -> bool:
  return lead_status and v_ego > NEAR_SPEED_HIGHWAY_MIN_SPEED


def is_vision_slow_lead(v_ego: float, lead_status: bool, lead_radar: bool, lead_prob: float, lead_dist: float, v_lead: float) -> bool:
  return (
    lead_status and
    not lead_radar and
    lead_prob >= VISION_SLOW_LEAD_MIN_MODEL_PROB and
    (v_ego - v_lead) >= VISION_SLOW_LEAD_MIN_DELTA and
    VISION_SLOW_LEAD_MIN_DIST <= lead_dist <= VISION_SLOW_LEAD_MAX_DIST
  )


def cached_rlog_url(route: str, seg: int) -> str:
  return f"https://commadata2.blob.core.windows.net/commadata2/{route}/{seg}/rlog.zst"


def parse_route_identifier(identifier: str) -> tuple[str, str | None]:
  parts = identifier.split("/")
  if len(parts) < 2:
    raise ValueError(f"Invalid route identifier: {identifier}")

  route = "/".join(parts[:2])
  remainder = parts[2:]
  if not remainder:
    return route, None

  first = remainder[0]
  if first in ("r", "q", "a", "i"):
    return route, None
  return route, first


def cached_rlog_chunk_paths(route: str, seg: int, cache_root: Path = COMMA_DATA_CACHE_ROOT) -> list[Path]:
  prefix = f"{hash_256(cached_rlog_url(route, seg))}_"
  chunk_paths = []
  for candidate in cache_root.glob(f"{prefix}*"):
    suffix = candidate.name.removeprefix(prefix)
    try:
      chunk_index = float(suffix)
    except ValueError:
      continue
    chunk_paths.append((chunk_index, candidate))
  return [path for _, path in sorted(chunk_paths, key=lambda item: item[0])]


def discover_cached_segment_indexes(route: str,
                                    cache_root: Path = COMMA_DATA_CACHE_ROOT,
                                    max_seg: int = MAX_CACHED_ROUTE_SEGMENTS) -> list[int]:
  found: list[int] = []
  consecutive_misses = 0
  for seg in range(max_seg + 1):
    if cached_rlog_chunk_paths(route, seg, cache_root):
      found.append(seg)
      consecutive_misses = 0
    elif found:
      consecutive_misses += 1
      if consecutive_misses >= MAX_CONSECUTIVE_CACHE_MISSES:
        break

  if not found:
    raise FileNotFoundError(f"No cached rlogs found for {route} under {cache_root}")
  return found


def select_segment_indexes(route: str, segment_slice: str | None, available_idxs: list[int]) -> list[int]:
  if segment_slice is None:
    return available_idxs

  available_set = set(available_idxs)
  if ":" not in segment_slice:
    seg = int(segment_slice)
    if seg not in available_set:
      raise FileNotFoundError(f"Requested segment {seg} is not available in local cache for {route}")
    return [seg]

  raw_parts = segment_slice.split(":")
  if len(raw_parts) > 3:
    raise ValueError(f"Invalid segment slice: {segment_slice}")
  parts = [int(part) if part else None for part in raw_parts]
  while len(parts) < 3:
    parts.append(None)
  start, end, step = parts
  max_seg = max(available_idxs)
  if end is None or end < 0 or (start is not None and start < 0):
    universe = list(range(max_seg + 1))
  else:
    universe = list(range(max(max_seg, end) + 1))
  requested = universe[slice(start, end, step)]
  missing = [seg for seg in requested if seg not in available_set]
  if missing:
    raise FileNotFoundError(f"Requested cached segments are unavailable for {route}: {missing[:8]}")
  return requested


def rebuild_cached_rlogs(identifier: str,
                         cache_root: Path = COMMA_DATA_CACHE_ROOT,
                         out_root: Path = ROUTE_CACHE_REBUILD_ROOT) -> tuple[str, list[str]]:
  route, segment_slice = parse_route_identifier(identifier)
  available_idxs = discover_cached_segment_indexes(route, cache_root)
  requested_idxs = select_segment_indexes(route, segment_slice, available_idxs)
  rebuilt_paths: list[str] = []

  for seg in requested_idxs:
    chunk_paths = cached_rlog_chunk_paths(route, seg, cache_root)
    if not chunk_paths:
      raise FileNotFoundError(f"Missing cached rlog chunks for {route}/{seg}")

    out_path = out_root / route / str(seg) / "rlog.zst"
    expected_size = sum(chunk_path.stat().st_size for chunk_path in chunk_paths)
    if not out_path.exists() or out_path.stat().st_size != expected_size:
      out_path.parent.mkdir(parents=True, exist_ok=True)
      with out_path.open("wb") as out_file:
        for chunk_path in chunk_paths:
          with chunk_path.open("rb") as chunk_file:
            out_file.write(chunk_file.read())
    rebuilt_paths.append(str(out_path))

  return route, rebuilt_paths


def score_route(route: str, capture_events: bool = False, max_events: int = 200, use_cached_rlogs: bool = False) -> tuple[RouteMetrics, list[dict]]:
  display_route = parse_route_identifier(route)[0] if use_cached_rlogs else route
  metrics = RouteMetrics(route=display_route)
  planner = None
  toggles = default_toggles()
  state: dict[str, object] = {}
  events: list[dict] = []

  highway_accels: list[float] = []
  highway_jerks: list[float] = []
  near_speed_accels: list[float] = []
  near_speed_jerks: list[float] = []
  slower_response_delays: list[float] = []
  active_slow_event: dict | None = None
  active_brake_stab: dict | None = None
  active_false_far_brake: dict | None = None
  prev_plan_t: int | None = None
  prev_a_target: float | None = None

  logreader_input: str | list[str]
  if use_cached_rlogs:
    _, logreader_input = rebuild_cached_rlogs(route)
  else:
    logreader_input = route

  for msg in LogReader(logreader_input, sort_by_time=True):
    which = msg.which()
    if which == "carParams" and planner is None:
      planner = LongitudinalPlanner(msg.carParams)
      continue

    if which not in REQUIRED_SERVICES and which != "modelV2":
      continue

    state[which] = getattr(msg, which)
    if which == "starpilotPlan":
      toggles = parse_toggles(state["starpilotPlan"].starpilotToggles, toggles)

    if which != "modelV2" or planner is None or not REQUIRED_SERVICES.issubset(state):
      continue

    planner.update(state, toggles)
    metrics.replayed_samples += 1

    car_state = state["carState"]
    radar_state = state["radarState"]
    lead = radar_state.leadOne
    v_ego = float(car_state.vEgo)
    lead_status = bool(lead.status)
    lead_dist = float(lead.dRel) if lead_status else float("inf")
    v_lead = float(lead.vLead) if lead_status else v_ego
    lead_prob = float(getattr(lead, "modelProb", 0.0))
    lead_radar = bool(getattr(lead, "radar", False))
    a_target = float(planner.output_a_target)
    mono_time = int(msg.logMonoTime)

    dt = None if prev_plan_t is None else max((mono_time - prev_plan_t) / 1e9, 1e-3)
    jerk = None if dt is None or prev_a_target is None else (a_target - prev_a_target) / dt

    near_speed_follow = is_near_speed_follow(v_ego, lead_status, v_lead)
    highway_follow = is_highway_follow(v_ego, lead_status)
    vision_slow_lead = is_vision_slow_lead(v_ego, lead_status, lead_radar, lead_prob, lead_dist, v_lead)

    if near_speed_follow:
      metrics.near_speed_samples += 1
      near_speed_accels.append(a_target)
      if jerk is not None:
        near_speed_jerks.append(jerk)
    if highway_follow:
      metrics.highway_follow_samples += 1
      highway_accels.append(a_target)
      if jerk is not None:
        highway_jerks.append(jerk)
    if vision_slow_lead:
      metrics.vision_slow_lead_samples += 1

    if near_speed_follow:
      if active_brake_stab is None and a_target < BRAKE_STAB_START:
        active_brake_stab = {
          "start_t": mono_time / 1e9,
          "start_mono_time": mono_time,
          "min_a_target": a_target,
          "start_lead_dist": lead_dist,
          "start_v_ego": v_ego,
          "start_v_lead": v_lead,
          "source": str(planner.mpc.source),
          "filter_time_factor": float(getattr(planner.mpc, "filter_time_factor", 1.0)),
        }
      elif active_brake_stab is not None and a_target > BRAKE_STAB_END:
        duration = mono_time / 1e9 - active_brake_stab["start_t"]
        if duration < BRAKE_STAB_MAX_DURATION:
          metrics.brake_stab_count += 1
          if capture_events and len(events) < max_events:
            events.append({
              "route": route,
              "kind": "brake_stab",
              "start_mono_time": active_brake_stab["start_mono_time"],
              "duration": duration,
              "min_a_target": active_brake_stab["min_a_target"],
              "start_lead_dist": active_brake_stab["start_lead_dist"],
              "start_v_ego": active_brake_stab["start_v_ego"],
              "start_v_lead": active_brake_stab["start_v_lead"],
              "source": active_brake_stab["source"],
              "filter_time_factor": active_brake_stab["filter_time_factor"],
            })
        active_brake_stab = None
      elif active_brake_stab is not None:
        active_brake_stab["min_a_target"] = min(active_brake_stab["min_a_target"], a_target)
    else:
      active_brake_stab = None

    lead_source_active = str(planner.mpc.source) in ("lead0", "lead1") or bool(getattr(state["starpilotPlan"], "trackingLead", False))
    false_far_brake = (
      highway_follow and
      lead_source_active and
      lead_status and
      not lead_radar and
      lead_dist > 80.0 and
      0.1 < (v_ego - v_lead) < 2.0 and
      a_target < -0.2
    )
    if false_far_brake:
      if active_false_far_brake is None:
        active_false_far_brake = {
          "start_mono_time": mono_time,
          "start_t": mono_time / 1e9,
          "min_a_target": a_target,
          "min_lead_dist": lead_dist,
          "max_closing_speed": max(0.0, v_ego - v_lead),
          "start_v_ego": v_ego,
          "start_v_lead": v_lead,
          "lead_prob": lead_prob,
          "source": str(planner.mpc.source),
          "filter_time_factor": float(getattr(planner.mpc, "filter_time_factor", 1.0)),
        }
      else:
        active_false_far_brake["min_a_target"] = min(active_false_far_brake["min_a_target"], a_target)
        active_false_far_brake["min_lead_dist"] = min(active_false_far_brake["min_lead_dist"], lead_dist)
        active_false_far_brake["max_closing_speed"] = max(active_false_far_brake["max_closing_speed"], max(0.0, v_ego - v_lead))
    elif active_false_far_brake is not None:
      if capture_events and len(events) < max_events:
        events.append({
          "route": route,
          "kind": "false_far_lead_brake",
          "start_mono_time": active_false_far_brake["start_mono_time"],
          "duration": mono_time / 1e9 - active_false_far_brake["start_t"],
          "min_a_target": active_false_far_brake["min_a_target"],
          "min_lead_dist": active_false_far_brake["min_lead_dist"],
          "max_closing_speed": active_false_far_brake["max_closing_speed"],
          "start_v_ego": active_false_far_brake["start_v_ego"],
          "start_v_lead": active_false_far_brake["start_v_lead"],
          "lead_prob": active_false_far_brake["lead_prob"],
          "source": active_false_far_brake["source"],
          "filter_time_factor": active_false_far_brake["filter_time_factor"],
        })
      metrics.false_far_lead_brake_count += 1
      active_false_far_brake = None

    if vision_slow_lead:
      ttc = lead_dist / max(v_ego - v_lead, 0.1)
      if active_slow_event is None:
        active_slow_event = {
          "start_t": mono_time / 1e9,
          "response_delay": None,
          "min_a_target": a_target,
          "min_ttc": ttc,
          "min_gap": lead_dist,
        }
      if active_slow_event["response_delay"] is None and a_target <= SLOW_LEAD_DECEL_TRIGGER:
        active_slow_event["response_delay"] = mono_time / 1e9 - active_slow_event["start_t"]
      active_slow_event["min_a_target"] = min(active_slow_event["min_a_target"], a_target)
      active_slow_event["min_ttc"] = min(active_slow_event["min_ttc"], ttc)
      active_slow_event["min_gap"] = min(active_slow_event["min_gap"], lead_dist)
    elif active_slow_event is not None:
      metrics.slower_lead_event_count += 1
      if active_slow_event["response_delay"] is not None:
        slower_response_delays.append(active_slow_event["response_delay"])
      metrics.slower_lead_min_a_target = finite_min(metrics.slower_lead_min_a_target, active_slow_event["min_a_target"])
      metrics.slower_lead_min_ttc = finite_min(metrics.slower_lead_min_ttc, active_slow_event["min_ttc"])
      metrics.slower_lead_min_gap = finite_min(metrics.slower_lead_min_gap, active_slow_event["min_gap"])
      active_slow_event = None

    prev_plan_t = mono_time
    prev_a_target = a_target

  if active_slow_event is not None:
    metrics.slower_lead_event_count += 1
    if active_slow_event["response_delay"] is not None:
      slower_response_delays.append(active_slow_event["response_delay"])
    metrics.slower_lead_min_a_target = finite_min(metrics.slower_lead_min_a_target, active_slow_event["min_a_target"])
    metrics.slower_lead_min_ttc = finite_min(metrics.slower_lead_min_ttc, active_slow_event["min_ttc"])
    metrics.slower_lead_min_gap = finite_min(metrics.slower_lead_min_gap, active_slow_event["min_gap"])
  if active_false_far_brake is not None and capture_events and len(events) < max_events:
    events.append({
      "route": route,
      "kind": "false_far_lead_brake",
      "start_mono_time": active_false_far_brake["start_mono_time"],
      "duration": prev_plan_t / 1e9 - active_false_far_brake["start_t"] if prev_plan_t is not None else 0.0,
      "min_a_target": active_false_far_brake["min_a_target"],
      "min_lead_dist": active_false_far_brake["min_lead_dist"],
      "max_closing_speed": active_false_far_brake["max_closing_speed"],
      "start_v_ego": active_false_far_brake["start_v_ego"],
      "start_v_lead": active_false_far_brake["start_v_lead"],
      "lead_prob": active_false_far_brake["lead_prob"],
      "source": active_false_far_brake["source"],
      "filter_time_factor": active_false_far_brake["filter_time_factor"],
    })
  if active_false_far_brake is not None:
    metrics.false_far_lead_brake_count += 1

  if highway_accels:
    metrics.highway_accel_std = float(np.std(highway_accels))
  if highway_jerks:
    metrics.highway_rms_jerk = float(np.sqrt(np.mean(np.square(highway_jerks))))
  if near_speed_accels:
    metrics.near_speed_accel_std = float(np.std(near_speed_accels))
  if near_speed_jerks:
    metrics.near_speed_rms_jerk = float(np.sqrt(np.mean(np.square(near_speed_jerks))))

  metrics.slower_lead_mean_response_delay = finite_mean(slower_response_delays)
  metrics.slower_lead_worst_response_delay = finite_max(slower_response_delays)
  return metrics, events


def route_weight(route: str, priority_routes: set[str], priority_weight: float, normal_count: int, priority_count: int) -> float:
  if priority_count == 0 or normal_count == 0:
    return 1.0 / max(priority_count + normal_count, 1)
  if route in priority_routes and priority_count > 0:
    return priority_weight / priority_count
  if route not in priority_routes and normal_count > 0:
    return (1.0 - priority_weight) / normal_count
  return 0.0


def aggregate_summary(results: list[RouteMetrics], priority_routes: set[str], priority_weight: float) -> dict:
  priority_count = sum(1 for result in results if result.route in priority_routes)
  normal_count = len(results) - priority_count
  weighted = defaultdict(float)
  for result in results:
    weight = route_weight(result.route, priority_routes, priority_weight, normal_count, priority_count)
    weighted["route_count"] += weight
    weighted["brake_stab_count"] += weight * result.brake_stab_count
    weighted["false_far_lead_brake_count"] += weight * result.false_far_lead_brake_count
    weighted["highway_accel_std"] += weight * result.highway_accel_std
    weighted["highway_rms_jerk"] += weight * result.highway_rms_jerk
    weighted["near_speed_accel_std"] += weight * result.near_speed_accel_std
    weighted["near_speed_rms_jerk"] += weight * result.near_speed_rms_jerk
    if result.slower_lead_mean_response_delay is not None:
      weighted["slower_lead_mean_response_delay"] += weight * result.slower_lead_mean_response_delay
    if result.slower_lead_worst_response_delay is not None:
      weighted["slower_lead_worst_response_delay"] += weight * result.slower_lead_worst_response_delay
  return dict(weighted)


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(
    description="Replay the longitudinal planner directly on local route logs and score planner behavior. Route identifiers are runtime-only inputs."
  )
  parser.add_argument("routes", nargs="+", help="Route or segment identifiers to replay")
  parser.add_argument("--priority-route", action="append", default=[],
                      help="Route identifier to weight in the priority subset")
  parser.add_argument("--priority-weight", type=float, default=0.60,
                      help="Total weight assigned to the priority subset")
  parser.add_argument("--planner-profile", choices=("current", "legacy_panic_bypass"), default="current",
                      help="Planner behavior profile used for local comparison runs")
  parser.add_argument("--cached-rlogs", action="store_true",
                      help="Replay from locally cached rlogs rebuilt from the download cache")
  parser.add_argument("--json-out", type=str,
                      help="Optional local output path for JSON results")
  parser.add_argument("--events-out", type=str,
                      help="Optional local output path for captured debug events")
  parser.add_argument("--max-events-per-route", type=int, default=200,
                      help="Maximum number of debug events to capture per route")
  return parser.parse_args()


def main() -> None:
  args = parse_args()
  configure_planner_profile(args.planner_profile)

  scored = [score_route(route,
                        capture_events=bool(args.events_out),
                        max_events=args.max_events_per_route,
                        use_cached_rlogs=args.cached_rlogs) for route in args.routes]
  results = [result for result, _ in scored]
  events = {route: route_events for (result, route_events), route in zip(scored, args.routes)}
  payload = {
    "summary": aggregate_summary(results, set(args.priority_route), args.priority_weight),
    "routes": [asdict(result) for result in results],
  }

  if args.json_out:
    out_dir = os.path.dirname(args.json_out)
    if out_dir:
      os.makedirs(out_dir, exist_ok=True)
    with open(args.json_out, "w", encoding="utf-8") as f:
      json.dump(payload, f, indent=2, sort_keys=True)

  if args.events_out:
    out_dir = os.path.dirname(args.events_out)
    if out_dir:
      os.makedirs(out_dir, exist_ok=True)
    with open(args.events_out, "w", encoding="utf-8") as f:
      json.dump(events, f, indent=2, sort_keys=True)

  print(json.dumps(payload, indent=2, sort_keys=True))


if __name__ == "__main__":
  main()
