#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json

from collections import Counter
from pathlib import Path


IMAGE_SUFFIXES = frozenset((".jpg", ".jpeg", ".png", ".bmp", ".webp"))


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Evaluate a YOLO classifier dataset with the runtime confidence threshold.")
  parser.add_argument("--model", type=Path, required=True)
  parser.add_argument("--data", type=Path, required=True, help="Classifier dataset root containing train/ and val/.")
  parser.add_argument("--split", choices=("train", "val"), default="val")
  parser.add_argument("--imgsz", type=int, default=128)
  parser.add_argument("--batch", type=int, default=64)
  parser.add_argument("--device", default="cpu")
  parser.add_argument("--min-confidence", type=float, default=0.60)
  parser.add_argument("--output-json", type=Path)
  return parser.parse_args()


def main() -> int:
  args = parse_args()
  split_root = args.data.expanduser().resolve() / args.split
  if not split_root.is_dir():
    raise FileNotFoundError(split_root)

  samples: list[tuple[Path, str]] = []
  for class_dir in sorted(split_root.iterdir()):
    if not class_dir.is_dir() or class_dir.name.startswith("._"):
      continue
    for image_path in sorted(class_dir.iterdir()):
      if image_path.name.startswith("._") or image_path.suffix.lower() not in IMAGE_SUFFIXES or not image_path.is_file():
        continue
      samples.append((image_path, class_dir.name))
  if not samples:
    raise RuntimeError(f"No classifier images found under {split_root}")

  try:
    from ultralytics import YOLO
  except Exception as exc:
    raise SystemExit("Ultralytics is required to evaluate classifier checkpoints.") from exc

  model = YOLO(str(args.model.expanduser().resolve()))
  predictions = model.predict(
    source=[str(path) for path, _ in samples],
    imgsz=args.imgsz,
    batch=args.batch,
    device=args.device,
    verbose=False,
    stream=True,
  )

  class_counts: dict[str, Counter[str]] = {}
  total_counts: Counter[str] = Counter()
  for (_, expected), result in zip(samples, predictions, strict=True):
    probabilities = result.probs
    if probabilities is None:
      raise RuntimeError("Classifier prediction did not include probabilities")
    predicted = str(result.names[int(probabilities.top1)])
    confidence = float(probabilities.top1conf)
    counts = class_counts.setdefault(expected, Counter())
    counts["total"] += 1
    total_counts["total"] += 1
    if predicted == expected:
      counts["top1_exact"] += 1
      total_counts["top1_exact"] += 1
    if confidence < args.min_confidence:
      counts["rejected"] += 1
      total_counts["rejected"] += 1
      continue
    counts["accepted"] += 1
    total_counts["accepted"] += 1
    if predicted == expected:
      counts["accepted_exact"] += 1
      total_counts["accepted_exact"] += 1
    else:
      counts["accepted_wrong"] += 1
      total_counts["accepted_wrong"] += 1

  def summarize(counts: Counter[str]) -> dict[str, float | int]:
    total = counts["total"]
    accepted = counts["accepted"]
    return {
      "total": total,
      "top1_exact": counts["top1_exact"],
      "top1_exact_rate": round(counts["top1_exact"] / total, 6) if total else 0.0,
      "accepted": accepted,
      "accepted_coverage": round(accepted / total, 6) if total else 0.0,
      "accepted_exact": counts["accepted_exact"],
      "accepted_wrong": counts["accepted_wrong"],
      "accepted_precision": round(counts["accepted_exact"] / accepted, 6) if accepted else 0.0,
      "rejected": counts["rejected"],
    }

  summary = {
    "model": str(args.model.expanduser().resolve()),
    "data": str(split_root),
    "minimum_confidence": args.min_confidence,
    "overall": summarize(total_counts),
    "classes": {name: summarize(class_counts[name]) for name in sorted(class_counts)},
  }
  encoded = json.dumps(summary, indent=2, sort_keys=True) + "\n"
  print(encoded, end="")
  if args.output_json:
    output_path = args.output_json.expanduser().resolve()
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(encoded, encoding="ascii")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
