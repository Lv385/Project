#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"

#include "dataaccessor.h"

class GUIManager : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QObject* friendModel READ friendModel NOTIFY friendModelChanged)

public:
  explicit GUIManager(QObject *parent = nullptr);

  FriendModel* friendModel();

  //test functions
  Q_INVOKABLE void newFriend();
  Q_INVOKABLE void deleteFriend(FriendItem*);

signals:
  void friendModelChanged();

public slots:
  void logIn();   //for testing
  void logIn2();  //for testing

private:
  void LoadFriends();

  FriendModel friend_model_;
  DataAccessor client_data_;  //for testing

};

#endif
