#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include "GUI/messageitem.h"

class MessageModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit MessageModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  void AddMessageToList(MessageItem*);
  void RemoveAllMessagesFromList();

private:
  QList<MessageItem*> messages_list_;
};
#endif // MESSAGEMODEL_H
