#ifndef	REQUEST_INFO_H
#define REQUEST_INFO_H

#include "info.h"
namespace SQLDAL {
class RequestInfo : public Info {
 public:
	 RequestInfo(unsigned int f_id, unsigned int s_id, std::shared_ptr<Connect> Connect);
  RequestInfo(std::shared_ptr<Connect> Connect);
  RequestInfo();
  void Add();
  QVector<RequestInfo> Get(const unsigned int id);
  void Delete();

 protected:
  QString AddQuery();
  QString GetQuery(const unsigned int id);
  QString DeleteQuery();
};
}  // namespace SQLDAL

#endif  // !REQUEST_INFO_H
