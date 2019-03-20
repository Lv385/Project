#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QObject>

class FriendItem : public QObject
{
  Q_OBJECT

  Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
  Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)

public:
  explicit FriendItem(QObject *parent = nullptr);
  FriendItem(QString login, bool status, QObject *parent = nullptr);
  FriendItem(const FriendItem& copy) = default;

  QString login() const;
  void setLogin(QString);

  bool status() const;
  void setStatus(bool);

signals:
  void loginChanged();  //stil not used
  void statusChanged(); //stil not used

private:
  QString login_;
  bool status_;
};

#endif // FRIENDITEM_H
