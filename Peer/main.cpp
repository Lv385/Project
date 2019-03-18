
#include <QApplication>
#include <QStyleFactory>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "mainwindow.h"
#include "GUI/guimanager.h"

static const bool kSetQML = 0;

int main(int argc, char* argv[]) {
  if(kSetQML) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    GUIManager guiManager;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("guiManager", &guiManager);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
  } else {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
  }
}
