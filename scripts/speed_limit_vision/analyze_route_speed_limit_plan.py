#!/usr/bin/env python3
from __future__ import annotations

import argparse
import bz2
import csv

from collections import Counter
from dataclasses import dataclass
from pathlib import Path

import zstandard as zstd
from cereal import log


MS_TO_MPH = 2.2369362920544
MS_TO_KPH = 3.6


@dataclass(frozen=True)
class PlanState:
  time_s: float
  segment: int
  source: str
  speed: int
  pending: int
  map_speed: int
  mapbox_speed: int
  next_speed: int


@dataclass(frozen=True)
class VisionSpan:
  start_s: float
  end_s: float
  speed: int


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Summarize actual speed-limit planner source changes from downloaded route qlogs.")
  parser.add_argument("routes", nargs="+", help="Route log ids like 00000004--0da2db69c7 or dongle/logid.")
  parser.add_argument("--clip-root", type=Path, default=Path("/Volumes/T5/starpilot_speed_limit/realdata"), help="Downloaded segment root.")
  parser.add_argument("--metric", action="store_true", help="Print km/h instead of mph.")
  parser.add_argument("--output-csv", type=Path, help="Optional CSV of all planner state changes.")
  parser.add_argument("--observed-hold-seconds", type=float, default=12.0, help="Hold duration used by the logged build.")
  parser.add_argument("--project-hold-seconds", type=float, default=0.0, help="Project Vision spans using this stale-hold duration.")
  return parser.parse_args()


def route_log_id(route: str) -> str:
  text = route.strip().strip("'\"")
  if "/" in text:
    text = text.rsplit("/", 1)[1]
  return text


def segment_index(path: Path) -> int:
  try:
    return int(path.parent.name.rsplit("--", 1)[1])
  except (IndexError, ValueError):
    return -1


def qlog_paths(clip_root: Path, log_id: str) -> list[Path]:
  paths: list[Path] = []
  for name in ("qlog.zst", "qlog.bz2", "qlog"):
    paths.extend(clip_root.glob(f"{log_id}--*/{name}"))
  return sorted((path for path in paths if not path.name.startswith("._")), key=segment_index)


def read_qlog(path: Path):
  if path.suffix == ".zst":
    with path.open("rb") as qlog_file, zstd.ZstdDecompressor().stream_reader(qlog_file) as reader:
      return log.Event.read_multiple_bytes(reader.read())
  if path.suffix == ".bz2":
    return log.Event.read_multiple_bytes(bz2.decompress(path.read_bytes()))
  return log.Event.read_multiple_bytes(path.read_bytes())


def convert_speed(speed_ms: float, metric: bool) -> int:
  return round(speed_ms * (MS_TO_KPH if metric else MS_TO_MPH))


def extract_changes(qlogs: list[Path], metric: bool) -> tuple[list[PlanState], Counter[str], Counter[tuple[str, int]]]:
  first_time_ns: int | None = None
  last_state: tuple[str, int, int, int, int, int] | None = None
  changes: list[PlanState] = []
  source_counts: Counter[str] = Counter()
  speed_counts: Counter[tuple[str, int]] = Counter()

  for qlog_path in qlogs:
    segment = segment_index(qlog_path)
    for event in read_qlog(qlog_path):
      if event.which() != "starpilotPlan":
        continue
      if first_time_ns is None:
        first_time_ns = event.logMonoTime

      plan = event.starpilotPlan
      source = str(plan.slcSpeedLimitSource)
      speed = convert_speed(float(plan.slcSpeedLimit), metric)
      pending = convert_speed(float(plan.unconfirmedSlcSpeedLimit), metric)
      map_speed = convert_speed(float(plan.slcMapSpeedLimit), metric)
      mapbox_speed = convert_speed(float(plan.slcMapboxSpeedLimit), metric)
      next_speed = convert_speed(float(plan.slcNextSpeedLimit), metric)
      state = (source, speed, pending, map_speed, mapbox_speed, next_speed)
      source_counts[source] += 1
      speed_counts[(source, speed)] += 1
      if state == last_state:
        continue

      changes.append(PlanState(
        time_s=(event.logMonoTime - first_time_ns) / 1e9,
        segment=segment,
        source=source,
        speed=speed,
        pending=pending,
        map_speed=map_speed,
        mapbox_speed=mapbox_speed,
        next_speed=next_speed,
      ))
      last_state = state

  return changes, source_counts, speed_counts


