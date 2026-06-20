---
name: upstream-sync
description: StarPilot 업스트림 동기화 - paddle5에 upstream/StarPilot 머지 후 paddle5_215-55-17 머지하고 두 브랜치 푸시
---

# Upstream Sync Workflow

이 프로젝트 전용 워크플로우:
1. `paddle5` 체크아웃
2. `upstream`에서 fetch
3. `upstream/StarPilot`을 `paddle5`로 merge
4. `paddle5_215-55-17` 체크아웃
5. `paddle5`를 `paddle5_215-55-17`로 merge
6. 두 브랜치 모두 push

## 사용법

Claude/OpenCode에 `/upstream-sync`라고 입력하면 됩니다. 또는 다음 명령을 직접 실행할 수 있습니다:

```bash
./.opencode/command/upstream-sync.sh
```

## 사전 요구사항

- `upstream` 리모트가 `https://github.com/firestar-link/starpilot` (또는 동등한 StarPilot 포크)을 가리키고 있어야 합니다.
- 워크트리 상태가 깔끔해야 합니다.