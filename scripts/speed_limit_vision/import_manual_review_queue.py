#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import shutil

from pathlib import Path

import cv2

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace  # type: ignore
else:
  from .common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace


CLASSIFIER_FIELDNAMES = [
  "record_key",
  "split",
  "speed_limit_mph",
  "review_sign_type",
  "crop_path",
  "frame_path",
  "bbox",
  "crop_bbox",
  "review_status",
  "candidate_speed_limit_mph",
  "candidate_confidence",
  "detector_class",
]

RUNTIME_FIELDNAMES = [
  "record_key",
  "split",
  "sample_type",
  "dataset_image",
  "speed_limit_mph",
  "review_status",
  "review_sign_type",
  "detector_class",
  "candidate_speed_limit_mph",
  "candidate_confidence",
]

DETECTOR_MANIFEST_FIELDNAMES = [
  "record_key",
  "split",
  "sample_type",
  "speed_limit_mph",
  "review_sign_type",
  "source_frame",
  "dataset_image",
  "dataset_label",
  "bbox",
  "class_id",
  "review_status",
  "detector_class",
]

POSITIVE_STATUSES = {"accepted", "corrected"}
UNCERTAIN_STATUS = "uncertain"
NEGATIVE_STATUS = "ignore"
SIGN_TYPE_CLASS_IDS = {
  "regulatory": 0,
  "advisory": 1,
  "school_zone": 2,
  "construction": 0,
}


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Import manually reviewed speed-limit rows into training/eval manifests.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--queue", type=Path, required=True, help="manual_review_queue.csv from build_manual_review_queue.py.")
  parser.add_argument("--labels", type=Path, help="manual_review_labels.csv. Defaults to <queue_dir>/manual_review_labels.csv.")
  parser.add_argument("--classifier-manifest-out", type=Path, help="Positive crop manifest for import_manifest_classifier_masks.py.")
  parser.add_argument("--runtime-manifest-out", type=Path, help="Full-frame eval manifest including positives and true negatives.")
  parser.add_argument("--detector-manifest-out", type=Path, help="Manifest of imported detector examples.")
  parser.add_argument("--source-name", default="manual_review", help="Filename prefix for detector dataset imports.")
  parser.add_argument("--mode", choices=("symlink", "copy"), default="symlink", help="How to place detector images.")
  parser.add_argument("--val-modulo", type=int, default=5, help="Hash modulo for validation split. 0 sends everything to train.")
  parser.add_argument("--val-remainder", type=int, default=0, help="Hash remainder used as validation split.")
  parser.add_argument("--max-detector-negatives", type=int, default=0, help="Cap true negative detector imports. 0 keeps all.")
  parser.add_argument("--overwrite", action="store_true", help="Replace existing detector image links/files and labels.")
  return parser.parse_args()


def read_csv(path: Path) -> list[dict[str, str]]:
  with path.open("r", encoding="utf-8", newline="") as handle:
    return list(csv.DictReader(handle))


def write_csv(path: Path, fieldnames: list[str], rows: list[dict[str, object]]) -> None:
  ensure_dir(path.parent)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(rows)


def split_for_key(key: str, val_modulo: int, val_remainder: int) -> str:
  if val_modulo <= 0:
    return "train"
  digest = hashlib.sha1(key.encode("utf-8")).hexdigest()
  return "val" if int(digest[:8], 16) % val_modulo == val_remainder else "train"


def parse_speed(text: str) -> int:
  text = (text or "").strip()
  if not text:
    return 0
  try:
    value = int(float(text))
  except ValueError:
    return 0
  return value if value in DEFAULT_SPEED_VALUES else 0


def parse_bbox(text: str) -> tuple[int, int, int, int] | None:
  parts = [part.strip() for part in (text or "").replace(";", ",").split(",") if part.strip()]
  if len(parts) != 4:
    return None
  try:
    x1, y1, x2, y2 = (int(round(float(part))) for part in parts)
  except ValueError:
    return None
  if x2 <= x1 or y2 <= y1:
    return None
  return x1, y1, x2, y2


def detector_class_id(row: dict[str, str]) -> int:
  sign_type = effective_sign_type(row)
  if sign_type in SIGN_TYPE_CLASS_IDS:
    return SIGN_TYPE_CLASS_IDS[sign_type]

  class_text = (row.get("class_id") or "").strip()
  if class_text.isdigit():
    class_id = int(class_text)
    if class_id in (0, 1, 2):
      return class_id

  detector_class = row.get("detector_class", "")
  if detector_class == "school_zone_speed_limit":
    return 2
  if detector_class == "advisory_speed_limit":
    return 1
  return 0


def effective_sign_type(row: dict[str, str]) -> str:
  sign_type = (row.get("review_sign_type") or "").strip()
  if sign_type and sign_type != "not_speed_limit":
    return sign_type

  detector_class = row.get("detector_class", "")
  if detector_class == "school_zone_speed_limit":
    return "school_zone"
  if detector_class == "advisory_speed_limit":
    return "advisory"
  if detector_class == "negative_empty":
    return "not_speed_limit"
  return "regulatory"


