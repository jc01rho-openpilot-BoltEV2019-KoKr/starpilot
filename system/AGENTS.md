# system/ - 시스템 서비스

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

40+개 관리 프로세스의 생명주기, 하드웨어 추상화, 카메라/센서 수집, 로깅, 클라우드 연결 담당.

## STRUCTURE

```
system/
├── manager/           ← 프로세스 오케스트레이터
│   ├── manager.py         ← ★ 메인 루프. 모든 프로세스 시작/중지/워치독
│   ├── process_config.py  ← managed_processes 딕셔너리 (40+ 프로세스 등록)
│   ├── process.py         ← PythonProcess, NativeProcess, DaemonProcess 추상화
│   └── build.py           ← 빌드 관리
├── hardware/          ← 하드웨어 추상화 계층 (HAL)
│   ├── base.py            ← HardwareBase 추상 클래스 (20+ 메소드)
│   ├── __init__.py        ← HARDWARE 싱글톤 (TICI → Tici/Pc 분기)
│   ├── tici/hardware.py   ← C3/C3X/C4 실제 구현 (600+줄)
│   ├── pc/hardware.py     ← PC 스텁 구현
│   └── hardwared.py       ← 하드웨어 상태 모니터링 데몬
├── camerad/           ← 카메라 데몬 (C++, VisionIPC 서버)
├── loggerd/           ← 로깅 데몬 (세그먼트, qlog/rlog, 비디오 인코딩)
├── athena/            ← 클라우드 WebSocket 연결 (JSON-RPC, 업로드)
├── sensord/           ← IMU/자력계 센서 (I2C, GPIO 인터럽트)
├── updated/           ← OTA 업데이트 (casync 기반)
├── ubloxd/            ← u-blox GPS 파싱
├── qcomgpsd/          ← Qualcomm GPS 모뎀
├── webrtc/            ← WebRTC 스트리밍 (aiohttp)
├── ui/                ← 시스템 UI (setup, updater, reset, spinner)
├── micd.py            ← 마이크 데몬 (SPL 측정)
├── statsd.py          ← 메트릭 수집 (InfluxDB 라인 형식)
├── sentry.py          ← 에러 리포팅 (Bugsink)
├── tombstoned.py      ← 크래시 덤프 모니터링
├── logmessaged.py     ← ZMQ 로그 수집
├── proclogd.py        ← /proc 상태 수집
├── timed.py           ← 시간 동기화
└── version.py         ← 빌드 메타데이터
```

## WHERE TO LOOK

| 작업                     | 위치                              | 비고                                           |
| ------------------------ | --------------------------------- | ---------------------------------------------- |
| 새 프로세스 등록         | manager/process_config.py         | `procs += [PythonProcess(...)]`                |
| 프로세스 타입 변경       | manager/process.py                | PythonProcess/NativeProcess/DaemonProcess      |
| 하드웨어 인터페이스 추가 | hardware/base.py                  | 추상 메소드 추가 → Tici/Pc 구현              |
| 카메라 드라이버 수정     | camerad/sensors/                  | AR0231, OX03C10, OS04C10                      |
| 로깅 형식 수정           | loggerd/loggerd.cc                | 세그먼트 로테이션, 인코딩                     |
| 클라우드 API 수정        | athena/athenad.py                 | WebSocket, JSON-RPC                           |
| 시스템 UI 수정           | ui/                               | tici_*/mici_* 분기 (Big/Small UI)             |
| 파라미터 마이그레이션    | manager/launch_param_migrations.py | 부팅 시 일회성 마이그레이션                   |

## CONVENTIONS

**프로세스 타입**: `PythonProcess` (importlib), `NativeProcess` (os.execvp), `DaemonProcess` (Popen, manager 재시작 시 유지).

**조건부 실행**: `always_run`, `only_onroad`, `only_offroad`, `driverview`, `logging` 등 predicate 함수.

**워치독**: `watchdog_max_dt` 설정 시 `/tmp/wd<name><pid>` 파일 모니터링. 타임아웃 시 덤프 + 재시작.

**StarPilot 확장**: `process_config.py`에서 `procs += [...]`로 StarPilot 전용 프로세스 추가.

**하드웨어 싱글톤**: `from openpilot.system.hardware import HARDWARE` (TICI 플래그로 분기).

**IPC 패턴**: cereal messaging(Pub/Sub), VisionIPC(공유 메모리), ZMQ(로그/통계).

## ANTI-PATTERNS

- **하드웨어 저전력 모드 금지**: SIL2 규칙. WFI만 허용, STOP/STANDBY 금지.
- **manager.py 수정 시 주의**: 전체 프로세스 생명주기에 영향.
