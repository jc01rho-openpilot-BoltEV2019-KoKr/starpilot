#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import os
import shutil

from collections import Counter
from pathlib import Path

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import EXTENDED_CLASSIFIER_SPEED_VALUES  # type: ignore  # noqa: TID251
else:
  from .common import EXTENDED_CLASSIFIER_SPEED_VALUES


IMAGE_SUFFIXES = frozenset((".jpg", ".jpeg", ".png", ".bmp", ".webp"))
SUPPORTED_CLASSES = frozenset(str(value) for value in EXTENDED_CLASSIFIER_SPEED_VALUES) | {"reject"}


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Merge image-folder classifier datasets using hard links when possible.")
  parser.add_argument("sources", nargs="+", type=Path, help="Classifier roots containing train/ and val/.")
  parser.add_argument("--output", type=Path, required=True)
  parser.add_argument("--overwrite", action="store_true")
  return parser.parse_args()


def link_or_copy(source: Path, destination: Path) -> None:
  destination.parent.mkdir(parents=True, exist_ok=True)
  try:
    os.link(source, destination)
  except OSError:
    # copy2 preserves macOS metadata as AppleDouble `._` files on exFAT. Image
    # loaders then mistake those sidecars for corrupt training images.
    shutil.copyfile(source, destination)


def main() -> int:
  args = parse_args()
  sources = [path.expanduser().resolve() for path in args.sources]
  output = args.output.expanduser().resolve()
  if output.exists():
    if not args.overwrite:
      raise FileExistsError(f"Output already exists: {output}")
    shutil.rmtree(output)

  counts: Counter[str] = Counter()
  for source_index, source_root in enumerate(sources):
    for split in ("train", "val"):
      split_root = source_root / split
      if not split_root.is_dir():
        raise FileNotFoundError(split_root)
      for class_dir in sorted(split_root.iterdir()):
        if not class_dir.is_dir() or class_dir.name.startswith("._"):
          continue
        if class_dir.name not in SUPPORTED_CLASSES:
          raise ValueError(f"Unsupported classifier class {class_dir.name!r} in {source_root}")
        for image_path in sorted(class_dir.iterdir()):
          if image_path.name.startswith("._") or image_path.suffix.lower() not in IMAGE_SUFFIXES or not image_path.is_file():
            continue
          destination = output / split / class_dir.name / f"s{source_index:02d}_{image_path.name}"
          link_or_copy(image_path, destination)
          counts[f"{split}/{class_dir.name}"] += 1

  summary = {
    "sources": [str(path) for path in sources],
    "output": str(output),
    "counts": dict(sorted(counts.items())),
  }
  (output / "merge_summary.json").write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="ascii")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
