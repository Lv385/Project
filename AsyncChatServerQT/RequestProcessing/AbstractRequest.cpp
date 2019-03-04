#include "AbstractRequest.h"



AbstractRequest::AbstractRequest(QByteArray& r, DAL &d) : database(d)
{
}



void AbstractRequest::connected() {

}