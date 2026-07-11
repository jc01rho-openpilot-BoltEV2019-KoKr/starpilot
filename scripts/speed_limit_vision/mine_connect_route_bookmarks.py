#!/usr/bin/env python3
from __future__ import annotations

import argparse
import bz2
import csv
import re

from pathlib import Path

import cv2
import zstandard as zstd
from cereal import log
import starpilot.system.speed_limit_vision as slv

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import ensure_dir, preferred_clip_root, resolve_workspace  # type: ignore
  from evaluate_bookmark_leadins import BookmarkWindow  # type: ignore
  from import_bookmark_leadins import extract_window_frames, write_contact_sheet  # type: ignore
  from localize_bookmark_signs import configure_models, iter_context_frames, score_frame  # type: ignore
else:
  from .common import ensure_dir, preferred_clip_root, resolve_workspace
  from .evaluate_bookmark_leadins import BookmarkWindow
  from .import_bookmark_leadins import extract_window_frames, write_contact_sheet
  from .localize_bookmark_signs import configure_models, iter_context_frames, score_frame


DEFAULT_WORKSPACE = Path("/Volumes/T5/starpilot_speed_limit/workspace/speed_limit_training_clean")
ROUTE_ID_RE = re.compile(r"([0-9a-f]{16})/([^/]+)")
BOOKMARK_TYPES = ("bookmarkButton", "userBookmark")


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Mine Connect routes with preserved rlog/fcamera into bookmark review sheets and localized sign candidates.")
  parser.add_argument("routes", nargs="+", help="Route ids like 'dongle/logid'.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root.")
  parser.add_argument("--clip-root", type=Path, default=preferred_clip_root(), help="Downloaded route clip root.")
  parser.add_argument("--models-dir", type=Path, help="Optional directory containing speed_limit_us_detector.onnx and speed_limit_us_value_classifier.onnx.")
  parser.add_argument("--lead-in", type=float, default=7.0, help="Seconds before each bookmark to sample into review sheets.")
  parser.add_argument("--sample-every", type=float, default=0.5, help="Seconds between sampled lead-in frames.")
  parser.add_argument("--max-samples", type=int, default=12, help="Max sampled frames per bookmark for the contact sheet.")
  parser.add_argument("--search-before", type=float, default=10.0, help="Seconds before each bookmark to scan for the most sign-like frame.")
  parser.add_argument("--search-after", type=float, default=1.0, help="Seconds after each bookmark to scan for the most sign-like frame.")
  parser.add_argument("--localize-sample-every", type=float, default=0.25, help="Seconds between frames while searching for the best sign candidate.")
  parser.add_argument("--top-k", type=int, default=1, help="Number of localized candidates to keep per bookmark.")
  parser.add_argument("--overwrite", action="store_true", help="Overwrite any existing outputs.")
  return parser.parse_args()


def parse_route_id(text: str) -> tuple[str, str]:
  match = ROUTE_ID_RE.fullmatch(text.strip().replace("|", "/"))
  if match is None:
    raise ValueError(f"Unrecognized route id: {text}")
  return match.group(1), match.group(2)


def read_log_bytes(path: Path) -> bytes:
  if path.suffix == ".zst":
    with path.open("rb") as handle:
      return zstd.ZstdDecompressor().stream_reader(handle).read()
  if path.suffix == ".bz2":
    return bz2.decompress(path.read_bytes())
  return path.read_bytes()


