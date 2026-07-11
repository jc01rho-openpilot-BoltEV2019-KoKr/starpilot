#!/usr/bin/env python3
from __future__ import annotations

import argparse
import bisect
import bz2
import csv

from dataclasses import dataclass
from pathlib import Path

import cv2
import zstandard as zstd
from cereal import log

import starpilot.system.speed_limit_vision as slv


@dataclass(frozen=True)
class RouteSummary:
  route: str
  segments: int
  qlog_context: bool
  sampled_frames: int
  inference_frames: int
  candidate_events: int
  publish_events: int
  stale_clear_events: int
  road_change_events: int


@dataclass
class QlogRuntimeContext:
  cpu_times: list[float]
  cpu_busy: list[bool]
  live_pose_times: list[float]
  live_pose_inputs_ok: list[bool]
  road_times: list[float]
  road_names: list[str]
  started_times: list[float]
  started: list[bool]

  def _last_index(self, times: list[float], now: float) -> int:
    return bisect.bisect_right(times, now) - 1

  def device_cpu_busy_at(self, now: float) -> bool:
    index = self._last_index(self.cpu_times, now)
    return index >= 0 and self.cpu_busy[index]

  def live_pose_inputs_ok_at(self, now: float) -> bool:
    index = self._last_index(self.live_pose_times, now)
    return index < 0 or self.live_pose_inputs_ok[index]

  def road_name_at(self, now: float) -> str:
    index = self._last_index(self.road_times, now)
    return self.road_names[index] if index >= 0 else ""

  def started_at(self, now: float) -> bool:
    index = self._last_index(self.started_times, now)
    return index < 0 or self.started[index]


class RouteReplayDaemon(slv.SpeedLimitVisionDaemon):
  def __init__(self, runtime_context: QlogRuntimeContext | None, measured_inference_seconds: float):
    super().__init__(use_runtime=False)
    self.runtime_context = runtime_context
    self.measured_inference_seconds = max(float(measured_inference_seconds), 0.0)
    self.next_available_at = -float("inf")
    self.now = 0.0
    self.sampled_frames = 0
    self.inference_frames = 0
    self.events: list[dict[str, str]] = []

  def _write_debug_event(self, event_type, frame_bgr=None, snapshot_prefix=None, **fields):
    if event_type not in ("candidate", "publish", "stale_clear", "road_change"):
      return
    record = {
      "time_s": f"{self.now:.3f}",
      "event": event_type,
    }
    for key, value in fields.items():
      record[key] = str(value)
    self.events.append(record)

  def _publish_status(self, status, clear_speed=False):
    if clear_speed:
      self._clear_detection()

  def _device_cpu_busy(self):
    if self.runtime_context is None:
      return False
    return self.runtime_context.device_cpu_busy_at(self.now)

  def prepare_tick(self, now: float) -> bool:
    self.now = now
    slv.time.monotonic = lambda now=now: now

    if self.runtime_context is None:
      return True

    if not self.runtime_context.started_at(now):
      if self.published_speed_limit_mph > 0:
        self._clear_detection()
      self.last_road_name = ""
      return False

    if not self.runtime_context.live_pose_inputs_ok_at(now):
      self.last_live_pose_inputs_not_ok_at = now

    road_name = self.runtime_context.road_name_at(now)
    if self.last_road_name and road_name and road_name != self.last_road_name:
      self._write_debug_event("road_change", previousRoadName=self.last_road_name, roadName=road_name)
      self._clear_detection()
    self.last_road_name = road_name or self.last_road_name
    return True

  def process_frame(self, now: float, frame_bgr):
    self.sampled_frames += 1
    if not self.prepare_tick(now):
      return
    if now < self.next_available_at:
      return
    self.current_frame_bgr = frame_bgr

    inference_interval = self._inference_interval(now)
    next_due = max(self.next_available_at, self.last_inference_at + inference_interval)
    if now < next_due:
      if self.published_speed_limit_mph > 0 and self._published_detection_stale(now):
        self._write_debug_event("stale_clear", reason="inference_interval")
        self._clear_detection()
      return

    self.last_inference_at = now
    self.next_available_at = now + self.measured_inference_seconds
    self.inference_frames += 1
    detection = self._detect_sign(frame_bgr)
    if detection is not None:
      self._update_detection(detection)
    elif self.published_speed_limit_mph > 0 and self._published_detection_stale(now):
      self._write_debug_event("stale_clear", reason="no_detection")
      self._clear_detection()


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Replay downloaded route camera segments through the runtime speed-limit vision cadence.")
  parser.add_argument("routes", nargs="+", help="Route log ids like 00000004--0da2db69c7 or dongle/logid.")
  parser.add_argument("--clip-root", type=Path, default=Path("/Volumes/T5/starpilot_speed_limit/realdata"), help="Downloaded segment root.")
  parser.add_argument("--models-dir", type=Path, default=Path("starpilot/assets/vision_models"), help="Directory containing runtime ONNX models.")
  parser.add_argument("--output-csv", type=Path, help="Optional CSV of candidate/publish/stale_clear events.")
  parser.add_argument("--start", type=float, default=0.0, help="Skip route time before this second.")
  parser.add_argument("--end", type=float, help="Stop once route time exceeds this second.")
  parser.add_argument("--progress", action="store_true", help="Print a one-line progress update after each segment.")
  parser.add_argument("--fast-seek", action="store_true", help="Use VideoCapture seeks when skipping frames. Faster, but less faithful for HEVC.")
  parser.add_argument("--qlog-context", action="store_true", help="Replay with logged deviceState/livePose/mapdOut context for closer runtime cadence.")
  parser.add_argument("--measured-inference-seconds", type=float, default=0.0, help="Simulate wall-clock time spent inside one runtime inference on the comma.")
  parser.add_argument(
    "--detector-region-mode",
    choices=("full", "right_roi", "full_and_right_roi"),
    help="Override the detector/classifier region mode used by speed_limit_vision.py.",
  )
  parser.add_argument("--right-roi-bounds", help="Override the right ROI as left,top,right,bottom ratios, for example 0.45,0,1,0.82.")
  parser.add_argument("--right-roi-min-confidence", type=float, help="Override the right ROI detector minimum confidence.")
  parser.add_argument("--full-frame-ocr", action="store_true", help="Enable the expensive full-frame OCR fallback during replay.")
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


