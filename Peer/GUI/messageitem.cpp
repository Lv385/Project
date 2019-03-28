#include "messageitem.h"

MessageItem::MessageItem(QString data, QString time, QString date,
                         int owner_id, QObject *parent)
    : QObject(parent),
      data_(data),
      time_(time),
      date_(date),
      owner_id_(owner_id) {

}

QString MessageItem::data() const {
  return data_;
}

void MessageItem::set_data(QString data)
{
  if (data_ == data)
      return;

  data_ = data;
  emit DataChanged();
}

QString MessageItem::time() const {
  return time_;
}

void MessageItem::set_time(QString time)
{
  if (time_ == time)
      return;

  time_ = time;
  emit TimeChanged();
}

QString MessageItem::date() const {
  return date_;
}

void MessageItem::set_date(QString date)
{
  if (date_ == date)
      return;

  date_ = date;
  emit DateChanged();
}

int MessageItem::owner_id() const {
  return owner_id_;
}

void MessageItem::set_owner_id(int owner_id)
{
  if (owner_id_ == owner_id)
      return;

  owner_id_ = owner_id;
  emit OwnerIdChanged();
}
