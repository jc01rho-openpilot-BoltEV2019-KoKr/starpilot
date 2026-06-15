#pragma once

#include "starpilot/ui/qt/offroad/starpilot_settings.h"

class StarPilotSoundsPanel : public StarPilotListWidget {
  Q_OBJECT

public:
  explicit StarPilotSoundsPanel(StarPilotSettingsWindow *parent, bool forceOpen = false);

signals:
  void openSubPanel();

protected:
  void showEvent(QShowEvent *event) override;

private:
  void initializeSoundPlayer();
  void testSound(const QString &key);
  void updateState(const UIState &s);
  void updateToggles();

  bool forceOpenDescriptions;
  bool started;

  std::map<QString, AbstractControl*> toggles;

  QSet<QString> alertCooldownKeys {"SwitchbackModeCooldown"};
  QSet<QString> alertVolumeControlKeys {"BelowSteerSpeedVolume", "DisengageVolume", "EngageVolume", "PromptDistractedVolume", "PromptVolume", "RefuseVolume", "WarningImmediateVolume", "WarningSoftVolume"};
  QSet<QString> customAlertsKeys {"GoatScream", "GoatScreamCriticalAlerts", "GreenLightAlert", "LeadDepartingAlert", "LoudBlindspotAlert", "LoudBlindspotAlertWhenDisengaged", "SpeedLimitChangedAlert"};

  QSet<QString> parentKeys;

  StarPilotSettingsWindow *parent;

  Params params;
  Params params_memory{"", true};

  QProcess *soundPlayerProcess;
};
