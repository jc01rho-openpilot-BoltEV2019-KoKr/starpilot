# selfdrive/ - 자율주행 코어 스택

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

12개 독립 데몬으로 구성된 파이프라인 아키텍처. cereal messaging(pub/sub), tinygrad ML 추론, Kalman 필터 기반 센서 융합.

## STRUCTURE

```
selfdrive/
├── selfdrived/        ← 상태 머신 & 이벤트 (selfdrived.py, events.py 1590줄, state.py)
├── car/               ← 차량 인터페이스 (card.py, car_specific.py, cruise.py)
├── controls/          ← 제어 시스템 (controlsd.py, plannerd.py, radard.py)
│   └── lib/           ← longcontrol, latcontrol_*, longitudinal_planner, desire_helper, ldw
├── modeld/            ← ML 모델 실행 (modeld.py, dmonitoringmodeld.py, transforms/)
├── locationd/         ← 센서 융합 (locationd, calibrationd, paramsd, torqued, lagd)
├── pandad/            ← Panda 하드웨어 인터페이스 (pandad.py, pandad.cc)
├── ui/                ← UI (Qt Big UI + raylib Mici UI 분기)
│   ├── layouts/       ← Big UI 레이아웃 (Qt C++)
│   └── mici/layouts/  ← Small UI 레이아웃 (Python raylib)
├── monitoring/        ← 운전자 모니터링 (dmonitoringd.py)
├── road_speed_limiter.py ← 내비 기반 속도 제한 (NaviServer)
└── debug/             ← 디버깅 도구 (34개 파일)
```

## WHERE TO LOOK

| 작업                  | 위치                             | 비고                                       |
| --------------------- | -------------------------------- | ------------------------------------------ |
| 차량 인터페이스 수정  | car/card.py                      | CAN 수신/송신, carState 퍼블리시           |
| 종방향 제어 수정      | controls/lib/longcontrol.py      | PID + D-term (aEgo LPF 미분). PEDAL_LONG은 I-term bleed/freeze/brake bias 별도 로직 |
| 종방향 튜닝 변경      | opendbc_repo/opendbc/car/*/interface.py | kpBP/kiBP/kdBP lookup으로 속도별 게인. PEDAL_LONG 차량은 kdV > 0 필수 |
| 횡방향 제어 수정      | controls/lib/latcontrol_torque.py | GM 기본. latcontrol_angle.py도 확인       |
| 경로 계획 수정        | controls/lib/longitudinal_planner.py | MPC 기반 종방향 계획                   |
| 모델 추론 수정        | modeld/modeld.py                 | tinygrad 기반, 20Hz                       |
| 이벤트/알림 추가      | selfdrived/events.py             | 1590줄. 모든 onroad 이벤트 정의           |
| 상태 전이 수정        | selfdrived/state.py              | enabled/disabled/preEnabled/softDisabling |
| 위치 추정 수정        | locationd/locationd.py           | Kalman 필터 융합                           |
| UI 수정 (Big)         | ui/layouts/                      | Qt C++ 코어 + Python 레이아웃              |
| UI 수정 (Small/Mici)  | ui/mici/layouts/                 | Python raylib 기반                         |
| 크루즈 속도 관리      | car/cruise.py                    | VCruiseHelper                              |

## ARCHITECTURE

```
[Camera] → camerad → modeld → modelV2 → plannerd → longitudinalPlan → controlsd
[IMU]    → locationd → livePose ──────────────────────────────────────→ controlsd
[CAN]    → pandad → card → carState ──────────────────────────────────→ controlsd
[DM]     → dmonitoringmodeld → dmonitoringd → driverMonitoringState ─→ selfdrived
```

**데몬 우선순위**: selfdrived/card/controlsd = CTRL_HIGH(4, 100Hz), plannerd = CTRL_LOW(5, 20Hz), modeld = RT(7, 20Hz)

**StarPilot 확장 패턴**: 기존 데몬이 `sm.extend(['starpilotPlan', ...])`로 StarPilot 메시지 구독.

## CONVENTIONS

**Ratekeeper 패턴**: 모든 데몬 루프에 `Ratekeeper(Hz).monitor_time()` 호출.

**Params 블로킹 초기화**: 시작 시 `Params().get("CarParams", block=True)`.

**StateMachine**: 5개 상태 전이 (disabled → preEnabled → enabled ↔ softDisabling ↔ overriding).

**Kalman 필터**: locationd의 5개 하위 데몬이 각자 KF로 파라미터 추정.

**tinygrad 모델**: pickle 직렬화, C++ OpenCL 변환 + Python tinygrad 실행.
