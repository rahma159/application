#include "gestionreclam.h"
#include "ui_gestionreclam.h"       // Includes UI class header
#include "ajoutreclamationdialog.h" // Include the add/edit dialog (Consider renaming -> addeditclaimdialog.h)

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase> // Needed for database operations
#include <QSqlQuery>    // Needed for database operations
#include <QSqlError>    // Needed for error handling
#include <QVariant>     // Needed for binding values
#include <QDateTime>    // Needed for placeholder ID generation

// Constructor
GestionReclamationDialog::GestionReclamationDialog(QWidget *parent) : // Consider renaming -> ClaimManagementDialog
    QDialog(parent),
    ui(new Ui::GestionReclamationDialog)
{
    ui->setupUi(this);

    // Configure table appearance
    // Ensure column indices match your .ui file definition
    ui->tableReclamations->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // Resize columns 0-4 to contents
    // Example: Assuming 'Description' is the 6th column (index 5)
    ui->tableReclamations->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch); // Stretch description column

    // Connect signals and slots
    // Assumes btnClose exists in the .ui file
    connect(ui->btnClose, &QPushButton::clicked, this, &GestionReclamationDialog::reject); // Close button closes the dialog
    connect(ui->tableReclamations->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &GestionReclamationDialog::onReclamationSelectionChanged); // Update buttons on selection change

    // Set initial button states based on selection
    onReclamationSelectionChanged(); // Call initially to disable modify/delete if nothing selected
    qDebug() << "Claim Management Dialog constructed.";
}

// Destructor
GestionReclamationDialog::~GestionReclamationDialog()
{
    qDebug() << "Claim Management Dialog destroyed.";
    delete ui;
}

// Sets the data for the table, potentially filtering by client ID
// Uses Reclamation struct (change to Claim if renamed)
void GestionReclamationDialog::setReclamationsData(const QList<Reclamation>& reclamations, const QString& filterClientId)
{
    m_reclamationsList = reclamations; // Consider renaming -> m_claimsList
    m_filterClientId = filterClientId; // Store the applied filter
    qDebug() << "setReclamationsData: Received" << reclamations.count() << "claims. Filter Client ID:" << filterClientId;
    populateTable(); // Update the table display
    onReclamationSelectionChanged(); // Update button states
}

// Fills the table widget with data from the m_reclamationsList
void GestionReclamationDialog::populateTable()
{
    ui->tableReclamations->setSortingEnabled(false); // Disable sorting during population for performance
    ui->tableReclamations->clearContents(); // Clear existing data rows
    ui->tableReclamations->setRowCount(0); // Reset row count
    qDebug() << "Populating claims table with" << m_reclamationsList.count() << "items."; // Use new variable name if changed

    // Uses Reclamation struct (change to Claim if renamed)
    for (const Reclamation& reclam : m_reclamationsList) { // Use new variable name if changed
        int row = ui->tableReclamations->rowCount();
        ui->tableReclamations->insertRow(row);

        // Create and set table items for each column
        // Ensure column indices match your .ui file definition
        ui->tableReclamations->setItem(row, 0, new QTableWidgetItem(reclam.id));           // ID
        ui->tableReclamations->setItem(row, 1, new QTableWidgetItem(reclam.clientId));    // Client ID
        ui->tableReclamations->setItem(row, 2, new QTableWidgetItem(reclam.date.toString("yyyy-MM-dd"))); // Date
        ui->tableReclamations->setItem(row, 3, new QTableWidgetItem(reclam.importance));  // Importance
        ui->tableReclamations->setItem(row, 4, new QTableWidgetItem(reclam.statut));      // Status

        // Truncate long descriptions and add tooltip for the 6th column (index 5)
        QString shortDesc = reclam.description.left(100) + (reclam.description.length() > 100 ? "..." : "");
        QTableWidgetItem *descItem = new QTableWidgetItem(shortDesc);
        descItem->setToolTip(reclam.description); // Show full description on hover
        ui->tableReclamations->setItem(row, 5, descItem);                                 // Description
    }

    ui->tableReclamations->setSortingEnabled(true); // Re-enable sorting
    qDebug() << "Table population finished. Row count:" << ui->tableReclamations->rowCount();
}

// --- CRUD and Refresh Slot Implementations ---

