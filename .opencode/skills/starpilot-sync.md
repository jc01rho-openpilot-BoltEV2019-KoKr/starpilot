---
name: starpilot-sync
description: StarPilot 업스트림 동기화 워크플로우 - paddle5에 upstream/StarPilot 머지, paddle5_215-55-17에 paddle5 머지, 두 브랜치 푸시. "starpilot sync", "upstream sync", "동기화", "paddle5 머지" 등에 트리거.
---

# StarPilot Sync Skill

## 워크플로우 순서

### 1. paddle5 동기화
```
git checkout paddle5
git fetch upstream
git merge upstream/StarPilot --no-edit
```

충돌 파일은 **양쪽(paddle5, upstream)이 같은 영역을 수정한 파일**이다 (upstream만 수정한 파일은 auto-merge되어 이미 최신 반영, 충돌 목록에 안 온다). 파일 유형으로 구분:
- **로컬 튜닝 파일** (longcontrol.py, opendbc_repo/opendbc/car/gm/carcontroller.py 등 로컬과 upstream이 같은 함수를 수정): 먼저 `git diff`로 upstream이 로컬 변경을 이미 포함(superset)했는지 확인. 포함 시 upstream 버전 채택, 아니면 `git merge-file` 3-way로 upstream 개선과 로컬 튜닝을 공존.
- **로컬 변경이 보존 가치 없는 파일** (노이즈/구버전 잔재): upstream 최신을 원하므로 `git checkout --theirs`.
- `--ours`는 로컬 버전을 반드시 지켜야 하는 예외에만. 맹목적 `--ours`는 upstream 개선을 버리므로 금지.

### 1.5 충돌 해결 후 검증 (커밋 전 필수)

충돌 마커를 모두 제거하고 stage하기 전에 반드시 검증한다. `.venv` 부재 시 시스템 `python3`(capnp 설치 확인)로 대체 가능하나, 검증 생략은 금지.

- **마커 잔여 확인**: `grep -rn '^<<<<<<<\|^=======\|^>>>>>>>' --include='*.py' --include='*.capnp' .` → 결과 없어야 함.
- **py_compile**: 편집·해결한 모든 `.py` 파일을 `python3 -m py_compile <files...>` → 전부 통과해야 함(마커 잔여·union 들여쓰기 오류 탐지).
- **capnp 스키마 로드 + ordinal 무결성** (`cereal/log.capnp` 수정 시 필수):
  ```
  python3 -c "
  import capnp; capnp.remove_import_hook()
  log = capnp.load('cereal/log.capnp')            # 컴파일 성공 = 중복/갭/순서 통과
  for st in (log.Event.schema,):
    ords = [f.proto.ordinal.explicit for f in st.fields_list if f.proto.ordinal.which()=='explicit']
    assert len(ords)==len(set(ords)), 'ordinal 중복'
    assert sorted(ords)==list(range(min(ords),max(ords)+1)), 'ordinal 갭'
  log.Event.new_message().init('naviData')        # 로컬 nda 필드 런타임 검증
  print('capnp OK')
  "
  ```
  - **naviData/nda 필드는 upstream 신규 필드(예: driverMonitoringState @151)와 필드번호가 겹치지 않도록 다음 빈 번호로 이동**해야 한다. ordinal은 `0..max` 연속·중복 없음이 강제된다(capnp 규칙). 겹치면 `capnp.load` 실패.
- **검증 실패 시 커밋·push 금지.** 원인 수정 후 재검증.

### 2. paddle5_215-55-17 동기화
```
git checkout paddle5_215-55-17
git merge paddle5 --no-edit
```

충돌 발생 시: `--ours`(paddle5_215-55-17 유지)로 해결.

### 3. Push
```
git push origin paddle5
git push origin paddle5_215-55-17
```

## 원칙
- Step 1 충돌은 파일 유형별로 superset 확인/3-way 머지 또는 `--theirs`(upstream 최신), `--ours`는 예외에만. Step 2 충돌만 `--ours`(215-55-17 지역 커스터마이징 유지).
- **충돌 해결 후 커밋 전 반드시 py_compile + capnp 로드/ordinal 검증(Step 1.5)을 통과해야 한다. 실패 시 push 금지.**
- merge는 `--no-edit`으로 자동 커밋 메시지 사용.
- 완료 후 `paddle5_215-55-17` 브랜치에서 대기.
