#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QObject>
#include "client_data_types.h"

class MessageItem : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString data READ data WRITE set_data NOTIFY DataChanged)
  Q_PROPERTY(QString time READ time CONSTANT)
  Q_PROPERTY(QString date READ date CONSTANT)
  Q_PROPERTY(int owner_id READ owner_id CONSTANT)

 public:
  MessageItem(Message* msg, QObject* parent = nullptr);

  QString data() const;
  void set_data(QString);
  QString time() const;
  QString date() const;
  int owner_id() const;

 signals:
  void DataChanged();

 private:
  Message* msg_;
};
#endif  // MESSAGEITEM_H
