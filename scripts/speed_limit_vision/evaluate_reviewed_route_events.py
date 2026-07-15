#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from collections import Counter, defaultdict
from dataclasses import dataclass
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from import_manual_review_queue import merged_review_rows, parse_speed  # type: ignore
  from replay_route_runtime import RouteReplayDaemon, configure_models  # type: ignore
else:
  from .import_manual_review_queue import merged_review_rows, parse_speed
  from .replay_route_runtime import RouteReplayDaemon, configure_models


POSITIVE_STATUSES = frozenset(("accepted", "corrected"))


@dataclass(frozen=True)
class ReviewedCase:
  record_key: str
  route: str
  segment: int
  frame_time_s: float
  source_video_path: Path
  expected_speed_limit_mph: int
  negative: bool


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Evaluate reviewed sign events through realistic runtime cadence and publish logic.")
  parser.add_argument("--queue", type=Path, required=True, help="Reviewed manual_review_queue.csv.")
  parser.add_argument("--labels", type=Path, help="Defaults to manual_review_labels.csv beside the queue.")
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"), help="Candidate ONNX model directory.")
  parser.add_argument("--output-csv", type=Path, required=True, help="Per-event evaluation output.")
  parser.add_argument("--window-before", type=float, default=4.0, help="Seconds replayed before the reviewed frame.")
  parser.add_argument("--window-after", type=float, default=3.0, help="Seconds replayed after the reviewed frame.")
  parser.add_argument("--dedupe-seconds", type=float, default=3.0, help="Collapse nearby reviewed rows with the same expected value.")
  parser.add_argument("--measured-base-inference-seconds", type=float, default=0.44, help="Measured no-proposal comma inference cost.")
  parser.add_argument("--measured-classifier-forward-seconds", type=float, default=0.066, help="Measured comma cost per classifier forward.")
  parser.add_argument("--measured-tracking-base-seconds", type=float, default=0.012, help="Measured optical-flow and crop preparation cost.")
  parser.add_argument("--disable-temporal-tracking", action="store_true", help="Disable proposal tracking for an A/B evaluation.")
  parser.add_argument("--track-classification-interval", type=float, help="Override seconds between tracked crop classifications.")
  parser.add_argument("--track-detector-interval", type=float, help="Override detector cadence while a proposal track is active.")
  parser.add_argument("--track-min-proposal-confidence", type=float, help="Override detector confidence required to begin tracking.")
  parser.add_argument("--track-unreadable-min-proposal-confidence", type=float, help="Override confidence required to track a proposal with no readable value.")
  parser.add_argument("--track-max-age", type=float, help="Override the maximum proposal track lifetime.")
  parser.add_argument("--crop-ocr", action="store_true", help="Evaluate with crop OCR confirmation enabled.")
  parser.add_argument("--classifier-min-confidence", type=float, help="Override the value classifier confidence threshold.")
  parser.add_argument("--trusted-model-min-confidence", type=float, help="Override tiny-box trusted model confidence.")
  parser.add_argument("--classifier-expansion-limit", type=int, help="Evaluate only the first N detector crop expansions.")
  parser.add_argument("--classifier-expansion-indices", help="Comma-separated detector crop expansion indices to evaluate.")
  parser.add_argument("--strong-rescue-min-proposal-confidence", type=float, help="Override single-frame tiny-sign proposal confidence.")
  parser.add_argument("--strong-rescue-min-read-confidence", type=float, help="Override single-frame tiny-sign classifier confidence.")
  parser.add_argument("--strong-rescue-min-support", type=int, help="Override agreeing crops required for tiny-sign strong rescue.")
  parser.add_argument("--low-speed-change-consistent-detections", type=int, help="Override reads required to change from 30+ mph to below 30 mph.")
  parser.add_argument("--low-speed-change-min-confidence", type=float, help="Override confidence required to change from 30+ mph to below 30 mph.")
  parser.add_argument(
    "--allow-low-speed-strong-consensus",
    action="store_true",
    help="Permit a strong multi-crop consensus to publish a low-speed change from one frame.",
  )
  parser.add_argument(
    "--enable-strong-model-consensus",
    action="store_true",
    help="Mark three agreeing high-confidence regulatory model crops as strong consensus.",
  )
  parser.add_argument(
    "--strong-model-min-proposal-confidence",
    type=float,
    help="Override proposal confidence required for a crop to contribute to strong model consensus.",
  )
  parser.add_argument(
    "--strong-model-consensus-min-read-confidence",
    type=float,
    help="Override classifier confidence required for a crop to contribute to strong model consensus.",
  )
  parser.add_argument(
    "--strong-model-consensus-min-support",
    type=int,
    help="Override the number of agreeing classifier crops required for strong model consensus.",
  )
  parser.add_argument("--initial-speed-limit", type=int, default=0, help="Seed each replay window with a currently published speed limit.")
  parser.add_argument("--positive-only", action="store_true", help="Replay only reviewed speed signs, omitting ignored-crop windows.")
  parser.add_argument("--negative-only", action="store_true", help="Replay only ignored not-speed-limit windows.")
  parser.add_argument("--route-file", type=Path, help="Only replay routes listed one per line in this file.")
  parser.add_argument("--record-key-file", type=Path, help="Only replay record keys listed one per line in this file.")
  parser.add_argument("--focus-eval-csv", type=Path, help="Only replay records selected from an earlier runtime evaluation.")
  parser.add_argument(
    "--focus-outcome",
    choices=("candidate_hit", "publish_hit"),
    default="candidate_hit",
    help="Outcome that must be false in --focus-eval-csv.",
  )
  parser.add_argument("--strong-detection-confidence", type=float, help="Override one-frame publication confidence.")
  parser.add_argument("--consistent-detections", type=int, help="Override matching reads required for an initial publication.")
  parser.add_argument("--change-consistent-detections", type=int, help="Override matching reads required to change a publication.")
  parser.add_argument("--change-single-read-min-confidence", type=float, help="Override confidence for a one-read speed change.")
  parser.add_argument("--change-repeat-min-confidence", type=float, help="Override confidence required from the confirming speed-change read.")
  parser.add_argument("--max-cases", type=int, default=0, help="Optional evaluation cap after deduplication.")
  return parser.parse_args()


