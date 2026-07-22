from openpilot.starpilot.common import connect_server as cs
from openpilot.starpilot.common import starpilot_functions as sf


class FakeParams:
  def __init__(self, values=None):
    self.values = dict(values or {})

  def get(self, key):
    return self.values.get(key)

  def get_bool(self, key):
    return self.values.get(key) in (True, 1, "1", b"1")

  def put(self, key, value):
    self.values[key] = value

  def put_bool(self, key, value):
    self.values[key] = b"1" if value else b"0"

  def remove(self, key):
    self.values.pop(key, None)


class FakeThreadManager:
  def is_thread_alive(self, name):
    return False


def test_automatic_update_requests_guarded_reboot(monkeypatch):
  params = FakeParams({
    "UpdaterState": "idle",
    "UpdaterFetchAvailable": True,
    "UpdateAvailable": False,
    "IsOnroad": False,
  })
  state_reads = 0
  update_checks = 0

  def get(key):
    nonlocal state_reads
    if key == "UpdaterState" and params.values[key] == "checking...":
      state_reads += 1
      if state_reads % 2 == 0:
        params.values[key] = "idle"
    return params.values.get(key)

  def run_cmd(command, *args, **kwargs):
    nonlocal update_checks
    if "-SIGUSR1" in command:
      update_checks += 1
      params.values["UpdaterState"] = "checking..."
      params.values["UpdaterFetchAvailable"] = update_checks == 1
    elif "-SIGHUP" in command:
      params.values["UpdateAvailable"] = True

  params.get = get
  monkeypatch.setattr(sf, "run_cmd", run_cmd)
  monkeypatch.setattr(sf.HARDWARE, "reboot", lambda: (_ for _ in ()).throw(AssertionError("direct reboot called")))

  sf.update_openpilot(FakeThreadManager(), params)

  assert params.get("DoReboot") == b"1"


def test_sync_konik_dongle_id_preserves_stock_id_before_switching(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "use_konik_server", lambda: True)
  monkeypatch.setattr(cs, "register", lambda **kwargs: "konik-dongle")

  params = FakeParams({"DongleId": "stock-dongle"})

  cs.sync_konik_dongle_id(params)

  assert params.get("StockDongleId") == "stock-dongle"
  assert params.get("KonikDongleId") == "konik-dongle"
  assert params.get("DongleId") == "konik-dongle"


def test_sync_konik_dongle_id_restores_stock_id_from_persist(monkeypatch, tmp_path):
  persist_root = tmp_path / "persist"
  persisted_dongle_id_path = persist_root / "comma" / "dongle_id"
  persisted_dongle_id_path.parent.mkdir(parents=True, exist_ok=True)
  persisted_dongle_id_path.write_text("stock-dongle")

  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(persist_root)))
  monkeypatch.setattr(cs, "use_konik_server", lambda: False)

  params = FakeParams({
    "DongleId": "konik-dongle",
    "KonikDongleId": "konik-dongle",
  })

  cs.sync_konik_dongle_id(params)

  assert params.get("StockDongleId") == "stock-dongle"
  assert params.get("DongleId") == "stock-dongle"


def test_sync_konik_dongle_id_skips_missing_stock_backup(monkeypatch, tmp_path):
  monkeypatch.setattr(cs.Paths, "persist_root", staticmethod(lambda: str(tmp_path)))
  monkeypatch.setattr(cs, "use_konik_server", lambda: False)

  params = FakeParams({
    "DongleId": "konik-dongle",
    "KonikDongleId": "konik-dongle",
  })

  cs.sync_konik_dongle_id(params)

  assert params.get("DongleId") == "konik-dongle"
  assert params.get("StockDongleId") is None


def test_prepare_konik_server_switch_clears_cached_konik_id():
  params = FakeParams({"KonikDongleId": "konik-dongle"})
  params_cache = FakeParams({"KonikDongleId": "konik-dongle"})

  cs.prepare_konik_server_switch(True, params, params_cache)

  assert params.get("UseKonikServer") == b"1"
  assert params.get("KonikDongleId") is None
  assert params_cache.get("KonikDongleId") is None


def test_prepare_konik_server_switch_clears_cached_stock_id():
  params = FakeParams({"DongleId": "konik-dongle"})
  params_cache = FakeParams({"DongleId": "konik-dongle"})

  cs.prepare_konik_server_switch(False, params, params_cache)

  assert params.get("UseKonikServer") == b"0"
  assert params.get("DongleId") is None
  assert params_cache.get("DongleId") is None
