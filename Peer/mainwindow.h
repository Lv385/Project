#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clientcontroller.h"
#include "clientlogger.h"
#include "dataaccessor.h"
#include "peer.h"
#include "signalredirector.h"
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
  void AppendHistory(QString);
  void AppendLogMessage(const char*, QString);

  void OnPbStartClicked();
  void OnPbStopClicked();

  void OnPbLoginClicked();
  void OnPbSendClicked();
  //void OnPbRegisterclicked();

  void OnRbSimpleClicked();
  void OnRbEngineeringClicked();

  void OnMessageRecieved(unsigned id);

 private:
  Ui::MainWindow* ui_;
  //  Peer* peer_;
  DataAccessor client_data_;
  ClientLogger* logger_;
  ClientController* client_controller_;
  QVector<PeerInfo> friends_;
};

#endif  // MAINWINDOW_H
