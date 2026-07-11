#!/usr/bin/env python3
from __future__ import annotations

import argparse
import bz2
import csv
import hashlib
import json
import math

from dataclasses import dataclass
from pathlib import Path

import cv2
import zstandard as zstd
from cereal import log

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import VALUE_LABEL_FIELDS, ensure_dir, preferred_clip_root, resolve_workspace  # type: ignore
  from localize_bookmark_signs import configure_models, score_frame  # type: ignore
else:
  from .common import VALUE_LABEL_FIELDS, ensure_dir, preferred_clip_root, resolve_workspace
  from .localize_bookmark_signs import configure_models, score_frame


DEFAULT_ROUTE_BUNDLE_STATE_DIR = Path("/Volumes/T5/starpilot_speed_limit/analysis/route_bundles/state")
DEFAULT_WORKSPACE = Path("/Volumes/T5/starpilot_speed_limit/workspace/speed_limit_training_clean")
DEFAULT_REVIEW_MANIFEST_NAME = "route_training_samples.csv"
MPH_PER_MS = 2.2369362920544
VALID_WEAK_LABEL_VALUES = set(slv.US_CLASSIFIER_SPEED_VALUES)
POSITIVE_FIELDNAMES = [
  "record_key",
  "route",
  "dongle_id",
  "log_id",
  "segment",
  "frame_time_s",
  "split",
  "sample_type",
  "dataset_image",
  "dataset_label",
  "speed_limit_mph",
  "class_id",
  "bbox",
  "score",
  "proposal_confidence",
  "consistent_read_count",
  "model_read",
  "ocr_read",
  "full_detection",
  "map_current_speed_limit_mph",
  "map_next_speed_limit_mph",
  "map_next_speed_limit_distance_m",
  "map_relation",
  "source_video_path",
]


@dataclass(frozen=True)
class MapContext:
  time_s: float
  current_speed_limit_mph: int
  next_speed_limit_mph: int
  next_speed_limit_distance_m: float


@dataclass(frozen=True)
class SegmentInfo:
  segment: int
  path: Path
  video_path: Path


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Mine completed comma route clips into weakly labeled speed-limit detector/classifier samples.")
  parser.add_argument("routes", nargs="*", help="Optional route ids like 'dongle/logid'. Defaults to completed route-bundle markers.")
  parser.add_argument("--routes-file", type=Path, help="Optional text file with one route id per line.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--clip-root", type=Path, default=preferred_clip_root(), help="Route realdata root.")
  parser.add_argument("--bundle-state-dir", type=Path, default=DEFAULT_ROUTE_BUNDLE_STATE_DIR, help="Completed extraction marker directory.")
  parser.add_argument("--models-dir", type=Path, help="Optional model directory for mining with non-repo ONNXs.")
  parser.add_argument("--manifest-out", type=Path, help=f"Review manifest path. Defaults to <workspace>/review/{DEFAULT_REVIEW_MANIFEST_NAME}.")
  parser.add_argument("--sample-every", type=float, default=4.0, help="Seconds between regular video samples.")
  parser.add_argument("--seek-sampling", action="store_true", help="Seek directly to sampled frames instead of sequentially grabbing through each segment.")
  parser.add_argument("--transition-radius", type=float, default=10.0, help="Extra seconds around map speed transitions to sample densely.")
  parser.add_argument("--transition-step", type=float, default=1.0, help="Seconds between transition-window samples.")
  parser.add_argument("--max-frames-per-route", type=int, default=360, help="Maximum frames to score per route.")
  parser.add_argument("--max-positives-per-route", type=int, default=90, help="Maximum positive training images to add per route.")
  parser.add_argument("--max-negatives-per-route", type=int, default=160, help="Maximum empty-label negatives to add per route.")
  parser.add_argument("--positive-min-score", type=float, default=1.35, help="Minimum localization score for map-agreeing positives.")
  parser.add_argument("--no-map-min-score", type=float, default=1.65, help="Minimum score for positives without map agreement.")
  parser.add_argument("--min-proposal-confidence", type=float, default=0.18, help="Minimum detector proposal confidence for positives.")
  parser.add_argument("--min-width", type=int, default=24, help="Minimum mined bbox width in pixels.")
  parser.add_argument("--min-height", type=int, default=36, help="Minimum mined bbox height in pixels.")
  parser.add_argument("--next-limit-distance", type=float, default=180.0, help="Treat map next-speed as agreeing only within this many meters.")
  parser.add_argument("--val-route-modulo", type=int, default=5, help="Use route hash modulo N to choose validation routes. 0 disables.")
  parser.add_argument("--val-route-remainder", type=int, default=0, help="Validation route hash remainder.")
  parser.add_argument("--limit-routes", type=int, default=0, help="Optional maximum routes to mine.")
  parser.add_argument("--force", action="store_true", help="Re-mine routes even if the route mining marker exists.")
  parser.add_argument("--overwrite", action="store_true", help="Overwrite existing mined image/label files.")
  parser.add_argument("--dry-run", action="store_true", help="Score frames and print counts without writing dataset files.")
  return parser.parse_args()


