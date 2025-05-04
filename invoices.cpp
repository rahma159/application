#include "invoices.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <stdexcept> // Keep if you plan exception handling, otherwise optional for this code
#include <QMetaType>
#include <cmath>   // For isnan, isinf
#include <limits>  // For infinity
#include <QMapIterator>
#include <QString>  // Ensure included for isnan/isinf
#include <QSqlDatabase>
#include <QDate>
#include <QDateTime>
#include "invoicelineitem.h"
#include <QTimeZone>
// --- Constructors ---
Invoices::Invoices()
    : invoice_id(-1), client_id(-1), issue_date(QDateTime::currentDateTime()),
    due_date(QDateTime::currentDateTime().addDays(30)),
    subtotal(0.0), tax_amount(0.0), total_amount(0.0),
    reminder_sent_date(QDateTime()) // Initialize to null QDateTime
{}

Invoices::Invoices(int invoice_id, const QString &invoice_number, int client_id,
                   const QString &client_name,const QString &client_email,
                   const QDateTime  &issue_date,
                   const QDateTime& dateParameter, const QString &payment_terms,
                   double subtotal, double tax_amount, double total_amount,
                   const QString &status, const QDate &payment_date, const QString& notes )
    : invoice_id(invoice_id), invoice_number(invoice_number),
    client_id(client_id), client_name(client_name),client_email(client_email),
    issue_date(issue_date),
    due_date(dateParameter), payment_terms(payment_terms), subtotal(subtotal),
    tax_amount(tax_amount), total_amount(total_amount), status(status),
    payment_date(payment_date), notes(notes),
    reminder_sent_date(QDateTime()) // Initialize to null QDateTime
{}

// --- Getters ---
int Invoices::getInvoiceId() const { return invoice_id; }
QString Invoices::getInvoiceNumber() const { return invoice_number; }
int Invoices::getClientId() const { return client_id; }
QString Invoices::getClientName() const { return client_name; }
QString Invoices::getClientEmail() const { return client_email; }
QDateTime Invoices::getIssueDate() const { return this->issue_date;}
QDateTime Invoices::getDueDate() const { return due_date; }
QString Invoices::getPaymentTerms() const { return payment_terms; }
double Invoices::getSubtotal() const { return subtotal; }
double Invoices::getTaxAmount() const { return tax_amount; }
double Invoices::getTotalAmount() const { return total_amount; }
QString Invoices::getStatus() const { return status; }
QDate Invoices::getPaymentDate() const { return payment_date; }
QString Invoices::getNotes() const { return notes; }
const QList<InvoiceLineItem>& Invoices::getLineItems() const { return lineItems; }
QSqlError Invoices::lastDbError() const { return dbError; }
QDateTime Invoices::getReminderSentDate() const { return reminder_sent_date; }
// --- Setters ---
void Invoices::setInvoiceId(int id) { invoice_id = id; }
void Invoices::setInvoiceNumber(const QString& number) { invoice_number = number; }
void Invoices::setClientId(int id) { client_id = id; }
void Invoices::setClientName(const QString& name) { client_name = name; }
void Invoices::setClientEmail(const QString& email) { client_email = email; }
void Invoices::setIssueDate(const QDateTime &dt) { // <--- Adjust parameter
    this->issue_date = dt;
}
void Invoices::setDueDate(const QDateTime& dateTime) { due_date = dateTime; }
void Invoices::setPaymentTerms(const QString& terms) { payment_terms = terms; }
void Invoices::setSubtotal(double sub) { subtotal = sub; }
void Invoices::setTaxAmount(double tax) { tax_amount = tax; }
void Invoices::setTotalAmount(double total) { total_amount = total; }
void Invoices::setStatus(const QString& st) { status = st; }
void Invoices::setPaymentDate(const QDate& date) { payment_date = date; }
void Invoices::setNotes(const QString& nts) { notes = nts; } // Use const&
void Invoices::setLineItems(const QList<InvoiceLineItem>& items) { lineItems = items; }
void Invoices::setReminderSentDate(const QDateTime& dt) { reminder_sent_date = dt; }



// --- Private Helpers ---

// Helper to get the next ID. Assumes db connection is passed and valid.
// Consider making this static if it doesn't rely on instance members.
int Invoices::getNextIdFromSequence(QSqlDatabase& db) {
    QSqlQuery query(db);
    // IMPORTANT: Verify your actual sequence name in Oracle (e.g., INVOICES_SEQ, INVOICE_ID_SEQ)
    if (query.exec("SELECT INVOICES_SEQ.NEXTVAL FROM dual")) {
        if (query.next()) {
            return query.value(0).toInt();
        } else {
            qWarning() << "Invoices::getNextIdFromSequence - Sequence query returned no rows.";
            dbError = query.lastError(); // Store error for later retrieval if needed
        }
    } else {
        qWarning() << "Invoices::getNextIdFromSequence - Error executing sequence query:" << query.lastError().text();
        dbError = query.lastError(); // Store error
    }
    return -1; // Indicate failure
}



// *** REMOVED DUPLICATE DEFINITION THAT WAS HERE ***

