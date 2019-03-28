#ifndef RECIEVEMESSAGESTRATEGY_H
#define RECIEVEMESSAGESTRATEGY_H

#include "abstractstrategy.h"

class RecieveMessageStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  RecieveMessageStrategy();
  ~RecieveMessageStrategy();
};

#endif  // !RECIEVEMESSAGESTRATEGY_H
