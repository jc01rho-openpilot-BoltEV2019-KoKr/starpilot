#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <map>
#include <cassert>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QProgressBar>
#include <QProcess>
#include <QWidget>
#include <QPair>
#include <QVector>

// --- Configuration ---
#define GIT_URL "https://github.com/27182818284590452353602874713526624977572470936999595"
#define BRANCH "161803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538689175212663386222353693179318006076672635443338908659593958290563832266131992829026788067520876689250171169620703222104321626954862629631361"
#define LOADING_MSG "314159265358979323846264338327950288419"
#define GIT_SSH_URL "git@github.com:commaai/openpilot.git"
#define CONTINUE_PATH "/data/continue.sh"
#define CACHE_PATH "/usr/comma/openpilot"
#define INSTALL_PATH "/data/openpilot"
#define TMP_INSTALL_PATH "/data/tmppilot"

// --- Embedded continue.sh ---
const char str_continue_data[] = R"(#!/usr/bin/env sh
exec /data/openpilot/launch_openpilot.sh
)";
const uint8_t *str_continue = (const uint8_t*)str_continue_data;
const uint8_t *str_continue_end = str_continue + sizeof(str_continue_data) - 1;

// --- Helper Functions ---
bool time_valid() {
  time_t rawtime;
  time(&rawtime);
  struct tm * sys_time = gmtime(&rawtime);
  return (1900 + sys_time->tm_year) >= 2020;
}

void run(const char* cmd) {
  int err = std::system(cmd);
  assert(err == 0);
}

float lerp(float a, float b, float f) {
  return (a * (1.0 - f)) + (b * f);
}

// --- Installer Class Definition ---
class Installer : public QWidget {
public:
  Installer(QWidget *parent = nullptr);

  void updateProgress(int percent);
  void doInstall();
  void freshClone();
  void cachedFetch();
  void readProgress();
  void cloneFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
  QProgressBar *bar;
  QLabel *val;
  QLabel *title;
  QProcess proc;
};

// --- Globals ---
static QString targetGitUrl = GIT_URL;
static QString targetBranch = BRANCH;

// --- Installer Implementation ---
Installer::Installer(QWidget *parent) : QWidget(parent) {
  QStackedLayout *stack = new QStackedLayout(this);
  stack->setMargin(0);

  // --- Page 0: Intro ---
  QWidget *introPage = new QWidget;
  QVBoxLayout *introLayout = new QVBoxLayout(introPage);
  introLayout->setContentsMargins(50, 50, 50, 50);
  introLayout->setSpacing(20);

  QLabel *introTitle = new QLabel("Select Installation Mode");
  introTitle->setStyleSheet("font-size: 60px; font-weight: 600; padding-bottom: 50px;");
  introTitle->setAlignment(Qt::AlignCenter);
  introLayout->addWidget(introTitle);

  QPushButton *btnDefault = new QPushButton("Default Installation");
  btnDefault->setFixedHeight(120);
  btnDefault->setStyleSheet("font-size: 40px; background-color: #333; border-radius: 10px;");
  introLayout->addWidget(btnDefault);

  QPushButton *btnBranch = new QPushButton("StarPilot Branch");
  btnBranch->setFixedHeight(120);
  btnBranch->setStyleSheet("font-size: 40px; background-color: #333; border-radius: 10px;");
  introLayout->addWidget(btnBranch);

  stack->addWidget(introPage);

  // --- Page 1: Branch Selection ---
  QWidget *branchPage = new QWidget;
  QVBoxLayout *branchLayout = new QVBoxLayout(branchPage);
  branchLayout->setContentsMargins(50, 50, 50, 50);

  QLabel *branchTitle = new QLabel("Select Branch");
  branchTitle->setStyleSheet("font-size: 50px; font-weight: 600;");
  branchLayout->addWidget(branchTitle);

  QListWidget *branchList = new QListWidget;
  branchList->setStyleSheet("font-size: 35px; background-color: #222;");
  branchLayout->addWidget(branchList);

  QHBoxLayout *btnLayout = new QHBoxLayout;
  QPushButton *btnCancel = new QPushButton("Cancel");
  btnCancel->setFixedHeight(100);
  btnCancel->setStyleSheet("font-size: 35px; background-color: #444; border-radius: 10px;");

  QPushButton *btnInstall = new QPushButton("Install");
  btnInstall->setFixedHeight(100);
  btnInstall->setStyleSheet("font-size: 35px; background-color: #007aff; border-radius: 10px;");

  btnLayout->addWidget(btnCancel);
  btnLayout->addWidget(btnInstall);
  branchLayout->addLayout(btnLayout);

  stack->addWidget(branchPage);

  // --- Page 2: Progress ---
  QWidget *progressPage = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout(progressPage);
  layout->setContentsMargins(150, 290, 150, 150);
  layout->setSpacing(0);

  title = new QLabel("Installing " LOADING_MSG);
  title->setStyleSheet("font-size: 90px; font-weight: 600;");
  layout->addWidget(title, 0, Qt::AlignTop);

  layout->addSpacing(170);

  bar = new QProgressBar();
  bar->setRange(0, 100);
  bar->setTextVisible(false);
  bar->setFixedHeight(72);
  layout->addWidget(bar, 0, Qt::AlignTop);

  layout->addSpacing(30);

  val = new QLabel("0%");
  val->setStyleSheet("font-size: 70px; font-weight: 300;");
  layout->addWidget(val, 0, Qt::AlignTop);

  layout->addStretch();
  stack->addWidget(progressPage);

  // --- Logic Wiring ---

  // Default Button
  QObject::connect(btnDefault, &QPushButton::clicked, [=]() {
    stack->setCurrentWidget(progressPage);
    QTimer::singleShot(100, this, &Installer::doInstall);
  });

  // StarPilot Button
  QObject::connect(btnBranch, &QPushButton::clicked, [=]() {
    stack->setCurrentWidget(branchPage);
    branchList->clear();
    branchList->addItem("Loading branches...");

    QProcess *p = new QProcess(this);
    QString url = "https://github.com/firestar5683/StarPilot";
    p->start("git", {"ls-remote", "--heads", url});

    QObject::connect(p, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode) {
      branchList->clear();
      if (exitCode == 0) {
        QString out = p->readAllStandardOutput();
        QStringList lines = out.split('\n');
        for (const QString &line : lines) {
           if (line.isEmpty()) continue;
           QStringList parts = line.split('\t');
           if (parts.size() < 2) continue;
           QString ref = parts[1];
           if (ref.startsWith("refs/heads/")) {
             branchList->addItem(ref.mid(11));
           }
        }
      } else {
        branchList->addItem("Error fetching branches");
      }
      p->deleteLater();
    });
  });

  // Cancel Button
  QObject::connect(btnCancel, &QPushButton::clicked, [=]() {
     stack->setCurrentWidget(introPage);
  });

  // Install Button
  QObject::connect(btnInstall, &QPushButton::clicked, [=]() {
     if (branchList->currentItem()) {
        targetGitUrl = "https://github.com/firestar5683/StarPilot";
        targetBranch = branchList->currentItem()->text();
        stack->setCurrentWidget(progressPage);
        title->setText("Installing " + targetBranch);
        QTimer::singleShot(100, this, &Installer::doInstall);
     }
  });

  QObject::connect(&proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &Installer::cloneFinished);
  QObject::connect(&proc, &QProcess::readyReadStandardError, this, &Installer::readProgress);

  setStyleSheet(R"(
    * {
      font-family: Inter;
      color: white;
      background-color: black;
    }
    QProgressBar {
      border: none;
      background-color: #292929;
    }
    QListWidget {
      border: 1px solid #444;
    }
  )");
}

