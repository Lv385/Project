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
  //Message mes = {peer_info.id, message};
  //work_manager_->SetWork(static_cast<quint8>(ClientRequest::MESSAGE), peer_info,
  //                       Parser::Message_ToByteArray(mes));
}

void ClientController::LogIn(QString login, QString password)
{
  
}

void ClientController::Register()
{

}

void ClientController::AddFriend()
{
}

void ClientController::DeleteFriend()
{
}

void ClientController::OnFriendRequestRecieved()
{}

void ClientController::OnNewConnection(QTcpSocket *socket) {
  if (socket->peerAddress().isEqual(app_info_.remote_server_ip),
      QHostAddress::TolerantConversion) {
    server_worker_;
  } else {
    BlockReader *reader = new BlockReader(socket);
    connect(reader, SIGNAL(ReadyReadBlock()), &client_worker_,
            SLOT(OnFirstRequestRecieved()));
  }
}

void ClientController::Start()
{
}

void ClientController::Stop()
{
}
