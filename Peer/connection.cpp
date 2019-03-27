#include "connection.h"
Connection::Connection(QObject* parent)
    : QTcpSocket(parent),
      receiver_ip_(QHostAddress::Null),
      receiver_port_(0),
      k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()) {  // the only idea i had, must be fixed
  logger_ = ClientLogger::Instance();
}

Connection::Connection(qintptr socketDescriptor, QObject* parent)
    : k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()) {
  setSocketDescriptor(socketDescriptor);
  logger_ = ClientLogger::Instance();
}

void Connection::SendMessage(Message message) {
  if (this->state() == QAbstractSocket::ConnectedState) {
    logger_->WriteLog(LogType::SUCCESS,
                     " Me: " + this->localAddress().toString() + ':' +
                         QString::number(this->localPort()) +
                         " Peer: " + this->peerAddress().toString() + ':' +
                         QString::number(this->peerPort()) + " sending");

    QByteArray to_write = Parser::Message_ToByteArray(message);       // pack
    to_write.append(k_unpossiblle_2_bytes_sequence_);                 // append separator
    this->write(to_write);                                            // need to be unpacked by Parser on the other side

    QString str = "->: " + message.message;
    emit SendMessageToUI(str);
    
	connection_timer_.start(30000);  //reset timer for new 30 sec

  } 
  else {

    QString str = QString(" cannot coonect to") + receiver_ip_.toString() +
                  ' : ' + QString::number(receiver_port_);
    logger_->WriteLog(LogType::ERROR, str);
    emit SendMessageToUI(str);
  }
}

bool Connection::LoginRequest(LoginInfo info) {
  if (this->state() == QAbstractSocket::ConnectedState) {
    QByteArray toWrite = Parser::LoginInfo_ToByteArray(info);
    write(toWrite);

    if (waitForReadyRead(4000)) {
      QByteArray read = readAll();
      logger_->WriteLog(LogType::INFO, " writing to server");
      read = read.left(read.indexOf(k_unpossiblle_2_bytes_sequence_));
      quint8 type = Parser::getRequestType(read);
      if (type == (quint8)ServerRequests::LOGIN_SUCCEED) {
        logger_->WriteLog(LogType::SUCCESS,
                                           " Logged in success");
        return true;
      }
    }
  }
  return false;
}

void Connection::StartConnectionTimer(unsigned miliseconds) {
  connection_timer_.start(miliseconds);
  connect(&connection_timer_, SIGNAL(timeout()), 
                        this, SIGNAL(ConnectionTimeout()));
}

//reading requests due to separator
void Connection::ReceiveRequests() {
  QByteArray nextData;
  int separatorIndex;

  received_data_.append(this->readAll());

  // work on all requests if there are more than one
  // using such a separator, untill we design something better
  while (received_data_.contains(k_unpossiblle_2_bytes_sequence_)) {
    separatorIndex = received_data_.indexOf(k_unpossiblle_2_bytes_sequence_);

    nextData = received_data_.mid(separatorIndex + 2);
    received_data_ = received_data_.left(separatorIndex);

    logger_->WriteLog(LogType::INFO, " recieving something from" +
      this->peerAddress().toString() + ":" + QString::number(this->peerPort()));

    // here we should change behaviour depening on type of message
    quint16 requestType = Parser::getRequestType(received_data_);


    switch (requestType) {
    case (quint8)ClientRequest::MESSAGE: {
      Message mes = Parser::ParseAsMessage(received_data_);
      QString str = QString("<%1>: %2").arg(client_data_.get_login_by_id(client_data_.get_id_by_ip_port(this->peerAddress().toString(), this->peerPort())))
                    .arg(mes.message);

      emit SendMessageToUI(str);

      client_data_.AddMessageToDB(mes.message, mes.id, mes.id);

      break;
    }
    }
    // no longer needed after using
    received_data_ = nextData;
  }
  // if there is a part of another request, save it
}

//#tofix should be refactored
void Connection::ServerWorker() {
  received_data_ = readAll();
  if (received_data_.contains(k_unpossiblle_2_bytes_sequence_)) {
    FriendUpdateInfo info = Parser::ParseAsFriendUpdateInfo(received_data_);
    QString str = info.ip.toString();
    client_data_.UpdateIPPort(info.id, info.ip.toString(), info.port);
    disconnect();
    deleteLater();
  }
}


Connection::~Connection() {}
