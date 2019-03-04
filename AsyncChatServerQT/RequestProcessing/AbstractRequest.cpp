#pragma once
#include "AbstractRequest.h"



AbstractRequest::AbstractRequest(std::vector<std::string>& r, DAL &d) :request(r), database(d)
{
}



void AbstractRequest::connected() {

}