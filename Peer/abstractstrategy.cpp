#include "abstractstrategy.h"
#include "signalredirector.h"


AbstractStrategy::AbstractStrategy() { }


AbstractStrategy::AbstractStrategy(QByteArray data)
    : data_(data){
}

void AbstractStrategy::set_data(QByteArray data) { 
  data_ = data; 
}

AbstractStrategy::~AbstractStrategy() {}

