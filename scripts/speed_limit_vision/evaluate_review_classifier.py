#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv

from collections import Counter
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Evaluate the integrated value/reject classifier on reviewed crops.")
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"))
  parser.add_argument("--positive-manifest", type=Path, required=True)
  parser.add_argument("--reject-manifest", type=Path, required=True)
  parser.add_argument("--split", choices=("train", "val"), help="Optional source split filter.")
  parser.add_argument("--output-csv", type=Path)
  return parser.parse_args()


def read_rows(path: Path) -> list[dict[str, str]]:
  with path.expanduser().resolve().open("r", encoding="utf-8", newline="") as handle:
    return list(csv.DictReader(handle))


def parse_speed(text: str) -> int | None:
  try:
    return int(float((text or "").strip()))
  except ValueError:
    return None


def main() -> int:
  args = parse_args()
  models_dir = args.models_dir.expanduser().resolve()
  slv.US_DETECTOR_MODEL_PATH = models_dir / "speed_limit_us_detector.onnx"
  slv.US_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_value_classifier.onnx"
  reject_path = models_dir / "speed_limit_us_reject_classifier.onnx"
  if reject_path.is_file():
    slv.US_REJECT_CLASSIFIER_MODEL_PATH = reject_path
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)

  cases: list[tuple[str, dict[str, str], int | None]] = []
  for row in read_rows(args.positive_manifest):
    if args.split and row.get("split") != args.split:
      continue
    kind = "advisory" if row.get("review_sign_type", "").strip().lower() == "advisory" else "regulatory"
    cases.append((kind, row, parse_speed(row.get("speed_limit_mph", "")) if kind == "regulatory" else None))
  for row in read_rows(args.reject_manifest):
    if not args.split or row.get("split") == args.split:
      cases.append(("hard_negative", row, None))

  counts: Counter[str] = Counter()
  output_rows = []
  for kind, row, expected in cases:
    crop_path = Path(row.get("crop_path", "")).expanduser()
    crop = cv2.imread(str(crop_path))
    if crop is None:
      counts[f"{kind}_unreadable"] += 1
      continue
    result = daemon._classify_speed_limit_from_model(crop)
    predicted = result[0] if result is not None else None
    confidence = result[1] if result is not None else None
    counts[f"{kind}_total"] += 1
    if kind == "regulatory":
      counts[f"regulatory_speed_{expected}_total"] += 1
      if predicted is not None:
        counts["regulatory_any"] += 1
      if predicted == expected:
        counts["regulatory_exact"] += 1
        counts[f"regulatory_speed_{expected}_exact"] += 1
      elif predicted is not None:
        counts["regulatory_wrong"] += 1
    elif predicted is None:
      counts[f"{kind}_rejected"] += 1
    else:
      counts[f"{kind}_false_read"] += 1
    output_rows.append({
      "record_key": row.get("record_key", ""),
      "split": row.get("split", ""),
      "kind": kind,
      "crop_path": str(crop_path),
      "expected_speed_limit_mph": "" if expected is None else expected,
      "predicted_speed_limit_mph": "" if predicted is None else predicted,
      "confidence": "" if confidence is None else f"{confidence:.6f}",
    })

  regulatory_total = counts["regulatory_total"]
  advisory_total = counts["advisory_total"]
  hard_negative_total = counts["hard_negative_total"]
  exact_rate = counts["regulatory_exact"] / regulatory_total if regulatory_total else 0.0
  advisory_reject_rate = counts["advisory_rejected"] / advisory_total if advisory_total else 0.0
  hard_negative_reject_rate = counts["hard_negative_rejected"] / hard_negative_total if hard_negative_total else 0.0
  regulatory_summary = f"Regulatory exact: {counts['regulatory_exact']}/{regulatory_total} ({exact_rate:.3f})"
  print(f"{regulatory_summary}; wrong reads: {counts['regulatory_wrong']}")
  print(f"Advisory rejected: {counts['advisory_rejected']}/{advisory_total} ({advisory_reject_rate:.3f})")
  hard_negative_summary = f"Hard negatives rejected: {counts['hard_negative_rejected']}/{hard_negative_total}"
  print(f"{hard_negative_summary} ({hard_negative_reject_rate:.3f})")
  speed_parts = []
  for speed in slv.US_CLASSIFIER_SPEED_VALUES:
    total = counts[f"regulatory_speed_{speed}_total"]
    if total:
      speed_parts.append(f"{speed}:{counts[f'regulatory_speed_{speed}_exact']}/{total}")
  print("Exact by speed: " + " ".join(speed_parts))

  if args.output_csv:
    output = args.output_csv.expanduser().resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("w", encoding="utf-8", newline="") as handle:
      writer = csv.DictWriter(handle, fieldnames=tuple(output_rows[0]) if output_rows else ("record_key",))
      writer.writeheader()
      writer.writerows(output_rows)
    print(f"Wrote {output}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
