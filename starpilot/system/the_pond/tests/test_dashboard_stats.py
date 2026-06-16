import importlib.util
import json
import sys

from pathlib import Path
from types import ModuleType, SimpleNamespace


MODULE_DIR = Path(__file__).resolve().parents[1]
if str(MODULE_DIR) not in sys.path:
  sys.path.insert(0, str(MODULE_DIR))

loggerd_config = ModuleType("openpilot.system.loggerd.config")
loggerd_config.get_available_bytes = lambda default=0: default
loggerd_config.get_used_bytes = lambda default=0: default
sys.modules.setdefault("openpilot.system.loggerd.config", loggerd_config)

loggerd_deleter = ModuleType("openpilot.system.loggerd.deleter")
loggerd_deleter.PRESERVE_ATTR_NAME = "preserve"
loggerd_deleter.PRESERVE_ATTR_VALUE = b"1"
loggerd_deleter.PRESERVE_COUNT = 0
sys.modules.setdefault("openpilot.system.loggerd.deleter", loggerd_deleter)

loggerd_uploader = ModuleType("openpilot.system.loggerd.uploader")
loggerd_uploader.listdir_by_creation = lambda path: [
  entry.name for entry in sorted(Path(path).iterdir(), key=lambda entry: entry.stat().st_ctime)
]
sys.modules.setdefault("openpilot.system.loggerd.uploader", loggerd_uploader)

model_manager = ModuleType("openpilot.starpilot.assets.model_manager")
model_manager.canonical_model_key = lambda value: str(value or "").strip().lower().replace(" ", "-")
sys.modules.setdefault("openpilot.starpilot.assets.model_manager", model_manager)

starpilot_variables = ModuleType("openpilot.starpilot.common.starpilot_variables")
starpilot_variables.THEME_SAVE_PATH = Path("/tmp/dashboard-test-themes")
starpilot_variables.VIDEO_CACHE_PATH = Path("/tmp/dashboard-test-video-cache")
sys.modules.setdefault("openpilot.starpilot.common.starpilot_variables", starpilot_variables)

theme_manager = ModuleType("openpilot.starpilot.assets.theme_manager")
theme_manager.HOLIDAY_THEME_PATH = Path("/tmp/dashboard-test-holiday-themes")
sys.modules.setdefault("openpilot.starpilot.assets.theme_manager", theme_manager)

import utilities


def _simple_module(name, **attrs):
  module = ModuleType(name)
  for attr, value in attrs.items():
    setattr(module, attr, value)
  return module


