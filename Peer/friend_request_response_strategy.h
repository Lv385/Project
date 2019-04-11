#ifndef FRIENDREQUESTRESPONSESTRATEGY_H
#define FRIENDREQUESTRESPONSESTRATEGY_H

#include <QObject>
#include "abstractstrategy.h"

class FriendRequestResponseStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  FriendRequestResponseStrategy();
  ~FriendRequestResponseStrategy();

  virtual void DoWork() override;

signals:
  void FriendRequestResult(bool);
  void AddFriendRequestInfo(QString);
};
#endif