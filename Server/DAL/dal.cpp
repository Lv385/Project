#include "dal.h"

DAL::DAL() {
  database_.GenerateUniqueConnection();
  users = database_.GetEntity<dal::Users>();
}

DAL::~DAL() {
   // if db connection is closing automatically
   // this destructor useless
  // if no it need to be not empty
}

void DAL::CreateNew(User cl) {
  users->AddNewUser(cl);
}

void DAL::UpdateClient(User cl) { 
                            
  QVector<UsersID> curr_pend_cl = cl.requests;
  QVector<UsersID> db_pend_cl = users->GetFriendsRequest(cl.id);
  if (curr_pend_cl.size() != db_pend_cl.size() ||
    ((!curr_pend_cl.isEmpty()) && db_pend_cl.last().first_user_id != curr_pend_cl.last().first_user_id)) {
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
      db_notif_cl.last().second_user_id != curr_notif_cl.last().second_user_id)) { 
    for (int i = 0; i < db_notif_cl.size(); ++i) {
      users->DeleteFriendNotification(db_notif_cl[i]);
    }
    for (int i = 0; i < curr_notif_cl.size(); i++) {
      users->AddFriendNotification(curr_notif_cl.at(i));
    }
  }
    
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

User DAL::getClient(QString login) {

  User usr = users->GetUser(login);
  if (CheckIfClientExistsInDb(usr) == false) {
    throw UserNotFound();
  }
  else {
    return usr;
  }
}

User DAL::getClient(quint32 i) {
  User u = users->GetUser(i);
  if (CheckIfClientExistsInDb(u) == false) {
    throw UserNotFound();
  }
  else {
    return u;
  }
}


bool DAL::CheckIfClientExistsInDb(User cl) {
  User user = users->GetUser(cl.login);
  return user.id != 0;
}

bool DAL::CheckIfClientExistsInDb(QString login) {
  User user = users->GetUser(login);
  return user.id != 0;
}

bool DAL::CheckIfFriends(User user1, User user2)  // test
{
  if (user1.friends.size() != user2.friends.size())  {
    if (user1.friends.size() > user2.friends.size()) {
      for (int i = 0; i < user2.friends.size(); i++) {
        for (int j = 0; user1.friends.size(); i++)   {
          if (user2.friends[i].second_user_id == user1.friends[j].first_user_id) {
            return true;
          }
        }
         //sort by second user id  1 and 2 and binary search of smaller in bigger  // not implemented
      }
    }
    if (user1.friends.size() < user2.friends.size()) {
      for (int i = 0; i < user1.friends.size(); i++)
      {
        for (int j = 0; user2.friends.size(); i++)
        {
          if (user1.friends[i].second_user_id == user2.friends[j].first_user_id) {
            return true;
          }
        }
      }
    }
  }
  else
  {
    for(int i=0;i<user2.friends.size();i++)
    {
      if(user1.friends[i].first_user_id==user2.friends[i].second_user_id)
      {
        return true;
      }
    }
  }
  return false;
}

int DAL::GetClientId(User cl) {
  User u = users->GetUser(cl.login);
  return u.id;
}
