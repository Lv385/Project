#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataaccessor.h"
#include "peer.h"
#include "clientcontroller.h"

#include "clientlogger.h"

#include <QComboBox>
#include <QMainWindow>
#include <QRegExpValidator>
#include <QShortcut>
#include <QVector>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);

  void SetIpValidator();

  ~MainWindow();

 private slots:
  void AppendMessage(QString);
  void AppendHistory();
  void AppendLogMessage(const char*,QString);

  void OnPbStartClicker();
  void OnPbLoginClicked();
  void OnPbSendClicked();
  void OnRbSimpleClicked();
  void OnRbEngineeringClicked();



 private:
  Ui::MainWindow* ui_;
  Peer* peer_;
  DataAccessor client_data_;
  ClientLogger* logger_;
};

#endif  // MAINWINDOW_H
