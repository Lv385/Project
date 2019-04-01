#include "worker.h"
#include "signalredirector.h"

Worker::Worker(BlockReader* reader, unsigned user_id, unsigned my_id)
    : reader_(reader),
      my_id_(my_id),
      logger_(ClientLogger::Instance()),
      redirector_(SignalRedirector::get_instance()) {
  peer_info_.id = user_id;
  socket_ = reader_->get_socket();
  writer_ = new BlockWriter(socket_);
  redirector_.ConnectToMessageSent(this);
  redirector_.ConnectToMessageRecieved(this);
  connect(socket_, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));
  strategies_.insert(static_cast<quint8>(ClientClientRequest::MESSAGE),
                     new RecieveMessageStrategy());
}

Worker::Worker(PeerInfo peer_info, QString message, unsigned my_id)
    : message_(message), peer_info_(peer_info), 
      my_id_(my_id),
      logger_(ClientLogger::Instance()),
      redirector_(SignalRedirector::get_instance()) {
  socket_ = new QTcpSocket();
  writer_ = new BlockWriter(socket_);
  reader_ = new BlockReader(socket_);
  redirector_.ConnectToMessageSent(this);
 // int a = receivers(SIGNAL(MessageSent(unsigned id, bool result)));

  redirector_.ConnectToMessageRecieved(this);
  //int b = receivers(SIGNAL(MessageRecieved(unsigned id)));

  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));
  this->dumpObjectInfo();

  connect(socket_, SIGNAL(connected()), this, SLOT(OnConnected()));
  connect(socket_, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
  connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(OnError(QAbstractSocket::SocketError)));
  socket_->connectToHost(peer_info_.ip, peer_info_.port);
  strategies_.insert(static_cast<quint8>(ClientClientRequest::MESSAGE),
                     new RecieveMessageStrategy());
}

void Worker::DoWork() { 
  strategy_->DoWork();
}

void Worker::SetStrategy(StrategyType strategy_type) {
  strategy_ = strategies_[strategy_type];
}

void Worker::set_message(QString message) { 
  message_ = message; 
}

void Worker::set_my_id(unsigned id) { 
  my_id_ = id; 
}

void Worker::SendMessage() {
  timer_.start(k_msc);
  Message mes = {message_};
  QByteArray data = Parser::Message_ToByteArray(mes);
  client_data_.AddMessageToDB(message_, peer_info_.id, my_id_);
  emit MessageSent(peer_info_.id, true);
  writer_->WriteBlock(data);
}

void Worker::OnDisconnected() {
  emit Disconnected(peer_info_.id);
}

void Worker::OnError(QAbstractSocket::SocketError) {
  emit Error(peer_info_.id);
}

void Worker::OnTimedOut() { 
  logger_->WriteLog(INFO, "Auto disconnecting from" + peer_info_.login);
  socket_->disconnectFromHost();
}

void Worker::OnConnected() {
  timer_.start(k_msc);
  connect(&timer_, SIGNAL(timeout()), 
          this, SLOT(OnTimedOut));
  unsigned id = peer_info_.id;
  emit Connected(id);
  ConnectInfo connect_info = {my_id_};
  writer_->WriteBlock(Parser::ConnectInfo_ToByteArray(connect_info));
  SendMessage();
}

void Worker::OnReadyReadBlock() {
  QByteArray data;
  while (reader_->HasPendingBlock()) {
    data = reader_->ReadNextBlock();
    quint8 type = Parser::getRequestType(data);
    strategy_ = strategies_[type];
    PeerInfo info;
    strategy_->set_data(data);
    strategy_->set_peer_info(peer_info_);
    strategy_->set_my_id(my_id_);
    DoWork();
  }
}

Worker::~Worker() {
  writer_;
  delete reader_;
  delete socket_;
}
