#ifndef FRIENDREQUESTMODEL_H
#define FRIENDREQUESTMODEL_H

#include <QAbstractListModel>
#include "GUI/friendrequestitem.h"

class FriendRequestModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit FriendRequestModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void AddRequestToList(FriendRequestItem*);
  bool RemoveRequestFromList(FriendRequestItem*);

private:
  QList<FriendRequestItem*> friend_requests_list_;
};
#endif // FRIENDREQUESTMODEL_H
