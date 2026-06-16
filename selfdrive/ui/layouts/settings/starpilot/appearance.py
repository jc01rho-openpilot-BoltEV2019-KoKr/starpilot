from __future__ import annotations
import re

from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.widgets import DialogResult
from openpilot.system.ui.widgets.option_dialog import MultiOptionDialog

from openpilot.selfdrive.ui.lib.starpilot_state import starpilot_state
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import _SettingsPage
import pyray as rl
from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
    AetherSliderDialog,
    DEFAULT_PANEL_STYLE,
    SettingRow,
    SettingSection,
    AetherSettingsView,
    TileGrid,
    ToggleTile,
    AetherAdjustorRow,
    draw_list_group_shell,
    draw_section_header,
)

PANEL_STYLE = DEFAULT_PANEL_STYLE

THEME_KEY_CONFIG = {
    "BootLogo": {
        "default": "starpilot",
        "extra": [],
    },
}

COLOR_PRESETS = ["Stock", "#FFFFFF", "#178644", "#3B82F6", "#E63956", "#8B5CF6", "#F59E0B"]
CAMERA_VIEWS = ["Auto", "Driver", "Standard", "Wide"]


def _theme_display_name(value: str) -> str:
    if not value:
        return "Stock"
    if value.lower() == "stock":
        return "Stock"
    if value.lower() == "none":
        return "None"
    base, creator = (value.split("~", 1) + [""])[:2] if "~" in value else (value, "")
    user_created_suffixes = ("-user_created", "_user_created", "-user-created", "_user-created")
    user_created = False
    for suffix in user_created_suffixes:
        if base.endswith(suffix):
            base = base[:-len(suffix)]
            user_created = True
            break
    parts = [part for part in re.split(r"[-_]+", base) if part]
    display = " ".join(part[:1].upper() + part[1:] for part in parts) if parts else value
    if user_created:
        display += " (User Created)"
    if creator:
        display += f" - by: {creator}"
    return display





# ═══════════════════════════════════════════════════════════════
# Unified Appearance panel
# ═══════════════════════════════════════════════════════════════

