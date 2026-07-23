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
- **capnp 스키마 + ordinal + union + round-trip + consumer 검증** (`*.capnp` 변경 시 필수, `cereal/log.capnp` 등). `capnp.load` 성공은 "문법·로딩 가능"만 증명할 뿐, ordinal 중복/갭이나 의미적 누락을 **탐지하지 않는다**. 아래 heredoc을 실행한다:
  ```bash
  python3 - <<'PY'
  import capnp  # pycapnp
  capnp.remove_import_hook()
  log = capnp.load('cereal/log.capnp')          # 로드 성공 = 문법·참조 해결 OK (중복/갭 미탐지)

  ev = log.Event.schema

  # (1) 명시 ordinal: 고유 + 연속(0..max). 비-union 필드(logMonoTime@0, valid@67 등)는
  #     ordinal이 explicit여도 순수 스칼라 필드이므로 반드시 대상에 포함해 함께 검사한다.
  ords = sorted(f.proto.ordinal.explicit for f in ev.fields_list
                if f.proto.ordinal.which() == 'explicit')
  assert len(ords) == len(set(ords)), f'ordinal 중복: {[o for o in ords if ords.count(o)>1]}'
  assert ords == list(range(min(ords), max(ords)+1)), f'ordinal 갭/불연속: {ords}'

  # (2) union 멤버 식별: discriminant 값이 0xffff(65535)가 아니면 union arm.
  #     logMonoTime/valid는 비-union 일반 필드이므로 제외된다.
  members = [f for f in ev.fields_list if f.proto.discriminantValue != 0xffff]
  assert members, 'Event union 멤버 없음(스키마 파싱 이상)'

  # (3) 모든 union 멤버 init 가능 여부 — 로컬/업스트림 신규 arm 포함 전수 검증.
  #     list-backed arm은 0-길이 초기화에 실패할 수 있으므로 KjException 시 길이 1로 재시도.
  for f in members:
      try:
          log.Event.new_message().init(f.proto.name)
      except capnp.lib.capnp.KjException:
          m = log.Event.new_message()
          m.init(f.proto.name, 1)

  # (4) round-trip: 변경/신규 필드 + 로컬 보존 union arm(naviData 등) 직렬화→역직렬화.
  #     list-backed arm을 포함해 KjException 가능하니 동일 폴백. reader는 반드시
  #     context manager로 열고 닫고, which()로 활성 arm을 재확인한다.
  #     ⟦필드명 목록은 실제 diff에 맞춰 갱신⟧
  for name in ('naviData', 'driverMonitoringState'):
      root = log.Event.new_message()
      try:
          root.init(name)
      except capnp.lib.capnp.KjException:
          root = log.Event.new_message()
          root.init(name, 1)
      wire = root.to_bytes()
      with log.Event.from_bytes(wire) as reader:
          assert reader.which() == name, f'{name} round-trip 실패: {reader.which()}'

  print('capnp OK: load, ordinals unique+contiguous, union init, round-trip')
  PY
  ```
  - **ordinal 규칙**: union arm은 discriminant ordinal(0..N)을 중복 없이 연속으로 유지해야 한다. 로컬 커스텀 필드(예: `naviData @152`)는 업스트림 신규 필드(예: `driverMonitoringState @151`)와 번호가 겹치지 않도록 다음 빈 번호로 배치한다.
  - **중첩 struct/enum 변경은 별도 round-trip·consumer 검증이 필요**: `Event` top-level ordinal 검증만으로는 `DriverData.sleepProb`, `DriverMonitoringState.lockoutCount`/`lockoutMinutesRemaining` 같은 중첩 필드 추가·이름 변경을 **기계적으로 탐지할 수 없다**. 변경된 중첩 struct/enum(예: `DriverStateV2`, `DriverMonitoringState.MonitoringPolicy`)은:
    - **serialize/deserialize round-trip**: 값 채워서 `to_bytes()`→`from_bytes()`→필드 접근 정상 확인.
    - **consumer 일치**: 추가/이름변경한 enum 값(예: alert, `EventName` 등)이 모든 consumer에서 유일하게 존재하는지 확인. 변경된 스키마를 참조하는 Python consumer 파일(예: `selfdrive/monitoring/policy.py`, `selfdrive/ui/*/driver_state.py`, migration `selfdrive/test/process_replay/migration.py`)을 `py_compile` 또는 타겟 테스트로 검증.
- **검증 실패 시 커밋·push 금지.** 원인 수정 후 Step 1.5 전체 재실행.

### 2. paddle5_215-55-17 동기화
```
git checkout paddle5_215-55-17
git merge paddle5 --no-edit
```

충돌 발생 시: `--ours`(paddle5_215-55-17 유지)로 해결.

> **capnp 변경 병합 시 재게이트**: Step 2 머지 결과에 `*.capnp` 변경이 포함되어 있으면 **병합 완료 직후** Step 1.5를 다시 통과해야 한다. 로컬 `paddle5`에서 통과한 게이트가 `215-55-17` 측 변경과의 충돌 해결로 의미가 달라질 수 있다.

### 3. Push
```
git push origin paddle5
git push origin paddle5_215-55-17
```

## 원칙
- Step 1 충돌은 파일 유형별로 superset 확인/3-way 머지 또는 `--theirs`(upstream 최신), `--ours`는 예외에만. Step 2 충돌만 `--ours`(215-55-17 지역 커스터마이징 유지).
- **충돌 해결 후 커밋 전 반드시 py_compile + capnp load+ordinal+union init+round-trip+consumer 검증(Step 1.5)을 통과해야 한다. 실패 시 push 금지.**
- merge는 `--no-edit`으로 자동 커밋 메시지 사용.
- 완료 후 `paddle5` 브랜치에서 대기.
