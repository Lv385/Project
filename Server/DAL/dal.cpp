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
void DAL::UpdateClient(User cl) { //maybe projob
                            // first_user_id is is pending users && second_user_id user
  QVector<UsersID> curr_pend_cl = cl.requests;
  QVector<UsersID> db_pend_cl = users->GetFriendsRequest(cl.id);
  if (curr_pend_cl.size() != db_pend_cl.size() ||
    ((!curr_pend_cl.isEmpty()) && db_pend_cl.last().first_user_id != curr_pend_cl.last().first_user_id)) {//???
    for(int i=0;i<db_pend_cl.size();++i){
      users->DeleteFriendRequest(db_pend_cl[i]); 
    }
    for (int i = 0; i < curr_pend_cl.size(); i++) {
      users->AddFriendRequest(curr_pend_cl.at(i));
    }
  }
  QVector<UsersID> curr_notif_cl=cl.notification;
  QVector<UsersID> db_notif_cl = users->GetFriendsNotification(cl.id);
  if (curr_notif_cl.size() != db_notif_cl.size() ||
    ((!curr_notif_cl.isEmpty()) &&
      db_notif_cl.last().second_user_id != curr_notif_cl.last().second_user_id)) { //??
    for (int i = 0; i < db_notif_cl.size(); ++i) {
      users->DeleteFriendNotification(db_notif_cl[i]);
    }
    for (int i = 0; i < curr_notif_cl.size(); i++) {
      users->AddFriendNotification(curr_notif_cl.at(i));
    }
  }
    //test stage
    QVector<UsersID>curr_friends_cl = cl.friends;
    QVector<UsersID>db_friends_cl = users->GetFriends(cl.id);
    if(curr_friends_cl.size() != db_friends_cl.size()||((!curr_friends_cl.isEmpty())
      &&(db_friends_cl.last().second_user_id!=curr_friends_cl.last().second_user_id))) {
      for (int i = 0; i < db_friends_cl.size(); ++i) {
        users->DeleteFriend(db_friends_cl[i]);
      }
      for (int i = 0; i < curr_friends_cl.size(); i++) {
        users->AddFriend(curr_friends_cl.at(i));
      }
    }
  users->UpdateUser(cl);
}
//DONe
User DAL::getClient(QString login) {

  User usr = users->GetUser(login);
  if (Check_If_Client_exists_In_Db(usr)==false) {
    throw UserNotFound();
  }
  else {
    return usr;
  }
}
//DONe
User DAL::getClient(quint32 i) {
  User u = users->GetUser(i);
  if (Check_If_Client_exists_In_Db(u)==false) {
    throw UserNotFound();
  }
  else {
    return u;
  }
}


bool DAL::Check_If_Client_exists_In_Db(User cl) {

  User user = users->GetUser(cl.login);
  if (user.id != 0)
  {
    return true;
  }else{
    return false;
  }
}

bool DAL::Check_If_Client_exists_In_Db(QString login) {
  User user = users->GetUser(login);
  if (user.id != 0)
  {
    return true;
  }
  else {
    return false;
  }
}
//DONe
int DAL::GetClientId(User cl) {
  User u = users->GetUser(cl.login);
  return u.id;
}
