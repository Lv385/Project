#include "connection.h"
Connection::Connection(QObject* parent)
    : QTcpSocket(parent),
      receiver_ip_(QHostAddress::Null),
      receiver_port_(0),
      k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()),
      reader_(this),
      writer_(this, this) {
  connect(&reader_, SIGNAL(ReadyReadBlock()), this, SLOT(ReceiveRequests()));
  }

Connection::Connection(qintptr socketDescriptor, QObject* parent)
    : k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()),
      reader_(this),
      writer_(this, this) {
  setSocketDescriptor(socketDescriptor);
  connect(&reader_, SIGNAL(ReadyReadBlock()), this, SLOT(ReceiveRequests()));
}

void Connection::SendMessage(Message message) {
  if (this->state() == QAbstractSocket::ConnectedState) {
    QString mes_log = "Me: " + this->localAddress().toString() + ':' +
                      QString::number(this->localPort()) +
                      "\nPeer: " + this->peerAddress().toString() + ':' +
                      QString::number(this->peerPort()) + "\nsending";

    emit SendLog(mes_log);

    QByteArray to_write = Parser::Message_ToByteArray(message);       // pack
    writer_.WriteBlock(to_write);  // need to be unpacked by Parser on the other side

    QString str = "->: " + message.message;
    emit SendMessageToUI(str);
    
	  connection_timer_.start(30000);  //reset timer for new 30 sec
  } 
  else {
    QString str = QString("cannot coonect to") + receiver_ip_.toString() +
                  ' : ' + QString::number(receiver_port_);
    emit SendLog(str);
    emit SendMessageToUI(str);
  }
}

bool Connection::LoginRequest(LoginInfo info) {
  if (this->state() == QAbstractSocket::ConnectedState) {
    QByteArray toWrite = Parser::LoginInfo_ToByteArray(info);
    write(toWrite);

    if (waitForReadyRead(4000)) {
      QByteArray read = readAll();
      emit SendLog("writing to server");
      read = read.left(read.indexOf(k_unpossiblle_2_bytes_sequence_));
      quint8 type = Parser::getRequestType(read);
      if (type == (quint8)ServerRequests::LOGIN_SUCCEED) {
        emit SendLog("Logged in success");
        return true;
      }
    }
  }
  return false;
}

void Connection::StartConnectionTimer(unsigned miliseconds) {
  connection_timer_.start(miliseconds);
  connect(&connection_timer_, SIGNAL(timeout()), 
                        this, SIGNAL(CoonectionTimeout()));
}

//reading requests due to separator
void Connection::ReceiveRequests() {
  while (reader_.HasPendingBlock()) {
    QByteArray data = reader_.ReadNextBlock();
    quint16 requestType = Parser::getRequestType(data);

    switch (requestType) {
    case (quint8)ClientClientRequest::MESSAGE: {
        Message mes = Parser::ParseAsMessage(data);
      QString str = QString("<%1>: %2").arg("not working now")
                    .arg(mes.message);

      emit SendMessageToUI(str);

      //client_dal_.AddMessageToDB(mes.message, mes.id, mes.id);

      break;
    }
    }
 
  }
}

//#tofix should be refactored
void Connection::ServerWorker() {
  received_data_ = readAll();
  if (received_data_.contains(k_unpossiblle_2_bytes_sequence_)) {
    FriendUpdateInfo info = Parser::ParseAsFriendUpdateInfo(received_data_);
    QString str = info.ip.toString();
    client_dal_.UpdateIPPort(info.id, info.ip.toString(), info.port);
    disconnect();
    deleteLater();
  }
}


Connection::~Connection() {}
