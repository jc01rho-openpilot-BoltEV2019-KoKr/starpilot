from __future__ import annotations

import argparse
import importlib.util

from pathlib import Path

import cv2
import numpy as np


def load_local_module(name: str):
  path = Path(__file__).resolve().with_name(f"{name}.py")
  spec = importlib.util.spec_from_file_location(f"test_local_{name}", path)
  assert spec is not None and spec.loader is not None
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


dataset = load_local_module("build_track_classifier_dataset")


def options(**overrides) -> argparse.Namespace:
  values = {
    "min_exact_confidence": 0.80,
    "min_detector_confidence": 0.30,
    "min_tracking_confidence": 0.75,
    "min_growth": 0.30,
    "max_growth": 8.0,
    "max_track_rank": 6,
  }
  values.update(overrides)
  return argparse.Namespace(**values)


def test_trusted_track_row_accepts_high_confidence_optical_flow() -> None:
  row = {
    "expected_speed_limit_mph": "35",
    "predicted_speed_limit_mph": "",
    "read_confidence": "0",
    "detector_confidence": "0",
    "tracking_confidence": "1.0",
    "area_ratio_to_anchor": "5.1",
    "rank": "6",
  }

  assert dataset.trusted_track_row(row, options())
  assert not dataset.trusted_track_row(row, options(min_tracking_confidence=1.01))
  assert not dataset.trusted_track_row(row, options(max_growth=5.0))


def test_stage_runtime_expansions_writes_each_view_and_repeat(tmp_path: Path) -> None:
  frame = np.zeros((100, 200, 3), dtype=np.uint8)
  frame[20:60, 50:70] = 255
  frame_path = tmp_path / "frame.jpg"
  assert cv2.imwrite(str(frame_path), frame)
  row = {
    "frame_path": str(frame_path),
    "bbox": "50,20,70,60",
    "track_key": "track",
    "rank": "2",
  }

  output = tmp_path / "crops"
  assert dataset.stage_runtime_expansions(row, output, repeat_count=2) == 6
  assert len(list(output.glob("*.jpg"))) == 6