def safe_key(text: str) -> str:
  return text.replace("/", "_").replace("|", "_").replace(":", "_")


def parse_route_id(text: str) -> tuple[str, str, str]:
  normalized = text.strip().replace("|", "/")
  if "/" not in normalized:
    raise ValueError(f"Route id must be dongle/logid: {text}")
  dongle_id, log_id = normalized.split("/", 1)
  return f"{dongle_id}/{log_id}", dongle_id, log_id


def route_split(route_id: str, val_modulo: int, val_remainder: int) -> str:
  if val_modulo <= 0:
    return "train"
  digest = hashlib.sha1(route_id.encode("utf-8")).hexdigest()
  return "val" if int(digest[:8], 16) % val_modulo == val_remainder else "train"


def completed_marker_routes(state_dir: Path) -> list[str]:
  routes: list[str] = []
  if not state_dir.is_dir():
    return routes
  for marker in sorted(path for path in state_dir.glob("*.json") if not path.name.startswith("._")):
    try:
      data = json.loads(marker.read_text(encoding="utf-8"))
    except Exception:
      continue
    if data.get("status") == "extracted" and data.get("route_id"):
      routes.append(str(data["route_id"]))
  return routes


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


def segment_number(path: Path) -> int:
  try:
    return int(path.name.rsplit("--", 1)[-1])
  except ValueError:
    return -1


def route_segments(clip_root: Path, log_id: str) -> list[SegmentInfo]:
  segments = []
  for segment_dir in sorted(clip_root.glob(f"{log_id}--*"), key=segment_number):
    video_path = segment_dir / "fcamera.hevc"
    if video_path.is_file():
      segments.append(SegmentInfo(segment_number(segment_dir), segment_dir, video_path))
  return segments


def read_log_bytes(path: Path) -> bytes:
  if path.suffix == ".zst":
    with path.open("rb") as handle:
      return zstd.ZstdDecompressor().stream_reader(handle).read()
  if path.suffix == ".bz2":
    return bz2.decompress(path.read_bytes())
  return path.read_bytes()


def round_mph_from_ms(speed_ms: float) -> int:
  if speed_ms <= 0.0:
    return 0
  mph = speed_ms * MPH_PER_MS
  rounded = int(round(mph / 5.0) * 5)
  return rounded if rounded in VALID_WEAK_LABEL_VALUES else 0


