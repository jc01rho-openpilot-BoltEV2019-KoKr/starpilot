# SELFDRIVE KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Core driver assistance stack managing sensor fusion, path planning, and vehicle actuation.

## WHERE TO LOOK

| Component | Location | Responsibility |
|-----------|----------|----------------|
| **Localization** | `locationd/` | Calibration (`calibrationd`), Kalman Filters (`live_kf.py`), and odometry. |
| **Monitoring** | `monitoring/` | Driver monitoring logic and distraction alerts (`dmonitoringd.py`). |
| **Navigation** | `navd/` | Route planning, map rendering, and instruction parsing. |
| **Messaging** | `pandad/` | Panda hardware communication daemon and CAN to capnp translation. |
| **Regression** | `test/process_replay/` | Regression testing by replaying logs through core processes. |
| **Assets** | `assets/` | Fonts, icons, sounds, and UI images used across the system. |
| **Daemons** | `*d.py` | Various background services: `navd`, `monitoringd`, `locationd`, etc. |

## CONVENTIONS

**Cross-Process Communication:**
- All communication must use `cereal` (Cap'n Proto) via `msgq` (ZeroMQ).
- Subscribe to `sm['socketName']` for synchronized multi-process state updates.

**Hardware Targets:**
- `larch64` (TICI): Primary production target with DSP/GPU acceleration (thneed).
- `x86_64`: Development/testing target (using ONNX fallback for models).

**UI/UX:**
- All UI strings must use `qsTr()` for internationalization.
- Translations are managed in `ui/translations/`.

**Performance:**
- `controlsd.py` is the highest priority process; keep its loop clean and non-blocking.
- Use `common.realtime.Priority` for scheduling sensitive tasks.

## ANTI-PATTERNS

| Pattern | Why Forbidden |
|---------|---------------|
| Blocking I/O in `controlsd` | Causes latency spikes that can lead to safety disengagements. |
| Raw CAN Access | Use `pandad` or `car` interfaces to maintain hardware abstraction. |
| Bypassing `cereal` | Breaks logging and replay capabilities; all state must be in messages. |
| Hardcoded Paths | Use `system.hardware.BASEDIR` or relative imports. |
| Direct `sys.exit()` | Use `CloudLog` and graceful shutdown for daemon stability. |

## COMMANDS

```bash
# Run process replay (regression test)
pytest selfdrive/test/process_replay/test_process_replay.py

# Run localization tests
pytest selfdrive/locationd/test/

# Check UI snapshots
python selfdrive/ui/tests/test_ui/run.py

# Test car interfaces (subset)
pytest selfdrive/car/tests/test_car_interfaces.py
```