def segment_paths(clip_root: Path, log_id: str) -> list[Path]:
  return sorted(
    (path for path in clip_root.glob(f"{log_id}--*/fcamera.hevc") if not path.name.startswith("._")),
    key=segment_index,
  )


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


def build_runtime_context(qlogs: list[Path]) -> QlogRuntimeContext:
  cpu_times: list[float] = []
  cpu_busy: list[bool] = []
  live_pose_times: list[float] = []
  live_pose_inputs_ok: list[bool] = []
  road_times: list[float] = []
  road_names: list[str] = []
  started_times: list[float] = []
  started: list[bool] = []

  for qlog_path in qlogs:
    events = list(read_qlog(qlog_path))
    if not events:
      continue

    segment_start_s = max(segment_index(qlog_path), 0) * 60.0
    segment_first_time_ns = events[0].logMonoTime

    for event in events:
      now = segment_start_s + (event.logMonoTime - segment_first_time_ns) / 1e9
      event_type = event.which()
      if event_type == "deviceState":
        device_state = event.deviceState
        usage = list(device_state.cpuUsagePercent)
        busy = slv.device_cpu_usage_busy(usage)
        cpu_times.append(now)
        cpu_busy.append(busy)
        started_times.append(now)
        started.append(bool(device_state.started))
      elif event_type == "livePose":
        live_pose_times.append(now)
        live_pose_inputs_ok.append(bool(event.livePose.inputsOK))
      elif event_type == "mapdOut":
        road_name = str(event.mapdOut.roadName or "")
        if road_name:
          road_times.append(now)
          road_names.append(road_name)

  return QlogRuntimeContext(
    cpu_times=cpu_times,
    cpu_busy=cpu_busy,
    live_pose_times=live_pose_times,
    live_pose_inputs_ok=live_pose_inputs_ok,
    road_times=road_times,
    road_names=road_names,
    started_times=started_times,
    started=started,
  )


def configure_models(models_dir: Path) -> None:
  models_dir = models_dir.expanduser().resolve()
  slv.US_DETECTOR_MODEL_PATH = models_dir / "speed_limit_us_detector.onnx"
  slv.US_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_value_classifier.onnx"
  slv.US_REJECT_CLASSIFIER_MODEL_PATH = models_dir / "speed_limit_us_reject_classifier.onnx"


