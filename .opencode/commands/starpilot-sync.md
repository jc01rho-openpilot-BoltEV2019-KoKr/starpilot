---
name: starpilot-sync
description: StarPilot 업스트림 동기화 - paddle5에 upstream/StarPilot 머지 후 paddle5_215-55-17 머지하고 두 브랜치 푸시
---

# StarPilot Sync Workflow

이 프로젝트 전용 워크플로우:
1. `paddle5` 체크아웃
2. `upstream`에서 fetch
3. `upstream/StarPilot`을 `paddle5`로 merge
4. `paddle5_215-55-17` 체크아웃
5. `paddle5`를 `paddle5_215-55-17`로 merge
6. 두 브랜치 모두 push

## 사용법

Claude/OpenCode에 `/starpilot-sync`라고 입력하면 됩니다. 또는 다음 명령을 직접 실행할 수 있습니다:

```bash
./.opencode/command/starpilot-sync.sh
```

## 충돌 해결 원칙

- **Step 1** (paddle5 ← upstream): 충돌 파일은 양쪽이 같은 영역을 수정한 파일(upstream만 수정 시 auto-merge로 이미 최신 반영). 로컬 튜닝 파일은 upstream superset 여부를 `git diff`로 확인 후 채택하거나 `git merge-file` 3-way로 공존, 보존 가치 없는 파일은 `--theirs`(upstream 최신). `--ours`는 로컬을 반드시 지켜야 하는 예외에만 — 맹목적 `--ours` 금지.
- **Step 2** (paddle5_215-55-17 ← paddle5): `--ours`로 해결.

## 커밋 전 검증 (필수)

충돌 해결 후 push 전 반드시 검증한다. `.venv/bin/python3` 우선, 부재 시 시스템 `python3`(capnp 설치 확인). 검증 생략 금지.
- **마커 잔여**: `grep -rn '^<<<<<<<\|^=======\|^>>>>>>>'` → 없어야 함.
- **py_compile**: 편집된 모든 `.py`를 `python3 -m py_compile` → 전부 통과.
- **capnp** (`cereal/log.capnp` 수정 시): `capnp.load('cereal/log.capnp')` 성공 + Event ordinal 중복/갭 없음 + `naviData` 런타임 init. naviData/nda 필드는 upstream 신규 필드(예: `driverMonitoringState @151`)와 번호 충돌 없게 다음 빈 번호로 이동.
- 검증 실패 시 커밋·push 금지.

## 사전 요구사항

- `upstream` 리모트가 `https://github.com/firestar-link/starpilot` (또는 동등한 StarPilot 포크)을 가리키고 있어야 합니다.
- 워크트리 상태가 깨끗해야 합니다.