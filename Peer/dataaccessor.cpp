#include "dataaccessor.h"

DataAccessor::DataAccessor(){
  db_.GenerateUniqueConnection();
  user_ = db_.GetEntity<dal::Friends>();
  message_ = db_.GetEntity<dal::Messages>();
  friend_requests_ = db_.GetEntity<dal::FriendRequests>();
}

DataAccessor::~DataAccessor(){}

QString DataAccessor::GetLoginById(const unsigned& user_id) { 
  Friend client_friend = user_->GetFriend(user_id);
  return client_friend.login;
}

QPair<QString, int> DataAccessor::GetIpPort(const unsigned& user_id){
  Friend client_friend = user_->GetFriend(user_id);
  QPair<QString, unsigned> ip_port{client_friend.ip, client_friend.port};
  return ip_port;
}

QVector<Friend> DataAccessor::GetFriends() { 
  QVector<Friend> client_friend = user_->GetFriends();
  return client_friend;
}

Friend DataAccessor::GetFriend(const unsigned& user_id) {
  return user_->GetFriend(user_id);
}

unsigned DataAccessor::GetIdByLogin(const QString& user_login) {
  Friend client_friend = user_->GetFriend(user_login);
  return client_friend.id;
}

QVector<Message> DataAccessor::GetMessages(const QString& user_login) {
  QVector<Message> messages = message_->GetMessages(user_login);
  return messages;
}

QVector<Message> DataAccessor::GetMessages(const unsigned& user_id) {
  QVector<Message> messages = message_->GetMessages(user_id);
  return messages;
}

void DataAccessor::SetFriendStatus(const unsigned& user_id, const bool& status) {
  Friend client_friend = user_->GetFriend(user_id);
  client_friend.status = status;
  user_->UpdateFriend(client_friend);
}

bool DataAccessor::GetFriendsStatus(const unsigned& user_id){
  Friend client_friend = user_->GetFriend(user_id);
  return client_friend.status;
}

void DataAccessor::AddFriend(const Friend& friend_info) {
  user_->AddNewFriend(friend_info);
}

void DataAccessor::AddFriend(const unsigned& user_id, const QString& login,
                             const QString& ip, const unsigned& port,
                             const QString& name, const QString& surname) {
  user_->AddNewFriend(Friend{user_id, login, ip, port, name, surname});
}

void DataAccessor::AddMessageToDB(const QString& msg, const unsigned& user_id,
                                  const unsigned& owner_id) {
  Message message;

  message.chat_id = user_id;
  message.owner_id = owner_id;
  message.data = msg;
  message.date = QDate::currentDate();
  message.time = QTime::currentTime();
  message_->AddNewMessage(message);
}

void DataAccessor::AddMessageToDB(const Message& message) {
  message_->AddNewMessage(message);
}

void DataAccessor::SaveRequest(const FriendRequest& friend_request) {
  friend_requests_->Add(friend_request);
}

QVector<FriendRequest> DataAccessor::GetRequests() { 
  return friend_requests_->Get();
}

void DataAccessor::DeleteRequest(const FriendRequest& friend_request) {
  if(friend_requests_->IsExist(friend_request)){
    friend_requests_->Delete(friend_request);
  }
}

void DataAccessor::UpdateIPPort(const unsigned& user_id, const QString& new_ip,
                                const unsigned& new_port) {
  Friend client_friend = user_->GetFriend(user_id);
  client_friend.ip = new_ip;
  client_friend.port = new_port;
  user_->UpdateFriend(client_friend);
}
