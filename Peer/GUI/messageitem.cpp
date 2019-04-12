#include "messageitem.h"

MessageItem::MessageItem(Message* msg, QObject *parent)
    : QObject(parent),
      msg_(msg){

}

QString MessageItem::data() const {
  return msg_->data;
}

void MessageItem::set_data(QString data)
{
  if (msg_->data == data)
      return;
  
  msg_->data = data;
  emit DataChanged();
}

QString MessageItem::time() const {
  return msg_->time.toString("hh:mm");
}


QString MessageItem::date() const {
  return msg_->date.toString("d MMM");
}


int MessageItem::owner_id() const {
  return msg_->owner_id;
}
