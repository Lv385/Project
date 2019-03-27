#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"
#include "GUI/messageitem.h"
#include "GUI/messagemodel.h"

#include "dataaccessor.h"


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

private:
  void LoadFriends();            //temporary implementation(for testing)

  int my_id;

  FriendModel friend_model_;
  MessageModel message_model_;

  FriendModel friend_model_;
  DataAccessor client_data_;  //for testing

};
#endif
