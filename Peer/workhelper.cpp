#include "workhelper.h"

WorkHelper::WorkHelper(QObject *parent, QTcpSocket* socket)
    : QObject(parent) 
      , peer_info() {
  
}

WorkHelper::~WorkHelper() {}

AbstractStrategy* WorkHelper::GetWork() { return nullptr; }

void WorkHelper::OnReadyRead() {
  

  //// work on all requests if there are more than one
  //// using such a separator, untill we design something better
  // (data_->contains(k_unpossiblle_2_bytes_sequence_)) {
  //  separatorIndex = data_->indexOf(k_unpossiblle_2_bytes_sequence_);

  //  nextData = data_->mid(separatorIndex + 2);
  //  *data_ = data_->left(separatorIndex);

  //  // here we should change behaviour depening on type of message
  //  quint16 requestType = Parser::getRequestType(*data_);
  //}
  // if there is a part of another request, save it
}

//#tofix should be refactored
