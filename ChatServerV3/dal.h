#ifndef DAL_H
#define DAL_H

#include "client.h"

#include <QString>
#include <map>



class DAL
{
public:
    DAL();
    //interface associated with database access will be placed here
    void setClient(QString, Client);
    Client getClient(QString);
private:
    std::map<QString, Client> database;
};

#endif // DAL_H
