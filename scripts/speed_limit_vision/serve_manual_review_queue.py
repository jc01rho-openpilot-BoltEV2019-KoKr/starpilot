#!/usr/bin/env python3
from __future__ import annotations

import argparse
import csv
import json

from datetime import UTC, datetime
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, urlparse


QUEUE_REVIEW_FIELDS = [
  "review_status",
  "review_speed_limit_mph",
  "review_sign_type",
  "review_bbox",
  "review_ignore_reason",
  "review_notes",
]

LABEL_FIELDNAMES = [
  "record_key",
  "review_status",
  "review_speed_limit_mph",
  "review_sign_type",
  "review_bbox",
  "review_ignore_reason",
  "review_notes",
  "reviewed_at_unix",
]

HTML = r"""<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>Speed Limit Review</title>
  <style>
    :root { color-scheme: dark; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif; }
    body { margin: 0; background: #111; color: #eee; }
    header { display: flex; align-items: center; gap: 16px; padding: 10px 14px; background: #1b1b1b; }
    header { border-bottom: 1px solid #333; position: sticky; top: 0; z-index: 2; }
    button, select, input, textarea { background: #222; color: #eee; border: 1px solid #555; border-radius: 6px; padding: 7px 9px; font: inherit; }
    button { cursor: pointer; }
    button:hover { background: #333; }
    button.primary { background: #285f9f; border-color: #3f7ec8; }
    button.warn { background: #6b3b18; border-color: #9a5a25; }
    main { display: grid; grid-template-columns: minmax(360px, 1fr) 420px; gap: 12px; padding: 12px; }
    .images { display: grid; gap: 12px; align-content: start; }
    .panel { background: #181818; border: 1px solid #303030; border-radius: 8px; padding: 10px; }
    .imageWrap { display: grid; place-items: center; background: #050505; border-radius: 6px; min-height: 160px; overflow: hidden; }
    .frameStage { position: relative; display: inline-block; max-width: 100%; }
    .frameStage img { display: block; }
    #bboxCanvas { position: absolute; inset: 0; width: 100%; height: 100%; cursor: crosshair; touch-action: none; }
    img { max-width: 100%; max-height: 52vh; object-fit: contain; }
    .crop img { image-rendering: auto; max-height: 28vh; }
    .meta { display: grid; gap: 5px; font-size: 13px; color: #ddd; }
    .meta code { color: #cfe5ff; overflow-wrap: anywhere; }
    .buttons { display: flex; flex-wrap: wrap; gap: 6px; margin: 8px 0; }
    .buttons button.active { outline: 2px solid #ddd; background: #345; }
    textarea { width: 100%; min-height: 70px; box-sizing: border-box; }
    .speed button { min-width: 42px; }
    .muted { color: #aaa; }
    .status { white-space: nowrap; }
    .hint { margin-bottom: 10px; padding: 8px; border-left: 3px solid #3f7ec8; background: #20252b; color: #dbeaff; }
    @media (max-width: 980px) { main { grid-template-columns: 1fr; } img { max-height: 45vh; } }
  </style>
</head>
<body>
  <header>
    <button id="prevBtn">Prev</button>
    <button id="nextBtn" class="primary">Next</button>
    <select id="filter">
      <option value="unreviewed">Unreviewed</option>
      <option value="all">All</option>
      <option value="school">School Zone</option>
      <option value="priority">Priority 30-65</option>
      <option value="disagreement">Disagreement</option>
      <option value="negative">Negatives</option>
    </select>
    <span class="status" id="status"></span>
    <span class="muted">Keys: Space/p accept model, type speed to correct, u uncertain, i/x ignore,
      Enter save correction, j/k next/prev, s school, r regulatory, a advisory</span>
  </header>
  <main>
    <section class="images">
      <div class="panel crop">
        <div class="muted">Crop</div>
        <div class="imageWrap"><img id="cropImg"></div>
      </div>
      <div class="panel">
        <div class="muted">Frame</div>
        <div class="imageWrap"><div class="frameStage"><img id="frameImg"><canvas id="bboxCanvas"></canvas></div></div>
      </div>
    </section>
    <aside class="panel">
      <div class="hint" id="taskHint" hidden></div>
      <div class="meta" id="meta"></div>
      <h3>Speed</h3>
      <div class="buttons speed" id="speedButtons"></div>
      <h3>Type</h3>
      <div class="buttons" id="typeButtons">
        <button data-type="regulatory">Regulatory</button>
        <button data-type="school_zone">School Zone</button>
        <button data-type="advisory">Advisory</button>
        <button data-type="construction">Construction</button>
        <button data-type="not_speed_limit">Not Speed Limit</button>
      </div>
      <h3>Action</h3>
      <div class="buttons" id="statusButtons">
        <button data-status="ignore" class="warn">Ignore / Bad Crop (i/x)</button>
        <button data-status="uncertain">Uncertain (u)</button>
        <button data-status="needs_later">Needs Later</button>
      </div>
      <label>Box (optional - redraw only when the current box is wrong)</label>
      <input id="bboxInput" placeholder="Drag around the complete sign only when correction is needed">
      <div class="buttons">
        <button id="clearBBoxBtn">Clear Box (b)</button>
      </div>
      <label>Ignore reason</label>
      <input id="ignoreReason" placeholder="false_positive, blurry, side_road, duplicate">
      <label>Notes</label>
      <textarea id="notes"></textarea>
      <div class="buttons">
        <button id="acceptPredBtn">Accept Model Prediction (Space)</button>
        <button id="saveBtn" class="primary">Save Correction (Enter)</button>
      </div>
    </aside>
  </main>
<script>
const speeds = [15,20,25,30,35,40,45,50,55,60,65,70,75];
let rows = [];
let index = 0;
let current = null;
let draft = {};
let speedBuffer = "";
let speedBufferTimer = null;
let drawingBox = false;
let drawingStart = null;
let previewBox = null;

function qs(sel) { return document.querySelector(sel); }
function qsa(sel) { return Array.from(document.querySelectorAll(sel)); }

async function loadQueue() {
  const filter = qs("#filter").value;
  const res = await fetch(`/api/queue?filter=${encodeURIComponent(filter)}`);
  const data = await res.json();
  rows = data.rows;
  index = 0;
  render();
}

function setActive(selector, attr, value) {
  qsa(selector).forEach(btn => btn.classList.toggle("active", btn.dataset[attr] === String(value)));
}

function clamp(value, min, max) {
  return Math.max(min, Math.min(max, value));
}

function parseBBox(text) {
  const values = String(text || "").split(",").map(v => Number(v.trim()));
  if (values.length !== 4 || values.some(v => !Number.isFinite(v))) return null;
  const [x1, y1, x2, y2] = values.map(v => Math.round(v));
  if (x2 <= x1 || y2 <= y1) return null;
  return [x1, y1, x2, y2];
}

function formatBBox(box) {
  return box.map(v => String(Math.round(v))).join(",");
}

function setBBox(text, shouldDraw = true) {
  draft.review_bbox = text || "";
  qs("#bboxInput").value = draft.review_bbox;
  if (shouldDraw) drawBBox();
}

function canvasPoint(ev) {
  const canvas = qs("#bboxCanvas");
  const img = qs("#frameImg");
  const rect = canvas.getBoundingClientRect();
  if (!img.naturalWidth || !img.naturalHeight || rect.width <= 0 || rect.height <= 0) return null;
  const x = clamp(Math.round((ev.clientX - rect.left) * img.naturalWidth / rect.width), 0, img.naturalWidth - 1);
  const y = clamp(Math.round((ev.clientY - rect.top) * img.naturalHeight / rect.height), 0, img.naturalHeight - 1);
  return [x, y];
}

function boxToCanvas(box) {
  const img = qs("#frameImg");
  const canvas = qs("#bboxCanvas");
  const sx = canvas.width / img.naturalWidth;
  const sy = canvas.height / img.naturalHeight;
  return [box[0] * sx, box[1] * sy, box[2] * sx, box[3] * sy];
}

function drawBBox() {
  const canvas = qs("#bboxCanvas");
  const img = qs("#frameImg");
  const ctx = canvas.getContext("2d");
  const displayWidth = Math.round(img.clientWidth || 0);
  const displayHeight = Math.round(img.clientHeight || 0);
  if (displayWidth > 0 && displayHeight > 0 && (canvas.width !== displayWidth || canvas.height !== displayHeight)) {
    canvas.width = displayWidth;
    canvas.height = displayHeight;
  }
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  if (!img.naturalWidth || !img.naturalHeight || canvas.width <= 0 || canvas.height <= 0) return;

  const box = previewBox || parseBBox(draft.review_bbox);
  if (!box) return;
  const [x1, y1, x2, y2] = boxToCanvas(box);
  ctx.lineWidth = 3;
  ctx.strokeStyle = previewBox ? "#ffd24a" : "#39a7ff";
  ctx.fillStyle = "rgba(57, 167, 255, 0.12)";
  ctx.fillRect(x1, y1, x2 - x1, y2 - y1);
  ctx.strokeRect(x1, y1, x2 - x1, y2 - y1);
}

function startBoxDraw(ev) {
  if (!current) return;
  const point = canvasPoint(ev);
  if (!point) return;
  ev.preventDefault();
  drawingBox = true;
  drawingStart = point;
  previewBox = [point[0], point[1], point[0] + 1, point[1] + 1];
  qs("#bboxCanvas").setPointerCapture(ev.pointerId);
  drawBBox();
}

function moveBoxDraw(ev) {
  if (!drawingBox || !drawingStart) return;
  const point = canvasPoint(ev);
  if (!point) return;
  ev.preventDefault();
  previewBox = [
    Math.min(drawingStart[0], point[0]),
    Math.min(drawingStart[1], point[1]),
    Math.max(drawingStart[0], point[0]),
    Math.max(drawingStart[1], point[1]),
  ];
  drawBBox();
}

function finishBoxDraw(ev) {
  if (!drawingBox) return;
  ev.preventDefault();
  drawingBox = false;
  const finalBox = previewBox;
  previewBox = null;
  drawingStart = null;
  if (finalBox && finalBox[2] - finalBox[0] >= 4 && finalBox[3] - finalBox[1] >= 4) {
    setBBox(formatBBox(finalBox));
  } else {
    drawBBox();
  }
}

function clearSpeedBuffer() {
  speedBuffer = "";
  if (speedBufferTimer) clearTimeout(speedBufferTimer);
  speedBufferTimer = null;
}

function inferredType(row) {
  if (!row) return "";
  if (row.detector_class === "school_zone_speed_limit") return "school_zone";
  if (row.detector_class === "advisory_speed_limit") return "advisory";
  if (row.detector_class === "negative_empty") return "not_speed_limit";
  return "regulatory";
}

function auditHint(row) {
  if (!row) return "";
  const previous = row.before_speed_limit_mph || "no value";
  const candidate = row.candidate_speed_limit_mph || "no value";
  if (row.comparison_change === "advisory_type_reaudit") {
    return `Recheck sign type for reviewed ${candidate}: Space = regulatory; A then Space = advisory; S then Space = school zone.`;
  }
  if (row.comparison_change === "lost_read") {
    return `Current model rejected previous ${previous}. Type the speed if readable; press i if it is not a speed sign.`;
  }
  if (row.comparison_change === "gained_read") return `Current model gained ${candidate}. Press Space if correct, or type the correct speed.`;
  if (row.comparison_change === "value_changed") {
    return `Model changed ${previous} to ${candidate}. Press Space for the current value, or type the correct speed.`;
  }
  return "";
}

function ensureSpeedSignType() {
  if (draft.review_sign_type === "not_speed_limit") {
    draft.review_sign_type = "regulatory";
    setActive("#typeButtons button", "type", draft.review_sign_type);
  }
}

function renderSpeedButtons() {
  const root = qs("#speedButtons");
  root.innerHTML = "";
  for (const speed of speeds) {
    const btn = document.createElement("button");
    btn.textContent = speed;
    btn.dataset.speed = speed;
    btn.onclick = () => {
      setSpeed(speed, false);
    };
    root.appendChild(btn);
  }
}

function setSpeed(speed, shouldSave) {
  draft.review_speed_limit_mph = String(speed);
  ensureSpeedSignType();
  setActive("#speedButtons button", "speed", speed);
  if (shouldSave) save(true, "corrected");
}

function handleDigitShortcut(digit) {
  speedBuffer += digit;
  if (speedBuffer.length > 2) speedBuffer = speedBuffer.slice(-2);
  if (speedBufferTimer) clearTimeout(speedBufferTimer);
  speedBufferTimer = setTimeout(clearSpeedBuffer, 1000);

  if (speedBuffer.length < 2) return;

  const speed = Number(speedBuffer);
  clearSpeedBuffer();
  if (speeds.includes(speed)) {
    setSpeed(speed, true);
    return;
  }

  speedBuffer = digit;
  speedBufferTimer = setTimeout(clearSpeedBuffer, 1000);
}

function render() {
  current = rows[index] || null;
  if (!current) {
    qs("#status").textContent = "No rows";
    qs("#meta").innerHTML = "";
    qs("#cropImg").removeAttribute("src");
    qs("#frameImg").removeAttribute("src");
    return;
  }
  draft = {
    review_status: current.review_status || "",
    review_speed_limit_mph: current.review_speed_limit_mph || current.candidate_speed_limit_mph || "",
    review_sign_type: current.review_sign_type || "regulatory",
    review_bbox: current.review_bbox || current.bbox || "",
    review_ignore_reason: current.review_ignore_reason || "",
    review_notes: current.review_notes || "",
  };
  qs("#status").textContent = `${index + 1}/${rows.length}`;
  const hint = auditHint(current);
  qs("#taskHint").textContent = hint;
  qs("#taskHint").hidden = !hint;
  qs("#cropImg").src = current.crop_path ? `/media/${current.record_key}/crop` : "";
  qs("#frameImg").src = `/media/${current.record_key}/frame`;
  setBBox(draft.review_bbox, false);
  qs("#ignoreReason").value = draft.review_ignore_reason;
  qs("#notes").value = draft.review_notes;
  setActive("#speedButtons button", "speed", draft.review_speed_limit_mph);
  setActive("#typeButtons button", "type", draft.review_sign_type);
  setActive("#statusButtons button", "status", draft.review_status);
  qs("#acceptPredBtn").disabled = !current.candidate_speed_limit_mph;
  const mapSummary = `${current.map_relation} current=${current.map_current_speed_limit_mph}`;
  const nextMapSummary = `next=${current.map_next_speed_limit_mph} dist=${current.map_next_speed_limit_distance_m}`;
  qs("#meta").innerHTML = [
    ["record", current.record_key],
    ["change", current.comparison_change],
    ["previous", `${current.before_speed_limit_mph || "none"} @ ${current.before_confidence || ""}`],
    ["candidate", `${current.candidate_speed_limit_mph || "none"} @ ${current.candidate_confidence || ""}`],
    ["class", `${current.detector_class} (${current.proposal_confidence})`],
    ["bbox", draft.review_bbox],
    ["reasons", current.review_reasons],
    ["map", `${mapSummary} ${nextMapSummary}`],
    ["reads", current.read_sources],
    ["route", current.route],
    ["time", `seg ${current.segment} @ ${current.frame_time_s}s`],
  ].map(([k,v]) => `<div><span class="muted">${k}:</span> <code>${String(v || "")}</code></div>`).join("");
}

function manualReviewStatus() {
  if (draft.review_status === "ignore" || draft.review_status === "needs_later" || draft.review_status === "uncertain") return draft.review_status;
  return "corrected";
}

async function save(moveNext = true, forcedStatus = null) {
  if (!current) return;
  draft.review_status = forcedStatus || manualReviewStatus();
  draft.review_bbox = qs("#bboxInput").value.trim();
  draft.review_ignore_reason = qs("#ignoreReason").value;
  draft.review_notes = qs("#notes").value;
  const payload = {record_key: current.record_key, ...draft};
  const res = await fetch("/api/review", {method: "POST", headers: {"Content-Type": "application/json"}, body: JSON.stringify(payload)});
  if (!res.ok) {
    alert(await res.text());
    return;
  }
  Object.assign(current, payload);
  if (moveNext) next();
  else render();
}

function next() { if (index < rows.length - 1) { index += 1; render(); } }
function prev() { if (index > 0) { index -= 1; render(); } }

renderSpeedButtons();
qs("#filter").onchange = loadQueue;
qs("#nextBtn").onclick = next;
qs("#prevBtn").onclick = prev;
qs("#saveBtn").onclick = () => save(true);
qs("#clearBBoxBtn").onclick = () => setBBox("");
qs("#acceptPredBtn").onclick = () => {
  if (!current) return;
  draft.review_speed_limit_mph = current.candidate_speed_limit_mph || "";
  save(true, "accepted");
};
qsa("#typeButtons button").forEach(btn => btn.onclick = () => {
  draft.review_sign_type = btn.dataset.type;
  setActive("#typeButtons button", "type", draft.review_sign_type);
});
qsa("#statusButtons button").forEach(btn => btn.onclick = () => {
  draft.review_status = btn.dataset.status;
  setActive("#statusButtons button", "status", draft.review_status);
});
qs("#bboxInput").oninput = () => setBBox(qs("#bboxInput").value.trim());
qs("#frameImg").onload = () => drawBBox();
qs("#bboxCanvas").addEventListener("pointerdown", startBoxDraw);
qs("#bboxCanvas").addEventListener("pointermove", moveBoxDraw);
qs("#bboxCanvas").addEventListener("pointerup", finishBoxDraw);
qs("#bboxCanvas").addEventListener("pointercancel", finishBoxDraw);
window.addEventListener("resize", drawBBox);
document.addEventListener("keydown", ev => {
  if (ev.target.tagName === "TEXTAREA" || ev.target.tagName === "INPUT") return;
  const key = ev.key.toLowerCase();
  if (/^[0-9]$/.test(ev.key)) {
    ev.preventDefault();
    handleDigitShortcut(ev.key);
    return;
  }
  if (key === "j") { clearSpeedBuffer(); next(); }
  if (key === "k") { clearSpeedBuffer(); prev(); }
  if (ev.key === " " || key === "p") {
    ev.preventDefault();
    clearSpeedBuffer();
    qs("#acceptPredBtn").click();
    return;
  }
  if (key === "s") { clearSpeedBuffer(); draft.review_sign_type = "school_zone"; setActive("#typeButtons button", "type", "school_zone"); }
  if (key === "r") { clearSpeedBuffer(); draft.review_sign_type = "regulatory"; setActive("#typeButtons button", "type", "regulatory"); }
  if (key === "a") { clearSpeedBuffer(); draft.review_sign_type = "advisory"; setActive("#typeButtons button", "type", "advisory"); }
  if (key === "b") {
    clearSpeedBuffer();
    setBBox("");
    return;
  }
  if (key === "i" || key === "x") {
    clearSpeedBuffer();
    draft.review_status = "ignore";
    draft.review_sign_type = "not_speed_limit";
    setActive("#statusButtons button", "status", "ignore");
    setActive("#typeButtons button", "type", "not_speed_limit");
    save(true, "ignore");
    return;
  }
  if (key === "u") {
    clearSpeedBuffer();
    draft.review_status = "uncertain";
    if (!draft.review_speed_limit_mph) draft.review_speed_limit_mph = current.candidate_speed_limit_mph || "";
    ensureSpeedSignType();
    setActive("#statusButtons button", "status", "uncertain");
    setActive("#speedButtons button", "speed", draft.review_speed_limit_mph);
    setActive("#typeButtons button", "type", draft.review_sign_type);
    save(true, "uncertain");
    return;
  }
  if (key === "enter") { clearSpeedBuffer(); save(true); }
});
loadQueue();
</script>
</body>
</html>
"""


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Serve a small browser UI for manually reviewing speed-limit queue rows.")
  parser.add_argument("--manifest", type=Path, required=True, help="manual_review_queue.csv from build_manual_review_queue.py")
  parser.add_argument("--labels-out", type=Path, help="Defaults to <manifest_dir>/manual_review_labels.csv")
  parser.add_argument("--host", default="127.0.0.1")
  parser.add_argument("--port", type=int, default=8765)
  return parser.parse_args()


