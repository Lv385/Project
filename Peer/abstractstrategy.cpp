#include "abstractstrategy.h"
#include "signalredirector.h"


AbstractStrategy::AbstractStrategy() 
  : redirector_(SignalRedirector::get_instance())
{ }


AbstractStrategy::AbstractStrategy(QByteArray data)
    : data_(data),
      redirector_(SignalRedirector::get_instance()){
}

void AbstractStrategy::set_data(QByteArray data) { 
  data_ = data; 
}

void AbstractStrategy::set_peer_info(PeerInfo info) { 
  peer_info_ = info; 
}

AbstractStrategy::~AbstractStrategy() {}

