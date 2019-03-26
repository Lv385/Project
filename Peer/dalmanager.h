#ifndef DALLMENEGER_H
#define DALLMENEGER_H

#include "../DAL/Client/clientdb.h"
#include "../Parser&Structs/request_types.h"

class DALManager {
 public:
  DALManager();
  ~DALManager();

  QString GetLoginById(const unsigned user_id) const;
  QVector<QString> GetFriendsLogin() const;
  QPair<QString, int> GetIPPort(const unsigned user_id) const;
  QVector<QString> GetFriendsIP() const;
  unsigned GetIDByLogin(const QString user_login) const;
  unsigned GetIDByIPPort(const QString ip, const unsigned port) const;
  QVector<ClientDAL::Message> GetMessages(const QString user_login) const;


  void SetFriendStatus(const unsigned user_id, const bool status);

  void AddMessageToDB(const QString message, const unsigned user_id, const unsigned owner_id);
  void UpdateIPPort(const unsigned id, const QString new_ip, const unsigned new_port);

  
  };
  #endif