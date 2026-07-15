#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import random

from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Evaluate runtime speed-limit ONNX models on a mined frame manifest.")
  parser.add_argument(
    "--models-dir",
    type=Path,
    default=Path("starpilot/assets/vision_models"),
    help="Directory containing speed_limit_us_detector.onnx and speed_limit_us_value_classifier.onnx.",
  )
  parser.add_argument("--manifest", type=Path, required=True, help="CSV manifest with dataset_image/frame_path/image_path and labels.")
  parser.add_argument("--split", action="append", help="Optional split filter. Repeat for multiple splits.")
  parser.add_argument("--max-rows", type=int, default=0, help="Optional cap after filtering.")
  parser.add_argument("--seed", type=int, default=0, help="Sampling seed used with --max-rows.")
  parser.add_argument("--output-csv", type=Path, help="Optional per-row prediction output.")
  parser.add_argument("--detector-min-confidence", type=float, help="Override runtime US detector confidence threshold.")
  parser.add_argument("--classifier-min-confidence", type=float, help="Override runtime US classifier confidence threshold.")
  parser.add_argument("--classifier-reject-min-confidence", type=float, help="Override runtime reject-class confidence threshold.")
  parser.add_argument("--trusted-model-min-confidence", type=float, help="Override tiny-box trusted model confidence for evaluation.")
  parser.add_argument("--strong-rescue-min-proposal-confidence", type=float, help="Override single-frame tiny-sign proposal confidence.")
  parser.add_argument("--strong-rescue-min-read-confidence", type=float, help="Override single-frame tiny-sign classifier confidence.")
  parser.add_argument(
    "--detector-region-mode",
    choices=("full", "right_roi", "full_and_right_roi"),
    help="Override the detector/classifier region mode used by speed_limit_vision.py.",
  )
  parser.add_argument("--right-roi-bounds", help="Override the right ROI as left,top,right,bottom ratios, for example 0.45,0,1,0.82.")
  parser.add_argument("--right-roi-min-confidence", type=float, help="Override the right ROI detector minimum confidence.")
  parser.add_argument("--full-frame-ocr", action="store_true", help="Enable the expensive full-frame OCR fallback during eval.")
  crop_ocr_group = parser.add_mutually_exclusive_group()
  crop_ocr_group.add_argument("--crop-ocr", action="store_true", dest="crop_ocr", default=None, help="Enable crop OCR confirmation.")
  crop_ocr_group.add_argument("--no-crop-ocr", action="store_false", dest="crop_ocr", help="Evaluate the model-only detector/classifier path.")
  parser.add_argument("--separate-reject-classifier", action="store_true", help="Enable the optional second-stage reject classifier during eval.")
  parser.add_argument("--classifier-expansion-limit", type=int, help="Evaluate only the first N detector crop expansions.")
  parser.add_argument("--classifier-expansion-indices", help="Comma-separated detector crop expansion indices to evaluate.")
  parser.add_argument("--include-uncertain", action="store_true", help="Include uncertain_positive review rows in positive metrics.")
  parser.add_argument("--advisory-positive", action="store_true", help="Score reviewed advisory rows as readable speed positives.")
  parser.add_argument("--strict-positive-recall", type=float, help="Exit non-zero if positive exact recall is below this value.")
  parser.add_argument("--strict-negative-fpr", type=float, help="Exit non-zero if negative false-positive rate is above this value.")
  return parser.parse_args()


