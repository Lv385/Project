#include "friendmodel.h"

FriendModel::FriendModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

int FriendModel::rowCount(const QModelIndex &parent) const
{  
  return parent.isValid() ? 0 : friends_list_.size();
}

QVariant FriendModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  switch (role) {       //FIXME
  case OBJECT_ROLE:
    return QVariant::fromValue(qobject_cast<QObject*>(friends_list_[index.row()]));
  }

  return QVariant();
}

QHash<int, QByteArray> FriendModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[OBJECT_ROLE] = "object";
  return names;
}

void FriendModel::addFriendToList(FriendItem * new_friend)   //adding to an end
{
  const int index = friends_list_.size();

  beginInsertRows(QModelIndex(), index, index);
  friends_list_.push_back(new_friend);
  endInsertRows();
}

bool FriendModel::removeFriendFromList(FriendItem * friend_to_delete)
{
  if (friends_list_.contains(friend_to_delete)) {
    const int index = friends_list_.indexOf(friend_to_delete);

    beginRemoveRows(QModelIndex(), index, index);
    friends_list_.removeAt(index);
    endRemoveRows();

    return true;
  } else {
      return false;
  }
}
