# UI KNOWLEDGE BASE

**Generated:** 2025-01-04

## OVERVIEW

Qt5 + QML reactive UI: dashboard, settings, car controls, live telemetry display.

## STRUCTURE

```
selfdrive/ui/
├── plated/             # QML UI components
│   ├── QML/
│   │   ├── APLValue.qml      # Text display
│   │   ├── APCommon.qml      # Base component
│   │   ├── OnroadUI.qml      # Main onroad view
│   │   ├── SettingsUI.qml    # Settings
│   │   └── ...
│   └── assets/         # Icons, fonts, images
├── __init__.py         # UI exports
└── test/               # UI tests
```

## WHERE TO LOOK

| Task | Location | Notes |
|------|----------|-------|
| Main onroad view | `plated/QML/OnroadUI.qml` | Dashboard, speed, steering wheel |
| Settings | `plated/QML/SettingsUI.qml` | Toggle switches, sliders |
| Value display | `plated/QML/APLValue.qml` | Speed, distance, time values |
| Fonts | `plated/assets/fonts/` | Inter, Roboto |
| Icons | `plated/assets/icons/` | SVG icons |
| Translations | `../translations/` | Crowdin i18n |
| State bindings | `plated/QML/APCommon.qml` | `Params`, `carState` bindings |

## CONVENTIONS

**QML components:**
- Use `qsTr()` for all user-facing text
- Component naming: `AP{Purpose}.qml` (e.g., `APValue`, `APCommon`)
- Use `Item` as root, not `Rectangle` (for clipping)
- Prefer `Column`/`Row` layouts over absolute positioning

**State bindings:**
```qml
Text {
  text: params.get("ControlState")
  visible: carState.enabled
}
```

**Color schemes:**
- Use `frogpilot/assets/themes/` if theming
- Otherwise: `#fff` (white), `#000` (black), `#e30` (red)

**Fonts:**
- Standard: `Inter-Regular.ttf`, `Inter-Medium.ttf`, `Inter-Bold.ttf`
- Load in `main.py` → `QFontDatabase.addApplicationFont()`

## ANTI-PATTERNS (THIS MODULE)

| Pattern | Why Forbidden |
|---------|---------------|
| Hardcoded text | Breaks i18n, use `qsTr()` |
| Absolute positioning | Breaks responsive layout |
| Direct `console.log` | Use `Log` component |
| Ignoring `frogpilot` themes | Use theme API, don't override |
| Missing translations | Crowdin integration required |

## COMMANDS

```bash
# UI tests
pytest selfdrive/ui/test/

# Update translations
python selfdrive/ui/translations/update_translations.py

# Build fonts
python tools/font_builder.py
```

## NOTES

**UI framework:**
- Qt5 + QML 2.15
- PyQt5 for Python-QML bridge
- PyOtherSide for JS execution (deprecated, using native bindings)

**Key state sources:**
- `Params`: `control`, `enabledState`, `roadName`
- `carState`: `speed`, `steerAngle`, `gearShifter`
- `controlsState`: `latActive`, `longActive`

**FrogPilot UI extensions:**
- Themes in `frogpilot/assets/themes/`
- Custom widgets in `frogpilot/ui/`
- Personality selector in `frogpilot/controls/`
