#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

static bool createConnection() {
    const QString connectionName = "OdbcConnection"; // Can keep same or change

    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase existingDb = QSqlDatabase::database(connectionName);
        if (existingDb.isOpen()) {
            qDebug() << "Database connection" << connectionName << "already open.";
            return true;
        }
        QSqlDatabase::removeDatabase(connectionName);
    }

    // --- Use the ODBC driver ---
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); // <<< CHANGE Driver to QODBC


    db.setDatabaseName("Source_Projet2A"); // <<< REPLACE with the EXACT DSN name you created
    db.setUserName("consultiq");          // Your Oracle username
    db.setPassword("hexacore");           // Your Oracle password




    // Try to open the connection using the DSN configuration
    if (!db.open()) {
        qCritical() << "Database Error: Failed to connect via ODBC! Connection Name:" << connectionName;
        qCritical() << "Error Details:" << db.lastError().text(); // This error might come from ODBC or Oracle
        qCritical() << "Check DSN Name:" << db.databaseName() << "User:" << db.userName();
        qCritical() << "Ensure the System DSN '" << db.databaseName() << "' is configured correctly in the 64-bit ODBC Administrator.";
        qCritical() << "Ensure the Oracle ODBC driver is installed (matching application architecture).";
        qCritical() << "Ensure Oracle client libraries are accessible (PATH).";
        qCritical() << "Ensure the Oracle Listener service is running.";
        return false;
    } else {
        qDebug() << "Database connected successfully via ODBC DSN:" << db.databaseName();
    }
    return true;
}

#endif // DBCONNECTION_H
