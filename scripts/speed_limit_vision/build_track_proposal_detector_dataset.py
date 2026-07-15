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
import yaml

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from import_manual_review_queue import merged_review_rows, parse_speed  # type: ignore
else:
  from .import_manual_review_queue import merged_review_rows, parse_speed


POSITIVE_STATUSES = frozenset(("accepted", "corrected"))
IMPORTANT_SPEEDS = frozenset(range(30, 70, 5))


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Add clean reviewed sign tracks to the single-class runtime proposal detector.")
  parser.add_argument("--base-yaml", type=Path, required=True, help="Existing single-class detector dataset YAML to preserve.")
  parser.add_argument("--queue", type=Path, required=True, help="Reviewed manual_review_queue.csv used to create the tracks.")
  parser.add_argument("--labels", type=Path, help="Defaults to manual_review_labels.csv beside the queue.")
  parser.add_argument("--track-samples", type=Path, required=True, help="track_samples.csv from mine_reviewed_sign_tracks.py.")
  parser.add_argument("--output", type=Path, required=True, help="Output directory for added images, labels, and dataset.yaml.")
  parser.add_argument("--train-ratio", type=float, default=0.85, help="Route-level train split ratio.")
  parser.add_argument("--min-growth", type=float, default=1.0, help="Minimum tracked box area relative to its reviewed anchor.")
  parser.add_argument("--min-exact-confidence", type=float, default=0.80)
  parser.add_argument("--min-detector-confidence", type=float, default=0.30)
  parser.add_argument("--min-tracking-confidence", type=float, default=1.01, help="Optical-flow confidence for detector-free tracks.")
  parser.add_argument("--max-track-rank", type=int, default=4)
  parser.add_argument("--important-repeat", type=int, default=2, help="Train repeats for accepted 30-65 mph samples.")
  parser.add_argument("--other-repeat", type=int, default=1, help="Train repeats for other accepted speed samples.")
  parser.add_argument(
    "--focus-eval-csv",
    type=Path,
    help="Optional runtime event CSV; only reviewed rows where --focus-outcome is false are added.",
  )
  parser.add_argument(
    "--focus-outcome",
    choices=("candidate_hit", "publish_hit"),
    default="publish_hit",
    help="Runtime outcome used to select hard positives from --focus-eval-csv.",
  )
  parser.add_argument(
    "--focus-train-only",
    action="store_true",
    help="Exclude selected records assigned to the route-level validation split.",
  )
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


def yolo_label(bbox: tuple[int, int, int, int], image_path: Path) -> str | None:
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
    (x1 + x2) / (2 * width),
    (y1 + y2) / (2 * height),
    (x2 - x1) / width,
    (y2 - y1) / height,
  )
  return f"0 {values[0]:.8f} {values[1]:.8f} {values[2]:.8f} {values[3]:.8f}\n"


def focus_record_keys(eval_path: Path, outcome: str) -> set[str]:
  selected: set[str] = set()
  with eval_path.expanduser().resolve().open(encoding="utf-8", newline="") as input_file:
    reader = csv.DictReader(input_file)
    if outcome not in (reader.fieldnames or ()):
      raise ValueError(f"{eval_path} does not contain {outcome}")
    for row in reader:
      record_key = row.get("record_key", "")
      outcome_value = row.get(outcome, "").strip().lower()
      if record_key and outcome_value not in ("1", "true", "yes"):
        selected.add(record_key)
  return selected


def reviewed_positive_rows(
  queue_path: Path,
  labels_path: Path,
  selected_record_keys: set[str] | None = None,
) -> dict[str, dict[str, str]]:
  return {
    row.get("record_key", ""): row
    for row in merged_review_rows(queue_path, labels_path)
    if (
      row.get("record_key") and
      (selected_record_keys is None or row.get("record_key") in selected_record_keys) and
      row.get("review_status") in POSITIVE_STATUSES and
      parse_speed(row.get("review_speed_limit_mph", ""))
    )
  }


