# TOOLS KNOWLEDGE BASE

**Generated:** 2026-01-04

## OVERVIEW
Dev tools for log analysis, simulation, car porting, and hardware-in-the-loop testing.

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| CAN analysis | `tools/cabana/` | Visualize CAN traffic and define DBC signals. |
| Log playback | `tools/replay/` | Replay `rlog`/`qlog` files with service mocking. |
| Simulation | `tools/sim/` | MetaDrive bridge for testing controls without hardware. |
| Car porting | `tools/car_porting/` | Guides and tools for adding new car support. |
| Log parsing | `tools/lib/` | `logreader.py` is the primary API for reading logs. |
| Plotting | `tools/plotjuggler/` | Advanced plotting tool for cereal messages. |
| Control tuning | `tools/tuning/` | Scripts for steering and longitudinal calibration. |
| Benchmarking | `tools/profiling/` | CPU and memory profiling for the openpilot stack. |

## CONVENTIONS
- **Route Access**: Use the `Route` and `LogReader` abstractions from `tools.lib`.
- **Route Format**: Identifiers follow the `<dongle_id>|<timestamp>` format.
- **Environment**: Most tools require a built stack (`scons`) and Python dependencies (`poetry install`).
- **GUIs**: Cabana and Replay are Qt-based; Sim requires the MetaDrive simulator.

## ANTI-PATTERNS
- **Manual Parsing**: Never manually parse cereal/CAN data; use `LogReader` or `Cabana`.
- **Hardcoded Routes**: Avoid hardcoding local paths; use route strings for remote fetching.
- **Missing Build**: Do not attempt to run tools without first building the core stack.
- **Ignoring DBCs**: Do not hardcode CAN offsets; define them in `opendbc` via Cabana.

## COMMANDS
```bash
# Analyze a route in Cabana
python tools/cabana/cabana "dongle_id|timestamp"

# Replay a drive locally
python tools/replay/replay "dongle_id|timestamp"

# Run MetaDrive simulator
python tools/sim/sim.py
```
