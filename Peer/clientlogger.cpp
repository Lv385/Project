#include "clientlogger.h"

void ClientLogger::WriteLogToFile(QString file_name, const QString& msg) {

  if (!file_name.isEmpty()) {
    file = new QFile;
    file->setFileName(file_name);
    file->open(QIODevice::Append | QIODevice::Text);
  }
  QString text = msg;
    text = QDateTime::currentDateTime().toString("\ndd.MM.yyyy hh:mm:ss ") + text;

  QTextStream out(file);
  if (file != 0) {
    out << text;
  }
}

void ClientLogger::WriteLogToUi(LogType type,const QString& msg) { 
  emit WriteLog(type, msg);
}
