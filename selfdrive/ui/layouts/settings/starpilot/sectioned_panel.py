from __future__ import annotations

from dataclasses import dataclass

import pyray as rl

from openpilot.system.ui.lib.application import FontWeight, gui_app
from openpilot.system.ui.lib.scroll_panel2 import GuiScrollPanel2
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.system.ui.widgets import Widget

from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import SPACING, TileGrid, AetherScrollbar


@dataclass(frozen=True)
class TileSection:
  title: str
  grid: TileGrid


class SectionedTileLayout(Widget):
  def __init__(self, section_gap: int = SPACING.section_gap, title_height: int = 32, title_gap: int = SPACING.sm,
               min_row_height: int = 150, max_row_height: int = 280, top_padding: int = 0,
               horizontal_padding: int = SPACING.xl, max_content_width: int | None = 1440):
    super().__init__()
    self._sections: list[TileSection] = []
    self._section_gap = section_gap
    self._title_height = title_height
    self._title_gap = title_gap
    self._min_row_height = min_row_height
    self._max_row_height = max_row_height
    self._top_padding = top_padding
    self._horizontal_padding = horizontal_padding
    self._max_content_width = max_content_width
    self._title_font_size = 26
    self._font_title = gui_app.font(FontWeight.BOLD)
    self._is_active = False
    self._scroll_panel = GuiScrollPanel2(horizontal=False)
    self._scrollbar = AetherScrollbar()
    self._scroll_offset = 0.0
    self._content_height = 0.0

  def set_sections(self, sections: list[TileSection]):
    if self._is_active:
      for section in self._sections:
        section.grid.hide_event()
    self._sections = list(sections)
    if self._is_active:
      for section in self._sections:
        section.grid.show_event()

  def clear(self):
    self._sections.clear()

  def show_event(self):
    self._is_active = True
    super().show_event()
    self._scroll_offset = 0.0
    for section in self._sections:
      section.grid.show_event()

  def hide_event(self):
    self._is_active = False
    super().hide_event()
    for section in self._sections:
      section.grid.hide_event()

  def _content_height_for_layout(self, rect: rl.Rectangle, sections: list[TileSection], title_height: int, title_gap: int, section_gap: int, row_height: float) -> float:
    total = self._top_padding
    for index, section in enumerate(sections):
      total += self._title_block_height(section, title_height, title_gap)
      total += (section.grid.get_row_count(available_width=rect.width) * row_height) + section.grid.get_internal_gap_height(available_width=rect.width)
      if index < len(sections) - 1:
        total += section_gap
    return total

  def _title_block_height(self, section: TileSection, title_height: int | None = None, title_gap: int | None = None) -> int:
    resolved_title_height = self._title_height if title_height is None else title_height
    resolved_title_gap = self._title_gap if title_gap is None else title_gap
    return (resolved_title_height + resolved_title_gap) if section.title else 0

  def _section_band_height(self, section: TileSection, row_height: float) -> float:
    rows = section.grid.get_row_count(available_width=self._content_rect(self._rect).width if self._rect.width else None)
    if rows <= 0:
      return 0.0
    return (rows * row_height) + (section.grid.gap * max(0, rows - 1))

  def _content_rect(self, rect: rl.Rectangle) -> rl.Rectangle:
    content_x = rect.x + self._horizontal_padding
    content_w = max(0.0, rect.width - (self._horizontal_padding * 2))
    if self._max_content_width is not None and content_w > self._max_content_width:
      content_w = float(self._max_content_width)
      content_x = rect.x + (rect.width - content_w) / 2
    return rl.Rectangle(content_x, rect.y, content_w, rect.height)

  def _layout_profile(self, rect: rl.Rectangle, sections: list[TileSection]) -> tuple[int, int, int, float]:
    total_rows = sum(section.grid.get_row_count(available_width=rect.width) for section in sections)
    if total_rows <= 0:
      return self._title_height, self._title_gap, self._section_gap, 0.0

    total_internal_gaps = sum(section.grid.get_internal_gap_height(available_width=rect.width) for section in sections)
    title_height = self._title_height
    title_gap = self._title_gap
    section_gap = self._section_gap

    for compact_pass in range(2):
      total_title_height = sum(self._title_block_height(section, title_height, title_gap) for section in sections)
      total_section_gaps = section_gap * max(0, len(sections) - 1)
      fit_row_height = max(0.0, (rect.height - self._top_padding - total_title_height - total_section_gaps - total_internal_gaps) / total_rows)
      min_row_height = min(self._min_row_height, 124) if rect.width < 960 or compact_pass else self._min_row_height
      if fit_row_height >= min_row_height:
        return title_height, title_gap, section_gap, min(fit_row_height, self._max_row_height)
      title_height = max(24, min(title_height, 28))
      title_gap = max(4, min(title_gap, 6))
      section_gap = max(12, min(section_gap, 16))

    return title_height, title_gap, section_gap, fit_row_height

  def _draw_section_title(self, rect: rl.Rectangle, title: str):
    title_text = title
    spacing = round(self._title_font_size * 0.08)
    size = measure_text_cached(self._font_title, title_text, self._title_font_size, spacing=spacing)
    text_y = rect.y + (rect.height - size.y) / 2
    text_pos = rl.Vector2(round(rect.x), round(text_y))
    rl.draw_text_ex(self._font_title, title_text, text_pos, self._title_font_size, spacing, rl.Color(236, 242, 250, 215))

    line_x = rect.x + size.x + SPACING.lg
    line_w = rect.width - (line_x - rect.x)
    if line_w <= 0:
      return
    line_y = int(rect.y + rect.height / 2)
    rl.draw_rectangle(int(line_x), line_y, int(line_w), 2, rl.Color(255, 255, 255, 36))

  def _render(self, rect: rl.Rectangle):
    self.set_rect(rect)
    sections = [section for section in self._sections if section.grid.tiles]
    if not sections:
      return

    content_rect = self._content_rect(rect)
    title_height, title_gap, section_gap, row_height = self._layout_profile(content_rect, sections)
    if row_height <= 0:
      return

    self._content_height = self._content_height_for_layout(content_rect, sections, title_height, title_gap, section_gap, row_height)
    self._scroll_panel.set_enabled(self.is_visible)
    self._scroll_offset = self._scroll_panel.update(content_rect, max(self._content_height, content_rect.height)) if self._content_height > content_rect.height else 0.0

    rl.begin_scissor_mode(int(content_rect.x), int(content_rect.y), int(content_rect.width), int(content_rect.height))

    y = content_rect.y + self._top_padding + self._scroll_offset
    for index, section in enumerate(sections):
      if section.title:
        title_rect = rl.Rectangle(content_rect.x, y, content_rect.width, title_height)
        self._draw_section_title(title_rect, section.title)
        y += title_height + title_gap

      active_grid_height = (section.grid.get_row_count(available_width=content_rect.width) * row_height) + section.grid.get_internal_gap_height(available_width=content_rect.width)
      if hasattr(section.grid, "set_touch_valid_callback"):
        section.grid.set_touch_valid_callback(lambda: self._scroll_panel.is_touch_valid())
      section.grid.set_parent_rect(content_rect)
      section.grid.render(rl.Rectangle(content_rect.x, y, content_rect.width, active_grid_height))
      y += self._section_band_height(section, row_height)

      if index < len(sections) - 1:
        y += section_gap

    rl.end_scissor_mode()

    if self._content_height > content_rect.height:
      self._scrollbar.render(content_rect, self._content_height, self._scroll_offset)
