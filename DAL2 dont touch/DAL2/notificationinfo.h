#ifndef NOTIFICATION_INFO_H
#define NOTIFICATION_INFO_H

#include "info.h"
namespace SQLDAL {
class NotificationInfo : public Info {
 public:
  NotificationInfo(std::shared_ptr<Connect> Connect);
  NotificationInfo();
  void Add();
  QVector<NotificationInfo> Get(const unsigned int id);
  void Delete();

 protected:
  QString AddQuery();
  QString GetQuery(const unsigned int id);
  QString DeleteQuery();
};
}  // namespace SQLDAL

#endif  // !NOTIFICATION_INFO_H