def configure_runtime_options(args: argparse.Namespace) -> None:
  if args.detector_region_mode:
    slv.DETECTOR_CLASSIFIER_REGION_MODE = args.detector_region_mode

  if args.full_frame_ocr:
    slv.FULL_FRAME_OCR_FALLBACK_ENABLED = True
  if args.crop_ocr is not None:
    slv.DETECTOR_CLASSIFIER_CROP_OCR_ENABLED = args.crop_ocr
  if args.separate_reject_classifier:
    slv.SEPARATE_REJECT_CLASSIFIER_ENABLED = True

  if args.right_roi_bounds:
    parts = [float(part.strip()) for part in args.right_roi_bounds.split(",")]
    if len(parts) != 4:
      raise ValueError("--right-roi-bounds must contain four comma-separated ratios")
    left, top, right, bottom = parts
    if not (0.0 <= left < right <= 1.0 and 0.0 <= top < bottom <= 1.0):
      raise ValueError("--right-roi-bounds must be normalized as 0 <= left < right <= 1 and 0 <= top < bottom <= 1")

    min_confidence = args.right_roi_min_confidence
    if min_confidence is None:
      min_confidence = float(slv.ROI_WINDOWS[-1]["min_confidence"]) if slv.ROI_WINDOWS else slv.US_DETECTOR_MIN_CONFIDENCE
    right_roi = {"bounds": (left, top, right, bottom), "min_confidence": float(min_confidence)}
    slv.ROI_WINDOWS = (*slv.ROI_WINDOWS[:-1], right_roi) if slv.ROI_WINDOWS else (right_roi,)
  elif args.right_roi_min_confidence is not None:
    if not slv.ROI_WINDOWS:
      right_roi = {"bounds": (0.72, 0.05, 1.00, 0.82), "min_confidence": float(args.right_roi_min_confidence)}
      slv.ROI_WINDOWS = (right_roi,)
    else:
      right_roi = dict(slv.ROI_WINDOWS[-1])
      right_roi["min_confidence"] = float(args.right_roi_min_confidence)
      slv.ROI_WINDOWS = (*slv.ROI_WINDOWS[:-1], right_roi)


def first_present(row: dict[str, str], keys: tuple[str, ...]) -> str:
  for key in keys:
    value = row.get(key, "").strip()
    if value:
      return value
  return ""


def expected_value(row: dict[str, str]) -> int | None:
  value_text = first_present(row, ("expected_speed_limit_mph", "speed_limit_mph", "dominant_value"))
  if value_text:
    try:
      return int(float(value_text))
    except ValueError:
      return None

  for key in ("full_detection", "model_read", "ocr_read"):
    read_text = row.get(key, "").strip()
    if "@" in read_text:
      try:
        return int(float(read_text.split("@", 1)[0]))
      except ValueError:
        return None
  return None


def is_negative(row: dict[str, str]) -> bool:
  sample_type = row.get("sample_type", "").lower()
  if "negative" in sample_type:
    return True
  return expected_value(row) is None


def load_rows(manifest_path: Path, splits: set[str] | None) -> list[dict[str, str]]:
  with manifest_path.open("r", encoding="utf-8", newline="") as manifest_file:
    reader = csv.DictReader(manifest_file)
    rows = []
    for row in reader:
      if splits is not None and row.get("split", "") not in splits:
        continue
      rows.append(row)
  return rows


