from datetime import datetime

from openpilot.selfdrive.ui.widgets.drive_stats import demo_drive_stats_data, load_drive_stats_data


class FakeParams:
  def __init__(self, values):
    self.values = values

  def get(self, key):
    return self.values.get(key)

  def get_bool(self, key):
    return bool(self.values.get(key, False))


def test_drive_stats_uses_cloud_totals_and_local_galaxy_week():
  params = FakeParams({
    "ApiCache_DriveStats": {
      "all": {"distance": 100.0, "routes": 12, "minutes": 360},
      "week": {"distance": 25.0, "routes": 3, "minutes": 90},
    },
    "GalaxyDashboardStats": {
      "ignoredRoutes": ["ignored"],
      "routes": {
        "previous-week": {
          "date": "2026-07-19T09:00:00",
          "distanceMeters": 8046.72,
          "duration": 1800,
          "engagedSeconds": 1200,
        },
        "this-week": {
          "date": "2026-07-20T09:00:00",
          "distanceMeters": 16093.44,
          "duration": 3600,
          "engagedSeconds": 3000,
        },
        "ignored": {
          "date": "2026-07-20T10:00:00",
          "distanceMeters": 160934.4,
          "duration": 7200,
        },
      },
      "personalRecords": {
        "longestDrive": {"distanceMeters": 32186.88, "date": "2026-07-18T09:00:00"},
        "mostEngagedDay": {"percent": 0, "date": ""},
      },
    },
  })

  data = load_drive_stats_data(params, now=datetime(2026, 7, 20, 12, 0, 0))

  assert data.all_time.drives == 12
  assert data.all_time.distance == 100.0
  assert data.all_time.hours == 6.0
  assert data.past_week.drives == 3
  assert data.past_week.distance == 25.0
  assert data.this_week.drives == 1
  assert data.this_week.distance == 10.0
  assert data.this_week.hours == 1.0
  assert [day.label for day in data.daily_distance] == ["M", "T", "W", "T", "F", "S", "S"]
  assert data.daily_distance[0].distance == 10.0
  assert data.daily_distance[0].is_today
  assert data.daily_distance[1].is_future
  assert data.records[0].value == "20.0 mi"
  assert data.records[0].detail == "Jul 18"
  assert data.records[1].value == "83%"
  assert data.records[1].detail == "Jul 20"


def test_drive_stats_falls_back_to_local_totals_and_computed_records():
  params = FakeParams({
    "IsMetric": True,
    "StarPilotStats": {
      "StarPilotMeters": 25000.0,
      "StarPilotSeconds": 7200,
      "StarPilotDrives": 4,
    },
    "GalaxyDashboardStats": {
      "routes": {
        "previous-week": {
          "date": "2026-07-19T09:00:00",
          "distanceMeters": 5000.0,
          "duration": 1800,
          "engagedSeconds": 900,
          "clean": True,
          "undistracted": True,
        },
        "this-week": {
          "date": "2026-07-20T09:00:00",
          "distanceMeters": 10000.0,
          "duration": 3600,
          "engagedSeconds": 3000,
          "clean": True,
          "undistracted": True,
        },
      },
    },
  })

  data = load_drive_stats_data(params, now=datetime(2026, 7, 20, 12, 0, 0))

  assert data.all_time.drives == 4
  assert data.all_time.distance == 25.0
  assert data.all_time.hours == 2.0
  assert data.past_week.drives == 2
  assert data.past_week.distance == 15.0
  assert data.this_week.drives == 1
  assert data.this_week.distance == 10.0
  assert data.records[0].value == "10.0 km"
  assert data.records[2].value == "10.0 km"
  assert data.records[3].value == "2 days"
  assert data.records[5].value == "2 drives"


def test_drive_stats_repairs_touched_filesystem_routes_without_moving_them_to_today():
  params = FakeParams({
    "ApiCache_DriveStats": {
      "week": {"distance": 302.9, "routes": 31, "minutes": 467},
    },
    "GalaxyDashboardStats": {
      "routes": {
        "000011e4--2ed59ee965": {
          "date": "2026-07-18T08:59:31",
          "distanceMeters": 1609.344,
          "duration": 600,
          "timeSource": "log",
        },
        "000011e5--92dc4759b2": {
          "date": "2026-07-20T11:33:49",
          "distanceMeters": 16093.44,
          "duration": 1800,
          "timeSource": "filesystem",
        },
        "000011e6--8b54c54356": {
          "date": "2026-07-19T07:03:36",
          "distanceMeters": 3218.688,
          "duration": 900,
          "timeSource": "log",
        },
        "000011e8--09c2203d2e": {
          "date": "2026-07-19T18:17:44",
          "distanceMeters": 1609.344,
          "duration": 600,
          "timeSource": "log",
        },
        "000011e9--a3a4dcd6ef": {
          "date": "2026-07-20T11:38:53",
          "distanceMeters": 32186.88,
          "duration": 1800,
          "timeSource": "filesystem",
        },
        "000011ea--00b28940d5": {
          "date": "2026-07-20T02:18:17",
          "distanceMeters": 8046.72,
          "duration": 900,
          "timeSource": "log",
        },
      },
    },
  })

  data = load_drive_stats_data(params, now=datetime(2026, 7, 20, 12, 0, 0))

  assert data.past_week.distance == 302.9
  assert round(data.this_week.distance, 1) == 25.0
  assert round(data.daily_distance[0].distance, 1) == 25.0


def test_drive_stats_uses_clean_empty_record_labels():
  data = load_drive_stats_data(FakeParams({}), now=datetime(2026, 7, 20, 12, 0, 0))

  assert data.records[2].detail == "No drives"
  assert data.records[3].value == "0 days"
  assert data.records[3].detail == "No drives"
  assert data.records[4].detail == "No clean drives"
  assert data.records[5].value == "0 drives"
  assert data.records[5].detail == "No clean drives"


def test_demo_drive_stats_populates_every_dashboard_section():
  data = demo_drive_stats_data(False, now=datetime(2026, 7, 20, 12, 0, 0))

  assert data.all_time.drives == 584
  assert data.past_week.drives == 18
  assert data.this_week.drives == 7
  assert len(data.daily_distance) == 7
  assert all(day.distance > 0 for day in data.daily_distance)
  assert data.daily_distance[0].is_today
  assert len(data.records) == 6

  metric_data = demo_drive_stats_data(True, now=datetime(2026, 7, 20, 12, 0, 0))
  assert metric_data.all_time.unit == "kilometers"
  assert metric_data.all_time.distance > data.all_time.distance
  assert metric_data.records[0].value.endswith(" km")
