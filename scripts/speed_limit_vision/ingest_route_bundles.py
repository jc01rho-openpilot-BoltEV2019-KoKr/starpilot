#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json
import re
import shutil
import time
import zipfile

from dataclasses import dataclass
from pathlib import Path

if __package__ in (None, ""):
  import sys
  sys.path.insert(0, str(Path(__file__).resolve().parent))
  from common import ensure_dir, preferred_clip_root, preferred_files_manifest_path, preferred_qlog_mtimes_path, resolve_workspace  # type: ignore
else:
  from .common import ensure_dir, preferred_clip_root, preferred_files_manifest_path, preferred_qlog_mtimes_path, resolve_workspace


DEFAULT_ROUTES_DIR = Path("/Volumes/T5/routes")
DEFAULT_WORKSPACE = Path("/Volumes/T5/starpilot_speed_limit/workspace/speed_limit_training_clean")
DEFAULT_BUNDLE_MANIFEST_DIR = Path("/Volumes/T5/starpilot_speed_limit/analysis/route_bundles/manifests")
DEFAULT_STATE_DIR = Path("/Volumes/T5/starpilot_speed_limit/analysis/route_bundles/state")

SEGMENT_FILE_RE = re.compile(r"/data/media/0/realdata/([^/]+)/(fcamera\.hevc|qlog\.zst|rlog\.zst|qlog\.bz2|rlog\.bz2)$")


@dataclass(frozen=True)
class BundleSummary:
  zip_path: Path
  bundle_name: str
  route_id: str
  dongle_id: str
  log_id: str
  size_bytes: int
  expected_segments: int
  segment_count: int
  fcamera_count: int
  qlog_count: int
  rlog_count: int
  git_commit: str
  platform: str
  start_time: str
  is_public: str
  maps_selected: str
  vision_detection: str
  auto_bookmark: str


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Inventory and extract StarPilot speed-limit route zip bundles into the SSD route corpus.")
  parser.add_argument("--routes-dir", type=Path, default=DEFAULT_ROUTES_DIR, help="Directory containing speed_limit_route_bundle_*.zip files.")
  parser.add_argument("--workspace", type=Path, default=DEFAULT_WORKSPACE, help="Training workspace root for review manifests.")
  parser.add_argument("--clip-root", type=Path, default=preferred_clip_root(), help="Destination realdata root.")
  parser.add_argument("--manifest-dir", type=Path, default=DEFAULT_BUNDLE_MANIFEST_DIR, help="Where bundle_manifest.json files are copied.")
  parser.add_argument("--state-dir", type=Path, default=DEFAULT_STATE_DIR, help="Where extraction marker files are written.")
  parser.add_argument("--inventory-out", type=Path, help="CSV inventory path. Defaults to <workspace>/review/route_bundle_inventory.csv.")
  parser.add_argument("--corpus-out", type=Path, help="CSV corpus path. Defaults to <workspace>/review/connect_route_corpus.csv.")
  parser.add_argument("--limit", type=int, default=0, help="Optional max number of bundles to process.")
  parser.add_argument("--extract", action="store_true", help="Extract route files into --clip-root.")
  parser.add_argument("--force", action="store_true", help="Re-extract files even when the bundle marker exists.")
  parser.add_argument("--overwrite-files", action="store_true", help="Overwrite existing destination segment files.")
  parser.add_argument("--dry-run", action="store_true", help="Inventory only; do not write extracted files or marker files.")
  return parser.parse_args()


def route_parts(route_id: str, fallback_log_id: str = "") -> tuple[str, str]:
  normalized = route_id.replace("|", "/")
  if "/" in normalized:
    dongle_id, log_id = normalized.split("/", 1)
    return dongle_id, log_id
  return "", fallback_log_id


def bundle_manifest_member(zip_file: zipfile.ZipFile) -> str | None:
  for name in zip_file.namelist():
    if name.endswith("/bundle_manifest.json") or name == "bundle_manifest.json":
      return name
  return None


