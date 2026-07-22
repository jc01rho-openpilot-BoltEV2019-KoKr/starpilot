#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib
import math

from collections import deque
from dataclasses import dataclass
from pathlib import Path

import cv2
import numpy as np

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import source_video_fps  # type: ignore  # noqa: TID251
  from import_manual_review_queue import merged_review_rows, parse_speed  # type: ignore
  from replay_route_runtime import configure_models  # type: ignore
else:
  from .common import source_video_fps
  from .import_manual_review_queue import merged_review_rows, parse_speed
  from .replay_route_runtime import configure_models


POSITIVE_STATUSES = frozenset(("accepted", "corrected"))


@dataclass(frozen=True)
class TrackCase:
  source_row: dict[str, str]
  track_key: str
  video_path: Path
  frame_time_s: float
  expected_speed_mph: int
  anchor_bbox: tuple[int, int, int, int]
  anchor_bbox_source: str


@dataclass(frozen=True)
class TrackSample:
  time_s: float
  bbox: tuple[int, int, int, int]
  crop_bbox: tuple[int, int, int, int]
  detector_confidence: float
  tracking_confidence: float
  predicted_speed_mph: int
  read_confidence: float
  sharpness: float
  brightness: float
  area_ratio_to_anchor: float
  score: float
  frame_jpeg: bytes
  crop_jpeg: bytes


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Track human-reviewed signs into nearby route frames.")
  parser.add_argument("--queue", type=Path, required=True, help="Reviewed manual_review_queue.csv.")
  parser.add_argument("--labels", type=Path, help="Defaults to manual_review_labels.csv beside the queue.")
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"))
  parser.add_argument("--output-dir", type=Path, required=True)
  parser.add_argument("--window-before", type=float, default=0.0, help="Seconds to track backward before the reviewed frame.")
  parser.add_argument("--window-after", type=float, default=2.5, help="Seconds to track after the reviewed anchor frame.")
  parser.add_argument("--sample-interval", type=float, default=0.10, help="Minimum spacing between ranked samples.")
  parser.add_argument("--detector-interval", type=float, default=0.20, help="How often to snap optical flow to detector proposals.")
  parser.add_argument("--max-samples-per-track", type=int, default=4)
  parser.add_argument("--max-samples-before-track", type=int, default=4)
  parser.add_argument("--dedupe-seconds", type=float, default=3.0)
  parser.add_argument("--min-area-growth", type=float, default=0.85)
  parser.add_argument("--min-backward-area-ratio", type=float, default=0.20)
  parser.add_argument("--limit", type=int, default=0)
  return parser.parse_args()


def parse_bbox(value: str) -> tuple[int, int, int, int] | None:
  try:
    values = tuple(int(round(float(part.strip()))) for part in value.split(","))
  except ValueError:
    return None
  if len(values) != 4:
    return None
  x1, y1, x2, y2 = values
  return values if x2 > x1 and y2 > y1 else None


def bbox_area(bbox: tuple[int, int, int, int]) -> int:
  x1, y1, x2, y2 = bbox
  return max(x2 - x1, 0) * max(y2 - y1, 0)


def bbox_iou(first: tuple[int, int, int, int], second: tuple[int, int, int, int]) -> float:
  ax1, ay1, ax2, ay2 = first
  bx1, by1, bx2, by2 = second
  intersection = max(min(ax2, bx2) - max(ax1, bx1), 0) * max(min(ay2, by2) - max(ay1, by1), 0)
  union = bbox_area(first) + bbox_area(second) - intersection
  return intersection / union if union > 0 else 0.0


def clamp_bbox(bbox: tuple[float, float, float, float], width: int, height: int) -> tuple[int, int, int, int] | None:
  x1, y1, x2, y2 = bbox
  result = (
    max(min(int(round(x1)), width - 1), 0),
    max(min(int(round(y1)), height - 1), 0),
    max(min(int(round(x2)), width), 0),
    max(min(int(round(y2)), height), 0),
  )
  return result if bbox_area(result) > 0 else None


