#ifndef TEST_H
#define TEST_H

#include <ui_mainwindow.h>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QNetworkSession>
#include <QObject>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QVector>

#include "connection.h"
#include "tcpserver.h"
#include "dataaccessor.h"
#include "clientlogger.h"


#include "../Parser&Structs/parser.h"

class Peer : public QObject {
  Q_OBJECT

 public:
  explicit Peer(QObject* parent = nullptr, quint16 listen_port = 0);

  // send message if there  connection, if not try to connect first
  void SendRequest(unsigned id, QString message);

  quint16 get_my_port() const;
  QHostAddress get_my_ip() const;

  void set_receiver_ip(const QHostAddress& receiver_ip);
  void set_receiver_port(const quint16& receiver_port);
  void set_login(const QString login);
  void set_id(const quint32 id);
  void set_server_ip_port(QHostAddress remote_server_ip,
                                 quint16 remote_server_port);

  bool is_active();

  bool StartListening(quint16 listen_port);
  bool ConnectToPeer(unsigned id);
  bool LogIn(QString login, QString password);

 signals:
  void SendMessageToUI(QString);

 private slots:
  void DisconncetFromPeer();
  void SetSocket(QTcpSocket*);
  void OnServerConnected(Connection* connection);
  void UpdateFriendsInfo();
  void SendUpdateInfo();
  void SetOfflineStatus();

  // to implement
  // void nullTcpSocket();
  // void DisplayError(QAbstractSocket::SocketError socketError);

 private:
  LocalServer* tcp_server_;  // server for listening

  QString my_login_;
  quint32 my_id_;

  QHostAddress server_ip_;
  quint16 server_port_;

  Connection* server_connection_;
  QHash<unsigned, Connection*> connections_;

  QUdpSocket update_sender_;
  QUdpSocket update_receiver_;
  QHostAddress udp_group_address_;
  QTimer update_info_timer_;
  QHash<unsigned, QTimer*> check_timers_;

  QHostAddress my_ip_;
  quint16 my_listen_port_;

  QHostAddress receiver_ip_;
  quint16 receiver_port_;

  bool is_active_;
  DataAccessor client_data_;
  ClientLogger* logger_;
};

#endif  // TEST_H
