#include "unitofwork.h"
namespace SQLDAL {
std::atomic<unsigned int> UnitOfWork::connection_number_ = 0;

UnitOfWork::UnitOfWork() : connection_(nullptr) {}

void UnitOfWork::GenerateUniqueConnection() {
  connection_ = std::make_shared<Connect>(GenerateNewConnection());
}

UnitOfWork::~UnitOfWork() { connection_->Close(); }

QString UnitOfWork::GenerateNewConnection() {
  return QString("Connection number:" + QString::number(connection_number_++));
}
}  // namespace SQLDAL