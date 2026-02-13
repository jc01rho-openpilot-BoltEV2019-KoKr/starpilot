# PANDA DAEMON KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Panda daemon: CAN communication, firmware management, safety checks.

## STRUCTURE

```
selfdrive/pandad/
├── __init__.py
├── test/
└── [pandad scripts]
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Panda management | `pandad/` | `manage.py` |
| CAN RX/TX | `pandad/` | `can_handler.py` |
| Firmware updates | `pandad/` | `firmware_update.py` |

## CONVENTIONS

**Panda API:**
- Use `panda.python.Panda` for CAN communication
- Use `panda.python.PandaDFU` for flashing

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Direct CAN manipulation | Use panda API, not raw CAN |
| Ignore safety checks | Panda safety mode = no control |
| Skip firmware check | Version mismatch = failures |

## COMMANDS

```bash
# Pandad tests
pytest selfdrive/pandad/test/
```

## NOTES

**Panda daemon responsibilities:**
- Manage panda device connection
- Handle CAN RX/TX
- Monitor panda health
- Update firmware

**Panda safety:**
- Safety checks in panda firmware
- Violations → safety mode
- Control disabled in safety mode
