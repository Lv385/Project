#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"
#include "GUI/friendrequestitem.h"
#include "GUI/friendrequestmodel.h"
#include "GUI/messageitem.h"
#include "GUI/messagemodel.h"

#include "dataaccessor.h"
#include "clientcontroller.h"
#include "signalredirector.h"

class GUIManager : public QObject {
  Q_OBJECT

  Q_PROPERTY(QObject* friend_model READ friend_model CONSTANT)
  Q_PROPERTY(QObject* message_model READ message_model CONSTANT)
  Q_PROPERTY(QObject* friend_request_model READ friend_request_model CONSTANT)

  Q_PROPERTY(unsigned selected_friend_id READ selected_friend_id 
             WRITE set_selected_friend_id NOTIFY SelectedFriendIdChanged)

 public:
  explicit GUIManager(QObject* parent = nullptr);
  GUIManager(const GUIManager&) = delete;
  GUIManager& operator=(const GUIManager&) = delete;

  FriendModel* friend_model();
  MessageModel* message_model();
  FriendRequestModel* friend_request_model();

  unsigned selected_friend_id();
  void set_selected_friend_id(unsigned);

  // theese functions must start from low letter
  Q_INVOKABLE void newFriend(QString);  // temporary implementation(for testing)
  Q_INVOKABLE void deleteFriend(FriendItem*);
  Q_INVOKABLE void newMessage(QString);
  Q_INVOKABLE void deleteFriendRiequest(FriendRequestItem*);
  void newFriendRiequest();

signals:
  void SelectedFriendIdChanged(unsigned id);
  void openMainPage();
  void logInFailed();

public slots:
  void LogIn(QString user_login, QString user_password);  //only starting socket, should implement LOGIN
  void OnLoginResult(bool);
  void SendMessage(QString message);
  void LoadMessages(unsigned id);  // temporary implementation(for testing)


  // void UserEntered();

 private:
  void LoadFriends();  // temporary implementation(for testing)

  int my_id_;
  unsigned selected_friend_id_;

  FriendModel friend_model_;
  MessageModel message_model_;
  FriendRequestModel friend_request_model_;

  QVector<Friend> friends_;   //FIXME: use id insted of Friend obj in sendMessage
  ClientController* controller_;
  ClientLogger* logger_;

  DataAccessor client_data_;  // for testing
};
#endif
