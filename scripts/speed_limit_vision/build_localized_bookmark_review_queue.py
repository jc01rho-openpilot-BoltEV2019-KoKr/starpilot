#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import re

from pathlib import Path

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from build_manual_review_queue import FIELDNAMES  # type: ignore
  from common import ensure_dir  # type: ignore  # noqa: TID251
  from serve_manual_review_queue import LABEL_FIELDNAMES  # type: ignore
else:
  from .build_manual_review_queue import FIELDNAMES
  from .common import ensure_dir
  from .serve_manual_review_queue import LABEL_FIELDNAMES


FRAME_KEY_RE = re.compile(r"^(?P<key>.+_bookmark_\d+_rank_\d+)$")
DETECTOR_CLASSES = {
  "0": "regulatory_speed_limit",
  "1": "advisory_speed_limit",
  "2": "school_zone_speed_limit",
}


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Convert inspected bookmark localizations into the standard manual-review format.")
  parser.add_argument("--localized-manifest", type=Path, required=True, help="localized_bookmarks.csv to convert.")
  parser.add_argument("--annotations", type=Path, required=True, help="CSV containing one reviewed row per localized record_key.")
  parser.add_argument("--output-dir", type=Path, required=True, help="Directory for queue, labels, and conversion summary.")
  parser.add_argument("--route", action="append", default=[], help="Optional log id or dongle/log id to include. Repeatable.")
  parser.add_argument("--allow-unreviewed", action="store_true", help="Allow localized rows without a matching annotation.")
  return parser.parse_args()


def read_csv(path: Path) -> list[dict[str, str]]:
  with path.open("r", encoding="utf-8", newline="") as handle:
    return list(csv.DictReader(handle))


def write_csv(path: Path, fieldnames: list[str], rows: list[dict[str, str]]) -> None:
  ensure_dir(path.parent)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    writer.writerows(rows)


def record_key(row: dict[str, str]) -> str:
  match = FRAME_KEY_RE.match(Path(row.get("frame_path", "")).stem)
  if match is None:
    raise ValueError(f"Cannot derive record key from frame path: {row.get('frame_path', '')}")
  return match.group("key")


def route_identity(row: dict[str, str]) -> tuple[str, str, str]:
  session_id = row.get("session_id", "")
  prefix = "connect_"
  if not session_id.startswith(prefix):
    raise ValueError(f"Unsupported bookmark session id: {session_id}")
  identity = session_id[len(prefix):]
  dongle_id, separator, log_id = identity.partition("_")
  if not separator or not dongle_id or not log_id:
    raise ValueError(f"Cannot parse route identity from session id: {session_id}")
  return f"{dongle_id}/{log_id}", dongle_id, log_id


def source_position(row: dict[str, str]) -> tuple[str, str]:
  if row.get("source_segment", "") and row.get("source_time_s", ""):
    return row["source_segment"], row["source_time_s"]

  bookmark_segment = int(row["segment"])
  relative_time_s = float(row["relative_time_s"])
  if relative_time_s < 0.0:
    return str(bookmark_segment - 1), f"{relative_time_s + 60.0:.3f}"
  return str(bookmark_segment), f"{relative_time_s:.3f}"


def parse_read(text: str) -> tuple[str, str]:
  speed, separator, confidence = (text or "").partition("@")
  return (speed, confidence) if separator else ("", "")


def nonzero_value(text: str) -> str:
  try:
    return text if float(text) > 0.0 else ""
  except (TypeError, ValueError):
    return ""


