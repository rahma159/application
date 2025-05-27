#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_Projet");
    db.setUserName("consultiq");
    db.setPassword("hexacore");

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Error: " << db.lastError().text();
    }

    return test;
}

