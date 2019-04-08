#ifndef FRIENDSUPDATEMANAGER_H
#define FRIENDSUPDATEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#include "client_data_types.h"
#include "../Parser&Structs/request_types.h"
#include "../Parser&Structs/parser.h"
#include "dataaccessor.h"
#include "clientlogger.h"
#include "application_info.h"



class FriendsUpdateManager : public QObject {
  Q_OBJECT

 public:
  FriendsUpdateManager(ApplicationInfo& app_info);
  ~FriendsUpdateManager();

  void Start();
  void Stop();

 private slots:
  void SendUpdateInfo();
  void UpdateFriendsInfo();
  void SetOfflineStatus();

 private:
  ApplicationInfo& app_info_;
  DataAccessor client_data_;
  ClientLogger* logger_;

  QByteArray datagram;
  IdPort updated_friend_info;
  QUdpSocket update_sender_;
  QUdpSocket update_receiver_;
  QTimer update_info_timer_;
  QMap<unsigned, QTimer*> check_timers_;
};

#endif  // !FRIENDSUPDATEMANAGER_H
