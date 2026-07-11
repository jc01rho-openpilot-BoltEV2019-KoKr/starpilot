from pathlib import Path

from openpilot.common.params import Params
from openpilot.system.athena.registration import register
from openpilot.system.hardware.hw import Paths

from openpilot.starpilot.common.starpilot_utilities import use_konik_server


def _cache_params_path() -> str:
  return Paths.params_cache_root()


def _normalize_dongle_id(value):
  if isinstance(value, bytes):
    value = value.decode("utf-8", errors="ignore")
  if value is None:
    return None
  value = str(value).strip()
  return value or None


def _read_persisted_stock_dongle_id():
  persisted_dongle_id_path = Path(Paths.persist_root()) / "comma" / "dongle_id"
  if not persisted_dongle_id_path.is_file():
    return None
  return _normalize_dongle_id(persisted_dongle_id_path.read_text())


def _remove_param_from_live_and_cache(key, params, params_cache=None):
  if params_cache is None:
    params_cache = Params(_cache_params_path())
  params.remove(key)
  params_cache.remove(key)


def prepare_konik_server_switch(use_konik, params, params_cache=None):
  params.put_bool("UseKonikServer", use_konik)
  if use_konik:
    _remove_param_from_live_and_cache("KonikDongleId", params, params_cache)
  else:
    _remove_param_from_live_and_cache("DongleId", params, params_cache)


def _ensure_stock_dongle_id(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  konik_dongle_id = _normalize_dongle_id(params.get("KonikDongleId"))
  stock_dongle_id = _normalize_dongle_id(params.get("StockDongleId"))

  if stock_dongle_id not in (None, konik_dongle_id):
    return stock_dongle_id

  candidate = _read_persisted_stock_dongle_id()
  if candidate in (None, konik_dongle_id):
    candidate = current_dongle_id if current_dongle_id != konik_dongle_id else None

  if candidate is not None and candidate != stock_dongle_id:
    params.put("StockDongleId", candidate)

  return candidate


def sync_konik_dongle_id(params):
  current_dongle_id = _normalize_dongle_id(params.get("DongleId"))
  konik_dongle_id = _normalize_dongle_id(params.get("KonikDongleId"))
  stock_dongle_id = _ensure_stock_dongle_id(params)

  if use_konik_server():
    if konik_dongle_id is None:
      konik_dongle_id = _normalize_dongle_id(register(show_spinner=True, register_konik=True))
      if konik_dongle_id is not None:
        params.put("KonikDongleId", konik_dongle_id)
    if konik_dongle_id is not None and current_dongle_id != konik_dongle_id:
      params.put("DongleId", konik_dongle_id)
  elif current_dongle_id == konik_dongle_id and stock_dongle_id is not None:
    params.put("DongleId", stock_dongle_id)
