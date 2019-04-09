#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QObject>
#include "../DAL/sqldal.h"

class FriendItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString login READ login WRITE set_login NOTIFY LoginChanged)
  Q_PROPERTY(bool status READ status WRITE set_status NOTIFY StatusChanged)
  Q_PROPERTY(unsigned id READ id WRITE set_id NOTIFY IdChanged)

public:
  FriendItem(QString login, bool status, unsigned id, QObject *parent = nullptr);

  QString login() const;
  void set_login(QString);
  bool status() const;
  void set_status(bool);
  unsigned id() const;
  void set_id(unsigned);

signals:
  void LoginChanged();
  void StatusChanged();
  void IdChanged();

private:
  QString login_;
  bool status_;
  unsigned id_;
};

#endif // FRIENDITEM_H
