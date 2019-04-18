#ifndef FRIENDREQUESTITEM_H
#define FRIENDREQUESTITEM_H

#include <QObject>

class FriendRequestItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString login READ login WRITE set_login NOTIFY LoginChanged)

public:
  FriendRequestItem(QString login, QObject *parent = nullptr);

  QString login() const;
  void set_login(QString);

signals:
  void LoginChanged();

private:
  QString login_;
};

#endif // FRIENDREQUESTITEM_H
