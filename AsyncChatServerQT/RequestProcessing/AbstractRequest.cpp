#include "AbstractRequest.h"




AbstractRequest::AbstractRequest(QByteArray& r, DAL &d) : database(d)
{
}
AbstractRequest::AbstractRequest(QByteArray& r)
{

}


void AbstractRequest::connected() {

}