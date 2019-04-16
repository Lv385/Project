#include "friendmodel.h"
#include "rolesenum.h"

FriendModel::FriendModel(QObject *parent)
  : QAbstractListModel(parent) {
}

unsigned FriendModel::GetFirstFriendId() const {
  if (!friends_list_.isEmpty()) {
    return friends_list_[0]->id();
  } else {
    return 0;    //FIXME
  }
}

int FriendModel::rowCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : friends_list_.size();
}

QVariant FriendModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role == Roles::FRIEND_ROLE)
    return QVariant::fromValue(qobject_cast<QObject*>(friends_list_[index.row()]));

  return QVariant();
}

QHash<int, QByteArray> FriendModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[Roles::FRIEND_ROLE] = "friend";
  return names;
}

void FriendModel::AddFriendToList(FriendItem* new_friend) {  //adding to an end
  const int index = friends_list_.size();

  beginInsertRows(QModelIndex(), index, index);
  friends_list_.push_back(new_friend);
  endInsertRows();
}

bool FriendModel::RemoveFriendFromList(FriendItem* friend_to_delete) {
  if (friends_list_.contains(friend_to_delete)) {
    const int index = friends_list_.indexOf(friend_to_delete);

    beginRemoveRows(QModelIndex(), index, index);
    friends_list_[index]->deleteLater();
    friends_list_.removeAt(index);
    endRemoveRows();

    return true;
  } else {
      return false;
  }
}

void FriendModel::SetStatus(unsigned id, bool status) {

  for(auto &a : friends_list_){
    if (a->id() == id) {
        a->set_status(status);
      break;
    }
  }
}

void FriendModel::AddUnreadMesg(unsigned id) {
  for (auto &a : friends_list_) {
    if (a->id() == id) {
      a->set_unread_msgs(a->unread_msgs() + 1);
      break;
    }
  }
}

void FriendModel::DeleteUnreadMesgs(unsigned id) {
  for (auto &a : friends_list_) {
    if (a->id() == id) {
      a->set_unread_msgs(0);
      break;
    }
  }
}
