#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import shutil

from collections import Counter
from pathlib import Path

import cv2

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from import_manual_review_queue import merged_review_rows, parse_speed  # type: ignore
else:
  from .import_manual_review_queue import merged_review_rows, parse_speed


SPEED_VALUES = (15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75)
SPEED_TO_CLASS = {speed: index for index, speed in enumerate(SPEED_VALUES)}
POSITIVE_STATUSES = frozenset(("accepted", "corrected"))


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Add reviewed comma sign tracks to a direct speed-class detector dataset.")
  parser.add_argument("--base", type=Path, required=True, help="Existing YOLO direct-value detector dataset.")
  parser.add_argument("--queue", type=Path, required=True, help="Source reviewed manual_review_queue.csv.")
  parser.add_argument("--labels", type=Path, help="Defaults to manual_review_labels.csv beside the queue.")
  parser.add_argument("--track-samples", type=Path, required=True)
  parser.add_argument("--output", type=Path, required=True)
  parser.add_argument("--train-ratio", type=float, default=0.85)
  parser.add_argument("--min-growth", type=float, default=1.10)
  parser.add_argument("--min-exact-confidence", type=float, default=0.80)
  parser.add_argument("--min-detector-confidence", type=float, default=0.30)
  parser.add_argument("--max-track-rank", type=int, default=3)
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


def split_for_key(key: str, train_ratio: float) -> str:
  fraction = int(hashlib.sha1(key.encode()).hexdigest()[:8], 16) / 0xFFFFFFFF
  return "train" if fraction < train_ratio else "val"


def link_or_copy(source: Path, destination: Path) -> None:
  destination.parent.mkdir(parents=True, exist_ok=True)
  if destination.exists():
    return
  try:
    os.link(source, destination)
  except OSError:
    shutil.copy2(source, destination)


def yolo_label(speed: int, bbox: tuple[int, int, int, int], image_path: Path) -> str | None:
  image = cv2.imread(str(image_path))
  if image is None:
    return None
  height, width = image.shape[:2]
  x1, y1, x2, y2 = bbox
  x1 = max(min(x1, width - 1), 0)
  y1 = max(min(y1, height - 1), 0)
  x2 = max(min(x2, width), 0)
  y2 = max(min(y2, height), 0)
  if x2 <= x1 or y2 <= y1:
    return None
  values = (
    SPEED_TO_CLASS[speed],
    (x1 + x2) / (2 * width),
    (y1 + y2) / (2 * height),
    (x2 - x1) / width,
    (y2 - y1) / height,
  )
  return f"{values[0]} {values[1]:.8f} {values[2]:.8f} {values[3]:.8f} {values[4]:.8f}\n"


def copy_base_dataset(base: Path, output: Path) -> Counter[str]:
  counts: Counter[str] = Counter()
  for split in ("train", "val"):
    image_dir = base / "images" / split
    label_dir = base / "labels" / split
    for source_image in image_dir.iterdir():
      if not source_image.is_file() or source_image.name.startswith("._"):
        continue
      source_label = label_dir / f"{source_image.stem}.txt"
      if not source_label.is_file():
        continue
      destination_stem = f"base_{source_image.stem}"
      link_or_copy(source_image, output / "images" / split / f"{destination_stem}{source_image.suffix.lower()}")
      link_or_copy(source_label, output / "labels" / split / f"{destination_stem}.txt")
      counts[f"base_{split}"] += 1
  return counts


