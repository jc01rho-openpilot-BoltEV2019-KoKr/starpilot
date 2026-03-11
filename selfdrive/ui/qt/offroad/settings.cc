#include <cassert>
#include <cmath>
#include <string>
#include <tuple>
#include <vector>

#include <QDebug>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QrCode.hpp>

#include "common/watchdog.h"
#include "common/util.h"
#include "selfdrive/ui/qt/network/networking.h"
#include "selfdrive/ui/qt/offroad/settings.h"
#include "selfdrive/ui/qt/qt_window.h"
#include "selfdrive/ui/qt/widgets/prime.h"
#include "selfdrive/ui/qt/widgets/scrollview.h"
#include "selfdrive/ui/qt/widgets/ssh_keys.h"

#include "frogpilot/ui/qt/offroad/frogpilot_settings.h"

TogglesPanel::TogglesPanel(SettingsWindow *parent) : ListWidget(parent) {
  // param, title, desc, icon
  std::vector<std::tuple<QString, QString, QString, QString>> toggle_defs{
    {
      "OpenpilotEnabledToggle",
      tr("Enable openpilot"),
      tr("Use the openpilot system for adaptive cruise control and lane keep driver assistance. Your attention is required at all times to use this feature. Changing this setting takes effect when the car is powered off."),
      "../assets/offroad/icon_openpilot.png",
    },
    {
      "ExperimentalLongitudinalEnabled",
      tr("openpilot Longitudinal Control (Alpha)"),
      QString("<b>%1</b><br><br>%2")
      .arg(tr("WARNING: openpilot longitudinal control is in alpha for this car and will disable Automatic Emergency Braking (AEB)."))
      .arg(tr("On this car, openpilot defaults to the car's built-in ACC instead of openpilot's longitudinal control. "
              "Enable this to switch to openpilot longitudinal control. Enabling Experimental mode is recommended when enabling openpilot longitudinal control alpha.")),
      "../assets/offroad/icon_speed_limit.png",
    },
    {
      "ExperimentalMode",
      tr("Experimental Mode"),
      "",
      "../assets/img_experimental_white.svg",
    },
    {
      "DisengageOnAccelerator",
      tr("Disengage on Accelerator Pedal"),
      tr("When enabled, pressing the accelerator pedal will disengage openpilot."),
      "../assets/offroad/icon_disengage_on_accelerator.svg",
    },
    {
      "IsLdwEnabled",
      tr("Enable Lane Departure Warnings"),
      tr("Receive alerts to steer back into the lane when your vehicle drifts over a detected lane line without a turn signal activated while driving over 31 mph (50 km/h)."),
      "../assets/offroad/icon_warning.png",
    },
    {
      "RecordFront",
      tr("Record and Upload Driver Camera"),
      tr("Upload data from the driver facing camera and help improve the driver monitoring algorithm."),
      "../assets/offroad/icon_monitoring.png",
    },
    {
      "IsMetric",
      tr("Use Metric System"),
      tr("Display speed in km/h instead of mph."),
      "../assets/offroad/icon_metric.png",
    },
#ifdef ENABLE_MAPS
    {
      "NavSettingTime24h",
      tr("Show ETA in 24h Format"),
      tr("Use 24h format instead of am/pm"),
      "../assets/offroad/icon_metric.png",
    },
    {
      "NavSettingLeftSide",
      tr("Show Map on Left Side of UI"),
      tr("Show map on left side when in split screen view."),
      "../assets/offroad/icon_road.png",
    },
#endif
  };


  std::vector<QString> longi_button_texts{tr("Aggressive"), tr("Standard"), tr("Relaxed")};
  long_personality_setting = new ButtonParamControl("LongitudinalPersonality", tr("Driving Personality"),
                                          tr("Standard is recommended. In aggressive mode, openpilot will follow lead cars closer and be more aggressive with the gas and brake. "
                                             "In relaxed mode openpilot will stay further away from lead cars. On supported cars, you can cycle through these personalities with "
                                             "your steering wheel distance button."),
                                          "../assets/offroad/icon_speed_limit.png",
                                          longi_button_texts);

  // set up uiState update for personality setting
  QObject::connect(uiState(), &UIState::uiUpdate, this, &TogglesPanel::updateState);

  for (auto &[param, title, desc, icon] : toggle_defs) {
    auto toggle = new ParamControl(param, title, desc, icon, this);

    bool locked = params.getBool((param + "Lock").toStdString());
    toggle->setEnabled(!locked);

    addItem(toggle);
    toggles[param.toStdString()] = toggle;

    // insert longitudinal personality after NDOG toggle
    if (param == "DisengageOnAccelerator") {
      addItem(long_personality_setting);
    }
  }

  // Toggles with confirmation dialogs
  toggles["ExperimentalMode"]->setActiveIcon("../assets/img_experimental.svg");
  toggles["ExperimentalMode"]->setConfirmation(true, true);
  toggles["ExperimentalLongitudinalEnabled"]->setConfirmation(true, false);

  connect(toggles["ExperimentalLongitudinalEnabled"], &ToggleControl::toggleFlipped, [=]() {
    updateToggles();
  });

  // FrogPilot signals
  connect(toggles["IsMetric"], &ToggleControl::toggleFlipped, [=](bool metric) {
    updateMetric(metric);
  });
}

