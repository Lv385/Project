#include "tcpserver.h"
#include "connection.h"

TcpServer::TcpServer(QObject* parent)
    : QTcpServer(parent)
      //remote_server_ip_(remote_server_ip),
      //remote_server_port_(remote_server_port) 
{}


void TcpServer::incomingConnection(qintptr socketDescriptor) {
  Connection* connection = new Connection(socketDescriptor, this);

  if (connection->peerAddress() == remote_server_ip_) {
    emit NewServerConnection(connection);
  } else {
    emit NewConnection(connection);
  }
}
void TcpServer::setRemoteServerIpPort(QHostAddress& remote_server_ip, quint16& remote_server_port) {
  remote_server_ip_ = remote_server_ip;
  remote_server_port_ = remote_server_port;
}


TcpServer::~TcpServer() {}