void Invoices::bindHeaderValues(QSqlQuery& query)
{
    qDebug() << "--- Binding Header Values (Native Types) ---"; // Updated comment

    // Bind strings
    query.bindValue(":invoice_number", this->invoice_number);
    query.bindValue(":client_name", this->client_name);
    query.bindValue(":payment_terms", this->payment_terms.isNull() ? QVariant(QMetaType(QMetaType::QString)) : QVariant(this->payment_terms));
    query.bindValue(":status", this->status);
   // QVariant notesVariant = this->notes.isNull() ? QVariant(QMetaType(QMetaType::QString)) : QVariant(this->notes);
   // query.bindValue(":notes", notesVariant);

    // Bind Dates directly
    qDebug() << "  BINDING :issue_date VALUE:" << this->issue_date << "isValid:" << this->issue_date.isValid();
    query.bindValue(":issue_date", this->issue_date.isValid() ? QVariant(this->issue_date) : QVariant(QMetaType(QMetaType::QDateTime)));

    qDebug() << "  BINDING :due_date VALUE:" << this->due_date << "isValid:" << this->due_date.isValid();
    query.bindValue(":due_date", this->due_date.isValid() ? QVariant(this->due_date) : QVariant(QMetaType(QMetaType::QDateTime)));

    // Bind payment_date (QDate)
    QVariant paymentDateVariant;
    if (this->payment_date.isValid()) {
        paymentDateVariant = QVariant(this->payment_date);
    } else {
        // Create a null QVariant for the DATE type
        paymentDateVariant = QVariant(QMetaType(QMetaType::QDate));
    }
    qDebug() << "  BINDING :payment_date VALUE:" << paymentDateVariant;
    query.bindValue(":payment_date", paymentDateVariant);


    // --- Check and bind numeric values DIRECTLY ---
    int clientId = this->client_id;
    double subtotal = this->subtotal;
    double taxAmount = this->tax_amount;
    double totalAmount = this->total_amount;

    qDebug() << "  BINDING :client_id VALUE:" << clientId;
    query.bindValue(":client_id", clientId); // Bind int

    qDebug() << "  CHECKING subtotal VALUE:" << subtotal;
    if (std::isnan(subtotal) || std::isinf(subtotal)) {
        qWarning() << "  !!! Subtotal is NaN or Inf! Binding 0.0 instead.";
        subtotal = 0.0;
    }
    query.bindValue(":subtotal", subtotal); // Bind double

    qDebug() << "  CHECKING tax_amount VALUE:" << taxAmount;
    if (std::isnan(taxAmount) || std::isinf(taxAmount)) {
        qWarning() << "  !!! Tax Amount is NaN or Inf! Binding 0.0 instead.";
        taxAmount = 0.0;
    }
    query.bindValue(":tax_amount", taxAmount); // Bind double

    qDebug() << "  CHECKING total_amount VALUE:" << totalAmount;
    if (std::isnan(totalAmount) || std::isinf(totalAmount)) {
        qWarning() << "  !!! Total Amount is NaN or Inf! Binding 0.0 instead.";
        totalAmount = 0.0;
    }
    query.bindValue(":total_amount", totalAmount); // Bind double



    query.bindValue(":reminder_sent_date",
                    this->reminder_sent_date.isValid() ? QVariant(this->reminder_sent_date) :
                        QVariant(QMetaType(QMetaType::QDateTime)));
    qDebug() << "  BINDING :reminder_sent_date VALUE:" << this->reminder_sent_date << "isValid:" << this->reminder_sent_date.isValid();
    qDebug() << "--- Binding Finished (Native Types) ---";
}
// --- Core Data Operations ---

