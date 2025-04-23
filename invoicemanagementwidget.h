#ifndef INVOICEMANAGEMENTWIDGET_H
#define INVOICEMANAGEMENTWIDGET_H

#include "invoices.h"
#include <QDialog>
#include <QItemSelection> // Needed for selectionChanged signal


// Forward declare classes to reduce include dependencies
namespace Ui { class InvoiceManagementWidget; }
class CreateEditInvoiceDialog;
class QSqlTableModel;
class QSqlQueryModel;
/*class QItemSelectionModel; // For signal parameter type
class QString; // Forward declare QString (though often included via other Qt headers)
class Invoices; // Forward declare your full Invoices data class/struct
class SomeFecDataStructure; // Forward declare the structure holding FEC data
template <typename T> class QList;
*/
class InvoiceManagementWidget : public QDialog
{
    Q_OBJECT

public:
    explicit InvoiceManagementWidget(QWidget *parent = nullptr);
    ~InvoiceManagementWidget();

private slots:
    // Filter/Action Buttons - Linked by on_... convention
    void on_applyFiltersButton_clicked();
    void on_clearFiltersButton_clicked();
    void on_newInvoiceButton_clicked();
    void on_editInvoiceButton_clicked();
    // Ensure button exists in UI



    void on_tableView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void handleTableViewClicked(const QModelIndex &index); // <<< NEW SLOT
    void on_deleteInvoiceButton_clicked();

    void on_tableView_activated(const QModelIndex &index);
    void on_markAsPaidButton_clicked();
    void on_sendInvoiceButton_clicked();
    /*void on_exportPdfButton_clicked();

    void on_exportFecbutton_clicked();*/

private:
    Ui::InvoiceManagementWidget *ui;
    QSqlQueryModel *model; // Model to display invoice list

    // === Private Helper Methods ===
    // These NEED to be implemented in the .cpp file
    void setupConnections();        // Connect signals/slots
    void loadInvoices(const QString &filterClause = ""); // Core data loading method
    void refreshInvoiceList();      // Reloads data using current filters
    int getSelectedInvoiceId();     // Safely gets ID from selected row
    void populateFilterComboBoxes(); // Fills filter dropdowns

   /* bool generateInvoicePdf(const QString &filePath, const Invoices &invoiceData);
    bool generateFecFile(const QString &filePath, const QList<SomeFecDataStructure> &fecData);*/

};

#endif // INVOICEMANAGEMENTWIDGET_H
