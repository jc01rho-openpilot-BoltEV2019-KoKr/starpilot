#!/bin/bash
# StarPilot Upstream Sync Script
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

# 1. paddle5 동기화
log "Step 1/4: paddle5 checkout & upstream fetch"
git checkout paddle5
git fetch upstream

log "Step 2/4: upstream/StarPilot merge into paddle5"
if git merge upstream/StarPilot --no-edit 2>/dev/null; then
  log "Merge 성공 (fast-forward 또는 auto-merge)"
else
  warn "Merge 충돌 발생, ours(paddle5)로 해결..."
  CONFLICTS=$(git diff --name-only --diff-filter=U)
  if [ -n "$CONFLICTS" ]; then
    git checkout --ours $CONFLICTS
    git add $CONFLICTS
    git commit --no-edit
    log "충돌 해결 완료"
  fi
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

# 3. Push
log "Step 4/4: Push both branches"
git push origin paddle5
git push origin paddle5_215-55-17

log "=== 완료 ==="
git log --oneline -5