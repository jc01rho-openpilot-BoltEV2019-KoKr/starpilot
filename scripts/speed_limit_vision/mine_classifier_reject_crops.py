#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib

from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from localize_bookmark_signs import configure_models  # type: ignore
else:
  from .localize_bookmark_signs import configure_models


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Mine model-confusing negative crops into an integrated classifier reject class.")
  parser.add_argument("--manifest", type=Path, action="append", required=True, help="Reviewed runtime manifest. Repeat for multiple sets.")
  parser.add_argument("--models-dir", type=Path, required=True, help="Detector/classifier ONNX bundle used to mine hard negatives.")
  parser.add_argument("--dataset", type=Path, required=True, help="Classifier dataset containing train/reject and val/reject.")
  parser.add_argument("--split", choices=("train", "val"), default="train", help="Destination dataset split.")
  parser.add_argument("--classifier-min-confidence", type=float, default=0.55, help="Minimum wrong speed confidence to mine.")
  parser.add_argument("--max-crops", type=int, default=2000, help="Maximum reject crops to add.")
  parser.add_argument("--overwrite", action="store_true", help="Overwrite an existing crop with the same content hash.")
  return parser.parse_args()


def first_present(row: dict[str, str], keys: tuple[str, ...]) -> str:
  for key in keys:
    value = row.get(key, "").strip()
    if value:
      return value
  return ""


def expected_value(row: dict[str, str]) -> int | None:
  value = first_present(row, ("expected_speed_limit_mph", "speed_limit_mph", "dominant_value"))
  if not value:
    return None
  try:
    return int(float(value))
  except ValueError:
    return None


def is_reviewed_negative(row: dict[str, str]) -> bool:
  sample_type = row.get("sample_type", "").lower()
  review_status = row.get("review_status", "").lower()
  explicit_negative = row.get("negative", "").strip().lower() in ("1", "true", "yes")
  return explicit_negative or "negative" in sample_type or review_status in ("negative", "reject")


def iter_negative_images(manifests: list[Path]):
  seen: set[Path] = set()
  for manifest in manifests:
    with manifest.expanduser().resolve().open("r", encoding="utf-8", newline="") as handle:
      for row in csv.DictReader(handle):
        if not is_reviewed_negative(row):
          continue
        image_text = first_present(row, ("dataset_image", "frame_path", "source_frame", "image_path"))
        if not image_text:
          continue
        image_path = Path(image_text).expanduser().resolve()
        if image_path in seen or not image_path.is_file():
          continue
        seen.add(image_path)
        yield image_path


def crop_hash(crop) -> str:
  ok, encoded = cv2.imencode(".jpg", crop, [cv2.IMWRITE_JPEG_QUALITY, 94])
  if not ok:
    return ""
  return hashlib.sha256(encoded.tobytes()).hexdigest()[:20]


def remove_appledouble_files(root: Path) -> int:
  removed = 0
  for path in root.rglob("._*"):
    if path.is_file():
      path.unlink()
      removed += 1
  return removed


def main() -> int:
  args = parse_args()
  configure_models(args.models_dir)
  slv.US_CLASSIFIER_MIN_CONFIDENCE = args.classifier_min_confidence
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  dataset_root = args.dataset.expanduser().resolve()
  appledouble_removed = remove_appledouble_files(dataset_root)
  output_dir = dataset_root / args.split / "reject"
  output_dir.mkdir(parents=True, exist_ok=True)

  added = 0
  frames = 0
  proposals = 0
  for image_path in iter_negative_images(args.manifest):
    if added >= args.max_crops:
      break
    frame_bgr = cv2.imread(str(image_path))
    if frame_bgr is None:
      continue
    frames += 1
    frame_height, frame_width = frame_bgr.shape[:2]

    for _proposal_confidence, class_id, (x1, y1, x2, y2) in daemon._collect_detector_classifier_proposals(frame_bgr):
      if class_id == 1:
        continue
      proposals += 1
      box_width = x2 - x1
      box_height = y2 - y1
      if box_width <= 0 or box_height <= 0:
        continue

      for expansion_index, (left, top, right, bottom, _weight) in enumerate(slv.DETECTOR_CLASSIFIER_EXPANSIONS):
        crop_x1 = max(int(x1 - box_width * left), 0)
        crop_y1 = max(int(y1 - box_height * top), 0)
        crop_x2 = min(int(x2 + box_width * right), frame_width)
        crop_y2 = min(int(y2 + box_height * bottom), frame_height)
        crop = frame_bgr[crop_y1:crop_y2, crop_x1:crop_x2]
        if crop.size == 0 or daemon._classify_speed_limit_from_model(crop) is None:
          continue

        digest = crop_hash(crop)
        if not digest:
          continue
        output_path = output_dir / f"hardneg_{digest}_e{expansion_index}.jpg"
        if output_path.exists() and not args.overwrite:
          continue
        cv2.imwrite(str(output_path), crop, [cv2.IMWRITE_JPEG_QUALITY, 94])
        added += 1
        if added >= args.max_crops:
          break
      if added >= args.max_crops:
        break

  if added:
    cache_path = dataset_root / f"{args.split}.cache"
    if cache_path.is_file():
      cache_path.unlink()
  summary = f"Hard-negative mining complete: frames={frames} proposals={proposals} added={added}"
  summary += f" appledouble_removed={appledouble_removed}"
  print(summary)
  print(f"Reject dataset: {output_dir}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
