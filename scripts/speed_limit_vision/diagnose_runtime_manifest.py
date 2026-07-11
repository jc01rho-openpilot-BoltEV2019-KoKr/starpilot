#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv

from collections import Counter
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Diagnose speed-limit runtime failures at detector proposal/read level.")
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"))
  parser.add_argument("--manifest", type=Path, required=True)
  parser.add_argument("--output-rows", type=Path, required=True)
  parser.add_argument("--output-proposals", type=Path, required=True)
  parser.add_argument("--only-errors", action="store_true", help="Only write proposal rows for non-exact positives and false positives.")
  parser.add_argument("--include-uncertain", action="store_true")
  parser.add_argument("--max-proposals", type=int, default=0, help="Optional proposal row cap per image.")
  return parser.parse_args()


def first_present(row: dict[str, str], keys: tuple[str, ...]) -> str:
  for key in keys:
    value = row.get(key, "").strip()
    if value:
      return value
  return ""


def int_value(text: str) -> int | None:
  text = text.strip()
  if not text:
    return None
  try:
    return int(float(text))
  except ValueError:
    return None


def expected_value(row: dict[str, str]) -> int | None:
  value = int_value(first_present(row, ("speed_limit_mph", "review_speed_limit_mph", "expected_speed_limit_mph", "dominant_value")))
  if value is not None:
    return value

  for key in ("full_detection", "model_read", "ocr_read"):
    read_text = row.get(key, "").strip()
    if "@" not in read_text:
      continue
    value = int_value(read_text.split("@", 1)[0])
    if value is not None:
      return value
  return None


def is_negative(row: dict[str, str]) -> bool:
  sample_type = row.get("sample_type", "").lower()
  if "negative" in sample_type:
    return True
  return expected_value(row) is None


def load_rows(manifest_path: Path, include_uncertain: bool) -> list[dict[str, str]]:
  with manifest_path.open("r", encoding="utf-8", newline="") as manifest_file:
    rows = list(csv.DictReader(manifest_file))
  if include_uncertain:
    return rows
  return [
    row for row in rows
    if row.get("sample_type", "") != "uncertain_positive" and row.get("review_status", "") != "uncertain"
  ]


def configure_models(models_dir: Path) -> None:
  models_dir = models_dir.expanduser().resolve()
  slv.US_DETECTOR_MODEL_PATH = models_dir / "speed_limit_us_detector.onnx"
  slv.US_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_value_classifier.onnx"
  slv.US_REJECT_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_reject_classifier.onnx"


def classify_row(expected: int | None, negative: bool, predicted: int | None, proposal_count: int, expected_read_count: int) -> str:
  if negative:
    return "false_positive" if predicted is not None else "true_negative"
  if predicted == expected:
    return "exact"
  if predicted is not None:
    return "wrong_value_expected_read_seen" if expected_read_count else "wrong_value_no_expected_read"
  if proposal_count <= 0:
    return "miss_no_detector_proposal"
  if expected_read_count > 0:
    return "miss_expected_read_seen"
  return "miss_no_expected_read"


def crop_reads(daemon: slv.SpeedLimitVisionDaemon, frame_bgr, bbox: tuple[int, int, int, int]):
  frame_height, frame_width = frame_bgr.shape[:2]
  x1, y1, x2, y2 = bbox
  box_width = x2 - x1
  box_height = y2 - y1
  for expansion_index, (expand_left, expand_top, expand_right, expand_bottom, expansion_weight) in enumerate(slv.DETECTOR_CLASSIFIER_EXPANSIONS):
    expanded_x1 = max(int(x1 - box_width * expand_left), 0)
    expanded_y1 = max(int(y1 - box_height * expand_top), 0)
    expanded_x2 = min(int(x2 + box_width * expand_right), frame_width)
    expanded_y2 = min(int(y2 + box_height * expand_bottom), frame_height)
    sign_crop = frame_bgr[expanded_y1:expanded_y2, expanded_x1:expanded_x2]
    if sign_crop.size == 0:
      continue

    model_read = daemon._classify_speed_limit_from_model(sign_crop)
    ocr_read = daemon._read_speed_limit_from_crop(sign_crop)
    yield {
      "expansion_index": expansion_index,
      "expansion_weight": expansion_weight,
      "expanded_bbox": (expanded_x1, expanded_y1, expanded_x2, expanded_y2),
      "is_regulatory": daemon._is_regulatory_speed_sign(sign_crop),
      "model_speed": model_read[0] if model_read is not None else None,
      "model_confidence": model_read[1] if model_read is not None else None,
      "ocr_speed": ocr_read[0] if ocr_read is not None else None,
      "ocr_confidence": ocr_read[1] if ocr_read is not None else None,
    }


