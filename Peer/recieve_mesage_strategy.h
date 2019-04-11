#ifndef RECIEVEMESSAGESTRATEGY_H
#define RECIEVEMESSAGESTRATEGY_H

#include "abstractstrategy.h"

#include <QObject>

class RecieveMessageStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  RecieveMessageStrategy();
  ~RecieveMessageStrategy();

  virtual void DoWork() override;

 signals:
  void MessageRecieved(unsigned);

 protected:
  MessageInfo message_;
};
#endif  // !RECIEVEMESSAGESTRATEGY_H