void TogglesPanel::updateState(const UIState &s) {
  const SubMaster &sm = *(s.sm);

  if (sm.updated("controlsState")) {
    auto personality = sm["controlsState"].getControlsState().getPersonality();
    if (personality != s.scene.personality && s.scene.started && isVisible()) {
      long_personality_setting->setCheckedButton(static_cast<int>(personality));
    }
    uiState()->scene.personality = personality;
  }
}

void TogglesPanel::expandToggleDescription(const QString &param) {
  toggles[param.toStdString()]->showDescription();
}

void TogglesPanel::showEvent(QShowEvent *event) {
  updateToggles();
}

void TogglesPanel::updateToggles() {
  FrogPilotUIState &fs = *frogpilotUIState();
  QJsonObject &frogpilot_toggles = fs.frogpilot_toggles;

  auto disengage_on_accelerator_toggle = toggles["DisengageOnAccelerator"];
  disengage_on_accelerator_toggle->setVisible(!frogpilot_toggles.value("always_on_lateral").toBool());
  auto driver_camera_toggle = toggles["RecordFront"];
  driver_camera_toggle->setVisible(!(frogpilot_toggles.value("no_logging").toBool() && frogpilot_toggles.value("no_uploads").toBool()));
  auto nav_settings_left_toggle = toggles["NavSettingLeftSide"];
  nav_settings_left_toggle->setVisible(!frogpilot_toggles.value("full_map").toBool());

  auto experimental_mode_toggle = toggles["ExperimentalMode"];
  auto op_long_toggle = toggles["ExperimentalLongitudinalEnabled"];
  const QString e2e_description = QString("%1<br>"
                                          "<h4>%2</h4><br>"
                                          "%3<br>"
                                          "<h4>%4</h4><br>"
                                          "%5<br>")
                                  .arg(tr("openpilot defaults to driving in <b>chill mode</b>. Experimental mode enables <b>alpha-level features</b> that aren't ready for chill mode. Experimental features are listed below:"))
                                  .arg(tr("End-to-End Longitudinal Control"))
                                  .arg(tr("Let the driving model control the gas and brakes. openpilot will drive as it thinks a human would, including stopping for red lights and stop signs. "
                                          "Since the driving model decides the speed to drive, the set speed will only act as an upper bound. This is an alpha quality feature; "
                                          "mistakes should be expected."))
                                  .arg(tr("New Driving Visualization"))
                                  .arg(tr("The driving visualization will transition to the road-facing wide-angle camera at low speeds to better show some turns. The Experimental mode logo will also be shown in the top right corner."));

  auto cp_bytes = params.get("CarParamsPersistent");
  if (!cp_bytes.empty()) {
    AlignedBuffer aligned_buf;
    capnp::FlatArrayMessageReader cmsg(aligned_buf.align(cp_bytes.data(), cp_bytes.size()));
    cereal::CarParams::Reader CP = cmsg.getRoot<cereal::CarParams>();

    if (!CP.getExperimentalLongitudinalAvailable()) {
      params.remove("ExperimentalLongitudinalEnabled");
    }
    op_long_toggle->setVisible(CP.getExperimentalLongitudinalAvailable());
    if (hasLongitudinalControl(CP)) {
      // normal description and toggle
      experimental_mode_toggle->setEnabled(true);
      experimental_mode_toggle->setDescription(e2e_description);
      long_personality_setting->setEnabled(true);
    } else {
      // no long for now
      experimental_mode_toggle->setEnabled(false);
      long_personality_setting->setEnabled(false);
      params.remove("ExperimentalMode");

      const QString unavailable = tr("Experimental mode is currently unavailable on this car since the car's stock ACC is used for longitudinal control.");

      QString long_desc = unavailable + " " + \
                          tr("openpilot longitudinal control may come in a future update.");
      if (CP.getExperimentalLongitudinalAvailable()) {
        long_desc = tr("Enable the openpilot longitudinal control (alpha) toggle to allow Experimental mode.");
      }
      experimental_mode_toggle->setDescription("<b>" + long_desc + "</b><br><br>" + e2e_description);
    }

    experimental_mode_toggle->refresh();
  } else {
    experimental_mode_toggle->setDescription(e2e_description);
    op_long_toggle->setVisible(false);
  }
}

