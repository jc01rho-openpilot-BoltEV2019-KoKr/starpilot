#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from pathlib import Path


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Merge fingerprint-compatible speed-limit manual review queues.")
  parser.add_argument("inputs", type=Path, nargs="+", help="Queue directories or manual_review_queue.csv files.")
  parser.add_argument("--output-dir", type=Path, required=True, help="Destination queue directory.")
  return parser.parse_args()


def queue_paths(input_path: Path) -> tuple[Path, Path]:
  resolved = input_path.expanduser().resolve()
  if resolved.is_dir():
    return resolved / "manual_review_queue.csv", resolved / "manual_review_summary.json"
  return resolved, resolved.with_name("manual_review_summary.json")


def main() -> int:
  args = parse_args()
  rows_by_key: dict[str, dict[str, str]] = {}
  summaries_by_route: dict[str, dict[str, object]] = {}
  fieldnames: list[str] | None = None
  mining_fingerprint = ""
  model_fingerprint = ""

  for input_path in args.inputs:
    queue_path, summary_path = queue_paths(input_path)
    if not queue_path.is_file() or not summary_path.is_file():
      raise FileNotFoundError(f"Queue or summary missing for {input_path}")
    summary = json.loads(summary_path.read_text(encoding="utf-8"))
    current_mining = str(summary.get("mining_fingerprint", ""))
    current_model = str(summary.get("model_fingerprint", ""))
    if not current_mining or not current_model:
      raise RuntimeError(f"Queue is not fingerprinted: {input_path}")
    if mining_fingerprint and current_mining != mining_fingerprint:
      raise RuntimeError(f"Mining fingerprint mismatch: {input_path}")
    if model_fingerprint and current_model != model_fingerprint:
      raise RuntimeError(f"Model fingerprint mismatch: {input_path}")
    mining_fingerprint = current_mining
    model_fingerprint = current_model

    with queue_path.open("r", encoding="utf-8", newline="") as handle:
      reader = csv.DictReader(handle)
      current_fields = list(reader.fieldnames or [])
      if fieldnames is not None and current_fields != fieldnames:
        raise RuntimeError(f"Queue fields differ: {input_path}")
      fieldnames = current_fields
      for row in reader:
        key = row.get("record_key", "")
        if key:
          rows_by_key[key] = row
    for route_summary in summary.get("routes", []):
      route = str(route_summary.get("route", ""))
      if route:
        summaries_by_route[route] = route_summary

  rows = sorted(rows_by_key.values(), key=lambda row: (-float(row.get("review_priority") or 0.0), row["record_key"]))
  route_summaries = sorted(summaries_by_route.values(), key=lambda item: str(item["route"]))
  output_dir = args.output_dir.expanduser().resolve()
  output_dir.mkdir(parents=True, exist_ok=True)
  queue_output = output_dir / "manual_review_queue.csv"
  with queue_output.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames or [])
    writer.writeheader()
    writer.writerows(rows)

  summary_output = output_dir / "manual_review_summary.json"
  summary_output.write_text(json.dumps({
    "mining_fingerprint": mining_fingerprint,
    "model_fingerprint": model_fingerprint,
    "manifest": str(queue_output),
    "rows": len(rows),
    "candidates": sum(row.get("detector_class") != "negative_empty" for row in rows),
    "negatives": sum(row.get("detector_class") == "negative_empty" for row in rows),
    "routes": route_summaries,
  }, indent=2, sort_keys=True) + "\n", encoding="utf-8")
  print(f"Merged {len(rows)} rows from {len(route_summaries)} routes into {queue_output}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
