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

void Connection::SendMessage(QString message)
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


		QString str = "->: " + message;
		emit SendMessageToUI(str);
		
		/*ClientDAL::ClientDB db;
		ClientDAL::Message msg;
		msg.data = message;
		db.AddMessage(msg, "markiyan");*/

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


void Connection::TryReadLine()
{
	QByteArray temp = this->readAll();
	int separatorIndex;

	//using such a separator, untill we Design something better
	while (temp.contains(k_unpossiblle_2_bytes_sequence_))
	{
		separatorIndex = temp.indexOf(k_unpossiblle_2_bytes_sequence_);

		received_data_.append(temp.left(separatorIndex));                    //until separator
		temp = temp.mid(separatorIndex + 2);						   //if there is data after separator we should save it 

		emit SendLog("recieving something from" +
					  this->peerAddress().toString() + QString::number(this->peerPort()));

		//here we should change behaviour depening on type of message
		if (Parser::getRequestType(received_data_) == (quint8)ClientRequest::MESSAGE) 
		{
			QString str = QString("<%1>: %2").arg(this->peerAddress().toString())
											 .arg(Parser::ParseAsMessage(received_data_));
			emit SendMessageToUI(str);
		}

		//no longer needed after using
		received_data_.clear();
	}

	//if there is a part of another request, save it
	received_data_.append(temp);
}


Connection::~Connection()
{

}