GalaxyQRPopup::GalaxyQRPopup(const QString &url, QWidget *parent) : DialogBase(parent) {
  setStyleSheet("GalaxyQRPopup { background-color: #1a1a30; }");
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setAlignment(Qt::AlignCenter);
  layout->setSpacing(30);
  layout->setContentsMargins(60, 40, 60, 40);

  // Generate QR image
  auto qr = qrcodegen::QrCode::encodeText(url.toUtf8().data(), qrcodegen::QrCode::Ecc::LOW);
  int sz = qr.getSize();
  QImage im(sz, sz, QImage::Format_RGB32);
  for (int y = 0; y < sz; y++)
    for (int x = 0; x < sz; x++)
      im.setPixel(x, y, qr.getModule(x, y) ? qRgb(0,0,0) : qRgb(255,255,255));
  QPixmap qrPixmap = QPixmap::fromImage(im.scaled(400, 400, Qt::KeepAspectRatio), Qt::MonoOnly);

  QLabel *title = new QLabel(tr("Scan to open Galaxy"), this);
  title->setStyleSheet("font-size: 52px; font-weight: bold; color: white;");
  title->setAlignment(Qt::AlignCenter);
  layout->addWidget(title);

  QLabel *qrLabel = new QLabel(this);
  qrLabel->setPixmap(qrPixmap);
  qrLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(qrLabel);

  QLabel *urlLabel = new QLabel(url, this);
  urlLabel->setStyleSheet("font-size: 36px; color: #8b6cc5;");
  urlLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(urlLabel);

  QLabel *hint = new QLabel(tr("Tap anywhere to dismiss"), this);
  hint->setStyleSheet("font-size: 28px; color: #7e7e98;");
  hint->setAlignment(Qt::AlignCenter);
  layout->addWidget(hint);
}

