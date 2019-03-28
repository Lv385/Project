#include "localserver.h"
#include "connection.h"

LocalServer::LocalServer(ApplicationInfo& app_info)
    : app_info_(app_info)
      //remote_server_ip_(remote_server_ip),
      //remote_server_port_(remote_server_port) 
{}


void LocalServer::incomingConnection(qintptr socketDescriptor) {
  QTcpSocket* socket = new QTcpSocket(this);
  socket->setSocketDescriptor(socketDescriptor);
  emit NewConnection(socket);
}
//void LocalServer::set_remote_server_ip_port(QHostAddress& remote_server_ip,
//                                          quint16& remote_server_port) {
//  app = remote_server_ip;
//  remote_server_port_ = remote_server_port;
//}

bool LocalServer::Start() {
  if (!this->listen(QHostAddress::Any, app_info_.my_port))
  {
    if(!this->listen())
    { return false;
    } else {
      app_info_.my_port = this->serverPort();
    
    }
  }
  return true;
}

LocalServer::~LocalServer() {}
