#include "connection.h"

Connection::Connection(QObject *parent)
	: QTcpSocket(parent),
	receiver_ip_(QHostAddress::Null),
	receiver_port_(0),
	k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence()) //the only idea i had, must be fixed
{
                                                    

}

Connection::Connection(qintptr socketDescriptor, QObject * parent)
	: k_unpossiblle_2_bytes_sequence_(Parser::GetUnpossibleSequence())
{
	setSocketDescriptor(socketDescriptor);
}

void Connection::SendMessage(Message message)
{
	if (this->state() == QAbstractSocket::ConnectedState)
	{
		//message += '\n';
		//qDebug() << "my server port: " << receiver_server_->serverPort();
		QString mes_log = "Me: " + this->localAddress().toString() + ':' + QString::number(this->localPort()) +
					  "\nPeer: " + this->peerAddress().toString() + ':' + QString::number(this->peerPort()) +
						"\nsending";

		emit SendLog(mes_log);		

		QByteArray to_write = Parser::Message_ToByteArray(message); //pack 
		to_write.append(k_unpossiblle_2_bytes_sequence_);			//append separator
		this->write(to_write);                                      //need to be unpacked by Parser on the other side

		QString str = "->: " + message.message;
		emit SendMessageToUI(str);	
		
		ClientDAL::ClientDB db;
		ClientDAL::Message msg;
		msg.data = message.message;
		msg.owner_id = db.GetIDByIpPort(localAddress().toString(), 8989);
		msg.date = QDate::currentDate();
		msg.time = QTime::currentTime();
		db.AddMessage(msg, db.GetIDByIpPort(peerAddress().toString(),8989));

		//receiver_socket_->close(); // calls disconnectFromHost which emits disconnected()
		//receiver_socket_ = nullptr;
		//m_sender_socket->disconnectFromHost();
	}
	/*else
	{
		QString str = QString("cannot coonect to") + receiver_ip_.toString() + ' : ' + QString::number(receiver_port_);
		emit SendLog(str);
		emit SendMessageToUI(str);
	}*/
}

bool Connection::LoginRequest(LoginOrRegisterInfo info)
{
	if (this->state() == QAbstractSocket::ConnectedState)
	{
		QByteArray toWrite = Parser::LoginOrRegisterInfo_ToByteArray(info);
		write(toWrite);

		if (waitForReadyRead(4000))
		{
			QByteArray read = readAll();
			emit SendLog("writing to server");
			read = read.mid(read.indexOf(k_unpossiblle_2_bytes_sequence_));
			quint8 type = Parser::getRequestType(read);
			if (type == (quint8)ServerRequests::LOGIN_SUCCEED)
			{			
				return true;
			}

		}

	}
	return false;
}

void Connection::TryReadLine()
{
	QByteArray nextData;
	received_data_.append(this->readAll());

	int separatorIndex;

	//using such a separator, untill we Design something better
	while (received_data_.contains(k_unpossiblle_2_bytes_sequence_))
	{
		separatorIndex = received_data_.indexOf(k_unpossiblle_2_bytes_sequence_);

		nextData = received_data_.mid(separatorIndex + 2);
		received_data_ = received_data_.left(separatorIndex);
		//received_data_.append(temp.left(separatorIndex));                    //until separator
		//temp = temp.mid(separatorIndex + 2);						   //if there is data after separator we should save it 

		emit SendLog("recieving something from" +
					  this->peerAddress().toString() + ":" + QString::number(this->peerPort()));

		//here we should change behaviour depening on type of message
		quint16 requestType = Parser::getRequestType(received_data_);

		switch (requestType)
		{
			case (quint8)ClientRequest::MESSAGE:
			{
				Message mes = Parser::ParseAsMessage(received_data_);
				ClientDAL::ClientDB db;
				QString str = QString("<%1>: %2").arg(db.GetLoginById(mes.id))
												 .arg(mes.message);

				emit SendMessageToUI(str);
				ClientDAL::Message msg;
				QString  address = peerAddress().toString();
				address.remove(0, 7);						    //#fix 


				msg.data = mes.message;
				msg.owner_id = mes.id;							//#fix
				msg.date = QDate::currentDate();
				msg.time = QTime::currentTime();

				db.AddMessage(msg, db.GetIDByIpPort(address, 8989));
				break;
			}

		}
		//no longer needed after using
		received_data_ = nextData;
	}
	//if there is a part of another request, save it
}

void Connection::ServerWorker()
{
	if (received_data_.contains(k_unpossiblle_2_bytes_sequence_))
	{
		FriendUpdateInfo info = Parser::ParseAsFriendUpdateInfo(received_data_);
		ClientDAL::ClientDB db;
		db.UpdateIPPort(info.id, info.ip.toString(), info.port);
		disconnect();
		deleteLater();
	}
}


Connection::~Connection()
{

}


