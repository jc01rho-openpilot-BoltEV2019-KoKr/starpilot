#!/bin/sh
""":"
REPO_ROOT="$(CDPATH= cd -- "$(dirname "$0")/../.." && pwd)"
PYTHON_BIN="$REPO_ROOT/.venv/bin/python"

if [ -x "$PYTHON_BIN" ]; then
  exec "$PYTHON_BIN" "$0" "$@"
fi

exec python3 "$0" "$@"
":"""
"""
Usage::

  usage: auth.py [-h] [{google,apple,github,jwt}] [jwt]

  Login to your comma account

  positional arguments:
    {google,apple,github,jwt}
    jwt

  optional arguments:
    -h, --help            show this help message and exit


Examples::

  ./auth.py  # Log in with google account
  ./auth.py github  # Log in with GitHub Account
  ./auth.py jwt ey......hw  # Log in with a JWT from https://jwt.comma.ai, for use in CI
"""

import argparse
import os
import pprint
import sys
import webbrowser
from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
from typing import Any
from urllib.parse import parse_qs, urlencode

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from openpilot.common.params import Params
from openpilot.tools.lib.api import APIError, CommaApi, UnauthorizedError
from openpilot.tools.lib.auth_config import DEFAULT_API_HOST, KONIK_API_HOST, get_token, normalize_api_host, set_token


def _use_konik_server():
  try:
    return Params().get_bool("UseKonikServer")
  except Exception:
    return False


API_HOST = normalize_api_host(os.getenv('API_HOST', KONIK_API_HOST if _use_konik_server() else DEFAULT_API_HOST))
PORT = 3000


class ClientRedirectServer(HTTPServer):
  query_params: dict[str, Any] = {}


class ClientRedirectHandler(BaseHTTPRequestHandler):
  def do_GET(self):
    if not self.path.startswith('/auth'):
      self.send_response(204)
      return

    query = self.path.split('?', 1)[-1]
    query_parsed = parse_qs(query, keep_blank_values=True)
    self.server.query_params = query_parsed

    self.send_response(200)
    self.send_header('Content-type', 'text/plain')
    self.end_headers()
    self.wfile.write(b'Return to the CLI to continue')

  def log_message(self, *args):
    pass  # this prevent http server from dumping messages to stdout


def resolve_api_host(host: str) -> str:
  if host in ("comma", "commaai", "commadotai"):
    return DEFAULT_API_HOST
  if host == "konik":
    return KONIK_API_HOST
  return normalize_api_host(host)


def auth_redirect_api_host(api_host: str) -> str:
  return "https://api.comma.ai" if normalize_api_host(api_host) == DEFAULT_API_HOST else normalize_api_host(api_host)


def auth_redirect_link(method, api_host=API_HOST):
  provider_id = {
    'google': 'g',
    'apple': 'a',
    'github': 'h',
  }[method]

  params = {
    'redirect_uri': f"{auth_redirect_api_host(api_host)}/v2/auth/{provider_id}/redirect/",
    'state': f'service,localhost:{PORT}',
  }

  if method == 'google':
    params.update({
      'type': 'web_server',
      'client_id': '45471411055-ornt4svd2miog6dnopve7qtmh5mnu6id.apps.googleusercontent.com',
      'response_type': 'code',
      'scope': 'https://www.googleapis.com/auth/userinfo.email',
      'prompt': 'select_account',
    })
    return 'https://accounts.google.com/o/oauth2/auth?' + urlencode(params)
  elif method == 'github':
    params.update({
      'client_id': 'Ov23liy0AI1YCd15pypf' if normalize_api_host(api_host) == KONIK_API_HOST else '28c4ecb54bb7272cb5a4',
      'scope': 'read:user',
    })
    return 'https://github.com/login/oauth/authorize?' + urlencode(params)
  elif method == 'apple':
    params.update({
      'client_id': 'ai.comma.login',
      'response_type': 'code',
      'response_mode': 'form_post',
      'scope': 'name email',
    })
    return 'https://appleid.apple.com/auth/authorize?' + urlencode(params)
  else:
    raise NotImplementedError(f"no redirect implemented for method {method}")


def login(method, api_host=API_HOST):
  oauth_uri = auth_redirect_link(method, api_host)

  web_server = ClientRedirectServer(('localhost', PORT), ClientRedirectHandler)
  print(f'To sign in, use your browser and navigate to {oauth_uri}')
  webbrowser.open(oauth_uri, new=2)

  while True:
    web_server.handle_request()
    if 'code' in web_server.query_params:
      break
    elif 'error' in web_server.query_params:
      print('Authentication Error: "{}". Description: "{}" '.format(
        web_server.query_params['error'],
        web_server.query_params.get('error_description')), file=sys.stderr)
      break

  try:
    auth_resp = CommaApi(host=api_host).post('v2/auth/', data={'code': web_server.query_params['code'], 'provider': web_server.query_params['provider']})
    return auth_resp['access_token']
  except APIError as e:
    print(f'Authentication Error: {e}', file=sys.stderr)
    return None


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Login to your comma account')
  parser.add_argument('--host', default=API_HOST, help='API host to authenticate with: comma, konik, or a URL')
  parser.add_argument('method', default='google', const='google', nargs='?', choices=['google', 'apple', 'github', 'jwt'])
  parser.add_argument('jwt', nargs='?')

  args = parser.parse_args()
  api_host = resolve_api_host(args.host)
  if args.method == 'jwt':
    if args.jwt is None:
      print("method JWT selected, but no JWT was provided")
      exit(1)

    token = args.jwt
  else:
    token = login(args.method, api_host)
    if token is None:
      exit(1)

  try:
    me = CommaApi(token=token, host=api_host).get('/v1/me')
    set_token(token, api_host)
    print("Authenticated!")
    pprint.pprint(me)
  except UnauthorizedError:
    print("Got invalid JWT")
    exit(1)
