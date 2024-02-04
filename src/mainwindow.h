#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include "QString"
#include "engine.h"
#include <QMainWindow>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QShortcut>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void load(QString path);

public slots:
  void update();
  void sliderMoved(int val);
  void togglePlay();
  void showToggleContextMenu(const QPoint &pos);
  void fastForward();
  void fastBackward();
  void next();
  void previous();
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void openSettingsWindow();
  void openFileDialog();
  void openSkipToTimeDialog();
  void activateNextClickCounts();
  void next5Sec();
  void previous5Sec();

protected:
  void paintEvent(QPaintEvent *event);

private:
  Ui::MainWindow *ui;

private:
  void dragEnterEvent(QDragEnterEvent *e);
  void dragMoveEvent();
  void dropEvent(QDropEvent *e);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void enterEvent(QEvent *event);
  void leaveEvent(QEvent *event);
  void resizeEvent(QResizeEvent *event);

  void loadPosAndSize();
  void loadPref();
  void setup();
  void enableControls();
  void setPlay(bool play);
  QString getSubtitle(bool sliderMoved);
  QString getEncoding(QString preset);
  QString promptForEncoding(QStringList codecNames, int recommendIndex);
  void adjustTime(long long interval);
  long long getAdjustInterval();

private:
  int m_nMouseClick_X_Coordinate;
  int m_nMouseClick_Y_Coordinate;
  long long int currentTime = 0LL;
  double speedFactor = 1.0;
  double intervalRemainder = 0; // for speed factor
  const long long int INTERVAL = 200LL;
  const long long int SLIDER_RATIO = 1000LL;
  Engine *engine = 0;
  QTimer *timer = 0;
  bool isPlaying = false;
  QMenu *menu = 0;
  QSettings settings;
  bool skipped = false;

  std::unique_ptr<QShortcut> m_ShortcutTogglePlay{nullptr};
  std::unique_ptr<QShortcut> m_ShortcutNext5Sec{nullptr};
  std::unique_ptr<QShortcut> m_ShortcutPrevious5Sec{nullptr};
};

#endif // MAINWINDOW_H