def main() -> int:
  args = parse_args()
  models_dir = args.models_dir.expanduser().resolve()
  detector_path = models_dir / "speed_limit_us_detector.onnx"
  classifier_path = models_dir / "speed_limit_us_value_classifier.onnx"
  reject_classifier_path = models_dir / "speed_limit_us_reject_classifier.onnx"
  if not detector_path.is_file():
    raise FileNotFoundError(detector_path)
  if not classifier_path.is_file():
    raise FileNotFoundError(classifier_path)

  rows = load_rows(args.manifest.expanduser().resolve(), set(args.split) if args.split else None)
  uncertain_count = sum(
    row.get("sample_type", "") == "uncertain_positive" or row.get("review_status", "") == "uncertain"
    for row in rows
  )
  if not args.include_uncertain:
    rows = [
      row for row in rows
      if row.get("sample_type", "") != "uncertain_positive" and row.get("review_status", "") != "uncertain"
    ]
  if args.max_rows > 0 and len(rows) > args.max_rows:
    rng = random.Random(args.seed)
    rows = rng.sample(rows, args.max_rows)

  slv.US_DETECTOR_MODEL_PATH = detector_path
  slv.US_CLASSIFIER_MODEL_PATH = classifier_path
  slv.US_REJECT_CLASSIFIER_MODEL_PATH = reject_classifier_path
  if args.detector_min_confidence is not None:
    slv.US_DETECTOR_MIN_CONFIDENCE = args.detector_min_confidence
  if args.classifier_min_confidence is not None:
    slv.US_CLASSIFIER_MIN_CONFIDENCE = args.classifier_min_confidence
  if args.classifier_reject_min_confidence is not None:
    slv.US_CLASSIFIER_REJECT_MIN_CONFIDENCE = args.classifier_reject_min_confidence
    slv.US_REJECT_CLASSIFIER_MIN_CONFIDENCE = args.classifier_reject_min_confidence
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
  configure_runtime_options(args)
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)

  output_rows: list[dict[str, str]] = []
  positive_count = 0
  positive_exact = 0
  positive_detected = 0
  negative_count = 0
  negative_false_positive = 0
  unreadable_count = 0

  for row in rows:
    image_text = first_present(row, ("dataset_image", "frame_path", "source_frame", "image_path"))
    if not image_text:
      unreadable_count += 1
      continue

    image_path = Path(image_text).expanduser().resolve()
    frame_bgr = cv2.imread(str(image_path))
    if frame_bgr is None:
      unreadable_count += 1
      continue

    detection = daemon._detect_sign(frame_bgr)
    predicted_value = detection.speed_limit_mph if detection is not None else None
    confidence = detection.confidence if detection is not None else None
    expected = expected_value(row)
    advisory_positive = args.advisory_positive and row.get("review_sign_type", "").strip().lower() == "advisory"
    negative = False if advisory_positive else is_negative(row)

    if negative:
      negative_count += 1
      if predicted_value is not None:
        negative_false_positive += 1
    else:
      positive_count += 1
      if predicted_value is not None:
        positive_detected += 1
      if predicted_value == expected:
        positive_exact += 1

    if args.output_csv:
      output_rows.append({
        "record_key": row.get("record_key", ""),
        "split": row.get("split", ""),
        "sample_type": row.get("sample_type", ""),
        "image_path": str(image_path),
        "expected_speed_limit_mph": "" if expected is None else str(expected),
        "predicted_speed_limit_mph": "" if predicted_value is None else str(predicted_value),
        "confidence": "" if confidence is None else f"{confidence:.6f}",
        "negative": str(negative),
      })

  positive_exact_recall = positive_exact / positive_count if positive_count else 0.0
  positive_any_recall = positive_detected / positive_count if positive_count else 0.0
  negative_fpr = negative_false_positive / negative_count if negative_count else 0.0

  print(f"Rows evaluated: {positive_count + negative_count}")
  if uncertain_count and not args.include_uncertain:
    print(f"Skipped uncertain rows: {uncertain_count}")
  print(f"Unreadable rows: {unreadable_count}")
  positive_summary = f"Positive exact: {positive_exact}/{positive_count} ({positive_exact_recall:.3f})"
  detection_summary = f"any detection: {positive_detected}/{positive_count} ({positive_any_recall:.3f})"
  print(f"{positive_summary}; {detection_summary}")
  print(f"Negative false positives: {negative_false_positive}/{negative_count} ({negative_fpr:.3f})")

  if args.output_csv:
    args.output_csv.parent.mkdir(parents=True, exist_ok=True)
    with args.output_csv.open("w", encoding="utf-8", newline="") as output_file:
      fieldnames = (
        "record_key",
        "split",
        "sample_type",
        "image_path",
        "expected_speed_limit_mph",
        "predicted_speed_limit_mph",
        "confidence",
        "negative",
      )
      writer = csv.DictWriter(output_file, fieldnames=fieldnames)
      writer.writeheader()
      writer.writerows(output_rows)
    print(f"Wrote {args.output_csv}")

  failed = False
  if args.strict_positive_recall is not None and positive_exact_recall < args.strict_positive_recall:
    failed = True
  if args.strict_negative_fpr is not None and negative_fpr > args.strict_negative_fpr:
    failed = True
  return 1 if failed else 0


if __name__ == "__main__":
  raise SystemExit(main())