def _install_server_import_stubs():
  cereal_module = _simple_module("cereal")
  car_module = _simple_module("cereal.car", CarParams=SimpleNamespace(from_bytes=lambda _: SimpleNamespace(__enter__=lambda self: self, __exit__=lambda *args: None)))
  custom_module = _simple_module("cereal.custom", StarPilotCarParams=object)
  log_module = _simple_module(
    "cereal.log",
    Event=object,
    DeviceState=SimpleNamespace(NetworkType=SimpleNamespace(none=0)),
    LiveDelayData=SimpleNamespace(Status=SimpleNamespace(estimated=1, unestimated=2, invalid=3)),
  )
  messaging_module = _simple_module(
    "cereal.messaging",
    SubMaster=lambda *args, **kwargs: {},
    PubMaster=lambda *args, **kwargs: SimpleNamespace(send=lambda *send_args, **send_kwargs: None),
    new_message=lambda *args, **kwargs: SimpleNamespace(),
    log_from_bytes=lambda *args, **kwargs: SimpleNamespace(liveDelay=SimpleNamespace(status=0)),
    sub_sock=lambda *args, **kwargs: None,
  )
  cereal_module.car = car_module
  cereal_module.custom = custom_module
  cereal_module.log = log_module
  cereal_module.messaging = messaging_module

  sys.modules["cereal"] = cereal_module
  sys.modules["cereal.car"] = car_module
  sys.modules["cereal.custom"] = custom_module
  sys.modules["cereal.log"] = log_module
  sys.modules["cereal.messaging"] = messaging_module

  sys.modules["opendbc.can.parser"] = _simple_module("opendbc.can.parser", CANParser=lambda *args, **kwargs: SimpleNamespace())
  sys.modules["opendbc.car.gm.values"] = _simple_module("opendbc.car.gm.values", GMFlags=SimpleNamespace(SASCM=SimpleNamespace(value=1)))
  sys.modules["opendbc.car.toyota.carcontroller"] = _simple_module("opendbc.car.toyota.carcontroller", LOCK_CMD=b"", UNLOCK_CMD=b"")
  sys.modules["opendbc.car.toyota.values"] = _simple_module(
    "opendbc.car.toyota.values",
    ToyotaStarPilotFlags=SimpleNamespace(SMART_DSU=SimpleNamespace(value=1), ZSS=SimpleNamespace(value=2)),
  )

  sys.modules["openpilot.common.realtime"] = _simple_module("openpilot.common.realtime", DT_HW=0.01)
  sys.modules["openpilot.common.time_helpers"] = _simple_module("openpilot.common.time_helpers", system_time_valid=lambda: True)
  sys.modules["openpilot.system.hardware"] = _simple_module(
    "openpilot.system.hardware",
    HARDWARE=SimpleNamespace(reboot=lambda: None, get_device_type=lambda: "pc", get_network_type=lambda: 1),
    PC=True,
  )
  sys.modules["openpilot.system.hardware.hw"] = _simple_module(
    "openpilot.system.hardware.hw",
    Paths=SimpleNamespace(log_root=lambda **kwargs: "/tmp/dashboard-test-routes/"),
  )
  sys.modules["openpilot.system.version"] = _simple_module("openpilot.system.version", get_build_metadata=lambda: SimpleNamespace())
  sys.modules["openpilot.tools.longitudinal_maneuvers.capabilities"] = _simple_module(
    "openpilot.tools.longitudinal_maneuvers.capabilities",
    get_longitudinal_maneuver_support=lambda *args, **kwargs: {},
  )
  sys.modules["panda"] = _simple_module("panda", Panda=lambda *args, **kwargs: SimpleNamespace(can_send=lambda *send_args, **send_kwargs: None))

  model_manager.is_builtin_model_key = lambda value: False
  model_manager.model_key_aliases = lambda value: [value]
  theme_manager.THEME_COMPONENT_PARAMS = {}

  sys.modules["openpilot.starpilot.common.accel_profile"] = _simple_module(
    "openpilot.starpilot.common.accel_profile",
    CUSTOM_ACCEL_PROFILE_INITIALIZED_KEY="CustomAccelProfileInitialized",
    CUSTOM_ACCEL_PROFILE_PARAM_KEYS=[],
    build_custom_accel_profile_defaults=lambda *args, **kwargs: {},
    custom_accel_profile_is_initialized=lambda *args, **kwargs: False,
    normalize_acceleration_profile=lambda value: value,
  )
  sys.modules["openpilot.starpilot.common.maps_catalog"] = _simple_module(
    "openpilot.starpilot.common.maps_catalog",
    MAPS_CATALOG=[],
    MAP_SCHEDULE_OPTIONS=[],
    get_selected_map_entries=lambda *args, **kwargs: [],
    sanitize_selected_locations_csv=lambda value: value,
    schedule_label=lambda value: value,
    schedule_param_value=lambda value: value,
  )
  sys.modules["openpilot.starpilot.common.model_versions"] = _simple_module(
    "openpilot.starpilot.common.model_versions",
    is_tinygrad_model_version=lambda *args, **kwargs: False,
    uses_combined_driving_artifacts=lambda *args, **kwargs: False,
    uses_split_off_policy_artifacts=lambda *args, **kwargs: False,
  )
  sys.modules["openpilot.starpilot.common.experimental_state"] = _simple_module(
    "openpilot.starpilot.common.experimental_state",
    sync_persist_chill_state=lambda *args, **kwargs: None,
    sync_persist_experimental_state=lambda *args, **kwargs: None,
  )
  sys.modules["openpilot.starpilot.common.favorite_slots"] = _simple_module(
    "openpilot.starpilot.common.favorite_slots",
    FAVORITE_SLOTS_PARAM="FavoriteSlots",
    normalize_favorite_slots=lambda *args, **kwargs: "",
  )
  sys.modules["openpilot.starpilot.common.starpilot_utilities"] = _simple_module(
    "openpilot.starpilot.common.starpilot_utilities",
    delete_file=lambda *args, **kwargs: None,
    get_lock_status=lambda *args, **kwargs: {},
    run_cmd=lambda *args, **kwargs: None,
  )
  for name, value in {
    "ACTIVE_THEME_PATH": Path("/tmp/dashboard-test-active-theme"),
    "ERROR_LOGS_PATH": "/tmp/dashboard-test-errors",
    "EXCLUDED_KEYS": set(),
    "LEGACY_STARPILOT_PARAM_RENAMES": {},
    "MAPS_PATH": Path("/tmp/dashboard-test-maps"),
    "MODELS_PATH": Path("/tmp/dashboard-test-models"),
    "RESOURCES_REPO": "resources",
    "SCREEN_RECORDINGS_PATH": Path("/tmp/dashboard-test-recordings"),
    "STOCK_THEME_PATH": Path("/tmp/dashboard-test-stock-theme"),
    "THEME_SAVE_PATH": Path("/tmp/dashboard-test-themes"),
  }.items():
    setattr(starpilot_variables, name, value)
  starpilot_variables.default_ev_tuning_enabled = lambda *args, **kwargs: False
  starpilot_variables.migrate_cancel_button_controls = lambda *args, **kwargs: False
  starpilot_variables.update_starpilot_toggles = lambda *args, **kwargs: None

  sys.modules["openpilot.starpilot.common.testing_grounds"] = _simple_module(
    "openpilot.starpilot.common.testing_grounds",
    DEFAULT_TESTING_GROUND_VARIANT="standard",
    TESTING_GROUND_VARIANT_LABELS={},
    TESTING_GROUND_VARIANTS=("standard",),
    TESTING_GROUNDS_SCHEMA_VERSION=1,
    TESTING_GROUNDS_SLOT_DEFINITIONS=(),
    TESTING_GROUNDS_STATE_PATH=Path("/tmp/dashboard-test-testing-grounds.json"),
  )
  sys.modules["openpilot.starpilot.navigation.destination_store"] = _simple_module(
    "openpilot.starpilot.navigation.destination_store",
    normalize_destination_payload=lambda payload: payload,
    update_recent_destinations=lambda *args, **kwargs: [],
  )
  sys.modules["openpilot.starpilot.system." + "the_" + "po" + "nd.factory_reset"] = _simple_module(
    "openpilot.starpilot.system." + "the_" + "po" + "nd.factory_reset",
    remove_path=lambda *args, **kwargs: None,
  )
  sys.modules["openpilot.starpilot.system." + "the_" + "po" + "nd.utilities"] = utilities


