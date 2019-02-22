#include "peer.h"

Peer::Peer(QObject *parent)
        : QObject(parent)
        , m_receiver_server(new QTcpServer(this))
        , m_receiver_socket(new QTcpSocket(this))
{

    if (!m_receiver_server->listen()) //we can leave parameters empty
    {
                //(tcpServer->errorString()));
        return;
    }

    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            m_my_IP = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (m_my_IP.isEmpty())
        m_my_IP = QHostAddress(QHostAddress::LocalHost).toString();


    in.setDevice(m_receiver_socket);


    connect(m_receiver_server, &QTcpServer::newConnection, this, &Peer::setReceiverSocket);
    connect(m_sender_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &Peer::displayError);

    //cannot catch this signal
    //connect(m_receiver_socket, &QIODevice::readyRead, this, &Peer::readMessage);


    connect(m_receiver_socket, &QAbstractSocket::disconnected, m_receiver_socket, &QObject::deleteLater);

}

void Peer::sendMessage(QString message)
{
    qDebug() << "send";
    m_sender_socket = new QTcpSocket(this);
    m_sender_socket->connectToHost(m_receiver_IP, m_receiver_port.toInt());

    if (m_sender_socket->waitForConnected()) //or make connect(... , SIGNAL(connected())...);)
    {
        m_sender_socket->write(message.toStdString().c_str());
        m_sender_socket->waitForBytesWritten();  //bytesWritten() signal

        QString qstr = "->: " + message;
        emit sendMessageToUI(qstr);

        m_sender_socket->close();
        //m_sender_socket->disconnectFromHost();
    }

    delete m_sender_socket;
}


void Peer::setReceiverSocket()
{
    qDebug() << "setting RECIEVEd message";
    m_receiver_socket = m_receiver_server->nextPendingConnection();

    //kostyl

    m_receiver_socket->waitForReadyRead();
    QByteArray qba = m_receiver_socket->readAll();

    m_received_message = qba;
    QString str = tr("<%1>: %2").arg(m_receiver_socket->peerAddress().toString()).arg(m_received_message);
    emit sendMessageToUI(str);
    m_receiver_socket->disconnectFromHost();

    //end kostyl
}

void Peer::readMessage()
{
    //is not used
/*
    qDebug() << "kek";
    in.startTransaction();
    in >> m_received_message;

    if (!in.commitTransaction())
    {
        return;
    }
    else
    {
        QString str = tr("<%1>: %2").arg(m_receiver_socket->peerAddress().toString()).arg(m_received_message);
        emit sendMessageToUI(str);

        m_receiver_socket->disconnectFromHost();
    }
*/
}

void Peer::displayError(QAbstractSocket::SocketError socketError)
{
    /*
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(m_sender_socket->errorString()));
    }
    */
}

void Peer::set_receiver_port(const QString &receiver_port)
{
    m_receiver_port = receiver_port;
}

void Peer::set_receiver_IP(const QString &receiver_IP)
{
    m_receiver_IP = receiver_IP;
}




