#!/usr/bin/env python3
from __future__ import annotations

import argparse

from pathlib import Path

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import DEFAULT_WORKSPACE, resolve_workspace  # type: ignore
else:
  from .common import DEFAULT_WORKSPACE, resolve_workspace


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Train the speed-limit value classifier using Ultralytics YOLO classification.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--data", type=Path, help="Classifier dataset root. Defaults to <workspace>/classifier.")
  parser.add_argument("--model", default="yolo11n-cls.pt", help="Ultralytics classification checkpoint to fine-tune.")
  parser.add_argument("--epochs", type=int, default=60, help="Training epochs.")
  parser.add_argument("--imgsz", type=int, default=128, help="Training image size.")
  parser.add_argument("--batch", type=int, default=32, help="Batch size.")
  parser.add_argument("--workers", type=int, default=8, help="Data loader workers.")
  parser.add_argument("--device", default="cpu", help="Ultralytics device string, for example cpu, mps, 0, or 0,1.")
  parser.add_argument("--project", type=Path, help="Training output directory. Defaults to <workspace>/runs/classifier.")
  parser.add_argument("--name", default="yolo11n-cls-speed-limit-us", help="Run name under --project.")
  parser.add_argument("--patience", type=int, default=15, help="Early stopping patience.")
  parser.add_argument("--cache", action="store_true", help="Cache images in RAM if supported.")
  parser.add_argument("--exist-ok", action="store_true", help="Allow overwriting an existing run directory.")
  parser.add_argument("--optimizer", help="Ultralytics optimizer name, for example SGD, Adam, or AdamW.")
  parser.add_argument("--lr0", type=float, help="Initial learning rate passed to Ultralytics.")
  parser.add_argument("--lrf", type=float, help="Final LR fraction passed to Ultralytics.")
  parser.add_argument("--warmup-epochs", type=float, help="Warmup epochs passed to Ultralytics.")
  parser.add_argument("--weight-decay", type=float, help="Weight decay passed to Ultralytics.")
  parser.add_argument("--cos-lr", action="store_true", help="Use cosine LR scheduling.")
  parser.add_argument("--degrees", type=float, help="Rotation augmentation degrees.")
  parser.add_argument("--translate", type=float, help="Translation augmentation fraction.")
  parser.add_argument("--scale", type=float, help="Scale augmentation gain.")
  parser.add_argument("--shear", type=float, help="Shear augmentation degrees.")
  parser.add_argument("--perspective", type=float, help="Perspective augmentation fraction.")
  parser.add_argument("--fliplr", type=float, help="Horizontal flip augmentation probability.")
  parser.add_argument("--erasing", type=float, help="Random erasing augmentation probability.")
  parser.add_argument("--auto-augment", help="Ultralytics classification auto-augment policy.")
  parser.add_argument("--dropout", type=float, help="Classification head dropout.")
  parser.add_argument("--freeze", type=int, help="Freeze the first N model layers.")
  return parser.parse_args()


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  data_path = args.data.resolve() if args.data else (workspace / "classifier")
  project_path = args.project.resolve() if args.project else (workspace / "runs" / "classifier")

  try:
    from ultralytics import YOLO
  except Exception as exc:
    raise SystemExit(
      "Ultralytics is not installed. Run `uv sync --extra speedvision` in the repo root before training."
    ) from exc

  train_kwargs = {
    "data": str(data_path),
    "epochs": args.epochs,
    "imgsz": args.imgsz,
    "batch": args.batch,
    "workers": args.workers,
    "device": args.device,
    "project": str(project_path),
    "name": args.name,
    "patience": args.patience,
    "cache": args.cache,
    "exist_ok": args.exist_ok,
  }
  optional_kwargs = {
    "optimizer": args.optimizer,
    "lr0": args.lr0,
    "lrf": args.lrf,
    "warmup_epochs": args.warmup_epochs,
    "weight_decay": args.weight_decay,
    "degrees": args.degrees,
    "translate": args.translate,
    "scale": args.scale,
    "shear": args.shear,
    "perspective": args.perspective,
    "fliplr": args.fliplr,
    "erasing": args.erasing,
    "auto_augment": args.auto_augment,
    "dropout": args.dropout,
    "freeze": args.freeze,
  }
  train_kwargs.update({key: value for key, value in optional_kwargs.items() if value is not None})
  if args.auto_augment is not None and args.auto_augment.lower() in ("none", "off", "false", "0"):
    train_kwargs["auto_augment"] = None
  if args.cos_lr:
    train_kwargs["cos_lr"] = True

  model = YOLO(args.model)
  model.train(
    **train_kwargs,
  )
  print(f"Classifier training complete under {project_path / args.name}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
