#include "messagemodel.h"
#include "rolesenum.h"

MessageModel::MessageModel(QObject *parent)
  : QAbstractListModel(parent) {
}

int MessageModel::rowCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : messages_list_.size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if(role == Roles::MESSAGE_ROLE)
    return QVariant::fromValue(qobject_cast<QObject*>(messages_list_[index.row()]));

  return QVariant();
}

QHash<int, QByteArray> MessageModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[Roles::MESSAGE_ROLE] = "message";
  return names;
}

void MessageModel::AddMessageToList(MessageItem* new_message) {

  beginInsertRows(QModelIndex(), 0, 0);
  messages_list_.push_front(new_message);
  endInsertRows();
}

void MessageModel::RemoveAllMessagesFromList() {
  if(!messages_list_.isEmpty()) {
    beginRemoveRows(QModelIndex(), 0, messages_list_.size() - 1);
    qDeleteAll(messages_list_);  //deleting all elements
    messages_list_.clear();      //removing all elements
    endRemoveRows();
  }
}

void MessageModel::SetMessagesAsSent() {
  for (auto it = messages_list_.begin(); it != messages_list_.end(); it++) {
    if ((*it)->sent_status()) {
      break;
    } else {
      (*it)->set_sent_status(true);
    }
  }
}

