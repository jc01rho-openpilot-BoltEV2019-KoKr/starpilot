---
name: upstream-sync
description: StarPilot 업스트림 동기화 워크플로우 - paddle5에 upstream/StarPilot 머지, paddle5_215-55-17에 paddle5 머지, 두 브랜치 푸시. "upstream sync", "동기화", "paddle5 머지" 등에 트리거.
---

# StarPilot Upstream Sync Skill

## 워크플로우 순서

### 1. paddle5 동기화
```
git checkout paddle5
git fetch upstream
git merge upstream/StarPilot --no-edit
```

충돌 발생 시: `git checkout --ours`로 paddle5 버전 유지, add + commit.

### 2. paddle5_215-55-17 동기화
```
git checkout paddle5_215-55-17
git merge paddle5 --no-edit
```

충돌 발생 시: 동일하게 `--ours`로 해결.

### 3. Push
```
git push origin paddle5
git push origin paddle5_215-55-17
```

## 원칙
- 충돌은 항상 로컬(paddle5 또는 paddle5_215-55-17) 버전을 우선(`--ours`)
- merge는 `--no-edit`으로 자동 커밋 메시지 사용
- 완료 후 `paddle5_215-55-17` 브랜치에서 대기