DevicePanel::DevicePanel(SettingsWindow *parent) : ListWidget(parent) {
  setSpacing(50);
  addItem(new LabelControl(tr("Dongle ID"), getDongleId().value_or(tr("N/A"))));
  addItem(new LabelControl(tr("Serial"), params.get("HardwareSerial").c_str()));

  pair_device = new ButtonControl(tr("Pair Device"), tr("PAIR"),
                                  useKonikServer() ? tr("Pair your device with Konik connect (stable.konik.ai).") : tr("Pair your device with comma connect (connect.comma.ai) and claim your comma prime offer."));
  connect(pair_device, &ButtonControl::clicked, [=]() {
    PairingPopup popup(this);
    popup.exec();
  });
  addItem(pair_device);

  // Shared helper to show QR popup
  auto showGalaxyQR = [=]() {
    std::string slug = util::read_file("/data/galaxy/glxyslug");
    if (slug.empty()) return;
    QString url = "https://galaxy.firestar.link/" + QString::fromStdString(slug);
    GalaxyQRPopup *popup = new GalaxyQRPopup(url, this);
    popup->exec();
    popup->deleteLater();
  };

  pair_galaxy = new ButtonControl(tr("Galaxy"), tr("Pair"), tr("Pair your device with Galaxy for remote access to The Pond."));
  connect(pair_galaxy, &ButtonControl::clicked, [=]() {
    std::string current_password = util::read_file("/data/galaxy/glxyauth");
    if (current_password.empty()) {
      QString new_password = InputDialog::getText(tr("Enter Password"), this, tr("Please enter a password to secure your Galaxy access. (Min 6 characters)"), false, 6);
      if (!new_password.isEmpty()) {
        std::string hash = QCryptographicHash::hash(new_password.toUtf8(), QCryptographicHash::Sha256).toHex().toStdString();
        util::create_directories("/data/galaxy", 0775);
        util::write_file("/data/galaxy/glxyauth", hash.data(), hash.size(), O_WRONLY | O_CREAT | O_TRUNC);

        // Generate 256-bit session token (64 hex chars)
        QByteArray session_bytes(32, 0);
        QRandomGenerator::securelySeeded().fillRange(reinterpret_cast<quint32*>(session_bytes.data()), 8);
        std::string session_token = session_bytes.toHex().toStdString();
        util::write_file("/data/galaxy/glxysession", session_token.data(), session_token.size(), O_WRONLY | O_CREAT | O_TRUNC);

        // Generate 16-char URL-safe slug (alphanumeric only)
        const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::string slug(16, '\0');
        auto *rng = QRandomGenerator::global();
        for (int i = 0; i < 16; i++) slug[i] = charset[rng->bounded(62)];
        util::write_file("/data/galaxy/glxyslug", slug.data(), slug.size(), O_WRONLY | O_CREAT | O_TRUNC);

        pair_galaxy->setText(tr("Unpair"));
        galaxy_qr_btn->setVisible(true);
        showGalaxyQR();
      }
    } else {
      if (ConfirmationDialog::confirm(tr("Are you sure you want to unpair from Galaxy?"), tr("Unpair"), this)) {
        std::remove("/data/galaxy/glxyauth");
        std::remove("/data/galaxy/glxysession");
        std::remove("/data/galaxy/glxyslug");
        pair_galaxy->setText(tr("Pair"));
        galaxy_qr_btn->setVisible(false);
      }
    }
  });

  // QR button — sits inline next to the Pair/Unpair button
  galaxy_qr_btn = new QPushButton(tr("QR"));
  galaxy_qr_btn->setFixedSize(250, 100);
  galaxy_qr_btn->setStyleSheet(R"(
    QPushButton { background-color: #393939; color: #E4E4E4; border-radius: 50px; font-size: 35px; font-weight: 500; }
    QPushButton:pressed { background-color: #4a4a4a; }
  )");
  galaxy_qr_btn->setVisible(false);
  connect(galaxy_qr_btn, &QPushButton::clicked, showGalaxyQR);
  if (QHBoxLayout *hlayout = pair_galaxy->findChild<QHBoxLayout *>()) {
    hlayout->insertWidget(3, galaxy_qr_btn);
  }

  addItem(pair_galaxy);

  // offroad-only buttons

  auto dcamBtn = new ButtonControl(tr("Driver Camera"), tr("PREVIEW"),
                                   tr("Preview the driver facing camera to ensure that driver monitoring has good visibility. (vehicle must be off)"));
  connect(dcamBtn, &ButtonControl::clicked, [=]() { emit showDriverView(); });
  addItem(dcamBtn);

  auto resetCalibBtn = new ButtonControl(tr("Reset Calibration"), tr("RESET"), "");
  connect(resetCalibBtn, &ButtonControl::showDescriptionEvent, this, &DevicePanel::updateCalibDescription);
  connect(resetCalibBtn, &ButtonControl::clicked, [&]() {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to reset calibration?"), tr("Reset"), this)) {
      params.remove("CalibrationParams");
      params.remove("LiveTorqueParameters");
      params.remove("LiveParameters");
      params.remove("LiveDelay");
    }
  });
  addItem(resetCalibBtn);

  auto retrainingBtn = new ButtonControl(tr("Review Training Guide"), tr("REVIEW"), tr("Review the rules, features, and limitations of openpilot"));
  connect(retrainingBtn, &ButtonControl::clicked, [=]() {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to review the training guide?"), tr("Review"), this)) {
      emit reviewTrainingGuide();
    }
  });
  addItem(retrainingBtn);

  if (Hardware::TICI()) {
    auto regulatoryBtn = new ButtonControl(tr("Regulatory"), tr("VIEW"), "");
    connect(regulatoryBtn, &ButtonControl::clicked, [=]() {
      const std::string txt = util::read_file("../assets/offroad/fcc.html");
      ConfirmationDialog::rich(QString::fromStdString(txt), this);
    });
    addItem(regulatoryBtn);
  }

  auto translateBtn = new ButtonControl(tr("Change Language"), tr("CHANGE"), "");
  connect(translateBtn, &ButtonControl::clicked, [=]() {
    QMap<QString, QString> langs = getSupportedLanguages();
    QString selection = MultiOptionDialog::getSelection(tr("Select a language"), langs.keys(), langs.key(uiState()->language), this);
    if (!selection.isEmpty()) {
      // put language setting, exit Qt UI, and trigger fast restart
      params.put("LanguageSetting", langs[selection].toStdString());
      qApp->exit(18);
      watchdog_kick(0);
    }
  });
  addItem(translateBtn);

  QObject::connect(uiState(), &UIState::primeTypeChanged, [this] (PrimeType type) {
    pair_device->setVisible(type == PrimeType::UNPAIRED);
  });
  QObject::connect(uiState(), &UIState::offroadTransition, [=](bool offroad) {
    for (auto btn : findChildren<ButtonControl *>()) {
      if (btn != pair_device) {
        btn->setEnabled(offroad);
      }
    }
  });

  // power buttons
  QHBoxLayout *power_layout = new QHBoxLayout();
  power_layout->setSpacing(30);

  QPushButton *reboot_btn = new QPushButton(tr("Reboot"));
  reboot_btn->setObjectName("reboot_btn");
  power_layout->addWidget(reboot_btn);
  QObject::connect(reboot_btn, &QPushButton::clicked, this, &DevicePanel::reboot);

  QPushButton *poweroff_btn = new QPushButton(tr("Power Off"));
  poweroff_btn->setObjectName("poweroff_btn");
  power_layout->addWidget(poweroff_btn);
  QObject::connect(poweroff_btn, &QPushButton::clicked, this, &DevicePanel::poweroff);

  if (!Hardware::PC()) {
    connect(uiState(), &UIState::offroadTransition, poweroff_btn, &QPushButton::setVisible);
  }

  setStyleSheet(R"(
    #reboot_btn { height: 120px; border-radius: 15px; background-color: #393939; }
    #reboot_btn:pressed { background-color: #4a4a4a; }
    #poweroff_btn { height: 120px; border-radius: 15px; background-color: #E22C2C; }
    #poweroff_btn:pressed { background-color: #FF2424; }
  )");
  addItem(power_layout);
}

