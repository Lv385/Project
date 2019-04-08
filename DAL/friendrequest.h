#ifndef FRIEND_REQUEST_H
#define FRIEND_REQUEST_H

#include "statement.h"

namespace dal {
	class FriendRequests : public Statement {
	public:
		FriendRequests(std::shared_ptr<Connect> Connect);
		FriendRequests();
		void					 Add(const FriendRequest& friend_request);
		QVector<FriendRequest>   Get();
		QVector<FriendRequest>   Get(const bool& type);
		void					 Delete(const FriendRequest& friend_request);

	private:
		QString					 AddQuery(const FriendRequest& friend_request);
		QString					 GetQuery();
		QString					 GetQuery(const bool& type);
		QString				     DeleteQuery(const FriendRequest& friend_request);
	};
}  // namespace dal

#endif  // !FRIEND_REQUEST_H
