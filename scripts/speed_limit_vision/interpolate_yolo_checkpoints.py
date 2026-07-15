#!/usr/bin/env python3
from __future__ import annotations

import argparse
import copy

from pathlib import Path

import torch


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Linearly interpolate compatible Ultralytics checkpoints.")
  parser.add_argument("--base", type=Path, required=True, help="Baseline checkpoint used at alpha=0.")
  parser.add_argument("--candidate", type=Path, required=True, help="Candidate checkpoint used at alpha=1.")
  parser.add_argument("--alpha", type=float, required=True, help="Candidate weight in [0, 1].")
  parser.add_argument("--output", type=Path, required=True, help="Interpolated checkpoint path.")
  return parser.parse_args()


def checkpoint_model(checkpoint: dict):
  model = checkpoint.get("ema") or checkpoint.get("model")
  if model is None:
    raise ValueError("Checkpoint contains neither model nor ema weights")
  return model.float()


def main() -> int:
  args = parse_args()
  if not 0.0 <= args.alpha <= 1.0:
    raise ValueError("--alpha must be between 0 and 1")
  base_checkpoint = torch.load(args.base.expanduser().resolve(), map_location="cpu", weights_only=False)
  candidate_checkpoint = torch.load(args.candidate.expanduser().resolve(), map_location="cpu", weights_only=False)
  base_model = checkpoint_model(base_checkpoint)
  candidate_model = checkpoint_model(candidate_checkpoint)
  base_state = base_model.state_dict()
  candidate_state = candidate_model.state_dict()
  if base_state.keys() != candidate_state.keys():
    raise ValueError("Checkpoint model state keys differ")

  interpolated_state = {}
  for key, base_value in base_state.items():
    candidate_value = candidate_state[key]
    if base_value.shape != candidate_value.shape:
      raise ValueError(f"Checkpoint tensor shape differs for {key}")
    if torch.is_floating_point(base_value):
      interpolated_state[key] = base_value * (1.0 - args.alpha) + candidate_value * args.alpha
    else:
      interpolated_state[key] = candidate_value if args.alpha >= 0.5 else base_value

  interpolated_model = copy.deepcopy(base_model)
  interpolated_model.load_state_dict(interpolated_state)
  output_checkpoint = dict(base_checkpoint)
  output_checkpoint.update({
    "model": interpolated_model,
    "ema": None,
    "optimizer": None,
    "epoch": -1,
    "best_fitness": None,
  })
  output = args.output.expanduser().resolve()
  output.parent.mkdir(parents=True, exist_ok=True)
  torch.save(output_checkpoint, output)
  print(f"Wrote alpha={args.alpha:.4f} interpolated checkpoint to {output}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
