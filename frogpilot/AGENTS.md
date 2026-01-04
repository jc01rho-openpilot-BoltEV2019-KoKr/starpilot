# FROGPILOT KNOWLEDGE BASE

**Generated:** 2026-01-04

## OVERVIEW
Bleeding-edge experimental fork featuring deep UI customization, adaptive driving personalities, and integrated OSM/Mapbox navigation.

## WHERE TO LOOK

| Component | Location | Implementation Details |
|-----------|----------|------------------------|
| **Themes** | `assets/`, `common/frogpilot_variables.py` | Icon/sound packs, custom color schemes, and seasonal assets. |
| **Personalities** | `controls/lib/frogpilot_following.py` | Jerk-based driving profiles: Traffic, Aggressive, Standard, Relaxed. |
| **Navigation** | `navigation/mapd.py` | OpenStreetMap and Mapbox integration for turn-by-turn and road names. |
| **CEM** | `controls/lib/conditional_experimental_mode.py` | Auto-switches Experimental Mode based on speed, leads, curves, and nav. |
| **SLC** | `controls/lib/speed_limit_controller.py` | Priority-based adaptation to posted limits (Nav, Map Data, Dashboard). |
| **Models** | `tinygrad_modeld/`, `assets/nnff_models/` | Tinygrad inference and Neural Network FeedForward (NNFF) models. |
| **Parameters** | `common/frogpilot_variables.py` | Centralized handling for 300+ custom toggles and tuning levels. |
| **UI** | `ui/qt/` | Custom QWidget/QML components for offroad settings and onroad display. |

## CONVENTIONS

**Parameter Management:**
- All custom settings must be centralized in `frogpilot_variables.py`.
- Params are prefixed with `FrogPilot` or `frogpilot_` for consistency.
- Use `params_memory` (in-memory) for high-frequency updates like CEM/SLC status.

**Core Modifications:**
- NEVER modify `selfdrive/` core directly. Use monkey-patching or overrides within `frogpilot/`.
- Maintain compatibility with `cereal` messaging while adding custom FrogPilot fields.

**Asset Organization:**
- Themes: `assets/themes/{theme_name}/`
- Icons: `assets/icons/`
- Sounds: `assets/sounds/`
- Seasonal: Managed via `HolidayThemes` toggle in `frogpilot_variables.py`.

## ANTI-PATTERNS

| Pattern | Why Forbidden |
|---------|---------------|
| `FrogPilot-Development` | Strictly for active dev; always broken. Use `frogpilot.download`. |
| Direct `Params` usage | Bypasses caching and tuning levels; use `frogpilot_variables.py` wrappers. |
| Patching `selfdrive/` | Breaks upstream mergeability and portability. |
| Hardcoded UI Colors | Breaks the Theme system; always reference `theme_colors.json`. |
| Synchronous API calls | Blocks control loops; use `ThreadPoolExecutor` (see `speed_limit_controller.py`). |

## NOTES
- **CEM (Conditional Experimental Mode)**: Uses `FirstOrderFilter` with speed-based time constants for smooth transitions.
- **SLC (Speed Limit Controller)**: Supports Mapbox filler when local OSM data is unavailable.
- **Personalities**: Adjusts `t_follow` and `jerk_factor` dynamically based on lead distance and velocity.
