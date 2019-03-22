#include "dal.h"

DAL::DAL() {
  QUuid uuid;
  connection_name_ = uuid.createUuid().toString();
  database_.NewConnection(connection_name_);
}

DAL::~DAL() { database_.CloseConncetion(connection_name_); }

void DAL::CreateNew(Client cl) {
  // this function is only for new user request (register)
  database_.AddNewUser(cl.GetUserName(), cl.GetUserPassword());
  database_.UpdateIPPort(cl.GetUserName(), cl.GetUserIp().toString(),
                         (int)cl.GetUserPort());
}


void DAL::UpdateClient(Client cl) {
  //  this is used when login   and MAYBE  when adding to friend
  database_.UpdateIPPort(cl.GetUserName(), cl.GetUserIp().toString(),(int)cl.GetUserPort());  
  QVector<unsigned int> curr_pend_cl = cl.Get_Pending_Requests();
  QVector<unsigned int> db_pend_cl = database_.GetPendingFriendRequests(cl.GetUserId());
  if (curr_pend_cl.size() != db_pend_cl.size() ||
      ((!curr_pend_cl.isEmpty()) && db_pend_cl.last() != curr_pend_cl.last())) {
    database_.DeleteAllPendingRequest(cl.GetUserId());
    for (int i = 0; i < curr_pend_cl.size(); i++) {
      database_.addPendingFriendRequest(cl.GetUserId(), curr_pend_cl.at(i));
    }
  }
  QVector<unsigned int> curr_notif_cl = cl.Get_Pending_Notifications();
  QVector<unsigned int> db_notif_cl = database_.GetPendingNotification(cl.GetUserId());
  if (curr_notif_cl.size() != db_notif_cl.size() ||
      ((!curr_notif_cl.isEmpty()) &&
       db_notif_cl.last() != curr_notif_cl.last())) {
    database_.DeleteAllPendingNotifications(cl.GetUserId());
    for (int i = 0; i < curr_notif_cl.size(); i++) {
      database_.addPendingNotification(cl.GetUserId(), curr_notif_cl.at(i));
    }
  }
  
}
Client DAL::getClient(QString login) {
  unsigned int id = database_.GetIDByLogin(login);
  if (id == 0) {
    throw UserNotFound();
  }
  Client toReturn;
  toReturn.SetUserId(id);
  toReturn.SetUserIp(QHostAddress(database_.GetIPPort(id).first));
  toReturn.SetUserPort((quint16)database_.GetIPPort(id).second);
  toReturn.SetUserName(database_.GetLoginByID(id));
  toReturn.SetUserPassword(database_.GetPasswordById(id));
  toReturn.SetFriends(database_.GetFriends(id));
  toReturn.Set_Pending_Request(database_.GetPendingFriendRequests(id));
  toReturn.Set_Pending_Noification(database_.GetPendingNotification(id));
  return toReturn;
}

Client DAL::getClient(quint32 i) {
  return getClient(database_.GetLoginByID(i));
}

bool DAL::Check_If_Client_exists_In_Db(Client cl) {
  if (database_.GetIDByLogin(cl.GetUserName()) ==
      0) {  // If login don't exist return id = 0

    return false;  // login dont exist

  } else {
    return true;  // login exist
  }
}

bool DAL::Check_If_Client_exists_In_Db(QString login) {
  if (database_.GetIDByLogin(login) == 0) {  // If login don't exist return id = 0

    return false;  // login dont exist

  } else {
    return true;  // login exist
  }
  return false;
}

int DAL::GetClientId(Client cl) {
  return database_.GetIDByLogin(cl.GetUserName());
}