def load_route_bookmarks(clip_root: Path, log_id: str) -> list[dict]:
  segment_dirs = sorted(clip_root.glob(f"{log_id}--*"), key=lambda path: int(path.name.rsplit("--", 1)[-1]))
  if not segment_dirs:
    raise FileNotFoundError(f"No downloaded segments found for {log_id} under {clip_root}")

  route_start_monotime = None
  raw_events: list[tuple[float, str]] = []
  for segment_dir in segment_dirs:
    rlog_path = segment_dir / "rlog.zst"
    if not rlog_path.exists():
      rlog_path = segment_dir / "rlog.bz2"
    if not rlog_path.exists():
      continue

    try:
      events = list(log.Event.read_multiple_bytes(read_log_bytes(rlog_path)))
    except Exception as exc:
      print(f"{segment_dir.name}: skipping unreadable rlog {rlog_path.name}: {exc}")
      continue
    if not events:
      continue
    if route_start_monotime is None:
      route_start_monotime = events[0].logMonoTime

    for event in events:
      event_type = event.which()
      if event_type not in BOOKMARK_TYPES:
        continue
      route_time_s = (event.logMonoTime - route_start_monotime) / 1e9
      raw_events.append((route_time_s, event_type))

  raw_events.sort(key=lambda item: item[0])
  deduped: list[dict] = []
  for route_time_s, event_type in raw_events:
    if deduped and abs(route_time_s - deduped[-1]["route_time_s"]) <= 0.5:
      if event_type == "userBookmark":
        deduped[-1]["event_type"] = event_type
        deduped[-1]["route_time_s"] = route_time_s
      continue

    segment = max(int(route_time_s // 60.0), 0)
    segment_offset_s = route_time_s - segment * 60.0
    deduped.append({
      "event_type": event_type,
      "route_time_s": route_time_s,
      "segment": segment,
      "segment_offset_s": segment_offset_s,
    })
  return deduped


def write_localized_manifest(path: Path, rows: list[dict]) -> None:
  ensure_dir(path.parent)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=[
      "session_id",
      "bookmark_number",
      "route",
      "segment",
      "relative_time_s",
      "source_video_path",
      "score",
      "proposal_confidence",
      "class_id",
      "is_regulatory",
      "model_read",
      "ocr_read",
      "full_detection",
      "frame_path",
      "crop_path",
      "box",
    ])
    writer.writeheader()
    writer.writerows(rows)


def fmt_detection(result) -> str:
  if result is None:
    return ""
  return f"{result[0]}@{result[1]:.3f}"


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  clip_root = args.clip_root.expanduser().resolve()
  review_root = ensure_dir(workspace / "review" / "connect_route_bookmarks")
  frame_dir = ensure_dir(review_root / "frames")
  crop_dir = ensure_dir(review_root / "crops")
  contact_sheet_dir = ensure_dir(review_root / "contact_sheets")
  leadin_manifest_path = review_root / "bookmark_leadins.csv"
  localized_manifest_path = review_root / "localized_bookmarks.csv"

  configure_models(args.models_dir)
  daemon = slv.SpeedLimitVisionDaemon(use_runtime=False)
  localized_rows: list[dict] = []
  leadin_rows: list[dict] = []

  for raw_route in args.routes:
    dongle_id, log_id = parse_route_id(raw_route)
    session_id = f"connect_{dongle_id}_{log_id}"
    bookmarks = load_route_bookmarks(clip_root, log_id)
    if not bookmarks:
      print(f"{raw_route}: no bookmark events found in downloaded rlogs")
      continue

    print(f"{raw_route}: found {len(bookmarks)} bookmark(s)")
    for bookmark_number, bookmark in enumerate(bookmarks, start=1):
      window = BookmarkWindow(
        bookmark_number=bookmark_number,
        route=log_id,
        segment=int(bookmark["segment"]),
        segment_offset_s=float(bookmark["segment_offset_s"]),
        leadin_start_s=float(bookmark["segment_offset_s"]) - args.lead_in,
        spans_previous_segment=float(bookmark["segment_offset_s"]) - args.lead_in < 0.0,
      )

      sampled_frames = extract_window_frames({
        "route": log_id,
        "segment": window.segment,
        "segmentOffsetS": window.segment_offset_s,
        "leadinStartS": window.leadin_start_s,
        "spansPreviousSegment": window.spans_previous_segment,
      }, clip_root, args.sample_every, args.max_samples)

      contact_sheet_frames = []
      contact_sheet_labels = []
      contact_sheet_name = f"{session_id}_bookmark_{bookmark_number:03d}.jpg"
      contact_sheet_path = contact_sheet_dir / contact_sheet_name

      for sample_index, sample in enumerate(sampled_frames, start=1):
        frame_name = f"{session_id}_bookmark_{bookmark_number:03d}_sample_{sample_index:02d}.jpg"
        frame_path = frame_dir / frame_name
        if args.overwrite or not frame_path.exists():
          cv2.imwrite(str(frame_path), sample["frame_bgr"], [cv2.IMWRITE_JPEG_QUALITY, 90])
        contact_sheet_frames.append(sample["frame_bgr"])
        contact_sheet_labels.append(f"t={sample['relative_offset_s']:+.2f}s")
        leadin_rows.append({
          "session_id": session_id,
          "bookmark_number": bookmark_number,
          "route": log_id,
          "segment": window.segment,
          "segment_offset_s": f"{window.segment_offset_s:.3f}",
          "sample_offset_s": f"{sample['relative_offset_s']:.3f}",
          "frame_path": str(frame_path.relative_to(workspace)),
          "contact_sheet_path": str(contact_sheet_path.relative_to(workspace)),
          "source_video_path": str(sample["source_video"]),
          "event_type": bookmark["event_type"],
          "route_time_s": f"{bookmark['route_time_s']:.3f}",
        })

      if contact_sheet_frames:
        write_contact_sheet(contact_sheet_path, contact_sheet_frames, contact_sheet_labels, args.overwrite)

      ranked = []
      for relative_time_s, source_video_path, _, frame_bgr in iter_context_frames(
        clip_root,
        window,
        args.search_before,
        args.search_after,
        args.localize_sample_every,
      ):
        scored = score_frame(daemon, frame_bgr)
        if scored is None:
          continue
        ranked.append((scored["score"], relative_time_s, source_video_path, frame_bgr, scored))

      ranked.sort(key=lambda item: item[0], reverse=True)
      for rank_index, (_, relative_time_s, source_video_path, frame_bgr, scored) in enumerate(ranked[:max(args.top_k, 1)], start=1):
        x1, y1, x2, y2 = scored["box"]
        crop = frame_bgr[y1:y2, x1:x2]
        frame_name = f"{session_id}_bookmark_{bookmark_number:03d}_rank_{rank_index:02d}.jpg"
        crop_name = f"{session_id}_bookmark_{bookmark_number:03d}_rank_{rank_index:02d}_crop.jpg"
        frame_path = frame_dir / frame_name
        crop_path = crop_dir / crop_name
        if args.overwrite or not frame_path.exists():
          cv2.imwrite(str(frame_path), frame_bgr, [cv2.IMWRITE_JPEG_QUALITY, 90])
        if crop.size != 0 and (args.overwrite or not crop_path.exists()):
          cv2.imwrite(str(crop_path), crop, [cv2.IMWRITE_JPEG_QUALITY, 90])

        full_detection = scored["full_detection"]
        localized_rows.append({
          "session_id": session_id,
          "bookmark_number": bookmark_number,
          "route": log_id,
          "segment": window.segment,
          "relative_time_s": f"{relative_time_s:.3f}",
          "source_video_path": str(source_video_path),
          "score": f"{scored['score']:.4f}",
          "proposal_confidence": f"{scored['proposal_confidence']:.4f}",
          "class_id": str(scored["class_id"]),
          "is_regulatory": str(bool(scored["is_regulatory"])),
          "model_read": fmt_detection(scored["model_read"]),
          "ocr_read": fmt_detection(scored["ocr_read"]),
          "full_detection": "" if full_detection is None else f"{full_detection.speed_limit_mph}@{full_detection.confidence:.3f}",
          "frame_path": str(frame_path),
          "crop_path": str(crop_path),
          "box": ",".join(str(value) for value in scored["box"]),
        })

  ensure_dir(leadin_manifest_path.parent)
  with leadin_manifest_path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=[
      "session_id",
      "bookmark_number",
      "route",
      "segment",
      "segment_offset_s",
      "sample_offset_s",
      "frame_path",
      "contact_sheet_path",
      "source_video_path",
      "event_type",
      "route_time_s",
    ])
    writer.writeheader()
    writer.writerows(leadin_rows)

  write_localized_manifest(localized_manifest_path, localized_rows)
  print(f"Wrote {len(leadin_rows)} sampled lead-in frame row(s) to {leadin_manifest_path}")
  print(f"Wrote {len(localized_rows)} localized candidate row(s) to {localized_manifest_path}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