class AppearanceManagerView(AetherSettingsView):
    def __init__(self, controller, sections, **kwargs):
        super().__init__(controller, sections, **kwargs)
        self._toggle_grid = TileGrid(columns=2, padding=12)
        self._toggle_grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
        self._init_toggles()
        self._init_adjustors()

    def _init_toggles(self):
        po = lambda: self._controller._params.get_bool("PedalsOnUI")
        ol = lambda: starpilot_state.car_state.hasOpenpilotLongitudinal
        bsm = lambda: starpilot_state.car_state.hasBSM

        toggles = [
            # Path Overlays
            {
                "title": tr("Driving Screen Widgets"),
                "subtitle": tr("Show interactive indicators on the driving screen."),
                "get_state": lambda: self._controller._params.get_bool("CustomUI"),
                "set_state": lambda s: self._controller._params.put_bool("CustomUI", s),
            },
            {
                "title": tr("Acceleration Path"),
                "get_state": lambda: self._controller._params.get_bool("AccelerationPath"),
                "set_state": lambda s: self._controller._params.put_bool("AccelerationPath", s),
                "is_enabled": ol,
            },
            {
                "title": tr("Adjacent Lanes"),
                "get_state": lambda: self._controller._params.get_bool("AdjacentPath"),
                "set_state": lambda s: self._controller._params.put_bool("AdjacentPath", s),
            },
            {
                "title": tr("Adjacent Lane Metrics"),
                "get_state": lambda: self._controller._params.get_bool("AdjacentPathMetrics"),
                "set_state": lambda s: self._controller._params.put_bool("AdjacentPathMetrics", s),
            },
            {
                "title": tr("Blind Spot Path"),
                "get_state": lambda: self._controller._params.get_bool("BlindSpotPath"),
                "set_state": lambda s: self._controller._params.put_bool("BlindSpotPath", s),
                "is_enabled": bsm,
            },
            # Dashboard Controls
            {
                "title": tr("Compass"),
                "get_state": lambda: self._controller._params.get_bool("Compass"),
                "set_state": lambda s: self._controller._params.put_bool("Compass", s),
            },
            {
                "title": tr("Personality Button"),
                "get_state": lambda: self._controller._params.get_bool("OnroadDistanceButton"),
                "set_state": lambda s: self._controller._params.put_bool("OnroadDistanceButton", s),
            },
            {
                "title": tr("Pedal Indicators"),
                "get_state": lambda: self._controller._params.get_bool("PedalsOnUI"),
                "set_state": lambda s: self._controller._params.put_bool("PedalsOnUI", s),
                "is_enabled": ol,
            },
            {
                "title": tr("Dynamic Pedals"),
                "get_state": lambda: self._controller._params.get_bool("DynamicPedalsOnUI"),
                "set_state": lambda s: self._controller._set_exclusive_pedal("DynamicPedalsOnUI", "StaticPedalsOnUI", s),
                "is_enabled": lambda: po() and ol(),
            },
            {
                "title": tr("Static Pedals"),
                "get_state": lambda: self._controller._params.get_bool("StaticPedalsOnUI"),
                "set_state": lambda s: self._controller._set_exclusive_pedal("StaticPedalsOnUI", "DynamicPedalsOnUI", s),
                "is_enabled": lambda: po() and ol(),
            },
            {
                "title": tr("Rotating Wheel"),
                "get_state": lambda: self._controller._params.get_bool("RotatingWheel"),
                "set_state": lambda s: self._controller._params.put_bool("RotatingWheel", s),
            },
            # Screen Borders
            {
                "title": tr("Steering Torque Indicator"),
                "get_state": lambda: self._controller._params.get_bool("ShowSteering"),
                "set_state": lambda s: self._controller._params.put_bool("ShowSteering", s),
            },
            {
                "title": tr("Turn Signal Borders"),
                "get_state": lambda: self._controller._params.get_bool("SignalMetrics"),
                "set_state": lambda s: self._controller._params.put_bool("SignalMetrics", s),
            },
            {
                "title": tr("Blind Spot Borders"),
                "get_state": lambda: self._controller._params.get_bool("BlindSpotMetrics"),
                "set_state": lambda s: self._controller._params.put_bool("BlindSpotMetrics", s),
                "is_enabled": bsm,
            },
            # Developer Metrics
            {
                "title": tr("Radar Point Display"),
                "get_state": lambda: self._controller._params.get_bool("RadarTracksUI"),
                "set_state": lambda s: self._controller._params.put_bool("RadarTracksUI", s),
            },
            {
                "title": tr("Lead Vehicle Metrics"),
                "get_state": lambda: self._controller._params.get_bool("LeadInfo"),
                "set_state": lambda s: self._controller._params.put_bool("LeadInfo", s),
                "is_enabled": ol,
            },
            {
                "title": tr("Show Stop Sign"),
                "get_state": lambda: self._controller._params.get_bool("ShowStoppingPoint"),
                "set_state": lambda s: self._controller._params.put_bool("ShowStoppingPoint", s),
                "is_enabled": ol,
            },
            {
                "title": tr("Stop Distance"),
                "get_state": lambda: self._controller._params.get_bool("ShowStoppingPointMetrics"),
                "set_state": lambda s: self._controller._params.put_bool("ShowStoppingPointMetrics", s),
                "is_enabled": lambda: self._controller._params.get_bool("ShowStoppingPoint") and ol(),
            },
            {
                "title": tr("Developer Sidebar"),
                "subtitle": tr("Driving metrics panel on the right"),
                "get_state": lambda: self._controller._params.get_bool("DeveloperSidebar"),
                "set_state": lambda s: self._controller._params.put_bool("DeveloperSidebar", s),
            },
        ]

        for toggle_def in toggles:
            self._toggle_grid.add_tile(
                ToggleTile(
                    title=toggle_def["title"],
                    get_state=toggle_def.get("get_state"),
                    set_state=toggle_def.get("set_state"),
                    bg_color=self._panel_style.accent,
                    desc=toggle_def.get("subtitle", ""),
                    is_enabled=toggle_def.get("is_enabled"),
                    disabled_label=toggle_def.get("disabled_label", ""),
                )
            )

        self.register_page_grid(self._toggle_grid)
        self._set_toggle_pages([toggles[i:i+6] for i in range(0, len(toggles), 6)])

    def _init_adjustors(self):
        ol = lambda: starpilot_state.car_state.hasOpenpilotLongitudinal
        def on_close(res, val):
            if res == DialogResult.CONFIRM:
                self._controller._params.put_int("LeadDetectionThreshold", int(val))
                
        self._adjustor = AetherAdjustorRow(
            tr("Lead Detection Threshold"),
            "",
            25.0, 100.0, 1.0,
            get_value=lambda: float(self._controller._params.get_int("LeadDetectionThreshold", return_default=True, default=35)),
            on_change=lambda _v: None,
            on_commit=None,
            unit="%",
            labels={},
            presets=[25, 50, 75, 100],
            is_active=lambda: False,
            set_active=lambda active: gui_app.push_widget(
                AetherSliderDialog(
                    tr("Lead Detection Threshold"),
                    25.0,
                    100.0,
                    1.0,
                    float(self._controller._params.get_int("LeadDetectionThreshold", return_default=True, default=35)),
                    on_close,
                    presets=[25.0, 50.0, 75.0, 100.0],
                    unit="%",
                    color=self._panel_style.accent,
                )
            ) if active else None,
            style=self._panel_style,
            color=self._panel_style.accent,
        )
        self._adjustor.set_enabled(ol)
        self._child(self._adjustor)

    def _measure_content_height(self, width: float) -> float:
        if self._active_tab_key == "widgets":
            col_width = (width - self.COLUMN_GAP) / 2 if self._uses_two_columns(width) else width
            
            left_h = self._adjustor.measure_height(col_width)
            section_overhead = self._metrics.section_header_height + self._metrics.section_header_gap
            left_column_total_h = left_h + section_overhead

            tiles_content_h = self._toggle_grid.measure_height(col_width - 24)
            right_column_total_h = tiles_content_h + 24 + section_overhead
            
            tab_h = self.TAB_HEIGHT + self.TAB_BOTTOM_GAP if self._tab_defs else 0
            
            if self._uses_two_columns(width):
                content_h = max(left_column_total_h, right_column_total_h)
            else:
                content_h = left_column_total_h + self._metrics.section_gap + right_column_total_h
            
            return tab_h + content_h
        else:
            return super()._measure_content_height(width)

    def _draw_scroll_content(self, rect: rl.Rectangle, width: float):
        if self._active_tab_key == "widgets":
            y = rect.y + self._scroll_offset
            if self._tab_defs:
                y = self._draw_tabs(y, rect.x, width)

            if self._uses_two_columns(width):
                col_w = self._column_width(width)
                
                # Left Column: Lead Detection Threshold
                draw_section_header(
                    rl.Rectangle(rect.x, y, col_w, self._metrics.section_header_height),
                    tr("Developer Metrics"), style=self._panel_style
                )
                left_group_y = y + self._metrics.section_header_height + self._metrics.section_header_gap
                
                left_h = self._adjustor.measure_height(col_w)
                draw_list_group_shell(rl.Rectangle(rect.x, left_group_y, col_w, left_h), style=self._panel_style)
                
                self._adjustor.set_is_last(True)
                self._adjustor.set_parent_rect(self._scroll_rect)
                self._adjustor.render(rl.Rectangle(rect.x, left_group_y, col_w, left_h))
                
                # Right Column: Toggles
                self._draw_two_column_tile_grid(self._toggle_grid, rect.x + col_w + self.COLUMN_GAP, y, col_w, self._scroll_rect.height - (y - rect.y), title=tr("Widgets"), style=self._panel_style)
            else:
                # Single column
                draw_section_header(
                    rl.Rectangle(rect.x, y, width, self._metrics.section_header_height),
                    tr("Developer Metrics"), style=self._panel_style
                )
                y += self._metrics.section_header_height + self._metrics.section_header_gap
                left_h = self._adjustor.measure_height(width)
                draw_list_group_shell(rl.Rectangle(rect.x, y, width, left_h), style=self._panel_style)
                self._adjustor.set_is_last(True)
                self._adjustor.set_parent_rect(self._scroll_rect)
                self._adjustor.render(rl.Rectangle(rect.x, y, width, left_h))
                y += left_h + self._metrics.section_gap
                
                draw_section_header(
                    rl.Rectangle(rect.x, y, width, self._metrics.section_header_height),
                    tr("Widgets"), style=self._panel_style
                )
                y += self._metrics.section_header_height + self._metrics.section_header_gap
                tiles_content_h = self._toggle_grid.measure_height(width - 24)
                draw_list_group_shell(rl.Rectangle(rect.x, y, width, tiles_content_h + 24), style=self._panel_style)
                self._render_page_grid(self._toggle_grid, rl.Rectangle(rect.x + 12, y + 12, width - 24, tiles_content_h))

        else:
            super()._draw_scroll_content(rect, width)

