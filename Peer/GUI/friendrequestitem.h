#ifndef FRIENDREQUESTITEM_H
#define FRIENDREQUESTITEM_H

#include <QObject>

class FriendRequestItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString login READ login WRITE set_login NOTIFY LoginChanged)
  Q_PROPERTY(unsigned id READ id WRITE set_id NOTIFY IdChanged)

public:
  FriendRequestItem(QString login, unsigned id, QObject *parent = nullptr);

  QString login() const;
  void set_login(QString);
  unsigned id() const;
  void set_id(unsigned);

signals:
  void LoginChanged();
  void IdChanged();

private:
  QString login_;
  unsigned id_;
};

#endif // FRIENDREQUESTITEM_H