// Save a NEW invoice to the database. Uses the default connection.
// Assumes header file declares: bool save();
bool Invoices::save()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Invoices::save - Database connection is not open.";
        dbError = QSqlError("Connection Error", "Database not open", QSqlError::ConnectionError);
        return false;
    }

    // Prevent saving if already has an ID (should use update)
    if (this->invoice_id > 0) {
        dbError = QSqlError("Save Error", "Object already has an ID; use update() instead.", QSqlError::StatementError);
        qWarning() << "Invoices::save - Attempted save on existing ID:" << this->invoice_id << ". Use update().";
        return false;
    }

    bool success = false;
    dbError = QSqlError(); // Clear previous errors for this operation

    // Transaction Management
    qDebug() << "Attempting to start transaction for save...";
    if (!db.transaction()) {
        dbError = db.lastError();
        qWarning() << "FAILED TO START TRANSACTION:" << dbError.text();
        return false;
    }

    qDebug() << "Transaction started. Preparing save operation...";

    // --- FIXED SAVE LOGIC ---
    int new_invoice_id = -1; // Initialize to invalid ID

    try { // Optional: Use try/catch for non-Qt exceptions if needed

        // 1. Get New Invoice ID from Sequence (pass the connection)
        qDebug() << "Attempting to get next sequence ID...";
        new_invoice_id = getNextIdFromSequence(db); // Call the helper function

        if (new_invoice_id <= 0) {
            qWarning() << "Failed to retrieve a valid new Invoice ID from sequence. Aborting save.";
            // dbError should already be set by getNextIdFromSequence
            db.rollback(); // Rollback transaction
            return false;
        }
        qDebug() << "Retrieved new Invoice ID:" << new_invoice_id;


        this->issue_date = Invoices::getCurrentTunisDateTime(); // <<< USE HELPER
        qDebug() << "  save(): Set issue_date to current Tunis timestamp:" << this->issue_date;


        // 2. Prepare INSERT statement for the INVOICES table
        QSqlQuery insertQuery(db);
        // IMPORTANT: Column names MUST match your INVOICES table EXACTLY
        // Using placeholders (e.g., :invoice_id)
        insertQuery.prepare(
            "INSERT INTO INVOICES ("
            "  INVOICE_ID, INVOICE_NUMBER, CLIENT_ID, CLIENT_NAME, ISSUE_DATE, DUE_DATE, "
            "  PAYMENT_TERMS, SUBTOTAL, TAX_AMOUNT, TOTAL_AMOUNT, STATUS, "
            "  PAYMENT_DATE, NOTES" // Removed REMINDER_SENT_DATE from the base query
            // Add REMINDER_SENT_DATE only if it's valid
            ") VALUES ("
            "  :invoice_id, :invoice_number, :client_id, :client_name, :issue_date, :due_date, "
            "  :payment_terms, :subtotal, :tax_amount, :total_amount, :status, "
            "  :payment_date, :notes" // Removed :reminder_sent_date from base query
            ")"
            );
        if (this->reminder_sent_date.isValid()) {
            QString sql = insertQuery.lastQuery();
            sql.insert(sql.indexOf(") VALUES ("), ", REMINDER_SENT_DATE");
            sql.insert(sql.lastIndexOf(")"), ", :reminder_sent_date");
            insertQuery.prepare(sql);
        }

        // 3. Bind the new ID separately (it's not part of the bindHeaderValues strategy)
        qDebug() << "Binding :invoice_id :" << new_invoice_id;
        insertQuery.bindValue(":invoice_id", new_invoice_id); // Bind the retrieved ID

        // 4. Bind the rest of the values using the helper function (Strategy 2)
        bindHeaderValues(insertQuery); // Pass the query object to the binding function

        // 5. Execute the INSERT query
        qDebug() << "Executing INSERT query...";
        success = insertQuery.exec();

        if (success) {
            qDebug() << "INSERT query executed successfully for header ID:" << new_invoice_id;
            // Assign the new ID to the object *only* on successful header insertion
            this->invoice_id = new_invoice_id;

            // === START: REPLACE PLACEHOLDER WITH THIS ===
            qDebug() << "Attempting to insert" << lineItems.count() << "line items...";
            for (const InvoiceLineItem& item : lineItems) { // Assuming lineItems is the QList<InvoiceLineItem> member
                QSqlQuery lineQuery(db); // Use the same transaction/database connection

                // Prepare INSERT for your line items table - ADJUST TABLE/COLUMN NAMES
                // Make sure INVOICE_LINE_ITEMS and its columns exist in your DB!
                lineQuery.prepare("INSERT INTO INVOICE_LINE_ITEMS "
                                  "(LINE_ITEM_ID,INVOICE_ID, DESCRIPTION, QUANTITY, UNIT_PRICE, AMOUNT) " // Add/remove columns as needed
                                  "VALUES (LINE_ITEM_ID_SEQ.NEXTVAL,:invoice_id, :description, :quantity, :unit_price, :amount)");

                // Bind the invoice_id (Foreign Key) from the newly saved header
                lineQuery.bindValue(":invoice_id", this->invoice_id);

                // Bind values from the current 'item' object
                // Adjust according to your InvoiceLineItem class members/getters
                // Ensure your InvoiceLineItem class HAS these getter methods!
                lineQuery.bindValue(":description", item.getDescription());
                lineQuery.bindValue(":quantity", item.getQuantity());
                lineQuery.bindValue(":unit_price", item.getUnitPrice());
                lineQuery.bindValue(":amount", item.getAmount());
                // Add binding for other line item columns if you have them (e.g., product_id)

                if (!lineQuery.exec()) { // <<< THE ERROR COULD BE HAPPENING HERE
                    qWarning() << "Failed to insert line item:" << lineQuery.lastError().text();
                    dbError = lineQuery.lastError();
                    success = false;
                    break;
                } else {
                    qDebug() << "Successfully inserted line item:" << item.getDescription();
                }
            }
            // === END: REPLACE PLACEHOLDER WITH THIS ===

            // ---^^^--- END OF LINE ITEM LOGIC BLOCK ---^^^---

        } else {
            // This else block handles the header insert failure
            qWarning() << "INSERT query failed for header:" << insertQuery.lastError().text();
            dbError = insertQuery.lastError(); // Store the error
            // 'success' is already false here
        }

    } catch (const std::exception& e) { // Example catch block
        qWarning() << "An unexpected C++ exception occurred during save:" << e.what();
        dbError = QSqlError("Exception", QString("std::exception: %1").arg(e.what()), QSqlError::TransactionError);
        success = false;
    } catch (...) { // Catch any other unknown exceptions
        qWarning() << "An unknown exception occurred during save.";
        dbError = QSqlError("Exception", "Unknown exception occurred", QSqlError::TransactionError);
        success = false;
    }

    // --- END OF FIXED SAVE LOGIC ---


    // 6. Commit or Rollback Transaction
    if (success) {
        qDebug() << "Attempting to commit transaction...";
        if (db.commit()) {
            qDebug() << "Transaction committed successfully.";
        } else {
            qWarning() << "FAILED TO COMMIT TRANSACTION:" << db.lastError().text();
            dbError = db.lastError(); // Store commit error
            success = false; // Mark operation as failed if commit fails
        }
    } else {
        qWarning() << "Operation failed, attempting to rollback transaction...";
        if (db.rollback()) {
            qDebug() << "Transaction rolled back successfully.";
        } else {
            qWarning() << "FAILED TO ROLLBACK TRANSACTION:" << db.lastError().text();
            // Usually, you'd prioritize the original error over the rollback error
            // but log the rollback error too.
        }
    }

    return success;
}


// Update an existing invoice. Assumes header file declares: bool update();

