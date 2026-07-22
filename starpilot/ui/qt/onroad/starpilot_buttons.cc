#include "starpilot/ui/qt/onroad/starpilot_buttons.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QPainterPath>
#include <string>

namespace {
constexpr int favorite_btn_size = btn_size;
constexpr int favorite_indicator_size = 22;
constexpr int favorite_slots_count = 3;
const QString favorite_action_decrease = "__starpilot_favorite_action__:distance_decrease";
const QString favorite_action_increase = "__starpilot_favorite_action__:distance_increase";
const std::string favorite_action_decel_counter = "FavoriteVirtualDecelCruiseCounter";
const std::string favorite_action_accel_counter = "FavoriteVirtualAccelCruiseCounter";

QJsonArray parseFavoriteSlots(const std::string &raw_slots) {
  QJsonParseError error;
  const QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(raw_slots), &error);
  if (error.error != QJsonParseError::NoError || !doc.isArray()) {
    return QJsonArray();
  }
  return doc.array();
}
}  // namespace

DrivingPersonalityButton::DrivingPersonalityButton(QWidget *parent) : QPushButton(parent) {
  setFixedSize(btn_size + UI_BORDER_SIZE, btn_size);

  QObject::connect(starpilotUIState(), &StarPilotUIState::themeUpdated, this, &DrivingPersonalityButton::updateTheme);
  QObject::connect(this, &QPushButton::pressed, [this] {params_memory.putBool("OnroadDistanceButtonPressed", true);});
  QObject::connect(this, &QPushButton::released, [this] {params_memory.putBool("OnroadDistanceButtonPressed", false);});
}

void DrivingPersonalityButton::showEvent(QShowEvent *event) {
  updateTheme();
}

void DrivingPersonalityButton::updateTheme() {
  for (QMap<int, QPair<QPixmap, QSharedPointer<QMovie>>>::iterator it = icon_map.begin(); it != icon_map.end(); ++it) {
    QSharedPointer<QMovie> &movie = it.value().second;
    if (!movie.isNull()) {
      QObject::disconnect(movie.data(), nullptr, this, nullptr);
      movie->stop();
    }
  }

  icon_map.clear();

  QPixmap traffic_img, aggressive_img, standard_img, relaxed_img;
  QSharedPointer<QMovie> traffic_gif, aggressive_gif, standard_gif, relaxed_gif;

  loadImage("../../starpilot/assets/active_theme/distance_icons/traffic", traffic_img, traffic_gif, QSize(btn_size, btn_size), this);
  loadImage("../../starpilot/assets/active_theme/distance_icons/aggressive", aggressive_img, aggressive_gif, QSize(btn_size, btn_size), this);
  loadImage("../../starpilot/assets/active_theme/distance_icons/standard", standard_img, standard_gif, QSize(btn_size, btn_size), this);
  loadImage("../../starpilot/assets/active_theme/distance_icons/relaxed", relaxed_img, relaxed_gif, QSize(btn_size, btn_size), this);

  icon_map.insert(0, qMakePair(traffic_img, traffic_gif));
  icon_map.insert(1, qMakePair(aggressive_img, aggressive_gif));
  icon_map.insert(2, qMakePair(standard_img, standard_gif));
  icon_map.insert(3, qMakePair(relaxed_img, relaxed_gif));

  theme_updated = true;
}

void DrivingPersonalityButton::updateState(const UIState &s, const StarPilotUIState &fs) {
  const UIScene &scene = s.scene;

  const SubMaster &fpsm = *(fs.sm);

  const cereal::StarPilotCarState::Reader &starpilotCarState = fpsm["starpilotCarState"].getStarpilotCarState();

  bool new_traffic_mode_active = starpilotCarState.getTrafficModeEnabled();

  int new_personality = static_cast<int>(scene.personality) + 1;

  bool state_changed = (traffic_mode_active != new_traffic_mode_active) ||
                       (personality != new_personality && !new_traffic_mode_active);

  if (!state_changed && !theme_updated) {
    return;
  }

  traffic_mode_active = new_traffic_mode_active;

  personality = new_personality;

  theme_updated = false;

  QPair<QPixmap, QSharedPointer<QMovie>> icon = icon_map.value(traffic_mode_active ? 0 : personality);
  currentImg = icon.first;
  currentGif = icon.second.data();
}

void DrivingPersonalityButton::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  drawIcon(p, rect().center() + QPoint(UI_BORDER_SIZE / 2, 0), currentGif ? currentGif->currentPixmap() : currentImg, Qt::transparent, 1.0);
}

FavoriteButton::FavoriteButton(int slot_index, QWidget *parent) : QPushButton(parent), slot_index(slot_index) {
  setFixedSize(favorite_btn_size, favorite_btn_size);
  QObject::connect(this, &QPushButton::clicked, this, &FavoriteButton::toggleFavorite);
}

