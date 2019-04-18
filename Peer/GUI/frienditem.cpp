#include "frienditem.h"


FriendItem::FriendItem(QString login, bool status, unsigned id, 
  unsigned unread_msgs, QObject *parent) 
  : QObject(parent)
    ,login_(login)
    ,status_(status)
    ,id_(id)
    ,unread_msgs_(unread_msgs) {
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

unsigned FriendItem::unread_msgs() const { 
  return unread_msgs_; 
}

void FriendItem::set_unread_msgs(unsigned unread_msgs) {
  if (unread_msgs_ == unread_msgs)
    return;

  unread_msgs_ = unread_msgs;
  emit UnreadMsgsChanged();
}