void DevicePanel::updateCalibDescription() {
  QString desc =
      tr("openpilot requires the device to be mounted within 4° left or right and "
         "within 5° up or 9° down. openpilot is continuously calibrating, resetting is rarely required.");
  std::string calib_bytes = params.get("CalibrationParams");
  if (!calib_bytes.empty()) {
    try {
      AlignedBuffer aligned_buf;
      capnp::FlatArrayMessageReader cmsg(aligned_buf.align(calib_bytes.data(), calib_bytes.size()));
      auto calib = cmsg.getRoot<cereal::Event>().getLiveCalibration();
      if (calib.getCalStatus() != cereal::LiveCalibrationData::Status::UNCALIBRATED) {
        double pitch = calib.getRpyCalib()[1] * (180 / M_PI);
        double yaw = calib.getRpyCalib()[2] * (180 / M_PI);
        desc += tr(" Your device is pointed %1° %2 and %3° %4.")
                    .arg(QString::number(std::abs(pitch), 'g', 1), pitch > 0 ? tr("down") : tr("up"),
                         QString::number(std::abs(yaw), 'g', 1), yaw > 0 ? tr("left") : tr("right"));
      }
    } catch (kj::Exception) {
      qInfo() << "invalid CalibrationParams";
    }
  }
  qobject_cast<ButtonControl *>(sender())->setDescription(desc);
}

void DevicePanel::reboot() {
  if (!uiState()->engaged()) {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to reboot?"), tr("Reboot"), this)) {
      // Check engaged again in case it changed while the dialog was open
      if (!uiState()->engaged()) {
        params.putBool("DoReboot", true);
      }
    }
  } else {
    ConfirmationDialog::alert(tr("Disengage to Reboot"), this);
  }
}

