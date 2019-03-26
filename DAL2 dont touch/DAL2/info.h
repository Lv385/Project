#ifndef INFO_H
#define INFO_H
#include "statement.h"

namespace SQLDAL {
class Info : public Statement {
 public:
  virtual void Add(const unsigned int first_user_id,
                   const unsigned int second_user_id) = 0;
  virtual QVector<unsigned int> Get(const unsigned int id) = 0;
  virtual void Delete(const unsigned int first_user_id,
                      const unsigned int second_user_id) = 0;

 protected:
  virtual QString AddQuery(const unsigned int first_user_id,
                           const unsigned int second_user_id) = 0;
  virtual QString GetQuery(const unsigned int id) = 0;
  virtual QString DeleteQuery(const unsigned int first_user_id,
                              const unsigned int second_user_id) = 0;
};
}  // namespace SQLDAL
#endif  // !INFO_H
