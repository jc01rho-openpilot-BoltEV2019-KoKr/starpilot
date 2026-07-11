#pragma once

#include "starpilot/ui/qt/offroad/starpilot_settings.h"

class StarPilotUtilitiesPanel : public StarPilotListWidget {
  Q_OBJECT

public:
  explicit StarPilotUtilitiesPanel(StarPilotSettingsWindow *parent, bool forceOpen = false);

private:
  bool forceOpenDescriptions;

  StarPilotSettingsWindow *parent;

  Params params;
  Params params_memory{"", true};

  std::set<std::string> excluded_keys = {
    "AvailableModels", "AvailableModelNames", "AvailableModelArtifactFormats", "StarPilotStats",
    "GithubSshKeys", "GithubUsername", "MapBoxRequests",
    "ModelDrivesAndScores", "ModelManifestVersion", "OverpassRequests", "SpeedLimits",
    "SpeedLimitsFiltered", "UpdaterAvailableBranches",
  };
};
