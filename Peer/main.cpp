
#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"
#include "signalredirector.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
