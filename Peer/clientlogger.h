#ifndef CLIENTLOGGER_H
#define CLIENTLOGGER_H

#define stringify(name) #name

#include <QDateTime>
#include <QObject>
#include <QPlainTextEdit>
#include <QTextStream>

enum LogType { 
  ERROR = 0, 
  SUCCESS,
  INFO,
  WARNING
};
class ClientLogger : public QObject {
  Q_OBJECT

 public:
  static ClientLogger* Instance();
  void WriteLog(LogType type, const QString& msg);

 signals:
  void DisplayLog(const char* ,QString msg);

 private:
  QFile* file_;
};
#endif