// Enables/disables Modify/Delete buttons based on table selection
// Consider renaming -> onClaimSelectionChanged
void GestionReclamationDialog::onReclamationSelectionChanged()
{
    bool hasSelection = ui->tableReclamations->selectionModel()->hasSelection();
    // Assumes btnModifier and btnSupprimer exist in the .ui file
    ui->btnModifier->setEnabled(hasSelection);
    ui->btnSupprimer->setEnabled(hasSelection);
}

// Handles the "Ajouter" (Add) button click
// Consider renaming button in .ui -> btnAdd -> on_btnAdd_clicked
void GestionReclamationDialog::on_btnAjouter_clicked()
{
    qDebug() << "Add button clicked.";
    // Consider renaming -> AddEditClaimDialog
    AjoutReclamationDialog dialog(this); // Create the add/edit dialog

    // Optional: Pre-fill client ID if viewing filtered data
    // if (!m_filterClientId.isEmpty()) {
    //     // Requires adding a method like setInitialClientId to AjoutReclamationDialog
    //     dialog.setInitialClientId(m_filterClientId);
    // }

    // Show the dialog and wait for user input
    if (dialog.exec() == QDialog::Accepted) {
        // Uses Reclamation struct (change to Claim if renamed)
        Reclamation newClaim = dialog.getReclamationData(); // Get data from the dialog

        // Basic validation
        if (newClaim.clientId.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Client ID cannot be empty."); // Translated message
            return;
        }

        // --- *** FIX FOR ORA-02291: Check if CLIENT_ID exists *** ---
        QSqlQuery checkClientQuery;
        // Make sure 'CLIENTS' table and 'ID' column names are correct for your schema
        checkClientQuery.prepare("SELECT 1 FROM CLIENTS WHERE ID = :clientId");
        checkClientQuery.bindValue(":clientId", newClaim.clientId);

        if (!checkClientQuery.exec()) {
            qWarning() << "ERROR checking client ID:" << checkClientQuery.lastError().text();
            QMessageBox::critical(this, "Database Error", "Could not verify Client ID:\n" + checkClientQuery.lastError().text()); // Translated message
            return; // Stop if we cannot verify
        }

        if (!checkClientQuery.next()) { // next() returns false if no rows are found
            qWarning() << "Client ID validation failed: ID" << newClaim.clientId << "not found in CLIENTS table.";
            QMessageBox::warning(this, "Invalid Client ID", QString("Client ID '%1' does not exist in the clients table. Please enter a valid Client ID.").arg(newClaim.clientId)); // Translated message
            return; // Stop insertion if client ID doesn't exist
        }
        qDebug() << "Client ID" << newClaim.clientId << "validated successfully.";
        // --- *** END FIX *** ---


        // --- Generate Placeholder ID (Replace with proper sequence/trigger if available) ---
        // Using timestamp is NOT robust for production but works as a placeholder
        // Ensure 'RECLAMATIONS' table and column names are correct
        QString newId = "REC" + QString::number(QDateTime::currentMSecsSinceEpoch() % 100000); // Example placeholder
        newClaim.id = newId;
        qDebug() << "Generated Claim ID (placeholder):" << newId;
        // --- End Placeholder ID Generation ---

        // --- Insert into DB (Proceed only if Client ID was valid) ---
        QSqlQuery insertQuery; // Use a different query object name
        // Ensure table 'RECLAMATIONS' and column names match your schema
        insertQuery.prepare("INSERT INTO RECLAMATIONS (ID, CLIENT_ID, DATE_RECLAMATION, DESCRIPTION, STATUT, IMPORTANCE) "
                            "VALUES (:id, :clientId, :dateReclam, :desc, :statut, :importance)");
        insertQuery.bindValue(":id", newClaim.id);
        insertQuery.bindValue(":clientId", newClaim.clientId); // This clientId is now validated
        insertQuery.bindValue(":dateReclam", newClaim.date);
        insertQuery.bindValue(":desc", newClaim.description);
        insertQuery.bindValue(":statut", newClaim.statut);
        insertQuery.bindValue(":importance", newClaim.importance);

        if (insertQuery.exec()) {
            qDebug() << "New claim successfully inserted into the DB. ID:" << newClaim.id;
            QMessageBox::information(this, "Success", "New claim added successfully!"); // Translated message
            refreshReclamationsTable(); // Refresh the table to show the new entry (Consider renaming -> refreshClaimsTable)
        } else {
            // Log the error (ORA-02291 should not happen now for CLIENT_ID, but other errors might)
            qWarning() << "ERROR inserting claim:" << insertQuery.lastError().text();
            QMessageBox::critical(this, "Database Error", "Could not add claim:\n" + insertQuery.lastError().text()); // Translated message
        }
        // --- End DB Insertion ---
    } else {
        qDebug() << "Add claim cancelled by user.";
    }
}