def load_cases(queue_path: Path, labels_path: Path, dedupe_seconds: float) -> list[ReviewedCase]:
  rows = merged_review_rows(queue_path, labels_path)
  cases: list[ReviewedCase] = []
  seen_buckets: set[tuple[str, int, int, int, bool]] = set()
  for row in rows:
    status = row.get("review_status", "")
    positive = status in POSITIVE_STATUSES
    negative = status == "ignore" and row.get("review_sign_type") == "not_speed_limit"
    if not positive and not negative:
      continue
    speed = parse_speed(row.get("review_speed_limit_mph", "")) if positive else 0
    if positive and not speed:
      continue
    try:
      segment = int(row.get("segment", ""))
      frame_time_s = float(row.get("frame_time_s", ""))
    except ValueError:
      continue
    source_video = Path(row.get("source_video_path", "")).expanduser()
    if not source_video.is_file():
      continue
    bucket = int(frame_time_s / max(dedupe_seconds, 0.1))
    dedupe_key = (row.get("route", ""), segment, bucket, speed, negative)
    if dedupe_key in seen_buckets:
      continue
    seen_buckets.add(dedupe_key)
    cases.append(ReviewedCase(
      record_key=row.get("record_key", ""),
      route=row.get("route", ""),
      segment=segment,
      frame_time_s=frame_time_s,
      source_video_path=source_video.resolve(),
      expected_speed_limit_mph=speed,
      negative=negative,
    ))
  return cases


def replay_video_cases(cases: list[ReviewedCase], args: argparse.Namespace) -> dict[str, tuple[list[dict[str, str]], int, int, int, int, float]]:
  daemons = {
    case.record_key: RouteReplayDaemon(
      runtime_context=None,
      measured_inference_seconds=0.0,
      measured_base_inference_seconds=args.measured_base_inference_seconds,
      measured_classifier_forward_seconds=args.measured_classifier_forward_seconds,
      measured_tracking_base_seconds=args.measured_tracking_base_seconds,
    )
    for case in cases
  }
  for daemon in daemons.values():
    daemon.published_speed_limit_mph = args.initial_speed_limit
    daemon.last_published_support_at = 0.0
  capture = cv2.VideoCapture(str(cases[0].source_video_path))
  fps = capture.get(cv2.CAP_PROP_FPS) or 20.0
  frame_count = int(capture.get(cv2.CAP_PROP_FRAME_COUNT) or 0)
  duration_s = frame_count / fps if frame_count > 0 else 60.0
  windows = {
    case.record_key: (
      max(case.frame_time_s - args.window_before, 0.0),
      min(case.frame_time_s + args.window_after, duration_s),
    )
    for case in cases
  }
  first_frame = max(int(min(window[0] for window in windows.values()) * fps), 0)
  end_frame = max(int(max(window[1] for window in windows.values()) * fps), first_frame)
  # Raw comma HEVC streams do not contain a usable random-access index.
  # OpenCV accepts CAP_PROP_POS_FRAMES but still returns frame zero.
  frame_index = 0
  while frame_index < first_frame:
    if not capture.grab():
      break
    frame_index += 1

  while frame_index <= end_frame:
    ok, frame_bgr = capture.read()
    if not ok:
      break
    frame_time_s = frame_index / fps
    for case in cases:
      start_s, end_s = windows[case.record_key]
      if start_s <= frame_time_s <= end_s:
        daemons[case.record_key].process_frame(frame_time_s - start_s, frame_bgr)
    frame_index += 1
  capture.release()

  results = {}
  for case in cases:
    daemon = daemons[case.record_key]
    results[case.record_key] = (
      daemon.events,
      daemon.inference_frames,
      daemon.detector_inference_count,
      daemon.track_inference_count,
      daemon.track_start_count,
      daemon.max_track_proposal_confidence,
    )
  return results