void DevicePanel::poweroff() {
  if (!uiState()->engaged()) {
    if (ConfirmationDialog::confirm(tr("Are you sure you want to power off?"), tr("Power Off"), this)) {
      // Check engaged again in case it changed while the dialog was open
      if (!uiState()->engaged()) {
        params.putBool("DoShutdown", true);
      }
    }
  } else {
    ConfirmationDialog::alert(tr("Disengage to Power Off"), this);
  }
}

void DevicePanel::showEvent(QShowEvent *event) {
  pair_device->setVisible(uiState()->primeType() == PrimeType::UNPAIRED);

  std::string galaxy_pin = util::read_file("/data/galaxy/glxyauth");
  bool galaxy_paired = !galaxy_pin.empty();
  pair_galaxy->setText(galaxy_paired ? tr("Unpair") : tr("Pair"));
  galaxy_qr_btn->setVisible(galaxy_paired);

  ListWidget::showEvent(event);
}

void SettingsWindow::hideEvent(QHideEvent *event) {
  closePanel();
  closeSubPanel();

  panelOpen = false;
  subPanelOpen = false;
  subSubPanelOpen = false;

  updateFrogPilotToggles();
}

void SettingsWindow::showEvent(QShowEvent *event) {
  setCurrentPanel(0);
}

void SettingsWindow::setCurrentPanel(int index, const QString &param) {
  panel_widget->setCurrentIndex(index);
  nav_btns->buttons()[index]->setChecked(true);
  if (!param.isEmpty()) {
    emit expandToggleDescription(param);
  }
}

