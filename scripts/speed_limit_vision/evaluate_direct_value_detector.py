#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import time

from collections import Counter, defaultdict
from pathlib import Path

import cv2
import numpy as np

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import source_video_fps  # type: ignore  # noqa: TID251
  from evaluate_runtime_manifest import expected_value, first_present, is_negative, load_rows  # type: ignore
  from evaluate_reviewed_route_events import load_cases  # type: ignore
  from replay_route_runtime import RouteReplayDaemon  # type: ignore
else:
  from .common import source_video_fps
  from .evaluate_runtime_manifest import expected_value, first_present, is_negative, load_rows
  from .evaluate_reviewed_route_events import load_cases
  from .replay_route_runtime import RouteReplayDaemon


SPEED_VALUES = (15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75)


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Evaluate a one-stage direct speed-value detector.")
  parser.add_argument("--detector", type=Path, required=True)
  parser.add_argument("--manifest", type=Path, help="Static reviewed-frame manifest.")
  parser.add_argument("--queue", type=Path, help="Reviewed queue for cadence-aware route replay.")
  parser.add_argument("--labels", type=Path)
  parser.add_argument("--output-csv", type=Path)
  parser.add_argument("--confidence", type=float, default=0.06)
  parser.add_argument("--advisory-positive", action="store_true")
  parser.add_argument("--include-uncertain", action="store_true")
  parser.add_argument("--positive-only", action="store_true")
  parser.add_argument("--max-cases", type=int, default=0)
  parser.add_argument("--window-before", type=float, default=4.0)
  parser.add_argument("--window-after", type=float, default=3.0)
  parser.add_argument("--dedupe-seconds", type=float, default=3.0)
  parser.add_argument("--measured-inference-seconds", type=float, default=0.44)
  args = parser.parse_args()
  if bool(args.manifest) == bool(args.queue):
    parser.error("exactly one of --manifest or --queue is required")
  return args


class DirectValueDetector:
  def __init__(self, model_path: Path, confidence: float):
    self.model_path = model_path.expanduser().resolve()
    self.confidence = confidence
    self.input_size = slv.SpeedLimitVisionDaemon._read_onnx_square_input_size(self.model_path, 256)
    self.net = cv2.dnn.readNetFromONNX(str(self.model_path))
    self.net.setPreferableBackend(cv2.dnn.DNN_BACKEND_OPENCV)
    self.net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)
    self.last_forward_seconds = 0.0

  def proposals(self, frame_bgr: np.ndarray) -> list[tuple[float, int, tuple[int, int, int, int]]]:
    frame_height, frame_width = frame_bgr.shape[:2]
    left_ratio, top_ratio, right_ratio, bottom_ratio = slv.ROI_WINDOWS[-1]["bounds"]
    origin_x = int(frame_width * left_ratio)
    origin_y = int(frame_height * top_ratio)
    right = int(frame_width * right_ratio)
    bottom = int(frame_height * bottom_ratio)
    region = frame_bgr[origin_y:bottom, origin_x:right]
    if region.size == 0:
      return []
    shape = (self.input_size, self.input_size)
    letterboxed, ratio, pad_width, pad_height = slv.SpeedLimitVisionDaemon._letterbox(region, shape=shape)
    blob = cv2.dnn.blobFromImage(letterboxed, scalefactor=1 / 255.0, size=shape, swapRB=True, crop=False)
    self.net.setInput(blob)
    started_at = time.monotonic()
    predictions = np.squeeze(self.net.forward())
    self.last_forward_seconds = time.monotonic() - started_at
    if predictions.ndim != 2:
      return []
    if predictions.shape[0] < predictions.shape[1]:
      predictions = predictions.T

    region_height, region_width = region.shape[:2]
    proposals: list[tuple[float, int, tuple[int, int, int, int]]] = []
    for prediction in predictions:
      class_scores = prediction[4:]
      if class_scores.size not in (len(SPEED_VALUES) - 1, len(SPEED_VALUES)):
        continue
      class_id = int(np.argmax(class_scores))
      confidence = float(class_scores[class_id])
      if confidence < self.confidence:
        continue
      center_x, center_y, width, height = prediction[:4]
      x1 = max(int((center_x - width / 2 - pad_width) / ratio), 0)
      y1 = max(int((center_y - height / 2 - pad_height) / ratio), 0)
      x2 = min(int((center_x + width / 2 - pad_width) / ratio), region_width)
      y2 = min(int((center_y + height / 2 - pad_height) / ratio), region_height)
      if x2 <= x1 or y2 <= y1:
        continue
      bbox = (x1 + origin_x, y1 + origin_y, x2 + origin_x, y2 + origin_y)
      box_width = bbox[2] - bbox[0]
      box_height = bbox[3] - bbox[1]
      if box_width < slv.MODEL_PROPOSAL_MIN_WIDTH or box_height < slv.MODEL_PROPOSAL_MIN_HEIGHT:
        continue
      if box_width * box_height > frame_width * frame_height * slv.MODEL_PROPOSAL_MAX_AREA_RATIO:
        continue
      if (bbox[0] + bbox[2]) / 2 < frame_width * slv.MODEL_PROPOSAL_MIN_X_RATIO:
        continue
      if bbox[1] > frame_height * slv.MODEL_PROPOSAL_MAX_Y_RATIO:
        continue
      proposals.append((confidence, class_id, bbox))
    return sorted(proposals, reverse=True)[:slv.MODEL_PROPOSAL_MAX_COUNT]

  def detect(self, frame_bgr: np.ndarray) -> slv.Detection | None:
    proposals = self.proposals(frame_bgr)
    if not proposals:
      return None
    confidence, class_id, _bbox = proposals[0]
    return slv.Detection(SPEED_VALUES[class_id], min(confidence, 0.95), confidence >= 0.80)


