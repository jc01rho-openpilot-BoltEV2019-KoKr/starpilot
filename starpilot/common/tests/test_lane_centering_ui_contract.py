from pathlib import Path


_REPO_ROOT = Path(__file__).resolve().parents[3]

_GALAXY_PY = (_REPO_ROOT / "starpilot/system/the_galaxy/the_galaxy.py").read_text(encoding="utf-8")


def test_galaxy_troubleshoot_advanced_lateral_keys():
  start = _GALAXY_PY.find("_TROUBLESHOOT_ADVANCED_LATERAL_KEYS")
  assert start != -1
  end = _GALAXY_PY.find("]", start)
  block = _GALAXY_PY[start:end]
  assert '"LaneCentering"' in block
  assert '"LaneCenterOffset"' in block
