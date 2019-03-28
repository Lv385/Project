#include "clientcontroller.h"

ClientController::ClientController(QObject *parent)
    : QObject(parent)
  
{
  connect(local_server_, SIGNAL(NewConnection(Connection *)), this,
          SLOT(OnNewConnection(Connection *)));
}

ClientController::~ClientController()
{

}

void ClientController::SendMessage(PeerInfo peer_info, QString message) {
  
}

void ClientController::LogIn(QString login, QString password){
  
}

//void ClientController::Register(){
//
//}
//
//void ClientController::AddFriend(){
//}

void ClientController::DeleteFriend(){
}

void ClientController::OnFriendRequestRecieved(){
}

void ClientController::OnNewConnection(QTcpSocket *socket) {
  if (socket->peerAddress().isEqual(app_info_.remote_server_ip),
      QHostAddress::TolerantConversion) {
    server_manager_;
  } else {
    BlockReader *reader = new BlockReader(socket);
    connect(reader, SIGNAL(ReadyReadBlock()), &friend_manager_,
            SLOT(OnFirstRequestRecieved()));
  }
}

void ClientController::Start()
{
}

void ClientController::Stop()
{
}
