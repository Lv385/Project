#ifndef REGISTERRESPONSESTRATEGY_H
#define REGISTERRESPONSESTRATEGY_H

#include <QObject>

#include "abstractstrategy.h"

class RegisterResponseStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  RegisterResponseStrategy();
  ~RegisterResponseStrategy();

  virtual void DoWork() override;
 signals:
  void RegisterResult(quint32);
};
#endif  // !REGISTERRESPONSESTRATEGY_H
