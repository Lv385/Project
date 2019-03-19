#include "clientlogger.h"

ClientLogger* ClientLogger::Instance() {
  static ClientLogger logger_; 
    return &logger_;
}
const char* ErrorValueNames[] = {GET_NAME(ERROR), GET_NAME(SUCCESS),
                                 GET_NAME(INFO), GET_NAME(WARNING), GET_NAME(DEBUG)};

ClientLogger::ClientLogger() {
  specific_log_ = false;
  if (!file_) {
    file_ = new QFile("Log.txt");
    file_->open(QIODevice::Append | QIODevice::Text);
  }
}
void ClientLogger::WriteLog(LogType type, const QString& msg) { 
  QString text;
  if(specific_log_ && type == specific_type_){
    text = tr("[%1] %2 |")
      .arg(ErrorValueNames[type])
      .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")) + msg + '\n';
  }
  if(!specific_log_){
    text = tr("[%1] %2 |")
      .arg(ErrorValueNames[type])
      .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ")) + msg + '\n';
  }
  QTextStream out(file_);
  if (file_) {
    out << text;
  }
  emit DisplayLog(ErrorValueNames[type], msg);
}

void ClientLogger::SetSpecificLog(LogType specific_type) {
  specific_log_ = true;
  specific_type_ = specific_type;

}

