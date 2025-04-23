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

// --- Constructors ---
Invoices::Invoices()
    : invoice_id(-1), client_id(-1), issue_date(QDateTime::currentDateTime()),
    due_date(QDateTime::currentDateTime().addDays(30)),
    subtotal(0.0), tax_amount(0.0), total_amount(0.0)
// payment_date is default constructed (null QDate)
{}

// Constructor needs adjustment for notes parameter type if changed in .h
Invoices::Invoices(int invoice_id, const QString &invoice_number, int client_id,
                   const QString &client_name, const QDateTime  &issue_date,
                   const QDateTime& dateParameter, const QString &payment_terms,
                   double subtotal, double tax_amount, double total_amount,
                   const QString &status, const QDate &payment_date, const QString& notes)
    : invoice_id(invoice_id), invoice_number(invoice_number),
    client_id(client_id), client_name(client_name), issue_date(issue_date),
    due_date(dateParameter), payment_terms(payment_terms), subtotal(subtotal),
    tax_amount(tax_amount), total_amount(total_amount), status(status),
    payment_date(payment_date), // Initialize in correct order as declared in .h
    notes(notes)
{}

// --- Getters ---
int Invoices::getInvoiceId() const { return invoice_id; }
QString Invoices::getInvoiceNumber() const { return invoice_number; }
int Invoices::getClientId() const { return client_id; }
QString Invoices::getClientName() const { return client_name; }
QDateTime Invoices::getIssueDate() const { // <--- Adjust return type
    return this->issue_date;
}
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

