<<<<<<< HEAD
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
    QSqlDatabase db;
public:
    Connection();
    bool createConnection();
    bool updateConnection();
    void closeConnection();

};

#endif // CONNECTION_H
=======
#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{

    QSqlDatabase db;

public:
    Connection();
    bool createconnect();
    void closeConnection();
};

#endif // CONNECTION_H
>>>>>>> dda11e097df4406bc6cbcd6cfed77643a4845011
