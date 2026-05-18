# StarPilot AGENTS.md

## Repository Overview
StarPilot is a custom fork of comma.ai's openpilot with GM vehicle support and enhanced tuning.
Monorepo structure: `selfdrive/`, `system/`, `common/`, `tools/`, `starpilot/`, `tinygrad_repo/`, `opendbc_repo/`.

## Key Commands

### Development
- `scripts/starpilot_build_flow.sh verify` — Run build parity guards.
- `scripts/starpilot_build_flow.sh mac [jobs]` — macOS validation build (no device binaries).
- `scripts/starpilot_build_flow.sh device [jobs]` — Full on-device build (requires `/TICI`).
- `scripts/starpilot_build_flow.sh laptop-device [jobs]` — Device-target build in container.

- `.venv/bin/python3` — Use this Python for all repo scripts.
- `./c3` — Launch large UI on PC.
- `./c4` — Launch small UI on PC.
- `./build` — Cross-compile for comma devices.

### Lint / Typecheck / Test
- `scripts/lint/lint.sh` — Full lint suite (ruff, mypy, codespell, pre-commit hooks).
- `scripts/lint/lint.sh -f` — Fast lint (skip mypy/codespell).
- `scripts/lint/lint.sh ruff mypy` — Run specific checks.
- `ruff check . --quiet` — Direct ruff invocation.
- `pytest -q` — Run tests (uses `conftest.py` fixtures; ignores `openpilot/`, `opendbc/`, `tinygrad_repo/` etc.).

## Workflow Rules
- Always run `.venv/bin/python3` for repo scripts.
- `scripts/lint/lint.sh` executes `ruff check`.
- `starpilot/common/starpilot_backups.py`:
  - `create_backup()` stores final size via `put_int("MinimumBackupSize")`.
  - Deletes `_in_progress.tar.zst` on `OSError` during `tar.add()`.
  - `backup_tar_filter()` excludes `.git`, `.mypy_cache`, `.pytest_cache`, `__pycache__`, `*.a`, `*.o`, `*.pyc`, `*.pyo`, `*.so`.
- `starpilot/common/starpilot_functions.py` starts boot thread that calls `backup_starpilot()`.
- `starpilot/common/starpilot_backups.py:backup_starpilot()` uses `MinimumBackupSize=0` default; free space check is `max(estimated*3, 2_000_000_000)`.
- `starpilot/controls/lib/speed_limit_controller.py` owns Map/Dashboard/Vision SLC calculations.
- `starpilot/controls/lib/starpilot_vcruise.py` initializes `SpeedLimiter.instance()` and calls `get_max_speed()` for navi vCruise cap.
- `selfdrive/selfdrived/events.py:get_nda_camera_warning_context()` prefers `naviData.camLimitSpeed`/`sectionLimitSpeed`, falls back to `starpilotPlan.unconfirmedSlcSpeedLimit` + `mapdOut.nextSpeedLimitDistance`.
- `selfdrive/selfdrived/selfdrived.py:update_nda_camera_warning()` early-returns on `apply_limit_speed<=0`, `left_dist<=2.0 || >=1000.0`, `current_speed_kph<=5.0`.
- `selfdrive/selfdrived/events.py:get_nda_camera_warning_policy()` returns `userPrompt` if `limit_speed>0 && speed_ratio<0.7`, else `critical`.
- `selfdrive/road_speed_limiter.py` imports `numpy as np` directly (no `openpilot.common.numpy_fast`), imports `CV` from `openpilot.common.constants`.
- `opendbc_repo/opendbc/car/common/conversions.py` is the canonical conversions source.

## GM Bolt EV Architecture

### Vehicle Variants
| Model | ACC | Pedal Long | Regen Paddle | CC_ONLY |
|-------|-----|------------|-------------|---------|
| `CHEVROLET_BOLT_CC_2017` | ❌ | ✅ | ✅ | ✅ |
| `CHEVROLET_BOLT_CC_2018_2021` | ❌ | ✅ | ✅ | ✅ |
| `CHEVROLET_BOLT_CC_2022_2023` | ❌ | ✅ | ✅ | ✅ |
| `CHEVROLET_BOLT_ACC_2022_2023` | ✅ (Stock) | ❌ | ❌ | ❌ |
| `CHEVROLET_BOLT_ACC_2022_2023_PEDAL` | ✅ | ✅ | ✅ | ✅ |

All Bolt EVs are in `EV_CAR` → `transmissionType=direct` → EV tuning auto-enabled via `default_ev_tuning_enabled()` (starpilot_variables.py). EV and Truck tuning are mutually exclusive.

### Longitudinal Control Chain
```
[StarPilotAcceleration] → max/min accel (ev_tuning, SLC, weather, gear)
    → [LongControl.update()] → PID: error = a_target - aEgo, feedforward = a_target × gain
    → [CarController.update()] → accel_cmd → gas/brake CAN or pedal interceptor
```