def main() -> int:
  args = parse_args()
  configure_models(args.models_dir)
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  rows = load_rows(args.manifest.expanduser().resolve(), args.include_uncertain)

  output_rows: list[dict[str, str]] = []
  proposal_rows: list[dict[str, str]] = []
  failure_counts: Counter[str] = Counter()

  for row in rows:
    image_text = first_present(row, ("dataset_image", "frame_path", "source_frame"))
    image_path = Path(image_text).expanduser().resolve() if image_text else None
    expected = expected_value(row)
    negative = is_negative(row)
    frame_bgr = cv2.imread(str(image_path)) if image_path is not None else None
    if frame_bgr is None:
      failure_type = "unreadable"
      predicted = None
      confidence = None
      proposals = []
      expected_read_count = 0
      read_values: set[int] = set()
    else:
      detection = daemon._detect_sign(frame_bgr)
      predicted = detection.speed_limit_mph if detection is not None else None
      confidence = detection.confidence if detection is not None else None
      proposals = daemon._collect_detector_classifier_proposals(frame_bgr)
      if args.max_proposals > 0:
        proposals = proposals[:args.max_proposals]

      expected_read_count = 0
      read_values = set()
      should_write_proposals = not args.only_errors
      if not negative and predicted != expected:
        should_write_proposals = True
      if negative and predicted is not None:
        should_write_proposals = True

      for proposal_index, (proposal_confidence, class_id, bbox) in enumerate(proposals):
        for read in crop_reads(daemon, frame_bgr, bbox):
          speeds = [speed for speed in (read["model_speed"], read["ocr_speed"]) if speed is not None]
          read_values.update(int(speed) for speed in speeds)
          if expected is not None and expected in speeds:
            expected_read_count += 1
          if should_write_proposals:
            proposal_rows.append({
              "record_key": row.get("record_key", ""),
              "proposal_index": str(proposal_index),
              "proposal_confidence": f"{proposal_confidence:.6f}",
              "class_id": str(class_id),
              "bbox": ",".join(str(int(value)) for value in bbox),
              "expansion_index": str(read["expansion_index"]),
              "expanded_bbox": ",".join(str(int(value)) for value in read["expanded_bbox"]),
              "expansion_weight": f"{read['expansion_weight']:.3f}",
              "is_regulatory": str(bool(read["is_regulatory"])),
              "model_speed": "" if read["model_speed"] is None else str(read["model_speed"]),
              "model_confidence": "" if read["model_confidence"] is None else f"{read['model_confidence']:.6f}",
              "ocr_speed": "" if read["ocr_speed"] is None else str(read["ocr_speed"]),
              "ocr_confidence": "" if read["ocr_confidence"] is None else f"{read['ocr_confidence']:.6f}",
            })

      failure_type = classify_row(expected, negative, predicted, len(proposals), expected_read_count)

    failure_counts[failure_type] += 1
    output_rows.append({
      "record_key": row.get("record_key", ""),
      "split": row.get("split", ""),
      "sample_type": row.get("sample_type", ""),
      "image_path": "" if image_path is None else str(image_path),
      "expected_speed_limit_mph": "" if expected is None else str(expected),
      "predicted_speed_limit_mph": "" if predicted is None else str(predicted),
      "confidence": "" if confidence is None else f"{confidence:.6f}",
      "negative": str(negative),
      "proposal_count": str(len(proposals)),
      "expected_read_count": str(expected_read_count),
      "read_values": " ".join(str(value) for value in sorted(read_values)),
      "failure_type": failure_type,
    })

  args.output_rows.parent.mkdir(parents=True, exist_ok=True)
  with args.output_rows.open("w", encoding="utf-8", newline="") as output_file:
    fieldnames = (
      "record_key",
      "split",
      "sample_type",
      "image_path",
      "expected_speed_limit_mph",
      "predicted_speed_limit_mph",
      "confidence",
      "negative",
      "proposal_count",
      "expected_read_count",
      "read_values",
      "failure_type",
    )
    writer = csv.DictWriter(output_file, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(output_rows)

  args.output_proposals.parent.mkdir(parents=True, exist_ok=True)
  with args.output_proposals.open("w", encoding="utf-8", newline="") as output_file:
    fieldnames = (
      "record_key",
      "proposal_index",
      "proposal_confidence",
      "class_id",
      "bbox",
      "expansion_index",
      "expanded_bbox",
      "expansion_weight",
      "is_regulatory",
      "model_speed",
      "model_confidence",
      "ocr_speed",
      "ocr_confidence",
    )
    writer = csv.DictWriter(output_file, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(proposal_rows)

  print(f"Rows: {len(output_rows)}")
  for failure_type, count in failure_counts.most_common():
    print(f"{failure_type}: {count}")
  print(f"Wrote {args.output_rows}")
  print(f"Wrote {args.output_proposals}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
