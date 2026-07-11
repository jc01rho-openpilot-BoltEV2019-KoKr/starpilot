#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import re

from collections import Counter, defaultdict
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import DEFAULT_WORKSPACE, DETECTOR_CLASS_NAMES, REPO_ASSET_DIR, ensure_dir, resolve_workspace  # type: ignore
  from rebalance_detector_dataset import link_or_copy, remove_appledouble_files, safe_unlink, write_dataset_yaml, visible_file_count  # type: ignore
else:
  from .common import DEFAULT_WORKSPACE, DETECTOR_CLASS_NAMES, REPO_ASSET_DIR, ensure_dir, resolve_workspace
  from .rebalance_detector_dataset import link_or_copy, remove_appledouble_files, safe_unlink, write_dataset_yaml, visible_file_count


DEFAULT_OLD_QUEUES = (
  "manual_review_queue_v1_initial10_fast",
  "manual_review_queue_v2_classifier_v1",
  "manual_review_queue_v3_diverse",
  "manual_review_queue_v4_diverse",
  "manual_review_queue_v5_diverse",
  "manual_review_queue_v6_clearer",
  "manual_review_queue_v7_regulatory_clear_filtered",
)
DEFAULT_BOX_QUEUE = "manual_detector_box_review_v1"
TREE_EVAL_NAME = "tree_promoted_threshold07_runtime_eval.csv"
RUNTIME_MANIFEST_NAME = "manual_review_runtime_eval_manifest.csv"
MANUAL_QUEUE_NAME = "manual_review_queue.csv"
MANUAL_LABELS_NAME = "manual_review_labels.csv"
IMPORTANT_SPEEDS = set(range(30, 70, 5))

SIGN_TYPE_TO_CLASS_ID = {
  "regulatory": 0,
  "regulatory_speed_limit": 0,
  "advisory": 1,
  "advisory_speed_limit": 1,
  "school": 2,
  "school_zone": 2,
  "school_zone_speed_limit": 2,
}

MANUAL_SKIP_STATUSES = {"ignore", "ignored", "needs_later"}
MANUAL_SKIP_SIGN_TYPES = {"not_speed_limit", "not_speed", "none", "no_sign"}


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Build a detector dataset that preserves current-correct reviews while adding manual box fixes.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--base-dataset", type=Path, help="Existing YOLO dataset to include before preservation samples.")
  parser.add_argument("--output-root", type=Path, help="Output YOLO dataset root.")
  parser.add_argument("--models-dir", type=Path, default=REPO_ASSET_DIR, help="Current tree ONNX model directory.")
  parser.add_argument("--old-queue", action="append", dest="old_queues", default=[], help="Reviewed queue name to preserve. Repeatable.")
  parser.add_argument("--box-queue", default=DEFAULT_BOX_QUEUE, help="Manual detector-box review queue name.")
  parser.add_argument("--manual-queue", action="append", dest="manual_queues", default=[], help="Manual detector-box review queue name to include. Repeatable.")
  parser.add_argument("--manual-repeat", type=int, default=2, help="Train-time repeats for manual box positives outside 30-65 mph.")
  parser.add_argument("--manual-important-repeat", type=int, default=3, help="Train-time repeats for manual box positives in 30-65 mph.")
  parser.add_argument("--manual-negative-repeat", type=int, default=0, help="Train-time repeats for ignored/not-speed-limit manual review rows as empty-label negatives.")
  parser.add_argument("--pseudo-repeat", type=int, default=1, help="Train-time repeats for current-tree exact pseudo positives.")
  parser.add_argument("--negative-repeat", type=int, default=1, help="Train-time repeats for old reviewed negatives.")
  parser.add_argument("--hard-negative-eval", action="append", default=[], type=Path, help="Runtime eval CSV whose false positives should be repeated as train negatives.")
  parser.add_argument("--hard-negative-repeat", type=int, default=1, help="Train-time repeats for false positives from --hard-negative-eval.")
  parser.add_argument("--include-val-hard-negatives", action="store_true", help="Also train on false positives whose source split was val.")
  parser.add_argument("--copy", action="store_true", help="Copy images/labels instead of symlinking.")
  return parser.parse_args()


