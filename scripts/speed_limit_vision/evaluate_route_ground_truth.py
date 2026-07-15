#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from replay_route_runtime import (  # type: ignore
    build_runtime_context,
    configure_models,
    qlog_paths,
    replay_route,
    route_log_id,
    segment_paths,
  )
else:
  from .replay_route_runtime import build_runtime_context, configure_models, qlog_paths, replay_route, route_log_id, segment_paths


@dataclass(frozen=True)
class GroundTruthEvent:
  route: str
  time_s: float
  speed_limit_mph: int
  sign_type: str
  initial_speed_limit_mph: int
  notes: str


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Score continuous route replay against independently labeled speed-sign events.")
  parser.add_argument("--ground-truth", type=Path, required=True, help="CSV with route,time_s,speed_limit_mph and optional metadata.")
  parser.add_argument("--clip-root", type=Path, default=Path("/Volumes/T5/starpilot_speed_limit/realdata"))
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"))
  parser.add_argument("--output-csv", type=Path, required=True)
  parser.add_argument("--window-before", type=float, default=2.0)
  parser.add_argument("--window-after", type=float, default=4.0)
  parser.add_argument("--event-dedupe-seconds", type=float, default=2.0)
  parser.add_argument("--qlog-context", action="store_true")
  parser.add_argument("--measured-base-inference-seconds", type=float, default=0.44)
  parser.add_argument("--measured-classifier-forward-seconds", type=float, default=0.066)
  parser.add_argument("--crop-ocr", action="store_true")
  return parser.parse_args()


def int_value(text: str, default: int = 0) -> int:
  try:
    return int(float(text))
  except (TypeError, ValueError):
    return default


def load_ground_truth(path: Path) -> list[GroundTruthEvent]:
  events: list[GroundTruthEvent] = []
  with path.open(encoding="utf-8", newline="") as input_file:
    for row in csv.DictReader(input_file):
      route = route_log_id(row.get("route", ""))
      try:
        time_s = float(row.get("time_s", ""))
      except ValueError:
        continue
      speed = int_value(row.get("speed_limit_mph", ""))
      applicable = row.get("applicable", "true").strip().lower() not in ("0", "false", "no")
      if not route or time_s < 0 or speed <= 0 or not applicable:
        continue
      events.append(GroundTruthEvent(
        route=route,
        time_s=time_s,
        speed_limit_mph=speed,
        sign_type=row.get("sign_type", "regulatory").strip() or "regulatory",
        initial_speed_limit_mph=int_value(row.get("initial_speed_limit_mph", "")),
        notes=row.get("notes", "").strip(),
      ))
  return sorted(events, key=lambda event: (event.route, event.time_s))


def runtime_value(event: dict[str, str]) -> int:
  key = "candidateSpeedLimitMph" if event.get("event") == "candidate" else "speedLimitMph"
  return int_value(event.get(key, ""))


def clustered_runtime_events(events: list[dict[str, str]], event_type: str, dedupe_seconds: float) -> list[dict[str, str]]:
  clusters: list[dict[str, str]] = []
  for event in events:
    if event.get("event") != event_type or runtime_value(event) <= 0:
      continue
    if (
      clusters and
      runtime_value(clusters[-1]) == runtime_value(event) and
      float(event["time_s"]) - float(clusters[-1]["time_s"]) <= dedupe_seconds
    ):
      continue
    clusters.append(event)
  return clusters


def events_in_window(events: list[dict[str, str]], truth: GroundTruthEvent, before: float, after: float) -> list[dict[str, str]]:
  return [event for event in events if truth.time_s - before <= float(event["time_s"]) <= truth.time_s + after]


def first_exact(events: list[dict[str, str]], speed: int) -> dict[str, str] | None:
  return next((event for event in events if runtime_value(event) == speed), None)