def add_reviewed_anchors(
  queue_path: Path,
  labels_path: Path,
  output: Path,
  train_ratio: float,
  seen_images: set[Path],
) -> Counter[str]:
  counts: Counter[str] = Counter()
  for row in merged_review_rows(queue_path, labels_path):
    if row.get("review_status") not in POSITIVE_STATUSES:
      continue
    speed = parse_speed(row.get("review_speed_limit_mph", ""))
    bbox = parse_bbox(row.get("review_bbox") or row.get("bbox", ""))
    image_path = Path(row.get("frame_path", "")).expanduser()
    if speed not in SPEED_TO_CLASS or bbox is None or not image_path.is_file():
      continue
    resolved_image = image_path.resolve()
    if resolved_image in seen_images:
      continue
    label = yolo_label(speed, bbox, resolved_image)
    if label is None:
      continue
    split = split_for_key(row.get("route") or row.get("record_key", ""), train_ratio)
    stem = f"review_{row.get('record_key', hashlib.sha1(str(resolved_image).encode()).hexdigest()[:16])}"
    destination_image = output / "images" / split / f"{stem}{resolved_image.suffix.lower()}"
    link_or_copy(resolved_image, destination_image)
    (output / "labels" / split / f"{stem}.txt").write_text(label, encoding="ascii")
    seen_images.add(resolved_image)
    counts[f"anchor_{split}"] += 1
    counts[f"speed_{speed}"] += 1
  return counts


def trusted_track_row(row: dict[str, str], args: argparse.Namespace) -> bool:
  try:
    expected = int(row.get("expected_speed_limit_mph", ""))
    predicted = int(row.get("predicted_speed_limit_mph", "") or 0)
    read_confidence = float(row.get("read_confidence", "") or 0.0)
    detector_confidence = float(row.get("detector_confidence", "") or 0.0)
    growth = float(row.get("area_ratio_to_anchor", "") or 0.0)
    rank = int(row.get("rank", "") or 999)
  except ValueError:
    return False
  exact_read = predicted == expected and read_confidence >= args.min_exact_confidence
  detector_snap = detector_confidence >= args.min_detector_confidence
  return expected in SPEED_TO_CLASS and growth >= args.min_growth and rank <= args.max_track_rank and (exact_read or detector_snap)


def add_track_samples(args: argparse.Namespace, output: Path, seen_images: set[Path]) -> Counter[str]:
  counts: Counter[str] = Counter()
  with args.track_samples.expanduser().resolve().open(encoding="utf-8", newline="") as input_file:
    for row in csv.DictReader(input_file):
      if not trusted_track_row(row, args):
        counts["track_rejected"] += 1
        continue
      speed = int(row["expected_speed_limit_mph"])
      bbox = parse_bbox(row.get("bbox", ""))
      image_path = Path(row.get("frame_path", "")).expanduser().resolve()
      if bbox is None or not image_path.is_file() or image_path in seen_images:
        counts["track_rejected"] += 1
        continue
      label = yolo_label(speed, bbox, image_path)
      if label is None:
        counts["track_rejected"] += 1
        continue
      split = split_for_key(row.get("route") or row.get("track_key", ""), args.train_ratio)
      stem = f"track_{row.get('track_key', '')}_{row.get('rank', '')}"
      destination_image = output / "images" / split / f"{stem}{image_path.suffix.lower()}"
      link_or_copy(image_path, destination_image)
      (output / "labels" / split / f"{stem}.txt").write_text(label, encoding="ascii")
      seen_images.add(image_path)
      counts[f"track_{split}"] += 1
      counts[f"speed_{speed}"] += 1
  return counts


def main() -> int:
  args = parse_args()
  base = args.base.expanduser().resolve()
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  output = args.output.expanduser().resolve()
  for split in ("train", "val"):
    (output / "images" / split).mkdir(parents=True, exist_ok=True)
    (output / "labels" / split).mkdir(parents=True, exist_ok=True)

  counts = copy_base_dataset(base, output)
  seen_images: set[Path] = set()
  counts.update(add_reviewed_anchors(queue_path, labels_path, output, args.train_ratio, seen_images))
  counts.update(add_track_samples(args, output, seen_images))
  yaml_lines = [
    f"path: {output}",
    "train: images/train",
    "val: images/val",
    "names:",
    *(f"  {index}: speed_limit_{speed}" for index, speed in enumerate(SPEED_VALUES)),
  ]
  (output / "dataset.yaml").write_text("\n".join(yaml_lines) + "\n", encoding="ascii")
  summary = {"base": str(base), "output": str(output), "counts": dict(sorted(counts.items()))}
  (output / "track_dataset_summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="ascii")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