// Handles the "Modifier" (Modify) button click
// Consider renaming button in .ui -> btnModify -> on_btnModify_clicked
void GestionReclamationDialog::on_btnModifier_clicked()
{
    qDebug() << "Modify button clicked.";
    QModelIndexList selection = ui->tableReclamations->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        qWarning() << "Modify clicked but no row selected.";
        return; // Should not happen if button is enabled correctly, but check anyway
    }

    int selectedRow = selection.first().row();
    // Get ID from first column (index 0)
    QString claimId = ui->tableReclamations->item(selectedRow, 0)->text();
    qDebug() << "Attempting to modify claim ID:" << claimId;

    // Find the corresponding Reclamation object in our local list to pre-fill the dialog
    // Uses Reclamation struct (change to Claim if renamed)
    Reclamation dataToEdit;
    bool found = false;
    // Use new variable name if changed (m_claimsList)
    for(const auto& reclam : m_reclamationsList) {
        if (reclam.id == claimId) {
            dataToEdit = reclam;
            found = true;
            break;
        }
    }

    if (!found) {
        qWarning() << "Could not find claim data in local list for ID:" << claimId;
        // Optionally: Try to fetch from DB directly as a fallback?
        QMessageBox::warning(this, "Error", "Could not find local data for the selected claim. Try refreshing."); // Translated message
        return;
    }

    // Open the add/edit dialog in "edit mode" using the appropriate constructor
    // Consider renaming -> AddEditClaimDialog
    // Pass Claim struct if renamed
    AjoutReclamationDialog dialog(dataToEdit, this);
    if (dialog.exec() == QDialog::Accepted) {
        // Uses Reclamation struct (change to Claim if renamed)
        Reclamation updatedClaim = dialog.getReclamationData();
        // The ID remains the same and is stored in updatedClaim.id (set by the dialog in edit mode)
        qDebug() << "Dialog accepted for modifying claim ID:" << updatedClaim.id;

        // --- Update DB ---
        QSqlQuery query;
        // Prepare the UPDATE statement
        // Ensure table 'RECLAMATIONS' and column names match your schema
        query.prepare("UPDATE RECLAMATIONS SET "
                      "CLIENT_ID = :clientId, " // Usually Client ID shouldn't change, but update if needed
                      "DATE_RECLAMATION = :dateReclam, "
                      "DESCRIPTION = :desc, "
                      "STATUT = :statut, "
                      "IMPORTANCE = :importance "
                      "WHERE ID = :id"); // Use the original ID in the WHERE clause

        // Bind the updated values
        query.bindValue(":clientId", updatedClaim.clientId); // NOTE: If Client ID is changed, it should also be validated!
        query.bindValue(":dateReclam", updatedClaim.date);
        query.bindValue(":desc", updatedClaim.description);
        query.bindValue(":statut", updatedClaim.statut);
        query.bindValue(":importance", updatedClaim.importance);
        query.bindValue(":id", updatedClaim.id); // The original ID for the WHERE clause

        if (query.exec()) {
            qDebug() << "Claim ID:" << updatedClaim.id << "updated successfully.";
            QMessageBox::information(this, "Success", "Claim updated successfully!"); // Translated message
            refreshReclamationsTable(); // Refresh the table (Consider renaming -> refreshClaimsTable)
        } else {
            qWarning() << "ERROR updating claim ID:" << updatedClaim.id << query.lastError().text();
            // Check for ORA-02291 if CLIENT_ID was potentially changed to an invalid one
            if (query.lastError().text().contains("ORA-02291")) { // Oracle specific error check
                QMessageBox::critical(this, "Database Error", "Could not update claim:\nThe specified Client ID does not exist."); // Translated message
            } else {
                QMessageBox::critical(this, "Database Error", "Could not update claim:\n" + query.lastError().text()); // Translated message
            }
        }
        // --- End DB Update ---
    } else {
        qDebug() << "Modify claim cancelled by user for ID:" << claimId;
    }
}