// Update an existing invoice - USING QString::number for doubles
bool Invoices::update()
{
    // Get default connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Invoices::update - Database connection is not open.";
        dbError = QSqlError("Connection Error", "Database not open", QSqlError::ConnectionError);
        return false;
    }

    if (this->invoice_id <= 0) {
        qWarning() << "Invoices::update() failed: Invoice ID is not set or invalid.";
        dbError = QSqlError("Update Error", "Cannot update without a valid ID.", QSqlError::StatementError);
        return false;
    }
    qDebug() << "Attempting update() for Invoice ID:" << this->invoice_id << " using QString::number for doubles";

    QSqlQuery query(db); // Use the connection

    // Build the base query
    QString queryStr =
        "UPDATE INVOICES SET "
        " INVOICE_NUMBER = :invoice_number, "
        " CLIENT_ID = :client_id, "
        " CLIENT_NAME = :client_name, "
        " ISSUE_DATE = :issue_date, "
        " DUE_DATE = :due_date, "
        " PAYMENT_TERMS = :payment_terms, "
        " SUBTOTAL = :subtotal, "
        " TAX_AMOUNT = :tax_amount, "
        " TOTAL_AMOUNT = :total_amount, "
        " STATUS = :status, "
        " PAYMENT_DATE = :payment_date, "
        " NOTES = :notes";

    // Conditionally add REMINDER_SENT_DATE if it's valid
    if (this->reminder_sent_date.isValid()) {
        queryStr += ", REMINDER_SENT_DATE = :reminder_sent_date";
    }

    // Add the WHERE clause
    queryStr += " WHERE INVOICE_ID = :invoice_id";

    query.prepare(queryStr);

    // --- Bind values ---

    // Bind strings (using QMetaType style for NULLs like save)
    query.bindValue(":invoice_number", this->invoice_number);
    query.bindValue(":client_name", this->client_name);
    query.bindValue(":payment_terms", this->payment_terms.isNull() ? QVariant(QMetaType(QMetaType::QString)) : QVariant(this->payment_terms));
    query.bindValue(":status", this->status);
    query.bindValue(":notes", this->notes.isNull() ? QVariant() : this->notes);

    // Bind Dates (using QMetaType style for NULLs like save)
    query.bindValue(":issue_date", this->issue_date.isValid() ? QVariant(this->issue_date) : QVariant(QMetaType(QMetaType::QDateTime)));
    query.bindValue(":due_date", this->due_date.isValid() ? QVariant(this->due_date) : QVariant(QMetaType(QMetaType::QDateTime)));
    query.bindValue(":payment_date", this->payment_date.isValid() ? QVariant(this->payment_date) : QVariant(QMetaType(QMetaType::QDate)));

    // Bind reminder_sent_date if valid
    if (this->reminder_sent_date.isValid()) {
        query.bindValue(":reminder_sent_date", this->reminder_sent_date);
    }

    // Bind int
    query.bindValue(":client_id", this->client_id);

    // --- BIND DOUBLES AS STRINGS (Clean Implementation) ---
    const int precision = 4; // Adjust precision (e.g., 2 for currency) as needed

    // Bind Subtotal
    if (std::isnan(this->subtotal) || std::isinf(this->subtotal)) {
        qWarning() << "Invoices::update - Subtotal is NaN or Inf! Binding NULL instead.";
        query.bindValue(":subtotal", QVariant(QMetaType(QMetaType::Double))); // Explicit NULL for double type
    } else {
        query.bindValue(":subtotal", QString::number(this->subtotal, 'f', precision));
    }

    // Bind Tax Amount
    if (std::isnan(this->tax_amount) || std::isinf(this->tax_amount)) {
        qWarning() << "Invoices::update - Tax Amount is NaN or Inf! Binding NULL instead.";
        query.bindValue(":tax_amount", QVariant(QMetaType(QMetaType::Double))); // Explicit NULL for double type
    } else {
        query.bindValue(":tax_amount", QString::number(this->tax_amount, 'f', precision));
    }

    // Bind Total Amount
    if (std::isnan(this->total_amount) || std::isinf(this->total_amount)) {
        qWarning() << "Invoices::update - Total Amount is NaN or Inf! Binding NULL instead.";
        query.bindValue(":total_amount", QVariant(QMetaType(QMetaType::Double))); // Explicit NULL for double type
    } else {
        query.bindValue(":total_amount", QString::number(this->total_amount, 'f', precision));
    }
    // --- END BIND DOUBLES AS STRINGS ---

    // Bind WHERE clause ID
    query.bindValue(":invoice_id", this->invoice_id);

    // --- Execution and Error Handling ---
    bool success = query.exec();
    if (!success) {
        qWarning() << "Update query failed (using clean QString::number binding):" << query.lastError().text();
        this->dbError = query.lastError();
    } else {
        qDebug() << "Update query successful for invoice header ID:" << this->invoice_id;
        if (query.numRowsAffected() == 0) {
            qWarning() << "Update(): Query executed successfully, but no rows were affected (ID:" << this->invoice_id << " might not exist in DB).";
        }
        qDebug() << "Placeholder: Need to implement Line Item synchronization logic for update.";
    }
    return success;
}

