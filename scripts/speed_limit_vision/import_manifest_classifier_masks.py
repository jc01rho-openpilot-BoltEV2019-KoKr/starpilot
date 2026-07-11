#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib
import random
import re

from pathlib import Path

import cv2

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from build_value_dataset import crop_box, parse_yolo_labels  # type: ignore
  from common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace  # type: ignore
  from generate_value_roi_classifier_dataset import augment_mask, extract_value_mask  # type: ignore
else:
  from .build_value_dataset import crop_box, parse_yolo_labels
  from .common import DEFAULT_SPEED_VALUES, DEFAULT_WORKSPACE, ensure_dir, resolve_workspace
  from .generate_value_roi_classifier_dataset import augment_mask, extract_value_mask


READ_RE = re.compile(r"^\s*(\d+)(?:@|$)")


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Import mined comma speed-limit crops as ROI classifier digit masks.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Target training workspace root.")
  parser.add_argument("--manifest", type=Path, action="append", required=True, help="CSV manifest to import. May be passed more than once.")
  parser.add_argument("--variants-per-example", type=int, default=3, help="Augmented mask variants to generate per imported crop.")
  parser.add_argument("--default-padding", type=float, default=0.12, help="Crop padding when a manifest row does not specify one.")
  parser.add_argument("--val-modulo", type=int, default=5, help="Hash modulo for rows that do not specify train/val. 0 sends them to train.")
  parser.add_argument("--val-remainder", type=int, default=0, help="Hash remainder for rows that do not specify train/val.")
  parser.add_argument("--max-rows", type=int, default=0, help="Optional maximum rows to attempt across all manifests.")
  parser.add_argument("--seed", type=int, default=20260630, help="Random seed.")
  return parser.parse_args()


def safe_stem(text: str) -> str:
  cleaned = re.sub(r"[^A-Za-z0-9_.-]+", "_", text.strip())
  return cleaned.strip("._")[:180] or "sample"


def short_stem(text: str, max_prefix: int = 80) -> str:
  prefix = safe_stem(text)[:max_prefix].strip("._") or "sample"
  digest = hashlib.sha1(text.encode("utf-8")).hexdigest()[:12]
  return f"{prefix}_{digest}"


def read_rows(path: Path) -> list[dict[str, str]]:
  with path.open("r", encoding="utf-8", newline="") as csv_file:
    return list(csv.DictReader(csv_file))


def parse_speed_from_read(text: str) -> int:
  match = READ_RE.match(text or "")
  if not match:
    return 0
  value = int(match.group(1))
  return value if value in DEFAULT_SPEED_VALUES else 0


def row_speed(row: dict[str, str]) -> int:
  for field in ("speed_limit_mph", "speed_limit", "posted_speed"):
    text = (row.get(field) or "").strip()
    if text.isdigit():
      value = int(text)
      if value in DEFAULT_SPEED_VALUES:
        return value
  for field in ("full_detection", "model_read", "ocr_read"):
    value = parse_speed_from_read(row.get(field, ""))
    if value:
      return value
  return 0


def row_split(row: dict[str, str], key_text: str, val_modulo: int, val_remainder: int) -> str:
  split = (row.get("split") or "").strip().lower()
  if split in ("train", "val"):
    return split
  if val_modulo <= 0:
    return "train"
  digest = hashlib.sha1(key_text.encode("utf-8")).hexdigest()
  return "val" if int(digest[:8], 16) % val_modulo == val_remainder else "train"


def resolve_existing_path(path_text: str, manifest_path: Path) -> Path | None:
  text = (path_text or "").strip()
  if not text:
    return None
  path = Path(text).expanduser()
  candidates = [path]
  if not path.is_absolute():
    candidates.append((manifest_path.parent / path).resolve())
  for candidate in candidates:
    if candidate.is_file():
      return candidate.resolve()
  return None


def parse_xyxy(text: str) -> tuple[int, int, int, int] | None:
  if not text:
    return None
  parts = [part.strip() for part in text.replace(";", ",").split(",") if part.strip()]
  if len(parts) != 4:
    return None
  try:
    x1, y1, x2, y2 = (int(round(float(part))) for part in parts)
  except ValueError:
    return None
  if x2 <= x1 or y2 <= y1:
    return None
  return x1, y1, x2, y2