// Handles the "Supprimer" (Delete) button click
// Consider renaming button in .ui -> btnDelete -> on_btnDelete_clicked
void GestionReclamationDialog::on_btnSupprimer_clicked()
{
    qDebug() << "Delete button clicked.";
    QModelIndexList selection = ui->tableReclamations->selectionModel()->selectedRows();
    if (selection.isEmpty()) { return; }

    int selectedRow = selection.first().row();
    // Get ID from first column (index 0)
    QString claimId = ui->tableReclamations->item(selectedRow, 0)->text();
    qDebug() << "Attempting to delete claim ID:" << claimId;

    // Ask for confirmation before deleting
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", // Translated title
                                  QString("Are you sure you want to delete claim ID: %1?") // Translated message
                                      .arg(claimId),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "User confirmed deletion for ID:" << claimId;

        // --- Delete from DB ---
        QSqlQuery query;
        // Ensure table 'RECLAMATIONS' and column 'ID' match your schema
        query.prepare("DELETE FROM RECLAMATIONS WHERE ID = :id");
        query.bindValue(":id", claimId);

        if (query.exec()) {
            qDebug() << "Claim ID:" << claimId << "deleted successfully.";
            QMessageBox::information(this, "Success", "Claim deleted successfully!"); // Translated message
            refreshReclamationsTable(); // Refresh the table (Consider renaming -> refreshClaimsTable)
        } else {
            qWarning() << "ERROR deleting claim ID:" << claimId << query.lastError().text();
            QMessageBox::critical(this, "Database Error", "Could not delete claim:\n" + query.lastError().text()); // Translated message
        }
        // --- End DB Deletion ---
    } else {
        qDebug() << "Deletion cancelled by user for ID:" << claimId;
    }
}

// Refreshes the table content by reloading data from the database
// Consider renaming -> refreshClaimsTable
void GestionReclamationDialog::refreshReclamationsTable() {
    qDebug() << "Refreshing claims table from DB...";
    m_reclamationsList.clear(); // Clear the current local list (Use new variable name if changed)

    QSqlDatabase db = QSqlDatabase::database(); // Get the default database connection
    if (!db.isOpen()) {
        qWarning() << "refreshReclamationsTable: Database connection is not open!";
        QMessageBox::critical(this, "Connection Error", "Database connection is closed. Cannot refresh."); // Translated message
        return; // Cannot proceed without connection
    }

    QSqlQuery query(db); // Create query object associated with the default connection
    // Ensure table 'RECLAMATIONS' and column names match your schema
    QString queryString = "SELECT ID, CLIENT_ID, DATE_RECLAMATION, DESCRIPTION, STATUT, IMPORTANCE FROM RECLAMATIONS";

    // Apply client filter if one is active
    if (!m_filterClientId.isEmpty()) {
        queryString += " WHERE CLIENT_ID = :clientId";
    }
    queryString += " ORDER BY DATE_RECLAMATION DESC"; // Example ordering

    query.prepare(queryString);

    // Bind the client ID if filtering
    if (!m_filterClientId.isEmpty()) {
        query.bindValue(":clientId", m_filterClientId);
    }

    if (!query.exec()) {
        qWarning() << "Error loading claims for refresh:" << query.lastError().text();
        QMessageBox::critical(this, "Loading Error", "Could not load claims from the database:\n" + query.lastError().text()); // Translated message
    } else {
        // Populate the local list with data from the query result
        // Use new variable name if changed (m_claimsList)
        // Uses Reclamation struct (change to Claim if renamed)
        while (query.next()) {
            Reclamation reclam; // Use Claim struct if renamed
            reclam.id = query.value(0).toString();
            reclam.clientId = query.value(1).toString();

            // Handle potential date/datetime types from DB
            QVariant dateVal = query.value(2);
            if (dateVal.typeId() == QMetaType::QDateTime) { reclam.date = dateVal.toDateTime().date(); }
            else if (dateVal.typeId() == QMetaType::QDate) { reclam.date = dateVal.toDate(); }
            else { reclam.date = QDate::fromString(dateVal.toString(), Qt::ISODate); } // Fallback for string dates

            reclam.description = query.value(3).toString();
            reclam.statut = query.value(4).toString();
            reclam.importance = query.value(5).toString();
            m_reclamationsList.append(reclam); // Use new variable name if changed
        }
        qDebug() << "Refresh loaded" << m_reclamationsList.count() << "claims."; // Use new variable name if changed
    }

    // Update the visual table
    populateTable();
    // Update button states (selection is lost after refresh)
    onReclamationSelectionChanged(); // Consider renaming -> onClaimSelectionChanged
}

// --- END OF CHANGES ---
