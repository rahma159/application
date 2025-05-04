#ifndef INVOICES_H
#define INVOICES_H

#include "invoicelineitem.h"
#include <QDate>
#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>    // Needed for DB access in the .cpp
#include <QVariant>     // Needed for DB access in the .cpp
#include <QDebug>


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
    QDateTime reminder_sent_date;

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

#endif // INVOICES_H
