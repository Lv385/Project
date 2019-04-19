#include "friendrequestitem.h"

FriendRequestItem::FriendRequestItem(QString login, QObject *parent) : QObject(parent)
    ,login_(login) {
}

QString FriendRequestItem::login() const {
  return login_;
}

void FriendRequestItem::set_login(QString login) {
  if (login_ == login)
      return;

  login_ = login;
  emit LoginChanged();
}