def load_segment_map_context(segment_dir: Path) -> list[MapContext]:
  log_path = segment_dir / "qlog.zst"
  if not log_path.exists():
    log_path = segment_dir / "qlog.bz2"
  if not log_path.exists():
    log_path = segment_dir / "rlog.zst"
  if not log_path.exists():
    log_path = segment_dir / "rlog.bz2"
  if not log_path.exists():
    return []

  try:
    events = list(log.Event.read_multiple_bytes(read_log_bytes(log_path)))
  except Exception:
    return []
  if not events:
    return []

  start_mono = events[0].logMonoTime
  rows: list[MapContext] = []
  last_current = 0
  last_next = 0
  last_next_distance = 0.0

  for event in events:
    event_type = event.which()
    current = 0
    next_speed = 0
    next_distance = 0.0
    if event_type == "mapdOut":
      mapd = event.mapdOut
      current = round_mph_from_ms(float(mapd.speedLimit or 0.0))
      next_speed = round_mph_from_ms(float(mapd.nextSpeedLimit or 0.0))
      next_distance = float(mapd.nextSpeedLimitDistance or 0.0)
    elif event_type == "starpilotPlan":
      plan = event.starpilotPlan
      current = round_mph_from_ms(float(plan.slcMapSpeedLimit or 0.0))
      next_speed = round_mph_from_ms(float(plan.slcNextSpeedLimit or 0.0))
      next_distance = last_next_distance
    else:
      continue

    if current == 0:
      current = last_current
    if next_speed == 0:
      next_speed = last_next
    if next_distance <= 0.0:
      next_distance = last_next_distance
    if current == 0 and next_speed == 0:
      continue

    last_current = current
    last_next = next_speed
    last_next_distance = next_distance
    rows.append(MapContext((event.logMonoTime - start_mono) / 1e9, current, next_speed, next_distance))

  return rows


def nearest_context(rows: list[MapContext], time_s: float, max_delta_s: float = 2.5) -> MapContext:
  if not rows:
    return MapContext(time_s, 0, 0, 0.0)
  best = min(rows, key=lambda row: abs(row.time_s - time_s))
  if abs(best.time_s - time_s) > max_delta_s:
    return MapContext(time_s, 0, 0, 0.0)
  return best


def transition_times(rows: list[MapContext]) -> list[float]:
  times = []
  previous = 0
  for row in rows:
    current = row.current_speed_limit_mph
    if current > 0 and previous > 0 and current != previous:
      times.append(row.time_s)
    if current > 0:
      previous = current
  return times


def sample_times(duration_s: float, regular_step_s: float, transition_centers: list[float], transition_radius_s: float, transition_step_s: float) -> list[float]:
  times = set()
  if regular_step_s > 0.0:
    sample_count = max(int(math.floor(duration_s / regular_step_s)), 0)
    for index in range(sample_count + 1):
      value = min(index * regular_step_s, max(duration_s - 0.05, 0.0))
      times.add(round(value, 3))

  if transition_radius_s > 0.0 and transition_step_s > 0.0:
    for center in transition_centers:
      offset = -transition_radius_s
      while offset <= transition_radius_s + 1e-6:
        value = center + offset
        if 0.0 <= value < duration_s:
          times.add(round(value, 3))
        offset += transition_step_s

  return sorted(times)


def iter_frames_at_times(capture: cv2.VideoCapture, fps: float, times: list[float]):
  targets: list[tuple[int, float]] = []
  previous_frame_index = -1
  for time_s in times:
    frame_index = max(int(round(time_s * fps)), 0)
    if frame_index == previous_frame_index:
      continue
    targets.append((frame_index, time_s))
    previous_frame_index = frame_index

  current_frame_index = -1
  for target_frame_index, time_s in targets:
    while current_frame_index + 1 < target_frame_index:
      if not capture.grab():
        return
      current_frame_index += 1

    ok, frame_bgr = capture.read()
    current_frame_index += 1
    if not ok or frame_bgr is None:
      return
    yield time_s, frame_bgr


def read_frame_at(capture: cv2.VideoCapture, fps: float, target_time_s: float):
  frame_index = max(int(round(target_time_s * fps)), 0)
  capture.set(cv2.CAP_PROP_POS_FRAMES, frame_index)
  ok, frame_bgr = capture.read()
  if not ok or frame_bgr is None:
    return None
  return frame_bgr


