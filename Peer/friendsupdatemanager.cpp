#include "friendsupdatemanager.h"

FriendsUpdateManager::FriendsUpdateManager(ApplicationInfo& app_info)
    : app_info_(app_info),
  logger_(ClientLogger::Instance()) {
  
  logger_->set_log_level(LogLevel::HIGH);

  connect(&update_info_timer_, SIGNAL(timeout()), this, 
    SLOT(SendUpdateInfo()));
  connect(&update_receiver_, SIGNAL(readyRead()), this,
    SLOT(UpdateFriendsInfo()));
}

FriendsUpdateManager::~FriendsUpdateManager(){
}

bool FriendsUpdateManager::SetUpdateReceiver() {
 return update_receiver_.bind(QHostAddress::AnyIPv4, app_info_.my_port,
                        QUdpSocket::ShareAddress);
}

bool FriendsUpdateManager::Start() {
  SetUpdateSender();
  return SetUpdateReceiver();
}

void FriendsUpdateManager::Stop() {
  update_sender_.close();
  update_receiver_.close();
  update_info_timer_.stop();
}

void FriendsUpdateManager::SetUpdateSender() {
    update_sender_.bind(QHostAddress(QHostAddress::AnyIPv4), 0);
    update_info_timer_.start(3000);  
    logger_->WriteLog(LogType::SUCCESS, "friend manager started");
}

void FriendsUpdateManager::SendUpdateInfo() { 

  IdPort my_id_port;
  my_id_port.id = app_info_.my_id;
  my_id_port.port = app_info_.my_port;

  QByteArray to_write = Parser::IdPort_ToByteArray(my_id_port);
  to_write.append(Parser::GetUnpossibleSequence());

  QVector<Friend> friends = client_data_.GetFriends();

  for (const Friend& i : friends) {
    update_sender_.writeDatagram(to_write, QHostAddress(i.ip),
                                 i.port);
  }
  logger_->WriteLog(LogType::INFO, " update sent");
}

void FriendsUpdateManager::UpdateFriendsInfo() {
  while (update_receiver_.hasPendingDatagrams()) {
    datagram.resize(static_cast<int>(update_receiver_.pendingDatagramSize()));
    QHostAddress peer_address;
    update_receiver_.readDatagram(datagram.data(), datagram.size(), &peer_address);
    updated_friend_info = Parser::ParseAsIdPort(datagram);
    if (updated_friend_info.id == app_info_.my_id)
          continue;

    if (check_timers_.find(updated_friend_info.id) == check_timers_.end()) {
      emit StatusChanged(updated_friend_info.id, true);

      QTimer* timer = new QTimer();
      timer->start(10000);
      check_timers_[updated_friend_info.id] = timer;

      logger_->WriteLog(LogType::INFO,
                        " updated " + QString::number(updated_friend_info.id) + "'s info");
      client_data_.UpdateIPPort(updated_friend_info.id, peer_address.toString(),
                                updated_friend_info.port);

      connect(timer, SIGNAL(timeout()), this, SLOT(SetOfflineStatus()));
    } else {
      check_timers_[updated_friend_info.id]->start(10000);  // reset timer
    }

  }
}

void FriendsUpdateManager::SetOfflineStatus() {
  QTimer* to_delete = static_cast<QTimer*>(QObject::sender());  // get user id that came offline
  unsigned id = check_timers_.key(to_delete);
  client_data_.SetFriendStatus(id, false);

  emit StatusChanged(id, false);

  logger_->WriteLog(LogType::INFO, " set " + client_data_.GetLoginById(id)
    + " offline status");
  check_timers_.remove(id);
  to_delete->deleteLater();  
}

