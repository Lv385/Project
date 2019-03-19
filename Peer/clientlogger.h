#ifndef CLIENTLOGGER_H
#define CLIENTLOGGER_H

#define GET_NAME(name) #name
#include <iomanip>
#include <QDateTime>
#include <QObject>
#include <QPlainTextEdit>
#include <QTextStream>

enum LogType { ERROR = 0, SUCCESS, INFO, WARNING, DEBUG };

class ClientLogger : public QObject {
  Q_OBJECT

 public:
  static ClientLogger* Instance();

  void WriteLog(LogType type, const QString& msg);

 signals:
  void DisplayLog(const char*, QString msg);

 private:
  ClientLogger();
  ClientLogger(ClientLogger const&) = delete;
  void operator=(ClientLogger const&) = delete;

 private:
  QFile* file_;
};
#endif