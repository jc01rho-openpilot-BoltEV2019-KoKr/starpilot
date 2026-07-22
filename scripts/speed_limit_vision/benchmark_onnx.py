#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import statistics
import time

from pathlib import Path

import cv2
import numpy as np


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Benchmark fixed-shape ONNX forwards through OpenCV DNN.")
  parser.add_argument("models", nargs="+", type=Path, help="ONNX model paths to benchmark.")
  parser.add_argument("--input-size", type=int, required=True, help="Square model input size.")
  parser.add_argument("--iterations", type=int, default=50)
  parser.add_argument("--warmup", type=int, default=5)
  return parser.parse_args()


def percentile(values: list[float], quantile: float) -> float:
  ordered = sorted(values)
  index = min(round((len(ordered) - 1) * quantile), len(ordered) - 1)
  return ordered[index]


def benchmark(path: Path, input_size: int, iterations: int, warmup: int) -> dict[str, object]:
  net = cv2.dnn.readNetFromONNX(str(path))
  blob = np.zeros((1, 3, input_size, input_size), dtype=np.float32)
  net.setInput(blob)
  output = net.forward()
  for _ in range(max(warmup - 1, 0)):
    net.setInput(blob)
    output = net.forward()

  durations_ms = []
  for _ in range(max(iterations, 1)):
    net.setInput(blob)
    started_at = time.perf_counter()
    output = net.forward()
    durations_ms.append((time.perf_counter() - started_at) * 1000.0)

  return {
    "model": str(path.resolve()),
    "input_size": input_size,
    "output_shape": list(output.shape),
    "iterations": len(durations_ms),
    "median_ms": round(statistics.median(durations_ms), 3),
    "p95_ms": round(percentile(durations_ms, 0.95), 3),
    "mean_ms": round(statistics.mean(durations_ms), 3),
  }


def main() -> int:
  args = parse_args()
  results = [
    benchmark(path.expanduser().resolve(), args.input_size, args.iterations, args.warmup)
    for path in args.models
  ]
  print(json.dumps(results, indent=2))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
