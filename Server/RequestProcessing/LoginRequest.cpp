#include "LoginRequest.h"

LoginRequest::LoginRequest(QByteArray& A, DAL* d, QTcpSocket* s)
    : AbstractRequest(d,s) {
	incoming_structure_ = Parser::ParseAsLoginInfo(A);
	PrepareResponse();
}

void LoginRequest::PrepareResponse()
{
	//check user in db  and set t or f
	requester_ = database_->getClient(incoming_structure_.id);
	if (requester_.GetUserName().length() > 1) {
		requester_.SetUserIp(incoming_structure_.ip);
		requester_.SetUserPort(incoming_structure_.port);

		database_->SetClient(requester_);
		logcheck = true;
	} else {
		logcheck = false;
	}

}
bool LoginRequest::SendResponde()
{
	//send enum answer to client
	if (logcheck == true) {

		QByteArray b = Parser::Empty_ToByteArray((quint8)ServerRequests::LOGIN_SUCCEED);
		b.append(Parser::GetUnpossibleSequence());
		client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();

		
		Client updatedClient = database_->getClient(requester_.GetUserName());
		toSend_.id = updatedClient.GetUserId();
		toSend_.ip = updatedClient.GetUserIp();
		toSend_.port = updatedClient.GetUserPort();

		QByteArray raw_data = Parser::FriendUpdateInfo_ToByteArray(toSend_);
		raw_data.append(Parser::GetUnpossibleSequence());

		QVector<unsigned int> currentFriends = updatedClient.GetFriends();
		QTcpSocket output_socket;
		for (unsigned i = 0; i < currentFriends.size(); i++) {
			Client tempClient = database_->getClient(currentFriends[i]);
			output_socket.connectToHost(tempClient.GetUserIp(), tempClient.GetUserPort());
			if (output_socket.waitForConnected(5000)) {
				output_socket.write(raw_data);
				output_socket.waitForBytesWritten(1000);
				output_socket.disconnectFromHost();
			}
		}
		output_socket.close();
	}else {

		QByteArray b = Parser::Empty_ToByteArray((quint8)ServerRequests::LOGIN_FAILED);
		b.append(Parser::GetUnpossibleSequence());
		client_socket_->write(b);
    client_socket_->waitForBytesWritten(3000);
    client_socket_->disconnectFromHost();
	}
	return true;
}

