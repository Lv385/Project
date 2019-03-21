#ifndef CLIENTLOGGER_H
#define CLIENTLOGGER_H

#define GET_NAME(name) #name

#include <QDateTime>
#include <QObject>
#include <QPlainTextEdit>
#include <QTextStream>

enum LogType { ERROR = 0, SUCCESS, INFO, WARNING, DEBUG };
enum LogLevel {NOLOG= 0, LOW, HIGH};

class ClientLogger : public QObject {
  Q_OBJECT

 public:
  static ClientLogger* Instance();

  void WriteLog(LogType type, const QString& msg);
  void SetSpecificLog(LogType specific_type);
  void SetLogLevel(LogLevel log_level);
 signals:
  void DisplayLog(const char*, QString msg);

 private:
  ClientLogger();
  ClientLogger(ClientLogger const&) = delete;
  void operator=(ClientLogger const&) = delete;

 private:
  QFile* file_;
  bool specific_log_;
  LogType specific_type_;
  LogLevel log_level_;
};
#endif
