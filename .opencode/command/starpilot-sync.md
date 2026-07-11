# Upstream Sync Workflow

StarPilot upstream 동기화 + paddle 브랜치 머지 + push를 한 번에 실행합니다.

## Workflow

1. **paddle5 브랜치 동기화**
   - `paddle5` 체크아웃
   - `upstream` 최신 fetch
   - `upstream/StarPilot` merge (충돌 시 `--ours`로 해결)
   - merge commit 생성

2. **paddle5_215-55-17 브랜치 동기화**
   - `paddle5_215-55-17` 체크아웃
   - `paddle5` merge

3. **Push**
   - `paddle5` → `origin/paddle5`
   - `paddle5_215-55-17` → `origin/paddle5_215-55-17`

## 실행 방법

이 커맨드는 다음 쉘 스크립트를 실행합니다:

```bash
#!/bin/bash
set -e
cd "$(git rev-parse --show-toplevel)"

echo "=== Step 1: paddle5 sync with upstream/StarPilot ==="
git checkout paddle5
git fetch upstream
git merge upstream/StarPilot --no-edit
# 충돌 발생 시 ours로 해결
if git diff --name-only --diff-filter=U | grep -q .; then
  echo "충돌 발생, ours로 해결..."
  git checkout --ours $(git diff --name-only --diff-filter=U)
  git add -A
  git commit --no-edit
fi

echo "=== Step 2: paddle5_215-55-17 merge paddle5 ==="
git checkout paddle5_215-55-17
git merge paddle5 --no-edit
# 충돌 발생 시 ours로 해결
if git diff --name-only --diff-filter=U | grep -q .; then
  echo "충돌 발생, ours로 해결..."
  git checkout --ours $(git diff --name-only --diff-filter=U)
  git add -A
  git commit --no-edit
fi

echo "=== Step 3: Push both branches ==="
git push origin paddle5
git push origin paddle5_215-55-17

echo "=== 완료 ==="
git checkout paddle5_215-55-17
git log --oneline -5
```

## 주의사항

- **Step 1 충돌** (paddle5 ← upstream): 충돌 파일은 양쪽이 같은 영역을 수정한 파일입니다(upstream만 수정한 파일은 auto-merge로 이미 최신 반영). 로컬 튜닝 파일은 superset 확인/`git merge-file` 3-way로 공존, 보존 가치 없는 파일은 `--theirs`(upstream 최신). `--ours`는 로컬을 반드시 지켜야 하는 예외에만 — 맹목적 `--ours` 금지.
- **Step 2 충돌** (paddle5_215-55-17 ← paddle5): `--ours`로 해결합니다.
- **충돌 해결 후 커밋 전 반드시 검증**: `grep`으로 마커 잔여 확인, `py_compile`로 편집된 `.py` 문법 검증, `cereal/log.capnp` 수정 시 `capnp.load()` + ordinal 중복/갭 검증 + naviData 런타임 init 확인. 실패 시 push 금지.
- merge 후 자동으로 push까지 진행합니다.
- `upstream` remote가 `https://github.com/firestar-link/starpilot` 또는 동일 upstream을 가리키고 있어야 합니다.
