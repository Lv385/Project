#include "guimanager.h"

GUIManager::GUIManager(QObject *parent)
    : QObject(parent),
      my_id(1) {     //for testing

  LoadFriends();
}

FriendModel* GUIManager::friend_model() {
  return  &friend_model_;
}

MessageModel* GUIManager::message_model() {
  return &message_model_;
}

void GUIManager::newFriend() {
  FriendItem* new_friend = new FriendItem("oleksyk", true);
  friend_model_.AddFriendToList(new_friend);
}

void GUIManager::deleteFriend(FriendItem* friend_to_delete) {
  if (!friend_to_delete)
      return;
  friend_model_.RemoveFriendFromList(friend_to_delete);
}

void GUIManager::newMessage(QString message) {
  MessageItem* new_message = new MessageItem(message, QTime::currentTime().toString("hh:mm"),
                                             QDate::currentDate().toString("d MMM"), my_id);
  message_model_.AddMessageToList(new_message);
}

void GUIManager::loadMessages(QString friend_login) {
  message_model_.RemoveAllMessagesFromList();

  QString data, time, date;
  int owner_id;
  MessageItem* new_message;

  QVector<ClientDAL::Message> history = client_dal_.GetMessages(friend_login);
  for(const auto& msg : history) {
    data = msg.data;
    time = msg.time.toString("hh:mm");
    date = msg.date.toString("d MMM");  //FIX date
    owner_id = msg.owner_id;
    new_message = new MessageItem(data, time, date, owner_id);
    message_model_.AddMessageToList(new_message);
  }
}

void GUIManager::LoadFriends() {   //don't forget to load id
  QVector<QString> friends = client_dal_.GetFriendsLogin();

  for(const QString& friend_login : friends) {
    bool status = client_dal_.GetFriendStatus(client_dal_.GetIDByLogin(friend_login));  // just for test
    FriendItem* friend_item = new FriendItem(friend_login, status);
    friend_model_.AddFriendToList(friend_item);
  }
}

