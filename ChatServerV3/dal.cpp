#include "dal.h"

DAL::DAL()
{

}

void DAL::setClient(QString ip, Client cl){
    database[ip]=cl;
}
Client DAL::getClient(QString ip){
    return database[ip];
}
