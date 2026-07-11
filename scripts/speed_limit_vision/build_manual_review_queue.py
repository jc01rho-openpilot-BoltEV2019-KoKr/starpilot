#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import math

from dataclasses import dataclass
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import ensure_dir, preferred_clip_root, resolve_workspace  # type: ignore
  from localize_bookmark_signs import configure_models  # type: ignore
  from mine_route_training_samples import (  # type: ignore
    MapContext,
    completed_marker_routes,
    fmt_read,
    iter_frames_at_times,
    load_segment_map_context,
    nearest_context,
    parse_route_id,
    read_frame_at,
    route_segments,
    safe_key,
    sample_times,
    transition_times,
  )
else:
  from .common import ensure_dir, preferred_clip_root, resolve_workspace
  from .localize_bookmark_signs import configure_models
  from .mine_route_training_samples import (
    MapContext,
    completed_marker_routes,
    fmt_read,
    iter_frames_at_times,
    load_segment_map_context,
    nearest_context,
    parse_route_id,
    read_frame_at,
    route_segments,
    safe_key,
    sample_times,
    transition_times,
  )


DEFAULT_WORKSPACE = Path("/Volumes/T5/starpilot_speed_limit/workspace/speed_limit_training_clean")
DEFAULT_ROUTE_BUNDLE_STATE_DIR = Path("/Volumes/T5/starpilot_speed_limit/analysis/route_bundles/state")
DEFAULT_OUTPUT_NAME = "manual_review_queue_v1"
PRIORITY_SPEED_VALUES = frozenset((30, 35, 40, 45, 50, 55, 60, 65))
FIELDNAMES = [
  "record_key",
  "route",
  "dongle_id",
  "log_id",
  "segment",
  "frame_time_s",
  "frame_path",
  "crop_path",
  "source_video_path",
  "bbox",
  "crop_bbox",
  "class_id",
  "detector_class",
  "proposal_confidence",
  "candidate_speed_limit_mph",
  "candidate_confidence",
  "model_read",
  "ocr_read",
  "full_detection",
  "read_sources",
  "read_support_count",
  "is_regulatory",
  "map_current_speed_limit_mph",
  "map_next_speed_limit_mph",
  "map_next_speed_limit_distance_m",
  "map_relation",
  "review_priority",
  "review_reasons",
  "review_status",
  "review_speed_limit_mph",
  "review_sign_type",
  "review_bbox",
  "review_ignore_reason",
  "review_notes",
]


