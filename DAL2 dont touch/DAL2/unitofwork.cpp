#include "unitofwork.h"
namespace SQLDAL {
std::atomic<unsigned int> UnitOfWork::Connect_number_ = 0;

UnitOfWork::UnitOfWork() { Connect_ = nullptr; }

void UnitOfWork::GenerateUniqueConnection() {
  Connect_ = std::make_shared<Connect>(GenerateNewConnection());
}

UnitOfWork::~UnitOfWork() { Connect_->Close(); }

QString UnitOfWork::GenerateNewConnection() {
  return QString("Connection number:" + QString::number(Connect_number_++));
}
}  // namespace SQLDAL