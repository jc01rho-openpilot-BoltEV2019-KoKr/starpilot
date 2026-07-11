#!/bin/bash
# StarPilot Sync Script
# 이 프로젝트 전용: upstream/StarPilot → paddle5 → paddle5_215-55-17 → push

set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

# 색상
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

log() { echo -e "${GREEN}[SYNC]${NC} $*"; }
warn() { echo -e "${YELLOW}[WARN]${NC} $*"; }
err() { echo -e "${RED}[ERR]${NC} $*" >&2; }

PY="${ROOT}/.venv/bin/python3"
[ -x "$PY" ] || PY="python3"
verify() {
  log "검증: 충돌 마커 / py_compile / capnp"
  if grep -rn '^<<<<<<<\|^=======\|^>>>>>>>' --include='*.py' --include='*.capnp' \
       --exclude-dir=tinygrad_repo --exclude-dir=.git . >/dev/null 2>&1; then
    err "충돌 마커 잔여 발견. 해결 후 재실행."; return 1
  fi
  local changed
  changed=$(git diff-tree --no-commit-id --name-only -r HEAD | grep '\.py$' | grep -v '^tinygrad_repo/' || true)
  if [ -n "$changed" ]; then
    # shellcheck disable=SC2086
    "$PY" -m py_compile $changed || { err "py_compile 실패"; return 1; }
    log "py_compile 통과: $(echo "$changed" | wc -l)개"
  fi
  if git diff-tree --no-commit-id --name-only -r HEAD | grep -q '^cereal/log.capnp$'; then
    "$PY" - <<'PYEOF' || { err "capnp 검증 실패"; return 1; }
import capnp; capnp.remove_import_hook()
log = capnp.load('cereal/log.capnp')
ords = [f.proto.ordinal.explicit for f in log.Event.schema.fields_list if f.proto.ordinal.which()=='explicit']
assert len(ords)==len(set(ords)), 'ordinal 중복'
assert sorted(ords)==list(range(min(ords), max(ords)+1)), 'ordinal 갭'
log.Event.new_message().init('naviData')
print('capnp OK: ordinal 중복/갭 없음, naviData 런타임 OK')
PYEOF
  fi
  log "검증 통과"
}

# 1. paddle5 동기화
log "Step 1/4: paddle5 checkout & upstream fetch"
git checkout paddle5
git fetch upstream

log "Step 2/4: upstream/StarPilot merge into paddle5"
if git merge upstream/StarPilot --no-edit 2>/dev/null; then
  log "Merge 성공 (fast-forward 또는 auto-merge)"
else
  # Step 1 충돌은 맹목적 --ours 금지(upstream 개선 유실). 로컬 튜닝 파일은
  # superset diff 확인 또는 git merge-file 3-way로 수동 해결해야 함.
  err "paddle5 ← upstream/StarPilot merge 충돌 발생. 자동 --ours 해결 안 함."
  err "충돌 파일을 파일 유형별로 수동 해결 후 재실행하세요:"
  git diff --name-only --diff-filter=U >&2
  exit 1
fi

# 2. paddle5_215-55-17 동기화
log "Step 3/4: paddle5_215-55-17 checkout & merge paddle5"
git checkout paddle5_215-55-17
if git merge paddle5 --no-edit 2>/dev/null; then
  log "Merge 성공 (fast-forward 또는 auto-merge)"
else
  warn "Merge 충돌 발생, ours(paddle5_215-55-17)로 해결..."
  CONFLICTS=$(git diff --name-only --diff-filter=U)
  if [ -n "$CONFLICTS" ]; then
    git checkout --ours $CONFLICTS
    git add $CONFLICTS
    git commit --no-edit
    log "충돌 해결 완료"
  fi
fi

# 3. 검증 (push 전 필수 게이트)
verify || { err "검증 실패. push 중단."; exit 1; }

# 4. Push
log "Step 4/4: Push both branches"
git push origin paddle5
git push origin paddle5_215-55-17

log "=== 완료 ==="
git log --oneline -5