@dataclass(frozen=True)
class ReadVote:
  speed_limit_mph: int
  confidence: float
  source: str
  expansion_index: int
  crop_box: tuple[int, int, int, int]
  is_regulatory: bool
  weight: float


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Build a broad manual-review queue from comma route footage.")
  parser.add_argument("routes", nargs="*", help="Optional route ids like 'dongle/logid'. Defaults to extracted route bundle markers.")
  parser.add_argument("--routes-file", type=Path, help="Optional text file with one route id per line.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--clip-root", type=Path, default=preferred_clip_root(), help="Route realdata root.")
  parser.add_argument("--bundle-state-dir", type=Path, default=DEFAULT_ROUTE_BUNDLE_STATE_DIR, help="Completed extraction marker directory.")
  parser.add_argument("--models-dir", type=Path, help="Optional model directory for mining with non-repo ONNXs.")
  parser.add_argument("--output-dir", type=Path, help=f"Defaults to <workspace>/review/{DEFAULT_OUTPUT_NAME}.")
  parser.add_argument("--manifest-out", type=Path, help="Defaults to <output-dir>/manual_review_queue.csv.")
  parser.add_argument("--sample-every", type=float, default=2.0, help="Seconds between regular video samples.")
  parser.add_argument("--seek-sampling", action="store_true", help="Seek directly to sampled frames instead of sequential grabbing.")
  parser.add_argument("--transition-radius", type=float, default=18.0, help="Extra seconds around map speed transitions to sample densely.")
  parser.add_argument("--transition-step", type=float, default=0.75, help="Seconds between transition-window samples.")
  parser.add_argument("--max-frames-per-route", type=int, default=1200, help="Maximum frames to score per route.")
  parser.add_argument("--max-candidates-per-route", type=int, default=500, help="Maximum review candidates to keep per route.")
  parser.add_argument("--max-candidates-per-frame", type=int, default=1, help="Maximum detector candidates to keep from a single video frame. 0 keeps all.")
  parser.add_argument("--max-negatives-per-route", type=int, default=60, help="Maximum empty/no-candidate frames to keep per route.")
  parser.add_argument("--min-proposal-confidence", type=float, default=0.025, help="Loose detector confidence floor for review candidates.")
  parser.add_argument("--no-read-min-proposal-confidence", type=float, default=0.12, help="Keep no-value detector boxes above this confidence.")
  parser.add_argument("--school-zone-min-proposal-confidence", type=float, default=0.02, help="Loose floor for school-zone detector candidates.")
  parser.add_argument("--min-width", type=int, default=12, help="Minimum detector bbox width.")
  parser.add_argument("--min-height", type=int, default=16, help="Minimum detector bbox height.")
  parser.add_argument("--dedupe-seconds", type=float, default=2.5, help="Approximate time bucket used to dedupe adjacent frames.")
  parser.add_argument("--limit-routes", type=int, default=0, help="Optional maximum routes to mine.")
  parser.add_argument("--include-advisory", action=argparse.BooleanOptionalAction, default=True, help="Include advisory-speed detector class candidates.")
  parser.add_argument("--include-full-detection", action="store_true", help="Also run the full runtime detector on each frame for extra context. Slower.")
  parser.add_argument("--overwrite-images", action="store_true", help="Rewrite existing review images.")
  parser.add_argument("--dry-run", action="store_true", help="Score frames and print counts without writing images/CSV.")
  return parser.parse_args()


def read_routes(args: argparse.Namespace) -> list[str]:
  routes = list(args.routes)
  if args.routes_file:
    routes.extend(
      line.strip()
      for line in args.routes_file.expanduser().read_text(encoding="utf-8").splitlines()
      if line.strip() and not line.lstrip().startswith("#")
    )
  if not routes:
    routes = completed_marker_routes(args.bundle_state_dir.expanduser().resolve())

  deduped = []
  seen = set()
  for route in routes:
    normalized, _, _ = parse_route_id(route)
    if normalized in seen:
      continue
    seen.add(normalized)
    deduped.append(normalized)
  if args.limit_routes > 0:
    deduped = deduped[:args.limit_routes]
  return deduped


def clamp_box(box: tuple[int, int, int, int], frame_shape: tuple[int, int, int]) -> tuple[int, int, int, int] | None:
  frame_height, frame_width = frame_shape[:2]
  x1, y1, x2, y2 = box
  x1 = max(min(int(x1), frame_width), 0)
  x2 = max(min(int(x2), frame_width), 0)
  y1 = max(min(int(y1), frame_height), 0)
  y2 = max(min(int(y2), frame_height), 0)
  if x2 <= x1 or y2 <= y1:
    return None
  return x1, y1, x2, y2


def expanded_box(
  box: tuple[int, int, int, int],
  frame_shape: tuple[int, int, int],
  expand_left: float,
  expand_top: float,
  expand_right: float,
  expand_bottom: float,
) -> tuple[int, int, int, int] | None:
  x1, y1, x2, y2 = box
  width = x2 - x1
  height = y2 - y1
  return clamp_box((
    int(x1 - width * expand_left),
    int(y1 - height * expand_top),
    int(x2 + width * expand_right),
    int(y2 + height * expand_bottom),
  ), frame_shape)


