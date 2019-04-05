#ifndef FRIENDSUPDATEMANAGER_H
#define FRIENDSUPDATEMANAGER_H

#include <QObject>

class FriendsUpdateManager : public QObject
{
  Q_OBJECT

public:
  void Start(); 
  void Stop();
  FriendsUpdateManager(QObject *parent);
  ~FriendsUpdateManager();
};

#endif // !FRIENDSUPDATEMANAGER_H
