#ifndef DELETE_FRIEND_NOTIFICATION_H
#define DELETE_FRIEND_NOTIFICATION_H

#include "info.h"

namespace dal {

	class DeleteFriendNotification : public Info
	{
	public:
		DeleteFriendNotification();
		DeleteFriendNotification(std::shared_ptr<Connect> Connect);
		
		void			   Add(const UsersID& users_id);
		QVector<UsersID>   Get(const unsigned int id);
		void			   Delete(const UsersID& users_id);

	protected:
		QString		       AddQuery(const UsersID& users_id);
		QString		       GetQuery(const unsigned int id);
		QString		       DeleteQuery(const UsersID& users_id);
	};
}
#endif  // !DELETE_FRIEND_NOTIFICATION_H