def load_csv(path: Path) -> list[dict[str, str]]:
  with path.open("r", encoding="utf-8", newline="") as handle:
    return list(csv.DictReader(handle))


def load_labels(path: Path) -> dict[str, dict[str, str]]:
  if not path.is_file():
    return {}
  rows = load_csv(path)
  return {row["record_key"]: row for row in rows if row.get("record_key")}


def write_labels(path: Path, labels: dict[str, dict[str, str]]) -> None:
  path.parent.mkdir(parents=True, exist_ok=True)
  with path.open("w", encoding="utf-8", newline="") as handle:
    writer = csv.DictWriter(handle, fieldnames=LABEL_FIELDNAMES, extrasaction="ignore")
    writer.writeheader()
    for key in sorted(labels):
      writer.writerow(labels[key])


def merged_rows(rows: list[dict[str, str]], labels: dict[str, dict[str, str]]) -> list[dict[str, str]]:
  merged = []
  for row in rows:
    item = dict(row)
    label = labels.get(row.get("record_key", ""))
    if label:
      item.update({field: label.get(field, "") for field in QUEUE_REVIEW_FIELDS})
    merged.append(item)
  return merged


def filter_rows(rows: list[dict[str, str]], filter_name: str) -> list[dict[str, str]]:
  if filter_name == "all":
    return rows
  if filter_name == "school":
    return [row for row in rows if "school_zone" in row.get("detector_class", "") or "school_zone_candidate" in row.get("review_reasons", "")]
  if filter_name == "priority":
    return [row for row in rows if "priority_30_65" in row.get("review_reasons", "")]
  if filter_name == "disagreement":
    return [row for row in rows if "disagreement" in row.get("review_reasons", "") or "multi_value_votes" in row.get("review_reasons", "")]
  if filter_name == "negative":
    return [row for row in rows if row.get("detector_class") == "negative_empty"]
  return [row for row in rows if not row.get("review_status")]


