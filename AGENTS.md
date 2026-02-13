# OPENPILOT PROJECT KNOWLEDGE BASE

**Generated:** 2025-01-04
**Monorepo:** openpilot + FrogPilot fork (300+ car support)

## OVERVIEW

Robotics operating system for driver assistance. Core stack: Python 3.11, C++ (SCons), Qt5, Cython. FrogPilot is experimental fork with bleeding-edge features.

## STRUCTURE

```
./
├── selfdrive/    # Core logic (controls, vision, models, UI)
├── frogpilot/     # Experimental fork features (themes, personalities)
├── system/        # System services (athena, camerad, loggerd)
├── tools/         # Dev tools (cabana, replay, sim)
├── common/        # Shared utilities
├── panda/         # CAN interface hardware
├── opendbc/       # CAN database for 300+ cars
├── body/          # Body board firmware
├── cereal/        # Cap'n Proto messaging
├── msgq_repo/     # ZeroMQ messaging library
├── rednose_repo/  # Embedded helpers
├── teleoprtc_repo/# WebRTC teleoperation
├── tinygrad_repo/ # Tensor library (AGENTS.md exists)
└── third_party/   # External deps (acados, snpe, libyuv)
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Car support | `selfdrive/car/` | 32+ car subdirs, porting guides in `tools/car_porting/` |
| Control logic | `selfdrive/controls/` | LatControl, LongControl, ModelManager |
| ML models | `selfdrive/modeld/` | thneed runners, models |
| UI/Qt | `selfdrive/ui/` | PyQt5 + QML, translations in `selfdrive/ui/translations/` |
| Camera | `system/camerad/` | Multi-camera capture (tici-only) |
| Logs | `system/loggerd/` | rlog uploads, segmenting |
| OTA | `system/athena/` | Over-the-air updates |
| CAN bus | `panda/python/` + `opendbc/` | Panda firmware + CAN DB |
| FrogPilot features | `frogpilot/` | Themes, personalities, navigation |
| Replay logs | `tools/replay/` | Log playback, visualization |
| Cabana | `tools/cabana/` | CAN log analysis tool |

## CONVENTIONS

**Build:**
- `scons` main build (NOT Make)
- `--minimal` flag for production builds
- `--coverage`, `--asan`, `--ubsan` for testing
- Python via `poetry`, C/C++ via SCons

**Code style:**
- Python: Ruff (2-space, 160 char lines)
- C/C++: cpplint (240 char lines)
- Mypy type checking enabled
- Pre-commit hooks mandatory

**Testing:**
- `pytest` with `-Werror` (warnings as errors)
- `pytest` markers: `slow`, `tici`
- `pytest-xdist` for parallel tests
- `testpaths` defined in pyproject.toml

**Git:**
- FrogPilot-Development branch: NEVER install (broken)
- Use `frogpilot.download` for production

## ANTI-PATTERNS (THIS PROJECT)

| Pattern | Why Forbidden |
|---------|---------------|
| Install FrogPilot-Development branch | Actively broken, for dev only |
| Ignore panda SPI HACK constants | Workarounds for ack timeouts, fragile |
| Skip bootstub.c flashing recovery | Green LED rapid blink = failure, needs manual recovery |
| Direct `openpilot/*` imports (use `from openpilot.*`) | Enforced by ruff banned imports |
| `unittest` usage (use `pytest`) | Enforced by ruff |

## COMMANDS

```bash
# Build
scons                           # Full build
scons --minimal                  # Minimal production build
scons --asan                     # Address sanitizer
scons --coverage                 # Test coverage

# Test
pytest                          # All tests
pytest -m "not slow"            # Skip slow tests
pytest -m "tici"                # Device-specific tests

# Install
poetry install                  # Python deps
pre-commit install               # Git hooks

# Tools
python tools/cabana/cabana      # CAN log analyzer
python tools/replay/replay       # Log player
```

## NOTES

**Architecture:**
- Messaging: cereal (Cap'n Proto) over msgq (ZeroMQ)
- Hardware abstraction: panda (CAN), body (body board)
- Models: ONNX runtime (selfdrive) + tinygrad (frogpilot)
- Qt5 for UI, QML for reactive components

**Gotchas:**
- Submodules (panda, msgq, rednose, teleoprtc, tinygrad) excluded from most tooling
- `third_party/` excluded from linting, type checking
- `larch64` = TICI device (Qualcomm)
- `aarch64` = Linux ARM, `x86_64` = Linux x64, `Darwin` = macOS
- Camera capture only on `larch64`
- acados for MPC controls (third_party)

**FrogPilot specifics:**
- Themes: `frogpilot/assets/` (color schemes, icons, sounds)
- Navigation: OpenStreetMap + Mapbox data
- Personalities: Traffic, Aggressive, Standard, Relaxed
- Conditional Experimental Mode (CEM): switches based on road conditions
