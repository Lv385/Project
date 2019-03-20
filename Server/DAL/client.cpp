#include "client.h"


Client::Client()
{

}

Client::Client(QString log, QString pas, QHostAddress i, quint16 p):
	user_name(log), user_password(pas), user_ip(i), user_port(p)
{
}



QString Client::GetUserName() const
{
	return user_name;
}

void Client::SetUserName( QString &value)
{
	user_name = value;
}

QHostAddress Client::GetUserIp() const
{
	return user_ip;
}

void Client::SetUserIp(const QHostAddress &value)
{
	user_ip = value;
}

quint16  Client::GetUserPort() const
{
	return user_port;
}

void Client::SetUserPort(const quint16 value)
{
	user_port = value;
}

quint32 Client::GetUserId() const
{
	return id;
}

void Client::SetUserId(const quint32 i)
{
	id = i;
}

QString Client::GetUserPassword() const
{
	return user_password;
}

void Client::SetUserPassword( QString &value)
{
	user_password = value;
}

void Client::AddFriend(Client& cl)
{	
	friends.push_back(cl.GetUserId());

}
/*Populate internal pending_requests_ vector.
* Receives instance of a client that want to be a friend of this user
*/
void Client::AddPendingFriendRequest(Client &cl) {
  pending_requests_.push_back(cl.GetUserId());
}

void Client::RemovePendingFriendRequest(Client &cl ) {
  for (int i = 0; i < pending_requests_.size(); i++) {
    if (pending_requests_[i] == cl.GetUserId()) {
      pending_requests_.remove(i);
    }
  }
}

void Client::RemoveFriend(Client & cl)
{	
	for (int i = 0; i < friends.size(); i++) {
		if (friends[i] == cl.GetUserId()) {
            friends.remove(i);
		}
	}
	
}

void Client::SetFriends(QVector<unsigned int> f)
{
	friends = f; 
}

void Client::Set_Pending_Request(QVector<unsigned int> r) {
  pending_requests_ = r;
}

void Client::AddPendingNotifiacation(Client &cl) {
  pending_friend_notifications_.push_back(cl.GetUserId());
}

void Client::RemovePendingNotification(Client &cl) {
  for (int i = 0; i < pending_friend_notifications_.size(); i++) {
    if (pending_friend_notifications_[i] == cl.GetUserId()) {
      pending_friend_notifications_.remove(i);
    }
  }
}

void Client::Set_Pending_Noification(QVector<unsigned int>r) {
  pending_requests_ = r;
}

QVector<unsigned int> *Client::Get_Pending_Notifications() { 
  return &pending_friend_notifications_;
 }

QVector<unsigned int> Client::GetFriends()
{
	return friends; }

QVector<unsigned int>* Client::Get_Pending_Requests() {
  return &pending_requests_;
}

bool Client::operator==(const Client &cl)
{
	return this->user_name.compare(cl.user_name) == 0;
}

std::ostream & operator<<(std::ostream & out, const Client& cl)
{
	out << cl.GetUserName().toStdString() << " " << cl.GetUserIp().toString().toStdString() << " " << cl.GetUserPassword().toStdString() << " " << cl.GetUserPort();
	return out;
}