// Static function to remove an invoice and its lines by ID.
// Assumes header file declares: static bool remove(int id_to_delete);
// Made static as it doesn't depend on a specific instance.
bool Invoices::remove(int id_to_delete)
{
    // Get default connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Invoices::remove - Database connection is not open.";
        // Cannot easily set dbError in a static method without a shared error mechanism
        return false;
    }

    if (id_to_delete <= 0) {
        qWarning() << "Static remove() failed: Invalid ID provided.";
        return false;
    }
    qDebug() << "Attempting static remove() for Invoice ID:" << id_to_delete;

    // --- Use Transaction ---
    bool tx_ok = db.transaction();
    if (!tx_ok) {
        qWarning() << "Static remove() failed to start transaction:" << db.lastError().text();
        return false;
    }

    bool lineSuccess = false;
    bool headerSuccess = false;

    // Must delete line items first due to Foreign Key Constraint
    QSqlQuery lineQuery(db);
    lineQuery.prepare("DELETE FROM INVOICE_LINE_ITEMS WHERE INVOICE_ID = :id");
    lineQuery.bindValue(":id", id_to_delete);
    lineSuccess = lineQuery.exec();

    if (!lineSuccess) {
        qWarning() << "Static remove() failed during line item delete:" << lineQuery.lastError().text();
        // Don't try to delete header if lines failed, FK would likely block it
        db.rollback(); // Rollback transaction
        return false;
    } else {
        qDebug() << "Static remove(): Line items deleted (or none existed) for ID:" << id_to_delete;

        // Now delete the header only if lines were successfully deleted
        QSqlQuery headerQuery(db);
        headerQuery.prepare("DELETE FROM INVOICES WHERE INVOICE_ID = :id");
        headerQuery.bindValue(":id", id_to_delete);
        headerSuccess = headerQuery.exec();

        if (!headerSuccess) {
            qWarning() << "Static remove() failed during header delete:" << headerQuery.lastError().text();
            db.rollback(); // Rollback transaction
            return false;
        } else {
            qDebug() << "Static remove(): Header deleted for ID:" << id_to_delete;
            if (headerQuery.numRowsAffected() == 0) {
                qWarning() << "Static remove(): Header delete query succeeded, but no rows affected (ID:" << id_to_delete << " might not have existed).";
                // Still consider this a success in terms of the desired state (it's gone)
            }
        }
    }

    // If we reach here, both line delete and header delete were successful
    if (db.commit()) {
        qDebug() << "Static remove(): Transaction committed.";
        return true; // Overall success
    } else {
        qWarning() << "Static remove(): FAILED TO COMMIT transaction:" << db.lastError().text();
        // Rollback might happen automatically, but explicit rollback is safer if commit fails
        db.rollback();
        return false; // Failed at commit stage
    }
}


