#include "dataaccessor.h"
DataAccessor::DataAccessor(){ 
  user_ = db_.GetEntity<SQLDAL::Friend>();
  message_ = db_.GetEntity<SQLDAL::Message>();
}

DataAccessor::~DataAccessor(){}

QString DataAccessor::get_login_by_id(const unsigned user_id) { 
  user_->id = user_id;
  user_->GetFriend();
  return user_->login;
}

QPair<QString, int> DataAccessor::get_ip_port(const unsigned user_id){
  user_->id = user_id;
  user_->GetFriend();
  QPair<QString, unsigned> ip_port{user_->ip, user_->port};
  return ip_port;
}

QVector<SQLDAL::Friend> DataAccessor::get_friends() { 
  QVector<SQLDAL::Friend> friends = user_->GetFriends();
  return friends;
}

unsigned DataAccessor::get_id_by_login(const QString user_login){ 
  user_->login = user_login;
  user_->GetFriend();
  return user_->id;
}

unsigned DataAccessor::get_id_by_ip_port(const QString ip, const unsigned port) {
  user_->ip = ip;
  user_->port = port;
  user_->GetFriend();
  return user_->id;
}

QVector<SQLDAL::Message> DataAccessor::get_messages(const QString user_login) {
  message_->chat_id = get_id_by_login(user_login);
  QVector<SQLDAL::Message> messages = message_->GetMessages();
  return messages;
}

void DataAccessor::set_friend_status(const unsigned user_id, const bool status) {
  user_->id = user_id;
  user_->GetFriend();
  user_->status = status;
  user_->UpdateFriend();
}

bool DataAccessor::get_friends_status(const unsigned user_id){
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
