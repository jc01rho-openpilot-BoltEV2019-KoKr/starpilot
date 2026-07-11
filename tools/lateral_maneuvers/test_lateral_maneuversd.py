from openpilot.tools.lateral_maneuvers import lateral_maneuversd


class FakeParams:
  def __init__(self):
    self.writes = []

  def put_nonblocking(self, key, value):
    self.writes.append((key, value))


def test_save_status_writes_json_param_as_dict():
  params = FakeParams()

  saved = lateral_maneuversd._save_status(params, {
    "state": "setup",
    "history": ["", "Armed"],
  })

  assert params.writes == [(lateral_maneuversd.STATUS_PARAM, saved)]
  assert isinstance(params.writes[0][1], dict)
  assert saved["history"] == ["Armed"]
