#include "localserver.h"
#include "connection.h"

LocalServer::LocalServer(ApplicationInfo& app_info)
    : app_info_(app_info),
      logger_(ClientLogger::Instance()){}


void LocalServer::incomingConnection(qintptr socketDescriptor) {
  QTcpSocket* socket = new QTcpSocket(this);
  socket->setSocketDescriptor(socketDescriptor);
  emit NewConnection(socket);
}

bool LocalServer::Start() {
  QString log; 
  if (!this->listen(QHostAddress::Any, app_info_.my_port))
  {
    if(!this->listen()) {
      log += "Failed to start on" + QString::number(this->serverPort());
      return false;
    } else {
      app_info_.my_port = this->serverPort();
    
    }
  }
  log = "Started on ";
  log += QString::number(this->serverPort());
  logger_->WriteLog(SUCCESS, log);
  return true;
}

void LocalServer::Stop() { 
  logger_->WriteLog(SUCCESS, "Stop listening on" + QString::number(this->serverPort()));
  this->close();
}

LocalServer::~LocalServer() {}
