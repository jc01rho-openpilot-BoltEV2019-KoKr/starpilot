#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from collections import Counter, defaultdict, deque
from pathlib import Path


PRIORITY_SPEED_ORDER = (60, 65, 55, 50, 45, 40, 35, 30, 25, 20, 70, 15, 75)
COMPARISON_PRIORITY_BONUS = {
  "value_changed": 4.0,
  "gained_read": 3.0,
  "lost_read": 3.0,
  "added_proposal": 1.0,
  "removed_proposal": 1.0,
}


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Select a diverse, high-value subset from a raw speed-limit review queue.")
  parser.add_argument("--input", type=Path, required=True, help="Raw manual_review_queue.csv.")
  parser.add_argument("--output", type=Path, required=True, help="Selected manual_review_queue.csv.")
  parser.add_argument("--max-rows", type=int, default=1000, help="Maximum selected rows.")
  parser.add_argument("--max-per-route", type=int, default=30, help="Maximum selected rows from one route.")
  parser.add_argument("--max-per-speed", type=int, default=140, help="Maximum rows for each predicted speed.")
  parser.add_argument(
    "--max-primary-speed",
    type=int,
    default=0,
    help="Optional per-speed cap for the primary 30-65 mph range; defaults to --max-per-speed.",
  )
  parser.add_argument(
    "--max-speed-20",
    type=int,
    default=0,
    help="Optional cap for 20 mph rows; defaults to --max-per-speed.",
  )
  parser.add_argument("--max-no-read", type=int, default=220, help="Maximum detector proposals without a value read.")
  parser.add_argument("--max-school", type=int, default=100, help="Maximum school-zone candidates.")
  parser.add_argument("--max-advisory", type=int, default=100, help="Maximum advisory candidates.")
  parser.add_argument(
    "--min-seconds-per-route-speed",
    type=float,
    default=3.0,
    help="Minimum spacing between selected rows from the same route, segment, and predicted-speed bucket.",
  )
  return parser.parse_args()


def read_rows(path: Path) -> tuple[list[str], list[dict[str, str]]]:
  with path.expanduser().resolve().open("r", encoding="utf-8", newline="") as handle:
    reader = csv.DictReader(handle)
    return list(reader.fieldnames or []), list(reader)


def predicted_speed(row: dict[str, str]) -> int:
  text = (row.get("candidate_speed_limit_mph") or "").strip()
  if not text and row.get("comparison_change") == "lost_read":
    text = (row.get("before_speed_limit_mph") or "").strip()
  try:
    return int(float(text)) if text else 0
  except ValueError:
    return 0


def bucket_name(row: dict[str, str]) -> str:
  detector_class = row.get("detector_class", "")
  if detector_class == "school_zone_speed_limit":
    return "school"
  if detector_class == "advisory_speed_limit":
    return "advisory"
  speed = predicted_speed(row)
  return f"speed_{speed}" if speed else "no_read"


def priority(row: dict[str, str]) -> tuple[float, float, float, str]:
  review_priority = (
    float(row.get("review_priority") or 0.0) +
    COMPARISON_PRIORITY_BONUS.get(row.get("comparison_change", ""), 0.0)
  )
  proposal_confidence = float(row.get("proposal_confidence") or 0.0)
  candidate_confidence = float(row.get("candidate_confidence") or 0.0)
  return review_priority, proposal_confidence, candidate_confidence, row.get("record_key", "")


def temporal_key(row: dict[str, str]) -> tuple[str, str, str, float] | None:
  try:
    frame_time_s = float(row.get("frame_time_s", ""))
  except ValueError:
    return None
  return row.get("route", ""), row.get("segment", ""), bucket_name(row), frame_time_s


def round_robin_routes(rows: list[dict[str, str]]):
  by_route: dict[str, deque[dict[str, str]]] = defaultdict(deque)
  for row in sorted(rows, key=priority, reverse=True):
    by_route[row.get("route", "")].append(row)
  route_order = deque(sorted(by_route, key=lambda route: priority(by_route[route][0]), reverse=True))
  while route_order:
    route = route_order.popleft()
    yield by_route[route].popleft()
    if by_route[route]:
      route_order.append(route)


