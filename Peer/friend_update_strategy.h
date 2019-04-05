#ifndef FRIENDUPDATESTRATEGY_H
#define FRIENDUPDATESTRATEGY_H

#include "abstractstrategy.h"
class FriendUpdateStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  FriendUpdateStrategy();
  ~FriendUpdateStrategy();

  virtual void DoWork() override;

  private:
  FriendUpdateInfo info_;
};

#endif  // !FRIENDUPDATESTRATEGY_H
