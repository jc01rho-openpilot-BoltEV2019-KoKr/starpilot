from openpilot.selfdrive.ui.lib.mode_banner import ModeBannerVariant, get_mode_banner_variant, mode_atom_color, mode_banner_color


class FakeParams:
  def __init__(self, bools=None, ints=None):
    self.bools = bools or {}
    self.ints = ints or {}

  def get_bool(self, key):
    return self.bools.get(key, False)

  def get_int(self, key, default=0):
    return self.ints.get(key, default)


def _rgb(color):
  return color.r, color.g, color.b


def test_mode_banner_variant_tracks_fixed_and_conditional_modes():
  assert get_mode_banner_variant(FakeParams()) == ModeBannerVariant.CHILL
  assert get_mode_banner_variant(FakeParams({"ExperimentalMode": True})) == ModeBannerVariant.EXPERIMENTAL
  assert get_mode_banner_variant(FakeParams({"ConditionalExperimental": True})) == ModeBannerVariant.CONDITIONAL_EXPERIMENTAL
  assert get_mode_banner_variant(FakeParams({"ConditionalChill": True})) == ModeBannerVariant.CONDITIONAL_CHILL
  assert get_mode_banner_variant(FakeParams({"SafeMode": True, "ConditionalExperimental": True})) == ModeBannerVariant.CHILL


def test_conditional_gradients_keep_full_major_and_partial_minor_colors():
  conditional_experimental = ModeBannerVariant.CONDITIONAL_EXPERIMENTAL
  assert _rgb(mode_banner_color(conditional_experimental, 0.0)) == (35, 149, 255)
  assert _rgb(mode_banner_color(conditional_experimental, 0.58)) == (20, 255, 171)
  assert _rgb(mode_banner_color(conditional_experimental, 0.80)) == (255, 138, 22)
  assert _rgb(mode_banner_color(conditional_experimental, 1.0)) == (231, 83, 30)

  conditional_chill = ModeBannerVariant.CONDITIONAL_CHILL
  assert _rgb(mode_banner_color(conditional_chill, 0.0)) == (255, 138, 22)
  assert _rgb(mode_banner_color(conditional_chill, 0.58)) == (219, 56, 34)
  assert _rgb(mode_banner_color(conditional_chill, 0.80)) == (35, 149, 255)
  assert _rgb(mode_banner_color(conditional_chill, 1.0)) == (25, 220, 199)


def test_atom_gradients_use_compact_icon_directions():
  assert _rgb(mode_atom_color(ModeBannerVariant.CHILL, 0.0)) == (35, 149, 255)
  assert _rgb(mode_atom_color(ModeBannerVariant.CHILL, 1.0)) == (20, 255, 171)
  assert _rgb(mode_atom_color(ModeBannerVariant.EXPERIMENTAL, 0.0)) == (255, 155, 63)
  assert _rgb(mode_atom_color(ModeBannerVariant.EXPERIMENTAL, 1.0)) == (219, 56, 34)

  for variant in (ModeBannerVariant.CONDITIONAL_EXPERIMENTAL, ModeBannerVariant.CONDITIONAL_CHILL):
    assert _rgb(mode_atom_color(variant, 0.0)) == _rgb(mode_banner_color(variant, 0.0))
    assert _rgb(mode_atom_color(variant, 1.0)) == _rgb(mode_banner_color(variant, 1.0))
