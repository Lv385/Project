#include "clientlogger.h"

//std::atomic<ClientLogger*> ClientLogger::logger_ = nullptr;
std::mutex ClientLogger::mutex_;
ClientLogger* ClientLogger::logger_ = nullptr;

ClientLogger* ClientLogger::Instance() {
  std::lock_guard<std::mutex> lock(mutex_);
    if(logger_ == nullptr){
      logger_ = new ClientLogger();
    }
  return logger_;
}
const char* ErrorValueNames[] = {GET_NAME(ERROR), GET_NAME(SUCCESS),
                                 GET_NAME(INFO), GET_NAME(WARNING), GET_NAME(DEBUG)};

ClientLogger::ClientLogger()
  : file_(new QFile("Log.txt")){
  file_->open(QIODevice::Append | QIODevice::Text);
  specific_log_ = false;
  log_level_ = LogLevel::NOLOG;
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
  std::lock_guard<std::mutex> lock(mutex_);
  QTextStream out(file_);
  if (file_ && file_->size() < kMaxFileSize) {
    out << text;
  } else{
    file_->resize(0);
    out << text;
  }
}

void ClientLogger::set_specific_log(LogType specific_type) {
  specific_log_ = true;
  specific_type_ = specific_type;
}

void ClientLogger::set_log_level(LogLevel log_level) { 
  log_level_ = log_level; 
}

