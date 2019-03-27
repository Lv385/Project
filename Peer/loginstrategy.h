#ifndef LOGINSTRATEGY_H
#define LOGINSTRATEGY_H

#include <QObject>

#include "abstractstrategy.h"

class LoginStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  LoginStrategy(PeerInfo peer_info);
  ~LoginStrategy();
};

#endif  // !LOGINSTRATEGY_H
