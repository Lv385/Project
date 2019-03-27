#ifndef MESSAGESTRATEGY_H
#define MESSAGESTRATEGY_H

#include "abstractstrategy.h"
#include "QTimer"

class MessageStrategy : public AbstractStrategy
{
  Q_OBJECT

public:
  MessageStrategy(QObject *parent, PeerInfo peer_info, 
                  QTcpSocket* socket);
  ~MessageStrategy();
 public slots:
  //void DoWork() override;
 signals:
  void MessageSent();

 private slots:
  void SendMessage();
private:

  QTimer timer_;
  static const int kMsecConnectionDuration_ = 60;
  PeerInfo peer_info_;
};


#endif // !MESSAGESTRATEGY_H

