#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

#include "mainwindow.h"

class GuiManager : public QObject {
  Q_OBJECT

public:
  GuiManager(QObject *parent);
  ~GuiManager();

private:
  // ClientController* client_controller;
  MainWindow* ui_;
};
#endif // !GUIMANAGER_H

