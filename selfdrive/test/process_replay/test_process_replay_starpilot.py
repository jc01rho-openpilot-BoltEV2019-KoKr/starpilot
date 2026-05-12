import os

os.environ["DEBUG"] = "0"

from openpilot.selfdrive.test.process_replay.process_replay import get_process_config


def test_plannerd_replay_includes_starpilot_inputs():
  cfg = get_process_config("plannerd")

  assert "starpilotPlan" in cfg.pubs
  assert "starpilotCarState" in cfg.pubs
