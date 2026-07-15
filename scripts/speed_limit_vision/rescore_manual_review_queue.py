#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from collections import Counter
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from compare_manual_review_queues import classify_change  # type: ignore
  from mine_route_training_samples import model_bundle_fingerprint  # type: ignore
  from replay_route_runtime import configure_models  # type: ignore
else:
  from .compare_manual_review_queues import classify_change
  from .mine_route_training_samples import model_bundle_fingerprint
  from .replay_route_runtime import configure_models


EXTRA_FIELDS = (
  "comparison_change",
  "before_speed_limit_mph",
  "before_confidence",
  "rescore_status",
)


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Rescore stored manual-review crops with a new value classifier.")
  parser.add_argument("--input", type=Path, required=True, help="Baseline manual_review_queue.csv.")
  parser.add_argument("--models-dir", type=Path, required=True, help="Candidate detector/classifier ONNX directory.")
  parser.add_argument("--output", type=Path, required=True, help="Rescored review-compatible output CSV.")
  parser.add_argument("--confidence-delta", type=float, default=0.05, help="Minimum confidence-only change to report.")
  parser.add_argument("--shard-count", type=int, default=1, help="Number of deterministic row shards.")
  parser.add_argument("--shard-index", type=int, default=0, help="Zero-based row shard processed by this invocation.")
  return parser.parse_args()


def rescore_row(
  row: dict[str, str],
  daemon: slv.SpeedLimitVisionDaemon,
  model_fingerprint: str,
  confidence_delta: float,
) -> dict[str, str]:
  output = dict(row)
  before_speed = row.get("candidate_speed_limit_mph", "")
  before_confidence = row.get("candidate_confidence", "")
  output["before_speed_limit_mph"] = before_speed
  output["before_confidence"] = before_confidence
  output["model_fingerprint"] = model_fingerprint

  crop_path = Path(row.get("crop_path", "")).expanduser()
  crop = cv2.imread(str(crop_path)) if crop_path.is_file() else None
  if crop is None:
    output["comparison_change"] = "unreadable"
    output["rescore_status"] = "unreadable"
    return output

  result = daemon._classify_speed_limit_from_model(crop)
  if result is None:
    output["candidate_speed_limit_mph"] = ""
    output["candidate_confidence"] = ""
    output["model_read"] = ""
  else:
    speed_limit_mph, confidence = result
    output["candidate_speed_limit_mph"] = str(int(speed_limit_mph))
    output["candidate_confidence"] = f"{float(confidence):.8f}"
    output["model_read"] = f"{int(speed_limit_mph)}@{float(confidence):.3f}"

  change = classify_change(row, output, confidence_delta)
  output["comparison_change"] = change or "unchanged"
  output["rescore_status"] = "rescored_crop"
  return output


def main() -> int:
  args = parse_args()
  if args.shard_count <= 0 or not 0 <= args.shard_index < args.shard_count:
    raise ValueError("--shard-index must be within --shard-count")

  configure_models(args.models_dir)
  slv.DETECTOR_CLASSIFIER_CROP_OCR_ENABLED = False
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  fingerprint = model_bundle_fingerprint()
  input_path = args.input.expanduser().resolve()
  with input_path.open("r", encoding="utf-8", newline="") as handle:
    reader = csv.DictReader(handle)
    input_fields = list(reader.fieldnames or [])
    rows = [row for index, row in enumerate(reader) if index % args.shard_count == args.shard_index]

  output_rows: list[dict[str, str]] = []
  changes: Counter[str] = Counter()
  transitions: Counter[str] = Counter()
  for index, row in enumerate(rows, start=1):
    rescored = rescore_row(row, daemon, fingerprint, args.confidence_delta)
    output_rows.append(rescored)
    change = rescored["comparison_change"]
    changes[change] += 1
    before_speed = rescored["before_speed_limit_mph"] or "none"
    after_speed = rescored.get("candidate_speed_limit_mph", "") or "none"
    if change != "unchanged":
      transitions[f"{before_speed}->{after_speed}"] += 1
    if index % 1000 == 0:
      print(f"Rescored {index}/{len(rows)} crops", flush=True)

  output_path = args.output.expanduser().resolve()
  output_path.parent.mkdir(parents=True, exist_ok=True)
  fieldnames = [*input_fields, *(field for field in EXTRA_FIELDS if field not in input_fields)]
  with output_path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(output_rows)

  summary = {
    "input": str(input_path),
    "output": str(output_path),
    "models_dir": str(args.models_dir.expanduser().resolve()),
    "model_fingerprint": fingerprint,
    "shard_count": args.shard_count,
    "shard_index": args.shard_index,
    "rows": len(output_rows),
    "changes": dict(sorted(changes.items())),
    "transitions": dict(sorted(transitions.items(), key=lambda item: (-item[1], item[0]))),
  }
  output_path.with_suffix(".json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
  print(json.dumps(summary, indent=2))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
