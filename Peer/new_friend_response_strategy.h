#pragma once

#include "abstractstrategy.h"

class NewFriendResponseStrategy : public AbstractStrategy
{
  Q_OBJECT

public:
    NewFriendResponseStrategy();
    ~NewFriendResponseStrategy();

    virtual void DoWork() override;

signals:
  void NewFriendRequestResult(QString);

private:
  NewFriendInfo info_;
};
