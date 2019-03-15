#include "tcpserver.h"
#include "connection.h"

TcpServer::TcpServer(QObject* parent)
    : QTcpServer(parent)
      //remote_server_ip_(remote_server_ip),
      //remote_server_port_(remote_server_port) 
{}


void TcpServer::incomingConnection(qintptr socketDescriptor) {
  Connection* connection = new Connection(socketDescriptor, this);
 
  if (connection->peerAddress().isEqual(remote_server_ip_, QHostAddress::TolerantConversion)) {
    emit NewServerConnection(connection);
  } else {
    emit NewConnection(connection);
  }
}
void TcpServer::set_remote_server_ip_port(QHostAddress& remote_server_ip,
                                          quint16& remote_server_port) {
  remote_server_ip_ = remote_server_ip;
  remote_server_port_ = remote_server_port;
}


TcpServer::~TcpServer() {}