def load_csv(path: Path) -> list[dict[str, str]]:
  if not path.is_file():
    return []
  with path.open("r", encoding="utf-8", newline="") as csv_file:
    return list(csv.DictReader(csv_file))


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
    if "@" in read_text:
      value = int_value(read_text.split("@", 1)[0])
      if value is not None:
        return value
  return None


def is_negative(row: dict[str, str]) -> bool:
  sample_type = row.get("sample_type", "").lower()
  if "negative" in sample_type:
    return True
  return expected_value(row) is None


def parse_bool(text: str) -> bool:
  return text.strip().lower() in ("1", "true", "yes")


def class_id_from_row(row: dict[str, str]) -> int:
  sign_type = first_present(row, ("review_sign_type", "detector_class"))
  return SIGN_TYPE_TO_CLASS_ID.get(sign_type.strip().lower(), 0)


def parse_bbox(text: str) -> tuple[int, int, int, int] | None:
  parts = [part.strip() for part in text.split(",")]
  if len(parts) != 4:
    return None
  try:
    x1, y1, x2, y2 = (int(round(float(part))) for part in parts)
  except ValueError:
    return None
  if x2 <= x1 or y2 <= y1:
    return None
  return x1, y1, x2, y2


def clamp_bbox(bbox: tuple[int, int, int, int], width: int, height: int) -> tuple[int, int, int, int] | None:
  x1, y1, x2, y2 = bbox
  x1 = max(min(x1, width - 1), 0)
  y1 = max(min(y1, height - 1), 0)
  x2 = max(min(x2, width), 0)
  y2 = max(min(y2, height), 0)
  if x2 <= x1 or y2 <= y1:
    return None
  return x1, y1, x2, y2


def yolo_label(class_id: int, bbox: tuple[int, int, int, int], image_width: int, image_height: int) -> str:
  x1, y1, x2, y2 = bbox
  center_x = ((x1 + x2) / 2) / image_width
  center_y = ((y1 + y2) / 2) / image_height
  width = (x2 - x1) / image_width
  height = (y2 - y1) / image_height
  return f"{class_id} {center_x:.6f} {center_y:.6f} {width:.6f} {height:.6f}\n"


def sanitize_name(text: str) -> str:
  sanitized = re.sub(r"[^A-Za-z0-9_.-]+", "_", text.strip())
  return sanitized[:180] or "sample"


def prepare_output(root: Path) -> None:
  for split in ("train", "val"):
    image_dir = ensure_dir(root / "images" / split)
    label_dir = ensure_dir(root / "labels" / split)
    for existing in image_dir.glob("*"):
      safe_unlink(existing)
    for existing in label_dir.glob("*"):
      safe_unlink(existing)


def add_sample(
  output_root: Path,
  split: str,
  name: str,
  image_path: Path,
  label_text: str,
  copy_files: bool,
) -> bool:
  if split not in ("train", "val"):
    split = "train"
  if not image_path.is_file():
    return False

  suffix = image_path.suffix or ".jpg"
  image_name = f"{name}{suffix}"
  label_name = f"{name}.txt"
  image_dst = output_root / "images" / split / image_name
  label_dst = output_root / "labels" / split / label_name
  link_or_copy(image_path, image_dst, copy_files)
  ensure_dir(label_dst.parent)
  label_dst.write_text(label_text, encoding="utf-8")
  return True


def include_base_dataset(base_dataset: Path, output_root: Path, copy_files: bool, stats: Counter[str]) -> None:
  for split in ("train", "val"):
    source_image_dir = base_dataset / "images" / split
    source_label_dir = base_dataset / "labels" / split
    if not source_image_dir.is_dir() or not source_label_dir.is_dir():
      continue
    for image_path in sorted(source_image_dir.glob("*")):
      if not image_path.is_file() or image_path.name.startswith("._"):
        continue
      label_path = source_label_dir / f"{image_path.stem}.txt"
      if not label_path.is_file():
        continue
      link_or_copy(image_path, output_root / "images" / split / image_path.name, copy_files)
      link_or_copy(label_path, output_root / "labels" / split / label_path.name, copy_files)
      stats[f"base_{split}"] += 1


