from __future__ import annotations

from enum import IntEnum, IntFlag
from pathlib import Path
import tempfile

try:
  from openpilot.common.params_pyx import Params as _Params, ParamKeyFlag, ParamKeyType, UnknownKeyName
except Exception:
  class UnknownKeyName(KeyError):
    pass

  class ParamKeyFlag(IntFlag):
    PERSISTENT = 0x02
    CLEAR_ON_MANAGER_START = 0x04
    CLEAR_ON_ONROAD_TRANSITION = 0x08
    CLEAR_ON_OFFROAD_TRANSITION = 0x10
    DONT_LOG = 0x20
    DEVELOPMENT_ONLY = 0x40
    CLEAR_ON_IGNITION_ON = 0x80
    ALL = 0xFFFFFFFF

  class ParamKeyType(IntEnum):
    STRING = 0
    BOOL = 1
    INT = 2
    FLOAT = 3
    TIME = 4
    JSON = 5
    BYTES = 6

  def _load_key_types() -> dict[str, ParamKeyType]:
    key_types: dict[str, ParamKeyType] = {}
    params_keys = Path(__file__).with_name("params_keys.h")
    if not params_keys.exists():
      return key_types

    for line in params_keys.read_text(encoding="utf-8", errors="ignore").splitlines():
      if not line.lstrip().startswith('{"'):
        continue

      parts = line.split('"')
      if len(parts) < 2:
        continue

      key = parts[1]
      for type_name in ParamKeyType.__members__:
        if f", {type_name}" in line:
          key_types[key] = ParamKeyType[type_name]
          break
      else:
        key_types[key] = ParamKeyType.STRING

    return key_types

  _KEY_TYPES = _load_key_types()
  _PERSISTENT_STORE: dict[str, object] = {}
  _MEMORY_STORE: dict[str, object] = {}

  class Params:
    def __init__(self, d: str | None = None, memory: bool = False, return_defaults: bool = False):
      self.d = d if d is not None else ""
      self.m = memory
      self.return_defaults = return_defaults
      self._store = _MEMORY_STORE if memory else _PERSISTENT_STORE

    def __reduce__(self):
      return type(self), (self.d, self.m, self.return_defaults)

    def clear_all(self, tx_flag=ParamKeyFlag.ALL):
      self._store.clear()

    def check_key(self, key):
      if isinstance(key, bytes):
        key = key.decode("utf-8")
      return str(key)

    def _coerce_bool(self, value) -> bool:
      if isinstance(value, bool):
        return value
      if isinstance(value, (int, float)):
        return bool(value)
      if isinstance(value, bytes):
        return value == b"1"
      if isinstance(value, str):
        return value.strip().lower() not in ("", "0", "false", "none", "null")
      return bool(value)

    def _coerce_value(self, key: str, value):
      value_type = self.get_type(key)
      if value_type == ParamKeyType.BOOL:
        return self._coerce_bool(value)
      if value_type == ParamKeyType.INT:
        return int(float(value))
      if value_type == ParamKeyType.FLOAT:
        return float(value)
      if value_type == ParamKeyType.BYTES and isinstance(value, str):
        return value.encode("utf-8")
      return value

    def get(self, key, block: bool = False, return_default: bool = False, encoding=None, default=None):
      key = self.check_key(key)
      value = self._store.get(key, default)
      if value is None:
        return default
      if encoding is not None and isinstance(value, bytes):
        try:
          return value.decode(encoding)
        except Exception:
          return value.decode("utf-8", errors="replace")
      return value

    def get_bool(self, key, block: bool = False, default: bool = False):
      value = self.get(key, block=block, return_default=True, default=default)
      return self._coerce_bool(value)

    def get_int(self, key, block: bool = False, return_default: bool = False, default: int = 0):
      value = self.get(key, block=block, return_default=return_default, encoding="utf-8", default=default)
      if value is None or value == "":
        return default
      try:
        return int(float(value))
      except (TypeError, ValueError):
        return default

    def get_float(self, key, block: bool = False, return_default: bool = False, default: float = 0.0):
      value = self.get(key, block=block, return_default=return_default, encoding="utf-8", default=default)
      if value is None or value == "":
        return default
      try:
        return float(value)
      except (TypeError, ValueError):
        return default

    def put(self, key, dat):
      key = self.check_key(key)
      self._store[key] = self._coerce_value(key, dat)

    def put_bool(self, key, val: bool):
      self.put(key, bool(val))

    def put_nonblocking(self, key, dat):
      self.put(key, dat)

    def put_bool_nonblocking(self, key, val: bool):
      self.put_bool(key, val)

    def put_int(self, key, val):
      self.put(key, int(val))

    def put_float(self, key, val):
      self.put(key, float(val))

    def remove(self, key):
      self._store.pop(self.check_key(key), None)

    def get_param_path(self, key: str = ""):
      base = Path(tempfile.gettempdir()) / ("params_memory" if self.m else "params")
      base.mkdir(parents=True, exist_ok=True)
      return str(base / key) if key else str(base)

    def get_type(self, key):
      return _KEY_TYPES.get(self.check_key(key), ParamKeyType.STRING)

    def all_keys(self):
      return list(_KEY_TYPES)

    def get_default_value(self, key):
      return None

    def cpp2python(self, key, value):
      return self._coerce_value(self.check_key(key), value)

    def get_key_flag(self, key):
      return ParamKeyFlag.PERSISTENT

    def get_stock_value(self, key):
      return None

    def get_tuning_level(self, key):
      return 0

