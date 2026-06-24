from __future__ import annotations
import re
import math

from openpilot.system.ui.lib.application import gui_app, FontWeight, MousePos
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.lib.scroll_panel2 import GuiScrollPanel2
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.system.ui.widgets import DialogResult, Widget
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
    AetherCategoryTileView,
    TileGrid,
    HubTile,
    draw_list_group_shell,
    _draw_rounded_fill,
    _draw_rounded_stroke,
    _point_hits,
    _snap_rect,
    _mix_colors,
    _with_alpha,
    hex_to_color,
    PLATE_TAU,
    AetherListColors,
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
    @property
    def vertical_scrolling_disabled(self) -> bool:
        return True

    def __init__(self, controller, sections, **kwargs):
        super().__init__(controller, sections, **kwargs)
        self._hero_grid = TileGrid(columns=3, padding=12)
        self._hero_grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
        self._child(self._hero_grid)

        self._standard_grid = TileGrid(columns=3, padding=12)
        self._standard_grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
        self._child(self._standard_grid)

        self._init_toggles()

    def _init_toggles(self):
        hero_data = [
            {
                "title": tr("Model & Path Visualization"),
                "desc": tr("Customize dynamic lane paths, road edges, and colors."),
                "icon": "steering",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Model & Path Visualization"),
                        self._controller._model_rows,
                        color="#8B5CF6",
                        subtitle=tr("Customize dynamic lane paths, road edges, and colors."),
                        panel_style=self._panel_style,
                    )
                )
            },
            {
                "title": tr("Driving Widgets & HUD"),
                "desc": tr("Configure compass, dynamic pedals, signals, and screen borders."),
                "icon": "display",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Driving Widgets & HUD"),
                        self._controller._hud_rows,
                        color="#8B5CF6",
                        subtitle=tr("Configure compass, dynamic pedals, signals, and screen borders."),
                        panel_style=self._panel_style,
                    )
                )
            },
            {
                "title": tr("Screen Declutter & Visibility"),
                "desc": tr("Toggle speed limits, alert banners, and driver monitoring icon."),
                "icon": "system",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Screen Declutter & Visibility"),
                        self._controller._declutter_rows,
                        color="#8B5CF6",
                        subtitle=tr("Toggle speed limits, alert banners, and driver monitoring icon."),
                        panel_style=self._panel_style,
                    )
                )
            },
        ]

        standard_data = [
            {
                "title": tr("Navigation & Mapping"),
                "desc": tr("Configure road names, Vienna signs, and offroad routes."),
                "icon": "navigate",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Navigation & Mapping"),
                        self._controller._nav_rows,
                        color="#8B5CF6",
                        subtitle=tr("Configure road names, Vienna signs, and offroad routes."),
                        panel_style=self._panel_style,
                    )
                )
            },
            {
                "title": tr("Camera & System Startup"),
                "desc": tr("Manage driver monitoring cameras, boot logos, and startup sounds."),
                "icon": "vehicle",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Camera & System Startup"),
                        self._controller._system_rows,
                        color="#8B5CF6",
                        subtitle=tr("Manage driver monitoring cameras, boot logos, and startup sounds."),
                        panel_style=self._panel_style,
                    )
                )
            },
            {
                "title": tr("Developer & Beta Metrics"),
                "desc": tr("Adjust radar plots, lead vehicle info, and stop sign metrics."),
                "icon": "sound",
                "color": "#8B5CF6",
                "on_click": lambda: gui_app.push_widget(
                    AetherCategoryTileView(
                        self._controller,
                        tr("Developer & Beta Metrics"),
                        self._controller._dev_rows,
                        color="#8B5CF6",
                        subtitle=tr("Adjust radar plots, lead vehicle info, and stop sign metrics."),
                        panel_style=self._panel_style,
                    )
                )
            },
        ]

        self._hero_grid.clear()
        for d in hero_data:
            self._hero_grid.add_tile(
                HubTile(
                    title=d["title"],
                    desc=d["desc"],
                    icon_key=d["icon"],
                    on_click=d["on_click"],
                    bg_color=d["color"],
                )
            )

        self._standard_grid.clear()
        for d in standard_data:
            self._standard_grid.add_tile(
                HubTile(
                    title=d["title"],
                    desc=d["desc"],
                    icon_key=d["icon"],
                    on_click=d["on_click"],
                    bg_color=d["color"],
                )
            )

    def _render(self, rect: rl.Rectangle):
        self.set_rect(rect)
        self._interactive_rects.clear()

        margin_x = 12.0
        margin_top = 16.0
        margin_bottom = 16.0
        header_h = 90.0
        gap_after_header = 16.0

        # Draw the header at the top of rect:
        header_rect = rl.Rectangle(rect.x + margin_x, rect.y + margin_top, rect.width - margin_x * 2, header_h)
        self._draw_header(header_rect)

        # Draw a nice separator line under the header:
        divider_y = rect.y + margin_top + header_h + 8.0
        rl.draw_line_ex(
            rl.Vector2(rect.x + margin_x, divider_y),
            rl.Vector2(rect.x + rect.width - margin_x, divider_y),
            2.0,
            rl.Color(255, 255, 255, 16)
        )

        # Compute remaining scroll rect:
        grid_top = divider_y + gap_after_header
        grid_h = rect.y + rect.height - grid_top - margin_bottom

        self._scroll_rect = rl.Rectangle(rect.x + margin_x, grid_top, rect.width - margin_x * 2, grid_h)
        self._content_height = grid_h

        # Update scroll panel to maintain touch/click validation:
        self._scroll_panel.set_enabled(self.is_visible)
        self._scroll_offset = self._scroll_panel.update(
            self._scroll_rect, self._scroll_rect.height
        )

        # Draw tiles inside scroll_rect:
        self._draw_scroll_content(self._scroll_rect, self._scroll_rect.width)

    def _draw_scroll_content(self, rect: rl.Rectangle, width: float):
        y = rect.y + self._scroll_offset
        viewport_h = rect.height
        
        gap_y = 12.0
        padding_bottom = 6.0
        tile_space = viewport_h - gap_y - padding_bottom
        
        # Hero tiles are larger/taller
        hero_h = tile_space * 0.55
        standard_h = tile_space * 0.45
        
        self._hero_grid._tile_height = hero_h
        self._standard_grid._tile_height = standard_h
        
        self._hero_grid.set_parent_rect(self._scroll_rect)
        self._hero_grid.render(rl.Rectangle(rect.x, y, width, hero_h))
        
        self._standard_grid.set_parent_rect(self._scroll_rect)
        self._standard_grid.render(rl.Rectangle(rect.x, y + hero_h + gap_y, width, standard_h))


