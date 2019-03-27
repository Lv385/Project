#ifndef FRIEND_INFO_H
#define FRIEND_INFO_H

#include "info.h"
namespace SQLDAL {
class FriendInfo : public Info {
 public:
  FriendInfo(std::shared_ptr<Connect> Connect);
  FriendInfo();
  void					Add();
  QVector<FriendInfo> Get(const unsigned int id);
  void				    Delete();

 protected:
  QString AddQuery();
  QString GetQuery(const unsigned int id);
  QString DeleteQuery();
};
}  // namespace SQLDAL

#endif  // !FRIEND_INFO_H
