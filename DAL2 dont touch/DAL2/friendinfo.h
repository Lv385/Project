#ifndef FRIEND_INFO_H
#define FRIEND_INFO_H

#include "info.h"
namespace SQLDAL {
  class FriendInfo : public Info {
   public:
	FriendInfo(std::shared_ptr<Connect> Connect);
	FriendInfo();
	void					Add(UsersID users_id);
	QVector<UsersID>		Get(const unsigned int id);
	void				    Delete(UsersID users_id);

   protected:
	QString				AddQuery(UsersID users_id);
	QString				GetQuery(const unsigned int id);
	QString				DeleteQuery(UsersID users_id);
  };
}  // namespace SQLDAL

#endif  // !FRIEND_INFO_H
