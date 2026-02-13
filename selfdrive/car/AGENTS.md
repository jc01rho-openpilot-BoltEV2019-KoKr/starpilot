# CAR INTERFACES KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

300+ car implementations: state reading, control application, CAN message handling.

## STRUCTURE

```
selfdrive/car/
├── __init__.py         # Interface registry
├── values.py           # Base classes (CarInterface, CarController)
├── carcontroller.py    # Base control application
├── carstate.py         # Base state extraction
└── {make}/             # Car-specific implementations
    ├── __init__.py
    ├── carcontroller.py
    ├── carstate.py
    ├── radarinterface.py
    ├── tests/
    └── __pycache__/
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| New car port | `tools/car_porting/` | Full porting guide |
| Car registry | `__init__.py` | `get_car()` factory |
| Base interfaces | `values.py` | `CarInterface`, `CarController` |
| Fingerprint logic | `fingerprinter.py` | VIN/frame-based matching |
| Bus configs | `{make}/` subdirs | `can_define`, ` dbc` files |
| Car params | `{make}/__init__.py` | `CAR`, `FW_VERSIONS` |

## CONVENTIONS

**File structure:**
- `__init__.py`: Exports `get_car()`, `CAR`, `FW_VERSIONS`
- `carcontroller.py`: `CarController` subclass
- `carstate.py`: `CarState` subclass
- `radarinterface.py`: `RadarInterface` subclass (if car has radar)

**Required exports:**
```python
from .carcontroller import CarController
from .carstate import CarState
from .radarinterface import RadarInterface  # optional
CAR = make_model_dict
FW_VERSIONS = {ecu: {address: {fw_hash: count}}}
```

**Fingerprinting:**
```python
CP.carFingerprint = {0: {addr: [bytes]}}
# Frame 0 → address → list of candidate CAN data
```

**Control application:**
```python
def update(self, c, can, cs):
    # c: carControl, can: CAN messages, cs: carState
    self.frame += 1
    return []  # List of CAN messages
```

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Skip `get_car()` registry | Breaks car detection |
| Hardcoded VIN checks | Use fingerprinting, not static VIN |
| Override `__init__` without `super()` | Breaks base class setup |
| Direct `panda` imports | Use `selfdrive.car.can` abstraction |
| Ignore `test/test_car_models.py` | Required for car support |

## COMMANDS

```bash
# Test specific car
pytest selfdrive/test/test_car_models.py -k honda

# All car tests
pytest selfdrive/test/test_car_models.py

# Generate car docs
python tools/car_porting/generate_car_docs.py
```

## NOTES

**Supported car makes:**
Toyota, Honda, Hyundai, GM, Ford, VW, BMW, Mercedes, Nissan, Subaru, Tesla, Mazda, Kia, Chrysler, Audi, Porsche, Volvo, Land Rover, Jeep, Ram, Lexus, Infiniti, Acura, Cadillac, Chevrolet, Buick, GMC, Rivian, Lucid.

**Common pitfalls:**
- Wrong `CAN.bus` (usually 0 for PT, 1 for radar)
- Missing `fw_versions` → no car match
- Incorrect `steer_ratio` → overshoot/undershoot
- `gasMax` too high → unintended acceleration

**DBC files:**
- Located in `opendbc/generated/{make}/`
- Use `can_define` to map signals
- Check `tools/cabana` for CAN message discovery