def expanded_bbox(bbox: tuple[int, int, int, int], width: int, height: int, padding: float = 0.12) -> tuple[int, int, int, int]:
  x1, y1, x2, y2 = bbox
  box_width = x2 - x1
  box_height = y2 - y1
  return (
    max(int(x1 - box_width * padding), 0),
    max(int(y1 - box_height * padding), 0),
    min(int(x2 + box_width * padding), width),
    min(int(y2 + box_height * padding), height),
  )


def feature_points(gray: np.ndarray, bbox: tuple[int, int, int, int]) -> np.ndarray | None:
  mask = np.zeros_like(gray)
  x1, y1, x2, y2 = bbox
  inset_x = max((x2 - x1) // 12, 1)
  inset_y = max((y2 - y1) // 12, 1)
  mask[y1 + inset_y:y2 - inset_y, x1 + inset_x:x2 - inset_x] = 255
  return cv2.goodFeaturesToTrack(gray, mask=mask, maxCorners=60, qualityLevel=0.01, minDistance=3, blockSize=5)


def flow_bbox(
  previous_gray: np.ndarray,
  current_gray: np.ndarray,
  bbox: tuple[int, int, int, int],
  points: np.ndarray | None,
) -> tuple[tuple[int, int, int, int] | None, np.ndarray | None]:
  if points is None or len(points) < 6:
    points = feature_points(previous_gray, bbox)
  if points is None or len(points) < 4:
    return None, None
  next_points, status, errors = cv2.calcOpticalFlowPyrLK(
    previous_gray,
    current_gray,
    points,
    None,
    winSize=(25, 25),
    maxLevel=3,
    criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 20, 0.03),
  )
  if next_points is None or status is None:
    return None, None
  good = status.reshape(-1).astype(bool)
  if errors is not None:
    good &= errors.reshape(-1) < 35.0
  old = points.reshape(-1, 2)[good]
  new = next_points.reshape(-1, 2)[good]
  if len(old) < 4:
    return None, None
  transform, inliers = cv2.estimateAffinePartial2D(old, new, method=cv2.RANSAC, ransacReprojThreshold=3.0)
  if transform is None or inliers is None or int(inliers.sum()) < 4:
    return None, None
  scale = math.hypot(float(transform[0, 0]), float(transform[0, 1]))
  if not 0.88 <= scale <= 1.18:
    return None, None
  x1, y1, x2, y2 = bbox
  corners = np.float32(((x1, y1), (x2, y1), (x2, y2), (x1, y2))).reshape(-1, 1, 2)
  moved = cv2.transform(corners, transform).reshape(-1, 2)
  tracked = clamp_bbox(
    (float(moved[:, 0].min()), float(moved[:, 1].min()), float(moved[:, 0].max()), float(moved[:, 1].max())),
    current_gray.shape[1],
    current_gray.shape[0],
  )
  if tracked is None:
    return None, None
  inlier_points = new[inliers.reshape(-1).astype(bool)].reshape(-1, 1, 2)
  return tracked, inlier_points


def matching_proposal(daemon: slv.SpeedLimitVisionDaemon, frame: np.ndarray, tracked_bbox: tuple[int, int, int, int]):
  tx1, ty1, tx2, ty2 = tracked_bbox
  track_center = np.array(((tx1 + tx2) / 2, (ty1 + ty2) / 2))
  track_diagonal = max(math.hypot(tx2 - tx1, ty2 - ty1), 1.0)
  best = None
  best_score = 0.0
  for confidence, _class_id, bbox in daemon._collect_detector_classifier_proposals(frame):
    x1, y1, x2, y2 = bbox
    center = np.array(((x1 + x2) / 2, (y1 + y2) / 2))
    distance_ratio = float(np.linalg.norm(center - track_center)) / track_diagonal
    overlap = bbox_iou(tracked_bbox, bbox)
    if overlap < 0.06 and distance_ratio > 0.85:
      continue
    score = overlap * 2.0 + max(1.0 - distance_ratio, 0.0) + float(confidence) * 0.25
    if score > best_score:
      best_score = score
      best = float(confidence), bbox
  return best


def encode_jpeg(image: np.ndarray, quality: int = 90) -> bytes:
  ok, encoded = cv2.imencode(".jpg", image, (cv2.IMWRITE_JPEG_QUALITY, quality))
  if not ok:
    raise RuntimeError("Could not encode tracked frame")
  return encoded.tobytes()


def ranked_samples(candidates: list[TrackSample], limit: int, sample_interval: float) -> list[TrackSample]:
  selected: list[TrackSample] = []
  for candidate in sorted(candidates, key=lambda item: item.score, reverse=True):
    if any(abs(candidate.time_s - kept.time_s) < max(sample_interval * 1.5, 0.12) for kept in selected):
      continue
    selected.append(candidate)
    if len(selected) >= limit:
      break
  return selected


def make_sample(
  case: TrackCase,
  daemon: slv.SpeedLimitVisionDaemon,
  frame: np.ndarray,
  bbox: tuple[int, int, int, int],
  detector_confidence: float,
  tracking_confidence: float,
  anchor_area: int,
  time_s: float,
  time_distance_s: float,
  backward: bool,
) -> TrackSample | None:
  height, width = frame.shape[:2]
  crop_box = expanded_bbox(bbox, width, height)
  x1, y1, x2, y2 = crop_box
  crop = frame[y1:y2, x1:x2]
  if crop.size == 0:
    return None
  read = daemon._classify_speed_limit_from_model(crop)
  predicted_speed = int(read[0]) if read is not None else 0
  read_confidence = float(read[1]) if read is not None else 0.0
  gray_crop = cv2.cvtColor(crop, cv2.COLOR_BGR2GRAY)
  sharpness = float(cv2.Laplacian(gray_crop, cv2.CV_64F).var())
  brightness = float(gray_crop.mean())
  growth = bbox_area(bbox) / anchor_area
  growth_score = math.log2(max(growth, 0.25)) * (0.15 if backward else 0.55)
  exact_bonus = read_confidence * 2.0 if predicted_speed == case.expected_speed_mph else 0.0
  wrong_penalty = read_confidence * 1.5 if predicted_speed and predicted_speed != case.expected_speed_mph else 0.0
  score = (
    growth_score +
    min(sharpness / 180.0, 1.0) * 0.35 +
    detector_confidence * 0.45 +
    tracking_confidence * 0.20 +
    exact_bonus - wrong_penalty +
    min(time_distance_s, 1.5) * (0.04 if backward else 0.08)
  )
  return TrackSample(
    time_s=time_s,
    bbox=bbox,
    crop_bbox=crop_box,
    detector_confidence=detector_confidence,
    tracking_confidence=tracking_confidence,
    predicted_speed_mph=predicted_speed,
    read_confidence=read_confidence,
    sharpness=sharpness,
    brightness=brightness,
    area_ratio_to_anchor=growth,
    score=score,
    frame_jpeg=encode_jpeg(frame),
    crop_jpeg=encode_jpeg(crop, 95),
  )


def load_cases(queue_path: Path, labels_path: Path, dedupe_seconds: float) -> tuple[list[TrackCase], list[str]]:
  with queue_path.open(encoding="utf-8", newline="") as queue_file:
    fieldnames = list(csv.DictReader(queue_file).fieldnames or ())
  rows = merged_review_rows(queue_path, labels_path)
  seen: set[tuple[str, int, int, int]] = set()
  cases: list[TrackCase] = []
  for row in rows:
    if row.get("review_status") not in POSITIVE_STATUSES:
      continue
    speed = parse_speed(row.get("review_speed_limit_mph", ""))
    reviewed_bbox = parse_bbox(row.get("review_bbox", ""))
    bbox = reviewed_bbox or parse_bbox(row.get("bbox", ""))
    try:
      frame_time_s = float(row.get("frame_time_s", ""))
      segment = int(row.get("segment", ""))
    except ValueError:
      continue
    video_path = Path(row.get("source_video_path", "")).expanduser()
    if not speed or bbox is None or not video_path.is_file():
      continue
    bucket = int(frame_time_s / max(dedupe_seconds, 0.1))
    dedupe_key = (row.get("route", ""), segment, bucket, speed)
    if dedupe_key in seen:
      continue
    seen.add(dedupe_key)
    digest = hashlib.sha1(f"{row.get('record_key')}:{speed}".encode()).hexdigest()[:16]
    cases.append(TrackCase(
      row,
      f"sign_track_{digest}",
      video_path.resolve(),
      frame_time_s,
      speed,
      bbox,
      "review_bbox" if reviewed_bbox is not None else "bbox",
    ))
  return cases, fieldnames


def mine_backward_samples(
  case: TrackCase,
  daemon: slv.SpeedLimitVisionDaemon,
  args: argparse.Namespace,
  frames: list[tuple[int, np.ndarray]],
  anchor_frame: np.ndarray,
  anchor_frame_index: int,
  fps: float,
  anchor_bbox: tuple[int, int, int, int],
  anchor_area: int,
) -> list[TrackSample]:
  if not frames or args.max_samples_before_track <= 0:
    return []
  previous_gray = cv2.cvtColor(anchor_frame, cv2.COLOR_BGR2GRAY)
  bbox = anchor_bbox
  points = feature_points(previous_gray, bbox)
  next_sample_elapsed = args.sample_interval
  next_detector_elapsed = 0.0
  candidates: list[TrackSample] = []
  height, width = anchor_frame.shape[:2]

  for frame_index, frame in reversed(frames):
    elapsed = (anchor_frame_index - frame_index) / fps
    current_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    bbox, points = flow_bbox(previous_gray, current_gray, bbox, points)
    previous_gray = current_gray
    if bbox is None:
      break
    x1, y1, x2, y2 = bbox
    growth = bbox_area(bbox) / anchor_area
    if growth < args.min_backward_area_ratio or growth > 1.35 or x1 <= 0 or y1 <= 0 or x2 >= width or y2 >= height:
      break
    detector_confidence = 0.0
    if elapsed + 1e-6 >= next_detector_elapsed:
      proposal = matching_proposal(daemon, frame, bbox)
      next_detector_elapsed = elapsed + args.detector_interval
      if proposal is not None:
        detector_confidence, proposal_bbox = proposal
        bbox = proposal_bbox
        points = feature_points(previous_gray, bbox)
        growth = bbox_area(bbox) / anchor_area
    if elapsed + 1e-6 < next_sample_elapsed:
      continue
    next_sample_elapsed = elapsed + args.sample_interval
    tracking_confidence = min(len(points) / 12.0, 1.0) if points is not None else 0.0
    sample = make_sample(
      case,
      daemon,
      frame,
      bbox,
      detector_confidence,
      tracking_confidence,
      anchor_area,
      frame_index / fps,
      elapsed,
      backward=True,
    )
    if sample is not None:
      candidates.append(sample)
  return ranked_samples(candidates, args.max_samples_before_track, args.sample_interval)


def mine_case(case: TrackCase, daemon: slv.SpeedLimitVisionDaemon, args: argparse.Namespace) -> list[TrackSample]:
  capture = cv2.VideoCapture(str(case.video_path))
  fps = source_video_fps(case.video_path, capture.get(cv2.CAP_PROP_FPS))
  anchor_frame_index = max(int(round(case.frame_time_s * fps)), 0)
  before_frame_count = max(int(round(args.window_before * fps)), 0)
  earlier_frames: deque[tuple[int, np.ndarray]] = deque(maxlen=before_frame_count)
  # Raw comma HEVC streams have no seek index. CAP_PROP_POS_FRAMES silently
  # returns frame zero, so advance sequentially to preserve timestamp alignment.
  for frame_index in range(anchor_frame_index):
    if before_frame_count and frame_index >= anchor_frame_index - before_frame_count:
      ok, frame = capture.read()
      if not ok or frame is None:
        capture.release()
        return []
      earlier_frames.append((frame_index, frame))
    elif not capture.grab():
      capture.release()
      return []
  ok, anchor_frame = capture.read()
  if not ok or anchor_frame is None:
    capture.release()
    return []

  height, width = anchor_frame.shape[:2]
  bbox = clamp_bbox(case.anchor_bbox, width, height)
  if bbox is None:
    capture.release()
    return []
  anchor_area = max(bbox_area(bbox), 1)
  backward_samples = mine_backward_samples(
    case,
    daemon,
    args,
    list(earlier_frames),
    anchor_frame,
    anchor_frame_index,
    fps,
    bbox,
    anchor_area,
  )
  previous_gray = cv2.cvtColor(anchor_frame, cv2.COLOR_BGR2GRAY)
  points = feature_points(previous_gray, bbox)
  next_sample_at = case.frame_time_s
  next_detector_at = case.frame_time_s
  end_frame_index = anchor_frame_index + int(round(args.window_after * fps))
  candidates: list[TrackSample] = []

  current_frame = anchor_frame
  current_index = anchor_frame_index
  while current_index <= end_frame_index:
    time_s = current_index / fps
    if current_index > anchor_frame_index:
      current_gray = cv2.cvtColor(current_frame, cv2.COLOR_BGR2GRAY)
      bbox, points = flow_bbox(previous_gray, current_gray, bbox, points)
      previous_gray = current_gray
      if bbox is None:
        break
      x1, y1, x2, y2 = bbox
      if bbox_area(bbox) > anchor_area * 12.0 or x1 <= 0 or y1 <= 0 or x2 >= width or y2 >= height:
        break
    detector_confidence = 0.0
    if time_s + 1e-6 >= next_detector_at:
      proposal = matching_proposal(daemon, current_frame, bbox)
      next_detector_at = time_s + args.detector_interval
      if proposal is not None:
        detector_confidence, proposal_bbox = proposal
        bbox = proposal_bbox
        points = feature_points(previous_gray, bbox)
    if time_s + 1e-6 >= next_sample_at:
      next_sample_at = time_s + args.sample_interval
      growth = bbox_area(bbox) / anchor_area
      if growth >= args.min_area_growth:
        tracking_confidence = min(len(points) / 12.0, 1.0) if points is not None else 0.0
        sample = make_sample(
          case,
          daemon,
          current_frame,
          bbox,
          detector_confidence,
          tracking_confidence,
          anchor_area,
          time_s,
          max(time_s - case.frame_time_s, 0.0),
          backward=False,
        )
        if sample is not None:
          candidates.append(sample)
    if current_index >= end_frame_index:
      break
    ok, current_frame = capture.read()
    if not ok:
      break
    current_index += 1
  capture.release()

  selected = ranked_samples(candidates, args.max_samples_per_track, args.sample_interval)
  return [*backward_samples, *selected]


def main() -> int:
  args = parse_args()
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  output_dir = args.output_dir.expanduser().resolve()
  frame_dir = output_dir / "frames"
  crop_dir = output_dir / "crops"
  frame_dir.mkdir(parents=True, exist_ok=True)
  crop_dir.mkdir(parents=True, exist_ok=True)
  configure_models(args.models_dir.expanduser().resolve())
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  cases, source_fieldnames = load_cases(queue_path, labels_path, args.dedupe_seconds)
  if args.limit > 0:
    cases = cases[:args.limit]

  queue_rows: list[dict[str, str]] = []
  sample_rows: list[dict[str, str]] = []
  for index, case in enumerate(cases, start=1):
    samples = mine_case(case, daemon, args)
    if not samples:
      continue
    for rank, sample in enumerate(samples, start=1):
      stem = f"{case.track_key}_r{rank:02d}_t{sample.time_s:07.3f}".replace(".", "p")
      frame_path = frame_dir / f"{stem}.jpg"
      crop_path = crop_dir / f"{stem}_crop.jpg"
      frame_path.write_bytes(sample.frame_jpeg)
      crop_path.write_bytes(sample.crop_jpeg)
      sample_rows.append({
        "track_key": case.track_key,
        "source_record_key": case.source_row.get("record_key", ""),
        "route": case.source_row.get("route", ""),
        "segment": case.source_row.get("segment", ""),
        "frame_time_s": f"{sample.time_s:.3f}",
        "expected_speed_limit_mph": str(case.expected_speed_mph),
        "review_sign_type": case.source_row.get("review_sign_type", ""),
        "frame_path": str(frame_path),
        "crop_path": str(crop_path),
        "source_video_path": str(case.video_path),
        "anchor_bbox_source": case.anchor_bbox_source,
        "bbox": ",".join(str(value) for value in sample.bbox),
        "crop_bbox": ",".join(str(value) for value in sample.crop_bbox),
        "detector_confidence": f"{sample.detector_confidence:.6f}",
        "tracking_confidence": f"{sample.tracking_confidence:.6f}",
        "predicted_speed_limit_mph": str(sample.predicted_speed_mph or ""),
        "read_confidence": f"{sample.read_confidence:.6f}",
        "sharpness": f"{sample.sharpness:.3f}",
        "brightness": f"{sample.brightness:.3f}",
        "area_ratio_to_anchor": f"{sample.area_ratio_to_anchor:.4f}",
        "track_score": f"{sample.score:.6f}",
        "rank": str(rank),
      })
      if rank == 1:
        review_row = dict(case.source_row)
        review_row.update({
          "record_key": case.track_key,
          "frame_time_s": f"{sample.time_s:.3f}",
          "frame_path": str(frame_path),
          "crop_path": str(crop_path),
          "source_video_path": str(case.video_path),
          "bbox": ",".join(str(value) for value in sample.bbox),
          "crop_bbox": ",".join(str(value) for value in sample.crop_bbox),
          "candidate_speed_limit_mph": str(case.expected_speed_mph),
          "candidate_confidence": f"{sample.read_confidence:.6f}",
          "model_read": str(sample.predicted_speed_mph or ""),
          "review_status": "",
          "review_speed_limit_mph": "",
          "review_sign_type": case.source_row.get("review_sign_type", "regulatory"),
          "review_bbox": "",
          "review_ignore_reason": "",
          "review_notes": f"tracked from {case.source_row.get('record_key', '')}",
          "source_record_key": case.source_row.get("record_key", ""),
          "source_review_status": case.source_row.get("review_status", ""),
          "source_review_speed_limit_mph": str(case.expected_speed_mph),
        })
        queue_rows.append(review_row)
    if index % 10 == 0:
      print(f"Tracked {index}/{len(cases)} reviewed signs; review rows={len(queue_rows)} samples={len(sample_rows)}", flush=True)

  queue_fieldnames = list(source_fieldnames)
  for extra in ("source_record_key",):
    if extra not in queue_fieldnames:
      queue_fieldnames.append(extra)
  with (output_dir / "manual_review_queue.csv").open("w", encoding="utf-8", newline="") as output_file:
    writer = csv.DictWriter(output_file, fieldnames=queue_fieldnames, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(queue_rows)
  sample_fieldnames = tuple(sample_rows[0]) if sample_rows else (
    "track_key", "source_record_key", "route", "segment", "frame_time_s", "expected_speed_limit_mph",
  )
  with (output_dir / "track_samples.csv").open("w", encoding="utf-8", newline="") as output_file:
    writer = csv.DictWriter(output_file, fieldnames=sample_fieldnames)
    writer.writeheader()
    writer.writerows(sample_rows)
  print(f"Track mining complete: cases={len(cases)} review_rows={len(queue_rows)} samples={len(sample_rows)} output={output_dir}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
