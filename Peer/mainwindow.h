#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dalmanager.h"
#include "peer.h"
#include "clientcontroller.h"

#include <QComboBox>
#include <QMainWindow>
#include <qmainwindow.h>
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
  void AppendLogMessage(QString);

  void OnPbStartClicker();
  void OnPbLoginClicked();
  void OnPbSendClicked();
  void OnRbSimpleClicked();
  void OnRbEngineeringClicked();



 private:
  Ui::MainWindow* ui_;
  //Peer* peer_;
  DALManager client_dal_;
  ClientController* client_controller_;
};

#endif  // MAINWINDOW_H
