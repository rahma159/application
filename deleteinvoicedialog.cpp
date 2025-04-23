#include "deleteinvoicedialog.h"
#include "ui_deleteinvoicedialog.h"
#include "invoices.h" // Include Invoices header for the static remove function

#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery> // Include if Invoices::remove needs it implicitly (it does in the simplified version)
#include <QSqlError> // Include if Invoices::remove uses it

DeleteInvoiceDialog::DeleteInvoiceDialog(int invoiceId, const QString& invoiceNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteInvoiceDialog),
    m_invoiceIdToDelete(invoiceId),         // Store the passed ID
    m_invoiceNumberToDelete(invoiceNumber) // Store the passed number
{
    ui->setupUi(this);
    setWindowTitle(tr("Confirm Deletion"));

    // Display the ID and number in the read-only line edits
    ui->invoiceIdLineEdit->setText(QString::number(m_invoiceIdToDelete));
    ui->invoiceNumberLineEdit->setText(m_invoiceNumberToDelete);

    // Connect the custom delete button
    // connect(ui->deleteButton, &QPushButton::clicked, this, &DeleteInvoiceDialog::on_deleteButton_clicked); // Already connected by name convention

    // Connect the standard Cancel button to QDialog::reject()
    // (Can be done automatically by name convention if objectName is 'cancelButton' or in a QDialogButtonBox)
    // Or connect explicitly if needed:
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

DeleteInvoiceDialog::~DeleteInvoiceDialog()
{
    delete ui;
}

// Slot executed when the "Delete" button in THIS dialog is clicked
void DeleteInvoiceDialog::on_deleteButton_clicked()
{
    qDebug() << "Delete button clicked in confirmation dialog for ID:" << m_invoiceIdToDelete;

    // Call the SIMPLIFIED static-like remove function from Invoices class
    // Pass the ID and potentially the number (as per your simplified function signature)
    // NOTE: Using static call style as your simplified `remove` didn't seem to need an object instance
    // Adjust if your final `remove` signature is different.
    bool success = Invoices::remove(m_invoiceIdToDelete);

    if (success) {
        qDebug() << "Deletion successful in database for ID:" << m_invoiceIdToDelete;
        QMessageBox::information(this, tr("Delete Successful"),
                                 tr("Invoice '%1' (ID: %2) was successfully deleted.")
                                     .arg(m_invoiceNumberToDelete) // Still use number for message
                                     .arg(m_invoiceIdToDelete));
        accept();
    } else {
        // Get last error
        QSqlQuery query;
        QSqlError error = query.lastError();
        qWarning() << "Deletion failed in database for ID:" << m_invoiceIdToDelete << "Error:" << error.text();
        QMessageBox::critical(this, tr("Delete Failed"),
                              tr("Could not delete invoice '%1'.\n\nError: %2")
                                  .arg(m_invoiceNumberToDelete)
                                  .arg(error.text()));
    }
}