def detector_label_line(detector_class: int, x1: int, y1: int, x2: int, y2: int, image_shape: tuple[int, int, int]) -> str:
  image_h, image_w = image_shape[:2]
  x_center = ((x1 + x2) / 2) / image_w
  y_center = ((y1 + y2) / 2) / image_h
  width = (x2 - x1) / image_w
  height = (y2 - y1) / image_h
  return f"{detector_class} {x_center:.6f} {y_center:.6f} {width:.6f} {height:.6f}\n"


def fmt_read(result) -> str:
  if result is None:
    return ""
  if hasattr(result, "speed_limit_mph"):
    return f"{result.speed_limit_mph}@{result.confidence:.3f}"
  return f"{result[0]}@{result[1]:.3f}"


def dominant_read(scored: dict) -> tuple[int, int]:
  counts: dict[int, int] = {}
  for key in ("model_read", "ocr_read"):
    result = scored.get(key)
    if result is not None:
      counts[int(result[0])] = counts.get(int(result[0]), 0) + 1
  full_detection = scored.get("full_detection")
  if full_detection is not None:
    counts[int(full_detection.speed_limit_mph)] = counts.get(int(full_detection.speed_limit_mph), 0) + 1
  if not counts:
    read_result = scored.get("read_result")
    if read_result is None:
      return 0, 0
    return int(read_result[0]), 1
  value, count = max(counts.items(), key=lambda item: (item[1], item[0]))
  return value, count


def map_relation(speed_limit_mph: int, context: MapContext, next_limit_distance_m: float) -> str:
  if speed_limit_mph <= 0:
    return "no_read"
  if context.current_speed_limit_mph == speed_limit_mph:
    return "agree_current"
  if (
    context.next_speed_limit_mph == speed_limit_mph and
    0.0 < context.next_speed_limit_distance_m <= next_limit_distance_m
  ):
    return "agree_next"
  if context.current_speed_limit_mph or context.next_speed_limit_mph:
    return "map_disagreement"
  return "no_map"


def should_keep_positive(scored: dict, speed_limit_mph: int, consistent_count: int, relation: str, args: argparse.Namespace) -> bool:
  if speed_limit_mph not in VALID_WEAK_LABEL_VALUES:
    return False
  if scored.get("class_id") == 1:
    return False
  if not scored.get("is_regulatory") and scored.get("class_id") != 2:
    return False
  x1, y1, x2, y2 = scored["box"]
  if x2 - x1 < args.min_width or y2 - y1 < args.min_height:
    return False
  if float(scored["proposal_confidence"]) < args.min_proposal_confidence:
    return False
  if relation in ("agree_current", "agree_next"):
    return float(scored["score"]) >= args.positive_min_score and consistent_count >= 1
  return float(scored["score"]) >= args.no_map_min_score and consistent_count >= 2


def load_csv_by_key(path: Path, key_field: str) -> dict[str, dict[str, str]]:
  if not path.is_file():
    return {}
  with path.open("r", encoding="utf-8", newline="") as handle:
    reader = csv.DictReader(handle)
    rows = {}
    for row in reader:
      key = row.get(key_field, "")
      if key:
        rows[key] = row
    return rows


def write_csv(path: Path, fieldnames: list[str], rows: list[dict[str, object]]) -> None:
  ensure_dir(path.parent)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    for row in rows:
      writer.writerow(row)


def merge_review_rows(path: Path, new_rows: list[dict[str, object]]) -> None:
  existing = load_csv_by_key(path, "record_key")
  for row in new_rows:
    existing[str(row["record_key"])] = {key: str(value) for key, value in row.items()}
  write_csv(path, POSITIVE_FIELDNAMES, [existing[key] for key in sorted(existing)])


def merge_value_labels(path: Path, new_rows: list[dict[str, object]]) -> None:
  existing = load_csv_by_key(path, "image_path")
  for row in new_rows:
    existing[str(row["image_path"])] = {key: str(value) for key, value in row.items()}
  write_csv(path, VALUE_LABEL_FIELDS, [existing[key] for key in sorted(existing)])


