#include "frienditem.h"


FriendItem::FriendItem(QString login, bool status, unsigned id, QObject *parent) : QObject(parent)
    ,login_(login)
    ,status_(status)
    ,id_(id){
}

QString FriendItem::login() const {
  return login_;
}

void FriendItem::set_login(QString login) {
  if (login_ == login)
      return;

  login_ = login;
  emit LoginChanged();
}

bool FriendItem::status() const {
  return status_;
}

void FriendItem::set_status(bool status) {
  if (status_ == status)
      return;

  status_ = status;
  emit StatusChanged();
}

unsigned FriendItem::id() const
{
  return id_;
}

void FriendItem::set_id(unsigned id)
{
  if (id_ == id)
      return;

  id_ = id;
  emit IdChanged();
}
