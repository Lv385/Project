#ifndef INFO_H
#define INFO_H
#include "statement.h"

namespace SQLDAL {
	class Info : public Statement {
	public:
		Info(std::shared_ptr<Connect> Connect) :Statement(Connect) {}
		Info() {}
		unsigned int first_user_id;
		unsigned int second_user_id;

  virtual void Add() = 0;
  //virtual QVector<unsigned int> Get(const unsigned int id) = 0;
  virtual void Delete() = 0;

 protected:
  virtual QString AddQuery() = 0;
  virtual QString GetQuery(const unsigned int id) = 0;
  virtual QString DeleteQuery() = 0;
};
}  // namespace SQLDAL
#endif  // !INFO_H
