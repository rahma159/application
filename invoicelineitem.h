#ifndef INVOICELINEITEM_H
#define INVOICELINEITEM_H

#include <QString>
#include <QSqlDatabase> // Needed for standalone methods if using default connection

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

#endif // INVOICELINEITEM_H
