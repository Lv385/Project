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
  static ClientLogger* Instance() {
    static ClientLogger logger_; 
    return &logger_;
  }

  void WriteLogToFile(QString, const QString& msg);
  void WriteLogToUi(LogType, const QString& msg);


 signals:
  void WriteLog(LogType,QString msg);

 private:
  QFile* file;
};
#endif