# ═══════════════════════════════════════════════════════════════
# Unified Appearance panel
# ═══════════════════════════════════════════════════════════════

class StarPilotAppearanceLayout(_SettingsPage):
    def __init__(self):
        super().__init__()
        self._build_view()

    def _build_view(self):
        tab_defs = [
            {"id": "widgets", "title": tr_noop("Widgets"), "subtitle": tr_noop("Driving indicators")},
            {"id": "display", "title": tr_noop("Display"), "subtitle": tr_noop("Screen visibility")},
            {"id": "convenience", "title": tr_noop("Convenience"), "subtitle": tr_noop("QOL & navigation")},
            {"id": "model", "title": tr_noop("Model"), "subtitle": tr_noop("Path visualization")},
            {"id": "theme", "title": tr_noop("Theme"), "subtitle": tr_noop("Customization")},
        ]

        po = lambda: self._params.get_bool("PedalsOnUI")
        ol = lambda: starpilot_state.car_state.hasOpenpilotLongitudinal
        bsm = lambda: starpilot_state.car_state.hasBSM

        sections: list[SettingSection] = [
            # ═══ Tab 2: Display — screen visibility toggles ═══
            SettingSection(tr_noop("Screen Elements"), [
                SettingRow("AdvancedCustomUI", "toggle", tr_noop("Advanced UI Controls"),
                           subtitle=tr_noop("Fine-tune which elements appear on screen."),
                           get_state=lambda: self._params.get_bool("AdvancedCustomUI"),
                           set_state=lambda s: self._params.put_bool("AdvancedCustomUI", s)),
                SettingRow("HideSpeed", "toggle", tr_noop("Hide Speed"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideSpeed"),
                           set_state=lambda s: self._params.put_bool("HideSpeed", s)),
                SettingRow("HideMaxSpeed", "toggle", tr_noop("Hide Max Speed"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideMaxSpeed"),
                           set_state=lambda s: self._params.put_bool("HideMaxSpeed", s)),
                SettingRow("HideAlerts", "toggle", tr_noop("Hide Alerts"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideAlerts"),
                           set_state=lambda s: self._params.put_bool("HideAlerts", s)),
                SettingRow("HideChangingLanesBanner", "toggle", tr_noop("Hide Changing Lanes Banner"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideChangingLanesBanner"),
                           set_state=lambda s: self._params.put_bool("HideChangingLanesBanner", s)),
                SettingRow("HideDistanceProfileBanner", "toggle", tr_noop("Hide Distance Profile Banner"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideDistanceProfileBanner"),
                           set_state=lambda s: self._params.put_bool("HideDistanceProfileBanner", s)),
                SettingRow("HideTurningBanner", "toggle", tr_noop("Hide Turning Banner"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideTurningBanner"),
                           set_state=lambda s: self._params.put_bool("HideTurningBanner", s)),
                SettingRow("HideDMIcon", "toggle", tr_noop("Hide Driver Monitoring Icon"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideDMIcon"),
                           set_state=lambda s: self._params.put_bool("HideDMIcon", s)),
                SettingRow("HideSteeringWheel", "toggle", tr_noop("Hide Steering Wheel"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideSteeringWheel"),
                           set_state=lambda s: self._params.put_bool("HideSteeringWheel", s)),
            ], tab_key="display", column_pair="display"),

            SettingSection(tr_noop("Speed Info"), [
                SettingRow("HideSpeedLimit", "toggle", tr_noop("Hide Speed Limit"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideSpeedLimit"),
                           set_state=lambda s: self._params.put_bool("HideSpeedLimit", s)),
                SettingRow("HideLeadMarker", "toggle", tr_noop("Hide Lead Marker"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("HideLeadMarker"),
                           set_state=lambda s: self._params.put_bool("HideLeadMarker", s),
                           visible=ol),
                SettingRow("WheelSpeed", "toggle", tr_noop("Wheel Speed"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("WheelSpeed"),
                           set_state=lambda s: self._params.put_bool("WheelSpeed", s)),
            ], tab_key="display", column_pair="display"),

            # ═══ Tab 3: Convenience — QOL + Navigation ═══
            SettingSection(tr_noop("Quality of Life"), [
                SettingRow("QOLVisuals", "toggle", tr_noop("Quality of Life"),
                           subtitle=tr_noop("Convenience features for everyday driving."),
                           get_state=lambda: self._params.get_bool("QOLVisuals"),
                           set_state=lambda s: self._params.put_bool("QOLVisuals", s)),
                SettingRow("CameraView", "value", tr_noop("Camera View"),
                           subtitle="",
                           get_value=lambda: tr(CAMERA_VIEWS[self._params.get_int("CameraView")]),
                           on_click=self._show_camera_view_selector),
                SettingRow("DriverCamera", "toggle", tr_noop("Driver Camera"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("DriverCamera"),
                           set_state=lambda s: self._params.put_bool("DriverCamera", s)),
                SettingRow("StoppedTimer", "toggle", tr_noop("Stopped Timer"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("StoppedTimer"),
                           set_state=lambda s: self._params.put_bool("StoppedTimer", s)),
            ], tab_key="convenience", column_pair="convenience"),

            SettingSection(tr_noop("Navigation"), [
                SettingRow("NavigationUI", "toggle", tr_noop("Navigation Widgets"),
                           subtitle=tr_noop("Show navigation info on the driving screen."),
                           get_state=lambda: self._params.get_bool("NavigationUI"),
                           set_state=lambda s: self._params.put_bool("NavigationUI", s)),
                SettingRow("ClearNavOnOffroad", "toggle", tr_noop("Clear Route When Offroad"),
                           subtitle=tr_noop("Clear the active navigation destination when the device goes offroad."),
                           get_state=lambda: self._params.get_bool("ClearNavOnOffroad"),
                           set_state=lambda s: self._params.put_bool("ClearNavOnOffroad", s)),
                SettingRow("RoadNameUI", "toggle", tr_noop("Road Name"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("RoadNameUI"),
                           set_state=lambda s: self._params.put_bool("RoadNameUI", s)),
                SettingRow("ShowSpeedLimits", "toggle", tr_noop("Speed Limits"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("ShowSpeedLimits"),
                           set_state=lambda s: self._params.put_bool("ShowSpeedLimits", s)),
                SettingRow("UseVienna", "toggle", tr_noop("Vienna Signs"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("UseVienna"),
                           set_state=lambda s: self._params.put_bool("UseVienna", s)),
            ], tab_key="convenience", column_pair="convenience"),

            # ═══ Tab 4: Model — path/lane visualization ═══
            SettingSection(tr_noop("Path & Lanes"), [
                SettingRow("ModelUI", "toggle", tr_noop("Model UI"),
                           subtitle=tr_noop("Display the driving model path, lanes, and road edges."),
                           get_state=lambda: self._params.get_bool("ModelUI"),
                           set_state=lambda s: self._params.put_bool("ModelUI", s)),
                SettingRow("DynamicPathWidth", "toggle", tr_noop("Dynamic Path"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("DynamicPathWidth"),
                           set_state=lambda s: self._params.put_bool("DynamicPathWidth", s)),
                SettingRow("LaneLinesWidth", "value", tr_noop("Lane Line Width"),
                           subtitle="",
                           get_value=lambda: self._get_lane_lines_display(),
                           on_click=lambda: self._show_int_selector("LaneLinesWidth", 0, 24, self._get_lane_lines_unit())),
                SettingRow("LaneLinesColor", "value", tr_noop("Lane Line Color"),
                           subtitle="",
                           get_value=lambda: self._get_color_display("LaneLinesColor"),
                           on_click=lambda: self._show_color_selector("LaneLinesColor")),
                SettingRow("PathWidth", "value", tr_noop("Path Width"),
                           subtitle="",
                           get_value=lambda: self._get_path_width_display(),
                           on_click=self._show_path_width_selector),
            ], tab_key="model", column_pair="model"),

            SettingSection(tr_noop("Edges & Colors"), [
                SettingRow("PathEdgeWidth", "value", tr_noop("Path Edge Width"),
                           subtitle="",
                           get_value=lambda: f"{self._params.get_int('PathEdgeWidth')}%",
                           on_click=lambda: self._show_int_selector("PathEdgeWidth", 0, 100, "%")),
                SettingRow("PathEdgesColor", "value", tr_noop("Path Edge Color"),
                           subtitle="",
                           get_value=lambda: self._get_color_display("PathEdgesColor"),
                           on_click=lambda: self._show_color_selector("PathEdgesColor")),
                SettingRow("PathColor", "value", tr_noop("Path Color"),
                           subtitle="",
                           get_value=lambda: self._get_color_display("PathColor"),
                           on_click=lambda: self._show_color_selector("PathColor")),
                SettingRow("RoadEdgesWidth", "value", tr_noop("Road Edge Width"),
                           subtitle="",
                           get_value=lambda: self._get_road_edges_display(),
                           on_click=lambda: self._show_int_selector("RoadEdgesWidth", 0, 24, self._get_road_edges_unit())),
                SettingRow("BorderWidth", "value", tr_noop("Border Width"),
                           subtitle="",
                           get_value=lambda: f"{int(round(self._params.get_float('BorderWidth')))}%",
                           on_click=lambda: self._show_float_selector("BorderWidth", 25, 250, 5, "%")),
            ], tab_key="model", column_pair="model"),

            # ═══ Tab 5: Theme — customization ═══
            SettingSection(tr_noop("Customization"), [
                SettingRow("BootLogo", "value", tr_noop("Boot Logo"),
                           subtitle="",
                           get_value=lambda: self._get_theme_value("BootLogo"),
                           on_click=lambda: self._show_theme_selector("BootLogo")),
                SettingRow("RainbowPath", "toggle", tr_noop("Rainbow Path"),
                           subtitle="",
                           get_state=lambda: self._params.get_bool("RainbowPath"),
                           set_state=lambda s: self._params.put_bool("RainbowPath", s)),
            ], tab_key="theme", column_pair="theme"),

            SettingSection(tr_noop("Options"), [
                SettingRow("StartupAlert", "value", tr_noop("Startup Alert"),
                           subtitle="",
                           get_value=self._get_startup_alert_display,
                           on_click=self._show_startup_alert_selector),
            ], tab_key="theme", column_pair="theme"),
        ]

        self._manager_view = AppearanceManagerView(
            self, sections,
            header_title=tr_noop("Appearance"),
            header_subtitle=tr_noop("Customize your display, driving widgets, model visualization, and themes."),
            tab_defs=tab_defs,
            panel_style=PANEL_STYLE,
        )

    # ── Theme helpers ──

    def _build_theme_options(self, key: str) -> tuple[list[str], dict[str, str], str]:
        config = THEME_KEY_CONFIG[key]
        options_map = {display: slug for slug, display in config["extra"]}
        current_slug = self._params.get(key, encoding='utf-8') or config["default"]
        current_display = _theme_display_name(current_slug)
        if current_display not in options_map:
            options_map[current_display] = current_slug
        options = sorted(options_map.keys(), key=str.casefold)
        return options, options_map, current_display

    def _get_theme_value(self, key: str) -> str:
        default = THEME_KEY_CONFIG[key]["default"]
        return _theme_display_name(self._params.get(key, encoding='utf-8') or default)

    def _show_theme_selector(self, key):
        themes, option_map, current = self._build_theme_options(key)
        if not themes:
            return

        def on_select(res):
            if res == DialogResult.CONFIRM and dialog.selection:
                selected_slug = option_map.get(dialog.selection)
                if selected_slug is None:
                    return
                self._params.put(key, selected_slug)

        dialog = MultiOptionDialog(tr(key), themes, current, callback=on_select)
        gui_app.push_widget(dialog)

    # ── Widget helpers ──

    def _set_exclusive_pedal(self, key, other_key, state):
        self._params.put_bool(key, state)
        if state:
            self._params.put_bool(other_key, False)

    # ── Camera view ──

    def _show_camera_view_selector(self):
        current = self._params.get_int("CameraView")

        def on_select(res):
            if res == DialogResult.CONFIRM and dialog.selection:
                idx = CAMERA_VIEWS.index(dialog.selection)
                self._params.put_int("CameraView", idx)

        dialog = MultiOptionDialog(tr("Camera View"), CAMERA_VIEWS, CAMERA_VIEWS[current], callback=on_select)
        gui_app.push_widget(dialog)

    # ── Color selectors ──

    def _get_color_display(self, key):
        val = self._params.get(key, encoding='utf-8') or ""
        if not val:
            return "Stock"
        return val.upper()

    def _show_color_selector(self, key):
        current = self._params.get(key, encoding='utf-8') or "Stock"

        def on_select(res):
            if res == DialogResult.CONFIRM and dialog.selection:
                if dialog.selection == "Stock":
                    self._params.remove(key)
                else:
                    self._params.put(key, dialog.selection)

        dialog = MultiOptionDialog(tr(key), COLOR_PRESETS, current, callback=on_select)
        gui_app.push_widget(dialog)

    # ── Numeric sliders (int / float) ──

    def _show_int_selector(self, key, min_v, max_v, unit=""):
        def on_close(res, val):
            if res == DialogResult.CONFIRM:
                self._params.put_int(key, int(val))
        gui_app.push_widget(AetherSliderDialog(tr(key), min_v, max_v, 1, self._params.get_int(key), on_close,
                                                 unit=unit, color=PANEL_STYLE.accent))

    def _show_float_selector(self, key, min_v, max_v, step, unit="", convert=None, unconvert=None):
        current = self._params.get_float(key)
        if convert:
            current = convert(current)

        def on_close(res, val):
            if res == DialogResult.CONFIRM:
                v = float(val)
                if unconvert:
                    v = unconvert(v)
                self._params.put_float(key, v)

        gui_app.push_widget(AetherSliderDialog(tr(key), min_v, max_v, step, current, on_close,
                                                 unit=unit, color=PANEL_STYLE.accent))

    # ── Unit-aware display helpers ──

    def _is_metric(self):
        return self._params.get_bool("IsMetric")

    def _get_lane_lines_unit(self):
        return "cm" if self._is_metric() else "in"

    def _get_lane_lines_display(self):
        val = self._params.get_int("LaneLinesWidth")
        if self._is_metric():
            return f"{int(val * 2.54)}cm"
        return f"{val}in"

    def _get_road_edges_unit(self):
        return "cm" if self._is_metric() else "in"

    def _get_road_edges_display(self):
        val = self._params.get_int("RoadEdgesWidth")
        if self._is_metric():
            return f"{int(val * 2.54)}cm"
        return f"{val}in"

    def _get_path_width_display(self):
        val = self._params.get_float("PathWidth")
        if self._is_metric():
            return f"{val / 3.28084:.1f}m"
        return f"{val:.1f}ft"

    def _show_path_width_selector(self):
        if self._is_metric():
            self._show_float_selector("PathWidth", 0, 10, 0.1, "m", convert=lambda v: v / 3.28084, unconvert=lambda v: v * 3.28084)
        else:
            self._show_float_selector("PathWidth", 0, 10, 0.1, "ft")

    # ── Startup alert ──

    def _get_startup_alert_display(self):
        current_top = self._params.get("StartupMessageTop", encoding='utf-8') or ""
        if current_top == "Be ready to take over at any time":
            return "Stock"
        if current_top == "Hop in and buckle up!":
            return "StarPilot"
        return "Clear"

    def _show_startup_alert_selector(self):
        options = ["Stock", "StarPilot", "Clear"]
        current = self._get_startup_alert_display()

        def on_select(res):
            if res == DialogResult.CONFIRM and dialog.selection:
                if dialog.selection == "Stock":
                    self._params.put("StartupMessageTop", "Be ready to take over at any time")
                    self._params.put("StartupMessageBottom", "Always keep hands on wheel and eyes on road")
                elif dialog.selection == "StarPilot":
                    self._params.put("StartupMessageTop", "Hop in and buckle up!")
                    self._params.put("StartupMessageBottom", "Human-tested, frog-approved")
                else:
                    self._params.remove("StartupMessageTop")
                    self._params.remove("StartupMessageBottom")

        dialog = MultiOptionDialog(tr("Startup Alert"), options, current, callback=on_select)
        gui_app.push_widget(dialog)
