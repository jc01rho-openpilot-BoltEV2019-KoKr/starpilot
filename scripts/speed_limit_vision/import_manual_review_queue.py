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
  from common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace  # type: ignore  # noqa: TID251
else:
  from .common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace


CLASSIFIER_FIELDNAMES = [
  "record_key",
  "route",
  "log_id",
  "segment",
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
  "route",
  "log_id",
  "segment",
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
  "route",
  "log_id",
  "segment",
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

REJECT_FIELDNAMES = [
  "record_key",
  "route",
  "log_id",
  "segment",
  "split",
  "crop_path",
  "frame_path",
  "bbox",
  "crop_bbox",
  "candidate_speed_limit_mph",
  "candidate_confidence",
  "detector_class",
  "review_ignore_reason",
  "review_notes",
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
  parser.add_argument("--reject-manifest-out", type=Path, help="Reviewed proposal crops that should train the classifier reject class.")
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


def split_group_key(row: dict[str, str]) -> str:
  return row.get("route") or row.get("log_id") or row["record_key"]


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


def is_advisory_positive(row: dict[str, str]) -> bool:
  return is_positive(row) and effective_sign_type(row) == "advisory"


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


def is_classifier_reject(row: dict[str, str]) -> bool:
  if row.get("review_status") != NEGATIVE_STATUS or row.get("detector_class") == "negative_empty":
    return False
  if row.get("review_sign_type") != "not_speed_limit":
    return False
  return Path(row.get("crop_path", "")).is_file()


def classifier_reject_row(row: dict[str, str], split: str) -> dict[str, object]:
  return {
    "record_key": row["record_key"],
    "route": row.get("route", ""),
    "log_id": row.get("log_id", ""),
    "segment": row.get("segment", ""),
    "split": split,
    "crop_path": row.get("crop_path", ""),
    "frame_path": row.get("frame_path", ""),
    "bbox": row.get("bbox", ""),
    "crop_bbox": row.get("crop_bbox", ""),
    "candidate_speed_limit_mph": row.get("candidate_speed_limit_mph", ""),
    "candidate_confidence": row.get("candidate_confidence", ""),
    "detector_class": row.get("detector_class", ""),
    "review_ignore_reason": row.get("review_ignore_reason", ""),
    "review_notes": row.get("review_notes", ""),
  }


RUNTIME_REJECT_CROP_EXPANSIONS = (
  (0.00, 0.00, 0.00, 0.00),
  (0.10, 0.06, 0.10, 0.12),
  (0.00, 0.00, 0.18, 0.18),
)


def classifier_reject_variant_rows(
  row: dict[str, str],
  split: str,
  output_dir: Path,
  overwrite: bool,
) -> list[dict[str, object]]:
  rows = [classifier_reject_row(row, split)]
  if row.get("review_ignore_reason") != "conditional_restriction":
    return rows

  frame_path = Path(row.get("frame_path", "")).expanduser()
  frame = cv2.imread(str(frame_path))
  bbox = parse_bbox(row.get("review_bbox") or row.get("bbox", ""))
  if frame is None or bbox is None:
    raise RuntimeError(f"Cannot generate conditional reject crops for {row['record_key']}: unreadable frame or bbox")

  image_h, image_w = frame.shape[:2]
  x1, y1, x2, y2 = bbox
  box_width = x2 - x1
  box_height = y2 - y1
  reject_dir = output_dir / "corrected_classifier_reject_crops"
  ensure_dir(reject_dir)
  for index, (expand_left, expand_top, expand_right, expand_bottom) in enumerate(RUNTIME_REJECT_CROP_EXPANSIONS):
    crop_bbox = (
      max(int(x1 - box_width * expand_left), 0),
      max(int(y1 - box_height * expand_top), 0),
      min(int(x2 + box_width * expand_right), image_w),
      min(int(y2 + box_height * expand_bottom), image_h),
    )
    crop_x1, crop_y1, crop_x2, crop_y2 = crop_bbox
    crop = frame[crop_y1:crop_y2, crop_x1:crop_x2]
    crop_path = reject_dir / f"{safe_stem(row['record_key'])}_runtime_expansion_{index}.jpg"
    if crop.size == 0:
      raise RuntimeError(f"Cannot generate conditional reject crop for {row['record_key']}: empty bbox {crop_bbox}")
    if overwrite or not crop_path.is_file():
      if not cv2.imwrite(str(crop_path), crop, [cv2.IMWRITE_JPEG_QUALITY, 94]):
        raise RuntimeError(f"Cannot write conditional reject crop for {row['record_key']}: {crop_path}")
    variant = classifier_reject_row(row, split)
    variant["record_key"] = f"{row['record_key']}_runtime_expansion_{index}"
    variant["crop_path"] = str(crop_path)
    variant["crop_bbox"] = ",".join(str(value) for value in crop_bbox)
    rows.append(variant)
  return rows


def corrected_classifier_crop(
  row: dict[str, str],
  output_dir: Path,
  overwrite: bool,
) -> tuple[str, str, bool]:
  original_crop = Path(row.get("crop_path", "")).expanduser()
  original_bbox = parse_bbox(row.get("bbox", ""))
  review_bbox = parse_bbox(row.get("review_bbox", ""))
  if review_bbox is None or review_bbox == original_bbox:
    return str(original_crop), row.get("crop_bbox", ""), False

  frame_path = Path(row.get("frame_path", "")).expanduser()
  frame = cv2.imread(str(frame_path))
  if frame is None:
    raise RuntimeError(f"Cannot regenerate corrected crop for {row['record_key']}: unreadable frame {frame_path}")

  image_h, image_w = frame.shape[:2]
  x1, y1, x2, y2 = review_bbox
  pad_x = max(round((x2 - x1) * 0.10), 2)
  pad_y = max(round((y2 - y1) * 0.10), 2)
  crop_bbox = (
    max(x1 - pad_x, 0),
    max(y1 - pad_y, 0),
    min(x2 + pad_x, image_w),
    min(y2 + pad_y, image_h),
  )
  crop_x1, crop_y1, crop_x2, crop_y2 = crop_bbox
  crop = frame[crop_y1:crop_y2, crop_x1:crop_x2]
  if crop.size == 0:
    raise RuntimeError(f"Cannot regenerate corrected crop for {row['record_key']}: empty review bbox {review_bbox}")

  corrected_dir = output_dir / "corrected_classifier_crops"
  corrected_path = corrected_dir / f"{safe_stem(row['record_key'])}_crop.jpg"
  if overwrite or not corrected_path.is_file():
    ensure_dir(corrected_dir)
    if not cv2.imwrite(str(corrected_path), crop, [cv2.IMWRITE_JPEG_QUALITY, 94]):
      raise RuntimeError(f"Cannot write corrected crop for {row['record_key']}: {corrected_path}")
  crop_bbox_text = ",".join(str(value) for value in crop_bbox)
  return str(corrected_path), crop_bbox_text, True


def positive_classifier_row(
  row: dict[str, str],
  split: str,
  crop_path: str | None = None,
  crop_bbox: str | None = None,
) -> dict[str, object]:
  speed = parse_speed(row.get("review_speed_limit_mph", ""))
  return {
    "record_key": row["record_key"],
    "route": row.get("route", ""),
    "log_id": row.get("log_id", ""),
    "segment": row.get("segment", ""),
    "split": split,
    "speed_limit_mph": speed,
    "review_sign_type": effective_sign_type(row),
    "crop_path": crop_path if crop_path is not None else row.get("crop_path", ""),
    "frame_path": row.get("frame_path", ""),
    "bbox": row.get("review_bbox") or row.get("bbox", ""),
    "crop_bbox": crop_bbox if crop_bbox is not None else row.get("crop_bbox", ""),
    "review_status": row.get("review_status", ""),
    "candidate_speed_limit_mph": row.get("candidate_speed_limit_mph", ""),
    "candidate_confidence": row.get("candidate_confidence", ""),
    "detector_class": row.get("detector_class", ""),
  }


def runtime_row(row: dict[str, str], split: str, sample_type: str) -> dict[str, object]:
  positive_sample_types = ("positive", "uncertain_positive", "advisory_negative")
  speed = parse_speed(row.get("review_speed_limit_mph", "")) if sample_type in positive_sample_types else 0
  return {
    "record_key": row["record_key"],
    "route": row.get("route", ""),
    "log_id": row.get("log_id", ""),
    "segment": row.get("segment", ""),
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
    "route": row.get("route", ""),
    "log_id": row.get("log_id", ""),
    "segment": row.get("segment", ""),
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
  classifier_manifest = (
    args.classifier_manifest_out.expanduser().resolve()
    if args.classifier_manifest_out else output_dir / "manual_review_classifier_manifest.csv"
  )
  runtime_manifest = (
    args.runtime_manifest_out.expanduser().resolve()
    if args.runtime_manifest_out else output_dir / "manual_review_runtime_eval_manifest.csv"
  )
  detector_manifest = (
    args.detector_manifest_out.expanduser().resolve()
    if args.detector_manifest_out else output_dir / "manual_review_detector_import_manifest.csv"
  )
  reject_manifest = (
    args.reject_manifest_out.expanduser().resolve()
    if args.reject_manifest_out else output_dir / "manual_review_classifier_reject_manifest.csv"
  )

  rows = merged_review_rows(queue_path, labels_path)
  positive_rows = [row for row in rows if is_positive(row)]
  advisory_positive_rows = [row for row in positive_rows if is_advisory_positive(row)]
  uncertain_positive_rows = [row for row in rows if is_uncertain_positive(row)]
  true_negative_rows = [row for row in rows if is_true_negative(row)]
  classifier_reject_rows = [row for row in rows if is_classifier_reject(row)]
  if args.max_detector_negatives > 0:
    true_negative_rows = true_negative_rows[:args.max_detector_negatives]

  classifier_rows: list[dict[str, object]] = []
  runtime_rows: list[dict[str, object]] = []
  detector_rows: list[dict[str, object]] = []
  reject_rows: list[dict[str, object]] = []
  corrected_classifier_crops = 0

  for row in positive_rows:
    split = split_for_key(split_group_key(row), args.val_modulo, args.val_remainder)
    classifier_crop_path, classifier_crop_bbox, corrected = corrected_classifier_crop(row, output_dir, args.overwrite)
    classifier_rows.append(positive_classifier_row(row, split, classifier_crop_path, classifier_crop_bbox))
    corrected_classifier_crops += int(corrected)
    sample_type = "advisory_negative" if is_advisory_positive(row) else "positive"
    runtime_rows.append(runtime_row(row, split, sample_type))
    detector_row = import_detector_example(workspace, row, split, args.source_name, "positive", args.mode, args.overwrite)
    if detector_row is not None:
      detector_rows.append(detector_row)

  for row in uncertain_positive_rows:
    split = split_for_key(split_group_key(row), args.val_modulo, args.val_remainder)
    runtime_rows.append(runtime_row(row, split, "uncertain_positive"))

  for row in true_negative_rows:
    split = split_for_key(split_group_key(row), args.val_modulo, args.val_remainder)
    runtime_rows.append(runtime_row(row, split, "negative_empty"))
    detector_row = import_detector_example(workspace, row, split, args.source_name, "negative_empty", args.mode, args.overwrite)
    if detector_row is not None:
      detector_rows.append(detector_row)

  for row in classifier_reject_rows:
    split = split_for_key(split_group_key(row), args.val_modulo, args.val_remainder)
    reject_rows.extend(classifier_reject_variant_rows(row, split, output_dir, args.overwrite))

  write_csv(classifier_manifest, CLASSIFIER_FIELDNAMES, classifier_rows)
  write_csv(runtime_manifest, RUNTIME_FIELDNAMES, runtime_rows)
  write_csv(detector_manifest, DETECTOR_MANIFEST_FIELDNAMES, detector_rows)
  write_csv(reject_manifest, REJECT_FIELDNAMES, reject_rows)

  summary = {
    "queue": str(queue_path),
    "labels": str(labels_path),
    "reviewed_rows": len(rows),
    "positive_rows": len(positive_rows),
    "advisory_positive_rows": len(advisory_positive_rows),
    "uncertain_positive_rows": len(uncertain_positive_rows),
    "true_negative_rows": len(true_negative_rows),
    "classifier_reject_rows": len(reject_rows),
    "corrected_classifier_crops": corrected_classifier_crops,
    "classifier_manifest": str(classifier_manifest),
    "runtime_manifest": str(runtime_manifest),
    "detector_manifest": str(detector_manifest),
    "detector_imported": len(detector_rows),
    "reject_manifest": str(reject_manifest),
  }
  summary_path = output_dir / "manual_review_import_summary.json"
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")

  review_counts = " ".join((
    f"reviewed={len(rows)} positives={len(positive_rows)}",
    f"uncertain_positives={len(uncertain_positive_rows)} true_negatives={len(true_negative_rows)}",
  ))
  import_counts = f"classifier_rejects={len(reject_rows)} detector_imported={len(detector_rows)}"
  print(f"Imported manual review queue: {review_counts} {import_counts}")
  print(f"Classifier manifest: {classifier_manifest}")
  print(f"Runtime eval manifest: {runtime_manifest}")
  print(f"Detector import manifest: {detector_manifest}")
  print(f"Classifier reject manifest: {reject_manifest}")
  print(f"Summary: {summary_path}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
