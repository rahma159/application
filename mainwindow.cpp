#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invoicemanagementwidget.h" // Already included via mainwindow.h, but explicit include here is fine too

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , invoiceWidget(nullptr) // Initialize the pointer
{
    ui->setupUi(this);

    // --- Database Connection Check ---
    QSqlDatabase db = QSqlDatabase::database(); // Get the default connection
    if (db.isOpen()) {
        // Use information level for success confirmation
        QMessageBox::information(this,
                                 tr("Database Connection"), // Use tr() for potential translation
                                 tr("Database connected successfully!"));
        qDebug() << "MainWindow: Confirmed database connection is open.";
    } else {
        // Use critical level for failure, as it might prevent app functionality
        QMessageBox::critical(this, tr("Database Error"),
                              tr("CRITICAL: Database connection failed or was lost. Please check configuration or restart."));
        qDebug() << "MainWindow: CRITICAL - database connection found closed or invalid.";
        // Consider disabling UI elements that require the database
        // ui->manageInvoicesButton->setEnabled(false);
        // ui->clientPaymentButton->setEnabled(false); // Payment likely needs DB too
    }

    // Ensure connections for buttons defined in the UI file are set up
    // Qt's auto-connection mechanism (on_<objectName>_<signalName>) handles this
    // if the slots are named correctly in the header and defined in the cpp.
}

MainWindow::~MainWindow()
{
    // invoiceWidget is managed by its WA_DeleteOnClose attribute if created,
    // so no 'delete invoiceWidget;' needed here generally, unless you
    // didn't set the attribute or close the window before MainWindow closes.
    delete ui;
}

void MainWindow::on_manageInvoicesButton_clicked()
{
    qDebug() << "Manage Invoices button clicked.";

    // Check DB connection again before opening sensitive windows
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available. Cannot manage invoices."));
        qDebug() << "Manage Invoices aborted: Database connection lost.";
        return; // Don't proceed
    }

    // Use the member pointer to manage a single instance of the invoice widget
    if (!invoiceWidget) { // If no instance exists yet
        invoiceWidget = new InvoiceManagementWidget(this); // Create it, parented to MainWindow
        // Set attribute to delete the object when the widget is closed
        invoiceWidget->setAttribute(Qt::WA_DeleteOnClose);
        // Connect the destroyed signal to our slot to reset the pointer
        connect(invoiceWidget, &QObject::destroyed, this, &MainWindow::onInvoiceWidgetDestroyed);
        invoiceWidget->show(); // Show the widget (non-modal)
    } else { // If an instance already exists
        invoiceWidget->raise(); // Bring the existing window to the front
        invoiceWidget->activateWindow(); // Give it focus
    }
}

// This slot is called when the InvoiceManagementWidget is closed (due to WA_DeleteOnClose)
void MainWindow::onInvoiceWidgetDestroyed()
{
    qDebug() << "InvoiceManagementWidget destroyed, resetting pointer.";
    invoiceWidget = nullptr; // Reset the pointer so a new one can be created next time
}





