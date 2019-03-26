#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <QAbstractListModel>
#include "GUI/frienditem.h"

class FriendModel : public QAbstractListModel
{
  Q_OBJECT


public:
  explicit FriendModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void AddFriendToList(std::shared_ptr<FriendItem>);
  bool RemoveFriendFromList(std::shared_ptr<FriendItem>);

private:
  QList<std::shared_ptr<FriendItem>> friends_list_;
};
#endif // FRIENDMODEL_H