def classify_expanded_proposal(
  daemon: slv.SpeedLimitVisionDaemon,
  frame_bgr,
  bbox: tuple[int, int, int, int],
) -> set[int]:
  frame_height, frame_width = frame_bgr.shape[:2]
  x1, y1, x2, y2 = bbox
  box_width = x2 - x1
  box_height = y2 - y1
  reads: set[int] = set()
  for expand_left, expand_top, expand_right, expand_bottom, _expansion_weight in slv.DETECTOR_CLASSIFIER_EXPANSIONS:
    expanded_x1 = max(int(x1 - box_width * expand_left), 0)
    expanded_y1 = max(int(y1 - box_height * expand_top), 0)
    expanded_x2 = min(int(x2 + box_width * expand_right), frame_width)
    expanded_y2 = min(int(y2 + box_height * expand_bottom), frame_height)
    crop = frame_bgr[expanded_y1:expanded_y2, expanded_x1:expanded_x2]
    if crop.size == 0:
      continue
    model_read = daemon._classify_speed_limit_from_model(crop)
    ocr_read = daemon._read_speed_limit_from_crop(crop)
    if model_read is not None:
      reads.add(int(model_read[0]))
    if ocr_read is not None:
      reads.add(int(ocr_read[0]))
  return reads


def select_current_tree_bbox(
  daemon: slv.SpeedLimitVisionDaemon,
  frame_bgr,
  expected_speed: int,
  target_class_id: int,
) -> tuple[int, int, int, int] | None:
  proposals = daemon._collect_detector_classifier_proposals(frame_bgr)
  if not proposals:
    return None

  same_class = []
  exact_read = []
  for confidence, class_id, bbox in proposals:
    proposal = (float(confidence), int(class_id), bbox)
    if int(class_id) == target_class_id:
      same_class.append(proposal)
    reads = classify_expanded_proposal(daemon, frame_bgr, bbox)
    if expected_speed in reads:
      exact_read.append(proposal)

  for pool in (
    [proposal for proposal in exact_read if proposal[1] == target_class_id],
    exact_read,
    same_class,
    [(float(confidence), int(class_id), bbox) for confidence, class_id, bbox in proposals],
  ):
    if pool:
      return max(pool, key=lambda proposal: proposal[0])[2]
  return None


def load_eval_by_record(eval_path: Path) -> dict[str, dict[str, str]]:
  return {row.get("record_key", ""): row for row in load_csv(eval_path)}


def add_old_queue_samples(
  workspace: Path,
  output_root: Path,
  queue_name: str,
  daemon: slv.SpeedLimitVisionDaemon,
  copy_files: bool,
  pseudo_repeat: int,
  negative_repeat: int,
  stats: Counter[str],
  class_stats: Counter[str],
) -> None:
  queue_root = workspace / "review" / queue_name
  manifest_rows = load_csv(queue_root / RUNTIME_MANIFEST_NAME)
  eval_by_record = load_eval_by_record(queue_root / TREE_EVAL_NAME)
  if not manifest_rows:
    stats[f"{queue_name}_missing_manifest"] += 1
    return

  for row_index, row in enumerate(manifest_rows):
    record_key = row.get("record_key", "")
    eval_row = eval_by_record.get(record_key, {})
    split = row.get("split", "train").strip() or "train"
    image_text = first_present(row, ("dataset_image", "frame_path", "source_frame"))
    if not image_text:
      stats[f"{queue_name}_missing_image"] += 1
      continue
    image_path = Path(image_text).expanduser().resolve()

    if is_negative(row):
      repeats = max(negative_repeat, 1) if split == "train" else 1
      for repeat_index in range(repeats):
        name = sanitize_name(f"preserve_negative_{queue_name}_{row_index:05d}_{repeat_index}_{record_key}")
        if add_sample(output_root, split, name, image_path, "", copy_files):
          stats[f"old_negative_{split}"] += 1
      continue

    expected = expected_value(row)
    predicted = int_value(eval_row.get("predicted_speed_limit_mph", ""))
    negative_eval = parse_bool(eval_row.get("negative", "False"))
    if expected is None or predicted != expected or negative_eval:
      stats[f"{queue_name}_positive_not_current_exact"] += 1
      continue

    frame_bgr = cv2.imread(str(image_path))
    if frame_bgr is None:
      stats[f"{queue_name}_unreadable_image"] += 1
      continue
    image_height, image_width = frame_bgr.shape[:2]
    class_id = class_id_from_row(row)
    bbox = select_current_tree_bbox(daemon, frame_bgr, expected, class_id)
    if bbox is None:
      stats[f"{queue_name}_missing_pseudo_bbox"] += 1
      continue
    bbox = clamp_bbox(bbox, image_width, image_height)
    if bbox is None:
      stats[f"{queue_name}_invalid_pseudo_bbox"] += 1
      continue

    label_text = yolo_label(class_id, bbox, image_width, image_height)
    repeats = max(pseudo_repeat, 1) if split == "train" else 1
    for repeat_index in range(repeats):
      name = sanitize_name(f"preserve_exact_{queue_name}_{row_index:05d}_{repeat_index}_{record_key}")
      if add_sample(output_root, split, name, image_path, label_text, copy_files):
        stats[f"old_pseudo_positive_{split}"] += 1
        class_stats[f"old_pseudo_{DETECTOR_CLASS_NAMES[class_id]}_{split}"] += 1