class DirectRouteReplayDaemon(RouteReplayDaemon):
  def __init__(self, detector: DirectValueDetector, measured_inference_seconds: float):
    super().__init__(runtime_context=None, measured_inference_seconds=measured_inference_seconds)
    self.direct_detector = detector

  def _detect_sign(self, frame_bgr):
    return self._publishable_detection(self.direct_detector.detect(frame_bgr))


def evaluate_manifest(args: argparse.Namespace, detector: DirectValueDetector) -> dict[str, object]:
  rows = load_rows(args.manifest.expanduser().resolve(), None)
  if not args.include_uncertain:
    rows = [row for row in rows if row.get("sample_type") != "uncertain_positive" and row.get("review_status") != "uncertain"]
  counts: Counter[str] = Counter()
  by_speed: dict[int, Counter[str]] = defaultdict(Counter)
  output_rows: list[dict[str, object]] = []
  for row in rows:
    image_text = first_present(row, ("dataset_image", "frame_path", "source_frame", "image_path"))
    frame_bgr = cv2.imread(str(Path(image_text).expanduser())) if image_text else None
    if frame_bgr is None:
      counts["unreadable"] += 1
      continue
    detection = detector.detect(frame_bgr)
    predicted = detection.speed_limit_mph if detection else 0
    expected = expected_value(row)
    advisory_positive = args.advisory_positive and row.get("review_sign_type", "").strip().lower() == "advisory"
    negative = False if advisory_positive else is_negative(row)
    if negative:
      counts.update(negative=1, negative_fp=int(bool(predicted)))
    else:
      counts.update(positive=1, positive_any=int(bool(predicted)), positive_exact=int(predicted == expected))
      if expected is not None:
        by_speed[expected].update(total=1, exact=int(predicted == expected), any=int(bool(predicted)))
    output_rows.append({
      "record_key": row.get("record_key", ""),
      "expected_speed_limit_mph": expected or "",
      "predicted_speed_limit_mph": predicted or "",
      "confidence": detection.confidence if detection else "",
      "negative": negative,
      "image_path": image_text,
    })
  if args.output_csv:
    args.output_csv.parent.mkdir(parents=True, exist_ok=True)
    with args.output_csv.open("w", encoding="utf-8", newline="") as output_file:
      writer = csv.DictWriter(output_file, fieldnames=output_rows[0].keys() if output_rows else ("record_key",))
      writer.writeheader()
      writer.writerows(output_rows)
  return {"counts": dict(counts), "by_speed": {str(speed): dict(values) for speed, values in sorted(by_speed.items())}}


def replay_video_cases(cases, detector: DirectValueDetector, args: argparse.Namespace):
  daemons = {case.record_key: DirectRouteReplayDaemon(detector, args.measured_inference_seconds) for case in cases}
  capture = cv2.VideoCapture(str(cases[0].source_video_path))
  fps = source_video_fps(cases[0].source_video_path, capture.get(cv2.CAP_PROP_FPS))
  windows = {
    case.record_key: (max(case.frame_time_s - args.window_before, 0.0), case.frame_time_s + args.window_after)
    for case in cases
  }
  first_frame = max(int(min(window[0] for window in windows.values()) * fps), 0)
  end_frame = max(int(max(window[1] for window in windows.values()) * fps), first_frame)
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
  return {
    case.record_key: (
      [int(event["candidateSpeedLimitMph"]) for event in daemons[case.record_key].events if event["event"] == "candidate"],
      [int(event["speedLimitMph"]) for event in daemons[case.record_key].events if event["event"] == "publish"],
    )
    for case in cases
  }


def evaluate_queue(args: argparse.Namespace, detector: DirectValueDetector) -> dict[str, object]:
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  cases = load_cases(queue_path, labels_path, args.dedupe_seconds)
  if args.positive_only:
    cases = [case for case in cases if not case.negative]
  if args.max_cases > 0:
    cases = cases[:args.max_cases]
  cases_by_video = defaultdict(list)
  for case in cases:
    cases_by_video[case.source_video_path].append(case)
  results = {}
  for index, video_cases in enumerate(cases_by_video.values(), start=1):
    results.update(replay_video_cases(video_cases, detector, args))
    if index % 10 == 0:
      print(f"Replayed {index}/{len(cases_by_video)} video segments", flush=True)
  counts: Counter[str] = Counter()
  by_speed: dict[int, Counter[str]] = defaultdict(Counter)
  for case in cases:
    candidates, publishes = results.get(case.record_key, ([], []))
    if case.negative:
      counts.update(negative=1, candidate_fp=int(bool(candidates)), publish_fp=int(bool(publishes)))
    else:
      candidate_hit = case.expected_speed_limit_mph in candidates
      publish_hit = case.expected_speed_limit_mph in publishes
      counts.update(positive=1, candidate_hit=int(candidate_hit), publish_hit=int(publish_hit))
      by_speed[case.expected_speed_limit_mph].update(total=1, candidate_hit=int(candidate_hit), publish_hit=int(publish_hit))
  return {"counts": dict(counts), "by_speed": {str(speed): dict(values) for speed, values in sorted(by_speed.items())}}


def main() -> int:
  args = parse_args()
  detector = DirectValueDetector(args.detector, args.confidence)
  result = evaluate_manifest(args, detector) if args.manifest else evaluate_queue(args, detector)
  print(json.dumps(result, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
