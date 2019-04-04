#ifndef REQUEST_INFO_H
#define REQUEST_INFO_H

#include "info.h"
namespace SQLDAL {
  class RequestInfo : public Info {
   public:
	RequestInfo(std::shared_ptr<Connect> Connect);
	RequestInfo();
	void			   Add(const UsersID& users_id);
	QVector<UsersID>   Get(const unsigned int id);
	void               Delete(const UsersID& users_id);

   protected:
	QString            AddQuery(const UsersID& users_id);
	QString		       GetQuery(const unsigned int id);
	QString            DeleteQuery(const UsersID& users_id);
  };
}  // namespace SQLDAL

#endif  // !REQUEST_INFO_H
