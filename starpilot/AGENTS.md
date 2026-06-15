# starpilot/ - StarPilot 커스텀 코드

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

openpilot 위에 오버레이되는 StarPilot 전용 기능. 모델/테마 관리, 조건부 실험 모드(CEM), 속도 제한 컨트롤러(SLC), Galaxy/The Pond 원격 관리 등.

## STRUCTURE

```
starpilot/
├── starpilot_process.py   ← 메인 엔트리포인트 (Ratekeeper 루프, PubMaster: starpilotPlan)
├── common/                ← 공유 유틸리티 (StarPilotVariables, ThreadManager, backups)
├── controls/              ← 제어 로직
│   ├── starpilot_planner.py   ← ★ 메인 compose 지점. 6개 하위 모듈 통합
│   ├── starpilot_card.py      ← 차량 버튼 이벤트 (AOL, experimental mode)
│   └── lib/                   ← CEM, SLC, CSC, Following, Acceleration, Events, NNFF
├── system/                ← 시스템 서비스 (The Pond, Galaxy, tracking, stats, speed_limit)
├── assets/                ← 모델/테마 다운로드 관리 (ModelManager, ThemeManager)
├── navigation/            ← mapd_wrapper.py (오프라인 지도 네비게이션)
├── tools/                 ← compile_models.py
├── ui/                    ← StarPilot UI 확장
└── third_party/           ← 번들 Python 라이브러리 (flask, influxdb, urllib3 등)
```

## WHERE TO LOOK

| 작업                | 위치                                     | 비고                                              |
| ------------------- | ---------------------------------------- | ------------------------------------------------- |
| 새 토글/설정 추가   | common/starpilot_variables.py            | StarPilotVariables 클래스 + SimpleNamespace 토글   |
| 새 제어 모듈 추가   | controls/starpilot_planner.py            | __init__에서 compose, update()에서 호출           |
| 속도 제한 로직 수정 | controls/lib/speed_limit_controller.py   | Mapbox + 지도 + 비전 통합                         |
| 곡선 속도 제어      | controls/lib/curve_speed_controller.py   | 학습형 곡선 속도                                  |
| CEM 수정            | controls/lib/conditional_experimental_mode.py | 곡선/리드/신호 자동 experimental 전환        |
| The Pond API 추가   | system/the_pond/the_pond.py              | setup(app)에 Flask 라우트 추가. 6267줄 주의       |
| Galaxy 수정         | system/galaxy/galaxy.py                  | frpc 프록시 기반 원격 액세스                      |
| 모델 관리           | assets/model_manager.py                  | 다운로드/랜덤화/캐시                              |
| 테마 관리           | assets/theme_manager.py                  | 다운로드/홀리데이 테마                            |
| 주행 통계           | system/starpilot_tracking.py             | InfluxDB 전송                                     |

## CONVENTIONS

**Constructor injection**: 하위 모듈이 상위 참조를 주입받음 (`def __init__(self, StarPilotPlanner)`). 직접 import하지 않음.

**SimpleNamespace 토글**: `get_starpilot_toggles(sm)`으로 전역 설정 접근. ~200개 속성.

**cereal 확장**: `sm.extend(['starpilotPlan', ...])`로 기존 메시지 스트림 확장.

**`__init__.py` 없음**: `common/`, `controls/`, `system/`, `assets/` 하위에 `__init__.py` 부재. 직접 import 경로 사용.

**듀얼 소스 다운로드**: GitHub 우선, GitLab 폴백.

## ANTI-PATTERNS

- **third_party/** 수정 금지. 외부 라이브러리 번들.
- **the_pond.py**는 6267줄 모놀리식. 새 기능은 별도 모듈로 분리 권장.
- **순환 의존성 주의**: `controls/lib/starpilot_events.py` ↔ `system/starpilot_tracking.py` 상수 참조. `common/`으로 분리 권장.
