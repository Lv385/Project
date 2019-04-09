#include "friendrequest.h"
namespace dal {
FriendRequests::FriendRequests(std::shared_ptr<Connect> Connect) : Statement(Connect) {
	connection_->Open(CLIENT_DB);
}

FriendRequests::FriendRequests()
{
}

void FriendRequests::Add(const FriendRequest & friend_request)
{
	ExectuteQuery(AddQuery(friend_request));
	query_.finish();
}

QVector<FriendRequest> FriendRequests::Get()
{
	QVector<FriendRequest> result;
	ExectuteQuery(GetQuery());
	FriendRequest friend_request;
	while (query_.next()) {

		friend_request.login = query_.record().value(0).toString();
		friend_request.type= query_.record().value(1).toBool();

		result.push_back(friend_request);
	}
	query_.finish();
	return result;
}

QVector<FriendRequest> FriendRequests::Get(const bool & type)
{
	QVector<FriendRequest> result;
	ExectuteQuery(GetQuery(type));
	FriendRequest friend_request;
	while (query_.next()) {

		friend_request.login = query_.record().value(0).toString();
		friend_request.type = query_.record().value(1).toBool();

		result.push_back(friend_request);
	}
	query_.finish();
	return result;
}

void FriendRequests::Delete(const FriendRequest & friend_request)
{
	ExectuteQuery(DeleteQuery(friend_request));
	query_.finish();
}

QString FriendRequests::AddQuery(const FriendRequest & friend_request)
{
	return QString(
		"insert into friend_request (user_login, request_type) values ('" +
		friend_request.login + "', " +
		QString::number(friend_request.type) + ")");
}

QString FriendRequests::GetQuery()
{
	return QString("select * from friend_request");
}

QString FriendRequests::GetQuery(const bool & type)
{
	return QString("select * from friend_request where request_type = " + QString::number(type));
}

QString FriendRequests::DeleteQuery(const FriendRequest & friend_request)
{
	return QString("delete from friend_request where user_login = '" +friend_request.login+"', and request_type = "+QString::number(friend_request.type));
}
}  // namespace dal
