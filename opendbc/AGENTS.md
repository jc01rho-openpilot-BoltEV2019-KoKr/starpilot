# CAN DATABASE KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

CAN database for 300+ cars: DBC files, CAN packer/parser, code generation.

## STRUCTURE

```
opendbc/
├── can/                # CAN packer/parser (Python)
│   ├── __init__.py
│   ├── packer.py       # CAN message packing
│   ├── parser.py       # CAN message parsing
│   └── can_define.py   # DBC definitions
├── generator/          # DBC code generation
│   ├── __init__.py
│   ├── base.py         # Base DBC files
│   └── generator.py    # Code generator
├── generated/          # Generated DBC files (per make)
│   ├── toyota_dbc/
│   ├── honda_dbc/
│   └── ...
├── tests/              # CAN tests
└── __init__.py
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| CAN packing | `can/packer.py` | `can_pack()`, `make_can_msg()` |
| CAN parsing | `can/parser.py` | `CANParser`, `can_list_to_can_capnp()` |
| DBC definitions | `can/can_define.py` | `DBC` class, signal definitions |
| Generate DBCs | `generator/generator.py` | `generate_code()` |
| Toyota DBC | `generated/toyota_dbc/` | Toyota CAN messages |
| Honda DBC | `generated/honda_dbc/` | Honda CAN messages |

## CONVENTIONS

**DBC comments:**
```c
// SG_ Name : Start|Length@ByteOrder (+/-) (Scale,Offset) [Min|Max] "Unit" ECU
// SG_ Speed : 24|8@1+ (0.01,0) [0|255] "km/h" ECU1
```
- `+` = little-endian, `-` = big-endian
- Unit: SI preferred (m/s, rad, not km/h, degrees)
- Smallest bit size possible

**CAN packing:**
```python
# From can/packer.py
from opendbc.can.packer import CANPacker

packer = CANPacker("toyota_dbc/Toyota_Camry_2017_PT.dbc")
msg = packer.make_can_msg("STEERING_CONTROL", 0, {
  "STEER_TORQUE_CMD": 100,
  "STEER_REQUEST": 1
})
```

**CAN parsing:**
```python
# From can/parser.py
from opendbc.can.parser import CANParser

parser = CANParser("toyota_dbc/Toyota_Camry_2017_PT.dbc", [
  ("STEERING_STATUS", 0),
  ("ENGINE_DATA", 0)
])
can_msg = [0x123, 0, b'\x00\x01\x02\x03\x04\x05\x06\x07', 0]
ret = parser.update([can_msg])
speed = ret["STEERING_STATUS"]["SPEED"]
```

**Code generation:**
```bash
python opendbc/generator/generator.py
```
- Reads `base/*.dbc` files
- Generates `can/packer.py` and `can/parser.py`
- Runs on DBC changes

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Manual CAN packing | Use `CANPacker`, not `struct.pack()` |
| Ignore DBC comments | DBC docs break without SG_ comments |
| Hardcode signal offsets | Use generated code, not magic numbers |
| Skip code generation | `packer.py`/`parser.py` auto-generated |

## COMMANDS

```bash
# Generate code from DBC
python opendbc/generator/generator.py

# CAN tests
pytest opendbc/can/test/

# Validate DBCs
python opendbc/generator/validate_dbcs.py
```

## NOTES

**Supported makes (300+ cars):**
Toyota, Honda, Hyundai, GM, Ford, VW, BMW, Mercedes, Nissan, Subaru, Tesla, Mazda, Kia, Chrysler, Audi, Porsche, Volvo, Land Rover, Jeep, Ram, Lexus, Infiniti, Acura, Cadillac, Chevrolet, Buick, GMC, Rivian, Lucid.

**DBC files:**
- Located in `opendbc/generated/{make}_dbc/`
- Naming: `{Make}_{Model}_{Year}_{Type}.dbc`
- Types: `PT` (powertrain), `ADAS` (ADAS), `CAM` (camera)

**CAN message structure:**
- CAN ID: `address` (e.g., 0x123)
- Data: `data` (8 bytes)
- Bus: `src` (0=PT, 1=radar, 2=camera)
- Timestamp: `logMonoTime`

**Signal extraction:**
- `packer.py` generates `DBC` class
- Each signal has `start_bit`, `length`, `scale`, `offset`
- Parser extracts signals automatically

**Gotchas:**
- DBC code generation required on DBC changes
- Signal names must match DBC exactly
- Byte order (+/-) critical for parsing
- Scale/offset must match DBC units