def read_bundle_manifest(zip_path: Path) -> tuple[str, dict]:
  with zipfile.ZipFile(zip_path) as zip_file:
    member = bundle_manifest_member(zip_file)
    if member is None:
      return "", {}
    with zip_file.open(member) as manifest_file:
      return member.split("/", 1)[0], json.loads(manifest_file.read().decode("utf-8"))


def summarize_bundle(zip_path: Path) -> BundleSummary:
  bundle_name, manifest = read_bundle_manifest(zip_path)
  route_id = str(manifest.get("routeId") or manifest.get("routeFullname") or "")
  if not route_id:
    stem = zip_path.stem.replace("speed_limit_route_bundle_", "")
    parts = stem.split("_", 1)
    route_id = f"{parts[0]}/{parts[1]}" if len(parts) == 2 else stem

  _, inferred_log_id = route_parts(route_id)
  route_files = list(manifest.get("files") or [])
  segments = {str(row.get("segment")) for row in route_files if row.get("segment") is not None}
  fcamera_count = sum(1 for row in route_files if str(row.get("filename")) == "fcamera.hevc")
  qlog_count = sum(1 for row in route_files if str(row.get("filename")) in ("qlog.zst", "qlog.bz2") or str(row.get("stream")) == "qlog")
  rlog_count = sum(1 for row in route_files if str(row.get("filename")) in ("rlog.zst", "rlog.bz2") or str(row.get("stream")) == "rlog")

  if not route_files:
    with zipfile.ZipFile(zip_path) as zip_file:
      for member in zip_file.namelist():
        match = SEGMENT_FILE_RE.search(member)
        if match is None:
          continue
        segment_name, filename = match.groups()
        segments.add(segment_name.rsplit("--", 1)[-1])
        fcamera_count += filename == "fcamera.hevc"
        qlog_count += filename.startswith("qlog.")
        rlog_count += filename.startswith("rlog.")

  dongle_id, log_id = route_parts(route_id, inferred_log_id)
  route_meta = manifest.get("routeMeta") or {}
  validation = manifest.get("validation") or {}
  return BundleSummary(
    zip_path=zip_path,
    bundle_name=bundle_name or zip_path.stem,
    route_id=f"{dongle_id}/{log_id}" if dongle_id and log_id else route_id,
    dongle_id=dongle_id,
    log_id=log_id,
    size_bytes=zip_path.stat().st_size,
    expected_segments=int(manifest.get("expectedSegments") or 0),
    segment_count=len(segments),
    fcamera_count=int(fcamera_count),
    qlog_count=int(qlog_count),
    rlog_count=int(rlog_count),
    git_commit=str(route_meta.get("gitCommit") or ""),
    platform=str(route_meta.get("platform") or route_meta.get("make") or ""),
    start_time=str(route_meta.get("startTime") or ""),
    is_public=str(validation.get("isPublic") if "isPublic" in validation else ""),
    maps_selected=str(validation.get("mapsSelected") or ""),
    vision_detection=str(validation.get("visionSpeedLimitDetection") or ""),
    auto_bookmark=str(validation.get("visionSpeedLimitAutoBookmark") or ""),
  )


def marker_path(state_dir: Path, summary: BundleSummary) -> Path:
  safe_route = summary.route_id.replace("/", "_").replace("|", "_")
  return state_dir / f"{safe_route}.json"