void Installer::updateProgress(int percent) {
  int h = (int)(lerp(233, 360 + 131, percent / 100.)) % 360;
  int s = lerp(78, 62, percent / 100.);
  int b = lerp(94, 87, percent / 100.);

  bar->setValue(percent);
  bar->setStyleSheet(QString(R"(
    QProgressBar::chunk {
      background-color: hsb(%1, %2%, %3%);
    })").arg(h).arg(s).arg(b));
  val->setText(QString("%1%").arg(percent));
  update();
}

void Installer::doInstall() {
  while (!time_valid()) {
    usleep(500 * 1000);
    qDebug() << "Waiting for valid time";
  }

  run("rm -rf " TMP_INSTALL_PATH " " INSTALL_PATH);

  if (QDir(CACHE_PATH).exists()) {
    cachedFetch();
  } else {
    freshClone();
  }
}

void Installer::freshClone() {
  qDebug() << "Doing fresh clone";
  proc.start("git", {"clone", "--progress", targetGitUrl, "-b", targetBranch,
                     "--depth=1", "--recurse-submodules", TMP_INSTALL_PATH});
}

void Installer::cachedFetch() {
  qDebug() << "Fetching with cache";

  run("cp -rp " CACHE_PATH " " TMP_INSTALL_PATH);
  int err = chdir(TMP_INSTALL_PATH);
  assert(err == 0);
  run(("git remote set-branches --add origin " + targetBranch.toStdString()).c_str());

  updateProgress(10);

  proc.setWorkingDirectory(TMP_INSTALL_PATH);
  proc.start("git", {"fetch", "--progress", "origin", targetBranch});
}

void Installer::readProgress() {
  const QVector<QPair<QString, int>> stages = {
    {"Receiving objects: ", 95},
    {"Filtering content: ", 5},
  };

  auto line = QString(proc.readAllStandardError());

  int base = 0;
  for (const QPair<QString, int> kv : stages) {
    if (line.startsWith(kv.first)) {
      auto perc = line.split(kv.first)[1].split("%")[0];
      int p = base + int(perc.toFloat() / 100. * kv.second);
      updateProgress(p);
      break;
    }
    base += kv.second;
  }
}

void Installer::cloneFinished(int exitCode, QProcess::ExitStatus exitStatus) {
  qDebug() << "git finished with " << exitCode;
  assert(exitCode == 0);

  title->setText("Installation complete");
  updateProgress(100);

  int err = chdir(TMP_INSTALL_PATH);
  assert(err == 0);
  run(("git checkout " + targetBranch.toStdString()).c_str());
  run(("git reset --hard origin/" + targetBranch.toStdString()).c_str());

  run("mv " TMP_INSTALL_PATH " " INSTALL_PATH);

// Embedded continue.sh write logic
  FILE *of = fopen("/data/continue.sh.new", "wb");
  assert(of != NULL);

  size_t num = str_continue_end - str_continue;
  size_t num_written = fwrite(str_continue, 1, num, of);
  assert(num == num_written);
  fclose(of);

  run("chmod +x /data/continue.sh.new");
  run("mv /data/continue.sh.new " CONTINUE_PATH);

  QTimer::singleShot(60 * 1000, &QCoreApplication::quit);
}

int main(int argc, char *argv[]) {
  // Simplest main setup
  QApplication a(argc, argv);
  Installer installer;
  installer.showFullScreen();
  return a.exec();
}
