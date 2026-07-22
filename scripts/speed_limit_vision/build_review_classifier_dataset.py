#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import shutil

from collections import Counter
from pathlib import Path

import cv2
import numpy as np


VALID_SPEEDS = frozenset((15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75))


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Build an isolated classifier dataset from a base corpus and reviewed crops.")
  parser.add_argument("--base", type=Path, required=True, help="Existing Ultralytics classification dataset root.")
  parser.add_argument("--output", type=Path, required=True, help="New isolated dataset root.")
  parser.add_argument("--positive-manifest", type=Path, action="append", default=[], help="Reviewed positive crop manifest. Repeat as needed.")
  parser.add_argument("--reject-manifest", type=Path, action="append", default=[], help="Reviewed classifier reject manifest. Repeat as needed.")
  parser.add_argument(
    "--exclude-base-record-key",
    action="append",
    default=[],
    help="Remove inherited samples whose staged filename contains this corrected record key. Repeat as needed.",
  )
  parser.add_argument(
    "--repeat-positive-record",
    action="append",
    default=[],
    metavar="RECORD_KEY=COUNT",
    help="Stage a reviewed positive COUNT times to give a hard example more training weight.",
  )
  parser.add_argument(
    "--repeat-reject-record",
    action="append",
    default=[],
    metavar="RECORD_KEY=COUNT",
    help="Stage a reviewed reject COUNT times to give a corrected hard negative more training weight.",
  )
  parser.add_argument(
    "--advisory-as-reject",
    action="store_true",
    help="Stage reviewed advisory-speed crops in the reject class instead of omitting them.",
  )
  parser.add_argument(
    "--include-advisory-positives",
    action="store_true",
    help="Train reviewed advisory crops as their numeric speed classes for recall-first models.",
  )
  parser.add_argument(
    "--advisory-reject-fraction",
    type=float,
    default=1.0,
    help="Deterministic fraction of training advisories staged as reject; validation advisories are always retained.",
  )
  parser.add_argument("--input-size", type=int, default=128, help="Square letterbox size used by the runtime classifier.")
  return parser.parse_args()


def read_rows(paths: list[Path]):
  for path in paths:
    resolved = path.expanduser().resolve()
    with resolved.open("r", encoding="utf-8", newline="") as handle:
      yield from csv.DictReader(handle)


def remove_appledouble_files(root: Path) -> int:
  removed = 0
  for path in root.rglob("._*"):
    if path.is_file():
      path.unlink()
      removed += 1
  return removed


def parse_speed(text: str) -> int:
  try:
    value = int(float((text or "").strip()))
  except ValueError:
    return 0
  return value if value in VALID_SPEEDS else 0


def is_advisory(row: dict[str, str]) -> bool:
  return row.get("review_sign_type", "").strip().lower() == "advisory"


def keep_advisory_reject(row: dict[str, str], fraction: float) -> bool:
  if row.get("split") == "val" or fraction >= 1.0:
    return True
  if fraction <= 0.0:
    return False
  digest = hashlib.sha256(row.get("record_key", "").encode("utf-8")).digest()
  return int.from_bytes(digest[:8], "big") / 2**64 < fraction


def safe_record_key(record_key: str) -> str:
  return "".join(char if char.isalnum() or char in "._-" else "_" for char in record_key)[:100]


def remove_inherited_records(root: Path, record_keys: list[str]) -> int:
  safe_keys = tuple(filter(None, (safe_record_key(record_key) for record_key in record_keys)))
  if not safe_keys:
    return 0
  removed = 0
  for split in ("train", "val"):
    for path in (root / split).rglob("*"):
      if path.is_file() and any(record_key in path.name for record_key in safe_keys):
        path.unlink()
        removed += 1
  return removed


def parse_record_repeat_counts(specs: list[str], sample_kind: str) -> dict[str, int]:
  repeat_counts: dict[str, int] = {}
  for spec in specs:
    record_key, separator, count_text = spec.rpartition("=")
    if not separator or not record_key:
      raise ValueError(f"Invalid --repeat-{sample_kind}-record value: {spec!r}")
    try:
      count = int(count_text)
    except ValueError as exc:
      raise ValueError(f"Invalid {sample_kind} repeat count: {spec!r}") from exc
    if count < 1:
      raise ValueError(f"{sample_kind.capitalize()} repeat count must be at least 1: {spec!r}")
    repeat_counts[record_key] = count
  return repeat_counts


def parse_reject_repeat_counts(specs: list[str]) -> dict[str, int]:
  return parse_record_repeat_counts(specs, "reject")


