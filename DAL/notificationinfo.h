#ifndef NOTIFICATION_INFO_H
#define NOTIFICATION_INFO_H

#include "info.h"
namespace SQLDAL {
  class NotificationInfo : public Info {
   public:
	NotificationInfo(std::shared_ptr<Connect> Connect);
	NotificationInfo();
	void			   Add(const UsersID& users_id);
	QVector<UsersID>   Get(const unsigned int id);
	void			   Delete(const UsersID& users_id);

   protected:
	QString		       AddQuery(const UsersID& users_id);
	QString		       GetQuery(const unsigned int id);
	QString		       DeleteQuery(const UsersID& users_id);
  };
}  // namespace SQLDAL

#endif  // !NOTIFICATION_INFO_H
