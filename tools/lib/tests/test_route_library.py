from collections import namedtuple

import pytest

from openpilot.tools.lib.api import APIError, UnauthorizedError
from openpilot.tools.lib.auth_config import DEFAULT_API_HOST, KONIK_API_HOST
from openpilot.tools.lib.route import Route, SegmentName

class TestRouteLibrary:
  def test_segment_name_formats(self):
    Case = namedtuple('Case', ['input', 'expected_route', 'expected_segment_num', 'expected_data_dir'])

    cases = [ Case("a2a0ccea32023010|2023-07-27--13-01-19", "a2a0ccea32023010|2023-07-27--13-01-19", -1, None),
              Case("a2a0ccea32023010/2023-07-27--13-01-19--1", "a2a0ccea32023010|2023-07-27--13-01-19", 1, None),
              Case("a2a0ccea32023010|2023-07-27--13-01-19/2", "a2a0ccea32023010|2023-07-27--13-01-19", 2, None),
              Case("a2a0ccea32023010/2023-07-27--13-01-19/3", "a2a0ccea32023010|2023-07-27--13-01-19", 3, None),
              Case("/data/media/0/realdata/a2a0ccea32023010|2023-07-27--13-01-19", "a2a0ccea32023010|2023-07-27--13-01-19", -1, "/data/media/0/realdata"),
              Case("/data/media/0/realdata/a2a0ccea32023010|2023-07-27--13-01-19--1", "a2a0ccea32023010|2023-07-27--13-01-19", 1, "/data/media/0/realdata"),
              Case("/data/media/0/realdata/a2a0ccea32023010|2023-07-27--13-01-19/2", "a2a0ccea32023010|2023-07-27--13-01-19", 2, "/data/media/0/realdata") ]

    def _validate(case):
      route_or_segment_name = case.input

      s = SegmentName(route_or_segment_name, allow_route_name=True)

      assert str(s.route_name) == case.expected_route
      assert s.segment_num == case.expected_segment_num
      assert s.data_dir == case.expected_data_dir

    for case in cases:
      _validate(case)

  def test_route_falls_back_to_konik_when_comma_route_missing(self, mocker):
    route_name = "59679e5e40b60ce0/0000091b--316e931f07"
    file_url = "https://konik.example/59679e5e40b60ce0/0000091b--316e931f07/0/qlog.zst"
    calls = []

    class FakeApi:
      def __init__(self, token=None, host=None):
        self.host = host

      def get(self, endpoint):
        calls.append((self.host, endpoint))
        if self.host == DEFAULT_API_HOST:
          raise APIError("404:not found", 404)
        if endpoint.endswith("/files"):
          return {"qlogs": [file_url]}
        return {"url": "https://connect.konik.ai/59679e5e40b60ce0/0000091b--316e931f07"}

    mocker.patch("openpilot.tools.lib.route.route_api_hosts", return_value=[DEFAULT_API_HOST, KONIK_API_HOST])
    mocker.patch("openpilot.tools.lib.route.get_token", return_value=None)
    mocker.patch("openpilot.tools.lib.route.CommaApi", FakeApi)

    route = Route(route_name)

    assert route.qlog_paths() == [file_url]
    assert calls[0] == (DEFAULT_API_HOST, f"v1/route/{route_name.replace('/', '|')}/files")
    assert calls[1] == (KONIK_API_HOST, f"v1/route/{route_name.replace('/', '|')}/files")
    assert calls[2] == (KONIK_API_HOST, f"v1/route/{route_name.replace('/', '|')}")

  def test_route_does_not_fall_back_to_konik_when_comma_unauthorized(self, mocker):
    route_name = "59679e5e40b60ce0/0000091b--316e931f07"
    calls = []

    class FakeApi:
      def __init__(self, token=None, host=None):
        self.host = host

      def get(self, endpoint):
        calls.append((self.host, endpoint))
        raise UnauthorizedError("unauthorized", 401)

    mocker.patch("openpilot.tools.lib.route.route_api_hosts", return_value=[DEFAULT_API_HOST, KONIK_API_HOST])
    mocker.patch("openpilot.tools.lib.route.get_token", return_value=None)
    mocker.patch("openpilot.tools.lib.route.CommaApi", FakeApi)

    with pytest.raises(UnauthorizedError):
      Route(route_name)

    assert calls == [(DEFAULT_API_HOST, f"v1/route/{route_name.replace('/', '|')}/files")]
