#!/usr/bin/env bash
set -euo pipefail

HOST="${1:-comma@192.168.3.110}"

SSH_OPTS=(-o BatchMode=yes -o ConnectTimeout=5)

if [[ -n "${SSH_KEY:-}" ]]; then
  SSH_OPTS+=(-i "$SSH_KEY" -o IdentitiesOnly=yes)
fi

ssh "${SSH_OPTS[@]}" "$HOST" 'bash -s' <<'REMOTE_SCRIPT'
set -u

echo "===== Device ====="
printf "AGNOS: "
cat /VERSION
printf "Model: "
tr -d '\000' </sys/firmware/devicetree/base/model
printf '\nUptime: '
cut -d' ' -f1 /proc/uptime

echo
echo "===== Boot Summary ====="
systemd-analyze time

echo
echo "===== Slowest Units ====="
systemd-analyze blame | head -n 20

echo
echo "===== Critical Chain ====="
systemd-analyze critical-chain graphical.target

echo
echo "===== Display Startup ====="
systemctl show comma.service weston.service weston-ready.service magic.service \
  -p Id -p LoadState -p ActiveState -p ActiveEnterTimestampMonotonic \
  -p ExecMainStartTimestampMonotonic -p ExecMainExitTimestampMonotonic --no-pager

if systemctl cat magic.service >/dev/null 2>&1; then
  echo "Display path: magic.service"
else
  echo "Display path: weston fallback (magic.service is not installed)"
fi

for socket_path in /tmp/drmfd.sock /var/tmp/weston/wayland-0; do
  if [[ -S "$socket_path" ]]; then
    echo "$socket_path: ready"
  else
    echo "$socket_path: missing"
  fi
done

echo
echo "===== comma.sh Readiness Logic ====="
if grep -q STARPILOT_DISPLAY_READY_WAIT_V1 /usr/comma/comma.sh; then
  sed -n '/STARPILOT_DISPLAY_READY_WAIT_V1/,+50p' /usr/comma/comma.sh
else
  sed -n '/waiting for magic/,+20p' /usr/comma/comma.sh
  if ! systemctl cat magic.service >/dev/null 2>&1; then
    echo "WARNING: comma.sh waits 20 seconds for a service that is not installed"
  fi
fi
REMOTE_SCRIPT