def queue_row(row: dict[str, str]) -> dict[str, str]:
  key = record_key(row)
  route, dongle_id, log_id = route_identity(row)
  segment, frame_time_s = source_position(row)
  candidate_speed, candidate_confidence = parse_read(row.get("model_read", ""))
  detector_class = DETECTOR_CLASSES.get(row.get("class_id", ""), "regulatory_speed_limit")
  read_sources = "model"
  if row.get("full_detection", ""):
    read_sources += ";full_detection"
  if row.get("event_type", "") == "visionPublish":
    read_sources += ";logged_vision_publish"

  review_reasons = ["corrected_source_timing"]
  review_priority = float(row.get("score") or 0.0)
  if row.get("event_type", "") == "visionPublish":
    published_speed = row.get("published_speed", "")
    review_reasons.extend(("route_vision_publish", f"published_{published_speed}"))
    if published_speed and candidate_speed and published_speed != candidate_speed:
      review_reasons.append("logged_current_value_disagreement")
      review_priority += 5.0
    map_speed = nonzero_value(row.get("map_speed", ""))
    if map_speed and published_speed and map_speed != published_speed:
      review_reasons.append("logged_map_disagreement")
      review_priority += 3.0
  else:
    review_reasons.append("route_bookmark")

  item = dict.fromkeys(FIELDNAMES, "")
  item.update({
    "record_key": key,
    "mining_fingerprint": "localized_bookmark_review_v1",
    "route": route,
    "dongle_id": dongle_id,
    "log_id": log_id,
    "segment": segment,
    "frame_time_s": frame_time_s,
    "frame_path": row.get("frame_path", ""),
    "crop_path": row.get("crop_path", ""),
    "source_video_path": row.get("source_video_path", ""),
    "bbox": row.get("box", ""),
    "crop_bbox": row.get("box", ""),
    "class_id": row.get("class_id", ""),
    "detector_class": detector_class,
    "proposal_confidence": row.get("proposal_confidence", ""),
    "candidate_speed_limit_mph": candidate_speed,
    "candidate_confidence": candidate_confidence,
    "model_read": row.get("model_read", ""),
    "ocr_read": row.get("ocr_read", ""),
    "full_detection": row.get("full_detection", ""),
    "read_sources": read_sources,
    "read_support_count": "1",
    "is_regulatory": row.get("is_regulatory", ""),
    "map_current_speed_limit_mph": nonzero_value(row.get("map_speed", "")),
    "map_next_speed_limit_mph": nonzero_value(row.get("next_speed", "")),
    "review_priority": f"{review_priority:.4f}",
    "review_reasons": ";".join(review_reasons),
  })
  return item


def main() -> int:
  args = parse_args()
  localized_path = args.localized_manifest.expanduser().resolve()
  annotations_path = args.annotations.expanduser().resolve()
  output_dir = ensure_dir(args.output_dir.expanduser().resolve())

  annotations = read_csv(annotations_path)
  annotations_by_key = {row["record_key"]: row for row in annotations if row.get("record_key")}
  if len(annotations_by_key) != len(annotations):
    raise ValueError("Annotations contain an empty or duplicate record_key")

  selected_routes = set(args.route)
  queue_rows: list[dict[str, str]] = []
  label_rows: list[dict[str, str]] = []
  localized_keys: set[str] = set()
  missing_annotations: list[str] = []
  for localized_row in read_csv(localized_path):
    route, _, log_id = route_identity(localized_row)
    if selected_routes and route not in selected_routes and log_id not in selected_routes:
      continue
    key = record_key(localized_row)
    localized_keys.add(key)
    annotation = annotations_by_key.get(key)
    if annotation is None:
      missing_annotations.append(key)
      if not args.allow_unreviewed:
        continue
    queue_rows.append(queue_row(localized_row))
    if annotation is not None:
      label = {field: annotation.get(field, "") for field in LABEL_FIELDNAMES}
      label["record_key"] = key
      label_rows.append(label)

  unused_annotations = sorted(set(annotations_by_key) - localized_keys)
  if missing_annotations and not args.allow_unreviewed:
    preview = ", ".join(missing_annotations[:5])
    raise ValueError(f"Missing annotations for {len(missing_annotations)} localized row(s): {preview}")
  if unused_annotations and not selected_routes:
    preview = ", ".join(unused_annotations[:5])
    raise ValueError(f"Annotations reference {len(unused_annotations)} unknown row(s): {preview}")

  queue_path = output_dir / "manual_review_queue.csv"
  labels_path = output_dir / "manual_review_labels.csv"
  write_csv(queue_path, FIELDNAMES, queue_rows)
  write_csv(labels_path, LABEL_FIELDNAMES, label_rows)

  summary = {
    "localized_manifest": str(localized_path),
    "annotations": str(annotations_path),
    "selected_routes": sorted(selected_routes),
    "queue_rows": len(queue_rows),
    "label_rows": len(label_rows),
    "missing_annotations": missing_annotations,
    "unused_annotations": unused_annotations,
    "queue": str(queue_path),
    "labels": str(labels_path),
  }
  summary_path = output_dir / "localized_review_conversion_summary.json"
  summary_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
  print(f"Wrote {len(queue_rows)} queue row(s) and {len(label_rows)} label row(s) to {output_dir}")
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
