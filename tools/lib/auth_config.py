import json
import os
from urllib.parse import urlparse, urlunparse

from openpilot.system.hardware.hw import Paths


class MissingAuthConfigError(Exception):
  pass


DEFAULT_API_HOST = "https://api.commadotai.com"
KONIK_API_HOST = "https://api.konik.ai"
COMMA_API_HOST_ALIASES = {"https://api.comma.ai", DEFAULT_API_HOST}


def normalize_api_host(host: str | None) -> str:
  if not host:
    host = DEFAULT_API_HOST

  parsed = urlparse(host)
  if not parsed.scheme:
    parsed = urlparse(f"https://{host}")

  normalized = urlunparse((parsed.scheme.lower(), parsed.netloc.lower(), "", "", "", "")).rstrip("/")
  if normalized in COMMA_API_HOST_ALIASES:
    return DEFAULT_API_HOST
  return normalized


def _auth_path() -> str:
  return os.path.join(Paths.config_root(), 'auth.json')


def _read_auth() -> dict:
  try:
    with open(_auth_path()) as f:
      return json.load(f)
  except Exception:
    return {}


def get_token(host: str | None = None):
  auth = _read_auth()
  if not auth:
    return None

  if host is not None:
    normalized_host = normalize_api_host(host)
    token = auth.get('tokens', {}).get(normalized_host)
    if token is not None:
      return token

    env_host = normalize_api_host(os.getenv("API_HOST", DEFAULT_API_HOST))
    if normalized_host == DEFAULT_API_HOST or normalized_host == env_host:
      return auth.get('access_token')
    return None

  return auth.get('access_token')


def set_token(token, host: str | None = None):
  normalized_host = normalize_api_host(host or os.getenv("API_HOST", DEFAULT_API_HOST))
  auth = _read_auth()
  tokens = auth.setdefault('tokens', {})
  tokens[normalized_host] = token

  # Preserve the legacy field for older tooling. Avoid replacing a comma token
  # when adding a Konik token unless this is an old-style hostless write.
  if host is None or normalized_host == DEFAULT_API_HOST or 'access_token' not in auth:
    auth['access_token'] = token

  os.makedirs(Paths.config_root(), exist_ok=True)
  with open(_auth_path(), 'w') as f:
    json.dump(auth, f)


def clear_token(host: str | None = None):
  if host is None:
    try:
      os.unlink(_auth_path())
    except FileNotFoundError:
      pass
    return

  auth = _read_auth()
  if not auth:
    return

  normalized_host = normalize_api_host(host)
  token = auth.get('tokens', {}).pop(normalized_host, None)
  if normalized_host == DEFAULT_API_HOST and auth.get('access_token') == token:
    auth.pop('access_token', None)

  with open(_auth_path(), 'w') as f:
    json.dump(auth, f)
