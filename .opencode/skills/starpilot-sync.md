---
name: starpilot-sync
description: StarPilot 업스트림 동기화 - paddle5에 upstream/stable 머지, paddle5_215-55-17에 paddle5 머지, 검증 후 PR로 두 브랜치 반영. "starpilot sync", "upstream sync", "동기화", "paddle5 머지" 등에 트리거.
---

# StarPilot Sync Skill (upstream/stable 기준)

2026-11-22부터 두 브랜치는 upstream/stable 위에 다시 올라가 있다. upstream/StarPilot은 0b2061df(Branch-Migration StarPilot -> stable)에서 동결됐고 더 이상 따라가지 않는다. 기존 브랜치 끝은 backup/paddle5-before-stable, backup/paddle5_215-55-17-before-stable 에 남아 있다.

## 레이아웃 요약 (stable)
- 파이썬 코드는 openpilot/ 패키지 아래(openpilot/cereal, openpilot/common, openpilot/selfdrive, openpilot/starpilot, openpilot/system). import는 openpilot.* 이다.
- opendbc_repo, panda, msgq_repo 등은 서브모듈이 아닌 일반 폴더다. upstream-sync.json 은 그 출처 기록이며 이 포크에서는 수정하지 않는다(검증기는 형식만 본다).
- 저장소 어디에도 AGENTS.md(대소문자 무관)나 .gitmodules 를 추적하면 기기 업데이터(openpilot/common/vendor_manifest.py validate_layout)가 업데이트를 거부한다. 절대 커밋하지 않는다.
- 이 포크는 prebuilt 마커를 추적하지 않는다. 기기는 부팅 때 build.py 로 직접 빌드한다. upstream 머지로 루트의 prebuilt 파일이 다시 생기면 지운다(git rm prebuilt).

## 워크플로우
작업은 메인 체크아웃이 아니라 전용 워크트리에서 한다.

### 1. paddle5 동기화
```
git fetch upstream stable && git fetch origin
git worktree add ../wt-sync -b sync/paddle5 origin/paddle5
cd ../wt-sync
git merge upstream/stable --no-edit
git ls-files prebuilt && git rm -q prebuilt   # 다시 생겼으면 제거
```
충돌은 양쪽이 같은 영역을 바꾼 파일에서만 난다. 포크 튜닝 파일은 먼저 upstream이 로컬 변경을 이미 포함했는지 git diff 로 확인하고, 포함했으면 upstream 채택, 아니면 git merge-file 3-way 로 공존시킨다. 보존 가치가 없는 로컬 잔재는 --theirs. 파일 전체 --ours 는 금지.

### 1.5 커밋 전 검증 (필수)
- 충돌 마커: `git diff --check` 와 `grep -rn '^<<<<<<<\|^>>>>>>>' --include='*.py' --include='*.capnp' openpilot opendbc_repo` 결과가 없어야 한다.
- py_compile: 바뀐 모든 .py 를 `python3 -m py_compile`.
- capnp (openpilot/cereal/*.capnp 또는 opendbc_repo/opendbc/car/car.capnp 변경 시): capnp.load, Event 유니온 서수 고유+연속, 모든 유니온 멤버 init, 포크 필드(naviData 등) round-trip. 포크 서수는 upstream 신규 필드와 겹치면 upstream 마지막 번호 다음으로 옮긴다. 현재 포크 배정: Event.naviData, EventName.ndaCameraWarn, AudibleAlert.speedDown (log.capnp 에서 확인). 추적되는 생성물(openpilot/cereal/gen)이 있으면 stable 규칙대로 재생성해 같이 커밋한다.
- params: openpilot/common/params_keys.h 에 포크 키가 남아 있는지, `python3 -m pytest openpilot/common/tests/test_params_registry_usage.py` 등 params 레지스트리 테스트 통과.
- 레이아웃: `python3 tools/vendor/check.py --revision HEAD` (커밋 후) 통과, `git ls-files | grep -i 'agents.md$\|\.gitmodules$'` 결과 없음.
- 포크 기능 테스트: NDA(navi_camera, road_speed_limiter), 저전압 Discord, Bolt 관련 테스트를 기준선과 비교. x86 호스트에서는 aarch64 산출물 때문에 일부 수집 실패가 정상이므로 머지 전 브랜치에서 같은 명령으로 기준선을 먼저 만든다.
- 실패하면 커밋·푸시 금지.

### 2. paddle5_215-55-17 동기화
```
git worktree add ../wt-sync-215 -b sync/215 origin/paddle5_215-55-17
cd ../wt-sync-215 && git merge sync/paddle5 --no-edit
```
215 전용 변경은 opendbc_repo/opendbc/car/interfaces.py 의 SPEED_CORRECTION = 1.04 (휠속도 +4%) 하나다. 충돌 시 그 hunk만 로컬을 유지한다. 머지 후 215 전용 델타(git diff sync/paddle5 HEAD)가 그 변경뿐인지 확인한다. capnp 가 바뀌었으면 1.5를 다시 통과한다.

### 3. 반영
sync 브랜치를 푸시하고 gh -R jc01rho-openpilot-BoltEV2019-KoKr/starpilot 로 PR(sync/paddle5 -> paddle5, sync/215 -> paddle5_215-55-17)을 만들어 머지한다. 머지 후 원격 브랜치가 upstream/stable 을 포함하는지(git merge-base --is-ancestor) 다시 읽고, 워크트리와 sync 브랜치를 지운다. force push 금지.
