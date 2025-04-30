#ifndef INVOICEMANAGEMENTWIDGET_H
#define INVOICEMANAGEMENTWIDGET_H

#include "invoices.h"
#include "statisticsdialog.h"
#include <QDialog>
#include <QItemSelection> // Needed for selectionChanged signal
#include <QString>      // Include QString
#include <QList>
#include <QAbstractItemModel>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel> // Might be needed for more advanced sorting later
#include <Qt>
#include <QSqlTableModel> // Forward declare if possible, otherwise include
#include <QTimer>
#include <QDate>

// Forward declare classes to reduce include dependencies
namespace Ui { class InvoiceManagementWidget; }
class CreateEditInvoiceDialog;
class QSqlTableModel;
class QSqlQueryModel;
class QModelIndex;    // Use forward declaration
class QLabel;
class StatisticsDialog;
class InvoiceManagementWidget : public QDialog
{
    Q_OBJECT

public:
    explicit InvoiceManagementWidget(QWidget *parent = nullptr);
    ~InvoiceManagementWidget();

private slots:
    void on_applyFiltersButton_clicked();
    void on_clearFiltersButton_clicked();
    void on_newInvoiceButton_clicked();
    void on_editInvoiceButton_clicked();
    void on_deleteInvoiceButton_clicked();
    void on_sendInvoiceButton_clicked();
    void on_markAsPaidButton_clicked();
    void on_exportInvoiceListPdfButton_clicked();
    void on_exportFecButton_clicked(); // Assuming TSV export button name
    void on_sortComboBox_currentIndexChanged(int index); // For the sort dropdown
    // --- Slots for Table View Interaction ---
    void on_tableView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_tableView_activated(const QModelIndex &index); // If you use double-click action

    // You might have a helper slot like this, declare if used
    void handleTableViewClicked(const QModelIndex &index);
    void on_viewStatisticsButton_clicked();
    void on_payInvoiceButton_clicked();

    void checkAndSendReminders();

private:
    Ui::InvoiceManagementWidget *ui;
    QSqlQueryModel *model; // Model to display invoice list
    QString m_currentFilterClause; // Reorder if needed for the -Wreorder warning
    QTimer *reminderTimer;

    QString m_currentOrderByClause;
    int m_sortColumn;
    Qt::SortOrder m_sortOrder;
    void setupConnections();
    void populateSortComboBox();
    void populateFilterComboBoxes(); // Fills filter dropdowns

    void loadInvoices(const QString &filterClause);
    void refreshInvoiceList();
    int getSelectedInvoiceId();
    void updateSortComboBoxSelection();
    bool generateInvoiceListPdf(const QString &filePath, QAbstractItemModel *invoiceModel);
    void updateSummaryLabels(const QString& currentFilterClause);

    bool sendReminderEmail(const QString &recipientEmail, const QString &clientName,
                           const QString &invoiceNumber, const QDate &dueDate, double amount,
                           const QString &reminderType);
    // ... existing private methods ...
    void setupReminderTimer();
};


#endif // INVOICEMANAGEMENTWIDGET_H