def add_manual_box_samples(
  workspace: Path,
  output_root: Path,
  queue_name: str,
  copy_files: bool,
  manual_repeat: int,
  manual_important_repeat: int,
  manual_negative_repeat: int,
  stats: Counter[str],
  class_stats: Counter[str],
) -> None:
  queue_root = workspace / "review" / queue_name
  queue_by_record = {row.get("record_key", ""): row for row in load_csv(queue_root / MANUAL_QUEUE_NAME)}
  manifest_by_record = {row.get("record_key", ""): row for row in load_csv(queue_root / RUNTIME_MANIFEST_NAME)}
  label_rows = load_csv(queue_root / MANUAL_LABELS_NAME)
  if not label_rows:
    stats[f"{queue_name}_missing_labels"] += 1
    return

  for row_index, label_row in enumerate(label_rows):
    record_key = label_row.get("record_key", "")
    queue_row = queue_by_record.get(record_key, {})
    manifest_row = manifest_by_record.get(record_key, {})
    merged = dict(queue_row)
    merged.update(manifest_row)
    merged.update({key: value for key, value in label_row.items() if value.strip()})

    review_status = merged.get("review_status", "").strip().lower()
    review_sign_type = merged.get("review_sign_type", "").strip().lower()
    if review_status in MANUAL_SKIP_STATUSES or review_sign_type in MANUAL_SKIP_SIGN_TYPES:
      stats["manual_ignored"] += 1
      if manual_negative_repeat > 0:
        image_text = first_present(merged, ("frame_path", "dataset_image", "source_frame"))
        if not image_text:
          stats["manual_ignored_missing_image"] += 1
          continue
        image_path = Path(image_text).expanduser().resolve()
        for repeat_index in range(manual_negative_repeat):
          name = sanitize_name(f"manual_ignored_negative_{queue_name}_{row_index:05d}_{repeat_index}_{record_key}")
          if add_sample(output_root, "train", name, image_path, "", copy_files):
            stats["manual_ignored_negative_train"] += 1
      continue

    speed = expected_value(merged)
    if speed is None:
      stats["manual_missing_speed"] += 1
      continue

    image_text = first_present(merged, ("frame_path", "dataset_image", "source_frame"))
    if not image_text:
      stats["manual_missing_image"] += 1
      continue
    image_path = Path(image_text).expanduser().resolve()
    frame_bgr = cv2.imread(str(image_path))
    if frame_bgr is None:
      stats["manual_unreadable_image"] += 1
      continue
    image_height, image_width = frame_bgr.shape[:2]

    bbox = parse_bbox(first_present(merged, ("review_bbox", "bbox", "crop_bbox")))
    if bbox is None:
      stats["manual_missing_bbox"] += 1
      continue
    bbox = clamp_bbox(bbox, image_width, image_height)
    if bbox is None:
      stats["manual_invalid_bbox"] += 1
      continue

    split = merged.get("split", "train").strip() or "train"
    class_id = class_id_from_row(merged)
    label_text = yolo_label(class_id, bbox, image_width, image_height)
    repeats = 1
    if split == "train":
      repeats = max(manual_important_repeat if speed in IMPORTANT_SPEEDS else manual_repeat, 1)
    for repeat_index in range(repeats):
      name = sanitize_name(f"manual_box_{queue_name}_{row_index:05d}_{repeat_index}_{record_key}")
      if add_sample(output_root, split, name, image_path, label_text, copy_files):
        stats[f"manual_positive_{split}"] += 1
        class_stats[f"manual_{DETECTOR_CLASS_NAMES[class_id]}_{split}"] += 1
        if speed in IMPORTANT_SPEEDS:
          stats[f"manual_important_{split}"] += 1