else:
  assert _Params
  assert ParamKeyFlag
  assert ParamKeyType
  assert UnknownKeyName

  class Params(_Params):
    def get(self, key, block=False, return_default=False, encoding=None, default=None):
      try:
        value = super().get(key, block=block, return_default=return_default)
      except UnknownKeyName:
        return default
      if value is None:
        return default
      if encoding is not None and isinstance(value, bytes):
        try:
          return value.decode(encoding)
        except Exception:
          return value.decode("utf-8", errors="replace")
      return value

    def get_bool(self, key, block=False, default=False):
      try:
        result = super().get(key, block=block, return_default=True)
        if result is None:
          return bool(default)
        return bool(result)
      except UnknownKeyName:
        return bool(default)

    def get_int(self, key, block=False, return_default=False, default=0):
      val = self.get(key, block=block, return_default=return_default, encoding="utf-8")
      if val is None or val == "":
        return default
      try:
        return int(float(val))
      except ValueError:
        return default

    def get_float(self, key, block=False, return_default=False, default=0.0):
      val = self.get(key, block=block, return_default=return_default, encoding="utf-8")
      if val is None or val == "":
        return default
      try:
        return float(val)
      except ValueError:
        return default

    def put_int(self, key, val):
      t = self.get_type(key)
      if t == ParamKeyType.FLOAT:
        self.put(key, float(val))
      elif t == ParamKeyType.INT:
        self.put(key, int(val))
      elif t == ParamKeyType.BOOL:
        self.put(key, bool(val))
      else:
        self.put(key, str(int(val)))

    def put_float(self, key, val):
      t = self.get_type(key)
      if t == ParamKeyType.FLOAT:
        self.put(key, float(val))
      elif t == ParamKeyType.INT:
        self.put(key, int(val))
      elif t == ParamKeyType.BOOL:
        self.put(key, bool(val))
      else:
        self.put(key, str(float(val)))


if __name__ == "__main__":
  import sys

  params = Params()
  key = sys.argv[1]
  assert params.check_key(key), f"unknown param: {key}"

  if len(sys.argv) == 3:
    val = sys.argv[2]
    print(f"SET: {key} = {val}")
    params.put(key, val)
  elif len(sys.argv) == 2:
    print(f"GET: {key} = {params.get(key)}")