SettingsWindow::SettingsWindow(QWidget *parent) : QFrame(parent) {

  // setup two main layouts
  sidebar_widget = new QWidget;
  QVBoxLayout *sidebar_layout = new QVBoxLayout(sidebar_widget);
  panel_widget = new QStackedWidget();

  // close button
  QPushButton *close_btn = new QPushButton(tr("← Back"));
  close_btn->setStyleSheet(R"(
    QPushButton {
      font-size: 50px;
      border-radius: 25px;
      background-color: #292929;
      font-weight: 500;
    }
    QPushButton:pressed {
      background-color: #ADADAD;
    }
  )");
  close_btn->setFixedSize(300, 125);
  sidebar_layout->addSpacing(10);
  sidebar_layout->addWidget(close_btn, 0, Qt::AlignRight);
  QObject::connect(close_btn, &QPushButton::clicked, [this]() {
    if (subSubPanelOpen) {
      closeSubSubPanel();

      subSubPanelOpen = false;
    } else if (subPanelOpen) {
      closeSubPanel();

      subPanelOpen = false;
    } else if (panelOpen) {
      closePanel();

      panelOpen = false;
    } else {
      closeSettings();
    }
  });

  // setup panels
  DevicePanel *device = new DevicePanel(this);
  QObject::connect(device, &DevicePanel::reviewTrainingGuide, this, &SettingsWindow::reviewTrainingGuide);
  QObject::connect(device, &DevicePanel::showDriverView, this, &SettingsWindow::showDriverView);

  TogglesPanel *toggles = new TogglesPanel(this);
  QObject::connect(this, &SettingsWindow::expandToggleDescription, toggles, &TogglesPanel::expandToggleDescription);

  // FrogPilot panels
  QObject::connect(toggles, &TogglesPanel::updateMetric, this, &SettingsWindow::updateMetric);

  FrogPilotSettingsWindow *frogpilotSettingsWindow = new FrogPilotSettingsWindow(this);
  QObject::connect(frogpilotSettingsWindow, &FrogPilotSettingsWindow::openPanel, [this]() {panelOpen=true;});
  QObject::connect(frogpilotSettingsWindow, &FrogPilotSettingsWindow::openSubPanel, [this]() {subPanelOpen=true;});
  QObject::connect(frogpilotSettingsWindow, &FrogPilotSettingsWindow::openSubSubPanel, [this]() {subSubPanelOpen=true;});

  QList<QPair<QString, QWidget *>> panels = {
    {tr("Device"), device},
    {tr("Network"), new Networking(this)},
    {tr("Toggles"), toggles},
    {tr("Software"), new SoftwarePanel(this)},
    {tr("FrogPilot"), frogpilotSettingsWindow},
  };

  nav_btns = new QButtonGroup(this);
  for (auto &[name, panel] : panels) {
    QPushButton *btn = new QPushButton(name);
    btn->setCheckable(true);
    btn->setChecked(nav_btns->buttons().size() == 0);
    btn->setStyleSheet(R"(
      QPushButton {
        color: grey;
        border: none;
        background: none;
        font-size: 65px;
        font-weight: 500;
      }
      QPushButton:checked {
        color: white;
      }
      QPushButton:pressed {
        color: #ADADAD;
      }
    )");
    btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    nav_btns->addButton(btn);
    sidebar_layout->addWidget(btn, 0, Qt::AlignRight);

    const int lr_margin = name != tr("Network") ? 50 : 0;  // Network panel handles its own margins
    panel->setContentsMargins(lr_margin, 25, lr_margin, 25);

    ScrollView *panel_frame = new ScrollView(panel, this);
    panel_widget->addWidget(panel_frame);

    QObject::connect(btn, &QPushButton::clicked, [=, w = panel_frame]() {
      if (w->widget() == frogpilotSettingsWindow) {
        bool tuningLevelConfirmed = params.getBool("TuningLevelConfirmed");

        if (!tuningLevelConfirmed) {
          int frogpilotHours = QJsonDocument::fromJson(QString::fromStdString(params.get("FrogPilotStats")).toUtf8()).object().value("FrogPilotSeconds").toInt() / (60 * 60);
          int openpilotHours = params.getInt("KonikMinutes") / 60 + params.getInt("openpilotMinutes") / 60;

          if (frogpilotHours < 1 && openpilotHours < 100) {
            if (openpilotHours < 10) {
              if (ConfirmationDialog::alert(tr("Welcome to FrogPilot! Since you're new to openpilot, the \"Minimal\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
                params.putBool("TuningLevelConfirmed", true);
                params.putInt("TuningLevel", 0);
              }
            } else {
              if (ConfirmationDialog::alert(tr("Welcome to FrogPilot! Since you're new to FrogPilot, the \"Minimal\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
                params.putBool("TuningLevelConfirmed", true);
                params.putInt("TuningLevel", 0);
              }
            }
          } else if (frogpilotHours < 50 && openpilotHours < 100) {
            if (ConfirmationDialog::alert(tr("Since you're fairly new to FrogPilot, the \"Minimal\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
              params.putBool("TuningLevelConfirmed", true);
              params.putInt("TuningLevel", 0);
            }
          } else if (frogpilotHours < 100) {
            if (openpilotHours >= 100) {
              if (ConfirmationDialog::alert(tr("Since you're experienced with openpilot, the \"Standard\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
                params.putBool("TuningLevelConfirmed", true);
                params.putInt("TuningLevel", 1);
              }
            } else {
              if (ConfirmationDialog::alert(tr("Since you're experienced with FrogPilot, the \"Standard\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
                params.putBool("TuningLevelConfirmed", true);
                params.putInt("TuningLevel", 1);
              }
            }
          } else if (frogpilotHours >= 100) {
            if (ConfirmationDialog::alert(tr("Since you're very experienced with FrogPilot, the \"Advanced\" toggle preset has been applied, but you can change this at any time via the \"Tuning Level\" button!"), this, true)) {
              params.putBool("TuningLevelConfirmed", true);
              params.putInt("TuningLevel", 2);
            }
          }
          updateTuningLevel();
        }
      }

      if (panelOpen) {
        closePanel();

        panelOpen = false;
      }
      if (subPanelOpen) {
        closeSubPanel();

        subPanelOpen = false;
      }
      btn->setChecked(true);
      panel_widget->setCurrentWidget(w);
    });
  }
  sidebar_layout->setContentsMargins(50, 50, 100, 50);

  // main settings layout, sidebar + main panel
  QHBoxLayout *main_layout = new QHBoxLayout(this);

  sidebar_widget->setFixedWidth(500);
  main_layout->addWidget(sidebar_widget);
  main_layout->addWidget(panel_widget);

  setStyleSheet(R"(
    * {
      color: white;
      font-size: 50px;
    }
    SettingsWindow {
      background-color: black;
    }
    QStackedWidget, ScrollView {
      background-color: #292929;
      border-radius: 30px;
    }
  )");
}
