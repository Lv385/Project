#include "LoginRequest.h"

LoginRequest::LoginRequest(QByteArray & A, DAL * d):AbstractRequest(A, d)
{
	log_ = Parser::ParseAsLoginOrRegisterInfo(A);
	prepareResponse();
}

void LoginRequest::prepareResponse()
{
	//check user in db  and set t or f
	requester_ = database->getClient(log_.id);
	if (requester_.GetUserName().length() > 1) {
		requester_.SetUserIp(log_.ip);
		requester_.SetUserPort(log_.port);

		database->setClient(requester_);
		logcheck = true;
	} else {
		logcheck = false;
	}

}
bool LoginRequest::sendResponde(QTcpSocket * initByClient)
{
	//send enum answer to client
	if (logcheck == true) {

		QByteArray b = Parser::yesNoResponseToByteArray((quint8)ServerRequests::LOGIN_SUCCEED);
		b.append(Parser::GetUnpossibleSequence());
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();

		
		Client updatedClient = database->getClient(requester_.GetUserName());
		toSend_.id = updatedClient.GetUserId();
		toSend_.ip = updatedClient.GetUserIp();
		toSend_.port = updatedClient.GetUserPort();

		QByteArray raw_data = Parser::FriendUpdateInfo_ToByteArray(toSend_);
		raw_data.append(Parser::GetUnpossibleSequence());

		QVector<unsigned int> currentFriends = updatedClient.GetFriends();
		QTcpSocket output_socket;
		for (unsigned i = 0; i < currentFriends.size(); i++) {
			Client tempClient = database->getClient(currentFriends[i]);
			output_socket.connectToHost(tempClient.GetUserIp(), tempClient.GetUserPort());
			if (output_socket.waitForConnected(5000)) {
				output_socket.write(raw_data);
				output_socket.waitForBytesWritten(1000);
				output_socket.disconnectFromHost();
			}
		}
		output_socket.close();
	}else {

		QByteArray b = Parser::yesNoResponseToByteArray((quint8)ServerRequests::LOGIN_FAILED);
		b.append(Parser::GetUnpossibleSequence());
		initByClient->write(b);
		initByClient->waitForBytesWritten(3000);
		initByClient->disconnectFromHost();
	}
	return true;
}

