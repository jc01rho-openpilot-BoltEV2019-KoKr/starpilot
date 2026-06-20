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

- 충돌은 항상 `paddle5` (ours) 기준으로 자동 해결합니다.
- merge 후 자동으로 push까지 진행합니다.
- `upstream` remote가 `https://github.com/firestar-link/starpilot` 또는 동일 upstream을 가리키고 있어야 합니다.