### Key Files
- `starpilot/controls/lib/starpilot_acceleration.py` — accel profile selection (ECO/SPORT/SPORT+/STANDARD), EV accel curves, SLC coasting shaping.
- `selfdrive/controls/lib/longcontrol.py` — PID loop, state machine (off→stopping→starting→pid), integrator freeze/bleed for Pedal Long.
- `openpilot/common/pid.py` — Generic PIDController (speed-dependent kp/ki/kd, anti-windup).
- `opendbc_repo/opendbc/car/gm/carcontroller.py` — Bolt-specific: `calc_pedal_command()` (gas interceptor), regen paddle state machine, EV gas/brake threshold.
- `opendbc_repo/opendbc/car/gm/values.py` — `CarControllerParams`, `EV_GAS_BRAKE_THRESHOLD_*`, `CC_ONLY_CAR`, `CC_REGEN_PADDLE_CAR`.
- `opendbc_repo/opendbc/car/gm/interface.py` — Bolt-specific `accel_limits` (BOLT_PEDAL_LONG_CARS: speed-interpolated min/max).

### Bolt EV CarControllerParams (values.py:80-101)
- CC (non-kaofui): `MAX_GAS=8191`, `MAX_ACC_REGEN=5500`, `max_regen_acceleration=-1.0` (ICE is -0.1).
- Camera ACC: `MAX_GAS=8848`, `MAX_ACC_REGEN=5610`, `max_regen_acceleration=0.0` (no regen while enabled).
- `BRAKE_SWITCH_MAX=MAX_ACC_REGEN` for EV (ICE uses `ZERO_GAS`).

### EV Gas/Brake Threshold (values.py:146-154)
Speed-dependent dynamic threshold determines motor drive ↔ regen braking transition:
- Low speed (≤1.3 m/s): threshold ≈ 0.0 m/s²
- High speed (≥20 m/s): threshold ≈ -1.1 m/s² (regen covers most deceleration)
- Updated every cycle via `update_ev_gas_brake_threshold(v_ego)`.

### Pedal Long Bolt — calc_pedal_command() (carcontroller.py:224-354)
Converts accel (m/s²) → pedal_gas (0.0~1.0) for gas interceptor:
- `pedaloffset`: speed-dependent creep offset (0.085~0.235).
- `small_cmd_scale`: non-linear scaling for small commands (decel: 0.44→1.0, accel: 0.58→1.0).
- `accel_gain`: 0.47→0.61 (speed-dependent).
- Rate limiter prevents abrupt pedal changes: rate_up (0.007~0.036/frame), rate_down (0.008~0.045/frame).
- `pedal_gas_max`: speed-dependent upper bound (0.20 at standstill → 1.0 at 12+ m/s).

### Regen Paddle Control (carcontroller.py:240-289)
`CC_REGEN_PADDLE_CAR` Bolts only. State machine with hysteresis:
- Press threshold: accel ≤ -0.90~-0.65 m/s² (speed-dependent).
- Release threshold: accel ≥ -0.10~-0.30 m/s² (speed-dependent).
- Min hold frames: 16~34 on, 10~16 off (speed-dependent).
- Maneuver modes: `auto` (algorithm), `off` (always released), `force` (pressed when accel < -0.02).

### Bolt vs Volt Differences
- Volt: pitch correction, aero drag compensation, auto hold (`AUTO_HOLD_VOLT_CARS`), `_shape_volt_test_tune_integrator()`.
- Bolt: no pitch/aero correction, uses `_trim_positive_overshoot_integrator()` for I-term management.

## Constraints
- `.venv` Python has no `numpy`; `selfdrive/road_speed_limiter.py` and `selfdrive/ui/soundd.py` import numpy.
- `selfdrive/road_speed_limiter.py` never imports `openpilot.common.numpy_fast`.
- Do not edit auto-generated files under `cereal/gen/`, `tinygrad_repo/extra/assembly/`.

## Style & Conventions
- 2-space indentation (see `.editorconfig`).
- Ruff line-length 160; banned imports redirect `selfdrive` → `openpilot.selfdrive` etc.
- Always use `time.monotonic` instead of `time.time`.
- Prefer `pytest` over `unittest` and direct `pytest.main` calls.

## Merge Workflow (upstream)
1. Hard-reset `paddleuncompiled` to `origin/paddle5`.
2. Merge upstream `StarPilot` branch into `paddle5`.
3. Merge `paddle5` into `paddle5_215-55-17`.

## References
- Existing `AGENTS.md` (this file) and `tinygrad_repo/CLAUDE.md` contain additional domain guidance.
- Wiki: https://wiki.firestar.link
- Discord: https://firestar.link/discord