def add_vote(votes: list[ReadVote], result, source: str, expansion_index: int, crop_box: tuple[int, int, int, int], is_regulatory: bool, weight: float) -> None:
  if result is None:
    return
  speed_limit_mph, confidence = result
  if int(speed_limit_mph) not in slv.US_CLASSIFIER_SPEED_VALUES:
    return
  votes.append(ReadVote(int(speed_limit_mph), float(confidence), source, expansion_index, crop_box, is_regulatory, weight))


def best_source_read(votes: list[ReadVote], source: str):
  source_votes = [vote for vote in votes if vote.source == source]
  if not source_votes:
    return None
  vote = max(source_votes, key=lambda item: item.confidence)
  return vote.speed_limit_mph, vote.confidence


def choose_vote(votes: list[ReadVote]) -> tuple[ReadVote | None, int]:
  if not votes:
    return None, 0

  support: dict[int, int] = {}
  best_by_speed: dict[int, ReadVote] = {}
  score_by_speed: dict[int, float] = {}
  for vote in votes:
    support[vote.speed_limit_mph] = support.get(vote.speed_limit_mph, 0) + 1
    if vote.speed_limit_mph not in best_by_speed or vote.confidence > best_by_speed[vote.speed_limit_mph].confidence:
      best_by_speed[vote.speed_limit_mph] = vote
    score_by_speed[vote.speed_limit_mph] = score_by_speed.get(vote.speed_limit_mph, 0.0) + vote.confidence * vote.weight

  speed_limit_mph = max(
    score_by_speed,
    key=lambda speed: (
      score_by_speed[speed] + max(support[speed] - 1, 0) * slv.DETECTOR_CLASSIFIER_SUPPORT_BONUS,
      best_by_speed[speed].confidence,
    ),
  )
  return best_by_speed[speed_limit_mph], support[speed_limit_mph]


def classify_map_relation(speed_limit_mph: int, context: MapContext, next_limit_distance_m: float = 180.0) -> str:
  if speed_limit_mph <= 0:
    if context.current_speed_limit_mph or context.next_speed_limit_mph:
      return "map_present_no_read"
    return "no_map_no_read"
  if context.current_speed_limit_mph == speed_limit_mph:
    return "agree_current"
  if context.next_speed_limit_mph == speed_limit_mph and 0.0 < context.next_speed_limit_distance_m <= next_limit_distance_m:
    return "agree_next"
  if context.current_speed_limit_mph or context.next_speed_limit_mph:
    return "map_disagreement"
  return "no_map"


def score_review_priority(class_id: int, proposal_confidence: float, chosen_vote: ReadVote | None, support_count: int, map_relation: str, reasons: set[str]) -> float:
  score = proposal_confidence * 2.0
  if chosen_vote is not None:
    score += chosen_vote.confidence * 2.0
    score += min(support_count, 4) * 0.18
    if chosen_vote.speed_limit_mph in PRIORITY_SPEED_VALUES:
      score += 2.0
    if chosen_vote.speed_limit_mph in slv.SCHOOL_ZONE_SPEED_VALUES:
      score += 0.8
  if class_id == 2:
    score += 2.2
  if "map_disagreement" in map_relation:
    score += 1.2
  if "read_disagreement" in reasons:
    score += 1.0
  if "no_value_read" in reasons:
    score += 0.5
  if "low_detector_confidence" in reasons:
    score += 0.25
  return score


def summarize_votes(votes: list[ReadVote]) -> str:
  if not votes:
    return ""
  compact = []
  for vote in sorted(votes, key=lambda item: (-item.confidence, item.source, item.expansion_index))[:8]:
    compact.append(f"{vote.source}{vote.expansion_index}:{vote.speed_limit_mph}@{vote.confidence:.3f}")
  return "|".join(compact)


