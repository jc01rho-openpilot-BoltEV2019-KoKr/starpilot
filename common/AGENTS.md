# common/ - 공유 인프라

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

프로젝트 전반에서 사용되는 공유 라이브러리. Params KVS, 로깅, 실시간 제어, 좌표계 변환, 단위 상수.

## STRUCTURE

```
common/
├── [핵심 인프라] params, swaglog, api, basedir
├── [제어 이론] pid, filter_simple, simple_kalman, stat_live
├── [실시간] realtime (DT_CTRL, Ratekeeper), watchdog, timeout
├── [상수] constants (CV 클래스), util.h (C++ 단위)
├── [좌표계] transformations/ (orientation, coordinates, camera, model)
├── [파일/OS] util, utils, gpio, gps
├── [부트스트랩] spinner, text_window, markdown
├── [테스트] mock/, prefix, file_chunker
└── [C++] params.cc, swaglog.cc, util.cc, ratekeeper.cc, watchdog.cc, timing.h
```

## WHERE TO LOOK

| 작업                | 위치                         | 비고                                         |
| ------------------- | ---------------------------- | -------------------------------------------- |
| 새 Params 키 등록   | params_keys.h                | 400+ 키. stock_value/tuning_level 속성 추가  |
| Params Python API   | params.py                    | get/put/getBool/putInt                       |
| Params C++ API      | params.cc/h, params_pyx.pyx  | Cython 바인딩                               |
| 로깅 수정           | swaglog.py, logging_extra.py | cloudlog 전역 싱글톤                         |
| 단위 변환           | constants.py                 | CV 클래스 (MPH_TO_KPH, MS_TO_KPH 등)       |
| 루프 속도 수정      | realtime.py                  | DT_CTRL=0.01, DT_MDL=0.05                   |
| PID 제어기 수정     | pid.py                       | 속도 기반 게인 보간                         |
| 필터 수정           | filter_simple.py             | FirstOrderFilter, BounceFilter               |
| 칼만 필터 수정      | simple_kalman.py             | KF1D 확장 칼만 필터                         |
| 좌표계 변환         | transformations/             | 오일러↔쿼터니언, ECEF↔NED, 카메라 캘리브레이션 |
| GPIO 제어           | gpio.py                      | sysfs + gpiochip ioctl                      |

## TOP IMPORTS (285+ 파일에서 사용)

1. `from openpilot.common.params import Params` — 압도적 1위
2. `from openpilot.common.constants import CV` — 단위 변환
3. `from openpilot.common.realtime import DT_CTRL, DT_MDL, Ratekeeper, config_realtime_process`
4. `from openpilot.common.filter_simple import FirstOrderFilter`
5. `from openpilot.common.swaglog import cloudlog`
6. `from openpilot.common.pid import PIDController`

## CONVENTIONS

**Params 인스턴스**: `Params()` (영속적), `Params(return_defaults=True)` (기본값), `Params(memory=True)` (휘발성).

**Python/C++ 중복**: FirstOrderFilter, Ratekeeper, 단위 상수가 Python과 C++에 각각 구현됨.

**transformations**: Cython 가속 C++ 구현. `.so` 파일 필요.

**BASEDIR**: `from openpilot.common.basedir import BASEDIR` — 프로젝트 루트 경로 상수.
