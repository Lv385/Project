#include "guimanager.h"

GUIManager::GUIManager(QObject *parent)
    : QObject(parent),
      my_id_(1),
      logger_(ClientLogger::Instance()) {     //for testing
  controller_ = new ClientController(this);
  logger_->set_log_level(LogLevel::HIGH);
  newFriendRiequest();
  newFriendRiequest();
  newFriendRiequest();
  newFriendRiequest();

  SignalRedirector::get_instance().set_controller(controller_);

  connect(this, SIGNAL(SelectedFriendIdChanged(unsigned)), this, SLOT(LoadMessages(unsigned)));
  connect(controller_, SIGNAL(MessageRecieved(unsigned)), this, SLOT(LoadMessages(unsigned)));
  connect(controller_, SIGNAL(LoginResult(bool)), this, SLOT(OnLoginResult(bool)));
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

unsigned GUIManager::selected_friend_id() { 
  return selected_friend_id_; 
}

void GUIManager::set_selected_friend_id(unsigned selected_id) {
  if (selected_friend_id_ == selected_id) return;

  selected_friend_id_ = selected_id;
  emit SelectedFriendIdChanged(selected_id);
}

void GUIManager::newFriend(QString new_friend_login) {
  FriendItem* new_friend = new FriendItem(new_friend_login, qrand() % 2, 9);
  friend_model_.AddFriendToList(new_friend);
}

void GUIManager::deleteFriend(FriendItem* friend_to_delete) {
  if (!friend_to_delete)
      return;
  friend_model_.RemoveFriendFromList(friend_to_delete);
}

void GUIManager::newMessage(QString message) {
  MessageItem* new_message = new MessageItem(message, QTime::currentTime().toString("hh:mm"),
                                             QDate::currentDate().toString("d MMM"), my_id_);
  message_model_.AddMessageToList(new_message);
}

void GUIManager::LoadMessages(unsigned friend_id) {
  if (friend_id) {
    message_model_.RemoveAllMessagesFromList();

    QString data, time, date;
    int owner_id;
    MessageItem* new_message;

    QVector<Message> history = client_data_.get_messages(friend_id);
    for (const auto& msg : history) {
      data = msg.data;
      time = msg.time.toString("hh:mm");
      date = msg.date.toString("d MMM");  // FIX date
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

void GUIManager::LogIn(QString user_login, QString user_password) { 
  controller_->app_info_.remote_server_ip = "192.168.103.55";
  controller_->app_info_.remote_server_port = 8888;
  controller_->app_info_.my_port = 8989;  //FIXME
  controller_->app_info_.my_login = user_login;
  controller_->app_info_.my_password = user_password;
  controller_->app_info_.my_id = client_data_.get_id_by_login(user_login);
  logger_->WriteLog(LogType::SUCCESS, user_login);
  controller_->Start();
  controller_->LogIn(user_login, user_password);

  OnLoginResult(true);
}

void GUIManager::OnLoginResult(bool logged_in) {
  // stop busy indicator
  if (logged_in) {
    friends_ = controller_->LoadFriends();
    LoadFriends();

    LoadMessages(friend_model_.GetFirstFriend());
    //signal to ui
    emit test();
  }
  else {
    controller_->Stop();
    //show popup FAILED
  }
}

void GUIManager::SendMessage(QString message) { 
  for (auto user : friends_)
    if (user.id == selected_friend_id_) 
      controller_->SendMessage(user, message);

}

void GUIManager::LoadFriends() {   //don't forget to load id

  for (const Friend& i : friends_) {
    bool status = client_data_.get_friends_status(i.id);  // just for test
    FriendItem* friend_item = new FriendItem(i.login, status, i.id);
    friend_model_.AddFriendToList(friend_item);
  }
}

