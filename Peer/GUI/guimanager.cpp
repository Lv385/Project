#include "guimanager.h"

GUIManager::GUIManager(QObject *parent)
    : QObject(parent),
      my_id(1) {     //for testing

  LoadFriends();
  loadMessages(friend_model_.GetFirstFriend());
  newFriendRiequest();
  newFriendRiequest();
  newFriendRiequest();
  newFriendRiequest();

}

FriendModel* GUIManager::friend_model() {
  return  &friend_model_;
}

MessageModel* GUIManager::message_model() {
  return &message_model_;
}

FriendRequestModel *GUIManager::friend_request_model() {
  return &friend_request_model_;
}

void GUIManager::newFriend(QString new_friend_login) {
  FriendItem* new_friend = new FriendItem(new_friend_login, qrand() % 2);
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
  if(friend_login != "") {    //FIXME
    message_model_.RemoveAllMessagesFromList();

    QString data, time, date;
    int owner_id;
    MessageItem* new_message;

    QVector<SQLDAL::Messages> history = client_data_.get_messages(friend_login);
    for(const auto& msg : history) {
      data = msg.data;
      time = msg.time.toString("hh:mm");
      date = msg.date.toString();  //FIX date
      owner_id = msg.owner_id;
      new_message = new MessageItem(data, time, date, owner_id);
      message_model_.AddMessageToList(new_message);
    }
  }
}

void GUIManager::deleteFriendRiequest(FriendRequestItem* friend_request_to_delete) {
  if (!friend_request_to_delete)
      return;
  friend_request_model_.RemoveRequestFromList(friend_request_to_delete);
}

void GUIManager::newFriendRiequest() {
  FriendRequestItem* new_friend_request = new FriendRequestItem("oleksyk", 7);
  friend_request_model_.AddRequestToList(new_friend_request);
}

void GUIManager::LoadFriends() {   //don't forget to load id
  QVector<SQLDAL::Friends> friends = client_data_.get_friends();

  for (const SQLDAL::Friends& i : friends) {
    bool status = client_data_.get_friends_status(i.id);  // just for test
    FriendItem* friend_item = new FriendItem(i.login, status);
    friend_model_.AddFriendToList(friend_item);
  }
}

