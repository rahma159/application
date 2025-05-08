// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invoicemanagementwidget.h"
#include "settingsdialog.h" // Make sure it's included if not already by mainwindow.h

#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , invoiceWidget(nullptr)
    , m_settingsDialog(nullptr) // <<< INITIALIZE THE POINTER
{
    ui->setupUi(this);

    // --- Database Connection Check ---
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QMessageBox::information(this,
                                 tr("Database Connection"),
                                 tr("Database connected successfully!"));
        qDebug() << "MainWindow: Confirmed database connection is open.";
    } else {
        QMessageBox::critical(this, tr("Database Error"),
                              tr("CRITICAL: Database connection failed or was lost. Please check configuration or restart."));
        qDebug() << "MainWindow: CRITICAL - database connection found closed or invalid.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_manageInvoicesButton_clicked()
{
    qDebug() << "Manage Invoices button clicked.";
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available. Cannot manage invoices."));
        qDebug() << "Manage Invoices aborted: Database connection lost.";
        return;
    }

    if (!invoiceWidget) {
        invoiceWidget = new InvoiceManagementWidget(this);
        invoiceWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(invoiceWidget, &QObject::destroyed, this, &MainWindow::onInvoiceWidgetDestroyed);
        invoiceWidget->show();
    } else {
        invoiceWidget->raise();
        invoiceWidget->activateWindow();
    }
}

void MainWindow::onInvoiceWidgetDestroyed()
{
    qDebug() << "InvoiceManagementWidget destroyed, resetting pointer.";
    invoiceWidget = nullptr;
}

// vvv ADD THIS METHOD vvv
void MainWindow::on_settingsButton_clicked() // Ensure your button is named 'settingsButton' in the .ui file
{
    qDebug() << "Settings button clicked.";

    // Option 1: Create a new dialog each time (common for modal dialogs)
    SettingsDialog settingsDlg(this); // Create on stack, parented to MainWindow
    if (settingsDlg.exec() == QDialog::Accepted) {
        qDebug() << "Settings dialog accepted (saved).";
        // Optionally, you can add code here to react to settings changes
        // For example, refresh parts of your UI or reload data that depends on settings.
    } else {
        qDebug() << "Settings dialog rejected (cancelled).";
    }

}
// ^^^ END OF ADDED METHOD ^^^
