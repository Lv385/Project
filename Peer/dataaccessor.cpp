#include "dataaccessor.h"

DataAccessor::DataAccessor(){
  db_.GenerateUniqueConnection();
  user_ = db_.GetEntity<SQLDAL::Friends>();
  message_ = db_.GetEntity<SQLDAL::Messages>();
}

DataAccessor::~DataAccessor(){}

QString DataAccessor::get_login_by_id(const unsigned user_id) { 
  Friend client_friend = user_->GetFriend(user_id);
  return client_friend.login;
}

QPair<QString, int> DataAccessor::get_ip_port(const unsigned user_id){
  Friend client_friend = user_->GetFriend(user_id);
  QPair<QString, unsigned> ip_port{client_friend.ip, client_friend.port};
  return ip_port;
}

QVector<Friend> DataAccessor::get_friends() { 
  QVector<Friend> client_friend = user_->GetFriends();
  return client_friend;
}


unsigned DataAccessor::get_id_by_login(const QString user_login){
  Friend client_friend = user_->GetFriend(user_login);
  return client_friend.id;
}
/*unsigned DataAccessor::get_id_by_ip_port(const QString ip, const unsigned port) {
  user_->id = 0;
  user_->login = "";
  user_->ip = ip;
  user_->port = port;
  user_->GetFriend();
  return user_->id;
}*/

QVector<Message> DataAccessor::get_messages(const QString user_login) {
  Friend f = user_->GetFriend(user_login);
  QVector<Message> messages = message_->GetMessages(f.id);
  return messages;
}

QVector<Message> DataAccessor::get_messages(unsigned user_id) {
  QVector<Message> messages = message_->GetMessages(user_id);
  return messages;
}

void DataAccessor::set_friend_status(const unsigned user_id, const bool status) {
  Friend client_friend = user_->GetFriend(user_id);
  client_friend.status = status;
  user_->UpdateFriend(client_friend);
}

bool DataAccessor::get_friends_status(const unsigned user_id){
  Friend client_friend = user_->GetFriend(user_id);
  return client_friend.status;
}

void DataAccessor::AddMessageToDB(const QString msg, const unsigned user_id,
                                const unsigned owner_id) {
  Message message;

  message.chat_id = user_id;
  message.owner_id = owner_id;
  message.data = msg;
  message.date = QDate::currentDate().toString("yyyy-MM-dd");
  message.time = QTime::currentTime();
  message_->AddNewMessage(message);
}

void DataAccessor::UpdateIPPort(const unsigned user_id, const QString new_ip, const unsigned new_port) {
  Friend client_friend = user_->GetFriend(user_id);
  client_friend.ip = new_ip;
  client_friend.port = new_port;
  user_->UpdateFriend(client_friend);
}