class ReviewServer(ThreadingHTTPServer):
  def __init__(self, server_address, handler_class, manifest_path: Path, labels_path: Path):
    super().__init__(server_address, handler_class)
    self.manifest_path = manifest_path
    self.labels_path = labels_path
    self.rows = load_csv(manifest_path)
    self.row_by_key = {row["record_key"]: row for row in self.rows}
    self.labels = load_labels(labels_path)


class Handler(BaseHTTPRequestHandler):
  server: ReviewServer

  def log_message(self, _format, *args):
    return

  def send_json(self, data, status=HTTPStatus.OK):
    body = json.dumps(data).encode("utf-8")
    self.send_response(status)
    self.send_header("Content-Type", "application/json")
    self.send_header("Content-Length", str(len(body)))
    self.end_headers()
    self.wfile.write(body)

  def send_text(self, text: str, status=HTTPStatus.OK, content_type="text/html; charset=utf-8"):
    body = text.encode("utf-8")
    self.send_response(status)
    self.send_header("Content-Type", content_type)
    self.send_header("Content-Length", str(len(body)))
    self.end_headers()
    self.wfile.write(body)

  def do_GET(self):
    parsed = urlparse(self.path)
    if parsed.path == "/":
      self.send_text(HTML)
      return
    if parsed.path == "/api/queue":
      params = parse_qs(parsed.query)
      filter_name = params.get("filter", ["unreviewed"])[0]
      rows = filter_rows(merged_rows(self.server.rows, self.server.labels), filter_name)
      self.send_json({"rows": rows, "count": len(rows), "reviewed": len(self.server.labels)})
      return
    if parsed.path.startswith("/media/"):
      parts = parsed.path.strip("/").split("/")
      if len(parts) != 3:
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      _, record_key, kind = parts
      row = self.server.row_by_key.get(record_key)
      if row is None:
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      image_path = Path(row.get("crop_path" if kind == "crop" else "frame_path", ""))
      if not image_path.is_file():
        self.send_error(HTTPStatus.NOT_FOUND)
        return
      body = image_path.read_bytes()
      self.send_response(HTTPStatus.OK)
      self.send_header("Content-Type", "image/jpeg")
      self.send_header("Content-Length", str(len(body)))
      self.end_headers()
      self.wfile.write(body)
      return
    self.send_error(HTTPStatus.NOT_FOUND)

  def do_POST(self):
    if urlparse(self.path).path != "/api/review":
      self.send_error(HTTPStatus.NOT_FOUND)
      return
    length = int(self.headers.get("Content-Length", "0"))
    try:
      payload = json.loads(self.rfile.read(length).decode("utf-8"))
    except Exception:
      self.send_error(HTTPStatus.BAD_REQUEST, "Invalid JSON")
      return
    record_key = str(payload.get("record_key") or "")
    if record_key not in self.server.row_by_key:
      self.send_error(HTTPStatus.BAD_REQUEST, "Unknown record_key")
      return
    label = {"record_key": record_key, "reviewed_at_unix": f"{datetime.now(UTC).timestamp():.3f}"}
    for field in QUEUE_REVIEW_FIELDS:
      label[field] = str(payload.get(field) or "")
    self.server.labels[record_key] = label
    write_labels(self.server.labels_path, self.server.labels)
    self.send_json({"ok": True, "reviewed": len(self.server.labels)})


def main() -> int:
  args = parse_args()
  manifest_path = args.manifest.expanduser().resolve()
  labels_path = args.labels_out.expanduser().resolve() if args.labels_out else manifest_path.with_name("manual_review_labels.csv")
  server = ReviewServer((args.host, args.port), Handler, manifest_path, labels_path)
  print(f"Review UI: http://{args.host}:{args.port}")
  print(f"Manifest:  {manifest_path}")
  print(f"Labels:    {labels_path}")
  try:
    server.serve_forever()
  except KeyboardInterrupt:
    pass
  return 0


if __name__ == "__main__":
  raise SystemExit(main())
