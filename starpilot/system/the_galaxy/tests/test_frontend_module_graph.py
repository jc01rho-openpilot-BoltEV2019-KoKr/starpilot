from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[4]
SETTINGS_PATH = REPO_ROOT / "starpilot/system/the_galaxy/assets/components/settings.js"
ROUTER_PATH = REPO_ROOT / "starpilot/system/the_galaxy/assets/components/router.js"
INDEX_PATH = REPO_ROOT / "starpilot/system/the_galaxy/templates/index.html"


def test_settings_does_not_create_a_second_router_module():
  source = SETTINGS_PATH.read_text(encoding="utf-8")

  assert "/assets/components/router.js" not in source
  assert "window.__theGalaxyNavigate" in source


def test_router_and_settings_cache_bust_is_consistent():
  router = ROUTER_PATH.read_text(encoding="utf-8")
  index = INDEX_PATH.read_text(encoding="utf-8")

  assert "/assets/components/settings.js?v=router-cycle-fix-1" in router
  assert "/assets/components/router.js?v=router-cycle-fix-1" in index
