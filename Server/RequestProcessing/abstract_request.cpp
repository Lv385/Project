#include "abstract_request.h"


AbstractRequest::AbstractRequest(DAL* d, QTcpSocket* s)
    : database_(d), client_socket_(s){
}

void AbstractRequest::connected() {

}