// --- Setters ---
void Invoices::setInvoiceId(int id) { invoice_id = id; }
void Invoices::setInvoiceNumber(const QString& number) { invoice_number = number; }
void Invoices::setClientId(int id) { client_id = id; }
void Invoices::setClientName(const QString& name) { client_name = name; }
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



        this->issue_date = QDateTime::currentDateTime();
        qDebug() << "  save(): Set issue_date to current timestamp:" << this->issue_date;
        // 2. Prepare INSERT statement for the INVOICES table
        QSqlQuery insertQuery(db);
        // IMPORTANT: Column names MUST match your INVOICES table EXACTLY
        // Using placeholders (e.g., :invoice_id)
        insertQuery.prepare(
            "INSERT INTO INVOICES ("
            "  INVOICE_ID, INVOICE_NUMBER, CLIENT_ID, CLIENT_NAME, ISSUE_DATE, DUE_DATE, "
            "  PAYMENT_TERMS, SUBTOTAL, TAX_AMOUNT, TOTAL_AMOUNT, STATUS, "
            "  PAYMENT_DATE , NOTES" // <<<< NOTES removed
            //") VALUES ("
            ") VALUES (" // Corrected parenthesis placement
            "  :invoice_id, :invoice_number, :client_id, :client_name, :issue_date, :due_date, "
            "  :payment_terms, :subtotal, :tax_amount, :total_amount, :status, "
            "  :payment_date,:notes "
            // <<<< :notes removed
            ")"
            );
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
    query.prepare(
        "UPDATE INVOICES SET "
        " INVOICE_NUMBER = :invoice_number, "
        " CLIENT_ID = :client_id, "
        " CLIENT_NAME = :client_name, "
        " ISSUE_DATE = :issue_date, "
        " DUE_DATE = :due_date, "
        " PAYMENT_TERMS = :payment_terms, "
        " SUBTOTAL = :subtotal, "           // Included
        " TAX_AMOUNT = :tax_amount, "       // Included
        " TOTAL_AMOUNT = :total_amount, "   // Included
        " STATUS = :status, "
        " PAYMENT_DATE = :payment_date, "
        " NOTES = :notes "        // NOTES is NOT included
        "WHERE INVOICE_ID = :invoice_id"
        );

    // --- Bind values ---

    // Bind strings (using QMetaType style for NULLs like save)
    query.bindValue(":invoice_number", this->invoice_number);
    query.bindValue(":client_name", this->client_name);
    query.bindValue(":payment_terms", this->payment_terms.isNull() ? QVariant(QMetaType(QMetaType::QString)) : QVariant(this->payment_terms));
    query.bindValue(":status", this->status);
    // NOTES binding is NOT included
    query.bindValue(":notes", this->notes.isNull() ? QVariant() : this->notes);
    // Bind Dates (using QMetaType style for NULLs like save)
    query.bindValue(":issue_date", this->issue_date.isValid() ? QVariant(this->issue_date) : QVariant(QMetaType(QMetaType::QDateTime)));
    query.bindValue(":due_date", this->due_date.isValid() ? QVariant(this->due_date) : QVariant(QMetaType(QMetaType::QDateTime)));
    query.bindValue(":payment_date", this->payment_date.isValid() ? QVariant(this->payment_date) : QVariant(QMetaType(QMetaType::QDate)));

    // Bind int
    query.bindValue(":client_id", this->client_id);

    // --- BIND DOUBLES AS STRINGS (Clean Implementation) ---
    const int precision = 4; // Adjust precision (e.g., 2 for currency) as needed

    // Bind Subtotal
    if (std::isnan(this->subtotal) || std::isinf(this->subtotal)) {
        qWarning() << "Invoices::update - Subtotal is NaN or Inf! Binding NULL instead.";
        // Bind actual NULL which Oracle typically handles correctly for NUMBER columns
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
        // *** CRITICAL: Check this error if it still fails! ***
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


// Static function to load an invoice by ID.
// Provide the database connection. ok is an optional output parameter.
// Assumes header declares: static Invoices loadById(int id, QSqlDatabase& db, bool* ok = nullptr);
Invoices Invoices::loadById(int id, QSqlDatabase& db, bool* ok) {
    if (ok) {
        *ok = false; // Assume failure initially
    }
    Invoices loadedInvoice; // Create an empty invoice to return on failure

    if (!db.isValid() || !db.isOpen()) {
        qWarning() << "Invoices::loadById - Database connection is invalid or not open.";
        return loadedInvoice;
    }
    if (id <= 0) {
        qWarning() << "Invoices::loadById - Invalid ID provided:" << id;
        return loadedInvoice;
    }

    qDebug() << "Attempting to load invoice by ID:" << id;

    // 1. Query Header Information
    QSqlQuery headerQuery(db);
    headerQuery.prepare(
        "SELECT INVOICE_NUMBER, CLIENT_ID, CLIENT_NAME, ISSUE_DATE, DUE_DATE, "
        "PAYMENT_TERMS, SUBTOTAL, TAX_AMOUNT, TOTAL_AMOUNT, STATUS, "
        "PAYMENT_DATE, NOTES "
        "FROM INVOICES WHERE INVOICE_ID = :id"
        );
    headerQuery.bindValue(":id", id);

    if (!headerQuery.exec()) {
        qWarning() << "Invoices::loadById - Failed to execute header query:" << headerQuery.lastError().text();
        loadedInvoice.dbError = headerQuery.lastError(); // Store error in the returned (empty) object
        return loadedInvoice;
    }

    // 2. Populate Header Information
    if (headerQuery.next()) {
        loadedInvoice.invoice_id = id; // Set the ID since we found it
        loadedInvoice.invoice_number = headerQuery.value("INVOICE_NUMBER").toString();
        loadedInvoice.client_id = headerQuery.value("CLIENT_ID").toInt();
        loadedInvoice.client_name = headerQuery.value("CLIENT_NAME").toString();
        loadedInvoice.issue_date = headerQuery.value("ISSUE_DATE").toDateTime();
        loadedInvoice.due_date = headerQuery.value("DUE_DATE").toDateTime();
        loadedInvoice.payment_terms = headerQuery.value("PAYMENT_TERMS").toString();
        loadedInvoice.subtotal = headerQuery.value("SUBTOTAL").toDouble();
        loadedInvoice.tax_amount = headerQuery.value("TAX_AMOUNT").toDouble();
        loadedInvoice.total_amount = headerQuery.value("TOTAL_AMOUNT").toDouble();
        loadedInvoice.status = headerQuery.value("STATUS").toString();
        loadedInvoice.payment_date = headerQuery.value("PAYMENT_DATE").toDate();
        loadedInvoice.notes = headerQuery.value("NOTES").toString(); // Assumes NOTES is not CLOB needing special handling on load

        qDebug() << "Invoice header loaded successfully for ID:" << id;

        // 3. Query Line Items
        QSqlQuery lineQuery(db);
        // IMPORTANT: Adjust table/column names as needed for your line items table
        lineQuery.prepare(
            "SELECT LINE_ITEM_ID, DESCRIPTION, QUANTITY, UNIT_PRICE, AMOUNT " // Adjust columns
            "FROM INVOICE_LINE_ITEMS WHERE INVOICE_ID = :id "
            "ORDER BY LINE_ITEM_ID" // Optional: Ensure consistent order
            );
        lineQuery.bindValue(":id", id);

        if (!lineQuery.exec()) {
            qWarning() << "Invoices::loadById - Failed to execute line item query:" << lineQuery.lastError().text();
            loadedInvoice.dbError = lineQuery.lastError();
            // Return the partially loaded header, but signal failure
            if (ok) *ok = false;
            return loadedInvoice;
        }

        // 4. Populate Line Items
        QList<InvoiceLineItem> items;
        while (lineQuery.next()) {
            InvoiceLineItem item;
            // Populate 'item' using lineQuery.value(...) for each column
            // Example (assuming InvoiceLineItem has appropriate members/setters):
            // item.setLineItemId(lineQuery.value("LINE_ITEM_ID").toInt());
            // item.setDescription(lineQuery.value("DESCRIPTION").toString());
            // item.setQuantity(lineQuery.value("QUANTITY").toDouble()); // Or toInt()
            // item.setUnitPrice(lineQuery.value("UNIT_PRICE").toDouble());
            // item.setamount(lineQuery.value("AMOUNT").toDouble());
            // item.setInvoiceId(id); // Associate with the parent invoice

            items.append(item);
        }
        loadedInvoice.setLineItems(items); // Add loaded items to the invoice object
        qDebug() << "Loaded" << items.count() << "line items for invoice ID:" << id;

        // If we got here, everything loaded successfully
        if (ok) {
            *ok = true;
        }

    } else {
        qWarning() << "Invoices::loadById - No invoice found with ID:" << id;
        // dbError is not set here as the query executed successfully but found no data
        // ok remains false (or its initial value if not provided)
    }

    return loadedInvoice; // Return the populated invoice (or empty if not found)
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
    // Keep binding QDate for PAYMENT_DATE
    query.bindValue(":paymentDate", QDate::currentDate());
    // *** ADD: Bind QDateTime for ISSUE_DATE using the :issueDate placeholder ***
    query.bindValue(":issueDate", QDateTime::currentDateTime());
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

    // *** CHANGE: Bind "sent" status ***
    query.bindValue(":status", "sent");
    // *** CHANGE: Bind QDateTime for issue date using the :sentDate placeholder ***
    query.bindValue(":sentDate", QDateTime::currentDateTime());
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
