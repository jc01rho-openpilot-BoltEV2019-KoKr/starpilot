import http.client
import json
import threading

import pytest

from openpilot.common.params import Params
from openpilot.starpilot.power import discord_report as report
from openpilot.starpilot.ui.feature_settings_state import FeatureSettingsRequest
from openpilot.starpilot.ui.power_owner import DISCORD, PowerOwner, confirm_question

WEBHOOK = "https://discord.com/api/webhooks/123/token-secret"


@pytest.fixture
def params(tmp_path):
  store = Params(str(tmp_path))
  store.put("GithubUsername", "jc01rho", block=True)
  store.put("GithubSshKeys", "ssh-ed25519 AAAA", block=True)
  return store


def test_power_owner_row_is_owner_only_and_needs_a_webhook(params, tmp_path):
  owner = PowerOwner(params, lambda: True)
  row = next(row for row in owner.snapshot().rows if row.key == DISCORD)
  assert row.value == "Off" and not row.available
  report.configure_webhook(params, WEBHOOK)
  params.put_bool(report.REPORT_KEY, False, block=True)
  row = next(row for row in owner.snapshot().rows if row.key == DISCORD)
  assert row.available and row.value == "Off"
  stale = FeatureSettingsRequest(DISCORD, b"1", "On", confirmation=True)
  assert not owner.apply(stale)
  request = FeatureSettingsRequest(DISCORD, row.source, "On", confirmation=True)
  assert "Discord" in confirm_question(request)
  assert owner.apply(request) and params.get_bool(report.REPORT_KEY)
  other = Params(str(tmp_path / "other"))
  assert all(row.key != DISCORD for row in PowerOwner(other, lambda: True).snapshot().rows)


@pytest.fixture
def api(tmp_path, params):
  from openpilot.starpilot.galaxy.access import GalaxyAccessOwner
  from openpilot.starpilot.galaxy.server import make_server
  access = GalaxyAccessOwner(tmp_path / "access")
  assert access.configure("password123", lambda: True)
  server = make_server(port=0, owner=access, parked=lambda: True, discord_report_params=params)
  worker = threading.Thread(target=server.serve_forever, kwargs={"poll_interval": 0.01}, daemon=True)
  worker.start()

  def request(method, path, body=None, *, cookie=""):
    conn = http.client.HTTPConnection("127.0.0.1", server.server_port, timeout=3)
    headers = {"Cookie": cookie}
    if method != "GET":
      headers.update({"Origin": f"http://127.0.0.1:{server.server_port}", "Content-Type": "application/json"})
    try:
      conn.request(method, path, body=None if body is None else json.dumps(body), headers=headers)
      response = conn.getresponse()
      raw = response.read()
      return response.status, json.loads(raw), raw
    finally:
      conn.close()

  conn = http.client.HTTPConnection("127.0.0.1", server.server_port, timeout=3)
  conn.request("POST", "/api/auth/login", body=json.dumps({"password": "password123"}),
               headers={"Content-Type": "application/json", "Origin": f"http://127.0.0.1:{server.server_port}"})
  response = conn.getresponse()
  response.read()
  cookie = response.getheader("Set-Cookie").split(";", 1)[0]
  conn.close()
  yield request, cookie
  server.shutdown()
  worker.join(timeout=2)
  server.server_close()


def test_galaxy_route_requires_session_and_never_returns_the_webhook(api, params):
  request, cookie = api
  assert request("GET", "/api/settings/discord-report")[0] == 401
  assert request("POST", "/api/settings/discord-report", {"action": "remove"})[0] == 401
  code, status, _ = request("GET", "/api/settings/discord-report", cookie=cookie)
  assert code == 200 and status == {"owner": True, "configured": False, "enabled": False}
  assert request("POST", "/api/settings/discord-report", {"action": "save", "webhook": "https://evil.example/x"}, cookie=cookie)[0] == 409
  assert request("POST", "/api/settings/discord-report", {"action": "save"}, cookie=cookie)[0] == 400
  code, status, raw = request("POST", "/api/settings/discord-report", {"action": "save", "webhook": WEBHOOK}, cookie=cookie)
  assert code == 200 and status == {"owner": True, "configured": True, "enabled": True}
  assert b"token-secret" not in raw and b"token-secret" not in request("GET", "/api/settings/discord-report", cookie=cookie)[2]
  code, status, _ = request("POST", "/api/settings/discord-report", {"action": "remove"}, cookie=cookie)
  assert code == 200 and status["configured"] is False and params.get(report.WEBHOOK_KEY) is None
  params.put("GithubUsername", "someone", block=True)
  assert request("POST", "/api/settings/discord-report", {"action": "save", "webhook": WEBHOOK}, cookie=cookie)[0] == 403
  assert params.get(report.WEBHOOK_KEY) is None
