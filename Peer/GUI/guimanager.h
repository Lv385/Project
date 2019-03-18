#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

class GUIManager : public QObject
{
  Q_OBJECT

public:
  GUIManager(QObject *parent = nullptr);

public slots:
  void logIn();
  void logIn2();
};

#endif
