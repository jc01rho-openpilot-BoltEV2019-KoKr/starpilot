# SYSTEM SERVICES KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Core system services for camera capture, logging, OTA updates, and process management.

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Process Management | `system/manager/` | Process lifecycle, health checks, `process_config.py` |
| Camera Capture | `system/camerad/` | TICI-only. ISP, AE/AWB, camera drivers (AR0231, OX03C10) |
| Logging & Encoding | `system/loggerd/` | `loggerd` (logs), `encoderd` (HEVC), `uploader` (rlogs) |
| OTA Updates | `system/athena/` | Device registration (`athenad`), OTA orchestration |
| Update Engine | `system/updated/` | `casync` based delta updates and system flashing |
| Sensors & GPS | `system/sensord/`, `system/ubloxd/` | IMU data, GNSS processing (Kaitai Struct generated) |
| Hardware Abstraction | `system/hardware/` | Thermal management, hardware-specific detection |

## CONVENTIONS

- **Process Definitions**: All system processes are defined in `system/manager/process_config.py`.
- **Hardware Abstraction**: Always use `system.hardware` for platform detection and thermal status.
- **Kaitai Struct**: GPS parsers in `system/ubloxd/` are generated from `.ksy` files. Do not edit `generated/` files directly.
- **Logging**: Routes are divided into 60s "segments". Each segment contains `rlog` (cereal) and video files (`fcamera.hevc`, etc.).

## ANTI-PATTERNS

| Pattern | Why Forbidden |
|---------|---------------|
| Hardcoding TICI paths | Use `system.hardware.TICI` or environment-aware paths |
| Blocking `SIGTERM` | Prevents clean shutdown by `manager`; results in forced kills |
| Editing `ubloxd/generated/` | Changes will be overwritten; edit `.ksy` files instead |
| Direct Camera I/O on PC | `camerad` hardware capture only works on TICI IPU6 |
| Bypassing `athenad` for OTA | Can break device registration and update consistency |
