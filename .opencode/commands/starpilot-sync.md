---
name: starpilot-sync
description: StarPilot 업스트림 동기화 - paddle5에 upstream/stable 머지 후 paddle5_215-55-17 머지, 검증 후 PR로 반영
---

# StarPilot Sync Workflow

절차와 검증 게이트는 .opencode/skills/starpilot-sync.md 를 따른다. 요약:
1. 전용 워크트리에서 origin/paddle5 기준 sync 브랜치에 upstream/stable 머지 (다시 생긴 prebuilt 마커는 제거)
2. 커밋 전 검증: 충돌 마커, py_compile, capnp 서수/round-trip, params 레지스트리, 레이아웃(AGENTS.md, .gitmodules 금지)
3. paddle5_215-55-17 에 결과 머지 (215 전용 델타는 SPEED_CORRECTION = 1.04 뿐)
4. PR 로 두 브랜치에 머지하고 원격 재확인, 워크트리 정리. force push 금지.

upstream 리모트는 https://github.com/StarPilotHQ/StarPilot.git, 기준 브랜치는 stable 이다.
