#ifndef FRIEND_INFO_H
#define FRIEND_INFO_H

#include "info.h"
namespace SQLDAL {
class FriendInfo : public Info {
 public:
  FriendInfo(std::shared_ptr<Connect> Connect);
  void					Add(const unsigned int first_user_id,
							const unsigned int second_user_id);
  QVector<unsigned int> Get(const unsigned int id);
  void				    Delete(const unsigned int first_user_id,
							   const unsigned int second_user_id);

 protected:
  QString AddQuery(const unsigned int first_user_id,
                   const unsigned int second_user_id);
  QString GetQuery(const unsigned int id);
  QString DeleteQuery(const unsigned int first_user_id,
                      const unsigned int second_user_id);
};
}  // namespace SQLDAL

#endif  // !FRIEND_INFO_H
