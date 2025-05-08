#ifndef DELETEINVOICEDIALOG_H
#define DELETEINVOICEDIALOG_H

#include <QDialog>
#include <QString>

// Forward declaration for the UI class
namespace Ui {
class DeleteInvoiceDialog;
}

class DeleteInvoiceDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor takes the ID and Number to display/delete
    explicit DeleteInvoiceDialog(int invoiceId, const QString& invoiceNumber, QWidget *parent = nullptr);
    ~DeleteInvoiceDialog();

private slots:
    // Slot for the custom Delete button
    void on_deleteButton_clicked();
    // The Cancel button can just use the default reject() slot

private:
    Ui::DeleteInvoiceDialog *ui;
    int m_invoiceIdToDelete; // Store the ID passed to the constructor
    QString m_invoiceNumberToDelete; // Store the number passed
};

#endif // DELETEINVOICEDIALOG_H
