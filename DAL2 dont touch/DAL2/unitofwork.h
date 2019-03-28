#ifndef UNITOFWORK_H
#define UNITOFWORK_H

#include <QString>
#include <atomic>
#include "statement.h"

namespace SQLDAL {

  class UnitOfWork {
   public:
	UnitOfWork();
	~UnitOfWork();

	template <typename T>
	std::shared_ptr<T>			       GetEntity();
	void							   GenerateUniqueConnection();

   private:
	std::shared_ptr<Connect>		   connection_;
	static std::atomic<unsigned int>   connection_number_;
	QString						       GenerateNewConnection();
  };

  template <typename T>
  std::shared_ptr<T> UnitOfWork::GetEntity() {
	return std::make_shared<T>(connection_);
  }

}  // namespace SQLDAL
#endif  // !UNITOFWORK_H