def vision_spans(changes: list[PlanState]) -> list[VisionSpan]:
  spans: list[VisionSpan] = []
  active: PlanState | None = None
  for state in changes:
    if active is not None and active.source == "Vision":
      spans.append(VisionSpan(active.time_s, state.time_s, active.speed))
    active = state if state.source == "Vision" else None
  return spans


def project_spans(spans: list[VisionSpan], observed_hold_s: float, project_hold_s: float) -> list[VisionSpan]:
  if project_hold_s <= 0:
    return []

  projected: list[VisionSpan] = []
  for index, span in enumerate(spans):
    support_end = max(span.start_s, span.end_s - observed_hold_s)
    projected_end = support_end + project_hold_s
    if index + 1 < len(spans):
      projected_end = min(projected_end, spans[index + 1].start_s)
    if projected and projected[-1].speed == span.speed and projected[-1].end_s >= span.start_s:
      previous = projected[-1]
      projected[-1] = VisionSpan(previous.start_s, max(previous.end_s, projected_end), previous.speed)
    else:
      projected.append(VisionSpan(span.start_s, projected_end, span.speed))
  return projected


def print_route_summary(
  route: str,
  qlogs: list[Path],
  changes: list[PlanState],
  source_counts: Counter[str],
  speed_counts: Counter[tuple[str, int]],
  spans: list[VisionSpan],
  projected: list[VisionSpan],
  unit: str,
) -> None:
  print(f"\nRoute {route}")
  print(f"  qlogs: {len(qlogs)}")
  print(f"  source counts: {dict(source_counts)}")
  print("  top source/speed states:")
  for (source, speed), count in speed_counts.most_common(8):
    print(f"    {source or 'None':8s} {speed:3d} {unit}: {count}")
  print("  planner changes:")
  for state in changes:
    print(
      f"    t={state.time_s:7.1f}s seg={state.segment:02d} "
      f"source={state.source:8s} speed={state.speed:3d} pending={state.pending:3d} "
      f"map={state.map_speed:3d} mapbox={state.mapbox_speed:3d} next={state.next_speed:3d}"
    )
  print("  actual Vision spans:")
  if not spans:
    print("    none")
  for span in spans:
    print(f"    {span.speed:3d} {unit} from {span.start_s:7.1f}s to {span.end_s:7.1f}s ({span.end_s - span.start_s:5.1f}s)")
  if projected:
    print("  projected Vision spans:")
    for span in projected:
      print(f"    {span.speed:3d} {unit} from {span.start_s:7.1f}s to {span.end_s:7.1f}s ({span.end_s - span.start_s:5.1f}s)")


def write_csv(output_csv: Path, rows: list[tuple[str, PlanState]]) -> None:
  output_csv.parent.mkdir(parents=True, exist_ok=True)
  with output_csv.open("w", encoding="utf-8", newline="") as csv_file:
    writer = csv.DictWriter(csv_file, fieldnames=[
      "route", "time_s", "segment", "source", "speed", "pending", "map_speed", "mapbox_speed", "next_speed",
    ])
    writer.writeheader()
    for route, state in rows:
      writer.writerow({
        "route": route,
        "time_s": f"{state.time_s:.3f}",
        "segment": state.segment,
        "source": state.source,
        "speed": state.speed,
        "pending": state.pending,
        "map_speed": state.map_speed,
        "mapbox_speed": state.mapbox_speed,
        "next_speed": state.next_speed,
      })


def main() -> int:
  args = parse_args()
  clip_root = args.clip_root.expanduser().resolve()
  unit = "km/h" if args.metric else "mph"
  csv_rows: list[tuple[str, PlanState]] = []

  for route_input in args.routes:
    log_id = route_log_id(route_input)
    qlogs = qlog_paths(clip_root, log_id)
    if not qlogs:
      print(f"\nRoute {log_id}")
      print(f"  no qlogs found under {clip_root}")
      continue

    changes, source_counts, speed_counts = extract_changes(qlogs, args.metric)
    spans = vision_spans(changes)
    projected = project_spans(spans, args.observed_hold_seconds, args.project_hold_seconds)
    print_route_summary(log_id, qlogs, changes, source_counts, speed_counts, spans, projected, unit)
    csv_rows.extend((log_id, state) for state in changes)

  if args.output_csv and csv_rows:
    write_csv(args.output_csv.expanduser().resolve(), csv_rows)
    print(f"\nWrote {args.output_csv.expanduser().resolve()}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
