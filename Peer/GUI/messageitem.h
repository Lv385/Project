#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QObject>

class MessageItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString data READ data WRITE set_data NOTIFY DataChanged)
  Q_PROPERTY(QString time READ time WRITE set_time NOTIFY TimeChanged)
  Q_PROPERTY(QString date READ date WRITE set_date NOTIFY DateChanged)
  Q_PROPERTY(int owner_id READ owner_id WRITE set_owner_id NOTIFY OwnerIdChanged)

public:
  MessageItem(QString data, QString time, QString date,
              int owner_id, QObject *parent = nullptr);

  QString data() const;
  void set_data(QString);
  QString time() const;
  void set_time(QString);
  QString date() const;
  void set_date(QString);
  int owner_id() const;
  void set_owner_id(int);

signals:
  void DataChanged();
  void TimeChanged();
  void DateChanged();
  void OwnerIdChanged();

private:
  QString data_;
  QString time_;
  QString date_;
  int owner_id_;
};
#endif // MESSAGEITEM_H
