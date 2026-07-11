#!/bin/sh
""":"
REPO_ROOT="$(CDPATH= cd -- "$(dirname "$0")/../.." && pwd)"
PYTHON_BIN="$REPO_ROOT/.venv/bin/python"

if [ -x "$PYTHON_BIN" ]; then
  exec "$PYTHON_BIN" "$0" "$@"
fi

exec python3 "$0" "$@"
":"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

if len(sys.argv) < 4:
  print(f"{sys.argv[0]} <route> <segment> <frame number> [front|wide|driver]")
  print('example: ./fetch_image_from_route.py "02c45f73a2e5c6e9|2020-06-01--18-03-08" 3 500 driver')
  exit(0)

cameras = {
  "front": "cameras",
  "wide": "ecameras",
  "driver": "dcameras"
}

from PIL import Image
from openpilot.tools.lib.framereader import FrameReader
from openpilot.tools.lib.route import Route

route = sys.argv[1]
segment = int(sys.argv[2])
frame = int(sys.argv[3])
camera = cameras[sys.argv[4]] if len(sys.argv) > 4 and sys.argv[4] in cameras else "cameras"

route_files = Route(route)
segments = {
  "cameras": route_files.camera_paths(),
  "ecameras": route_files.ecamera_paths(),
  "dcameras": route_files.dcamera_paths(),
}[camera]
if segment >= len(segments) or segments[segment] is None:
  raise Exception(f"segment {segment} not found, got {len(segments)} segments")

fr = FrameReader(segments[segment])
if frame >= fr.frame_count:
  raise Exception("frame {frame} not found, got {fr.frame_count} frames")

im = Image.fromarray(fr.get(frame))
fn = f"uxxx_{route.replace('|', '_')}_{segment}_{frame}.png"
im.save(fn)
print(f"saved {fn}")
