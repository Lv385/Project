#include "clientcontroller.h"

ClientController::ClientController(QObject *parent)
    : QObject(parent), 
      local_server_(app_info_), 
      friend_manager_(app_info_),
      server_manager_(nullptr, app_info_),
      cache_data_(CacheData::get_instance())
{
  connect(&local_server_, SIGNAL(NewConnection(QTcpSocket* )), this,
          SLOT(OnNewConnection(QTcpSocket *)));
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i) {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
        ipAddressesList.at(i).toIPv4Address()) {
      app_info_.my_ip = ipAddressesList.at(i);
      break;
    }
  }
  // if we did not find one, use IPv4 localhost
  if (app_info_.my_ip.toString().isEmpty())
    app_info_.my_ip = QHostAddress(QHostAddress::LocalHost);
}

ClientController::~ClientController() {}

QVector<PeerInfo> ClientController::LoadFriends() {
  QVector<SQLDAL::Friend> friends = client_data_.get_friends();
  QVector<PeerInfo> result;
  PeerInfo info;
  for (auto a : friends) {
    info.id = a.id;
    info.ip = a.ip;
    info.is_online = a.status;
    info.port = a.port;
    info.login = a.login;
    result.push_back(info);
  }
  return result;
}

void ClientController::SendMessage(PeerInfo peer_info, QString message) {
  friend_manager_.SendMessage(peer_info, message);
}

void ClientController::LogIn(QString login, QString password) {
  LoginInfo info;
  info.id = client_data_.get_id_by_login(login);
  info.password = password;
  info.port = app_info_.my_port;

  QByteArray data = Parser::LoginInfo_ToByteArray(info);

  server_manager_.SendRequest(data);
}

void ClientController::Register(QString login, QString password) {
  RegisterInfo info;
  info.login = login;
  info.password = password;
  info.port = app_info_.my_port;

  QByteArray data = Parser::RegisterInfo_ToByteArray(info);

  server_manager_.SendRequest(data);
}

void ClientController::AddFriend(QString login) {
  FriendRequestInfo info;
  info.id = app_info_.my_id;
  info.other_login = login;
  info.password = app_info_.my_password;

  QByteArray data = Parser::FriendRequestInfo_ToByteArray(
      info, static_cast<quint8>(ClientRequest::FRIEND_REQUEST));
  server_manager_.SendRequest(data);
}

void ClientController::SetAppInfo(ApplicationInfo info) {}

QVector<SQLDAL::Message> ClientController::LoadMessages(unsigned id) {

  QVector<SQLDAL::Message> result = client_data_.get_messages(id);
  return result;
}

void ClientController::OnFriendRequestRecieved() {}

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

void ClientController::Start() { 
  local_server_.Start(); 
}

void ClientController::Stop() {}
