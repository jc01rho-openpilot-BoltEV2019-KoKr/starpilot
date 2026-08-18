#!/usr/bin/env bash
set -euo pipefail

HOST="${1:-comma@192.168.3.110}"
MANIFEST="${2:?usage: $0 [host] manifest.json boot.img.xz system.img.xz}"
BOOT_IMAGE="${3:?missing boot image}"
SYSTEM_IMAGE="${4:?missing system image}"
EXPECTED_VERSION="${EXPECTED_VERSION:-19.6.1}"

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/../.." && pwd)"

SSH_OPTS=(-o BatchMode=yes -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null)
if [[ -n "${SSH_KEY:-}" ]]; then
  SSH_OPTS=(-i "$SSH_KEY" "${SSH_OPTS[@]}")
fi

for path in "$MANIFEST" "$BOOT_IMAGE" "$SYSTEM_IMAGE"; do
  if [[ ! -f "$path" ]]; then
    echo "missing file: $path" >&2
    exit 1
  fi
done

SESSION="local_agnos_pair_flash"
REMOTE_DIR="/data/local_agnos_pair_flash"
REMOTE_MANIFEST="${REMOTE_DIR}/agnos-local.json"
REMOTE_RUNNER="${REMOTE_DIR}/run_flash.sh"
REMOTE_AGNOS="${REMOTE_DIR}/agnos.py"
PORT="8989"

LOCAL_DIR="$(mktemp -d "${TMPDIR:-/tmp}/agnos-pair.XXXXXX")"
trap 'rm -rf "$LOCAL_DIR"' EXIT
LOCAL_MANIFEST="${LOCAL_DIR}/agnos-local.json"
LOCAL_AGNOS="${LOCAL_DIR}/agnos.py"

python3 - "$MANIFEST" "$LOCAL_MANIFEST" "$PORT" "$BOOT_IMAGE" "$SYSTEM_IMAGE" <<'PY'
import json
import sys
from pathlib import Path

source, destination, port, boot_image, system_image = sys.argv[1:]
images = {"boot": Path(boot_image), "system": Path(system_image)}
manifest = json.loads(Path(source).read_text(encoding="utf-8"))

if len(manifest) != len(images) or {entry.get("name") for entry in manifest} != set(images):
  raise SystemExit("local test manifest must contain exactly boot and system entries")

for entry in manifest:
  name = entry["name"]
  if not entry.get("has_ab"):
    raise SystemExit(f"{name} must be an A/B partition")
  if entry.get("sparse"):
    raise SystemExit(f"{name} must use a raw, non-sparse payload for local flashing")
  entry["url"] = f"http://127.0.0.1:{port}/{images[name].name}"
  entry.pop("alt", None)
  entry.pop("casync_caibx", None)
  entry.pop("casync_store", None)

Path(destination).write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
PY

python3 - "$REPO_ROOT/system/hardware/tici/agnos.py" "$LOCAL_AGNOS" <<'PY'
import sys
from pathlib import Path

src, dst = map(Path, sys.argv[1:])
data = src.read_text(encoding="utf-8")
needle = "import openpilot.system.updated.casync.casync as casync"
if data.count(needle) != 1:
  raise SystemExit("could not isolate the casync dependency in agnos.py")
data = data.replace(
  needle,
  '''class _UnusedCasync:
  ChunkReader = object
  ChunkDict = object

  def __getattr__(self, name):
    raise RuntimeError("casync support is unavailable in local AGNOS flash runner")
casync = _UnusedCasync()''',
)
dst.write_text(data, encoding="utf-8")
PY

ssh "${SSH_OPTS[@]}" "$HOST" "mkdir -p '$REMOTE_DIR'"
scp "${SSH_OPTS[@]}" "$LOCAL_MANIFEST" "$HOST:$REMOTE_MANIFEST"
scp "${SSH_OPTS[@]}" "$LOCAL_AGNOS" "$HOST:$REMOTE_AGNOS"
scp "${SSH_OPTS[@]}" "$BOOT_IMAGE" "$SYSTEM_IMAGE" "$HOST:$REMOTE_DIR/"

ssh "${SSH_OPTS[@]}" "$HOST" "cat > '$REMOTE_RUNNER' && chmod +x '$REMOTE_RUNNER'" <<'REMOTE_RUNNER'
#!/usr/bin/env bash
set -euo pipefail

: "${REMOTE_DIR:?}"
: "${REMOTE_MANIFEST:?}"
: "${REMOTE_AGNOS:?}"
: "${PORT:?}"
: "${EXPECTED_VERSION:?}"

exec > >(tee -a "${REMOTE_DIR}/flash.log") 2>&1

echo "[STEP] Local AGNOS boot+system flash"
echo "[CHECK] Device: $(tr -d '\0' </sys/firmware/devicetree/base/model)"
echo "[CHECK] Installed AGNOS: $(cat /VERSION 2>/dev/null || echo unknown)"
echo "[CHECK] Target AGNOS: ${EXPECTED_VERSION}"
echo "[CHECK] Active slot before flash: $(abctl --boot_slot)"
df -h /data

if [[ -x /usr/local/venv/bin/python3 ]]; then
  PYTHON_BIN="/usr/local/venv/bin/python3"
else
  PYTHON_BIN="python3"
fi

pkill -f "http.server ${PORT}.*${REMOTE_DIR}" >/dev/null 2>&1 || true
"$PYTHON_BIN" -m http.server "$PORT" --bind 127.0.0.1 --directory "$REMOTE_DIR" >"${REMOTE_DIR}/http.log" 2>&1 &
http_pid="$!"
trap 'kill "$http_pid" >/dev/null 2>&1 || true' EXIT

http_ready=0
for _ in $(seq 1 20); do
  if "$PYTHON_BIN" - "$REMOTE_MANIFEST" <<'PY'
import json
import sys
import urllib.request
from pathlib import Path

for entry in json.loads(Path(sys.argv[1]).read_text(encoding="utf-8")):
  with urllib.request.urlopen(entry["url"], timeout=2) as response:
    response.read(1)
PY
  then
    http_ready=1
    break
  fi
  sleep 0.25
done

if [[ "$http_ready" != "1" ]]; then
  echo "[ERROR] Local image HTTP server did not become ready" >&2
  cat "${REMOTE_DIR}/http.log" >&2 || true
  exit 1
fi

echo "[FLASH] Writing boot and system to the inactive AGNOS slot"
PYTHONPATH="$(dirname "$REMOTE_AGNOS")" "$PYTHON_BIN" "$REMOTE_AGNOS" --swap "$REMOTE_MANIFEST"

echo "[DONE] Both partitions verified and the inactive slot was selected"
echo "[REBOOT] Rebooting now"
sudo reboot
REMOTE_RUNNER

ssh "${SSH_OPTS[@]}" "$HOST" "tmux kill-session -t '$SESSION' >/dev/null 2>&1 || true"
ssh "${SSH_OPTS[@]}" "$HOST" "rm -f '$REMOTE_DIR/flash.log' '$REMOTE_DIR/http.log'"
ssh "${SSH_OPTS[@]}" "$HOST" \
  "tmux new-session -d -s '$SESSION' \"REMOTE_DIR='$REMOTE_DIR' REMOTE_MANIFEST='$REMOTE_MANIFEST' REMOTE_AGNOS='$REMOTE_AGNOS' PORT='$PORT' EXPECTED_VERSION='$EXPECTED_VERSION' bash '$REMOTE_RUNNER'\""

echo "Started remote tmux session: $SESSION"
echo "Watch it with: ssh $HOST 'tmux attach -t $SESSION'"
