#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <QAbstractListModel>
#include "GUI/frienditem.h"

class FriendModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit FriendModel(QObject *parent = nullptr);

  enum {
    OBJECT_ROLE = Qt::UserRole
  };

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


  QHash<int, QByteArray> roleNames() const override;

  void addFriendToList(FriendItem*);
  bool removeFriendFromList(FriendItem*);

private:
  QList<FriendItem*> friends_list_;
};

#endif // FRIENDMODEL_H
