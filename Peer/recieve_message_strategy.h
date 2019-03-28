#pragma once

#include <AbstractStrategy>

class RecieveMessageStrategy : public AbstractStrategy
{
  Q_OBJECT

public:
    RecieveMessageStrategy(QObject *parent);
    ~RecieveMessageStrategy();
};
