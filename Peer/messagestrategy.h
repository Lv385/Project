#ifndef MESSAGESTRATEGY_H
#define MESSAGESTRATEGY_H

#include "abstractstrategy.h"
#include "blockwriter.h"

#include "QTimer"

class SendMessageStrategy : public AbstractStrategy{
  Q_OBJECT

public:
  SendMessageStrategy(PeerInfo peer_info, 
                      QTcpSocket* socket, QByteArray data);
 ~SendMessageStrategy();
 public slots:
  //void DoWork() override;.

 signals:
  void MessageSent();

 private slots:
  void SendMessage();
private:

  QTimer timer_;
  PeerInfo peer_info_;
  BlockWriter writer_;
};


#endif // !MESSAGESTRATEGY_H

