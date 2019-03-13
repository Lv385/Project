#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>

#include <ui_mainwindow.h>
#include "dalmanager.h"
#include "../DAL/Client/clientdb.h"
#include "../Parser&Structs/parser.h"

class Connection : public QTcpSocket {
  Q_OBJECT

 public:
  Connection(QObject* parent);
  Connection(qintptr socketDescriptor, QObject* parent = 0);

  void SendMessage(Message message);
  bool LoginRequest(LoginOrRegisterInfo info);
  void StartConnectionTimer(unsigned miliseconds);

  ~Connection();

 private slots:
  void ReceiveRequests();
  void ServerWorker();

 signals:
  void SendLog(QString);
  void SendMessageToUI(QString);
  void CoonectionTimeout();

 private:
  QByteArray received_data_;

  QTimer connection_timer_;

  QHostAddress receiver_ip_;
  quint16 receiver_port_;

  const QByteArray k_unpossiblle_2_bytes_sequence_;
  DALManager client_dal_;
};
#endif
