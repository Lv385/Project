#include "friendrequestitem.h"

FriendRequestItem::FriendRequestItem(QString login, unsigned id, QObject *parent) : QObject(parent)
    ,login_(login)
    ,id_(id) {
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

unsigned FriendRequestItem::id() const
{
  return id_;
}

void FriendRequestItem::set_id(unsigned id)
{
  if (id_ == id)
      return;

  id_ = id;
  emit IdChanged();
}