def detector_label_line(class_id: int, bbox: tuple[int, int, int, int], image_shape: tuple[int, int, int]) -> str:
  image_h, image_w = image_shape[:2]
  x1, y1, x2, y2 = bbox
  x_center = ((x1 + x2) / 2) / image_w
  y_center = ((y1 + y2) / 2) / image_h
  width = (x2 - x1) / image_w
  height = (y2 - y1) / image_h
  return f"{class_id} {x_center:.6f} {y_center:.6f} {width:.6f} {height:.6f}\n"


def stage_image(source_path: Path, dest_path: Path, mode: str, overwrite: bool) -> None:
  ensure_dir(dest_path.parent)
  if dest_path.exists() or dest_path.is_symlink():
    if not overwrite:
      return
    dest_path.unlink()
  if mode == "copy":
    shutil.copy2(source_path, dest_path)
  else:
    dest_path.symlink_to(source_path.resolve())


def safe_stem(text: str) -> str:
  keep = []
  for char in text:
    keep.append(char if char.isalnum() or char in "._-" else "_")
  cleaned = "".join(keep).strip("._")
  return cleaned[:180] or "sample"


def merged_review_rows(queue_path: Path, labels_path: Path) -> list[dict[str, str]]:
  queue_rows = read_csv(queue_path)
  labels_by_key = {row["record_key"]: row for row in read_csv(labels_path) if row.get("record_key")}
  merged = []
  for row in queue_rows:
    label = labels_by_key.get(row.get("record_key", ""))
    if not label:
      continue
    item = dict(row)
    item.update({
      "review_status": label.get("review_status", ""),
      "review_speed_limit_mph": label.get("review_speed_limit_mph", ""),
      "review_sign_type": label.get("review_sign_type", ""),
      "review_bbox": label.get("review_bbox", ""),
      "review_ignore_reason": label.get("review_ignore_reason", ""),
      "review_notes": label.get("review_notes", ""),
    })
    merged.append(item)
  return merged


def is_positive(row: dict[str, str]) -> bool:
  if row.get("review_status") not in POSITIVE_STATUSES:
    return False
  if not parse_speed(row.get("review_speed_limit_mph", "")):
    return False
  return Path(row.get("crop_path", "")).is_file() and Path(row.get("frame_path", "")).is_file()


def is_uncertain_positive(row: dict[str, str]) -> bool:
  if row.get("review_status") != UNCERTAIN_STATUS:
    return False
  if not parse_speed(row.get("review_speed_limit_mph", "")):
    return False
  return Path(row.get("frame_path", "")).is_file()


def is_true_negative(row: dict[str, str]) -> bool:
  if row.get("review_status") != NEGATIVE_STATUS:
    return False
  if row.get("detector_class") != "negative_empty":
    return False
  return Path(row.get("frame_path", "")).is_file()


def positive_classifier_row(row: dict[str, str], split: str) -> dict[str, object]:
  speed = parse_speed(row.get("review_speed_limit_mph", ""))
  return {
    "record_key": row["record_key"],
    "split": split,
    "speed_limit_mph": speed,
    "review_sign_type": effective_sign_type(row),
    "crop_path": row.get("crop_path", ""),
    "frame_path": row.get("frame_path", ""),
    "bbox": row.get("bbox", ""),
    "crop_bbox": row.get("crop_bbox", ""),
    "review_status": row.get("review_status", ""),
    "candidate_speed_limit_mph": row.get("candidate_speed_limit_mph", ""),
    "candidate_confidence": row.get("candidate_confidence", ""),
    "detector_class": row.get("detector_class", ""),
  }


def runtime_row(row: dict[str, str], split: str, sample_type: str) -> dict[str, object]:
  speed = parse_speed(row.get("review_speed_limit_mph", "")) if sample_type in ("positive", "uncertain_positive") else 0
  return {
    "record_key": row["record_key"],
    "split": split,
    "sample_type": sample_type,
    "dataset_image": row.get("frame_path", ""),
    "speed_limit_mph": "" if speed == 0 else speed,
    "review_status": row.get("review_status", ""),
    "review_sign_type": effective_sign_type(row),
    "detector_class": row.get("detector_class", ""),
    "candidate_speed_limit_mph": row.get("candidate_speed_limit_mph", ""),
    "candidate_confidence": row.get("candidate_confidence", ""),
  }


