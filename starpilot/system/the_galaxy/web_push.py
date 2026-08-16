"""Small synchronous Web Push sender for the device Galaxy runtime.

The desktop dependency, pywebpush, also imports aiohttp even when only its
synchronous sender is used. The device Galaxy runtime does not ship aiohttp,
so keep the synchronous path independent of that optional dependency.
"""

from __future__ import annotations

import base64
import os
import time
from collections.abc import Mapping
from urllib.parse import urlparse

import http_ece
import requests
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import ec
from py_vapid import Vapid, Vapid01


class WebPushException(Exception):
  def __init__(self, message: str, response=None) -> None:
    super().__init__(message)
    self.response = response


def _decode_urlsafe_base64(value: str) -> bytes:
  encoded = value.encode("ascii")
  return base64.urlsafe_b64decode(encoded + b"=" * (-len(encoded) % 4))


def _vapid_key(value) -> Vapid01:
  if isinstance(value, Vapid01):
    return value
  if isinstance(value, str):
    if os.path.isfile(value):
      return Vapid.from_file(private_key_file=value)
    return Vapid.from_string(private_key=value)
  raise WebPushException("VAPID private key is missing")


def webpush(
  subscription_info: Mapping,
  data: str | bytes | None = None,
  vapid_private_key=None,
  vapid_claims: Mapping | None = None,
  content_encoding: str = "aes128gcm",
  ttl: int = 0,
  timeout: float | None = None,
  headers: Mapping | None = None,
):
  """Encrypt and synchronously publish one browser push notification."""
  endpoint = str(subscription_info.get("endpoint") or "")
  keys = subscription_info.get("keys")
  if not endpoint or not isinstance(keys, Mapping):
    raise WebPushException("Push subscription is missing its endpoint or keys")

  receiver_key = _decode_urlsafe_base64(str(keys.get("p256dh") or ""))
  auth_secret = _decode_urlsafe_base64(str(keys.get("auth") or ""))
  if len(receiver_key) != 65 or not receiver_key.startswith(b"\x04") or not auth_secret:
    raise WebPushException("Push subscription contains invalid encryption keys")

  request_headers = {str(key): str(value) for key, value in (headers or {}).items()}
  claims = dict(vapid_claims or {})
  if claims:
    if not claims.get("aud"):
      parsed_endpoint = urlparse(endpoint)
      claims["aud"] = f"{parsed_endpoint.scheme}://{parsed_endpoint.netloc}"
    if not claims.get("exp") or int(claims["exp"]) < int(time.time()):
      claims["exp"] = int(time.time()) + 12 * 60 * 60
    request_headers.update({str(key): str(value) for key, value in _vapid_key(vapid_private_key).sign(claims).items()})

  payload = b"" if data is None else data.encode("utf-8") if isinstance(data, str) else data
  sender_key = ec.generate_private_key(ec.SECP256R1(), default_backend())
  encrypted = http_ece.encrypt(
    payload,
    private_key=sender_key,
    dh=receiver_key,
    auth_secret=auth_secret,
    version=content_encoding,
  )
  request_headers.update({
    "Content-Encoding": content_encoding,
    "TTL": str(ttl),
  })

  response = requests.post(endpoint, data=encrypted, headers=request_headers, timeout=timeout or 10)
  if response.status_code > 202:
    raise WebPushException(
      f"Push failed: {response.status_code} {response.reason}\nResponse body:{response.text}",
      response=response,
    )
  return response
