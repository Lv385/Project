#include "dalmanager.h"
DALManager::DALManager()  {

}

DALManager::~DALManager()
{}

QString DALManager::GetLoginById(const unsigned user_id) { 
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->id = user_id;
  user->GetFriend();
  return user->login;
}

QVector<QString> DALManager::GetFriendsLogin(){ 
  auto user = db_.GetEntity<SQLDAL::Friend>();
  QVector<SQLDAL::Friend> friends = user->GetFriends();
  QVector<QString> logins(friends.length());
  for (int i = 0; i < friends.length(); i++) {
    logins[i] = friends[i].login;
  }
  return logins;
}

QPair<QString, int> DALManager::GetIPPort(const unsigned user_id){
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->id = user_id;
  user->GetFriend();
  QPair<QString, unsigned> ip_port{ user->ip, user->port};
  return ip_port;
}

QVector<QString> DALManager::GetFriendsIP(){ 
  auto user = db_.GetEntity<SQLDAL::Friend>();
  QVector<SQLDAL::Friend> friends = user->GetFriends();
  QVector<QString> friends_ip(friends.length());
  for (int i = 0; i < friends.length(); i++) {
    friends_ip[i] = friends[i].ip;
  }
  return friends_ip;
}

unsigned DALManager::GetIDByLogin(const QString user_login){ 
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->login = user_login;
  user->GetFriend();
  return user->id;
}

unsigned DALManager::GetIDByIPPort(const QString ip, const unsigned port) {
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->ip = ip;
  user->port = port;
  user->GetFriend();
  return user->id;
}

QVector<SQLDAL::Message> DALManager::GetMessages(const QString user_login) {
  auto message = db_.GetEntity<SQLDAL::Message>();
  message->chat_id = GetIDByLogin(user_login);
  QVector<SQLDAL::Message> messages = message->GetMessages();
  return messages;
}

void DALManager::SetFriendStatus(const unsigned user_id, const bool status) {
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->id = user_id;
  user->GetFriend();
  user->status = status;
  user->UpdateFriend();
}

bool DALManager::GetFriendStatus(const unsigned user_id){
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->id = user_id;
  user->GetFriend();
  return user->status;
}

void DALManager::AddMessageToDB(const QString message, const unsigned user_id,
                                const unsigned owner_id) {
  auto add_message = db_.GetEntity<SQLDAL::Message>();
  add_message->chat_id = user_id;
  add_message->owner_id = owner_id;
  add_message->data = message;
  add_message->date = QDate::currentDate();
  add_message->time = QTime::currentTime();
  add_message->AddNewMessage();
}

void DALManager::UpdateIPPort(const unsigned id, const QString new_ip, const unsigned new_port) {
  auto user = db_.GetEntity<SQLDAL::Friend>();
  user->id = id;
  user->GetFriend();
  user->ip = new_ip;
  user->port = new_port;
  user->UpdateFriend();
}
