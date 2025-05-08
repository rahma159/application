#ifndef CREATEEDITINVOICEDIALOG_H
#define CREATEEDITINVOICEDIALOG_H
#include <QDialog> // Replace QDialogwith QDialogfor inheritance
#include <QList>
#include <QDate>
#include <QDateTime> // <-- NÉCESSAIRE pour QDateTime
#include <QTime>     // <-- NÉCESSAIRE pour QTime
#include "invoicemanagementwidget.h"
// Forward declarations
namespace Ui {
class CreateEditInvoiceDialog;
}
class Invoices;
class InvoiceLineItem;
class QSqlDatabase;
class QSqlError;


class CreateEditInvoiceDialog : public QDialog  { // Change inheritance from QDialogto QDialog
    Q_OBJECT

public:
    explicit CreateEditInvoiceDialog(QDialog  *parent = nullptr);
    ~CreateEditInvoiceDialog();

    void prepareForNewInvoice();
    bool loadInvoiceForEditing(int invoiceId);

private slots:
    void on_saveDraftButton_clicked();
    void on_saveAndSendButton_clicked();
    void on_addLineItemButton_clicked();
    void on_removeLineItemButton_clicked();
    void on_previewButton_clicked();
    void on_cancelInvoiceButton_clicked();

    void on_clientSelectComboBox_currentIndexChanged(int index);
    void on_issueDateEdit_dateTimeChanged(const QDateTime &dateTime);
    void on_paymentTermsLineEdit_textChanged(const QString &arg1);
    void on_lineItemsTableWidget_cellChanged(int row, int column);
private:
    Ui::CreateEditInvoiceDialog *ui;
    int currentInvoiceId;
    bool isEditMode;

    void setupConnections();
    void setupLineItemsTable();
    void populateClientComboBox();
    void displayClientDetails(int clientId);
    void calculateAndDisplayTotals();
    void updateDueDate();

    void populateUiFromInvoice(const Invoices& invoice);
    void populateInvoiceObjectFromUi(Invoices& invoiceToPopulate, QList<InvoiceLineItem>& itemsToPopulate);
    void on_dueDateEdit_dateTimeChanged(const QDateTime &dateTime);
    void saveInvoice(const QString& status);


};

#endif // CREATEEDITINVOICEDIALOG_H
