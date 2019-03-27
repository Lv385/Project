#include "localserver.h"
#include "connection.h"

LocalServer::LocalServer(QObject* parent)
    : QTcpServer(parent)
      //remote_server_ip_(remote_server_ip),
      //remote_server_port_(remote_server_port) 
{}


void LocalServer::incomingConnection(qintptr socketDescriptor) {
  QTcpSocket* socket = new QTcpSocket(this);
  socket->setSocketDescriptor(socketDescriptor);
  emit NewConnection(socket);
}
void LocalServer::set_remote_server_ip_port(QHostAddress& remote_server_ip,
                                          quint16& remote_server_port) {
  remote_server_ip_ = remote_server_ip;
  remote_server_port_ = remote_server_port;
}


LocalServer::~LocalServer() {}