class FakeParams:
  def __init__(self, values=None):
    self.values = values or {}

  def get(self, key, encoding=None, default=None, block=False):
    del block
    value = self.values.get(key, default)
    if encoding and isinstance(value, bytes):
      return value.decode(encoding, errors="replace")
    return value

  def get_bool(self, key):
    value = self.values.get(key, False)
    if isinstance(value, bool):
      return value
    return str(value).strip().lower() in ("1", "true", "yes", "on")

  def put(self, key, value):
    self.values[key] = value


class FakeMessage:
  def __init__(self, kind, log_mono_time, payload):
    self._kind = kind
    self.logMonoTime = log_mono_time
    setattr(self, kind, payload)

  def which(self):
    return self._kind


def msg(kind, seconds, payload):
  return FakeMessage(kind, int(seconds * 1e9), payload)


def events(*names):
  return [SimpleNamespace(name=name) for name in names]


def test_route_metrics_count_selected_attention_events():
  route = {
    "name": "route-a",
    "segmentCount": 1,
    "startedAt": None,
  }
  messages = [
    msg("initData", 0, SimpleNamespace(params={"DrivingModelName": b"North Star"})),
    msg("carState", 0, SimpleNamespace(vEgo=10.0)),
    msg("selfdriveState", 0, SimpleNamespace(enabled=True)),
    msg("onroadEvents", 1, events("promptDriverDistracted")),
    msg("onroadEvents", 2, events("promptDriverDistracted")),
    msg("onroadEvents", 3, events()),
    msg("onroadEvents", 4, events("promptDriverDistracted")),
    msg("onroadEvents", 5, events("driverUnresponsive")),
    msg("onroadEvents", 6, events("driverUnresponsive")),
    msg("carState", 10, SimpleNamespace(vEgo=10.0)),
    msg("selfdriveState", 10, SimpleNamespace(enabled=False)),
  ]

  drive = utilities._analyze_route_messages(messages, route, {}, is_metric=False)

  assert drive["distance"] == 0.1
  assert drive["duration"] == 10
  assert drive["avgSpeed"] == 22
  assert drive["engagedPercent"] == 100
  assert drive["model"] == "North Star"
  assert drive["distractedMoments"] == 2
  assert drive["unresponsiveMoments"] == 1


def test_route_model_falls_back_to_catalog_key():
  route = {"name": "route-a", "segmentCount": 1, "startedAt": None}
  messages = [
    msg("initData", 0, SimpleNamespace(params={"Model": b"orion"})),
  ]
  model_names = {"orion": {"name": "Orion", "series": "City", "key": "orion"}}

  drive = utilities._analyze_route_messages(messages, route, model_names, is_metric=True)

  assert drive["model"] == "Orion"


