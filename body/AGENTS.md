# BODY BOARD KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Body board firmware: STM32F413, 3-phase BLDC control, CAN communication, secure boot.

## STRUCTURE

```
body/
├── board/              # STM32F413 board
│   ├── drivers/        # STM32 HAL drivers
│   │   ├── llbxcan.c   # CAN driver
│   │   └── angle_sensor.c  # Angle sensor driver
├── bldc/               # BLDC motor control
│   ├── foc.c           # Field-oriented control
│   ├── motor.c         # Motor state machine
│   └── driver.c       # Motor driver API
├── crypto/             # Secure boot crypto
├── inc/                # Headers
├── src/                # Source files
│   ├── main.c          # Main loops (1Hz, 10Hz, 100Hz, 16kHz)
│   └── comms.c         # CAN communication
├── site_scons/         # Build system
└── uds.h               # UDS (OBD-II) protocol
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Main loops | `src/main.c` | 1Hz, 10Hz, 100Hz, 16kHz loops |
| BLDC control | `bldc/foc.c` | FOC algorithm (16kHz) |
| Motor driver | `bldc/driver.c` | `driver_enable()`, `driver_set_current()` |
| CAN driver | `board/drivers/llbxcan.c` | CAN TX/RX |
| Angle sensor | `board/drivers/angle_sensor.c` | Hall effect sensor |
| Secure boot | `crypto/` | RSA, SHA256 |
| OTA flashing | `uds.h` | UDS protocol for flashing |

## CONVENTIONS

**Main loops:**
```c
// From src/main.c
void main(void) {
  // 1Hz loop: Status, diagnostics
  // 10Hz loop: Control, CAN comms
  // 100Hz loop: Fast control
  // 16kHz loop: FOC BLDC control
}
```

**BLDC control:**
- FOC (field-oriented control) algorithm
- 16kHz PWM for motor control
- 3-phase BLDC motor
- Current feedback from angle sensor

**Motor driver:**
```c
// From bldc/driver.c
void driver_enable(bool enable);
void driver_set_current(float current);  // Amps
void driver_set_direction(bool forward);
```

**CAN communication:**
```c
// From src/comms.c
void can_tx(uint32_t id, uint8_t *data, uint8_t len);
void can_rx(uint32_t id, uint8_t *data, uint8_t len);
```

**Secure boot:**
- RSA-2048 signature verification
- SHA-256 hash check
- Authored firmware only

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Skip 16kHz loop | Motor control fails |
| Bypass secure boot | Bricked board, unauthorized firmware |
| Hardcode PWM duty | Use FOC, not raw PWM |
| Ignore thermal limits | Motor burnout |
| Skip UDS checks | OTA flashing security |

## COMMANDS

```bash
# Build firmware
scons body

# Flash via UDS
python tools/flash_body.py

# Motor tests
pytest body/bldc/test/
```

## NOTES

**BLDC motor:**
- 3-phase BLDC (brushless DC)
- FOC algorithm for smooth control
- 16kHz PWM (high frequency)
- Hall effect angle sensor
- Max current: 10A

**Main loop rates:**
- 1Hz: Status LEDs, diagnostics
- 10Hz: Control loop, CAN communication
- 100Hz: Fast control
- 16kHz: FOC BLDC control (interrupt-driven)

**Secure boot:**
- Firmware signed with RSA-2048
- SHA-256 hash verification
- Signature check in `crypto/`
- Rejects unsigned firmware

**OTA flashing:**
- UDS (Unified Diagnostic Services) protocol
- Flashed via CAN (OBD-II port)
- Authenticated commands only
- Rollback on flash failure

**Gotchas:**
- 16kHz loop MUST NOT block (motor control)
- Secure boot rejects unsigned firmware
- UDS flashing requires authentication
- Thermal limits: Max 85°C
- Motor current limit: 10A
