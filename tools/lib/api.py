import os
import requests

from openpilot.common.params import Params
from openpilot.tools.lib.auth_config import DEFAULT_API_HOST, KONIK_API_HOST, normalize_api_host


def _use_konik_server():
  try:
    return Params().get_bool("UseKonikServer")
  except Exception:
    return False


API_HOST = normalize_api_host(os.getenv('API_HOST', KONIK_API_HOST if _use_konik_server() else DEFAULT_API_HOST))


def route_api_hosts() -> list[str]:
  if os.getenv("API_HOST"):
    return [API_HOST]
  return [DEFAULT_API_HOST, KONIK_API_HOST]

# TODO: this should be merged into common.api

class CommaApi:
  def __init__(self, token=None, host: str | None = None):
    self.host = normalize_api_host(host or API_HOST)
    self.session = requests.Session()
    self.session.headers['User-agent'] = 'OpenpilotTools'
    if token:
      self.session.headers['Authorization'] = 'JWT ' + token

  def request(self, method, endpoint, **kwargs):
    with self.session.request(method, self.host + '/' + endpoint.lstrip('/'), **kwargs) as resp:
      try:
        resp_json = resp.json()
      except ValueError:
        resp_json = None

      if resp.status_code in [401, 403]:
        raise UnauthorizedError('Unauthorized. Authenticate with tools/lib/auth.py', resp.status_code)

      if resp.status_code >= 400:
        description = resp.text.strip() if resp.text else resp.reason
        raise APIError(f"{resp.status_code}:{description}", resp.status_code)

      if isinstance(resp_json, dict) and resp_json.get('error'):
        raise APIError(str(resp.status_code) + ":" + resp_json.get('description', str(resp_json['error'])), resp.status_code)
      return resp_json

  def get(self, endpoint, **kwargs):
    return self.request('GET', endpoint, **kwargs)

  def post(self, endpoint, **kwargs):
    return self.request('POST', endpoint, **kwargs)

class APIError(Exception):
  def __init__(self, message, status_code=None):
    super().__init__(message)
    self.status_code = status_code

class UnauthorizedError(APIError):
  def __init__(self, message, status_code=None):
    super().__init__(message, status_code)
