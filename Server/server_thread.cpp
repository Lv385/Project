#include "server_thread.h"
#include <QTcpSocket>
#include <sstream>
#include "RequestProcessing/new_user_request.h"
#include "RequestProcessing/login_request.h"
#include "RequestProcessing/add_friend_request.h"
#include "RequestProcessing/friendship_request.h"
#include "RequestProcessing/delete_friend_request.h"

ServerThread::ServerThread(int socket_descriptor, QObject *parent) : QThread(parent),socket_descriptor_(socket_descriptor)
{
	qDebug() << "New threaded connection!\a\n";
}


void ServerThread::run()
{
	QTcpSocket incomming_connection;
  incomming_connection.setSocketDescriptor(socket_descriptor_);
	
	if (incomming_connection.waitForReadyRead(10000)) 
	{
		
          data_ = incomming_connection.readAll();
          SetRequest(Parser::getRequestType(data_), &incomming_connection);
    
    
		request_->SendResponde();
    // Watch out!!! This thread should be alive till incomming_connection is in use
    //Consider parcing while(signal) here
	}
}

void ServerThread::SetRequest(quint8 type, QTcpSocket* connection)
{	
	switch (type)
	{
	case (quint8)ClientRequest::REGISTER: 
		 request_ = new NewUserRequest(data_, &dal_, connection); 
		 break;
	case (quint8)ClientRequest::LOGIN:
     request_ = new LoginRequest(data_, &dal_, connection);
     break;
  case (quint8)ClientRequest::FRIEND_REQUEST:
    request_ = new AddFriendRequest(data_, &dal_, connection);
    break;
  case (quint8)ClientRequest::FRIENDSHIP_ACCEPTED:
  case (quint8)ClientRequest::FRIENDSHIP_REJECTED:
    request_ = new FriendshipRequest(data_, &dal_, connection);
    break;
  case(quint8)ClientRequest::DELETE_REQUEST:
    request_ = new DeleteFriendRequest(data_, &dal_, connection);
    break;
  default:
    qDebug() << "No such type of request" << "\n";
    break;
	}
}


ServerThread::~ServerThread()
{
	delete request_; 
}
