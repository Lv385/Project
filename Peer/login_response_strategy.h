#ifndef LOGINRESPONSESTRATEGY_H
#define LOGINRESPONSESTRATEGY_H
#include <QObject>
#include "abstractstrategy.h"

class LoginResponseStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  LoginResponseStrategy();
  ~LoginResponseStrategy();

  virtual void DoWork() override;
signals:
  void LoginResult(bool result);
};

#endif  // !LOGINRESPONSESTRATEGY_H
