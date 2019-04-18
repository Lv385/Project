
#include <QApplication>
#include <QStyleFactory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include "GUI/guimanager.h"
#include "GUI/friendmodel.h"
#include "GUI/frienditem.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/MesX_logo2.png"));

  GUIManager guiManager;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("guiManager", &guiManager);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
      return -1;

  return app.exec();
}