def main() -> int:
  args = parse_args()
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  configure_models(args.models_dir)
  if args.disable_temporal_tracking:
    slv.TEMPORAL_TRACKING_ENABLED = False
  if args.track_classification_interval is not None:
    slv.TRACK_CLASSIFICATION_INTERVAL = args.track_classification_interval
  if args.track_detector_interval is not None:
    slv.TRACK_DETECTOR_INTERVAL = args.track_detector_interval
  if args.track_min_proposal_confidence is not None:
    slv.TRACK_MIN_PROPOSAL_CONFIDENCE = args.track_min_proposal_confidence
  if args.track_unreadable_min_proposal_confidence is not None:
    slv.TRACK_UNREADABLE_MIN_PROPOSAL_CONFIDENCE = args.track_unreadable_min_proposal_confidence
  if args.track_max_age is not None:
    slv.TRACK_MAX_AGE_SECONDS = args.track_max_age
  slv.DETECTOR_CLASSIFIER_CROP_OCR_ENABLED = args.crop_ocr
  if args.classifier_min_confidence is not None:
    slv.US_CLASSIFIER_MIN_CONFIDENCE = args.classifier_min_confidence
  if args.trusted_model_min_confidence is not None:
    slv.DETECTOR_CLASSIFIER_TRUSTED_MODEL_MIN_READ_CONFIDENCE = args.trusted_model_min_confidence
  if args.classifier_expansion_indices:
    indices = tuple(int(value) for value in args.classifier_expansion_indices.split(","))
    if not indices or min(indices) < 0 or max(indices) >= len(slv.DETECTOR_CLASSIFIER_EXPANSIONS):
      raise ValueError("--classifier-expansion-indices contains an invalid index")
    slv.DETECTOR_CLASSIFIER_EXPANSIONS = tuple(slv.DETECTOR_CLASSIFIER_EXPANSIONS[index] for index in indices)
  elif args.classifier_expansion_limit is not None:
    if args.classifier_expansion_limit < 1:
      raise ValueError("--classifier-expansion-limit must be at least 1")
    slv.DETECTOR_CLASSIFIER_EXPANSIONS = slv.DETECTOR_CLASSIFIER_EXPANSIONS[:args.classifier_expansion_limit]
  if args.strong_rescue_min_proposal_confidence is not None:
    slv.DETECTOR_CLASSIFIER_STRONG_RESCUE_MIN_PROPOSAL_CONFIDENCE = args.strong_rescue_min_proposal_confidence
  if args.strong_rescue_min_read_confidence is not None:
    slv.DETECTOR_CLASSIFIER_STRONG_RESCUE_MIN_READ_CONFIDENCE = args.strong_rescue_min_read_confidence
  if args.strong_rescue_min_support is not None:
    if args.strong_rescue_min_support < 1:
      raise ValueError("--strong-rescue-min-support must be at least 1")
    slv.DETECTOR_CLASSIFIER_STRONG_RESCUE_MIN_SUPPORT = args.strong_rescue_min_support
  if args.low_speed_change_consistent_detections is not None:
    slv.LOW_SPEED_CHANGE_CONSISTENT_DETECTIONS = args.low_speed_change_consistent_detections
  if args.low_speed_change_min_confidence is not None:
    slv.LOW_SPEED_CHANGE_MIN_CONFIDENCE = args.low_speed_change_min_confidence
  if args.allow_low_speed_strong_consensus:
    slv.LOW_SPEED_CHANGE_ALLOW_STRONG_CONSENSUS = True
  if args.enable_strong_model_consensus:
    slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_ENABLED = True
  if args.strong_model_min_proposal_confidence is not None:
    slv.DETECTOR_CLASSIFIER_STRONG_MODEL_MIN_PROPOSAL_CONFIDENCE = args.strong_model_min_proposal_confidence
  if args.strong_model_consensus_min_read_confidence is not None:
    slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_MIN_READ_CONFIDENCE = args.strong_model_consensus_min_read_confidence
  if args.strong_model_consensus_min_support is not None:
    if args.strong_model_consensus_min_support < 1:
      raise ValueError("--strong-model-consensus-min-support must be at least 1")
    slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_MIN_SUPPORT = args.strong_model_consensus_min_support
  if args.strong_detection_confidence is not None:
    slv.STRONG_DETECTION_CONFIDENCE = args.strong_detection_confidence
  if args.consistent_detections is not None:
    slv.CONSISTENT_DETECTIONS = args.consistent_detections
  if args.change_consistent_detections is not None:
    slv.CHANGE_CONSISTENT_DETECTIONS = args.change_consistent_detections
  if args.change_single_read_min_confidence is not None:
    slv.CHANGE_SINGLE_READ_MIN_CONFIDENCE = args.change_single_read_min_confidence
  if args.change_repeat_min_confidence is not None:
    slv.CHANGE_REPEAT_MIN_CONFIDENCE = args.change_repeat_min_confidence
  cases = load_cases(queue_path, labels_path, args.dedupe_seconds)
  if args.focus_eval_csv:
    with args.focus_eval_csv.expanduser().resolve().open(encoding="utf-8", newline="") as input_file:
      selected_record_keys = {
        row.get("record_key", "")
        for row in csv.DictReader(input_file)
        if row.get("record_key") and row.get(args.focus_outcome, "").strip().lower() not in ("1", "true", "yes")
      }
    cases = [case for case in cases if case.record_key in selected_record_keys]
  if args.record_key_file:
    selected_record_keys = {
      line.strip() for line in args.record_key_file.expanduser().resolve().read_text(encoding="utf-8").splitlines() if line.strip()
    }
    cases = [case for case in cases if case.record_key in selected_record_keys]
  if args.route_file:
    selected_routes = {
      line.strip() for line in args.route_file.expanduser().resolve().read_text(encoding="utf-8").splitlines() if line.strip()
    }
    cases = [case for case in cases if case.route in selected_routes]
  if args.positive_only:
    cases = [case for case in cases if not case.negative]
  if args.negative_only:
    cases = [case for case in cases if case.negative]
  if args.positive_only and args.negative_only:
    raise ValueError("--positive-only and --negative-only are mutually exclusive")
  if args.max_cases > 0:
    cases = cases[:args.max_cases]

  output_rows: list[dict[str, object]] = []
  positive_by_speed: dict[int, Counter[str]] = defaultdict(Counter)
  negative_counts: Counter[str] = Counter()
  results: dict[str, tuple[list[dict[str, str]], int, int, int, int, float]] = {}
  cases_by_video: dict[Path, list[ReviewedCase]] = defaultdict(list)
  for case in cases:
    cases_by_video[case.source_video_path].append(case)
  for index, video_cases in enumerate(cases_by_video.values(), start=1):
    results.update(replay_video_cases(video_cases, args))
    if index % 10 == 0:
      print(f"Replayed {index}/{len(cases_by_video)} video segments", flush=True)

  for case in cases:
    events, inference_frames, detector_inference_frames, track_inference_frames, track_starts, max_track_confidence = results.get(
      case.record_key, ([], 0, 0, 0, 0, 0.0),
    )
    candidate_events = [event for event in events if event["event"] == "candidate"]
    publish_events = [event for event in events if event["event"] == "publish"]
    candidates = [int(event["candidateSpeedLimitMph"]) for event in candidate_events]
    publishes = [int(event["speedLimitMph"]) for event in publish_events]
    candidate_hit = case.expected_speed_limit_mph in candidates if not case.negative else False
    publish_hit = case.expected_speed_limit_mph in publishes if not case.negative else False
    wrong_candidate_values = [] if case.negative else [value for value in candidates if value != case.expected_speed_limit_mph]
    wrong_publish_values = [] if case.negative else [value for value in publishes if value != case.expected_speed_limit_mph]
    false_candidate = bool(candidates) if case.negative else False
    false_publish = bool(publishes) if case.negative else False
    if case.negative:
      negative_counts.update(total=1, candidate_fp=int(false_candidate), publish_fp=int(false_publish))
    else:
      positive_by_speed[case.expected_speed_limit_mph].update(
        total=1,
        candidate_hit=int(candidate_hit),
        publish_hit=int(publish_hit),
        wrong_candidate=int(bool(wrong_candidate_values)),
        wrong_publish=int(bool(wrong_publish_values)),
      )
    output_rows.append({
      "record_key": case.record_key,
      "route": case.route,
      "segment": case.segment,
      "frame_time_s": f"{case.frame_time_s:.3f}",
      "expected_speed_limit_mph": "" if case.negative else case.expected_speed_limit_mph,
      "negative": case.negative,
      "candidate_values": "|".join(str(value) for value in candidates),
      "publish_values": "|".join(str(value) for value in publishes),
      "candidate_confidences": "|".join(event.get("candidateConfidence", "") for event in candidate_events),
      "candidate_strong_consensus": "|".join(event.get("candidateStrongConsensus", "") for event in candidate_events),
      "publish_confidences": "|".join(event.get("confidence", "") for event in publish_events),
      "candidate_hit": candidate_hit,
      "publish_hit": publish_hit,
      "wrong_candidate_values": "|".join(str(value) for value in wrong_candidate_values),
      "wrong_publish_values": "|".join(str(value) for value in wrong_publish_values),
      "wrong_candidate": bool(wrong_candidate_values),
      "wrong_publish": bool(wrong_publish_values),
      "false_candidate": false_candidate,
      "false_publish": false_publish,
      "inference_frames": inference_frames,
      "detector_inference_frames": detector_inference_frames,
      "track_inference_frames": track_inference_frames,
      "track_starts": track_starts,
      "max_track_proposal_confidence": f"{max_track_confidence:.4f}",
      "source_video_path": str(case.source_video_path),
    })
  output_path = args.output_csv.expanduser().resolve()
  output_path.parent.mkdir(parents=True, exist_ok=True)
  fieldnames = list(output_rows[0]) if output_rows else []
  with output_path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(output_rows)

  totals = Counter()
  for counts in positive_by_speed.values():
    totals.update(counts)
  negative_scope = " ".join((
    "Reviewed negative labels apply to the proposed crop.",
    "Candidate/publish counts replay the full video window and are an upper bound, not confirmed false positives,",
    "because another valid sign may be visible in that window.",
  ))
  summary = {
    "models_dir": str(args.models_dir.expanduser().resolve()),
    "crop_ocr": args.crop_ocr,
    "classifier_min_confidence": slv.US_CLASSIFIER_MIN_CONFIDENCE,
    "measured_base_inference_seconds": args.measured_base_inference_seconds,
    "measured_classifier_forward_seconds": args.measured_classifier_forward_seconds,
    "measured_tracking_base_seconds": args.measured_tracking_base_seconds,
    "temporal_tracking_enabled": slv.TEMPORAL_TRACKING_ENABLED,
    "track_confirmed_proposals_enabled": slv.TRACK_CONFIRMED_PROPOSALS_ENABLED,
    "track_classification_interval": slv.TRACK_CLASSIFICATION_INTERVAL,
    "track_detector_interval": slv.TRACK_DETECTOR_INTERVAL,
    "track_min_proposal_confidence": slv.TRACK_MIN_PROPOSAL_CONFIDENCE,
    "track_unreadable_min_proposal_confidence": slv.TRACK_UNREADABLE_MIN_PROPOSAL_CONFIDENCE,
    "track_max_age_seconds": slv.TRACK_MAX_AGE_SECONDS,
    "initial_speed_limit_mph": args.initial_speed_limit,
    "low_speed_change_consistent_detections": slv.LOW_SPEED_CHANGE_CONSISTENT_DETECTIONS,
    "low_speed_change_min_confidence": slv.LOW_SPEED_CHANGE_MIN_CONFIDENCE,
    "change_single_read_min_confidence": slv.CHANGE_SINGLE_READ_MIN_CONFIDENCE,
    "change_repeat_min_confidence": slv.CHANGE_REPEAT_MIN_CONFIDENCE,
    "low_speed_change_allow_strong_consensus": slv.LOW_SPEED_CHANGE_ALLOW_STRONG_CONSENSUS,
    "strong_model_consensus_enabled": slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_ENABLED,
    "strong_model_min_proposal_confidence": slv.DETECTOR_CLASSIFIER_STRONG_MODEL_MIN_PROPOSAL_CONFIDENCE,
    "strong_model_consensus_min_read_confidence": slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_MIN_READ_CONFIDENCE,
    "strong_model_consensus_min_support": slv.DETECTOR_CLASSIFIER_STRONG_MODEL_CONSENSUS_MIN_SUPPORT,
    "positive": dict(totals),
    "positive_by_speed": {str(speed): dict(counts) for speed, counts in sorted(positive_by_speed.items())},
    "negative": dict(negative_counts),
    "negative_scope": negative_scope,
  }
  summary_path = output_path.with_suffix(".json")
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
