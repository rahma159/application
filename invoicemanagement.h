#ifndef INVOICEMANAGEMENTWIDGET_H
#define INVOICEMANAGEMENTWIDGET_H

#include <QDialog> // Or QWidget if you changed the base class

// Forward declaration for the UI class
namespace Ui {
class InvoiceManagementWidget;
}

// Forward declaration for data model (replace with your actual model class)
class QStandardItemModel; // Example: Use QStandardItemModel or your custom model

class InvoiceManagementWidget : public QDialog // Or QWidget
{
    Q_OBJECT

public:
    explicit InvoiceManagementWidget(QWidget *parent = nullptr);
    ~InvoiceManagementWidget();

private slots:
    // Slots for top buttons
    void on_createInvoiceButton_clicked();
    void on_editInvoiceButton_clicked();   // Renamed from NewInvoiceButton
    void on_deleteInvoiceButton_clicked(); // Renamed from pushButton
    void on_markAsPaidButton_clicked();
    void on_sendInvoiceButton_clicked();
    void on_exportPdfButton_clicked();
    void on_exportFecButton_clicked();

    // Slots for filter controls
    void on_applyFiltersButton_clicked();
    void on_clearFiltersButton_clicked();

    // Slot for table selection changes (to enable/disable buttons)
    void on_invoiceTableView_selectionChanged(); // Connect manually if needed

private:
    Ui::InvoiceManagementWidget *ui;
    QStandardItemModel *invoiceModel; // Example data model pointer

    void setupConnections();
    void populateInvoiceTable(); // Load/refresh data into the table
    void updateSummaryLabels();  // Update totals at the bottom
    void updateButtonStates();   // Enable/disable buttons based on selection/state
    void applyFilters();         // Helper to apply current filters
};

#endif // INVOICEMANAGEMENTWIDGET_H