def select_rows(rows: list[dict[str, str]], args: argparse.Namespace) -> list[dict[str, str]]:
  buckets: dict[str, list[dict[str, str]]] = defaultdict(list)
  for row in rows:
    if row.get("detector_class") == "negative_empty":
      continue
    buckets[bucket_name(row)].append(row)

  max_primary_speed = int(getattr(args, "max_primary_speed", 0))
  max_speed_20 = int(getattr(args, "max_speed_20", 0))
  primary_limit = max_primary_speed if max_primary_speed > 0 else args.max_per_speed
  speed_20_limit = max_speed_20 if max_speed_20 > 0 else args.max_per_speed
  limits = {
    f"speed_{speed}": (
      primary_limit if 30 <= speed <= 65 else speed_20_limit if speed == 20 else args.max_per_speed
    )
    for speed in PRIORITY_SPEED_ORDER
  }
  limits.update({"school": args.max_school, "advisory": args.max_advisory, "no_read": args.max_no_read})
  ordered_buckets = [f"speed_{speed}" for speed in PRIORITY_SPEED_ORDER] + ["school", "advisory", "no_read"]
  ordered_buckets.extend(sorted(set(buckets) - set(ordered_buckets)))

  selected: list[dict[str, str]] = []
  selected_keys: set[str] = set()
  route_counts: Counter[str] = Counter()
  bucket_counts: Counter[str] = Counter()
  selected_times: dict[tuple[str, str, str], list[float]] = defaultdict(list)
  min_spacing = max(float(getattr(args, "min_seconds_per_route_speed", 0.0)), 0.0)

  def try_add(row: dict[str, str], bucket: str) -> bool:
    key = row.get("record_key", "")
    route = row.get("route", "")
    if not key or key in selected_keys or route_counts[route] >= args.max_per_route:
      return False
    if bucket_counts[bucket] >= limits.get(bucket, args.max_per_speed):
      return False
    time_key = temporal_key(row)
    if time_key is not None and min_spacing > 0.0:
      route_key = time_key[:3]
      if any(abs(time_key[3] - selected_time) < min_spacing for selected_time in selected_times[route_key]):
        return False
    selected.append(row)
    selected_keys.add(key)
    route_counts[route] += 1
    bucket_counts[bucket] += 1
    if time_key is not None:
      selected_times[time_key[:3]].append(time_key[3])
    return True

  iterators = {bucket: iter(round_robin_routes(buckets[bucket])) for bucket in ordered_buckets if buckets.get(bucket)}
  active = deque(bucket for bucket in ordered_buckets if bucket in iterators)
  while active and len(selected) < args.max_rows:
    bucket = active.popleft()
    iterator = iterators[bucket]
    added = False
    for row in iterator:
      if try_add(row, bucket):
        added = True
        break
    if added and bucket_counts[bucket] < limits.get(bucket, args.max_per_speed):
      active.append(bucket)

  if len(selected) < args.max_rows:
    for row in sorted(rows, key=priority, reverse=True):
      if len(selected) >= args.max_rows:
        break
      try_add(row, bucket_name(row))

  return sorted(selected, key=priority, reverse=True)


def main() -> int:
  args = parse_args()
  fieldnames, rows = read_rows(args.input)
  selected = select_rows(rows, args)
  output = args.output.expanduser().resolve()
  output.parent.mkdir(parents=True, exist_ok=True)
  with output.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(selected)

  summary = {
    "input": str(args.input.expanduser().resolve()),
    "output": str(output),
    "input_rows": len(rows),
    "selected_rows": len(selected),
    "routes": len({row.get("route", "") for row in selected}),
    "buckets": dict(sorted(Counter(bucket_name(row) for row in selected).items())),
    "min_seconds_per_route_speed": args.min_seconds_per_route_speed,
  }
  summary_path = output.with_name("manual_review_selection_summary.json")
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
  print(json.dumps(summary, indent=2, sort_keys=True))
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