def test_route_model_reads_logged_param_entries():
  route = {"name": "route-a", "segmentCount": 1, "startedAt": None}
  params = SimpleNamespace(entries=[
    SimpleNamespace(key="Model", value=b"orion"),
  ])
  messages = [
    msg("initData", 0, SimpleNamespace(params=params)),
  ]
  model_names = {"orion": {"name": "Orion", "series": "City", "key": "orion"}}

  drive = utilities._analyze_route_messages(messages, route, model_names, is_metric=True)

  assert drive["model"] == "Orion"


def test_week_and_record_summaries_use_analyzed_drives():
  now = utilities.datetime(2026, 6, 16, 12, 0, 0)
  drives = [
    {"date": "2026-06-15T08:00:00", "distance": 10.0, "duration": 1200, "engagedSeconds": 900, "distractedMoments": 0, "unresponsiveMoments": 0},
    {"date": "2026-06-16T08:00:00", "distance": 4.0, "duration": 600, "engagedSeconds": 600, "distractedMoments": 1, "unresponsiveMoments": 0},
    {"date": "2026-06-08T08:00:00", "distance": 25.0, "duration": 1800, "engagedSeconds": 900, "distractedMoments": 0, "unresponsiveMoments": 0},
  ]

  week = utilities._build_week_summary(drives, now, is_metric=False)
  records = utilities._build_records(drives, is_metric=False)

  assert week["distance"] == 14.0
  assert week["drives"] == 2
  assert week["engagedPercent"] == 83
  assert records["longestDrive"]["value"] == "25.0"
  assert records["highestStreak"]["value"] == "2 days"
  assert records["longestUndistractedDrive"]["value"] == "0.5 hours"
  assert records["cleanDriveStreak"]["value"] == "3 drives"


def test_attention_records_use_distracted_for_undistracted_and_unresponsive_for_clean_streak():
  drives = [
    {"date": "2026-06-15T08:00:00", "distance": 10.0, "duration": 1200, "engagedSeconds": 900, "distractedMoments": 0, "unresponsiveMoments": 0},
    {"date": "2026-06-16T08:00:00", "distance": 4.0, "duration": 3600, "engagedSeconds": 600, "distractedMoments": 1, "unresponsiveMoments": 0},
    {"date": "2026-06-17T08:00:00", "distance": 6.0, "duration": 600, "engagedSeconds": 400, "distractedMoments": 0, "unresponsiveMoments": 1},
    {"date": "2026-06-18T08:00:00", "distance": 8.0, "duration": 900, "engagedSeconds": 800, "distractedMoments": 0, "unresponsiveMoments": 0},
  ]

  records = utilities._build_records(drives, is_metric=False)

  assert records["longestUndistractedDrive"]["value"] == "0.3 hours"
  assert records["cleanDriveStreak"]["value"] == "2 drives"


def test_route_sampling_bounds_analyzed_segments():
  route = {
    "name": "route-a",
    "segmentCount": 10,
    "segments": [{"num": idx, "path": Path(f"/tmp/segment-{idx}")} for idx in range(10)],
  }

  sampled = utilities._sample_route_info(route, limit=3)

  assert sampled["segmentCount"] == 10
  assert sampled["analysisSegmentCount"] == 3
  assert [segment["num"] for segment in sampled["segments"]] == [0, 4, 9]


def test_top_models_are_ranked_from_persisted_usage_not_favorites():
  params = FakeParams({
    "AvailableModels": "orion,vega,atlas,nova",
    "AvailableModelNames": "Orion,Vega,Atlas,Nova",
    "AvailableModelSeries": "City,Highway,Experimental,Custom",
    "UserFavorites": "orion",
    "CommunityFavorites": "vega",
  })
  persistent = {
    "modelUsage": {
      "orion": {"name": "Orion", "drives": 3},
      "vega": {"name": "Vega", "drives": 1},
      "atlas": {"name": "Atlas", "drives": 9},
      "nova": {"name": "Nova", "drives": 4},
    },
  }

  favorites = utilities._build_favorite_models(params, persistent)

  assert [model["name"] for model in favorites] == ["Atlas", "Nova", "Orion"]
  assert len(favorites) == 3
  assert favorites[0]["userFavorite"] is False
  assert favorites[0]["drives"] == 9
  assert favorites[2]["userFavorite"] is True