def crop_from_xyxy(image, box: tuple[int, int, int, int], padding: float):
  height, width = image.shape[:2]
  x1, y1, x2, y2 = box
  pad_x = int(round((x2 - x1) * padding))
  pad_y = int(round((y2 - y1) * padding))
  x1 = max(x1 - pad_x, 0)
  y1 = max(y1 - pad_y, 0)
  x2 = min(x2 + pad_x, width)
  y2 = min(y2 + pad_y, height)
  if x2 <= x1 or y2 <= y1:
    return None
  return image[y1:y2, x1:x2]


def load_crop(row: dict[str, str], manifest_path: Path, default_padding: float):
  crop_path = resolve_existing_path(row.get("crop_path", ""), manifest_path)
  if crop_path is not None:
    crop = cv2.imread(str(crop_path))
    if crop is not None and crop.size:
      return crop

  image_path = (
    resolve_existing_path(row.get("image_path", ""), manifest_path) or
    resolve_existing_path(row.get("dataset_image", ""), manifest_path) or
    resolve_existing_path(row.get("frame_path", ""), manifest_path)
  )
  if image_path is None:
    return None

  image = cv2.imread(str(image_path))
  if image is None or not image.size:
    return None

  padding_text = (row.get("padding") or "").strip()
  padding = float(padding_text) if padding_text else default_padding
  box = parse_xyxy(row.get("bbox", "") or row.get("box", ""))
  if box is not None:
    return crop_from_xyxy(image, box, padding)

  label_path = (
    resolve_existing_path(row.get("label_path", ""), manifest_path) or
    resolve_existing_path(row.get("dataset_label", ""), manifest_path)
  )
  if label_path is None:
    return image

  bbox_index = int((row.get("bbox_index") or "0").strip() or "0")
  boxes = parse_yolo_labels(label_path)
  if bbox_index >= len(boxes):
    return None
  return crop_box(image, boxes[bbox_index], padding)


def write_mask(workspace: Path, split: str, speed_value: int, stem: str, image_bgr) -> bool:
  output_dir = ensure_dir(workspace / "classifier" / split / str(speed_value))
  return cv2.imwrite(str(output_dir / f"{stem}.png"), image_bgr)


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  rng = random.Random(args.seed)

  attempted = 0
  imported = 0
  skipped_no_speed = 0
  skipped_no_crop = 0
  skipped_no_mask = 0
  skipped_write_failed = 0
  written = 0

  for manifest_path in [path.expanduser().resolve() for path in args.manifest]:
    rows = read_rows(manifest_path)
    for row_index, row in enumerate(rows):
      if args.max_rows > 0 and attempted >= args.max_rows:
        break
      attempted += 1

      speed_value = row_speed(row)
      if not speed_value:
        skipped_no_speed += 1
        continue

      key_text = "|".join(
        row.get(field, "")
        for field in ("record_key", "image_path", "dataset_image", "crop_path", "frame_path", "session_id", "bookmark_number")
      ) or f"{manifest_path}:{row_index}"
      split = row_split(row, key_text, args.val_modulo, args.val_remainder)
      crop = load_crop(row, manifest_path, args.default_padding)
      if crop is None:
        skipped_no_crop += 1
        continue

      mask = extract_value_mask(crop)
      if mask is None:
        skipped_no_mask += 1
        continue

      manifest_stem = short_stem(manifest_path.stem, max_prefix=48)
      source_stem = short_stem(key_text, max_prefix=72)
      base_stem = f"manifest_{manifest_stem}_{row_index:06d}_{source_stem}"
      base_mask = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
      row_written = 0
      if write_mask(workspace, split, speed_value, f"{base_stem}_base", base_mask):
        written += 1
        row_written += 1

      for variant_index in range(max(args.variants_per_example, 0)):
        augmented = augment_mask(mask, rng)
        if write_mask(workspace, split, speed_value, f"{base_stem}_var{variant_index:02d}", augmented):
          written += 1
          row_written += 1
      if row_written:
        imported += 1
      else:
        skipped_write_failed += 1
    if args.max_rows > 0 and attempted >= args.max_rows:
      break

  print(
    "Imported manifest classifier masks: "
    f"attempted={attempted} imported={imported} written={written} "
    f"skipped_no_speed={skipped_no_speed} skipped_no_crop={skipped_no_crop} skipped_no_mask={skipped_no_mask} "
    f"skipped_write_failed={skipped_write_failed}"
  )
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
