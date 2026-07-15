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

from starpilot.system.speed_limit_vision import DETECTOR_CLASSIFIER_EXPANSIONS


SPEED_VALUES = frozenset((15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75))


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Add trusted later-frame sign tracks to a classifier dataset.")
  parser.add_argument("--base", type=Path, required=True)
  parser.add_argument("--track-samples", type=Path, required=True)
  parser.add_argument("--output", type=Path, required=True)
  parser.add_argument("--train-ratio", type=float, default=0.85)
  parser.add_argument("--min-growth", type=float, default=1.10)
  parser.add_argument("--max-growth", type=float, default=float("inf"))
  parser.add_argument("--min-exact-confidence", type=float, default=0.80)
  parser.add_argument("--min-detector-confidence", type=float, default=0.30)
  parser.add_argument("--min-tracking-confidence", type=float, default=1.01)
  parser.add_argument("--max-track-rank", type=int, default=3)
  parser.add_argument("--hard-example-repeat", type=int, default=1, help="Train repeats for rejected or low-confidence track crops.")
  parser.add_argument("--hard-example-min-confidence", type=float, default=0.90)
  parser.add_argument(
    "--runtime-expansions",
    action="store_true",
    help="Build crops from each source frame using the live detector/classifier expansion geometry.",
  )
  return parser.parse_args()


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


def remove_appledouble_files(root: Path) -> int:
  removed = 0
  for path in root.rglob("._*"):
    if path.is_file():
      path.unlink()
      removed += 1
  return removed


def parse_bbox(value: str) -> tuple[int, int, int, int] | None:
  try:
    bbox = tuple(int(round(float(part.strip()))) for part in value.split(","))
  except ValueError:
    return None
  if len(bbox) != 4:
    return None
  x1, y1, x2, y2 = bbox
  return (x1, y1, x2, y2) if x2 > x1 and y2 > y1 else None


def stage_runtime_expansions(row: dict[str, str], destination_dir: Path, repeat_count: int) -> int:
  frame_path = Path(row.get("frame_path", "")).expanduser().resolve()
  bbox = parse_bbox(row.get("bbox", ""))
  if not frame_path.is_file() or bbox is None:
    return 0
  frame = cv2.imread(str(frame_path))
  if frame is None:
    return 0

  frame_height, frame_width = frame.shape[:2]
  x1, y1, x2, y2 = bbox
  box_width = x2 - x1
  box_height = y2 - y1
  destination_dir.mkdir(parents=True, exist_ok=True)
  staged = 0
  track_key = row.get("track_key", "")
  rank = row.get("rank", "")
  for repeat_index in range(repeat_count):
    repeat_suffix = f"_r{repeat_index:02d}" if repeat_count > 1 else ""
    for expansion_index, (left, top, right, bottom, _weight) in enumerate(DETECTOR_CLASSIFIER_EXPANSIONS):
      crop_x1 = max(int(x1 - box_width * left), 0)
      crop_y1 = max(int(y1 - box_height * top), 0)
      crop_x2 = min(int(x2 + box_width * right), frame_width)
      crop_y2 = min(int(y2 + box_height * bottom), frame_height)
      crop = frame[crop_y1:crop_y2, crop_x1:crop_x2]
      if crop.size == 0:
        continue
      destination = destination_dir / f"track_{track_key}_{rank}_e{expansion_index:02d}{repeat_suffix}.jpg"
      if destination.exists() or cv2.imwrite(str(destination), crop, (cv2.IMWRITE_JPEG_QUALITY, 95)):
        staged += 1
  return staged


def trusted_track_row(row: dict[str, str], args: argparse.Namespace) -> bool:
  try:
    expected = int(row.get("expected_speed_limit_mph", ""))
    predicted = int(row.get("predicted_speed_limit_mph", "") or 0)
    read_confidence = float(row.get("read_confidence", "") or 0.0)
    detector_confidence = float(row.get("detector_confidence", "") or 0.0)
    tracking_confidence = float(row.get("tracking_confidence", "") or 0.0)
    growth = float(row.get("area_ratio_to_anchor", "") or 0.0)
    rank = int(row.get("rank", "") or 999)
  except ValueError:
    return False
  exact = predicted == expected and read_confidence >= args.min_exact_confidence
  detector_snap = detector_confidence >= args.min_detector_confidence
  optical_flow_track = tracking_confidence >= args.min_tracking_confidence
  return (
    expected in SPEED_VALUES and
    args.min_growth <= growth <= args.max_growth and
    rank <= args.max_track_rank and
    (exact or detector_snap or optical_flow_track)
  )


def main() -> int:
  args = parse_args()
  if args.hard_example_repeat < 1:
    raise ValueError("--hard-example-repeat must be at least 1")
  if args.max_growth < args.min_growth:
    raise ValueError("--max-growth must be at least --min-growth")
  base = args.base.expanduser().resolve()
  output = args.output.expanduser().resolve()
  counts: Counter[str] = Counter()
  validation_routes: set[str] = set()
  for split in ("train", "val"):
    for class_dir in (base / split).iterdir():
      if not class_dir.is_dir() or class_dir.name.startswith("._"):
        continue
      for source in class_dir.iterdir():
        if not source.is_file() or source.name.startswith("._") or source.suffix.lower() not in (".jpg", ".jpeg", ".png"):
          continue
        link_or_copy(source, output / split / class_dir.name / f"base_{source.name}")
        counts[f"base_{split}"] += 1

  with args.track_samples.expanduser().resolve().open(encoding="utf-8", newline="") as input_file:
    for row in csv.DictReader(input_file):
      if not trusted_track_row(row, args):
        counts["track_rejected"] += 1
        continue
      source = Path(row.get("crop_path", "")).expanduser().resolve()
      if not source.is_file():
        counts["track_rejected"] += 1
        continue
      speed = int(row["expected_speed_limit_mph"])
      split = split_for_key(row.get("route") or row.get("track_key", ""), args.train_ratio)
      if split == "val" and row.get("route"):
        validation_routes.add(row["route"])
      predicted = int(row.get("predicted_speed_limit_mph", "") or 0)
      read_confidence = float(row.get("read_confidence", "") or 0.0)
      hard_example = predicted != speed or read_confidence < args.hard_example_min_confidence
      repeat_count = args.hard_example_repeat if split == "train" and hard_example else 1
      if args.runtime_expansions:
        staged = stage_runtime_expansions(row, output / split / str(speed), repeat_count)
      else:
        staged = 0
        for repeat_index in range(repeat_count):
          repeat_suffix = f"_r{repeat_index:02d}" if repeat_count > 1 else ""
          name = f"track_{row.get('track_key', '')}_{row.get('rank', '')}{repeat_suffix}{source.suffix.lower()}"
          link_or_copy(source, output / split / str(speed) / name)
          staged += 1
      if staged == 0:
        counts["track_rejected"] += 1
        continue
      if hard_example:
        counts[f"hard_track_{split}"] += staged
      counts[f"track_{split}"] += staged
      counts[f"speed_{speed}"] += staged

  counts["appledouble_removed"] = remove_appledouble_files(output)
  (output / "track_validation_routes.txt").write_text("\n".join(sorted(validation_routes)) + "\n", encoding="ascii")
  summary = {"base": str(base), "output": str(output), "counts": dict(sorted(counts.items()))}
  (output / "track_dataset_summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="ascii")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