def square_resize(image: np.ndarray, size: int, color: tuple[int, int, int] = (114, 114, 114)) -> np.ndarray:
  image_height, image_width = image.shape[:2]
  ratio = min(size / max(image_height, 1), size / max(image_width, 1))
  resized_width = max(int(round(image_width * ratio)), 1)
  resized_height = max(int(round(image_height * ratio)), 1)
  resized = cv2.resize(image, (resized_width, resized_height), interpolation=cv2.INTER_LINEAR)
  canvas = np.full((size, size, image.shape[2]), color, dtype=image.dtype)
  offset_x = (size - resized_width) // 2
  offset_y = (size - resized_height) // 2
  canvas[offset_y:offset_y + resized_height, offset_x:offset_x + resized_width] = resized
  return canvas


def stage_crop(source: Path, destination_dir: Path, record_key: str, input_size: int) -> bool:
  if not source.is_file():
    return False
  digest = hashlib.sha256(source.read_bytes()).hexdigest()[:16]
  suffix = source.suffix.lower() if source.suffix.lower() in (".jpg", ".jpeg", ".png") else ".jpg"
  safe_key = safe_record_key(record_key)
  destination_dir.mkdir(parents=True, exist_ok=True)
  destination = destination_dir / f"review_{safe_key}_{digest}{suffix}"
  if not destination.exists():
    image = cv2.imread(str(source))
    if image is None or image.size == 0:
      return False
    normalized = square_resize(image, input_size)
    if not cv2.imwrite(str(destination), normalized, [cv2.IMWRITE_JPEG_QUALITY, 95]):
      return False
  return True


def main() -> int:
  args = parse_args()
  if args.advisory_as_reject and args.include_advisory_positives:
    raise ValueError("--advisory-as-reject and --include-advisory-positives are mutually exclusive")
  if not 0.0 <= args.advisory_reject_fraction <= 1.0:
    raise ValueError("--advisory-reject-fraction must be between 0 and 1")
  base = args.base.expanduser().resolve()
  output = args.output.expanduser().resolve()
  if not base.is_dir():
    raise FileNotFoundError(base)
  if output.exists():
    raise FileExistsError(f"Output dataset already exists: {output}")
  shutil.copytree(base, output, copy_function=shutil.copyfile)
  appledouble_removed = remove_appledouble_files(output)
  inherited_records_removed = remove_inherited_records(output, args.exclude_base_record_key)
  positive_repeat_counts = parse_record_repeat_counts(args.repeat_positive_record, "positive")
  reject_repeat_counts = parse_reject_repeat_counts(args.repeat_reject_record)

  positive_counts: Counter[str] = Counter()
  reject_counts: Counter[str] = Counter()
  skipped = 0
  for row in read_rows(args.positive_manifest):
    if is_advisory(row):
      if args.include_advisory_positives:
        pass
      elif args.advisory_as_reject and keep_advisory_reject(row, args.advisory_reject_fraction):
        split = row.get("split", "")
        source = Path(row.get("crop_path", "")).expanduser()
        if split in ("train", "val") and stage_crop(
          source, output / split / "reject", row.get("record_key", "advisory"), args.input_size,
        ):
          reject_counts[f"advisory_{split}"] += 1
        else:
          skipped += 1
        continue
      else:
        continue
    split = row.get("split", "")
    speed = parse_speed(row.get("speed_limit_mph", ""))
    source = Path(row.get("crop_path", "")).expanduser()
    record_key = row.get("record_key", "positive")
    repeat_count = positive_repeat_counts.get(record_key, 1) if split == "train" else 1
    staged = split in ("train", "val") and bool(speed)
    for repeat_index in range(repeat_count):
      staged_key = record_key if repeat_index == 0 else f"{record_key}_repeat_{repeat_index:03d}"
      staged = staged and stage_crop(source, output / split / str(speed), staged_key, args.input_size)
    if not staged:
      skipped += 1
      continue
    positive_counts[f"{split}/{speed}"] += repeat_count

  for row in read_rows(args.reject_manifest):
    split = row.get("split", "")
    source = Path(row.get("crop_path", "")).expanduser()
    record_key = row.get("record_key", "reject")
    repeat_count = reject_repeat_counts.get(record_key, 1) if split == "train" else 1
    staged = split in ("train", "val")
    for repeat_index in range(repeat_count):
      staged_key = record_key if repeat_index == 0 else f"{record_key}_repeat_{repeat_index:03d}"
      staged = staged and stage_crop(source, output / split / "reject", staged_key, args.input_size)
    if not staged:
      skipped += 1
      continue
    reject_counts[split] += repeat_count

  appledouble_removed += remove_appledouble_files(output)
  for split in ("train", "val"):
    cache_path = output / f"{split}.cache"
    if cache_path.is_file():
      cache_path.unlink()

  summary = {
    "base": str(base),
    "output": str(output),
    "positive_counts": dict(sorted(positive_counts.items())),
    "reject_counts": dict(sorted(reject_counts.items())),
    "skipped": skipped,
    "appledouble_removed": appledouble_removed,
    "inherited_records_removed": inherited_records_removed,
  }
  summary_path = output / "review_dataset_summary.json"
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