def analyze_proposal(daemon: slv.SpeedLimitVisionDaemon, frame_bgr, proposal, full_detection, context: MapContext, args: argparse.Namespace):
  proposal_confidence, class_id, raw_box = proposal
  if class_id == 1 and not args.include_advisory:
    return None
  box = clamp_box(raw_box, frame_bgr.shape)
  if box is None:
    return None
  x1, y1, x2, y2 = box
  width = x2 - x1
  height = y2 - y1
  if width < args.min_width or height < args.min_height:
    return None
  if class_id == 2:
    if proposal_confidence < args.school_zone_min_proposal_confidence:
      return None
  elif proposal_confidence < args.min_proposal_confidence:
    return None

  votes: list[ReadVote] = []
  any_regulatory = False
  for expansion_index, (expand_left, expand_top, expand_right, expand_bottom, weight) in enumerate(slv.DETECTOR_CLASSIFIER_EXPANSIONS):
    crop_box = expanded_box(box, frame_bgr.shape, expand_left, expand_top, expand_right, expand_bottom)
    if crop_box is None:
      continue
    crop = frame_bgr[crop_box[1]:crop_box[3], crop_box[0]:crop_box[2]]
    if crop.size == 0:
      continue
    is_regulatory = daemon._is_regulatory_speed_sign(crop) or class_id == 2
    any_regulatory = any_regulatory or is_regulatory
    add_vote(votes, daemon._classify_speed_limit_from_model(crop), "model", expansion_index, crop_box, is_regulatory, weight)
    add_vote(votes, daemon._read_speed_limit_from_crop(crop), "ocr", expansion_index, crop_box, is_regulatory, weight)

  chosen_vote, support_count = choose_vote(votes)
  if chosen_vote is None and proposal_confidence < args.no_read_min_proposal_confidence and class_id != 2:
    return None

  model_read = best_source_read(votes, "model")
  ocr_read = best_source_read(votes, "ocr")
  candidate_speed = chosen_vote.speed_limit_mph if chosen_vote is not None else 0
  map_relation = classify_map_relation(candidate_speed, context)
  reasons: set[str] = set()
  if class_id == 2:
    reasons.add("school_zone_candidate")
  if class_id == 1:
    reasons.add("advisory_candidate")
  if chosen_vote is None:
    reasons.add("no_value_read")
  elif chosen_vote.speed_limit_mph in PRIORITY_SPEED_VALUES:
    reasons.add("priority_30_65")
  if proposal_confidence < 0.12:
    reasons.add("low_detector_confidence")
  if model_read is not None and ocr_read is not None and int(model_read[0]) != int(ocr_read[0]):
    reasons.add("read_disagreement")
  vote_values = {vote.speed_limit_mph for vote in votes}
  if len(vote_values) > 1:
    reasons.add("multi_value_votes")
  if "disagreement" in map_relation:
    reasons.add("map_disagreement")
  elif map_relation.startswith("agree"):
    reasons.add("map_agreement")
  elif map_relation.startswith("map_present"):
    reasons.add("map_context")

  crop_box = chosen_vote.crop_box if chosen_vote is not None else box
  priority = score_review_priority(class_id, proposal_confidence, chosen_vote, support_count, map_relation, reasons)
  return {
    "bbox": box,
    "crop_bbox": crop_box,
    "class_id": class_id,
    "detector_class": slv.US_DETECTOR_CLASSES.get(class_id, str(class_id)),
    "proposal_confidence": proposal_confidence,
    "candidate_speed_limit_mph": "" if chosen_vote is None else chosen_vote.speed_limit_mph,
    "candidate_confidence": "" if chosen_vote is None else f"{chosen_vote.confidence:.6f}",
    "model_read": fmt_read(model_read),
    "ocr_read": fmt_read(ocr_read),
    "full_detection": fmt_read(full_detection),
    "read_sources": summarize_votes(votes),
    "read_support_count": support_count,
    "is_regulatory": any_regulatory,
    "map_relation": map_relation,
    "review_priority": priority,
    "review_reasons": "|".join(sorted(reasons)),
  }