FavoriteSlotState FavoriteButton::currentSlot() {
  FavoriteSlotState next_slot;
  if (slot_index < 0 || slot_index >= favorite_slots_count) {
    return next_slot;
  }

  const QJsonArray favorite_slots = parseFavoriteSlots(params.get("StarPilotFavoriteSlots"));
  if (slot_index >= favorite_slots.size() || !favorite_slots.at(slot_index).isObject()) {
    return next_slot;
  }

  const QJsonObject slot_obj = favorite_slots.at(slot_index).toObject();
  next_slot.enabled = slot_obj.value("enabled").toBool(false);
  next_slot.show_onroad = slot_obj.value("show_onroad").toBool(false);
  next_slot.key = slot_obj.value("key").toString().trimmed();
  next_slot.label = slot_obj.value("label").toString().trimmed();
  next_slot.action = next_slot.key == favorite_action_decrease || next_slot.key == favorite_action_increase;

  if (!next_slot.action &&
      (next_slot.key.isEmpty() || !params.checkKey(next_slot.key.toStdString()) || params.getKeyType(next_slot.key.toStdString()) != ParamKeyType::BOOL)) {
    next_slot.enabled = false;
    next_slot.show_onroad = false;
    next_slot.key.clear();
    next_slot.label.clear();
    return next_slot;
  }

  if (next_slot.label.isEmpty() && next_slot.action) {
    next_slot.label = next_slot.key == favorite_action_increase ? "Distance + / RES" : "Distance - / SET";
  } else if (next_slot.label.isEmpty()) {
    next_slot.label = next_slot.key;
  }
  next_slot.value = !next_slot.action && params.getBool(next_slot.key.toStdString());
  return next_slot;
}

void FavoriteButton::updateState() {
  const FavoriteSlotState next_slot = currentSlot();
  const bool changed = next_slot.enabled != slot.enabled ||
                       next_slot.show_onroad != slot.show_onroad ||
                       next_slot.action != slot.action ||
                       next_slot.value != slot.value ||
                       next_slot.key != slot.key ||
                       next_slot.label != slot.label;
  slot = next_slot;
  setVisible(shouldShow());
  if (changed) {
    update();
  }
}

bool FavoriteButton::shouldShow() const {
  return slot.enabled && slot.show_onroad && !slot.key.isEmpty();
}

void FavoriteButton::toggleFavorite() {
  slot = currentSlot();
  if (!slot.enabled || slot.key.isEmpty()) {
    return;
  }

  if (slot.action) {
    const std::string counter_key = slot.key == favorite_action_increase ? favorite_action_accel_counter : favorite_action_decel_counter;
    params_memory.putInt(counter_key, params_memory.getInt(counter_key) + 1);
    update();
    return;
  }

  const bool next_value = !params.getBool(slot.key.toStdString());
  params.putBool(slot.key.toStdString(), next_value);
  params_memory.putBool("StarPilotTogglesUpdated", true);
  slot.value = next_value;
  update();
}

QFont FavoriteButton::fittedLabelFont(QPainter &p, const QString &label, const QRect &text_rect) const {
  QFont font = p.font();
  font.setWeight(QFont::DemiBold);
  font.setLetterSpacing(QFont::AbsoluteSpacing, 0);

  for (int font_size = 28; font_size >= 18; --font_size) {
    font.setPixelSize(font_size);
    const QFontMetrics metrics(font);
    const QRect bounds = metrics.boundingRect(text_rect, Qt::AlignCenter | Qt::TextWordWrap, label);
    if (bounds.width() <= text_rect.width() && bounds.height() <= text_rect.height()) {
      return font;
    }
  }

  font.setPixelSize(18);
  return font;
}

void FavoriteButton::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  const QRectF bg_rect = rect().adjusted(0, 0, -1, -1);
  QPainterPath bg_path;
  bg_path.addRoundedRect(bg_rect, 12, 12);
  p.fillPath(bg_path, QColor(0, 0, 0, isDown() ? 190 : 166));
  p.setPen(QPen(QColor(255, 255, 255, isDown() ? 130 : 95), 2));
  p.drawPath(bg_path);

  const QColor indicator_color = slot.action ? QColor(139, 108, 197) : (slot.value ? QColor(48, 255, 156) : QColor(135, 135, 135));
  const int indicator_x = width() - 20 - favorite_indicator_size;
  const int indicator_y = 20;
  p.setPen(Qt::NoPen);
  p.setBrush(indicator_color);
  p.drawEllipse(indicator_x, indicator_y, favorite_indicator_size, favorite_indicator_size);
  if (slot.action) {
    QFont action_font = p.font();
    action_font.setPixelSize(20);
    action_font.setWeight(QFont::DemiBold);
    p.setFont(action_font);
    p.setPen(QColor(255, 255, 255, 230));
    p.drawText(QRect(indicator_x, indicator_y - 1, favorite_indicator_size, favorite_indicator_size), Qt::AlignCenter, slot.key == favorite_action_increase ? "+" : "-");
  }

  QFont slot_font = p.font();
  slot_font.setPixelSize(20);
  slot_font.setWeight(QFont::DemiBold);
  slot_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
  p.setFont(slot_font);
  p.setPen(QColor(255, 255, 255, 175));
  p.drawText(QRect(18, 14, 54, 32), Qt::AlignLeft | Qt::AlignVCenter, QString("#%1").arg(slot_index + 1));

  const QString label = slot.label.isEmpty() ? QStringLiteral("Favorite") : slot.label;
  const QRect text_rect(14, 50, width() - 28, height() - 64);
  p.setFont(fittedLabelFont(p, label, text_rect));
  p.setPen(QColor(255, 255, 255, 245));
  p.drawText(text_rect, Qt::AlignCenter | Qt::TextWordWrap, label);
}