class StarPilotAppearanceLayout(_SettingsPage):
    def __init__(self):
        super().__init__()
        self._build_view()

    def _show_lead_detection_threshold_selector(self):
        def on_close(res, val):
            if res == DialogResult.CONFIRM:
                self._params.put_int("LeadDetectionThreshold", int(val))
        gui_app.push_widget(
            AetherSliderDialog(
                tr("Lead Detection Threshold"),
                25.0, 100.0, 1.0,
                float(self._params.get_int("LeadDetectionThreshold", return_default=True, default=35)),
                on_close,
                presets=[25.0, 50.0, 75.0, 100.0],
                unit="%",
                color=PANEL_STYLE.accent,
            )
        )

    def _build_view(self):
        po = lambda: self._params.get_bool("PedalsOnUI")
        ol = lambda: starpilot_state.car_state.hasOpenpilotLongitudinal
        bsm = lambda: starpilot_state.car_state.hasBSM

        # ═══ 1. Model & Path Visualization ═══
        self._model_rows = [
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
                       get_value=self._get_lane_lines_display,
                       on_click=lambda: self._show_int_selector("LaneLinesWidth", 0, 24, self._get_lane_lines_unit())),
            SettingRow("LaneLinesColor", "value", tr_noop("Lane Line Color"),
                       subtitle="",
                       get_value=lambda: self._get_color_display("LaneLinesColor"),
                       on_click=lambda: self._show_color_selector("LaneLinesColor")),
            SettingRow("PathWidth", "value", tr_noop("Path Width"),
                       subtitle="",
                       get_value=self._get_path_width_display,
                       on_click=self._show_path_width_selector),
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
                       get_value=self._get_road_edges_display,
                       on_click=lambda: self._show_int_selector("RoadEdgesWidth", 0, 24, self._get_road_edges_unit())),
            SettingRow("RainbowPath", "toggle", tr_noop("Rainbow Path"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("RainbowPath"),
                       set_state=lambda s: self._params.put_bool("RainbowPath", s)),
            SettingRow("AccelerationPath", "toggle", tr_noop("Acceleration Path"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("AccelerationPath"),
                       set_state=lambda s: self._params.put_bool("AccelerationPath", s),
                       enabled=ol),
            SettingRow("AdjacentPath", "toggle", tr_noop("Adjacent Lanes"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("AdjacentPath"),
                       set_state=lambda s: self._params.put_bool("AdjacentPath", s)),
            SettingRow("AdjacentPathMetrics", "toggle", tr_noop("Adjacent Lane Metrics"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("AdjacentPathMetrics"),
                       set_state=lambda s: self._params.put_bool("AdjacentPathMetrics", s)),
            SettingRow("BlindSpotPath", "toggle", tr_noop("Blind Spot Path"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("BlindSpotPath"),
                       set_state=lambda s: self._params.put_bool("BlindSpotPath", s),
                       enabled=bsm),
        ]

        # ═══ 2. Driving Widgets & HUD ═══
        self._hud_rows = [
            SettingRow("CustomUI", "toggle", tr_noop("Driving Screen Widgets"),
                       subtitle=tr_noop("Show interactive indicators on the driving screen."),
                       get_state=lambda: self._params.get_bool("CustomUI"),
                       set_state=lambda s: self._params.put_bool("CustomUI", s)),
            SettingRow("Compass", "toggle", tr_noop("Compass"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("Compass"),
                       set_state=lambda s: self._params.put_bool("Compass", s)),
            SettingRow("OnroadDistanceButton", "toggle", tr_noop("Personality Button"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("OnroadDistanceButton"),
                       set_state=lambda s: self._params.put_bool("OnroadDistanceButton", s)),
            SettingRow("RotatingWheel", "toggle", tr_noop("Rotating Wheel"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("RotatingWheel"),
                       set_state=lambda s: self._params.put_bool("RotatingWheel", s)),
            SettingRow("ShowSteering", "toggle", tr_noop("Steering Torque Indicator"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("ShowSteering"),
                       set_state=lambda s: self._params.put_bool("ShowSteering", s)),
            SettingRow("SignalMetrics", "toggle", tr_noop("Turn Signal Borders"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("SignalMetrics"),
                       set_state=lambda s: self._params.put_bool("SignalMetrics", s)),
            SettingRow("BlindSpotMetrics", "toggle", tr_noop("Blind Spot Borders"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("BlindSpotMetrics"),
                       set_state=lambda s: self._params.put_bool("BlindSpotMetrics", s),
                       enabled=bsm),
            SettingRow("WheelSpeed", "toggle", tr_noop("Wheel Speed"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("WheelSpeed"),
                       set_state=lambda s: self._params.put_bool("WheelSpeed", s)),
            SettingRow("BorderWidth", "value", tr_noop("Border Width"),
                       subtitle="",
                       get_value=lambda: f"{int(round(self._params.get_float('BorderWidth')))}%",
                       on_click=lambda: self._show_float_selector("BorderWidth", 25, 250, 5, "%")),
            SettingRow("PedalsOnUI", "toggle", tr_noop("Pedal Indicators"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("PedalsOnUI"),
                       set_state=lambda s: self._params.put_bool("PedalsOnUI", s),
                       enabled=ol),
            SettingRow("DynamicPedalsOnUI", "toggle", tr_noop("Dynamic Pedals"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("DynamicPedalsOnUI"),
                       set_state=lambda s: self._set_exclusive_pedal("DynamicPedalsOnUI", "StaticPedalsOnUI", s),
                       enabled=lambda: po() and ol()),
            SettingRow("StaticPedalsOnUI", "toggle", tr_noop("Static Pedals"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("StaticPedalsOnUI"),
                       set_state=lambda s: self._set_exclusive_pedal("StaticPedalsOnUI", "DynamicPedalsOnUI", s),
                       enabled=lambda: po() and ol()),
            SettingRow("StoppedTimer", "toggle", tr_noop("Stopped Timer"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("StoppedTimer"),
                       set_state=lambda s: self._params.put_bool("StoppedTimer", s)),
        ]

        # ═══ 3. Screen Declutter & Visibility ═══
        self._declutter_rows = [
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
            SettingRow("HideSpeedLimit", "toggle", tr_noop("Hide Speed Limit"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("HideSpeedLimit"),
                       set_state=lambda s: self._params.put_bool("HideSpeedLimit", s)),
            SettingRow("HideAlerts", "toggle", tr_noop("Hide Alerts"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("HideAlerts"),
                       set_state=lambda s: self._params.put_bool("HideAlerts", s)),
            SettingRow("HideSteeringWheel", "toggle", tr_noop("Hide Steering Wheel"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("HideSteeringWheel"),
                       set_state=lambda s: self._params.put_bool("HideSteeringWheel", s)),
            SettingRow("HideDMIcon", "toggle", tr_noop("Hide Driver Monitoring Icon"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("HideDMIcon"),
                       set_state=lambda s: self._params.put_bool("HideDMIcon", s)),
            SettingRow("HideLeadMarker", "toggle", tr_noop("Hide Lead Marker"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("HideLeadMarker"),
                       set_state=lambda s: self._params.put_bool("HideLeadMarker", s),
                       visible=ol),
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
        ]

        # ═══ 4. Navigation & Mapping ═══
        self._nav_rows = [
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
            SettingRow("QOLVisuals", "toggle", tr_noop("Quality of Life"),
                       subtitle=tr_noop("Convenience features for everyday driving."),
                       get_state=lambda: self._params.get_bool("QOLVisuals"),
                       set_state=lambda s: self._params.put_bool("QOLVisuals", s)),
        ]

        # ═══ 5. Camera & System Startup ═══
        self._system_rows = [
            SettingRow("CameraView", "value", tr_noop("Camera View"),
                       subtitle="",
                       get_value=lambda: tr(CAMERA_VIEWS[self._params.get_int("CameraView")]),
                       on_click=self._show_camera_view_selector),
            SettingRow("DriverCamera", "toggle", tr_noop("Driver Camera"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("DriverCamera"),
                       set_state=lambda s: self._params.put_bool("DriverCamera", s)),
            SettingRow("BootLogo", "value", tr_noop("Boot Logo"),
                       subtitle="",
                       get_value=lambda: self._get_theme_value("BootLogo"),
                       on_click=lambda: self._show_theme_selector("BootLogo")),
            SettingRow("StartupAlert", "value", tr_noop("Startup Alert"),
                       subtitle="",
                       get_value=self._get_startup_alert_display,
                       on_click=self._show_startup_alert_selector),
        ]

        # ═══ 6. Developer & Beta Metrics ═══
        self._dev_rows = [
            SettingRow("DeveloperSidebar", "toggle", tr_noop("Developer Sidebar"),
                       subtitle=tr_noop("Driving metrics panel on the right"),
                       get_state=lambda: self._params.get_bool("DeveloperSidebar"),
                       set_state=lambda s: self._params.put_bool("DeveloperSidebar", s)),
            SettingRow("LeadDetectionThreshold", "value", tr_noop("Lead Detection Threshold"),
                       subtitle="",
                       get_value=lambda: f"{self._params.get_int('LeadDetectionThreshold', return_default=True, default=35)}%",
                       on_click=self._show_lead_detection_threshold_selector,
                       enabled=ol),
            SettingRow("LeadInfo", "toggle", tr_noop("Lead Vehicle Metrics"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("LeadInfo"),
                       set_state=lambda s: self._params.put_bool("LeadInfo", s),
                       enabled=ol),
            SettingRow("RadarTracksUI", "toggle", tr_noop("Radar Point Display"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("RadarTracksUI"),
                       set_state=lambda s: self._params.put_bool("RadarTracksUI", s)),
            SettingRow("ShowStoppingPoint", "toggle", tr_noop("Show Stop Sign"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("ShowStoppingPoint"),
                       set_state=lambda s: self._params.put_bool("ShowStoppingPoint", s),
                       enabled=ol),
            SettingRow("ShowStoppingPointMetrics", "toggle", tr_noop("Stop Distance"),
                       subtitle="",
                       get_state=lambda: self._params.get_bool("ShowStoppingPointMetrics"),
                       set_state=lambda s: self._params.put_bool("ShowStoppingPointMetrics", s),
                       enabled=lambda: self._params.get_bool("ShowStoppingPoint") and ol()),
        ]

        self._manager_view = AppearanceManagerView(
            self, [],
            header_title=tr_noop("Appearance"),
            header_subtitle=tr_noop("Customize your display, driving widgets, model visualization, and themes."),
            tab_defs=None,
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