def score_route(
  truth_events: list[GroundTruthEvent],
  runtime_events: list[dict[str, str]],
  window_before: float,
  window_after: float,
  dedupe_seconds: float,
) -> tuple[list[dict[str, object]], Counter[str]]:
  candidates = clustered_runtime_events(runtime_events, "candidate", dedupe_seconds)
  publishes = clustered_runtime_events(runtime_events, "publish", dedupe_seconds)
  rows: list[dict[str, object]] = []
  totals: Counter[str] = Counter(total=len(truth_events))

  for truth in truth_events:
    candidate_window = events_in_window(candidates, truth, window_before, window_after)
    publish_window = events_in_window(publishes, truth, window_before, window_after)
    exact_candidate = first_exact(candidate_window, truth.speed_limit_mph)
    exact_publish = first_exact(publish_window, truth.speed_limit_mph)
    wrong_candidates = sorted({runtime_value(event) for event in candidate_window if runtime_value(event) != truth.speed_limit_mph})
    wrong_publishes = sorted({runtime_value(event) for event in publish_window if runtime_value(event) != truth.speed_limit_mph})
    totals.update(
      candidate_hit=int(exact_candidate is not None),
      publish_hit=int(exact_publish is not None),
      wrong_candidate=int(bool(wrong_candidates)),
      wrong_publish=int(bool(wrong_publishes)),
    )
    rows.append({
      "route": truth.route,
      "time_s": f"{truth.time_s:.3f}",
      "speed_limit_mph": truth.speed_limit_mph,
      "sign_type": truth.sign_type,
      "candidate_hit": exact_candidate is not None,
      "publish_hit": exact_publish is not None,
      "candidate_latency_s": f"{float(exact_candidate['time_s']) - truth.time_s:.3f}" if exact_candidate else "",
      "publish_latency_s": f"{float(exact_publish['time_s']) - truth.time_s:.3f}" if exact_publish else "",
      "candidate_values": "|".join(str(runtime_value(event)) for event in candidate_window),
      "publish_values": "|".join(str(runtime_value(event)) for event in publish_window),
      "wrong_candidate_values": "|".join(map(str, wrong_candidates)),
      "wrong_publish_values": "|".join(map(str, wrong_publishes)),
      "notes": truth.notes,
    })

  unmatched_publishes = [
    event for event in publishes
    if not any(
      truth.time_s - window_before <= float(event["time_s"]) <= truth.time_s + window_after and
      runtime_value(event) == truth.speed_limit_mph
      for truth in truth_events
    )
  ]
  totals["publish_bursts"] = len(publishes)
  totals["unmatched_publish_bursts"] = len(unmatched_publishes)
  return rows, totals


def main() -> int:
  args = parse_args()
  configure_models(args.models_dir)
  slv.DETECTOR_CLASSIFIER_CROP_OCR_ENABLED = args.crop_ocr
  clip_root = args.clip_root.expanduser().resolve()
  truth_by_route: dict[str, list[GroundTruthEvent]] = defaultdict(list)
  for event in load_ground_truth(args.ground_truth.expanduser().resolve()):
    truth_by_route[event.route].append(event)
  if not truth_by_route:
    raise ValueError("Ground-truth manifest contains no applicable speed-sign events")

  output_rows: list[dict[str, object]] = []
  aggregate: Counter[str] = Counter()
  by_speed: dict[int, Counter[str]] = defaultdict(Counter)
  route_summaries: dict[str, dict[str, int]] = {}
  for route, truth_events in truth_by_route.items():
    segments = segment_paths(clip_root, route)
    if not segments:
      raise FileNotFoundError(f"No camera segments for {route} under {clip_root}")
    runtime_context = None
    if args.qlog_context:
      qlogs = qlog_paths(clip_root, route)
      runtime_context = build_runtime_context(qlogs) if qlogs else None
    initial_speed = next((event.initial_speed_limit_mph for event in truth_events if event.initial_speed_limit_mph > 0), 0)
    _summary, runtime_events = replay_route(
      route,
      segments,
      runtime_context,
      0.0,
      None,
      False,
      False,
      0.0,
      args.measured_base_inference_seconds,
      args.measured_classifier_forward_seconds,
      initial_speed,
    )
    rows, totals = score_route(truth_events, runtime_events, args.window_before, args.window_after, args.event_dedupe_seconds)
    output_rows.extend(rows)
    aggregate.update(totals)
    route_summaries[route] = dict(totals)
    for row in rows:
      speed_counts = by_speed[int(row["speed_limit_mph"])]
      speed_counts.update(
        total=1,
        candidate_hit=int(bool(row["candidate_hit"])),
        publish_hit=int(bool(row["publish_hit"])),
        wrong_publish=int(bool(row["wrong_publish_values"])),
      )

  output_path = args.output_csv.expanduser().resolve()
  output_path.parent.mkdir(parents=True, exist_ok=True)
  with output_path.open("w", encoding="utf-8", newline="") as output_file:
    writer = csv.DictWriter(output_file, fieldnames=list(output_rows[0]))
    writer.writeheader()
    writer.writerows(output_rows)
  summary = {
    "models_dir": str(args.models_dir.expanduser().resolve()),
    "ground_truth": str(args.ground_truth.expanduser().resolve()),
    "continuous_route_replay": True,
    "detector_selected_inputs": False,
    "measured_base_inference_seconds": args.measured_base_inference_seconds,
    "measured_classifier_forward_seconds": args.measured_classifier_forward_seconds,
    "totals": dict(aggregate),
    "by_speed": {str(speed): dict(counts) for speed, counts in sorted(by_speed.items())},
    "by_route": route_summaries,
  }
  output_path.with_suffix(".json").write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="ascii")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