def configure_runtime_options(args: argparse.Namespace) -> None:
  if args.detector_region_mode:
    slv.DETECTOR_CLASSIFIER_REGION_MODE = args.detector_region_mode

  if args.full_frame_ocr:
    slv.FULL_FRAME_OCR_FALLBACK_ENABLED = True

  if args.right_roi_bounds:
    parts = [float(part.strip()) for part in args.right_roi_bounds.split(",")]
    if len(parts) != 4:
      raise ValueError("--right-roi-bounds must contain four comma-separated ratios")
    left, top, right, bottom = parts
    if not (0.0 <= left < right <= 1.0 and 0.0 <= top < bottom <= 1.0):
      raise ValueError("--right-roi-bounds must be normalized as 0 <= left < right <= 1 and 0 <= top < bottom <= 1")

    min_confidence = args.right_roi_min_confidence
    if min_confidence is None:
      min_confidence = float(slv.ROI_WINDOWS[-1]["min_confidence"]) if slv.ROI_WINDOWS else slv.US_DETECTOR_MIN_CONFIDENCE
    right_roi = {"bounds": (left, top, right, bottom), "min_confidence": float(min_confidence)}
    slv.ROI_WINDOWS = (*slv.ROI_WINDOWS[:-1], right_roi) if slv.ROI_WINDOWS else (right_roi,)
  elif args.right_roi_min_confidence is not None:
    if not slv.ROI_WINDOWS:
      right_roi = {"bounds": (0.72, 0.05, 1.00, 0.82), "min_confidence": float(args.right_roi_min_confidence)}
      slv.ROI_WINDOWS = (right_roi,)
    else:
      right_roi = dict(slv.ROI_WINDOWS[-1])
      right_roi["min_confidence"] = float(args.right_roi_min_confidence)
      slv.ROI_WINDOWS = (*slv.ROI_WINDOWS[:-1], right_roi)


def skip_to_frame(capture, frame_index: int, target_index: int, fast_seek: bool) -> int:
  if target_index <= frame_index:
    return frame_index
  if fast_seek:
    capture.set(cv2.CAP_PROP_POS_FRAMES, target_index)
    return target_index
  while frame_index < target_index:
    if not capture.grab():
      return target_index
    frame_index += 1
  return frame_index


def replay_route(
  log_id: str,
  segments: list[Path],
  runtime_context: QlogRuntimeContext | None,
  start_s: float,
  end_s: float | None,
  progress: bool,
  fast_seek: bool,
  measured_inference_seconds: float,
) -> tuple[RouteSummary, list[dict[str, str]]]:
  daemon = RouteReplayDaemon(runtime_context, measured_inference_seconds)
  for segment_path in segments:
    segment = segment_index(segment_path)
    capture = cv2.VideoCapture(str(segment_path))
    fps = capture.get(cv2.CAP_PROP_FPS) or 20.0
    total_frames = int(capture.get(cv2.CAP_PROP_FRAME_COUNT) or 0)
    segment_start_s = segment * 60.0
    frame_index = max(int(round(max(start_s - segment_start_s, 0.0) * fps)), 0)
    if frame_index > 0:
      if fast_seek:
        capture.set(cv2.CAP_PROP_POS_FRAMES, frame_index)
      else:
        frame_index = skip_to_frame(capture, 0, frame_index, fast_seek=False)

    while total_frames <= 0 or frame_index < total_frames:
      now = segment_start_s + frame_index / fps
      if end_s is not None and now > end_s:
        capture.release()
        summary = summarize(log_id, len(segments), runtime_context is not None, daemon)
        return summary, daemon.events

      if not daemon.prepare_tick(now):
        frame_index = skip_to_frame(capture, frame_index, frame_index + 1, fast_seek)
        continue

      inference_interval = daemon._inference_interval(now)
      next_due = max(daemon.next_available_at, daemon.last_inference_at + inference_interval)
      if now < next_due:
        target_index = max(frame_index + 1, int(round((next_due - segment_start_s) * fps)))
        if total_frames > 0:
          target_index = min(target_index, total_frames)
        if target_index <= frame_index:
          target_index = frame_index + 1
        frame_index = skip_to_frame(capture, frame_index, target_index, fast_seek)
        continue

      ok, frame_bgr = capture.read()
      if not ok:
        break
      frame_index += 1
      daemon.process_frame(now, frame_bgr)

    capture.release()
    if progress:
      print(
        f"  seg {segment:02d}: sampled={daemon.sampled_frames} inference={daemon.inference_frames} "
        f"events={len(daemon.events)}",
        flush=True,
      )

  return summarize(log_id, len(segments), runtime_context is not None, daemon), daemon.events


