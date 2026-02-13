# LOCATION KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Localization: GPS, IMU fusion, road matching, navigation integration.

## STRUCTURE

```
selfdrive/locationd/
├── __init__.py
├── test/
└── [localization scripts]
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| GPS fusion | `locationd/` | `gps_fusion.py` |
| IMU fusion | `locationd/` | `imu_fusion.py` |
| Road matching | `locationd/` | `road_match.py` |
| Navigation integration | `frogpilot/navigation/` | Mapbox + OSM |

## CONVENTIONS

**Coordinate transforms:**
- Use `common.transformations` for ECEF/NED/Device/Car
- Use `ubloxd` for GPS data

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Bypass coordinate transforms | Use library, don't manual math |
| Ignore GPS validity | Check `gps_valid` flag |
| Hardcode road positions | Use map matching, not hardcoded |

## COMMANDS

```bash
# Localization tests
pytest selfdrive/locationd/test/
```

## NOTES

**Navigation integration:**
- Mapbox API for turn-by-turn
- OSM tiles for road network
- FrogPilot provides navigation features

**Coordinate systems:**
- ECEF: GPS coordinates
- NED: Local tangent plane
- Device: Phone frame
- Car: Vehicle frame
