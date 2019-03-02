#include "connection.h"


Connection::Connection(QObject *parent)
	: QTcpSocket(parent)
{

}

Connection::Connection(qintptr socketDescriptor, QObject * parent)
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
					  "\nPeer: " + this->peerAddress().toString() + ':' + QString::number(this->peerPort());
		emit SendLog(mes_log);
		message += '\0';

		this->write(message.toUtf8());
		emit SendLog("send");

		QString str = "->: " + message;
		emit SendMessageToUI(str);

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
	if (temp.contains('\0'))
	{
		received_message_.append(temp);
		QString str = QString("<%1>: %2").arg(this->peerAddress().toString())
			.arg(QString(received_message_));
		emit SendMessageToUI(str);
		received_message_.clear();
	}
	else
	{
		received_message_.append(temp);
	}
}


Connection::~Connection()
{
}
