#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include "GUI/frienditem.h"
#include "GUI/friendmodel.h"

#include "dalmanager.h"

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
  DALManager client_dal_;  //for testing

};

#endif
