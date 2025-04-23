#include "mainwindow.h"
#include "connection.h" // Include your connection header
#include <QApplication>
#include <QMessageBox> // For showing critical errors
#include <QSqlDatabase> // Include for checking connection later if needed
#include <QFile>      // <<< Include for file operations
#include <QTextStream>// <<< Include for reading file
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion")); // Optionnel, définit un style de base si le .qss ne couvre pas tout

    // --- Charger et appliquer le style AVANT de créer les widgets ---
    QFile styleFile(":/styles/style.qss");
    if (!styleFile.exists()) {
        qWarning() << "Style file not found at" << styleFile.fileName();
        // Procéder sans feuille de style ou afficher une erreur
    } else {
        if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Reading stylesheet from" << styleFile.fileName();
            QTextStream stream(&styleFile);
            QString styleSheet = stream.readAll();
            styleFile.close();
            a.setStyleSheet(styleSheet); // <-- APPLIQUER LE STYLE ICI !
            qDebug() << "Stylesheet applied.";
        } else {
            qWarning() << "Could not open style file:" << styleFile.errorString();
            qWarning() << "Error details:" << styleFile.errorString(); // Afficher l'erreur spécifique
        }
    }
    // --- Style appliqué ---


    // --- Establish Database Connection ---
    Connection dbConnection; // Create an instance of your Connection class
    if (!dbConnection.createConnection()) {
        // Critical error if connection fails on startup
        QMessageBox::critical(nullptr, "Database Connection Error",
                              "Failed to connect to the database.\n"
                              "Please check configuration and database status.\n"
                              "Application will exit.");
        return 1; // Exit the application
    } else {
        qDebug() << "Database connection established successfully."; // Optional confirmation
    }
    // --- Connection Established ---


    MainWindow w; // Create the main window (les widgets seront créés et stylés ici)
    w.show();     // Affiche la fenêtre principale

    int appResult = a.exec(); // <-- Démarrer la boucle d'événements MAINTENANT

    // --- Close Connection Before Exiting ---
    // Cette partie s'exécute lorsque a.exec() se termine
    dbConnection.closeConnection(); // Close using your class method
    qDebug() << "Database connection closed.";
    // --- Connection Closed ---

    return appResult;
}