def write_sample(frame_bgr, image_path: Path, label_path: Path, label_text: str, overwrite: bool, dry_run: bool) -> bool:
  if dry_run:
    return True
  if image_path.exists() and label_path.exists() and not overwrite:
    return False
  ensure_dir(image_path.parent)
  ensure_dir(label_path.parent)
  cv2.imwrite(str(image_path), frame_bgr, [cv2.IMWRITE_JPEG_QUALITY, 92])
  label_path.write_text(label_text, encoding="utf-8")
  return True


def mine_route(route_id: str, daemon: slv.SpeedLimitVisionDaemon, args: argparse.Namespace, workspace: Path, clip_root: Path, manifest_path: Path, route_state_dir: Path) -> dict[str, int | str | float]:
  route_id, dongle_id, log_id = parse_route_id(route_id)
  route_key = safe_key(route_id)
  state_path = route_state_dir / f"{route_key}.json"
  if state_path.exists() and not args.force:
    return {"route": route_id, "status": "skipped", "positives": 0, "negatives": 0, "scored": 0}

  split = route_split(route_id, args.val_route_modulo, args.val_route_remainder)
  image_dir = ensure_dir(workspace / "detector" / "images" / split)
  label_dir = ensure_dir(workspace / "detector" / "labels" / split)
  segments = route_segments(clip_root, log_id)
  if not segments:
    return {"route": route_id, "status": "missing_segments", "positives": 0, "negatives": 0, "scored": 0}

  route_rows: list[dict[str, object]] = []
  value_rows: list[dict[str, object]] = []
  positives = 0
  negatives = 0
  scored_frames = 0

  for segment in segments:
    if scored_frames >= args.max_frames_per_route:
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
      if scored_frames >= args.max_frames_per_route:
        break
      if positives >= args.max_positives_per_route and negatives >= args.max_negatives_per_route:
        break
      if frame_bgr is None:
        continue

      scored_frames += 1
      scored = score_frame(daemon, frame_bgr)
      context = nearest_context(contexts, time_s)

      if scored is None:
        if negatives >= args.max_negatives_per_route:
          continue
        sample_index = f"s{segment.segment:04d}_t{time_s:06.2f}".replace(".", "p")
        record_key = f"real_route_negative_{route_key}_{sample_index}"
        image_path = image_dir / f"{record_key}.jpg"
        label_path = label_dir / f"{record_key}.txt"
        if write_sample(frame_bgr, image_path, label_path, "", args.overwrite, args.dry_run):
          negatives += 1
          route_rows.append({
            "record_key": record_key,
            "route": route_id,
            "dongle_id": dongle_id,
            "log_id": log_id,
            "segment": segment.segment,
            "frame_time_s": f"{time_s:.3f}",
            "split": split,
            "sample_type": "negative_empty",
            "dataset_image": str(image_path),
            "dataset_label": str(label_path),
            "speed_limit_mph": "",
            "class_id": "",
            "bbox": "",
            "score": "",
            "proposal_confidence": "",
            "consistent_read_count": "",
            "model_read": "",
            "ocr_read": "",
            "full_detection": "",
            "map_current_speed_limit_mph": context.current_speed_limit_mph,
            "map_next_speed_limit_mph": context.next_speed_limit_mph,
            "map_next_speed_limit_distance_m": f"{context.next_speed_limit_distance_m:.1f}",
            "map_relation": "no_candidate",
            "source_video_path": str(segment.video_path),
          })
        continue

      speed_limit_mph, consistent_count = dominant_read(scored)
      relation = map_relation(speed_limit_mph, context, args.next_limit_distance)
      if not should_keep_positive(scored, speed_limit_mph, consistent_count, relation, args):
        continue
      if positives >= args.max_positives_per_route:
        continue

      sample_index = f"s{segment.segment:04d}_t{time_s:06.2f}".replace(".", "p")
      record_key = f"real_route_positive_{route_key}_{sample_index}"
      image_path = image_dir / f"{record_key}.jpg"
      label_path = label_dir / f"{record_key}.txt"
      x1, y1, x2, y2 = scored["box"]
      detector_class = 2 if int(scored["class_id"]) == 2 else 0
      label_text = detector_label_line(detector_class, x1, y1, x2, y2, frame_bgr.shape)
      if not write_sample(frame_bgr, image_path, label_path, label_text, args.overwrite, args.dry_run):
        continue

      positives += 1
      bbox = ",".join(str(value) for value in scored["box"])
      route_rows.append({
        "record_key": record_key,
        "route": route_id,
        "dongle_id": dongle_id,
        "log_id": log_id,
        "segment": segment.segment,
        "frame_time_s": f"{time_s:.3f}",
        "split": split,
        "sample_type": "positive_weak_map" if relation in ("agree_current", "agree_next") else "positive_weak_nomap",
        "dataset_image": str(image_path),
        "dataset_label": str(label_path),
        "speed_limit_mph": speed_limit_mph,
        "class_id": detector_class,
        "bbox": bbox,
        "score": f"{scored['score']:.4f}",
        "proposal_confidence": f"{scored['proposal_confidence']:.4f}",
        "consistent_read_count": consistent_count,
        "model_read": fmt_read(scored.get("model_read")),
        "ocr_read": fmt_read(scored.get("ocr_read")),
        "full_detection": fmt_read(scored.get("full_detection")),
        "map_current_speed_limit_mph": context.current_speed_limit_mph,
        "map_next_speed_limit_mph": context.next_speed_limit_mph,
        "map_next_speed_limit_distance_m": f"{context.next_speed_limit_distance_m:.1f}",
        "map_relation": relation,
        "source_video_path": str(segment.video_path),
      })
      value_rows.append({
        "image_path": str(image_path),
        "split": split,
        "speed_limit_mph": speed_limit_mph,
        "bbox_index": 0,
        "padding": 0.12,
        "label_path": str(label_path),
      })

    capture.release()

  if not args.dry_run:
    merge_review_rows(manifest_path, route_rows)
    merge_value_labels(workspace / "classifier" / "value_labels.csv", value_rows)
    state_path.write_text(json.dumps({
      "route": route_id,
      "status": "mined",
      "positives": positives,
      "negatives": negatives,
      "scored": scored_frames,
      "segments": len(segments),
    }, indent=2, sort_keys=True) + "\n", encoding="utf-8")

  return {
    "route": route_id,
    "status": "mined",
    "positives": positives,
    "negatives": negatives,
    "scored": scored_frames,
  }