def write_image(path: Path, image, quality: int, overwrite: bool) -> None:
  if path.exists() and not overwrite:
    return
  ensure_dir(path.parent)
  cv2.imwrite(str(path), image, [cv2.IMWRITE_JPEG_QUALITY, quality])


def cluster_key(route_id: str, segment: int, time_s: float, frame_shape: tuple[int, int, int], candidate: dict, dedupe_seconds: float) -> str:
  x1, y1, x2, y2 = candidate["bbox"]
  frame_height, frame_width = frame_shape[:2]
  center_x = ((x1 + x2) / 2) / max(frame_width, 1)
  center_y = ((y1 + y2) / 2) / max(frame_height, 1)
  time_bucket = int(math.floor(time_s / max(dedupe_seconds, 0.1)))
  grid_x = int(center_x * 12)
  grid_y = int(center_y * 8)
  return f"{route_id}|{segment}|{time_bucket}|{candidate['class_id']}|{grid_x}|{grid_y}"


def candidate_record_key(route_key: str, segment: int, time_s: float, index: int) -> str:
  sample_index = f"s{segment:04d}_t{time_s:07.3f}_c{index:02d}".replace(".", "p")
  return f"manual_review_{route_key}_{sample_index}"


def mine_route(route_id: str, daemon: slv.SpeedLimitVisionDaemon, args: argparse.Namespace, output_dir: Path) -> tuple[list[dict[str, object]], dict[str, object]]:
  route_id, dongle_id, log_id = parse_route_id(route_id)
  route_key = safe_key(route_id)
  clip_root = args.clip_root.expanduser().resolve()
  segments = route_segments(clip_root, log_id)
  if not segments:
    return [], {"route": route_id, "status": "missing_segments", "frames": 0, "candidates": 0, "negatives": 0}

  frame_dir = output_dir / "frames"
  crop_dir = output_dir / "crops"
  rows_by_cluster: dict[str, dict[str, object]] = {}
  route_candidates = 0
  negatives = 0
  frames_scored = 0

  for segment in segments:
    if frames_scored >= args.max_frames_per_route or route_candidates >= args.max_candidates_per_route:
      break
    contexts = load_segment_map_context(segment.path)
    capture = cv2.VideoCapture(str(segment.video_path))
    fps = capture.get(cv2.CAP_PROP_FPS) or 20.0
    frame_count = capture.get(cv2.CAP_PROP_FRAME_COUNT) or 0
    duration_s = frame_count / fps if frame_count > 0 else 60.0
    times = sample_times(duration_s, args.sample_every, transition_times(contexts), args.transition_radius, args.transition_step)
    if args.seek_sampling:
      frame_iter = ((time_s, read_frame_at(capture, fps, time_s)) for time_s in times)
    else:
      frame_iter = iter_frames_at_times(capture, fps, times)

    for time_s, frame_bgr in frame_iter:
      if frames_scored >= args.max_frames_per_route or route_candidates >= args.max_candidates_per_route:
        break
      if frame_bgr is None:
        continue
      frames_scored += 1
      context = nearest_context(contexts, time_s)
      full_detection = daemon._detect_sign(frame_bgr) if args.include_full_detection else None
      proposals = daemon._collect_detector_classifier_proposals(frame_bgr)
      candidate_index = 0
      frame_candidates: list[tuple[int, dict[str, object], object]] = []
      for proposal in proposals:
        candidate = analyze_proposal(daemon, frame_bgr, proposal, full_detection, context, args)
        if candidate is None:
          continue
        candidate_index += 1
        x1, y1, x2, y2 = candidate["crop_bbox"]
        crop = frame_bgr[y1:y2, x1:x2]
        frame_candidates.append((candidate_index, candidate, crop))

      frame_candidates.sort(key=lambda item: float(item[1]["review_priority"]), reverse=True)
      if args.max_candidates_per_frame > 0:
        frame_candidates = frame_candidates[:args.max_candidates_per_frame]
      kept_any = bool(frame_candidates)

      for candidate_index, candidate, crop in frame_candidates:
        record_key = candidate_record_key(route_key, segment.segment, time_s, candidate_index)
        frame_path = frame_dir / f"{record_key}.jpg"
        crop_path = crop_dir / f"{record_key}_crop.jpg"
        row = {
          "record_key": record_key,
          "route": route_id,
          "dongle_id": dongle_id,
          "log_id": log_id,
          "segment": segment.segment,
          "frame_time_s": f"{time_s:.3f}",
          "frame_path": str(frame_path),
          "crop_path": str(crop_path),
          "source_video_path": str(segment.video_path),
          "bbox": ",".join(str(value) for value in candidate["bbox"]),
          "crop_bbox": ",".join(str(value) for value in candidate["crop_bbox"]),
          "class_id": candidate["class_id"],
          "detector_class": candidate["detector_class"],
          "proposal_confidence": f"{candidate['proposal_confidence']:.6f}",
          "candidate_speed_limit_mph": candidate["candidate_speed_limit_mph"],
          "candidate_confidence": candidate["candidate_confidence"],
          "model_read": candidate["model_read"],
          "ocr_read": candidate["ocr_read"],
          "full_detection": candidate["full_detection"],
          "read_sources": candidate["read_sources"],
          "read_support_count": candidate["read_support_count"],
          "is_regulatory": str(bool(candidate["is_regulatory"])),
          "map_current_speed_limit_mph": context.current_speed_limit_mph,
          "map_next_speed_limit_mph": context.next_speed_limit_mph,
          "map_next_speed_limit_distance_m": f"{context.next_speed_limit_distance_m:.1f}",
          "map_relation": candidate["map_relation"],
          "review_priority": f"{candidate['review_priority']:.4f}",
          "review_reasons": candidate["review_reasons"],
          "review_status": "",
          "review_speed_limit_mph": "",
          "review_sign_type": "",
          "review_bbox": "",
          "review_ignore_reason": "",
          "review_notes": "",
        }
        key = cluster_key(route_id, segment.segment, time_s, frame_bgr.shape, candidate, args.dedupe_seconds)
        existing = rows_by_cluster.get(key)
        if existing is None or float(row["review_priority"]) > float(existing["review_priority"]):
          if not args.dry_run:
            write_image(frame_path, frame_bgr, quality=88, overwrite=args.overwrite_images)
            write_image(crop_path, crop, quality=92, overwrite=args.overwrite_images)
          rows_by_cluster[key] = row
        kept_any = True

      if kept_any:
        route_candidates = len(rows_by_cluster)
      elif negatives < args.max_negatives_per_route:
        record_key = candidate_record_key(route_key, segment.segment, time_s, 0)
        frame_path = frame_dir / f"{record_key}.jpg"
        row = {
          "record_key": record_key,
          "route": route_id,
          "dongle_id": dongle_id,
          "log_id": log_id,
          "segment": segment.segment,
          "frame_time_s": f"{time_s:.3f}",
          "frame_path": str(frame_path),
          "crop_path": "",
          "source_video_path": str(segment.video_path),
          "bbox": "",
          "crop_bbox": "",
          "class_id": "",
          "detector_class": "negative_empty",
          "proposal_confidence": "",
          "candidate_speed_limit_mph": "",
          "candidate_confidence": "",
          "model_read": "",
          "ocr_read": "",
          "full_detection": fmt_read(full_detection),
          "read_sources": "",
          "read_support_count": "",
          "is_regulatory": "",
          "map_current_speed_limit_mph": context.current_speed_limit_mph,
          "map_next_speed_limit_mph": context.next_speed_limit_mph,
          "map_next_speed_limit_distance_m": f"{context.next_speed_limit_distance_m:.1f}",
          "map_relation": classify_map_relation(0, context),
          "review_priority": "0.1000",
          "review_reasons": "negative_empty",
          "review_status": "",
          "review_speed_limit_mph": "",
          "review_sign_type": "",
          "review_bbox": "",
          "review_ignore_reason": "",
          "review_notes": "",
        }
        rows_by_cluster[f"{route_id}|negative|{segment.segment}|{negatives}"] = row
        negatives += 1
        if not args.dry_run:
          write_image(frame_path, frame_bgr, quality=82, overwrite=args.overwrite_images)

    capture.release()

  rows = sorted(rows_by_cluster.values(), key=lambda row: (-float(row["review_priority"]), str(row["record_key"])))
  if args.max_candidates_per_route > 0:
    positives = [row for row in rows if row["detector_class"] != "negative_empty"][:args.max_candidates_per_route]
    negative_rows = [row for row in rows if row["detector_class"] == "negative_empty"][:args.max_negatives_per_route]
    rows = sorted(positives + negative_rows, key=lambda row: (-float(row["review_priority"]), str(row["record_key"])))
  return rows, {
    "route": route_id,
    "status": "mined",
    "frames": frames_scored,
    "candidates": sum(1 for row in rows if row["detector_class"] != "negative_empty"),
    "negatives": sum(1 for row in rows if row["detector_class"] == "negative_empty"),
  }


