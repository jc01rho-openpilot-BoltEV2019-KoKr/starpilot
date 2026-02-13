# DEBUG TOOLS KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Diagnostic tools: CAN monitoring, process debugging, log analysis, system health.

## STRUCTURE

```
selfdrive/debug/
├── __init__.py
├── test/
└── [debug scripts]
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| CAN monitoring | `debug/` | `can_monitor.py` |
| Process debugging | `debug/` | `process_debug.py` |
| Log analysis | `debug/` | `log_analyzer.py` |
| System health | `debug/` | `health_check.py` |

## CONVENTIONS

**Debug scripts:**
- Use `swaglog` for logging
- Exit with `0` on success, `1` on error
- Provide usage help (`--help` flag)

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Direct `print()` | Use `swaglog`, not `print()` |
| Ignore errors | Must exit with non-zero on failure |
| Hardcode paths | Use `common.params` for config |

## COMMANDS

```bash
# Debug tests
pytest selfdrive/debug/test/
```

## NOTES

This is a directory for ad-hoc debugging tools and diagnostic scripts. See individual scripts for usage.
