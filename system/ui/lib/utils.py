import pyray as rl


_draw_circle_gradient_vector_api: bool | None = None


def draw_circle_gradient_compat(center_x: float, center_y: float, radius: float,
                                inner: rl.Color, outer: rl.Color) -> None:
  """Draw a circle gradient with either the Raylib 5 or Raylib 6 Python API."""
  global _draw_circle_gradient_vector_api

  if _draw_circle_gradient_vector_api is True:
    rl.draw_circle_gradient(rl.Vector2(center_x, center_y), radius, inner, outer)
    return
  if _draw_circle_gradient_vector_api is False:
    rl.draw_circle_gradient(int(center_x), int(center_y), radius, inner, outer)
    return

  # Raylib 6 changed DrawCircleGradient from (x, y, radius, colors) to
  # (Vector2, radius, colors). StarPilot supports devices on both bindings.
  try:
    rl.draw_circle_gradient(rl.Vector2(center_x, center_y), radius, inner, outer)
  except (RuntimeError, TypeError):
    rl.draw_circle_gradient(int(center_x), int(center_y), radius, inner, outer)
    _draw_circle_gradient_vector_api = False
  else:
    _draw_circle_gradient_vector_api = True


class GuiStyleContext:
  def __init__(self, styles: list[tuple[int, int, int]]):
    """styles is a list of tuples (control, prop, new_value)"""
    self.styles = styles
    self.prev_styles: list[tuple[int, int, int]] = []

  def __enter__(self):
    for control, prop, new_value in self.styles:
      prev_value = rl.gui_get_style(control, prop)
      self.prev_styles.append((control, prop, prev_value))
      rl.gui_set_style(control, prop, new_value)

  def __exit__(self, exc_type, exc_value, traceback):
    for control, prop, prev_value in self.prev_styles:
      rl.gui_set_style(control, prop, prev_value)
