#include "clientlogger.h"

ClientLogger* ClientLogger::Instance() {
  static ClientLogger logger_; 
    return &logger_;
}
const char* ErrorValueNames[] = {GET_NAME(ERROR), GET_NAME(SUCCESS),
                                 GET_NAME(INFO), GET_NAME(WARNING), GET_NAME(DEBUG)};

ClientLogger::ClientLogger() {
  specific_log_ = false;
  log_level_ = LogLevel::NOLOG;
  if (!file_) {
    file_ = new QFile("Log.txt");
    file_->open(QIODevice::Append | QIODevice::Text);
  }
}
void ClientLogger::WriteLog(LogType type, const QString& msg) { 
  QString text;
  QString log = '\t' + QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ") + msg + '\n'; 

  if (!log_level_) return;

  if(specific_log_ && type == specific_type_){
    text = tr("[%1] %2 ").arg(ErrorValueNames[type]).arg(log);
  }
  if(!specific_log_ && log_level_ == LogLevel::LOW){           // low level of logs
    if (type == LogType::ERROR || type == LogType::WARNING){
      return;
    }else {
      text = tr("[%1] %2 ").arg(ErrorValueNames[type]).arg(log);
    }
  }else{
    text = tr("[%1] %2 ").arg(ErrorValueNames[type]).arg(log);
  }
  QTextStream out(file_);
  if (file_) {
    out << text;
  }
  emit DisplayLog(ErrorValueNames[type], msg);
}

void ClientLogger::set_specific_log(LogType specific_type) {
  specific_log_ = true;
  specific_type_ = specific_type;
}

void ClientLogger::set_log_level(LogLevel log_level) { 
  log_level_ = log_level; 
}

