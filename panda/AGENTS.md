# PANDA KNOWLEDGE BASE

**Monorepo Submodule:** CAN interface hardware and firmware logic.

## OVERVIEW
Universal car interface supporting CAN/CAN-FD, featuring STM32 firmware and Python API for safety-enforced vehicle communication.

## WHERE TO LOOK
| Component | Location | Details |
|-----------|----------|---------|
| Firmware | `board/` | STM32 code (`main.c`), CAN logic, and peripheral drivers |
| Safety Hooks | `board/safety/` | Car-specific safety logic and MISRA-C compliant hooks |
| Python API | `python/` | `Panda` class (in `__init__.py`) and hardware-specific modules |
| Hardware Config | `board/boards/` | Board-specific pinouts and configurations (F413/H725) |
| Recovery | `board/bootstub.c` | Minimal bootloader for flashing and emergency recovery |

## CONVENTIONS
- **Safety Silence:** Devices start in `SAFETY_SILENT`; active safety mode must be set to allow TX.
- **MISRA Compliance:** All code in `board/` must adhere to MISRA-C:2012 standards.
- **Hardware Abstraction:** Use `board/drivers/` for peripheral access; avoid direct register writes.
- **SPI Protocol:** Comma 3/3X (TICI) uses a custom SPI protocol with `SPI HACK (0x79)`.

## ANTI-PATTERNS
- **Safety Bypass:** Avoid `SAFETY_ALLOUTPUT` in code; it's for bench testing only.
- **Bricking Risk:** If green LED blinks fast, firmware is invalid; run `board/flash.py` immediately.
- **Manual DFU:** Don't rely on shorting J10 unless software-triggered DFU (`PandaDFU`) fails.
- **Redundant Imports:** Use `from panda import Panda` instead of importing from `python/` directly.

## KEY COMMANDS
```bash
# Flash standard application firmware
python panda/board/flash.py

# Perform full recovery (flashes bootstub + app)
python panda/board/recover.py

# Run all panda-related tests
pytest panda/tests/
```
