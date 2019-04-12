#ifndef ADDFRIENDUPDATESTRATEGY_H
#define ADDFRIENDUPDATESTRATEGY_H

#include "abstractstrategy.h"

class AddFriendRequestStrategy : public AbstractStrategy
{
  Q_OBJECT

public:
  AddFriendRequestStrategy();
  ~AddFriendRequestStrategy();
    
  virtual void DoWork() override;

signals:
  void AddFriendRequestInfo(QString);

 private:
  AddFriendInfo info_;
};
#endif