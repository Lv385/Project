#ifndef CLIENTLOGGER_H
#define CLIENTLOGGER_H

#define GET_NAME(name) #name

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <mutex>
#include "D:\Projects\Project\Parser&Structs\parser.h"

enum LogType { ERROR = 0, SUCCESS, INFO, WARNING, DEBUG };
enum LogLevel { NOLOG = 0, LOW, HIGH };

class ClientLogger : public QObject {
  Q_OBJECT

 public:
  static ClientLogger* Instance();

  void WriteLog(LogType type, const QString& msg);
  void set_specific_log(LogType specific_type);
  void set_log_level(LogLevel log_level);
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

  static std::atomic<ClientLogger*> logger_;
  static std::mutex mutex_;

};

#endif
