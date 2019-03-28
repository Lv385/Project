#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"
#include "GUI/messageitem.h"
#include "GUI/messagemodel.h"
#include "GUI/friendrequestitem.h"
#include "GUI/friendrequestmodel.h"

#include "dalmanager.h"


class GUIManager : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QObject* friend_model READ friend_model CONSTANT)
  Q_PROPERTY(QObject* message_model READ message_model CONSTANT)

public:
  explicit GUIManager(QObject *parent = nullptr);
  GUIManager(const GUIManager&) = delete;
  GUIManager& operator= (const GUIManager&) = delete;

  FriendModel* friend_model();
  MessageModel* message_model();


  //theese functions must start from low letter
  Q_INVOKABLE void newFriend();             //temporary implementation(for testing)
  Q_INVOKABLE void deleteFriend(FriendItem*);
  Q_INVOKABLE void newMessage(QString);
  Q_INVOKABLE void loadMessages(QString);   //temporary implementation(for testing)
  Q_INVOKABLE void deleteFriendRiequest(FriendRequestItem*);
  void newFriendRiequest();

  //void UserEntered();

private:
  void LoadFriends();            //temporary implementation(for testing)

  int my_id;

  FriendModel friend_model_;
  MessageModel message_model_;
  FriendRequestModel friend_request_model_;

  //ClientController* controller_;

  DALManager client_dal_;        //for testing
};
#endif
