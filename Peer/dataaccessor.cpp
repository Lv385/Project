#include "dataaccessor.h"
DataAccessor::DataAccessor(){ 
  user_ = db_.GetEntity<SQLDAL::Friend>();
  message_ = db_.GetEntity<SQLDAL::Message>();
}

DataAccessor::~DataAccessor(){}

QString DataAccessor::GetLoginById(const unsigned user_id) { 
  user_->id = user_id;
  user_->GetFriend();
  return user_->login;
}

QPair<QString, int> DataAccessor::GetIPPort(const unsigned user_id){
  user_->id = user_id;
  user_->GetFriend();
  QPair<QString, unsigned> ip_port{user_->ip, user_->port};
  return ip_port;
}

QVector<SQLDAL::Friend> DataAccessor::GetFriends() { 
  QVector<SQLDAL::Friend> friends = user_->GetFriends();
  return friends;
}

unsigned DataAccessor::GetIDByLogin(const QString user_login){ 
  user_->login = user_login;
  user_->GetFriend();
  return user_->id;
}

unsigned DataAccessor::GetIDByIPPort(const QString ip, const unsigned port) {
  user_->ip = ip;
  user_->port = port;
  user_->GetFriend();
  return user_->id;
}

QVector<SQLDAL::Message> DataAccessor::GetMessages(const QString user_login) {
  message_->chat_id = GetIDByLogin(user_login);
  QVector<SQLDAL::Message> messages = message_->GetMessages();
  return messages;
}

void DataAccessor::SetFriendStatus(const unsigned user_id, const bool status) {
  user_->id = user_id;
  user_->GetFriend();
  user_->status = status;
  user_->UpdateFriend();
}

bool DataAccessor::GetFriendStatus(const unsigned user_id){
  user_->id = user_id;
  user_->GetFriend();
  return user_->status;
}

void DataAccessor::AddMessageToDB(const QString message, const unsigned user_id,
                                const unsigned owner_id) {
  message_->chat_id = user_id;
  message_->owner_id = owner_id;
  message_->data = message;
  message_->date = QDate::currentDate();
  message_->time = QTime::currentTime();
  message_->AddNewMessage();
}

void DataAccessor::UpdateIPPort(const unsigned id, const QString new_ip, const unsigned new_port) {
  user_->id = id;
  user_->GetFriend();
  user_->ip = new_ip;
  user_->port = new_port;
  user_->UpdateFriend();
}