def add_hard_negative_samples(
  output_root: Path,
  eval_path: Path,
  copy_files: bool,
  hard_negative_repeat: int,
  include_val_hard_negatives: bool,
  stats: Counter[str],
) -> None:
  rows = load_csv(eval_path)
  if not rows:
    stats["hard_negative_missing_eval"] += 1
    return

  seen_images: set[str] = set()
  for row_index, row in enumerate(rows):
    expected = int_value(row.get("expected_speed_limit_mph", ""))
    predicted = int_value(row.get("predicted_speed_limit_mph", ""))
    negative = parse_bool(row.get("negative", "False")) or expected is None
    if not negative or predicted is None:
      continue

    source_split = row.get("split", "train").strip() or "train"
    if source_split == "val" and not include_val_hard_negatives:
      stats["hard_negative_skipped_val"] += 1
      continue

    image_text = first_present(row, ("image_path", "dataset_image", "frame_path", "source_frame"))
    if not image_text:
      stats["hard_negative_missing_image"] += 1
      continue
    image_path = Path(image_text).expanduser().resolve()
    image_key = str(image_path)
    if image_key in seen_images:
      stats["hard_negative_duplicate"] += 1
      continue
    seen_images.add(image_key)

    repeats = max(hard_negative_repeat, 1)
    for repeat_index in range(repeats):
      name = sanitize_name(f"hard_negative_{eval_path.stem}_{row_index:05d}_{repeat_index}_{row.get('record_key', '')}")
      if add_sample(output_root, "train", name, image_path, "", copy_files):
        stats["hard_negative_train"] += 1


def print_stats(output_root: Path, stats: Counter[str], class_stats: Counter[str]) -> None:
  print(f"Created preservation detector dataset at {output_root}")
  print(f"Dataset YAML: {output_root / 'dataset.yaml'}")
  print(f"Train images: {visible_file_count(output_root / 'images' / 'train')}")
  print(f"Val images: {visible_file_count(output_root / 'images' / 'val')}")
  print("Sample stats:")
  for key, count in sorted(stats.items()):
    print(f"  {key}: {count}")
  print("Class stats:")
  for key, count in sorted(class_stats.items()):
    print(f"  {key}: {count}")


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  output_root = args.output_root.expanduser().resolve() if args.output_root else workspace / "detector_preserve_box_v1"
  base_dataset = args.base_dataset.expanduser().resolve() if args.base_dataset else workspace / "detector_rebalanced_box_v1"
  old_queues = tuple(args.old_queues) if args.old_queues else DEFAULT_OLD_QUEUES

  prepare_output(output_root)
  stats: Counter[str] = Counter()
  class_stats: Counter[str] = Counter()

  if base_dataset.is_dir():
    include_base_dataset(base_dataset, output_root, args.copy, stats)
  else:
    stats["missing_base_dataset"] += 1

  models_dir = args.models_dir.expanduser().resolve()
  slv.US_DETECTOR_MODEL_PATH = models_dir / "speed_limit_us_detector.onnx"
  slv.US_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_value_classifier.onnx"
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)

  for queue_name in old_queues:
    add_old_queue_samples(
      workspace,
      output_root,
      queue_name,
      daemon,
      args.copy,
      args.pseudo_repeat,
      args.negative_repeat,
      stats,
      class_stats,
    )

  manual_queues = tuple(args.manual_queues) if args.manual_queues else (args.box_queue,)
  for queue_name in manual_queues:
    add_manual_box_samples(
      workspace,
      output_root,
      queue_name,
      args.copy,
      args.manual_repeat,
      args.manual_important_repeat,
      args.manual_negative_repeat,
      stats,
      class_stats,
    )

  for eval_path in args.hard_negative_eval:
    add_hard_negative_samples(
      output_root,
      eval_path.expanduser().resolve(),
      args.copy,
      args.hard_negative_repeat,
      args.include_val_hard_negatives,
      stats,
    )

  remove_appledouble_files(output_root)
  write_dataset_yaml(output_root)
  print_stats(output_root, stats, class_stats)
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