def reviewed_row_for_track(
  track_row: dict[str, str],
  reviewed_rows: dict[str, dict[str, str]],
) -> dict[str, str] | None:
  return reviewed_rows.get(track_row.get("track_key", "")) or reviewed_rows.get(track_row.get("source_record_key", ""))


def trusted_track_row(row: dict[str, str], reviewed_row: dict[str, str], args: argparse.Namespace) -> bool:
  original_bbox = parse_bbox(reviewed_row.get("bbox", ""))
  corrected_bbox = parse_bbox(reviewed_row.get("review_bbox", ""))
  if corrected_bbox is not None and corrected_bbox != original_bbox and row.get("anchor_bbox_source") != "review_bbox":
    # Existing tracks predate manual box correction, so their propagated boxes are stale.
    return False
  try:
    expected = int(row.get("expected_speed_limit_mph", ""))
    reviewed_speed = int(parse_speed(reviewed_row.get("review_speed_limit_mph", "")) or 0)
    predicted = int(row.get("predicted_speed_limit_mph", "") or 0)
    read_confidence = float(row.get("read_confidence", "") or 0.0)
    detector_confidence = float(row.get("detector_confidence", "") or 0.0)
    tracking_confidence = float(row.get("tracking_confidence", "") or 0.0)
    growth = float(row.get("area_ratio_to_anchor", "") or 0.0)
    rank = int(row.get("rank", "") or 999)
  except ValueError:
    return False
  exact_read = predicted == expected and read_confidence >= args.min_exact_confidence
  detector_snap = detector_confidence >= args.min_detector_confidence
  optical_flow_track = tracking_confidence >= args.min_tracking_confidence
  return (
    expected == reviewed_speed and
    growth >= args.min_growth and
    rank <= args.max_track_rank and
    (exact_read or detector_snap or optical_flow_track)
  )


def add_sample(
  output: Path,
  split: str,
  stem: str,
  image_path: Path,
  bbox: tuple[int, int, int, int],
  repeats: int,
) -> int:
  label = yolo_label(bbox, image_path)
  if label is None:
    return 0
  created = 0
  for repeat in range(max(repeats, 1) if split == "train" else 1):
    suffix = f"_r{repeat:02d}" if split == "train" and repeats > 1 else ""
    destination_stem = f"{stem}{suffix}"
    destination_image = output / "images" / split / f"{destination_stem}{image_path.suffix.lower()}"
    destination_label = output / "labels" / split / f"{destination_stem}.txt"
    link_or_copy(image_path, destination_image)
    destination_label.parent.mkdir(parents=True, exist_ok=True)
    destination_label.write_text(label, encoding="ascii")
    created += 1
  return created


def add_reviewed_anchors(
  reviewed_rows: dict[str, dict[str, str]],
  output: Path,
  args: argparse.Namespace,
) -> Counter[str]:
  counts: Counter[str] = Counter()
  for record_key, row in reviewed_rows.items():
    speed = int(parse_speed(row.get("review_speed_limit_mph", "")) or 0)
    bbox = parse_bbox(row.get("review_bbox") or row.get("bbox", ""))
    image_path = Path(row.get("frame_path", "")).expanduser().resolve()
    if bbox is None or not image_path.is_file():
      counts["anchor_rejected"] += 1
      continue
    split = split_for_key(row.get("route") or record_key, args.train_ratio)
    repeats = args.important_repeat if speed in IMPORTANT_SPEEDS else args.other_repeat
    created = add_sample(output, split, f"anchor_{record_key}", image_path, bbox, repeats)
    counts[f"anchor_{split}"] += created
    counts[f"speed_{speed}"] += created
  return counts


