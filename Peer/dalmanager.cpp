#include "dalmanager.h"
DALManager::DALManager()  {

}

DALManager::~DALManager()
{}

QString DALManager::GetLoginById(const unsigned user_id) const { 
  ClientDAL::ClientDB cdb;
  return cdb.GetLoginById(user_id); 
}

QVector<QString> DALManager::GetFriendsLogin() const { 
  ClientDAL::ClientDB cdb;
  return cdb.GetFriendsLogin(); 
}

QPair<QString, int> DALManager::GetIPPort(const unsigned user_id) const {
  ClientDAL::ClientDB cdb;
  return cdb.GetIPPort(user_id);
}

QVector<QString> DALManager::GetFriendsIP() const { 
  ClientDAL::ClientDB cdb;
  return cdb.GetFriendsIp(); 
}

unsigned DALManager::GetIDByLogin(const QString user_login) const { 
  ClientDAL::ClientDB cdb;
  return cdb.GetIDByLogin(user_login); 
}

unsigned DALManager::GetIDByIPPort(const QString ip, const unsigned port) const { 
  ClientDAL::ClientDB cdb;
  return cdb.GetIDByIpPort(ip,port);
}

QVector<ClientDAL::Message> DALManager::GetMessages(const QString user_login) const {
  ClientDAL::ClientDB cdb;
  return cdb.GetMessages(user_login);
}

void DALManager::SetFriendStatus(const unsigned user_id, const bool status) {
  ClientDAL::ClientDB cdb;
  cdb.SetFriendStatus(user_id, status);
}

bool DALManager::GetFriendStatus(const unsigned user_id)
{
  ClientDAL::ClientDB cdb;
  return cdb.GetFriendStatus(user_id);
}

void DALManager::AddMessageToDB(const QString message, const unsigned user_id,
                                const unsigned owner_id) {
  ClientDAL::ClientDB cdb;
  ClientDAL::Message msg;
  msg.data = message;
  msg.owner_id = owner_id;
  msg.date = QDate::currentDate();
  msg.time = QTime::currentTime();
  cdb.AddMessage(msg, user_id);
}

void DALManager::UpdateIPPort(const unsigned id, const QString new_ip,  const unsigned new_port) {
  ClientDAL::ClientDB cdb;
  cdb.UpdateIPPort(id, new_ip, new_port);
}
