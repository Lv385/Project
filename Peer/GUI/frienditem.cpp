#include "frienditem.h"

FriendItem::FriendItem(QObject *parent) : QObject(parent)
{

}

FriendItem::FriendItem(QString login, bool status, QObject *parent) : QObject(parent)
    ,login_(login)
    ,status_(status)
{

}

QString FriendItem::login() const
{
  return login_;
}

void FriendItem::setLogin(QString login)
{
  if (login_ == login)
      return;

  login_ = login;
  emit loginChanged();
}

bool FriendItem::status() const
{
  return status_;
}

void FriendItem::setStatus(bool status)
{
  if (status_ == status)
      return;

  status_ = status;
  emit statusChanged();
}
