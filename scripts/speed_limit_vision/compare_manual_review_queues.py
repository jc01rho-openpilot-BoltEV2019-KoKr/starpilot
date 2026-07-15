#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from collections import Counter
from pathlib import Path


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Compare two fingerprinted manual-review queues by stable record key.")
  parser.add_argument("--before", type=Path, required=True, help="Baseline manual_review_queue.csv.")
  parser.add_argument("--after", type=Path, required=True, help="Candidate manual_review_queue.csv.")
  parser.add_argument("--output-csv", type=Path, required=True, help="Changed-row output CSV.")
  parser.add_argument("--review-output", type=Path, help="Optional review-compatible manifest containing the changed source rows.")
  parser.add_argument("--confidence-delta", type=float, default=0.05, help="Minimum confidence-only change to report.")
  return parser.parse_args()


def read_rows(path: Path) -> dict[str, dict[str, str]]:
  with path.expanduser().resolve().open("r", encoding="utf-8", newline="") as handle:
    return {row["record_key"]: row for row in csv.DictReader(handle) if row.get("record_key")}


def parse_float(text: str) -> float:
  try:
    return float(text)
  except (TypeError, ValueError):
    return 0.0


def classify_change(before: dict[str, str] | None, after: dict[str, str] | None, confidence_delta: float) -> str:
  if before is None:
    return "added_proposal"
  if after is None:
    return "removed_proposal"

  before_speed = before.get("candidate_speed_limit_mph", "")
  after_speed = after.get("candidate_speed_limit_mph", "")
  if not before_speed and after_speed:
    return "gained_read"
  if before_speed and not after_speed:
    return "lost_read"
  if before_speed != after_speed:
    return "value_changed"

  confidence_change = abs(
    parse_float(after.get("candidate_confidence", "")) - parse_float(before.get("candidate_confidence", ""))
  )
  if confidence_change >= confidence_delta:
    return "confidence_changed"
  return ""


def comparison_row(record_key: str, change: str, before: dict[str, str] | None, after: dict[str, str] | None) -> dict[str, str]:
  source = after or before or {}
  return {
    "record_key": record_key,
    "change": change,
    "route": source.get("route", ""),
    "segment": source.get("segment", ""),
    "frame_time_s": source.get("frame_time_s", ""),
    "detector_class": source.get("detector_class", ""),
    "proposal_confidence": source.get("proposal_confidence", ""),
    "before_speed_limit_mph": (before or {}).get("candidate_speed_limit_mph", ""),
    "before_confidence": (before or {}).get("candidate_confidence", ""),
    "after_speed_limit_mph": (after or {}).get("candidate_speed_limit_mph", ""),
    "after_confidence": (after or {}).get("candidate_confidence", ""),
    "before_support": (before or {}).get("read_support_count", ""),
    "after_support": (after or {}).get("read_support_count", ""),
    "frame_path": source.get("frame_path", ""),
    "crop_path": source.get("crop_path", ""),
    "source_video_path": source.get("source_video_path", ""),
  }


def main() -> int:
  args = parse_args()
  before = read_rows(args.before)
  after = read_rows(args.after)
  rows: list[dict[str, str]] = []
  review_rows: list[dict[str, str]] = []
  change_counts: Counter[str] = Counter()
  transition_counts: Counter[str] = Counter()

  for record_key in sorted(before.keys() | after.keys()):
    before_row = before.get(record_key)
    after_row = after.get(record_key)
    change = classify_change(before_row, after_row, args.confidence_delta)
    if not change:
      continue
    row = comparison_row(record_key, change, before_row, after_row)
    rows.append(row)
    source_row = dict(after_row or before_row or {})
    source_row.update({
      "comparison_change": change,
      "before_speed_limit_mph": row["before_speed_limit_mph"],
      "before_confidence": row["before_confidence"],
    })
    review_rows.append(source_row)
    change_counts[change] += 1
    before_speed = row["before_speed_limit_mph"] or "none"
    after_speed = row["after_speed_limit_mph"] or "none"
    transition_counts[f"{before_speed}->{after_speed}"] += 1

  output_path = args.output_csv.expanduser().resolve()
  output_path.parent.mkdir(parents=True, exist_ok=True)
  fieldnames = list(rows[0]) if rows else list(comparison_row("", "", None, None))
  with output_path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames)
    writer.writeheader()
    writer.writerows(rows)

  if args.review_output:
    review_output = args.review_output.expanduser().resolve()
    review_output.parent.mkdir(parents=True, exist_ok=True)
    review_fieldnames = list(review_rows[0]) if review_rows else []
    with review_output.open("w", encoding="utf-8", newline="") as handle:
      writer = csv.DictWriter(handle, fieldnames=review_fieldnames, extrasaction="ignore")
      writer.writeheader()
      writer.writerows(review_rows)

  summary = {
    "before": str(args.before.expanduser().resolve()),
    "after": str(args.after.expanduser().resolve()),
    "before_rows": len(before),
    "after_rows": len(after),
    "changed_rows": len(rows),
    "review_output": str(args.review_output.expanduser().resolve()) if args.review_output else "",
    "changes": dict(sorted(change_counts.items())),
    "transitions": dict(sorted(transition_counts.items(), key=lambda item: (-item[1], item[0]))),
  }
  output_path.with_suffix(".json").write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
  print(json.dumps(summary, indent=2))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
