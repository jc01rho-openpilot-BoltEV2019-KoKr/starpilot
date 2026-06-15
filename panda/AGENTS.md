# panda/ - CAN 버스 인터페이스 펌웨어

**Parent:** [../AGENTS.md](../AGENTS.md)

## OVERVIEW

STM32 MCU 기반 CAN/CAN-FD 인터페이스. openpilot과 차량 간 CAN 메시지 안전 중계. 2-stage 부팅(RSA 서명 검증), 하트비트 감시, 레지스터 무결성 검증.

## STRUCTURE

```
panda/
├── board/                 ← ★ STM32 펌웨어 C 코드
│   ├── main.c                 ← 메인 펌웨어 (8Hz tick 루프)
│   ├── bootstub.c             ← 부트로더 (RSA 서명 검증)
│   ├── config.h               ← 전역 설정
│   ├── can.h                  ← CAN 메시지 정의 (opendbc에서 포함)
│   ├── can_comms.h            ← CAN↔USB/SPI 패킷 조립/분해
│   ├── main_comms.h           ← USB/SPI 제어 패킷 라우터 (~30개 명령)
│   ├── faults.h               ← 결함 시스템 (27개 결함 플래그)
│   ├── health.h               ← health_t, can_health_t 구조체
│   ├── critical.h             ← 인터럽트 보호 영역
│   ├── boards/                ← 보드별 하드웨어 정의 (dos, red, tres, cuatro)
│   ├── stm32f4/               ← STM32F4 플랫폼 HAL
│   ├── stm32h7/               ← STM32H7 플랫폼 HAL (CAN-FD 지원)
│   ├── drivers/               ← 공통 드라이버 (CAN, USB, SPI, harness, registers)
│   ├── body/                  ← Body (로봇 모터 제어) 펌웨어
│   └── jungle/                ← Jungle (테스트/프로비저닝 보드) 펌웨어
├── python/                ← 사용자 공간 Python 라이브러리 (Panda 클래스)
├── crypto/                ← RSA 서명 검증 (부트로더용)
├── tests/                 ← 테스트 스위트
│   ├── hitl/                  ← 하드웨어-in-the-loop (9개 시나리오)
│   ├── misra/                 ← MISRA C:2012 규정 준수
│   ├── libpanda/              ← C 라이브러리 Python 바인딩 테스트
│   └── usbprotocol/           ← USB 프로토콜 단위 테스트
├── drivers/               ← 호스트 OS SPI 드라이버
├── SConstruct/SConscript  ← 빌드 시스템 (6개 타겟)
└── Jenkinsfile            ← CI/CD (Docker + HITL)
```

## WHERE TO LOOK

| 작업                   | 위치                       | 비고                                            |
| ---------------------- | -------------------------- | ----------------------------------------------- |
| CAN 메시지 처리 수정   | board/drivers/can_common.h | 큐, 링버퍼, TX/RX 루틴                         |
| 안전 모드 수정         | board/main.c               | set_safety_hooks() — opendbc에서 제공           |
| USB 명령 추가          | board/main_comms.h         | 제어 패킷 라우터 (~30개 명령)                   |
| 결함 플래그 추가       | board/faults_declarations.h | 27개 결함 플래그                               |
| 보드별 하드웨어 수정   | board/boards/              | dos.h, red.h, tres.h, cuatro.h                 |
| Python API 수정        | python/__init__.py         | Panda 클래스 (852줄)                            |
| 빌드 타겟 추가         | SConscript                 | 6개 타겟: panda, panda_h7, panda_remote 등     |
| 릴레이/하네스 수정     | board/drivers/harness.h    | 방향 감지, 릴레이 제어                          |
| 레지스터 무결성        | board/drivers/registers.h  | 주기적 레지스터 값 검증                         |

## BUILD TARGETS

| 타겟              | MCU       | 플래그                       | 용도                    |
| ----------------- | --------- | ---------------------------- | ----------------------- |
| `panda`             | STM32F4   | -                            | 원래 panda              |
| `panda_h7`          | STM32H7   | -                            | Red Panda               |
| `panda_remote`      | STM32F4   | `-DPANDA_GM_REMOTE_START_C9`   | GM 원격시동             |
| `panda_h7_remote`   | STM32H7   | `-DPANDA_GM_REMOTE_START_C9`   | GM 원격시동 (H7)        |
| `panda_jungle_h7`   | STM32H7   | `-DPANDA_JUNGLE`               | 테스트 보드             |
| `body_h7`           | STM32H7   | `-DPANDA_BODY`                 | 로봇 모터 제어          |

## CONVENTIONS

**안전 모델 분리**: panda 자체에 안전 로직 없음. `opendbc/safety/safety.h`에서 차종별 hooks 제공.

**하트비트 감시**: openpilot이 주기적으로 `0xf3` 전송 필요. 미수신 시 5초(시동ON)/2초(시동OFF) 후 SILENT 모드.

**Vtable 보드 추상화**: `struct board` 함수 포인터 테이블로 하드웨어별 동작 분리.

**조건부 컴파일**: `#ifdef STM32F4/STM32H7/PANDA_JUNGLE/PANDA_BODY`.

**링버퍼 큐**: 인터럽트 안전한 `can_ring` (ENTER_CRITICAL/EXIT_CRITICAL).

**2-stage 부팅**: bootstub(RSA 서명 검증) → main(안전 앱).

## ANTI-PATTERNS

- **SIL2 규칙**: 하드웨어 저전력 모드(STOP/STANDBY) 구현 금지. WFI만 허용.
- **safety 코드 수정 시**: `opendbc_repo/opendbc/safety/` 전체 안전 테스트 통과 필수.
- **레지스터 무결성**: `check_registers()`가 주기적으로 검증. 하드웨어 레지스터 임의 수정 시 FAULT_REGISTER_DIVERGENT 발생.