def main() -> int:
  try:
    cv2.setLogLevel(1)
  except Exception:
    pass

  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  clip_root = args.clip_root.expanduser().resolve()
  manifest_path = args.manifest_out.expanduser().resolve() if args.manifest_out else (ensure_dir(workspace / "review") / DEFAULT_REVIEW_MANIFEST_NAME)
  route_state_dir = ensure_dir(workspace / "review" / "route_training_samples_state")
  routes = read_routes(args)
  if not routes:
    raise SystemExit("No routes to mine. Pass route ids, --routes-file, or completed bundle markers.")

  configure_models(args.models_dir)
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)

  total_positive = 0
  total_negative = 0
  total_scored = 0
  for index, route in enumerate(routes, start=1):
    result = mine_route(route, daemon, args, workspace, clip_root, manifest_path, route_state_dir)
    total_positive += int(result.get("positives", 0))
    total_negative += int(result.get("negatives", 0))
    total_scored += int(result.get("scored", 0))
    print(
      f"[{index}/{len(routes)}] {result['route']}: {result['status']} "
      f"positives={result['positives']} negatives={result['negatives']} scored={result['scored']}",
      flush=True,
    )

  print(
    f"Route mining complete: routes={len(routes)} positives={total_positive} negatives={total_negative} scored={total_scored}",
    flush=True,
  )
  print(f"Review manifest: {manifest_path}", flush=True)
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
