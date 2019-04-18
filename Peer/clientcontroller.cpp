#include "clientcontroller.h"
#include "signalredirector.h"

ClientController::ClientController(QObject *parent)
    : QObject(parent),
      local_server_(app_info_),
      friend_manager_(app_info_),
      redirector_(SignalRedirector::get_instance()),
      server_manager_(nullptr),
      cache_data_(CacheData::get_instance()) {

  connect(&local_server_, SIGNAL(NewConnection(QTcpSocket *)), this,
          SLOT(OnNewConnection(QTcpSocket *)));

  connect(this, SIGNAL(LoginResult(bool)), this,
          SLOT(OnLogin(bool)));

  redirector_.set_controller(this);

  server_manager_ = new ServerManager(nullptr, app_info_);
  friends_update_manager_ = new FriendsUpdateManager(app_info_);

  connect(friends_update_manager_, SIGNAL(StatusChanged(unsigned, bool)), this,
          SIGNAL(StatusChanged(unsigned, bool)));

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

ClientController::~ClientController() { 
  server_manager_->deleteLater();
}

QVector<Friend> ClientController::LoadFriends() {
  return client_data_.GetFriends();
}

void ClientController::SendMessage(const unsigned& id, const QString& message) {
  Friend friend_info = client_data_.GetFriend(id);
  friend_manager_.SendMessage(friend_info, message);
}

void ClientController::LogIn(const QString& login, const QString& password) {
  LoginInfo info;
  info.id = client_data_.GetIdByLogin(login);   //FIXME: LogIn should work by login(not id)
  info.password = password;
  info.port = app_info_.my_port;

  QByteArray data = Parser::LoginInfo_ToByteArray(info);
  this->Start();
  server_manager_->SendRequest(data);
}

void ClientController::Register(const QString& login,const QString& password) {
  RegisterInfo info;
  info.login = login;
  info.password = password;
  info.port = app_info_.my_port;

  QByteArray data = Parser::RegisterInfo_ToByteArray(info);
  this->Start();
  server_manager_->SendRequest(data);

}

void ClientController::AddFriend(const QString& login) {
  FriendRequestInfo info;
  info.id = app_info_.my_id;
  info.other_login = login;
  info.password = app_info_.my_password;

  QByteArray data = Parser::FriendRequestInfo_ToByteArray(
      info, static_cast<quint8>(ClientRequest::FRIEND_REQUEST));
  server_manager_->SendRequest(data);
}

void ClientController::DeleteFriend(const QString& login) {
  FriendRequestInfo info;
  info.id = app_info_.my_id;
  info.other_login = login;
  info.password = app_info_.my_password;

  QByteArray data = Parser::FriendRequestInfo_ToByteArray(
      info, static_cast<quint8>(ClientRequest::DELETE_REQUEST));
  server_manager_->SendRequest(data);
}

void ClientController::AddMeToDB() {
  client_data_.AddFriend(app_info_.my_id, app_info_.my_login,
                         app_info_.my_ip.toString(),
                         app_info_.my_port);
}

void ClientController::SetAppInfo(ApplicationInfo info) {}

void ClientController::InitNetworkSettings() {
  QSettings settings(k_ini_file_name, QSettings::IniFormat);
  app_info_.remote_server_ip = settings.value("remote_server_ip", k_default_remote_server_ip).toString();
  app_info_.remote_server_port = settings.value("remote_server_port", k_default_remote_server_ip).toInt();
  app_info_.my_port = settings.value("my_port", k_default_my_ip).toInt();
  settings.sync();
}

void ClientController::GetIdByLogin(const QString &login) {
  client_data_.GetIdByLogin(login);
}

QVector<Message> ClientController::LoadMessages(unsigned id) {
  QVector<Message> result = client_data_.GetMessages(id);
  return result;
}

void ClientController::FriendRequestAccepted(const QString& login) {
  FriendRequestInfo info;
  info.id = app_info_.my_id;
  info.other_login = login;
  info.password = app_info_.my_password;

  QByteArray data = Parser::FriendRequestInfo_ToByteArray(
      info, static_cast<quint8>(ClientRequest::FRIENDSHIP_ACCEPTED));
  server_manager_->SendRequest(data);
  FriendRequest request_to_delete{login, RequestForMe};
  client_data_.DeleteRequest(request_to_delete);
}  

void ClientController::FriendRequestRejected(const QString& login) {
  FriendRequestInfo info;
  info.id = app_info_.my_id;
  info.other_login = login;
  info.password = app_info_.my_password;

  QByteArray data = Parser::FriendRequestInfo_ToByteArray(
      info, static_cast<quint8>(ClientRequest::FRIENDSHIP_REJECTED));
  server_manager_->SendRequest(data);
  FriendRequest request_to_delete{login, RequestForMe};
  client_data_.DeleteRequest(request_to_delete);
}

void ClientController::OnLogin(bool logged_in) {
  if(logged_in){
    friends_update_manager_->Start();
  } else{
    this->Stop();
  }
}

void ClientController::OnNewConnection(QTcpSocket *socket) {
  if (socket->peerAddress().isEqual(app_info_.remote_server_ip,
                                    QHostAddress::TolerantConversion)) {
    server_manager_->set_socket(socket);
  } else {
    BlockReader *reader = new BlockReader(socket);
    connect(reader, SIGNAL(ReadyReadBlock()), &friend_manager_,
            SLOT(OnFirstRequestRecieved()));
  }
}

void ClientController::Start() { 
  local_server_.Start();
}

void ClientController::Stop() { 
  local_server_.Stop(); 
}
