#ifndef DELETEREQUESTRESPONSESTRATEGY_H
#define DELETEREQUESTRESPONSESTRATEGY_H


#include "abstractstrategy.h"

class DeleteRequestResponseStrategy : public AbstractStrategy {
  Q_OBJECT

 public:
  DeleteRequestResponseStrategy();
  ~DeleteRequestResponseStrategy();

  virtual void DoWork() override;

 signals:
  void DeleteRequestResult(quint32);
};
#endif  // !DELETEREQUESTRESPONSESTRATEGY_H