def test_persistent_personal_records_and_model_usage_survive_empty_routes():
  params = FakeParams({"AvailableModels": "orion", "AvailableModelNames": "Orion", "CommunityFavorites": "orion"})
  drives = [
    {
      "name": "route-1",
      "date": "2026-06-15T08:00:00",
      "distanceMeters": 10000.0,
      "duration": 1200,
      "engagedSeconds": 900.0,
      "model": "Orion",
      "distractedMoments": 0,
      "unresponsiveMoments": 0,
      "routeModifiedAt": 100,
    },
    {
      "name": "route-2",
      "date": "2026-06-16T08:00:00",
      "distanceMeters": 5000.0,
      "duration": 600,
      "engagedSeconds": 600.0,
      "model": "Orion",
      "distractedMoments": 1,
      "unresponsiveMoments": 0,
      "routeModifiedAt": 100,
    },
    {
      "name": "route-3",
      "date": "2026-06-17T08:00:00",
      "distanceMeters": 20000.0,
      "duration": 1800,
      "engagedSeconds": 900.0,
      "model": "Orion",
      "distractedMoments": 0,
      "unresponsiveMoments": 0,
      "routeModifiedAt": 100,
    },
  ]

  persistent = utilities._update_dashboard_persistent_stats(params, drives, wall_now=1000)
  records = utilities._display_personal_records(persistent, is_metric=False)
  favorites = utilities._build_favorite_models(params, persistent)

  assert records["longestDrive"]["value"] == "12.4"
  assert records["mostEngagedDay"]["value"] == "100%"
  assert records["bestWeek"]["value"] == "21.7"
  assert records["highestStreak"]["value"] == "3 days"
  assert records["longestUndistractedDrive"]["value"] == "0.5 hours"
  assert records["cleanDriveStreak"]["value"] == "3 drives"
  assert favorites[0]["drives"] == 3

  restored = utilities._update_dashboard_persistent_stats(params, [], wall_now=2000)
  restored_records = utilities._display_personal_records(restored, is_metric=False)

  assert restored_records["longestDrive"]["value"] == "12.4"
  assert restored_records["mostEngagedDay"]["value"] == "100%"
  assert restored_records["bestWeek"]["value"] == "21.7"
  assert restored_records["highestStreak"]["value"] == "3 days"
  assert restored_records["longestUndistractedDrive"]["value"] == "0.5 hours"
  assert restored_records["cleanDriveStreak"]["value"] == "3 drives"


def test_github_urls_accept_owner_repo_origin():
  assert utilities.get_github_changelog_url("owner/repo", "main") == "https://github.com/owner/repo/commits/main/"
  assert utilities.get_github_changelog_url("github.com/owner/repo", "main") == "https://github.com/owner/repo/commits/main/"
  assert utilities.get_github_commit_url("owner/repo", "abcdef") == "https://github.com/owner/repo/commit/abcdef"


def _load_server_module():
  _install_server_import_stubs()
  spec = importlib.util.spec_from_file_location("dashboard_server", MODULE_DIR / ("the_" + "po" + "nd.py"))
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def test_stats_endpoint_keeps_existing_keys_and_adds_dashboard(monkeypatch):
  server = _load_server_module()
  assert getattr(server, "_import_" + "po" + "nd_web_symbols")()

  app = server.Flask(
    "dashboard_test",
    template_folder=str(MODULE_DIR / "templates"),
    static_folder=str(MODULE_DIR / "assets"),
  )
  server.setup(app)

  fake_metadata = SimpleNamespace(
    channel="test-branch",
    release_channel=False,
    tested_channel=False,
    openpilot=SimpleNamespace(
      git_commit="abcdef123456",
      git_normalized_origin="owner/repo",
      git_commit_date="'1700000000 2023-11-14 00:00:00 -0000'",
    ),
  )
  monkeypatch.setattr(server, "get_build_metadata", lambda: fake_metadata)
  monkeypatch.setattr(server, "FOOTAGE_PATHS", [])
  monkeypatch.setattr(server, "params", FakeParams({"UpdaterFetchAvailable": False, "IsMetric": False}))
  monkeypatch.setattr(server.utilities, "get_disk_usage", lambda: [{"free": "1 GB", "size": "2 GB", "used": "1 GB", "usedPercentage": "50.00%"}])
  monkeypatch.setattr(server.utilities, "get_drive_stats", lambda: {"all": {"drives": 0, "distance": 0, "hours": 0, "unit": "miles"}})
  monkeypatch.setattr(server.utilities, "get_dashboard_stats", lambda footage_paths, params_obj: {"lastDrive": {}, "recentDrives": []})

  response = app.test_client().get("/api/stats")
  payload = response.get_json()

  assert response.status_code == 200
  assert "diskUsage" in payload
  assert "driveStats" in payload
  assert "softwareInfo" in payload
  assert payload["dashboard"]["recentDrives"] == []
