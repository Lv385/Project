#include "worker.h"
#include "signalredirector.h"

Worker::Worker(BlockReader* reader)
    : reader_(reader),
      socket_(reader_->get_socket()),
      redirector_(SignalRedirector::get_instance()){
  writer_ = new BlockWriter(socket_);
  connect(reader_, SIGNAL(ReadyReadBlock()), this, SLOT(OnReadyReadBlock()));
  strategies_.insert(static_cast<quint8>(ClientClientRequest::MESSAGE), new RecieveMessageStrategy());
}

Worker::Worker(PeerInfo peer_info, QString message)
    : message_(message),
      peer_info_(peer_info),
      redirector_(SignalRedirector::get_instance()) {
  socket_ = new QTcpSocket();
  writer_ = new BlockWriter(socket_);
  reader_ = new BlockReader(socket_);
  connect(socket_, SIGNAL(connected()), this, SLOT(OnConnected()));
  socket_->connectToHost(peer_info_.ip, peer_info_.port);
}

void Worker::DoWork() { 
  strategy_->DoWork(); 
}

void Worker::SetStrategy(StrategyType strategy_type) {
  strategy_ = strategies_[strategy_type];
}

void Worker::set_message(QString message) { 
  message_ = message; }

void Worker::SendMessage() {
  Message mes = {message_};
  QByteArray data = Parser::Message_ToByteArray(mes);
  emit MessageSent(peer_info_.id, true);
  writer_->WriteBlock(data);
}

void Worker::OnDisconnected() { 
  emit Disconnected(peer_info_.id);
}

void Worker::OnConnected() {
  unsigned id = peer_info_.id;
  emit Connected(id);
  ConnectInfo connect_info = {id};
  writer_->WriteBlock(Parser::ConnectInfo_ToByteArray(connect_info));
  SendMessage();
}

void Worker::OnReadyReadBlock() {
  QByteArray data;
  while (reader_->HasPendingBlock()) {
    data = reader_->ReadNextBlock();
    quint8 type = Parser::getRequestType(data);
    strategy_ = strategies_[type];
    DoWork();
  }
}

Worker::~Worker() { 
  delete writer_;
  delete reader_;
  delete socket_;
}
