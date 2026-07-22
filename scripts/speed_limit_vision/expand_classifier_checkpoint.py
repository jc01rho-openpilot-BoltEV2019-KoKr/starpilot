#!/usr/bin/env python3
from __future__ import annotations

import argparse

from pathlib import Path

import torch

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import EXTENDED_CLASSIFIER_SPEED_VALUES  # type: ignore  # noqa: TID251
else:
  from .common import EXTENDED_CLASSIFIER_SPEED_VALUES


DEFAULT_CLASSES = tuple(str(value) for value in EXTENDED_CLASSIFIER_SPEED_VALUES) + ("reject",)


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Expand a YOLO classification head while preserving existing class rows.")
  parser.add_argument("--model", type=Path, required=True, help="Existing Ultralytics classification checkpoint.")
  parser.add_argument("--output", type=Path, required=True, help="Expanded checkpoint path.")
  parser.add_argument("--classes", nargs="+", default=DEFAULT_CLASSES, help="New output classes in dataset index order.")
  return parser.parse_args()


def main() -> int:
  from ultralytics import YOLO

  args = parse_args()
  model = YOLO(str(args.model.expanduser().resolve()))
  old_names = {int(index): str(name) for index, name in model.names.items()}
  new_names = dict(enumerate(args.classes))
  if len(set(new_names.values())) != len(new_names):
    raise ValueError("--classes contains duplicate names")
  if not set(old_names.values()).issubset(new_names.values()):
    missing = sorted(set(old_names.values()) - set(new_names.values()))
    raise ValueError(f"Expanded classes omit existing outputs: {missing}")

  head = model.model.model[-1]
  old_linear = head.linear
  new_linear = torch.nn.Linear(
    old_linear.in_features,
    len(new_names),
    bias=old_linear.bias is not None,
    device=old_linear.weight.device,
    dtype=old_linear.weight.dtype,
  )
  new_index_by_name = {name: index for index, name in new_names.items()}
  with torch.no_grad():
    for old_index, name in old_names.items():
      new_index = new_index_by_name[name]
      new_linear.weight[new_index].copy_(old_linear.weight[old_index])
      if old_linear.bias is not None:
        new_linear.bias[new_index].copy_(old_linear.bias[old_index])

  head.linear = new_linear
  head.np = sum(parameter.numel() for parameter in head.parameters())
  model.model.names = new_names
  model.model.yaml["nc"] = len(new_names)
  model.model.args["classes"] = None

  output = args.output.expanduser().resolve()
  output.parent.mkdir(parents=True, exist_ok=True)
  model.save(str(output))
  print(f"Expanded {len(old_names)} outputs to {len(new_names)}: {output}")
  print(new_names)
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