def write_manifest(path: Path, rows: list[dict[str, object]]) -> None:
  ensure_dir(path.parent)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=FIELDNAMES, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(rows)


def write_summary(path: Path, manifest_path: Path, rows: list[dict[str, object]], summaries: list[dict[str, object]]) -> None:
  path.write_text(json.dumps({
    "routes": summaries,
    "manifest": str(manifest_path),
    "rows": len(rows),
    "candidates": sum(1 for row in rows if row["detector_class"] != "negative_empty"),
    "negatives": sum(1 for row in rows if row["detector_class"] == "negative_empty"),
  }, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def main() -> int:
  try:
    cv2.setLogLevel(1)
  except Exception:
    pass

  args = parse_args()
  configure_models(args.models_dir)
  workspace = resolve_workspace(args.workspace)
  output_dir = args.output_dir.expanduser().resolve() if args.output_dir else ensure_dir(workspace / "review" / DEFAULT_OUTPUT_NAME)
  manifest_path = args.manifest_out.expanduser().resolve() if args.manifest_out else output_dir / "manual_review_queue.csv"
  routes = read_routes(args)
  if not routes:
    raise SystemExit("No routes to mine. Pass route ids, --routes-file, or extracted route bundle markers.")

  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  all_rows: list[dict[str, object]] = []
  summaries = []
  summary_path = output_dir / "manual_review_summary.json"
  for index, route_id in enumerate(routes, start=1):
    rows, summary = mine_route(route_id, daemon, args, output_dir)
    all_rows.extend(rows)
    summaries.append(summary)
    print(
      f"[{index}/{len(routes)}] {summary['route']}: {summary['status']} "
      f"frames={summary['frames']} candidates={summary['candidates']} negatives={summary['negatives']}"
    )
    if not args.dry_run:
      all_rows.sort(key=lambda row: (-float(row["review_priority"]), str(row["record_key"])))
      write_manifest(manifest_path, all_rows)
      write_summary(summary_path, manifest_path, all_rows, summaries)

  all_rows.sort(key=lambda row: (-float(row["review_priority"]), str(row["record_key"])))
  if not args.dry_run:
    write_manifest(manifest_path, all_rows)
    write_summary(summary_path, manifest_path, all_rows, summaries)
    print(f"Wrote {len(all_rows)} review rows to {manifest_path}")
    print(f"Summary: {summary_path}")
  else:
    print(f"Dry run rows={len(all_rows)} candidates={sum(1 for row in all_rows if row['detector_class'] != 'negative_empty')}")

  return 0


if __name__ == "__main__":
  raise SystemExit(main())
