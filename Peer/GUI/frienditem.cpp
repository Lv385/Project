#include "frienditem.h"


FriendItem::FriendItem(QString login, bool status, QObject *parent) : QObject(parent)
    ,login_(login)
    ,status_(status) {
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
