#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include "enhanced_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ✅ Configure Oracle ODBC connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("consulting_office2");  // 🛠 Replace with your actual DSN
    db.setUserName("consultiq");               // 🛠 Replace with your Oracle username
    db.setPassword("hexacore");                // 🛠 Replace with your Oracle password

    // ❌ Check database connection
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Connection Failed", db.lastError().text());
        return -1;
    }

    // 🪟 Show the main window
    EnhancedMainWindow window;
    window.show();

    return app.exec();
}
