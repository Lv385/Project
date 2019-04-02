#include "friendrequestmodel.h"
#include "rolesenum.h"

FriendRequestModel::FriendRequestModel(QObject *parent)
  : QAbstractListModel(parent) {
}

int FriendRequestModel::rowCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : friend_requests_list_.size();
}

QVariant FriendRequestModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role == Roles::FRIEND_REQUEST_ROLE)
    return QVariant::fromValue(qobject_cast<QObject*>(friend_requests_list_[index.row()]));

  return QVariant();
}

QHash<int, QByteArray> FriendRequestModel::roleNames() const {
  QHash<int, QByteArray> names;
  names[Roles::FRIEND_REQUEST_ROLE] = "friend_request";
  return names;
}

void FriendRequestModel::AddRequestToList(FriendRequestItem* new_friend_request) {
  const int index = friend_requests_list_.size();

  beginInsertRows(QModelIndex(), index, index);
  friend_requests_list_.push_back(new_friend_request);
  endInsertRows();
}

bool FriendRequestModel::RemoveRequestFromList(FriendRequestItem * friend_request_to_delete) {
  if (friend_requests_list_.contains(friend_request_to_delete)) {
    const int index = friend_requests_list_.indexOf(friend_request_to_delete);

    beginRemoveRows(QModelIndex(), index, index);
    //friends_list_[index]->deleteLater();
    friend_requests_list_.removeAt(index);
    endRemoveRows();

    return true;
  } else {
      return false;
  }
}


