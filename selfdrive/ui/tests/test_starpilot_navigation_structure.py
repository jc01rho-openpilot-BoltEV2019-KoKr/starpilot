from openpilot.selfdrive.ui.layouts.settings.starpilot.main_panel import StarPilotLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.navigation import StarPilotNavigationLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanelType


def test_navigation_and_maps_is_the_parent_folder_for_map_data_and_navigation():
  category = next(item for item in StarPilotLayout.CATEGORIES if item["title"] == "Navigation & Maps")

  assert "panel" not in category
  assert category["buttons"] == [
    ("Map Data", "MAPS", "navigate"),
    ("Navigation", "NAVIGATION", "road"),
  ]
  assert all(item["title"] != "Map Data" for item in StarPilotLayout.CATEGORIES)
  assert StarPilotPanelType.NAVIGATION.value == 13


def test_navigation_start_is_the_summary_action_not_a_duplicate_rail_target():
  layout = object.__new__(StarPilotNavigationLayout)
  layout._draft_destination = {
    "name": "Home",
    "place_name": "Home",
    "latitude": 1.0,
    "longitude": 2.0,
  }
  layout._selected_favorite = None
  layout._favorites = []

  action_ids = [action[0] for action in layout._action_definitions()]

  assert action_ids == ["action:favorite", "action:home", "action:work"]


def test_rejected_search_invalidates_an_in_flight_request_generation():
  layout = object.__new__(StarPilotNavigationLayout)
  layout._search_generation = 3
  layout._query = "previous"
  layout._search_results = []
  layout._search_error = ""
  layout._draft_destination = None
  layout._selected_favorite = None

  layout._start_search("ab")

  assert layout._search_generation == 4
  assert layout._search_error
