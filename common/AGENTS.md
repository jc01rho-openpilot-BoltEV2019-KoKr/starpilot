# COMMON UTILITIES KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Shared utilities: logging, coordinate transforms, params, time system, dict helpers.

## STRUCTURE

```
common/
├── api/                # API clients (comma.ai, etc.)
├── mock/               # Mock implementations
├── tests/              # Common tests
├── transformations/    # Coordinate transforms
│   ├── coordinates.py  # ECEF, NED, Device, Car
│   └── orientation.py  # Quaternions, Euler angles
├── __init__.py         # Common exports
├── dict_helpers.py     # Dict manipulation
├── params.py           # Key-value storage
�   ├── time.py          # Time system, Ratekeeper
└── swaglog.py          # Cloudlog, IPC logging
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Coordinate transforms | `transformations/coordinates.py` | ECEF → NED → Car |
| Time management | `time.py` | `system_time_valid()`, `Ratekeeper` |
| Logging | `swaglog.py` | `cloudlog.error()`, IPC logging |
| Params | `params.py` | `Params.get()`, `Params.put()` |
| Dict helpers | `dict_helpers.py` | `get_only_key()`, `merge_dicts()` |
| Orientation | `transformations/orientation.py` | `rot_from_quat()`, `quat_from_rot()` |

## CONVENTIONS

**Coordinate systems:**
```python
# From transformations/coordinates.py
# ECEF (Earth-Centered Earth-Fixed) → NED (North-East-Down)
# NED → Device (phone frame)
# Device → Car (vehicle frame)

from common.transformations.coordinates import NED_to_Device
pos_device = NED_to_Device(pos_ned, orientation_ned)
```

**Time system:**
```python
# From time.py
from common.time import system_time_valid, Ratekeeper

if not system_time_valid():
  cloudlog.warning("System time invalid")

rk = Ratekeeper(100)  # 100 Hz
while True:
  rk.keep_time()
  # Do work at 100 Hz
```

**Logging:**
```python
# From swaglog.py
from common.swaglog import cloudlog

cloudlog.info("Message")
cloudlog.warning("Warning")
cloudlog.error("Error")
cloudlog.critical("Critical")
```

**Params:**
```python
# From params.py
from common.params import Params

params = Params()
enabled = params.get("OpenpilotEnabled") == b"1"
params.put("CustomKey", b"value")
```

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Bypass `system_time_valid()` | Invalid time → crashes |
| Use `print()` instead of `swaglog` | No cloud logging |
| Direct `os.environ` | Use `Params.get()`, not env vars |
| Manual coordinate math | Use transforms library, don't reinvent |
| Ignore `Ratekeeper` | Process must respect rate limits |

## COMMANDS

```bash
# Common tests
pytest common/test/

# Coordinate transform tests
pytest common/transformations/test/

# Time tests
pytest common/test/test_time.py
```

## NOTES

**Coordinate transforms:**
- **ECEF**: Earth-centered (GPS coordinates)
- **NED**: Local tangent plane (North, East, Down)
- **Device**: Phone/sensor frame
- **Car**: Vehicle frame (forward, right, down)

**Ratekeeper:**
- Enforces loop rate (e.g., 100 Hz, 20 Hz)
- Logs if loop is too slow
- Prevents CPU overload

**Time sync:**
- TICI: GPS + NTP
- PC: NTP only
- Mac: NTP only
- Invalid time = critical error

**Dict helpers:**
- `get_only_key(dict)`: Get single key from dict
- `merge_dicts(dict1, dict2)`: Merge nested dicts
- `split_on_key(dict, key)`: Split dict by key

**Gotchas:**
- Params stored in `/data/params/` on TICI
- Params persist across reboots
- Invalid system time → location errors
- Ratekeeper logs on missed deadlines
