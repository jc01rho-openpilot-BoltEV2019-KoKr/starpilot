# tools/ - 개발 도구

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

개발 환경 설정, 로그 분석, 시뮬레이션, 차량 포팅, 프로파일링 등 15+ 하위 도구. `op.sh`가 통일 인터페이스.

## STRUCTURE

```
tools/
├── op.sh              ← ★ 메인 CLI wrapper (setup, build, check, replay 등 20+ 명령어)
├── setup.sh           ← 시스템 전체 설치
├── lib/               ← 공통 라이브러리 (logreader, route, framereader, auth, api)
├── plotjuggler/       ← PlotJuggler 로그 시각화 (XML 레이아웃)
├── jotpluggler/       ← 웹 기반 로그 시각화 (YAML 레이아웃)
├── cabana/            ← CAN 메시지 분석 (C++)
├── replay/            ← 드라이브 리플레이 (C++ 바이너리 + Python UI)
├── sim/               ← MetaDrive 시뮬레이터 브리지
├── car_porting/       ← 차량 포팅 도구 (auto_fingerprint, test_car_model)
├── joystick/          ← 조이스틱/키보드 제어
├── longitudinal_maneuvers/ ← 종방향 기동 테스트
├── lateral_maneuvers/ ← 횡방향 기동 테스트
├── clip/              ← 비디오 클립 생성 (ffmpeg)
├── camerastream/      ← 카메라 스트림 디코딩 (VisionIPC)
├── webcam/            ← 웹캠 카메라 드라이버
├── profiling/         ← ftrace, py-spy, perfetto, clpeak
├── scripts/           ← 유틸리티 (SSH, 이미지 추출, 오디오 추출)
├── StarPilot/         ← StarPilot 전용 (derive_feasible_params, generate_pond_layout)
├── tuning/            ← GM 차량 튜닝 도구
├── longitudinal/      ← 종방향 루트 점수 계산
├── agnos/             ← AGNOS 시스템 이미지 패치
├── laptop_device_build/ ← 크로스 컴파일 Docker 설정
└── truenas_github_runner/ ← GitHub Actions 셀프호스티드 러너 Docker
```

## WHERE TO LOOK

| 작업                | 위치                         | 비고                                         |
| ------------------- | ---------------------------- | -------------------------------------------- |
| 개발 환경 설정      | op.sh setup                  | 또는 setup.sh / ubuntu_setup.sh / mac_setup.sh |
| 로그 분석           | plotjuggler/juggle.py        | `./dev juggle <route>`                       |
| 웹 로그 분석        | jotpluggler/pluggle.py       | 웹 기반 시각화                               |
| CAN 분석            | cabana/                      | `./dev cabana <route>`                       |
| 리플레이            | replay/                      | `./dev replay <route>`                       |
| 시뮬레이션          | sim/run_bridge.py            | MetaDrive 시뮬레이터                         |
| 차량 포팅           | car_porting/                 | auto_fingerprint.py, test_car_model.py       |
| 비디오 클립         | clip/run.py                  | `tools/clip/run.py <route/start/end>`        |
| 프로파일링          | profiling/                   | ftrace, py-spy, perfetto                     |
| StarPilot 튜닝      | StarPilot/, tuning/          | GM 전용 도구                                 |
| 빌드 수정           | laptop_device_build/         | Docker arm64 크로스 컴파일                   |

## CONVENTIONS

**Split-build**: `./build` (디바이스 arm64) vs `./dev`/`./tool`/`./tools/host` (호스트 x86_64).

**호스트 캐시 격리**: `.host_runtime/<platform>/`에 호스트 아티팩트 저장.

**리플레이 기반 워크플로우**: 대부분의 분석 도구는 `replay`를 통해 로그 데이터 로드.

**op.sh 통일 인터페이스**: `op setup`, `op build`, `op juggle`, `op replay` 등.

**데스크톱 UI**: `./c3` (Big), `./c4` (Small), `./raybig` (Big raylib).

**루트 식별자**: `dongle_id|timestamp` (예: `a2a0ccea32023010|2023-07-27--13-01-19`).