def add_track_samples(
  reviewed_rows: dict[str, dict[str, str]],
  output: Path,
  args: argparse.Namespace,
) -> Counter[str]:
  counts: Counter[str] = Counter()
  with args.track_samples.expanduser().resolve().open(encoding="utf-8", newline="") as input_file:
    for row in csv.DictReader(input_file):
      reviewed_row = reviewed_row_for_track(row, reviewed_rows)
      if reviewed_row is None or not trusted_track_row(row, reviewed_row, args):
        counts["track_rejected"] += 1
        continue
      bbox = parse_bbox(row.get("bbox", ""))
      image_path = Path(row.get("frame_path", "")).expanduser().resolve()
      if bbox is None or not image_path.is_file():
        counts["track_rejected"] += 1
        continue
      speed = int(row["expected_speed_limit_mph"])
      split = split_for_key(row.get("route") or row.get("track_key", ""), args.train_ratio)
      repeats = args.important_repeat if speed in IMPORTANT_SPEEDS else args.other_repeat
      stem = f"track_{row.get('track_key', '')}_{row.get('rank', '')}_{row.get('frame_time_s', '').replace('.', 'p')}"
      created = add_sample(output, split, stem, image_path, bbox, repeats)
      counts[f"track_{split}"] += created
      counts[f"speed_{speed}"] += created
  return counts


def resolved_dataset_paths(base_yaml: Path, key: str) -> list[str]:
  data = yaml.safe_load(base_yaml.read_text(encoding="utf-8")) or {}
  base_root = Path(data.get("path", base_yaml.parent)).expanduser()
  if not base_root.is_absolute():
    base_root = (base_yaml.parent / base_root).resolve()
  entries = data.get(key, [])
  if isinstance(entries, str):
    entries = [entries]
  return [str((base_root / entry).resolve()) if not Path(entry).is_absolute() else str(Path(entry).resolve()) for entry in entries]


def write_dataset_yaml(base_yaml: Path, output: Path) -> Path:
  train_paths = (*resolved_dataset_paths(base_yaml, "train"), str((output / "images" / "train").resolve()))
  val_paths = (*resolved_dataset_paths(base_yaml, "val"), str((output / "images" / "val").resolve()))
  lines = ["train:", *(f"  - {path}" for path in train_paths), "val:", *(f"  - {path}" for path in val_paths), "names:", "  0: speed_limit_sign"]
  dataset_yaml = output / "dataset.yaml"
  dataset_yaml.write_text("\n".join(lines) + "\n", encoding="ascii")
  return dataset_yaml


def main() -> int:
  args = parse_args()
  if not 0.0 < args.train_ratio < 1.0:
    raise ValueError("--train-ratio must be between zero and one")
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  output = args.output.expanduser().resolve()
  for split in ("train", "val"):
    (output / "images" / split).mkdir(parents=True, exist_ok=True)
    (output / "labels" / split).mkdir(parents=True, exist_ok=True)

  selected_record_keys = focus_record_keys(args.focus_eval_csv, args.focus_outcome) if args.focus_eval_csv else None
  reviewed_rows = reviewed_positive_rows(queue_path, labels_path, selected_record_keys)
  if args.focus_train_only:
    reviewed_rows = {
      key: row
      for key, row in reviewed_rows.items()
      if split_for_key(row.get("route") or key, args.train_ratio) == "train"
    }
  counts = add_reviewed_anchors(reviewed_rows, output, args)
  counts.update(add_track_samples(reviewed_rows, output, args))
  dataset_yaml = write_dataset_yaml(args.base_yaml.expanduser().resolve(), output)
  summary = {
    "accepted_source_records": len(reviewed_rows),
    "base_yaml": str(args.base_yaml.expanduser().resolve()),
    "dataset_yaml": str(dataset_yaml),
    "focus_eval_csv": str(args.focus_eval_csv.expanduser().resolve()) if args.focus_eval_csv else None,
    "focus_outcome": args.focus_outcome if args.focus_eval_csv else None,
    "focus_train_only": args.focus_train_only,
    "output": str(output),
    "counts": dict(sorted(counts.items())),
  }
  (output / "track_proposal_dataset_summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="ascii")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
