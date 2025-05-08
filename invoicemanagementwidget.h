#ifndef INVOICEMANAGEMENTWIDGET_H
#define INVOICEMANAGEMENTWIDGET_H

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
#include <QSqlDatabase>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>    // Needed for DB access in the .cpp
#include <QVariant>     // Needed for DB access in the .cpp
#include <QDebug>
#include <QObject>
// Forward declare classes to reduce include dependencies

namespace Ui { class InvoiceManagementWidget; }
class CreateEditInvoiceDialog;
class QSqlTableModel;
class QSqlQueryModel;
class QModelIndex;    // Use forward declaration
class QLabel;
class StatisticsDialog;

class EmailService : public QObject
{
    Q_OBJECT
public:
    explicit EmailService(QObject *parent = nullptr);

    enum ReminderType {
        PreDueReminder,
        DueDateReminder,
        OverdueReminder,
        PaymentVerification
    };
    bool isConfigured() const;

    bool sendEmail(const QString &recipient, const QString &subject, const QString &body);
    QString generateReminderContent(ReminderType type, const QString &clientName,
                                    const QString &invoiceNumber, const QDate &dueDate,
                                    double amount, int daysOverdue = 0);

private:
    QString m_smtpServer;
    int m_smtpPort;
    QString m_senderEmail;
    QString m_senderPassword;
};

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
public slots:

    void forceSendTestReminders();
    void manualTestReminder();
private:
    Ui::InvoiceManagementWidget *ui;
    QSqlQueryModel *model; // Model to display invoice list
    QString m_currentFilterClause; // Reorder if needed for the -Wreorder warning
    QTimer *reminderTimer;

    EmailService *m_emailService;
    void checkAndSendReminders();
    void checkPreDueReminders(QSqlDatabase& db, const QDate& today);
    void checkDueDateReminders(QSqlDatabase& db, const QDate& today);
    void checkOverdueReminders(QSqlDatabase& db, const QDate& today);
    void processReminder(QSqlQuery& query, EmailService::ReminderType type,
                         const QDate& today, int daysOverdue = 0);
    void sendPaymentVerification(int invoiceId);


    bool testClientExists();
    void createTestClient();
    int ensureTestInvoiceExists();
    void setTestInvoiceDueDate(QSqlDatabase& db, int invoiceId, const QDate& dueDate);

    // Add these with your other private members
    QAction *m_newInvoiceAction;
    QAction *m_editInvoiceAction;
    QAction *m_deleteInvoiceAction;
    QAction *m_payInvoiceAction;
    QAction *m_sendInvoiceAction;
    QAction *m_markPaidAction;



    void setupActionsMenu();
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

    void createTestClientIfNeeded();
    int createTestInvoice(const QDate& dueDate);
    void logReminderTest(const QString &message);
};


class InvoiceLineItem {
private:
    int line_item_id;
    int invoice_id; // Foreign key to INVOICES table
    QString description;
    double quantity;
    double unit_price;
    double amount; // Typically quantity * unit_price (+ VAT if applicable)

public:
    // --- Constructors ---
    InvoiceLineItem();
    InvoiceLineItem(int line_item_id, int invoice_id,
                    const QString &description, double quantity,
                    double unit_price, double amount);

    // --- Getters ---
    int getLineItemId() const;
    int getInvoiceId() const;
    QString getDescription() const;
    double getQuantity() const;
    double getUnitPrice() const;
    double getAmount() const; // Returns the stored amount

    // --- Setters ---
    void setLineItemId(int id);
    void setInvoiceId(int id); // Set the parent invoice ID
    void setDescription(const QString& description);
    void setQuantity(double quantity);
    void setUnitPrice(double price);
    void setAmount(double amount); // Allows setting pre-calculated amount

    // --- Standalone Database Operations (Use with Caution - Prefer Invoices class methods) ---
    bool ajouter(QSqlDatabase& db); // Pass DB connection explicitly is better
    bool modifier(QSqlDatabase& db);
    static bool supprimer(int line_item_id_to_delete, QSqlDatabase& db);
};



class QSqlQuery;

class Invoices {
private:
    int invoice_id;
    QString invoice_number;
    int client_id;
    QString client_name;
    QString client_email;
    QString client_contact;
    QString client_country;
    QDateTime issue_date; // <--- CHANGE THIS from QDate to QDateTime
    QDateTime due_date;
    QString payment_terms;
    double subtotal;
    double tax_amount;
    double total_amount;
    QString status;
    QDate payment_date;
    QString notes;

    QList<InvoiceLineItem> lineItems;
    QSqlError dbError;

    int getNextIdFromSequence(QSqlDatabase& db);
    void bindHeaderValues(QSqlQuery& query);

public:
    Invoices();
    Invoices(int invoice_id, const QString &invoice_number, int client_id,
             const QString &client_name,const QString &client_email,const QDateTime  &issue_date,
             const QDateTime  &due_date, const QString &payment_terms,
             double subtotal, double tax_amount, double total_amount,
             const QString &status, const QDate &payment_date,
             const QString& notes );
    // Getters
    int getInvoiceId() const;
    QString getInvoiceNumber() const;
    int getClientId() const;
    QString getClientName() const;
    QString getClientEmail() const;
    QDateTime getIssueDate() const;
    QDateTime getDueDate() const;
    QString getPaymentTerms() const;
    double getSubtotal() const;
    double getTaxAmount() const;
    double getTotalAmount() const;
    QString getStatus() const;
    QDate getPaymentDate() const;
    QString getNotes() const;
    const QList<InvoiceLineItem>& getLineItems() const;
    QSqlError lastDbError() const;
    QDateTime getReminderSentDate() const;
    // Setters
    void setInvoiceId(int id);
    void setInvoiceNumber(const QString& number);
    void setClientId(int id);
    void setClientName(const QString& name);
    void setClientEmail(const QString& email);
    void setIssueDate(const QDateTime &dt);
    void setDueDate(const QDateTime& dateTime);
    void setPaymentTerms(const QString& terms);
    void setSubtotal(double subtotal);
    void setTaxAmount(double tax);
    void setTotalAmount(double total);
    void setStatus(const QString& status);
    void setPaymentDate(const QDate& date);
    void setNotes(const QString& notes); // Use const&
    void setLineItems(const QList<InvoiceLineItem>& items);
    void setReminderSentDate(const QDateTime& dt);
    // Core Data Operations
    bool save();
    bool update();
    static bool remove(int id_to_delete);    // Static Loading Method
    static Invoices loadById(int id, QSqlDatabase& db, bool* ok = nullptr);
    static bool markAsPaidStatic(int invoiceId);

    static bool loadFullInvoiceDetails(int invoiceId, Invoices &invoiceObject);
    static bool markAsSentStatic(int invoiceId);
    void addLineItem(const InvoiceLineItem &item) { lineItems.append(item);}
    void clearLineItems() { lineItems.clear(); }
    static QDateTime getCurrentTunisDateTime();
    static bool markAsRemindedStatic(int invoiceId);
    static bool columnExists(QSqlDatabase& db, const QString& tableName, const QString& columnName);

};





#endif
