#include "mainwindow.h" // Include the MainWindow header
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection c;
    bool test = c.createconnect();
    MainWindow w; // Now MainWindow is recognized

    if (test)
    {
        qDebug() << "Connexion réussie!";
        w.show(); // 'w' is now declared
        // Optional: Show notification on successful connection
        // w.showNotification("Database", "Connection successful!"); // Need to make showNotification public or call it internally
    }
    else
    {
        qDebug() << "Connexion échouée!";
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
        return -1; // Exit if connection fails
    }

    return a.exec();
}