def summarize(route: str, segment_count: int, qlog_context: bool, daemon: RouteReplayDaemon) -> RouteSummary:
  event_counts = {
    event_name: sum(1 for event in daemon.events if event["event"] == event_name)
    for event_name in ("candidate", "publish", "stale_clear", "road_change")
  }
  return RouteSummary(
    route=route,
    segments=segment_count,
    qlog_context=qlog_context,
    sampled_frames=daemon.sampled_frames,
    inference_frames=daemon.inference_frames,
    candidate_events=event_counts["candidate"],
    publish_events=event_counts["publish"],
    stale_clear_events=event_counts["stale_clear"],
    road_change_events=event_counts["road_change"],
  )


def write_events(path: Path, route_events: list[tuple[str, dict[str, str]]]) -> None:
  path.parent.mkdir(parents=True, exist_ok=True)
  fieldnames = [
    "route", "time_s", "event", "candidateSpeedLimitMph", "speedLimitMph", "confidence", "reason",
    "previousRoadName", "roadName",
  ]
  with path.open("w", encoding="utf-8", newline="") as output_file:
    writer = csv.DictWriter(output_file, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    for route, event in route_events:
      row = {"route": route}
      row.update(event)
      writer.writerow(row)


def publish_speed_changes(events: list[dict[str, str]]) -> list[tuple[float, str]]:
  changes: list[tuple[float, str]] = []
  last_speed = ""
  for event in events:
    if event["event"] in ("stale_clear", "road_change"):
      last_speed = ""
      continue
    if event["event"] != "publish":
      continue

    speed = event.get("speedLimitMph", "")
    if not speed or speed == last_speed:
      continue
    changes.append((float(event["time_s"]), speed))
    last_speed = speed
  return changes


def main() -> int:
  args = parse_args()
  configure_models(args.models_dir)
  configure_runtime_options(args)
  clip_root = args.clip_root.expanduser().resolve()
  all_events: list[tuple[str, dict[str, str]]] = []

  for route_input in args.routes:
    log_id = route_log_id(route_input)
    paths = segment_paths(clip_root, log_id)
    if not paths:
      print(f"{log_id}: no fcamera.hevc segments found under {clip_root}")
      continue

    runtime_context = None
    if args.qlog_context:
      qlogs = qlog_paths(clip_root, log_id)
      if not qlogs:
        print(f"{log_id}: no qlogs found under {clip_root}; replaying without qlog context")
      else:
        runtime_context = build_runtime_context(qlogs)

    summary, events = replay_route(
      log_id,
      paths,
      runtime_context,
      args.start,
      args.end,
      args.progress,
      args.fast_seek,
      args.measured_inference_seconds,
    )
    all_events.extend((log_id, event) for event in events)
    print(
      f"{summary.route}: segments={summary.segments} qlog_context={int(summary.qlog_context)} sampled={summary.sampled_frames} "
      f"inference={summary.inference_frames} candidate={summary.candidate_events} "
      f"publish={summary.publish_events} stale_clear={summary.stale_clear_events} road_change={summary.road_change_events} "
      f"measured_inference_s={args.measured_inference_seconds:.3f} region={slv.DETECTOR_CLASSIFIER_REGION_MODE}",
      flush=True,
    )
    publish_values = [event.get("speedLimitMph") for event in events if event["event"] == "publish"]
    if publish_values:
      print(f"  publishes: {', '.join(publish_values)}", flush=True)
    speed_changes = publish_speed_changes(events)
    if speed_changes:
      print("  speed changes: " + ", ".join(f"{time_s:.1f}s={speed}" for time_s, speed in speed_changes), flush=True)

  if args.output_csv:
    write_events(args.output_csv.expanduser().resolve(), all_events)
    print(f"Wrote {args.output_csv.expanduser().resolve()}", flush=True)

  return 0


if __name__ == "__main__":
  raise SystemExit(main())