Invoices Invoices::loadById(int id, QSqlDatabase& db, bool* ok) {
    if (ok) *ok = false;
    Invoices loadedInvoice;

    if (!db.isValid() || !db.isOpen()) {
        qWarning() << "Invoices::loadById - Database connection is invalid or not open.";
        return loadedInvoice;
    }
    if (id <= 0) {
        qWarning() << "Invoices::loadById - Invalid ID provided:" << id;
        return loadedInvoice;
    }

    // Build the query string
    QString queryStr =
        "SELECT INVOICE_NUMBER, CLIENT_ID, CLIENT_NAME, ISSUE_DATE, DUE_DATE, "
        "PAYMENT_TERMS, SUBTOTAL, TAX_AMOUNT, TOTAL_AMOUNT, STATUS, "
        "PAYMENT_DATE, NOTES";

    // Only add REMINDER_SENT_DATE if the column exists
    bool hasReminderColumn = columnExists(db, "INVOICES", "REMINDER_SENT_DATE");
    if (hasReminderColumn) {
        queryStr += ", REMINDER_SENT_DATE";
    }

    queryStr += " FROM INVOICES WHERE INVOICE_ID = :id";

    QSqlQuery headerQuery(db);
    headerQuery.prepare(queryStr);
    headerQuery.bindValue(":id", id);

    if (!headerQuery.exec()) {
        qWarning() << "Invoices::loadById - Failed to execute header query:" << headerQuery.lastError().text();
        loadedInvoice.dbError = headerQuery.lastError();
        return loadedInvoice;
    }

    if (headerQuery.next()) {
        loadedInvoice.invoice_id = id;
        loadedInvoice.invoice_number = headerQuery.value("INVOICE_NUMBER").toString();
        loadedInvoice.client_id = headerQuery.value("CLIENT_ID").toInt();
        loadedInvoice.client_name = headerQuery.value("CLIENT_NAME").toString();
        loadedInvoice.issue_date = headerQuery.value("ISSUE_DATE").toDateTime();
        qDebug() << "Loaded ISSUE_DATE for ID" << id << ":" << loadedInvoice.issue_date;

        loadedInvoice.due_date = headerQuery.value("DUE_DATE").toDateTime();
        loadedInvoice.payment_terms = headerQuery.value("PAYMENT_TERMS").toString();
        loadedInvoice.subtotal = headerQuery.value("SUBTOTAL").toDouble();
        loadedInvoice.tax_amount = headerQuery.value("TAX_AMOUNT").toDouble();
        loadedInvoice.total_amount = headerQuery.value("TOTAL_AMOUNT").toDouble();
        loadedInvoice.status = headerQuery.value("STATUS").toString();
        loadedInvoice.payment_date = headerQuery.value("PAYMENT_DATE").toDate();
        loadedInvoice.notes = headerQuery.value("NOTES").toString();

        // Only try to read REMINDER_SENT_DATE if it was in the query
        if (hasReminderColumn) {
            loadedInvoice.reminder_sent_date = headerQuery.value("REMINDER_SENT_DATE").toDateTime();
        }

        qDebug() << "Invoice header loaded successfully for ID:" << id;

        // Query Line Items
        QSqlQuery lineQuery(db);
        lineQuery.prepare(
            "SELECT LINE_ITEM_ID, DESCRIPTION, QUANTITY, UNIT_PRICE, AMOUNT "
            "FROM INVOICE_LINE_ITEMS WHERE INVOICE_ID = :id "
            "ORDER BY LINE_ITEM_ID"
            );
        lineQuery.bindValue(":id", id);

        if (!lineQuery.exec()) {
            qWarning() << "Invoices::loadById - Failed to execute line item query:" << lineQuery.lastError().text();
            loadedInvoice.dbError = lineQuery.lastError();
            if (ok) *ok = false;
            return loadedInvoice;
        }

        // Populate Line Items
        QList<InvoiceLineItem> items;
        while (lineQuery.next()) {
            InvoiceLineItem item;
            // Populate your line items here as before
            // item.setLineItemId(lineQuery.value("LINE_ITEM_ID").toInt());
            // item.setDescription(lineQuery.value("DESCRIPTION").toString());
            // etc...
            items.append(item);
        }
        loadedInvoice.setLineItems(items);
        qDebug() << "Loaded" << items.count() << "line items for invoice ID:" << id;

        if (ok) *ok = true;
    } else {
        qWarning() << "Invoices::loadById - No invoice found with ID:" << id;
    }

    return loadedInvoice;
}
bool Invoices::markAsPaidStatic(int invoiceId) {
    if (invoiceId <= 0) {
        qWarning() << "Invoices::markAsPaidStatic - Invalid ID provided:" << invoiceId;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database(); // Get default connection
    if (!db.isOpen()) {
        qWarning() << "Invoices::markAsPaidStatic - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);

    // *** CHANGE: Modify the UPDATE statement ***
    // *** VERIFY THESE COLUMN NAMES (CASE!) match your Oracle table ***
    query.prepare("UPDATE INVOICES SET "
                  " STATUS = :status, "
                  " PAYMENT_DATE = :paymentDate, " // Keep setting payment date
                  " ISSUE_DATE = :issueDate "    // *** ADD: Also set issue date ***
                  "WHERE INVOICE_ID = :invoiceId"); // *** VERIFY INVOICE_ID column name ***

    // --- Bind the values ---
    query.bindValue(":status", "paid");
    // Also use Tunis date for the payment date
    // OLD: query.bindValue(":paymentDate", QDate::currentDate());
    query.bindValue(":paymentDate", Invoices::getCurrentTunisDateTime().date()); // <<< USE HELPER's DATE part
    // Use Tunis date/time for the issue date update
    // OLD: query.bindValue(":issueDate", QDateTime::currentDateTime());
    query.bindValue(":issueDate", Invoices::getCurrentTunisDateTime()); // <<< USE HELPER
    query.bindValue(":invoiceId", invoiceId);

    qDebug() << "Executing markAsPaidStatic (now also updating ISSUE_DATE) for ID:" << invoiceId;
    bool success = query.exec();

    if (!success) {
        qWarning() << "Invoices::markAsPaidStatic - Query failed:" << query.lastError().text();
    } else {
        if (query.numRowsAffected() == 0) {
            qWarning() << "Invoices::markAsPaidStatic - Update query succeeded, but no rows affected (ID:" << invoiceId << " might not exist).";
        } else {
            qDebug() << "Invoices::markAsPaidStatic - Successfully updated status, payment_date, and issue_date for ID:" << invoiceId;
        }
    }
    return success;
}

bool Invoices::markAsSentStatic(int invoiceId) {
    if (invoiceId <= 0) {
        qWarning() << "Invoices::markAsSentStatic - Invalid ID provided:" << invoiceId;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database(); // Get default connection
    if (!db.isOpen()) {
        qWarning() << "Invoices::markAsSentStatic - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);

    // *** CHANGE: Update SQL Statement ***
    // *** VERIFY THESE COLUMN NAMES (CASE SENSITIVE!) match your Oracle table ***
    query.prepare("UPDATE INVOICES SET "
                  " STATUS = :status, "
                  " ISSUE_DATE = :sentDate " // *** CHANGE: Use ISSUE_DATE column ***
                  "WHERE INVOICE_ID = :invoiceId"); // *** VERIFY INVOICE_ID column name ***

    query.bindValue(":status", "sent");
    // Use Tunis date/time when setting issue date on send
    // OLD: query.bindValue(":sentDate", QDateTime::currentDateTime());
    query.bindValue(":sentDate", Invoices::getCurrentTunisDateTime()); // <<< USE HELPER
    query.bindValue(":invoiceId", invoiceId);


    qDebug() << "Executing markAsSentStatic for ID:" << invoiceId;
    bool success = query.exec();

    if (!success) {
        // Simple error logging like the original example
        qWarning() << "Invoices::markAsSentStatic - Query failed:" << query.lastError().text();
    } else {
        if (query.numRowsAffected() == 0) {
            qWarning() << "Invoices::markAsSentStatic - Update query succeeded, but no rows affected (ID:" << invoiceId << " might not exist).";
        } else {
            qDebug() << "Invoices::markAsSentStatic - Successfully updated status for ID:" << invoiceId;
        }
    }
    // Return true if the query executed successfully, false otherwise
    return success;
}
QDateTime Invoices::getCurrentTunisDateTime() {
    static const QTimeZone tunisTimeZone("Africa/Tunis");
    if (!tunisTimeZone.isValid()) {
        qWarning() << "*** Timezone 'Africa/Tunis' is not valid! Falling back to system local time.";
        return QDateTime::currentDateTime();
    }
    return QDateTime::currentDateTime(tunisTimeZone);
}

bool Invoices::loadFullInvoiceDetails(int invoiceId, Invoices &invoiceObject) {
    qDebug().noquote() << QString("--- loadFullInvoiceDetails called for ID: %1 ---").arg(invoiceId);

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qCritical().noquote() << QString("!!! Database not open in loadFullInvoiceDetails for ID: %1").arg(invoiceId);
        return false;
    }
    qDebug() << "  Database connection is open.";

    // --- Query 1: Get Main Invoice and Client Data ---
    QSqlQuery headerQuery(db);
    const QString headerSql = QString(
        "SELECT i.INVOICE_NUMBER, i.ISSUE_DATE, i.DUE_DATE, i.STATUS, "
        "       i.SUBTOTAL, i.TAX_AMOUNT, i.TOTAL_AMOUNT, i.NOTES, "
        "       i.REMINDER_SENT_DATE, " // Added REMINDER_SENT_DATE
        "       i.CLIENT_ID, c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
        "FROM INVOICES i "
        "LEFT JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        "WHERE i.INVOICE_ID = :id");


    qDebug().noquote() << QString("  Preparing header query: %1").arg(headerSql);
    headerQuery.prepare(headerSql);
    headerQuery.bindValue(":id", invoiceId);

    qDebug().noquote() << QString("  Executing header query for ID: %1").arg(invoiceId);
    if (!headerQuery.exec()) {
        qCritical().noquote() << QString("!!! Failed to execute header query for ID: %1. Error: %2")
        .arg(invoiceId).arg(headerQuery.lastError().text());
        qCritical().noquote() << QString("  Executed Header Query was: %1").arg(headerQuery.executedQuery());
        return false;
    }
    qDebug() << "  Header query executed successfully.";

    qDebug() << "  Checking if header query found a row...";
    if (!headerQuery.next()) { // Use !next() directly for clarity
        qWarning().noquote() << QString("!!! Invoice header ID %1 not found in database.").arg(invoiceId);
        qDebug().noquote() << QString("--- loadFullInvoiceDetails returning FALSE (Header not found for ID: %1) ---").arg(invoiceId);
        return false;
    }

    // --- Populate Header (Wrap in try-catch just in case) ---
    try {
        qDebug().noquote() << QString("  Invoice header found for ID: %1. Populating object...").arg(invoiceId);
        invoiceObject.setInvoiceId(invoiceId);
        invoiceObject.setInvoiceNumber(headerQuery.value("INVOICE_NUMBER").toString());
        invoiceObject.setIssueDate(headerQuery.value("ISSUE_DATE").toDateTime());
        invoiceObject.setDueDate(headerQuery.value("DUE_DATE").toDateTime());
        invoiceObject.setStatus(headerQuery.value("STATUS").toString());
        invoiceObject.setSubtotal(headerQuery.value("SUBTOTAL").toDouble());
        invoiceObject.setTaxAmount(headerQuery.value("TAX_AMOUNT").toDouble());
        invoiceObject.setTotalAmount(headerQuery.value("TOTAL_AMOUNT").toDouble());
        invoiceObject.setNotes(headerQuery.value("NOTES").toString());
        invoiceObject.setClientId(headerQuery.value("CLIENT_ID").toInt());
        QString firstName = headerQuery.value("FIRST_NAME").toString();
        QString lastName = headerQuery.value("LAST_NAME").toString();
        invoiceObject.setClientName( (firstName + " " + lastName).trimmed() );
        invoiceObject.setClientEmail(headerQuery.value("EMAIL").toString());
        invoiceObject.setReminderSentDate(headerQuery.value("REMINDER_SENT_DATE").toDateTime());
        qDebug() << "  Finished populating header object.";
    } catch (const std::exception& e) {
        qCritical().noquote() << QString("!!! EXCEPTION during header population for ID: %1 - %2").arg(invoiceId).arg(e.what());
        return false;
    } catch (...) {
        qCritical().noquote() << QString("!!! UNKNOWN EXCEPTION during header population for ID: %1").arg(invoiceId);
        return false;
    }


    // --- Query 2: Get Line Items ---
    QSqlQuery itemQuery(db);
    // Ensure NO ORDER BY if LINE_ITEM_ID doesn't exist
    const QString itemSql = QString(
        "SELECT DESCRIPTION, QUANTITY, UNIT_PRICE, AMOUNT "
        "FROM INVOICE_LINE_ITEMS "
        "WHERE INVOICE_ID = :id"); // Removed ORDER BY for safety

    qDebug().noquote() << QString("  Preparing item query: %1").arg(itemSql);
    itemQuery.prepare(itemSql);
    itemQuery.bindValue(":id", invoiceId);

    qDebug().noquote() << QString("  Executing item query for ID: %1").arg(invoiceId);
    if (!itemQuery.exec()) {
        // This block should not be entered for ID 26 based on tests
        qWarning().noquote() << QString("!!! Failed to execute query for invoice items for ID: %1. Error: %2")
                                    .arg(invoiceId).arg(itemQuery.lastError().text());
        qWarning().noquote() << QString("  Executed Item Query was: %1").arg(itemQuery.executedQuery());
        // Decide: Is missing items an error? If so: return false; Otherwise, continue.
        // For now, assume PDF can be generated without items, just log warning.
    } else {
        qDebug().noquote() << QString("  +++ Item query executed successfully for ID: %1. Processing results... +++").arg(invoiceId);
        qDebug() << "    Item query isActive?" << itemQuery.isActive() << "isValid?" << itemQuery.isValid();

        // --- Safely Clear Line Items ---
        try {
            qDebug() << "    Attempting invoiceObject.clearLineItems(). Current count before clear:" << invoiceObject.getLineItems().count();
            invoiceObject.clearLineItems();
            qDebug() << "    invoiceObject.clearLineItems() completed. Current count after clear:" << invoiceObject.getLineItems().count();
        } catch (const std::exception& e) {
            qCritical().noquote() << QString("!!! EXCEPTION during clearLineItems() for ID: %1 - %2").arg(invoiceId).arg(e.what());
            return false;
        } catch (...) {
            qCritical().noquote() << QString("!!! UNKNOWN EXCEPTION during clearLineItems() for ID: %1").arg(invoiceId);
            return false;
        }

        // --- Process Results ---
        int itemsLoaded = 0;
        qDebug() << "    Starting loop through item query results...";
        while (itemQuery.next()) { // Loop through results
            itemsLoaded++;
            qDebug().noquote() << QString("    Processing item #%1 for Invoice ID: %2").arg(itemsLoaded).arg(invoiceId);

            // Wrap item processing in try-catch
            try {
                InvoiceLineItem tempItem;
                tempItem.setInvoiceId(invoiceId);

                QVariant descVar = itemQuery.value("DESCRIPTION");
                QString desc = descVar.toString();
                tempItem.setDescription(desc);
                qDebug() << "      Description:" << desc << "(Variant type:" << descVar.typeName() << ")";

                bool okQty = false;
                QVariant qtyVar = itemQuery.value("QUANTITY");
                double qty = qtyVar.toDouble(&okQty);
                if (!okQty) { qWarning() << "      !!! Conversion warning for QUANTITY. Variant type:" << qtyVar.typeName() << "Value:" << qtyVar; qty = 0.0; }
                tempItem.setQuantity(qty);
                qDebug() << "      Quantity:" << qty << "(conversion ok:" << okQty << ")";

                bool okPrice = false;
                QVariant priceVar = itemQuery.value("UNIT_PRICE");
                double price = priceVar.toDouble(&okPrice);
                if (!okPrice) { qWarning() << "      !!! Conversion warning for UNIT_PRICE. Variant type:" << priceVar.typeName() << "Value:" << priceVar; price = 0.0; }
                tempItem.setUnitPrice(price);
                qDebug() << "      Unit Price:" << price << "(conversion ok:" << okPrice << ")";

                bool okAmount = false;
                QVariant amountVar = itemQuery.value("AMOUNT");
                double amount = amountVar.toDouble(&okAmount);
                if (!okAmount) { qWarning() << "      !!! Conversion warning for AMOUNT. Variant type:" << amountVar.typeName() << "Value:" << amountVar; amount = 0.0; }
                tempItem.setAmount(amount);
                qDebug() << "      Amount:" << amount << "(conversion ok:" << okAmount << ")";

                // Add item
                qDebug() << "      Attempting invoiceObject.addLineItem()...";
                invoiceObject.addLineItem(tempItem);
                qDebug() << "      invoiceObject.addLineItem() completed for item #" << itemsLoaded;

            } catch (const std::exception& e) {
                qCritical().noquote() << QString("!!! EXCEPTION during item processing loop (item #%1) for ID: %2 - %3")
                .arg(itemsLoaded).arg(invoiceId).arg(e.what());
                return false; // Stop if processing an item fails critically
            } catch (...) {
                qCritical().noquote() << QString("!!! UNKNOWN EXCEPTION during item processing loop (item #%1) for ID: %2")
                .arg(itemsLoaded).arg(invoiceId);
                return false; // Stop if processing an item fails critically
            }
        } // End while loop

        qDebug() << "    Finished loop. Last error on itemQuery:" << itemQuery.lastError().text(); // Check for errors *after* loop
        qDebug().noquote() << QString("    Loaded %1 line items total for invoice ID: %2").arg(itemsLoaded).arg(invoiceId);

    } // End else block (item query succeeded)

    // If we reach here, everything should have worked.
    qDebug().noquote() << QString(">>> About to return TRUE from loadFullInvoiceDetails for ID: %1 <<<").arg(invoiceId);
    return true;
}



bool Invoices::markAsRemindedStatic(int invoiceId) {
    if (invoiceId <= 0) {
        qWarning() << "Invoices::markAsRemindedStatic - Invalid ID provided:" << invoiceId;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Invoices::markAsRemindedStatic - Database connection is not open.";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE INVOICES SET "
                  " REMINDER_SENT_DATE = :reminderDate "
                  "WHERE INVOICE_ID = :invoiceId");

    query.bindValue(":reminderDate", Invoices::getCurrentTunisDateTime());
    query.bindValue(":invoiceId", invoiceId);

    qDebug() << "Executing markAsRemindedStatic for ID:" << invoiceId;
    bool success = query.exec();

    if (!success) {
        qWarning() << "Invoices::markAsRemindedStatic - Query failed:" << query.lastError().text();
    } else {
        if (query.numRowsAffected() == 0) {
            qWarning() << "Invoices::markAsRemindedStatic - Update query succeeded, but no rows affected (ID:" << invoiceId << " might not exist).";
        } else {
            qDebug() << "Invoices::markAsRemindedStatic - Successfully updated reminder date for ID:" << invoiceId;
        }
    }

    return success;
}

bool Invoices::columnExists(QSqlDatabase& db, const QString& tableName, const QString& columnName)
{
    QSqlQuery query(db);
    query.prepare(
        "SELECT COUNT(*) FROM USER_TAB_COLUMNS "
        "WHERE TABLE_NAME = :tableName AND COLUMN_NAME = :columnName");
    query.bindValue(":tableName", tableName.toUpper());
    query.bindValue(":columnName", columnName.toUpper());

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}
