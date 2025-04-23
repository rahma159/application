#include "invoicelineitem.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// --- Constructors ---
InvoiceLineItem::InvoiceLineItem()
    : line_item_id(-1), invoice_id(-1), quantity(0.0), unit_price(0.0), amount(0.0) {}

InvoiceLineItem::InvoiceLineItem(int line_item_id, int invoice_id,
                                 const QString &description, double quantity,
                                 double unit_price, double amount)
    : line_item_id(line_item_id), invoice_id(invoice_id),
    description(description), quantity(quantity), unit_price(unit_price),
    amount(amount) {}

// --- Getters ---
int InvoiceLineItem::getLineItemId() const { return line_item_id; }
int InvoiceLineItem::getInvoiceId() const { return invoice_id; }
QString InvoiceLineItem::getDescription() const { return description; }
double InvoiceLineItem::getQuantity() const { return quantity; }
double InvoiceLineItem::getUnitPrice() const { return unit_price; }
double InvoiceLineItem::getAmount() const { return amount; }

// --- Setters ---
void InvoiceLineItem::setLineItemId(int id) { line_item_id = id; }
void InvoiceLineItem::setInvoiceId(int id) { invoice_id = id; }
void InvoiceLineItem::setDescription(const QString& desc) { description = desc; }
void InvoiceLineItem::setQuantity(double qty) { quantity = qty; }
void InvoiceLineItem::setUnitPrice(double price) { unit_price = price; }
void InvoiceLineItem::setAmount(double amt) { amount = amt; }

// --- Standalone Database Operations (Use with Caution) ---

// Add single line item (Assumes INVOICE_ID is set)
bool InvoiceLineItem::ajouter(QSqlDatabase& db) {
    qWarning() << "Standalone InvoiceLineItem::ajouter() called. Use Invoices::save() for transactional safety.";
    if (this->invoice_id <= 0) {
        qWarning() << "InvoiceLineItem::ajouter() - Cannot add item without a valid INVOICE_ID.";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "InvoiceLineItem::ajouter() - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO INVOICE_LINE_ITEMS (INVOICE_ID, DESCRIPTION, QUANTITY, UNIT_PRICE, AMOUNT) "
                  "VALUES (:invoice_id, :description, :quantity, :unit_price, :amount)");
    query.bindValue(":invoice_id", this->invoice_id);
    query.bindValue(":description", this->description);
    query.bindValue(":quantity", this->quantity);
    query.bindValue(":unit_price", this->unit_price);
    query.bindValue(":amount", (this->amount != 0.0) ? this->amount : this->quantity * this->unit_price); // Recalculate if needed

    if (!query.exec()) {
        qDebug() << "Error adding InvoiceLineItem:" << query.lastError().text();
        return false;
    }
    // Optionally retrieve and set line_item_id if needed using query.lastInsertId() (driver dependent)
    return true;
}

// Update single line item (Assumes LINE_ITEM_ID is set)
bool InvoiceLineItem::modifier(QSqlDatabase& db) {
    qWarning() << "Standalone InvoiceLineItem::modifier() called. Use Invoices::update() for transactional safety.";
    if (this->line_item_id <= 0) {
        qWarning() << "InvoiceLineItem::modifier() - Cannot modify item without a valid LINE_ITEM_ID.";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "InvoiceLineItem::modifier() - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE INVOICE_LINE_ITEMS SET INVOICE_ID = :invoice_id, DESCRIPTION = :description, "
                  "QUANTITY = :quantity, UNIT_PRICE = :unit_price, AMOUNT = :amount "
                  "WHERE LINE_ITEM_ID = :line_item_id");
    query.bindValue(":invoice_id", this->invoice_id);
    query.bindValue(":description", this->description);
    query.bindValue(":quantity", this->quantity);
    query.bindValue(":unit_price", this->unit_price);
    query.bindValue(":amount", (this->amount != 0.0) ? this->amount : this->quantity * this->unit_price);
    query.bindValue(":line_item_id", this->line_item_id);

    if (!query.exec()) {
        qDebug() << "Error updating InvoiceLineItem:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0; // Return true only if a row was actually updated
}

// Delete single line item by ID
bool InvoiceLineItem::supprimer(int line_item_id_to_delete, QSqlDatabase& db) {
    qWarning() << "Standalone InvoiceLineItem::supprimer() called. Use Invoices::remove() or Invoices::update() for transactional safety.";
    if (line_item_id_to_delete <= 0) {
        qWarning() << "InvoiceLineItem::supprimer() - Invalid LINE_ITEM_ID provided.";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "InvoiceLineItem::supprimer() - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM INVOICE_LINE_ITEMS WHERE LINE_ITEM_ID = :line_item_id");
    query.bindValue(":line_item_id", line_item_id_to_delete);

    if (!query.exec()) {
        qDebug() << "Error deleting InvoiceLineItem:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0; // Return true only if a row was actually deleted
}
