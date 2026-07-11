#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path

import cv2

import starpilot.system.speed_limit_vision as slv


class ReplayDaemon(slv.SpeedLimitVisionDaemon):
  def __init__(self, runtime_cadence: bool):
    super().__init__(use_runtime=False)
    self.now = 0.0
    self.runtime_cadence = runtime_cadence

  def _write_debug_event(self, event_type, frame_bgr=None, snapshot_prefix=None, **fields):
    if event_type in ("candidate", "publish", "stale_clear"):
      print(f"t={self.now:6.2f}s {event_type:12} {fields}")

  def _publish_status(self, status, clear_speed=False):
    if clear_speed:
      self._clear_detection()

  def _publish_detection(self, speed_limit_mph, confidence, status_prefix):
    super()._publish_detection(speed_limit_mph, confidence, status_prefix)

  def process_frame(self, now, frame_bgr):
    self.now = now
    slv.time.monotonic = lambda now=now: now
    self.current_frame_bgr = frame_bgr

    if self.runtime_cadence:
      inference_interval = self._inference_interval(now)
      if now - self.last_inference_at < inference_interval:
        if self.published_speed_limit_mph > 0 and self._published_detection_stale(now):
          print(f"t={self.now:6.2f}s stale_clear   {{'reason': 'inference_interval'}}")
          self._clear_detection()
        return

    self.last_inference_at = now
    detection = self._detect_sign(frame_bgr)
    if detection is not None:
      self._update_detection(detection)
    elif self.published_speed_limit_mph > 0 and self._published_detection_stale(now):
      print(f"t={self.now:6.2f}s stale_clear   {{'reason': 'no_detection'}}")
      self._clear_detection()


def iter_directory_frames(path: Path, fps: float):
  for index, frame_path in enumerate(sorted(path.glob("frame_*.png")), start=1):
    frame = cv2.imread(str(frame_path))
    if frame is None:
      continue
    yield (index - 1) / fps, frame


def iter_video_frames(path: Path):
  cap = cv2.VideoCapture(str(path))
  fps = cap.get(cv2.CAP_PROP_FPS) or 25.0
  frame_index = 0
  while True:
    ok, frame = cap.read()
    if not ok:
      break
    yield frame_index / fps, frame
    frame_index += 1
  cap.release()


def main():
  parser = argparse.ArgumentParser(description="Replay StarPilot speed-limit vision on saved video or extracted frames.")
  parser.add_argument("path", help="Path to an fcamera.hevc file or a directory of frame_XXX.png images.")
  parser.add_argument("--frames-fps", type=float, default=5.0, help="FPS to assume when replaying an extracted frame directory.")
  parser.add_argument("--start", type=float, default=0.0, help="Skip frames before this timestamp in seconds.")
  parser.add_argument("--end", type=float, default=None, help="Stop once this timestamp in seconds is exceeded.")
  parser.add_argument("--all-frames", action="store_true", help="Run inference on every decoded frame instead of the runtime cadence.")
  parser.add_argument("--models-dir", type=Path, help="Directory containing speed_limit_us_detector.onnx and speed_limit_us_value_classifier.onnx.")
  args = parser.parse_args()

  path = Path(args.path)
  if not path.exists():
    raise FileNotFoundError(path)

  if args.models_dir:
    models_dir = args.models_dir.expanduser().resolve()
    detector_path = models_dir / "speed_limit_us_detector.onnx"
    classifier_path = models_dir / "speed_limit_us_value_classifier.onnx"
    reject_classifier_path = models_dir / "speed_limit_us_reject_classifier.onnx"
    if not detector_path.is_file():
      raise FileNotFoundError(detector_path)
    if not classifier_path.is_file():
      raise FileNotFoundError(classifier_path)
    slv.US_DETECTOR_MODEL_PATH = detector_path
    slv.US_CLASSIFIER_MODEL_PATH = classifier_path
    slv.US_REJECT_CLASSIFIER_MODEL_PATH = reject_classifier_path

  daemon = ReplayDaemon(runtime_cadence=not args.all_frames)
  frame_iter = iter_directory_frames(path, max(args.frames_fps, 0.1)) if path.is_dir() else iter_video_frames(path)
  for now, frame_bgr in frame_iter:
    if now < args.start:
      continue
    if args.end is not None and now > args.end:
      break
    daemon.process_frame(now, frame_bgr)


if __name__ == "__main__":
  main()
