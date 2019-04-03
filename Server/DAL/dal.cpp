#include "dal.h"
//done
DAL::DAL() {
  database_.GenerateUniqueConnection();
  users = database_.GetEntity<SQLDAL::Users>();
}
//DONE
DAL::~DAL() {
   // if db connection is closing automatically
   // this destructor useless
  // if no it need to be not empty
}
//Done
void DAL::CreateNew(User cl) {
  users->AddNewUser(cl);
}
//done
void DAL::UpdateClient(User cl) {
  //form ->change ->update
  //get ->change -> update                               // first_user_id is user && second_user_id is pending users
  QVector<UsersID> curr_pend_cl = cl.requests;
  QVector<UsersID> db_pend_cl = users->GetFriendsRequest(cl.id);
  if (curr_pend_cl.size() != db_pend_cl.size() ||
    ((!curr_pend_cl.isEmpty()) && db_pend_cl.last().second_user_id != curr_pend_cl.last().second_user_id)) {//???
    for(int i=0;i<db_pend_cl.size();++i){
      users->DeleteFriendRequest(db_pend_cl[i]); //questionable  all update whould be tested
    }
    for (int i = 0; i < curr_pend_cl.size(); i++) {
      users->AddFriendRequest(curr_pend_cl.at(i));
    }
  }
  QVector<UsersID> curr_notif_cl=cl.notification;
  QVector<UsersID> db_notif_cl = users->GetFriendsNotification(cl.id);
  if (curr_notif_cl.size() != db_notif_cl.size() ||
    ((!curr_notif_cl.isEmpty()) &&
      db_notif_cl.last().second_user_id != curr_notif_cl.last().second_user_id)) { //?
    for (int i = 0; i < db_notif_cl.size(); ++i) {
      users->DeleteFriendNotification(db_notif_cl[i]);//questionable  all update whould be tested
    }
    for (int i = 0; i < curr_notif_cl.size(); i++) {
      users->AddFriendNotification(curr_notif_cl.at(i));
    }
  }

  users->UpdateUser(cl);
}
//DONe
User DAL::getClient(QString login) {
  /*if (id == 0) {
    throw UserNotFound();
  }*/
  User usr = users->GetUser(login);
  return usr;
}
//DONe
User DAL::getClient(quint32 i) {
  /*if (id == 0) {
    throw UserNotFound();
  }*/
  User u = users->GetUser(i);
  return u;
}


bool DAL::Check_If_Client_exists_In_Db(User cl) {
  //if (database_.GetIDByLogin(cl.GetUserName()) == 0) {  // If login don't exist return id = 0
  //  return false;  // login dont exist

  //} else {
  //  return true;  // login exist
  //}
  return true;

}

bool DAL::Check_If_Client_exists_In_Db(QString login) {
  //return !(database_.GetIDByLogin(login) == 0); // according to mentor recomendations
  return true;
}
//DONe
int DAL::GetClientId(User cl) {
  User u = users->GetUser(cl.login);
  return u.id;
}
