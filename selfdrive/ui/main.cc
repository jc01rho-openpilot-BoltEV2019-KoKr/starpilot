#include <sys/resource.h>
#include <unistd.h>

#include <QApplication>
#include <QTranslator>

#include "common/swaglog.h"
#include "common/util.h"
#include "system/hardware/hw.h"
#include "selfdrive/ui/qt/qt_window.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/window.h"

// Qt 5.12.8's qErrnoWarning() emits QtCriticalMsg then calls abort() directly,
// bypassing the fatal-message path. Intercept critical+fatal Wayland messages
// before the unconditional abort() fires and clean-exit so the manager restarts
// us quickly instead of going through the slow abort/crash-handler path.
void waylandAwareMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  if (type == QtCriticalMsg || type == QtFatalMsg) {
    QByteArray bytes = msg.toUtf8();
    if (bytes.contains("ayland") || bytes.contains("wl_display")) {
      swagLogMessageHandler(type, context, msg);
      LOGE("UI WAYLAND EXIT: %s", bytes.constData());
      _exit(0);  // clean exit; manager restarts us
    }
  }
  swagLogMessageHandler(type, context, msg);
  // Non-Wayland fatal: let Qt abort normally; crash_handler will capture it.
}

int main(int argc, char *argv[]) {
  setpriority(PRIO_PROCESS, 0, -20);

  // Pin the UI to the little cores (0-3). The realtime control loop
  // (card/controlsd/selfdrived) runs SCHED_FIFO on core 4; without this pin the
  // kernel can schedule the UI there, and a UI stall/restart spike preempts
  // selfdrived, starving its 100 Hz loop and firing the "System Lagging" alert.
  // Set before any threads spawn so children inherit the affinity.
  if (!Hardware::PC()) {
    util::set_core_affinity({0, 1, 2, 3});
  }

  qInstallMessageHandler(waylandAwareMessageHandler);
  initApp(argc, argv);

  QTranslator translator;
  QString translation_file = QString::fromStdString(Params().get("LanguageSetting"));
  if (!translator.load(QString(":/%1").arg(translation_file)) && translation_file.length()) {
    qCritical() << "Failed to load translation file:" << translation_file;
  }

  QApplication a(argc, argv);
  a.installTranslator(&translator);

  MainWindow w;
  setMainWindow(&w);
  a.installEventFilter(&w);
  return a.exec();
}
