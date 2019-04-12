#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include <QAbstractListModel>
#include "GUI/frienditem.h"

class FriendModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit FriendModel(QObject* parent = nullptr);
  unsigned GetFirstFriend() const;    //for loading on startup

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void AddFriendToList(FriendItem*);
  bool RemoveFriendFromList(FriendItem*);
  void SetStatus(unsigned id, bool status);

private:
  QList<FriendItem*> friends_list_;
};
#endif // FRIENDMODEL_H