def write_json(path: Path, data: dict) -> None:
  ensure_dir(path.parent)
  path.write_text(json.dumps(data, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def extract_member(zip_file: zipfile.ZipFile, member: str, destination: Path, overwrite: bool) -> bool:
  if destination.exists() and not overwrite:
    return False
  ensure_dir(destination.parent)
  tmp_path = destination.with_name(f".{destination.name}.tmp")
  with zip_file.open(member) as src, tmp_path.open("wb") as dst:
    shutil.copyfileobj(src, dst, length=1024 * 1024)
  tmp_path.replace(destination)
  return True


def extract_bundle(summary: BundleSummary, clip_root: Path, manifest_dir: Path, state_dir: Path, overwrite_files: bool, force: bool, dry_run: bool) -> dict:
  marker = marker_path(state_dir, summary)
  if marker.exists() and not force:
    return {"status": "skipped", "reason": "marker_exists", "written": 0, "skipped": 0}

  written = 0
  skipped = 0
  started_at = time.time()
  with zipfile.ZipFile(summary.zip_path) as zip_file:
    manifest_member = bundle_manifest_member(zip_file)
    if manifest_member is not None and not dry_run:
      extract_member(zip_file, manifest_member, manifest_dir / f"{summary.route_id.replace('/', '_')}.json", overwrite=True)

    for member in zip_file.namelist():
      match = SEGMENT_FILE_RE.search(member)
      if match is None:
        continue
      segment_name, filename = match.groups()
      destination = clip_root / segment_name / filename
      if dry_run:
        skipped += int(destination.exists())
        written += int(not destination.exists())
        continue
      if extract_member(zip_file, member, destination, overwrite=overwrite_files):
        written += 1
      else:
        skipped += 1

  result = {
    "status": "dry_run" if dry_run else "extracted",
    "route_id": summary.route_id,
    "zip_path": str(summary.zip_path),
    "written": written,
    "skipped": skipped,
    "duration_s": round(time.time() - started_at, 3),
  }
  if not dry_run:
    write_json(marker, result)
  return result


def write_inventory(path: Path, summaries: list[BundleSummary]) -> None:
  ensure_dir(path.parent)
  fieldnames = [
    "route_id", "dongle_id", "log_id", "zip_path", "size_bytes", "expected_segments", "segment_count",
    "fcamera_count", "qlog_count", "rlog_count", "git_commit", "platform", "start_time", "is_public",
    "maps_selected", "vision_detection", "auto_bookmark",
  ]
  with path.open("w", encoding="utf-8", newline="") as csv_file:
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
    writer.writeheader()
    for summary in summaries:
      writer.writerow({
        "route_id": summary.route_id,
        "dongle_id": summary.dongle_id,
        "log_id": summary.log_id,
        "zip_path": str(summary.zip_path),
        "size_bytes": summary.size_bytes,
        "expected_segments": summary.expected_segments,
        "segment_count": summary.segment_count,
        "fcamera_count": summary.fcamera_count,
        "qlog_count": summary.qlog_count,
        "rlog_count": summary.rlog_count,
        "git_commit": summary.git_commit,
        "platform": summary.platform,
        "start_time": summary.start_time,
        "is_public": summary.is_public,
        "maps_selected": summary.maps_selected,
        "vision_detection": summary.vision_detection,
        "auto_bookmark": summary.auto_bookmark,
      })


def load_existing_corpus(path: Path) -> dict[str, dict[str, str]]:
  if not path.is_file():
    return {}
  with path.open("r", encoding="utf-8", newline="") as csv_file:
    reader = csv.DictReader(csv_file)
    rows = {}
    for row in reader:
      route = row.get("route") or row.get("route_id") or ""
      if route:
        rows[route] = row
    return rows


def write_corpus(path: Path, summaries: list[BundleSummary]) -> None:
  ensure_dir(path.parent)
  existing = load_existing_corpus(path)
  for summary in summaries:
    full_video = summary.expected_segments == 0 or summary.fcamera_count >= min(summary.expected_segments, summary.segment_count)
    route_status = "full_fcamera" if full_video and summary.fcamera_count else "partial_or_missing_fcamera"
    existing[summary.route_id] = {
      "route": summary.route_id,
      "dongle_id": summary.dongle_id,
      "log_id": summary.log_id,
      "status": route_status,
      "source": "route_zip_bundle",
      "expected_segments": str(summary.expected_segments),
      "fcamera_segments": str(summary.fcamera_count),
      "qlog_segments": str(summary.qlog_count),
      "rlog_segments": str(summary.rlog_count),
      "bookmark_count": existing.get(summary.route_id, {}).get("bookmark_count", ""),
      "vision_source_messages": existing.get(summary.route_id, {}).get("vision_source_messages", ""),
      "zip_path": str(summary.zip_path),
      "git_commit": summary.git_commit,
      "platform": summary.platform,
      "start_time": summary.start_time,
      "notes": "Imported from /Volumes/T5/routes zip bundle; not treated as labeled positives by default.",
    }

  fieldnames = [
    "route", "dongle_id", "log_id", "status", "source", "expected_segments", "fcamera_segments",
    "qlog_segments", "rlog_segments", "bookmark_count", "vision_source_messages", "zip_path",
    "git_commit", "platform", "start_time", "notes",
  ]
  with path.open("w", encoding="utf-8", newline="") as csv_file:
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames, extrasaction="ignore")
    writer.writeheader()
    for route in sorted(existing):
      writer.writerow(existing[route])


def refresh_route_meta_files(clip_root: Path, files_manifest: Path, qlog_mtimes: Path) -> None:
  ensure_dir(files_manifest.parent)
  rows: list[str] = []
  mtimes: list[str] = []
  for segment_dir in sorted((path for path in clip_root.iterdir() if path.is_dir()), key=lambda path: path.name):
    for filename in ("fcamera.hevc", "qlog.zst", "rlog.zst", "qlog.bz2", "rlog.bz2"):
      file_path = segment_dir / filename
      if not file_path.is_file():
        continue
      rows.append(str(file_path))
      if filename.startswith("qlog."):
        mtimes.append(f"{file_path} {int(file_path.stat().st_mtime)}")
  files_manifest.write_text("\n".join(rows) + ("\n" if rows else ""), encoding="utf-8")
  qlog_mtimes.write_text("\n".join(mtimes) + ("\n" if mtimes else ""), encoding="utf-8")


def main() -> int:
  args = parse_args()
  workspace = resolve_workspace(args.workspace)
  routes_dir = args.routes_dir.expanduser().resolve()
  clip_root = args.clip_root.expanduser().resolve()
  manifest_dir = args.manifest_dir.expanduser().resolve()
  state_dir = args.state_dir.expanduser().resolve()
  inventory_out = args.inventory_out.expanduser().resolve() if args.inventory_out else (ensure_dir(workspace / "review") / "route_bundle_inventory.csv")
  corpus_out = args.corpus_out.expanduser().resolve() if args.corpus_out else (ensure_dir(workspace / "review") / "connect_route_corpus.csv")

  zip_paths = sorted(routes_dir.glob("*.zip"))
  if args.limit > 0:
    zip_paths = zip_paths[:args.limit]
  if not zip_paths:
    raise FileNotFoundError(f"No .zip bundles found under {routes_dir}")

  ensure_dir(clip_root)
  ensure_dir(manifest_dir)
  ensure_dir(state_dir)

  summaries: list[BundleSummary] = []
  for zip_path in zip_paths:
    try:
      summaries.append(summarize_bundle(zip_path))
    except Exception as exc:
      print(f"ERROR inventory {zip_path}: {exc}")

  write_inventory(inventory_out, summaries)
  write_corpus(corpus_out, summaries)
  print(f"Inventory: {inventory_out}")
  print(f"Corpus:    {corpus_out}")
  print(f"Bundles:   {len(summaries)}")
  print(f"Segments:  {sum(summary.segment_count for summary in summaries)}")
  print(f"fcamera:   {sum(summary.fcamera_count for summary in summaries)}")

  if args.extract:
    for index, summary in enumerate(summaries, start=1):
      result = extract_bundle(summary, clip_root, manifest_dir, state_dir, args.overwrite_files, args.force, args.dry_run)
      print(
        f"[{index}/{len(summaries)}] {summary.route_id}: {result['status']} "
        f"written={result['written']} skipped={result['skipped']} {result.get('reason', '')}"
      )
    if not args.dry_run:
      refresh_route_meta_files(clip_root, preferred_files_manifest_path(), preferred_qlog_mtimes_path())
      print(f"Clip root: {clip_root}")
      print(f"Files manifest: {preferred_files_manifest_path()}")
      print(f"Qlog mtimes:    {preferred_qlog_mtimes_path()}")

  return 0


if __name__ == "__main__":
  raise SystemExit(main())