def import_detector_example(
  workspace: Path,
  row: dict[str, str],
  split: str,
  source_name: str,
  sample_type: str,
  mode: str,
  overwrite: bool,
) -> dict[str, object] | None:
  source_frame = Path(row.get("frame_path", "")).expanduser()
  if not source_frame.is_file():
    return None

  stem = f"{safe_stem(source_name)}_{safe_stem(row['record_key'])}"
  image_path = workspace / "detector" / "images" / split / f"{stem}{source_frame.suffix.lower() or '.jpg'}"
  label_path = workspace / "detector" / "labels" / split / f"{stem}.txt"
  stage_image(source_frame, image_path, mode, overwrite)
  ensure_dir(label_path.parent)

  class_id = ""
  bbox_text = ""
  if sample_type == "positive":
    bbox = parse_bbox(row.get("review_bbox") or row.get("bbox", ""))
    if bbox is None:
      return None
    image = cv2.imread(str(source_frame))
    if image is None:
      return None
    class_id_int = detector_class_id(row)
    label_path.write_text(detector_label_line(class_id_int, bbox, image.shape), encoding="utf-8")
    class_id = str(class_id_int)
    bbox_text = ",".join(str(value) for value in bbox)
  else:
    label_path.write_text("", encoding="utf-8")

  return {
    "record_key": row["record_key"],
    "split": split,
    "sample_type": sample_type,
    "speed_limit_mph": parse_speed(row.get("review_speed_limit_mph", "")) if sample_type == "positive" else "",
    "review_sign_type": effective_sign_type(row),
    "source_frame": str(source_frame),
    "dataset_image": str(image_path),
    "dataset_label": str(label_path),
    "bbox": bbox_text,
    "class_id": class_id,
    "review_status": row.get("review_status", ""),
    "detector_class": row.get("detector_class", ""),
  }


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  queue_path = args.queue.expanduser().resolve()
  labels_path = args.labels.expanduser().resolve() if args.labels else queue_path.with_name("manual_review_labels.csv")
  output_dir = queue_path.parent
  classifier_manifest = args.classifier_manifest_out.expanduser().resolve() if args.classifier_manifest_out else output_dir / "manual_review_classifier_manifest.csv"
  runtime_manifest = args.runtime_manifest_out.expanduser().resolve() if args.runtime_manifest_out else output_dir / "manual_review_runtime_eval_manifest.csv"
  detector_manifest = args.detector_manifest_out.expanduser().resolve() if args.detector_manifest_out else output_dir / "manual_review_detector_import_manifest.csv"

  rows = merged_review_rows(queue_path, labels_path)
  positive_rows = [row for row in rows if is_positive(row)]
  uncertain_positive_rows = [row for row in rows if is_uncertain_positive(row)]
  true_negative_rows = [row for row in rows if is_true_negative(row)]
  if args.max_detector_negatives > 0:
    true_negative_rows = true_negative_rows[:args.max_detector_negatives]

  classifier_rows: list[dict[str, object]] = []
  runtime_rows: list[dict[str, object]] = []
  detector_rows: list[dict[str, object]] = []

  for row in positive_rows:
    split = split_for_key(row["record_key"], args.val_modulo, args.val_remainder)
    classifier_rows.append(positive_classifier_row(row, split))
    runtime_rows.append(runtime_row(row, split, "positive"))
    detector_row = import_detector_example(workspace, row, split, args.source_name, "positive", args.mode, args.overwrite)
    if detector_row is not None:
      detector_rows.append(detector_row)

  for row in uncertain_positive_rows:
    split = split_for_key(row["record_key"], args.val_modulo, args.val_remainder)
    runtime_rows.append(runtime_row(row, split, "uncertain_positive"))

  for row in true_negative_rows:
    split = split_for_key(row["record_key"], args.val_modulo, args.val_remainder)
    runtime_rows.append(runtime_row(row, split, "negative_empty"))
    detector_row = import_detector_example(workspace, row, split, args.source_name, "negative_empty", args.mode, args.overwrite)
    if detector_row is not None:
      detector_rows.append(detector_row)

  write_csv(classifier_manifest, CLASSIFIER_FIELDNAMES, classifier_rows)
  write_csv(runtime_manifest, RUNTIME_FIELDNAMES, runtime_rows)
  write_csv(detector_manifest, DETECTOR_MANIFEST_FIELDNAMES, detector_rows)

  summary = {
    "queue": str(queue_path),
    "labels": str(labels_path),
    "reviewed_rows": len(rows),
    "positive_rows": len(positive_rows),
    "uncertain_positive_rows": len(uncertain_positive_rows),
    "true_negative_rows": len(true_negative_rows),
    "classifier_manifest": str(classifier_manifest),
    "runtime_manifest": str(runtime_manifest),
    "detector_manifest": str(detector_manifest),
    "detector_imported": len(detector_rows),
  }
  summary_path = output_dir / "manual_review_import_summary.json"
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")

  print(
    "Imported manual review queue: "
    f"reviewed={len(rows)} positives={len(positive_rows)} uncertain_positives={len(uncertain_positive_rows)} true_negatives={len(true_negative_rows)} "
    f"detector_imported={len(detector_rows)}"
  )
  print(f"Classifier manifest: {classifier_manifest}")
  print(f"Runtime eval manifest: {runtime_manifest}")
  print(f"Detector import manifest: {detector_manifest}")
  print(f"Summary: {summary_path}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
