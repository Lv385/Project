#ifndef LOGINSTRATEGY_H
#define LOGINSTRATEGY_H

#include <QObject>

#include "abstractstrategy.h"

class LoginStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  LoginStrategy(QObject *parent);
  ~LoginStrategy();
};

#endif  // !LOGINSTRATEGY_H
