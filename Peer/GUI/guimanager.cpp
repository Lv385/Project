#include "guimanager.h"

#include <chrono>
#include <thread>
#include <QtConcurrent>

GUIManager::GUIManager(QObject *parent)
    : QObject(parent) {
}


void GUIManager::logIn() {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  qDebug() << "Hello from c++";
}

void GUIManager::logIn2()
{
  QtConcurrent::run(this, &GUIManager::logIn);
}
