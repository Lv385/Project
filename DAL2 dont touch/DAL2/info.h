#ifndef INFO_H
#define INFO_H
#include "statement.h"

namespace SQLDAL {

struct UsersID {
  unsigned int first_user_id;
  unsigned int second_user_id;
};

class Info : public Statement {
 public:
  Info(std::shared_ptr<Connect> Connect) : Statement(Connect) {}
  Info() {}

  virtual void			   Add(const UsersID& users_id) = 0;
  virtual QVector<UsersID> Get(const unsigned int id) = 0;
  virtual void             Delete(const UsersID& users_id) = 0;

 protected:
  virtual QString          AddQuery(const UsersID& users_id) = 0;
  virtual QString		   GetQuery(const unsigned int id) = 0;
  virtual QString		   DeleteQuery(const UsersID& users_id) = 0;
};
}  // namespace SQLDAL
#endif  // !INFO_H
