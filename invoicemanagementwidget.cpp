
#include "invoicemanagementwidget.h"
#include "ui_invoicemanagementwidget.h"
#include "createeditinvoicedialog.h" // Include the dialog header
#include "deleteinvoicedialog.h"
#include "invoices.h" // Include your Invoices class header
#include <QSqlTableModel>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QItemSelectionModel>
#include <QHeaderView> // For QHeaderView::ResizeMode
#include <QModelIndexList>
#include <QStyledItemDelegate> // <<< ADD THIS LINE
#include <QMetaType>    // For qDebug messages
#include <QTableView>
#include <QAbstractItemModel>
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QFileDialog> // For save dialog
/*#include <QPrinter>    // For PDF output
#include <QPainter> //for drawing
#include <QFile>       // For writing text file
#include <QTextStream> // For writing text file
#include <QStringConverter> // For FEC UTF-8 encoding (if using Qt 6)*/
// --- Constructor ---
// --- Inline Delegate Class Definition (WITH DEBUGGING) ---


class InlineDateDelegate : public QStyledItemDelegate
{
public:
    explicit InlineDateDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent),
        // VVVVV Ensure date-only format VVVVV
        m_dateFormat("yyyy/MM/dd hh:mm:ss")
    {
        qDebug() << "InlineDateDelegate created. Format:" << m_dateFormat; // Constructor debug
    }
    // Override the function that controls the display text
    QString displayText(const QVariant &value, const QLocale &locale) const override
    {
        // VVVVV Add Debugging Here VVVVV
        qDebug() << "InlineDateDelegate::displayText called. Value:" << value << "Type:" << value.typeName();

        Q_UNUSED(locale); // Using fixed format

        // Check if the data from the model is a QDateTime or QDate
        if (value.typeId() == QMetaType::QDateTime) {
            QDateTime dt = value.toDateTime();
            if (dt.isValid()) {
                QString formatted = dt.toString(m_dateFormat);
                qDebug() << "  -> Formatting QDateTime to:" << formatted;
                return formatted; // Use the format string
            } else {
                qDebug() << "  -> Invalid QDateTime received.";
            }
        } else if (value.typeId() == QMetaType::QDate) {
            QDate d = value.toDate();
            if (d.isValid()) {
                QString formatted = d.toString(m_dateFormat);
                qDebug() << "  -> Formatting QDate to:" << formatted;
                return formatted; // Use the format string
            } else {
                qDebug() << "  -> Invalid QDate received.";
            }
        } else {
            qDebug() << "  -> Value is not QDateTime or QDate. Using default display.";
        }

        // Fallback for other types or invalid dates/datetimes
        return QStyledItemDelegate::displayText(value, locale);
    }

    void setDateFormat(const QString &format) {
        m_dateFormat = format;
        qDebug() << "InlineDateDelegate format set to:" << m_dateFormat;
    }

private:
    QString m_dateFormat;
};
// --- End of Inline Delegate Class Definition ---

InvoiceManagementWidget::InvoiceManagementWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvoiceManagementWidget),
    model(nullptr) // Initialize model pointer
{
    ui->setupUi(this);

    // Table View Setup
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true); // Improves readability
    ui->tableView->verticalHeader()->setVisible(false); // Hide row numbers

    // === Calls to implemented helper methods ===
    setupConnections();         // Connect signals/slots
    populateFilterComboBoxes(); // Populate filters
    refreshInvoiceList();       // Load initial data (calls loadInvoices via filter button)

}

// --- Destructor ---
InvoiceManagementWidget::~InvoiceManagementWidget()
{
    delete model; // Clean up the model
    delete ui;
}
void InvoiceManagementWidget::handleTableViewClicked(const QModelIndex &index)
{
    qDebug() << "*** handleTableViewClicked SLOT ENTERED for index:" << index.row() << "," << index.column();
    Q_UNUSED(index); // We don't actually need the index here

    // The goal is just to trigger the button state update logic.
    // We can call the original slot, passing dummy selections,
    // or duplicate the enabling logic here. Calling the original is simpler.
    on_tableView_selectionChanged(QItemSelection(), QItemSelection());
}


// Connect signals/slots
// Inside InvoiceManagementWidget::setupConnections()

void InvoiceManagementWidget::setupConnections() {
    // Connect selectionChanged (KEEP THIS ONE)
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &InvoiceManagementWidget::on_tableView_selectionChanged);
    qDebug() << "Connected tableView selectionChanged to on_tableView_selectionChanged slot.";

    // Connect view's clicked signal USING A LAMBDA
    connect(ui->tableView, &QAbstractItemView::clicked, this,
            [this](const QModelIndex &index){ // Lambda function captures 'this' pointer
                qDebug() << "*** tableView clicked LAMBDA ENTERED for index:" << index.row() << "," << index.column();
                Q_UNUSED(index);
                // Call the original slot to update buttons
                this->on_tableView_selectionChanged(QItemSelection(), QItemSelection());
            });
    qDebug() << "Connected tableView clicked to lambda -> on_tableView_selectionChanged.";


   /* // Connect the delete button IF it exists in the UI
    if (ui->deleteInvoiceButton) {
        connect(ui->deleteInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_deleteInvoiceButton_clicked);
        qDebug() << "Connected deleteInvoiceButton clicked to on_deleteInvoiceButton_clicked slot.";
    } else {
        qDebug() << "deleteInvoiceButton not found during connection setup.";
    }

    // Connect edit button (implicitly by name or explicitly)
    connect(ui->editInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_editInvoiceButton_clicked);
    qDebug() << "Connected editInvoiceButton clicked to on_editInvoiceButton_clicked slot.";

    // Connect filter buttons (implicitly by name or explicitly)
    //connect(ui->applyFiltersButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_applyFiltersButton_clicked);
   // connect(ui->clearFiltersButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_clearFiltersButton_clicked);
    //connect(ui->newInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_newInvoiceButton_clicked);
   // connect(ui->markAsPaidButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_markAsPaidButton_clicked);
    connect(ui->sendInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_sendInvoiceButton_clicked);*/

}

// Populate filter combo boxes
void InvoiceManagementWidget::populateFilterComboBoxes() {
    // Status Filter
    ui->statusFilterComboBox->clear();
    ui->statusFilterComboBox->addItem(tr("All")); // Use tr() for potential translation
    // Add statuses relevant to your application
    ui->statusFilterComboBox->addItems({"unpaid", "paid", "draft", "sent", "overdue", "cancelled"}); // Example

    // Client Filter
    ui->clientFilterComboBox->clear();
    ui->clientFilterComboBox->addItem(tr("All"), -1); // Store -1 for "All"
    QSqlQuery clientQuery;
    if (clientQuery.exec("SELECT CLIENT_ID, CLIENT_NAME FROM CLIENTS ORDER BY CLIENT_NAME")) {
        while(clientQuery.next()) {
            ui->clientFilterComboBox->addItem(clientQuery.value(1).toString(), // Use column index (safer)
                                              clientQuery.value(0).toInt());
        }
    } else {
        qWarning() << "Could not load client names for filter:" << clientQuery.lastError().text();
    }
}

// Safely get the ID of the selected invoice row
int InvoiceManagementWidget::getSelectedInvoiceId() {
    if (!model) { return -1; }
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    if (!selectionModel || !selectionModel->hasSelection()) { return -1; }
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (selectedRows.isEmpty()) { return -1; }
    QModelIndex invoiceIdIndex = model->index(selectedRows.first().row(), 0); // Get index for row/col 0
    bool ok;
    int invoiceId = model->data(invoiceIdIndex).toInt(&ok);
    if (!ok || invoiceId <= 0) {
        qWarning() << "Could not retrieve valid Invoice ID from selected row. Data:" << model->data(invoiceIdIndex);
        return -1;
    }
    return invoiceId;
}

// Core data loading method
// Inside invoicemanagementwidget.cpp

// ... (includes and InlineDateDelegate class definition are already correct) ...


// Core data loading method
void InvoiceManagementWidget::loadInvoices(const QString &filterClause)
{
    qDebug() << "loadInvoices called with filter:" << filterClause;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qCritical() << "Database connection is not open in loadInvoices!";
        QMessageBox::critical(this, "Database Error", "Database connection is closed.");
        if (model){
            model->clear(); // Clear existing model data if DB fails
        }
        return; // Don't proceed if DB is closed
    }

    if (!model) {
        model = new QSqlQueryModel(this);
        qDebug() << "Created new QSqlQueryModel.";
    } else {
        qDebug() << "Reusing existing QSqlQueryModel.";
    }

    // ... (Build your queryString based on filterClause) ...
    QString queryString = "SELECT "
                          "  i.INVOICE_ID, i.INVOICE_NUMBER, i.CLIENT_NAME, "
                          "  i.ISSUE_DATE, i.TOTAL_AMOUNT, i.STATUS "
                          "FROM INVOICES i";
    if (!filterClause.isEmpty()) { queryString += " WHERE " + filterClause; }
    queryString += " ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC";


    qDebug() << "Executing query:" << queryString;
    model->setQuery(queryString, db); // Execute the query

    // Check for query errors *immediately* after setQuery
    if (model->lastError().isValid()) {
        qCritical() << "Query Error:" << model->lastError().databaseText();
        QMessageBox::critical(this, "Query Error", "Failed to load invoices: " + model->lastError().databaseText());
        model->clear(); // Clear model on error
        // Optionally set model to null or handle table view state
        // ui->tableView->setModel(nullptr); // Or keep old model? Decide based on desired UX
    } else {
        // Query was successful, proceed with setup
        qDebug() << "Query successful, rows loaded:" << model->rowCount();

        // --- Set Headers ---
        // Do this *before* trying to find index by header name
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Invoice Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Client Name"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Issue Date")); // <<< Header text we'll use
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Total Amount"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Status"));

        // --- Set the Model on the Table View ---
        ui->tableView->setModel(model);

        // ***** START: INSERT STEP 3 CODE HERE *****


        int issueDateColumnIndex = -1;
        if (model) {
            for (int col = 0; col < model->columnCount(); ++col) {
                // VVVVV Make sure this text matches the setHeaderData call exactly VVVVV
                if (model->headerData(col, Qt::Horizontal).toString().compare(tr("Issue Date"), Qt::CaseInsensitive) == 0) {
                    issueDateColumnIndex = col;
                    qDebug() << "Found 'Issue Date' column at index:" << issueDateColumnIndex;
                    break;
                }
            }
        }

        // 2. Create and apply the delegate if the column was found
        if (issueDateColumnIndex != -1) {
            qDebug() << "Applying InlineDateDelegate to column index:" << issueDateColumnIndex;
            InlineDateDelegate *delegate = new InlineDateDelegate(ui->tableView);
            // Optional: set specific format here if needed, otherwise uses delegate's default
            // delegate->setDateFormat("dd-MM-yyyy");
            ui->tableView->setItemDelegateForColumn(issueDateColumnIndex, delegate);
        } else {
            qWarning() << "Could not find 'Issue Date' column index to apply date delegate!";
        }
        // --- End of Delegate Application ---

        // ***** END: ENSURE THIS CODE IS PRESENT AND ACTIVE *****


        // --- Continue with other table view setup ---
        ui->tableView->setColumnHidden(0, true);
        ui->tableView->resizeColumnsToContents();

        // Apply stretch AFTER resizeToContents if needed
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Stretch Client Name

        // Clear previous selection after setting a new model or refreshing data
        ui->tableView->clearSelection();

        // Debug selection state immediately after clearing
        if(ui->tableView->selectionModel()) {
            qDebug() << "State *immediately after* loadInvoices/clearSelection: hasSelection() ="
                     << ui->tableView->selectionModel()->hasSelection();
        } else {
            qDebug() << "Selection model is NULL *after* loadInvoices!";
        }

        // Explicitly update button states after clearing selection
        on_tableView_selectionChanged(QItemSelection(), QItemSelection());

    } // End of else block (query successful)

} // End of loadInvoices function

// Reloads data using current filters
void InvoiceManagementWidget::refreshInvoiceList() {
    on_applyFiltersButton_clicked(); // Easiest way is to re-apply filters
}


// --- SLOTS IMPLEMENTATIONS ---

// Apply Filters Button
void InvoiceManagementWidget::on_applyFiltersButton_clicked()
{
    // <<< METTEZ LE CODE DE DÉBOGAGE ICI >>>
    QDate startDateDbg = ui->startDateEdit->date(); // Lire la date de début depuis l'UI
    QDate endDateDbg   = ui->endDateEdit->date();   // Lire la date de fin depuis l'UI
    qDebug() << "--- on_applyFiltersButton_clicked ---"; // Marqueur de début
    qDebug() << "Date début lue (startDateEdit):" << startDateDbg;
    qDebug() << "Date fin lue (endDateEdit):" << endDateDbg;
    // <<< FIN DU CODE DE DÉBOGAGE >>>


    // --- Le reste de votre logique de filtrage commence ici ---
    QStringList conditions;
    QString status = ui->statusFilterComboBox->currentText();
    // Use combo box data to get Client ID if storing ID, otherwise use text
    QString clientFilterValue = ui->clientFilterComboBox->currentText(); // Assuming text filtering for now
    QVariant clientData = ui->clientFilterComboBox->currentData();

    if (status != tr("All") && !status.isEmpty()) {
        conditions << QString("i.STATUS = '%1'").arg(status.replace("'", "''"));
    }
    // Example: Filter by Client ID if available, otherwise by name like before
    if (clientData.isValid() && clientData.toInt() > 0) {
        conditions << QString("i.CLIENT_ID = %1").arg(clientData.toInt());
    } else if (clientFilterValue != tr("All") && !clientFilterValue.isEmpty()) {
        conditions << QString("i.CLIENT_NAME LIKE '%%1%'").arg(clientFilterValue.replace("'", "''"));
    }

    // Utiliser les variables de débogage pour vérifier la validité
    // Ou relire les dates si vous préférez, mais c'est redondant
    if (startDateDbg.isValid() && endDateDbg.isValid() &&
        startDateDbg > QDate(2025, 04, 21) && endDateDbg >= startDateDbg) {
        QString startDateStr = startDateDbg.toString("yyyy-MM-dd");
        QString endDateStr   = endDateDbg.toString("yyyy-MM-dd");
        qDebug() << "Dates valides et dans l'intervalle. Application du filtre de date SQL.";
        qDebug() << "  Start Date String pour SQL:" << startDateStr;
        qDebug() << "  End Date String pour SQL:" << endDateStr;
        conditions << QString("TRUNC(i.ISSUE_DATE) BETWEEN TO_DATE('%1', 'YYYY-MM-DD') AND TO_DATE('%2', 'YYYY-MM-DD')");
        conditions << QString("TRUNC(i.DUE_DATE) BETWEEN TO_DATE('%1', 'YYYY-MM-DD') AND TO_DATE('%2', 'YYYY-MM-DD')");
    } else {
        // Ajouter un message si les dates ne sont PAS appliquées
        qDebug() << "Le filtre de date n'est PAS appliqué (dates invalides, hors limites ou ordre incorrect).";
        qDebug() << "  startDateDbg.isValid():" << startDateDbg.isValid();
        qDebug() << "  endDateDbg.isValid():" << endDateDbg.isValid();
        qDebug() << "  startDateDbg > QDate(2025, 04, 21):" << (startDateDbg > QDate(2025, 04, 21));
        qDebug() << "  endDateDbg >= startDateDbg:" << (endDateDbg >= startDateDbg);
    }



    QString searchTerm = ui->searchInvoiceLineEdit->text().trimmed();
    if (!searchTerm.isEmpty()) {
        QString escapedTerm = searchTerm.replace("'", "''");
        qDebug() << "Application du filtre de recherche textuelle:" << escapedTerm;
        conditions << QString("(UPPER(i.INVOICE_NUMBER) LIKE UPPER('%%1%') OR UPPER(i.CLIENT_NAME) LIKE UPPER('%%1%'))").arg(escapedTerm); // Case-insensitive search
    }

    QString finalFilter = conditions.join(" AND "); // Construire la condition finale
    qDebug() << "Condition WHERE finale pour loadInvoices:" << finalFilter;
    loadInvoices(finalFilter); // Appeler loadInvoices avec la condition construite
    qDebug() << "--- Fin on_applyFiltersButton_clicked ---"; // Marqueur de fin
}

// Clear Filters Button
void InvoiceManagementWidget::on_clearFiltersButton_clicked()
{
    ui->statusFilterComboBox->setCurrentIndex(0);
    ui->clientFilterComboBox->setCurrentIndex(0);
    if (ui->searchInvoiceLineEdit) ui->searchInvoiceLineEdit->clear();
    ui->startDateEdit->setDate(QDate(2025, 04, 21));
    ui->endDateEdit->setDate(QDate::currentDate());
    loadInvoices(); // Reload all


}

// New Invoice Button
void InvoiceManagementWidget::on_newInvoiceButton_clicked()
{
    CreateEditInvoiceDialog dialog(this);
    dialog.prepareForNewInvoice();
    if (dialog.exec() == QDialog::Accepted) {
        refreshInvoiceList();
    }



}

// Edit Invoice Button
void InvoiceManagementWidget::on_editInvoiceButton_clicked()
{
    int invoiceIdToEdit = getSelectedInvoiceId();
    if (invoiceIdToEdit <= 0) { return; } // getSelectedInvoiceId shows warning if needed
    CreateEditInvoiceDialog dialog(this);
    if (dialog.loadInvoiceForEditing(invoiceIdToEdit)) {
        if (dialog.exec() == QDialog::Accepted) {
            refreshInvoiceList();
        }
    }
}

// Delete Invoice Button
void InvoiceManagementWidget::on_deleteInvoiceButton_clicked() {
    qDebug() << "Main Delete Invoice button clicked.";

    // 1. Get selected row and Invoice ID/Number FROM THE MODEL
    QItemSelectionModel *select = ui->tableView->selectionModel();

    if (!model || !select || !select->hasSelection()) {
        qWarning() << "Delete clicked, but no row selected or model invalid.";
        QMessageBox::warning(this, tr("Delete Invoice"), tr("Please select an invoice to delete."));
        return;
    }

    QModelIndexList selectedRows = select->selectedRows();
    if (selectedRows.count() != 1) {
        QMessageBox::warning(this, tr("Delete Invoice"), tr("Please select only one invoice to delete at a time."));
        return;
    }
    QModelIndex selectedIndex = selectedRows.first();
    int modelRow = selectedIndex.row();

    // Get ID (Column 0)
    QModelIndex idIndex = model->index(modelRow, 0);
    bool okId;
    int invoiceIdToDelete = model->data(idIndex).toInt(&okId);
    if (!okId || !idIndex.isValid() || invoiceIdToDelete <= 0) {
        qWarning() << "Invalid invoice ID retrieved from model row" << modelRow;
        QMessageBox::critical(this, tr("Error"), tr("Invalid invoice ID found for the selected row."));
        return;
    }

    // Get Number (Column 1)
    QString invoiceNumber = "N/A";
    QModelIndex numberIndex = model->index(modelRow, 1);
    if(numberIndex.isValid()) {
        invoiceNumber = model->data(numberIndex).toString();
    }
    qDebug() << "Invoice selected for potential deletion - ID:" << invoiceIdToDelete << "Number:" << invoiceNumber;


    // 2. Create and Show the Confirmation Dialog
    DeleteInvoiceDialog deleteDialog(invoiceIdToDelete, invoiceNumber, this); // Pass ID and Number
    int dialogResult = deleteDialog.exec(); // Show the dialog modally

    // 3. Handle the Dialog's Result
    if (dialogResult == QDialog::Accepted) {
        // Deletion was attempted AND reported as successful by the dialog
        qDebug() << "Delete dialog accepted (deletion successful). Refreshing list.";
        refreshInvoiceList(); // Refresh the main table view
    } else {
        // Dialog was cancelled or deletion failed within the dialog
        qDebug() << "Delete dialog rejected or deletion failed within dialog.";
        // No need to do anything here, the dialog showed the error message if needed
    }
}
// Inside InvoiceManagementWidget class in invoicemanagementwidget.cpp

// invoicemanagementwidget.cpp

void InvoiceManagementWidget::on_tableView_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    qDebug() << "*** on_tableView_selectionChanged SLOT ENTERED ***";
    Q_UNUSED(selected); Q_UNUSED(deselected);

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    if (!selectionModel) {
        qDebug() << "Selection model is NULL! Cannot determine selection.";
        ui->editInvoiceButton->setEnabled(false);
        if (ui->deleteInvoiceButton) ui->deleteInvoiceButton->setEnabled(false);
        return; // Exit if no selection model
    }

    // --- Attempt 1: Use selectedIndexes() count ---
    // Sometimes more reliable immediately after model changes than hasSelection()
    bool selectionExists = !selectionModel->selectedIndexes().isEmpty();
    qDebug() << "Check 1: selectedIndexes().isEmpty() is" << !selectionExists;


    // --- Attempt 2: Check selectedRows() count (what you were using) ---
    // Let's log its count directly
    int selectedRowCount = selectionModel->selectedRows().count();
    qDebug() << "Check 2: selectedRows().count() is" << selectedRowCount;

    // Determine final state based on either check being positive
    // We generally want at least one index/row selected
    bool enableButtons = selectionExists || (selectedRowCount > 0);


    // Update Buttons
    ui->editInvoiceButton->setEnabled(enableButtons);

    bool deleteButtonState = false;
    if (ui->deleteInvoiceButton) {
        ui->deleteInvoiceButton->setEnabled(enableButtons);
        deleteButtonState = ui->deleteInvoiceButton->isEnabled();
    } else {
        qDebug() << "deleteInvoiceButton pointer is NULL!";
    }

    qDebug() << "Final Decision: EnableButtons:" << enableButtons << "| Edit Button Enabled:" << ui->editInvoiceButton->isEnabled() << "| Delete Button Enabled:" << deleteButtonState;
}


void InvoiceManagementWidget::on_tableView_activated(const QModelIndex &index)
{
    qDebug() << "Table view activated for row:" << index.row();

    // Add the code you want to execute on activation here.
    // For example, you might want to call the edit function:
    // on_editInvoiceButton_clicked();

    // Or just leave it empty if you don't need it right now,
    // but keeping the empty implementation fixes the linker error.*/
    Q_UNUSED(index); // Add this if you don't use the index parameter to avoid warnings
}

void InvoiceManagementWidget::on_markAsPaidButton_clicked()
{
    qDebug() << "Mark As Paid button clicked.";

    // --- 1. Get Selected Invoice Info ---
    int selectedRow = -1;
    int invoiceId = -1;
    QString invoiceNumber = "N/A";
    QString currentStatus = "N/A";
    int invoiceNumberCol = -1;
    int statusCol = -1;

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    if (!model || !selectionModel || !selectionModel->hasSelection()) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice from the table first."));
        return;
    }

    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice row from the table first."));
        return;
    }

    // Get data from the *first* selected row (assuming single selection)
    selectedRow = selectedRows.first().row();

    // Find column indices by header name (robust way)
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        if (header.compare("ID", Qt::CaseInsensitive) == 0) { // Assuming "ID" is header for col 0
            invoiceId = model->data(model->index(selectedRow, col)).toInt();
        } else if (header.compare("Invoice Number", Qt::CaseInsensitive) == 0) {
            invoiceNumberCol = col;
        } else if (header.compare("Status", Qt::CaseInsensitive) == 0) {
            statusCol = col;
        }
    }

    // Retrieve Invoice Number and Status using found indices
    if (invoiceNumberCol != -1) {
        invoiceNumber = model->data(model->index(selectedRow, invoiceNumberCol)).toString();
    } else {
        qWarning() << "Could not find 'Invoice Number' column.";
        // Optionally use ID if number not found
        invoiceNumber = QString("ID: %1").arg(invoiceId > 0 ? QString::number(invoiceId) : "Unknown");
    }
    if (statusCol != -1) {
        currentStatus = model->data(model->index(selectedRow, statusCol)).toString();
    } else {
        qWarning() << "Could not find 'Status' column.";
    }


    // --- 2. Validations ---
    if (invoiceId <= 0) {
        QMessageBox::critical(this, tr("Error"), tr("Could not retrieve a valid ID for the selected invoice."));
        return;
    }

    if (currentStatus.compare("paid", Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, tr("Already Paid"), tr("Invoice '%1' is already marked as paid.").arg(invoiceNumber));
        return;
    }

    // --- 3. Confirmation Dialog ---
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirm Payment"),
                                  tr("Do you really want to mark invoice '%1' as paid?").arg(invoiceNumber),
                                  QMessageBox::Yes | QMessageBox::Cancel);

    // --- 4. Process Confirmation ---
    if (reply == QMessageBox::Yes) {
        qDebug() << "User confirmed marking invoice ID" << invoiceId << "as paid.";

        // --- 5. Call Database Update ---
        bool updateSuccess = Invoices::markAsPaidStatic(invoiceId); // Call static function

        // --- 6. Handle Update Result ---
        if (updateSuccess) {
            QMessageBox::information(this, tr("Success"), tr("Invoice '%1' successfully marked as paid.").arg(invoiceNumber));
            refreshInvoiceList(); // Reload data in the table
        } else {
            // Retrieve the last error *from the database connection* if the static method doesn't return it
            QSqlError lastError = QSqlDatabase::database().lastError();
            QMessageBox::critical(this, tr("Database Error"),
                                tr("Failed to mark invoice '%1' as paid.\n\nError: %2")
                                      .arg(invoiceNumber)
                                      .arg(lastError.isValid() ? lastError.text() : tr("Unknown error.")));
        }
    } else {
        qDebug() << "User cancelled marking invoice as paid.";
    }

}

void InvoiceManagementWidget::on_sendInvoiceButton_clicked() {
    qDebug() << "Send Invoice button clicked.";

    // --- 1. Get Selected Invoice Info ---
    int selectedRow = -1;
    int invoiceId = -1;
    QString invoiceNumber = "N/A";
    QString currentStatus = "N/A";
    int idCol = -1; // Added for clarity
    int invoiceNumberCol = -1;
    int statusCol = -1;

    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    // Add basic model check
    if (!model) {
        QMessageBox::critical(this, tr("Error"), tr("Table model is not initialized."));
        return;
    }
    if (!selectionModel || !selectionModel->hasSelection()) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice from the table first."));
        return;
    }

    QModelIndexList selectedRows = selectionModel->selectedRows();
        // Handle case where full row might not be selected initially
    if (selectedRows.isEmpty()) {
        QModelIndex currentIndex = ui->tableView->currentIndex();
        if (!currentIndex.isValid()) {
            QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice cell from the table first."));
            return;
        }
        selectedRow = currentIndex.row();
    } else {
        selectedRow = selectedRows.first().row();
    }

    if (selectedRow < 0) {
        QMessageBox::warning(this, tr("No Selection"), tr("Could not determine selected row."));
        return;
    }

    // Find column indices by header name (robust way)
    // *Ensure your table view headers are exactly "ID", "Invoice Number", "Status"*
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        if (header.compare("ID", Qt::CaseInsensitive) == 0) {
            idCol = col;
        } else if (header.compare("Invoice Number", Qt::CaseInsensitive) == 0) {
            invoiceNumberCol = col;
        } else if (header.compare("Status", Qt::CaseInsensitive) == 0) {
            statusCol = col;
        }
    }

    // Retrieve ID - Essential
    if (idCol != -1) {
        invoiceId = model->data(model->index(selectedRow, idCol)).toInt();
    } else {
        qWarning() << "Could not find 'ID' column header.";
        QMessageBox::critical(this, tr("Configuration Error"), tr("Could not find 'ID' column in table. Cannot proceed."));
        return;
    }

    // Retrieve Invoice Number and Status using found indices
    if (invoiceNumberCol != -1) {
        invoiceNumber = model->data(model->index(selectedRow, invoiceNumberCol)).toString();
    } else {
        qWarning() << "Could not find 'Invoice Number' column header.";
        invoiceNumber = QString("ID: %1").arg(invoiceId); // Fallback display
    }
    if (statusCol != -1) {
        currentStatus = model->data(model->index(selectedRow, statusCol)).toString();
    } else {
        qWarning() << "Could not find 'Status' column header.";
        // Cannot check current status if column not found
    }


    // --- 2. Validations ---
    if (invoiceId <= 0) {
        QMessageBox::critical(this, tr("Error"), tr("Could not retrieve a valid ID for the selected invoice."));
        return;
    }

    // *** CHANGE: Check if already "sent" ***
    // Only check if status was found
    if (statusCol != -1 && currentStatus.compare("sent", Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, tr("Already Sent"), tr("Invoice '%1' is already marked as sent.").arg(invoiceNumber));
        return;
    }

    // --- 3. Confirmation Dialog ---
    // *** CHANGE: Update confirmation message ***
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirm Send"),
                                  tr("Do you really want to mark invoice '%1' as sent?").arg(invoiceNumber),
                                  QMessageBox::Yes | QMessageBox::Cancel);

    // --- 4. Process Confirmation ---
    if (reply == QMessageBox::Yes) {
        qDebug() << "User confirmed marking invoice ID" << invoiceId << "as sent.";

        // --- 5. Call Database Update ---
        // *** CHANGE: Call the new static function ***
        bool updateSuccess = Invoices::markAsSentStatic(invoiceId); // Call static function

        // --- 6. Handle Update Result ---
        if (updateSuccess) {
            // *** CHANGE: Update success message ***
            QMessageBox::information(this, tr("Success"), tr("Invoice '%1' successfully marked as sent.").arg(invoiceNumber));
            refreshInvoiceList(); // Reload data in the table
        } else {
            // Retrieve the last error *from the database connection*
            QSqlError lastError = QSqlDatabase::database().lastError();
            // *** CHANGE: Update error message ***
            QMessageBox::critical(this, tr("Database Error"),
                                  tr("Failed to mark invoice '%1' as sent.\n\nError: %2")
                                      .arg(invoiceNumber)
                                      .arg(lastError.isValid() ? lastError.text() : tr("Unknown error."))); // Same fallback message
        }
    } else {
        qDebug() << "User cancelled marking invoice as sent.";
    }
}


/*
void InvoiceManagementWidget::on_exportPdfButton_clicked() {
    qDebug() << "Export PDF button clicked.";

    // --- 1. Get Selected Invoice Info ---
    int selectedRow = -1;
    int invoiceId = -1;
    // ... (Code to get selectedRow and invoiceId - similar to previous examples) ...
    // ... (Find idCol, get invoiceId from model->data(...)) ...

    if (invoiceId <= 0) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice first."));
        return;
    }
    qDebug() << "Selected Invoice ID for PDF Export:" << invoiceId;

    // --- 2. Fetch Full Invoice Data ---
    // NOTE: This part is crucial and depends on your data model.
    // You need a way to get all details based on invoiceId.
    // Placeholder - replace with your actual data loading:
    Invoices currentInvoiceData; // Assuming Invoices class holds all details
    bool dataLoaded = Invoices::loadFullInvoiceDetails(invoiceId, currentInvoiceData); // Example static function

    if (!dataLoaded) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load full details for invoice ID %1.").arg(invoiceId));
        return;
    }

    // --- 3. Prompt for Save Location ---
    QString suggestedFileName = QString("Invoice_%1.pdf").arg(currentInvoiceData.getInvoiceNumber()); // Use a relevant field
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Invoice PDF"), suggestedFileName, tr("PDF Documents (*.pdf)"));

    if (fileName.isEmpty()) {
        qDebug() << "User cancelled PDF save dialog.";
        return; // User cancelled
    }

    // --- 4. Generate PDF ---
    bool success = generateInvoicePdf(fileName, currentInvoiceData);

    // --- 5. Show Result ---
    if (success) {
        QMessageBox::information(this, tr("Success"), tr("Invoice successfully exported to:\n%1").arg(fileName));
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to generate PDF for invoice ID %1.").arg(invoiceId));
        // More specific errors should ideally be logged or returned from generateInvoicePdf
    }
}

// --- Helper Function for PDF Generation (add this to the class or make it static) ---
bool InvoiceManagementWidget::generateInvoicePdf(const QString &filePath, const Invoices &invoiceData) {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4)); // Or appropriate size
    printer.setPageMargins(QMarginsF(15, 15, 15, 15)); // Example margins (mm)

    QPainter painter;
    if (!painter.begin(&printer)) { // Start painting onto the printer (PDF)
        qWarning() << "Failed to start painter for PDF generation!";
        return false;
    }

    // *** This is where you draw the invoice content ***
    // This is a VERY basic example. Real implementation needs layout, fonts, etc.
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));

    int yPos = 50; // Example starting Y position
    painter.drawText(50, yPos, QString("Invoice #: %1").arg(invoiceData.getInvoiceNumber()));
    yPos += 30;
    painter.drawText(50, yPos, QString("Client: %1").arg(invoiceData.getClientName()));
    yPos += 30;
    painter.drawText(50, yPos, QString("Issue Date: %1").arg(invoiceData.getIssueDate().toString(Qt::ISODate)));
    yPos += 30;
    // ... Draw client address, your address, line items (in a loop), totals, notes etc. ...
    // You'll need to calculate positions, handle page breaks if necessary.

    painter.end(); // Finalize painting

    qDebug() << "PDF generation attempted for:" << filePath;
    // QPrinter doesn't directly return success/failure of writing easily,
    // but if painter.begin failed, we returned false. Check if file exists?
    return QFile::exists(filePath); // Basic check
}


void InvoiceManagementWidget::on_exportFecbutton_clicked() {
    qDebug() << "Export FEC button clicked.";

    // --- OPTIONAL: Get Selected Invoice Info (If FEC is per-invoice) ---
    // Many FEC exports are for a whole accounting period, not just one invoice.
    // Adapt this section based on whether you export for one invoice or a period.
    int selectedRow = -1;
    int invoiceId = -1;
    // ... (Code to get selectedRow and invoiceId - similar to previous examples) ...
    // ... (Find idCol, get invoiceId from model->data(...)) ...

    // if (invoiceId <= 0) { // If exporting for a specific invoice
    //     QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice first."));
    //     return;
    // }
    // qDebug() << "Selected Invoice ID for FEC Export:" << invoiceId;

    // --- 2. Get Data for FEC ---
    // CRITICAL: This needs to fetch the required *accounting entries* based on
    // the FEC specification. This might involve complex queries joining
    // invoices, journal entries, accounts, etc., possibly filtered by date range.
    // Placeholder - replace with your actual data fetching logic:
    // QList<AccountingEntry> fecData = AccountingData::getFecEntries(startDate, endDate); // Example for a period
    QList<SomeFecDataStructure> fecData; // Replace with your data structure
   // bool dataLoaded = fetchFecData(fecData , potentially invoiceId or date rang);

    if (!dataLoaded || fecData.isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load or no accounting data found for FEC export."));
        return;
    }

    // --- 3. Prompt for Save Location ---
    // FEC files often have specific naming conventions e.g., SIREN+FEC+ clôture.txt
    QString suggestedFileName = QString("FEC_Export.txt"); // Adjust as needed
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save FEC File"), suggestedFileName, tr("Text Files (*.txt);;All Files (*)")); // FEC is often .txt

    if (fileName.isEmpty()) {
        qDebug() << "User cancelled FEC save dialog.";
        return; // User cancelled
    }

    // --- 4. Generate FEC File ---
    bool success = generateFecFile(fileName, fecData);

    // --- 5. Show Result ---
    if (success) {
        QMessageBox::information(this, tr("Success"), tr("FEC data successfully exported to:\n%1").arg(fileName));
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to generate FEC file."));
        // More specific errors should ideally be logged or returned from generateFecFile
    }
}

// --- Helper Function for FEC Generation (add this to the class or make it static) ---
// *** THIS IS A VERY SIMPLIFIED STRUCTURE - CONSULT OFFICIAL FEC SPECS ***
bool InvoiceManagementWidget::generateFecFile(const QString &filePath, const QList<SomeFecDataStructure> &fecData) {
    QFile file(filePath);
    // Open in WriteOnly mode, Text mode is important for newline handling
    // Ensure UTF-8 encoding is used.
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing FEC data:" << filePath << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8); // Explicitly set UTF-8 encoding is crucial for FEC
    // out.setGenerateByteOrderMark(false); // Often FEC should NOT have a BOM

    // --- Write Header Row ---
    // This MUST match the exact FEC specification column names and order
    // Example (replace with actual FEC columns!):
    out << "JournalCode\tJournalLib\tEcritureNum\tEcritureDate\tCompteNum\tCompteLib\tCompAuxNum\tCompAuxLib\tPieceRef\tPieceDate\tEcritureLib\tDebit\tCredit\tEcritureLet\tDateLet\tValidDate\tMontantdevise\tIdevise" << Qt::endl;


    // --- Write Data Rows ---
    QString separator = "\t"; // FEC often uses TAB as separator

    for (const SomeFecDataStructure &entry : fecData) {
        // --- Format each field according to FEC rules ---
        // Dates: YYYYMMDD
        // Numbers: Dot (.) as decimal separator, no thousands separator. Format to 2 decimal places.
        // Text: Ensure proper encoding, escape special characters if needed (though usually not required if using TSV).
        // Empty fields: Usually represented by empty strings ""

        // Example formatting (replace with your actual data members and formatting):
        QStringList fields;
        fields << entry.getJournalCode(); // Example getter
        fields << entry.getJournalLib();
        fields << entry.getEntryNum();
        fields << entry.getEntryDate().toString("yyyyMMdd"); // Date format
        fields << entry.getAccountNumber();
        fields << entry.getAccountLib();
        fields << entry.getAuxAccountNumber(); // May be empty
        fields << entry.getAuxAccountLib();   // May be empty
        fields << entry.getPieceRef();
        fields << entry.getPieceDate().toString("yyyyMMdd"); // Date format
        fields << entry.getEntryLib();
        // Format numbers carefully
        fields << QString::number(entry.getDebitAmount(), 'f', 2); // Debit
        fields << QString::number(entry.getCreditAmount(), 'f', 2); // Credit
        fields << entry.getLettrageCode(); // May be empty
        fields << entry.getLettrageDate().toString("yyyyMMdd"); // May be empty or 00000000
        fields << entry.getValidationDate().toString("yyyyMMdd");
        fields << (entry.hasCurrencyAmount() ? QString::number(entry.getCurrencyAmount(), 'f', 2) : ""); // Optional fields
        fields << (entry.hasCurrencyCode() ? entry.getCurrencyCode() : ""); // Optional fields

        out << fields.join(separator) << Qt::endl;
    }

    file.close(); // Important to close the file to flush buffers

    qDebug() << "FEC generation attempted for:" << filePath;
    return file.error() == QFile::NoError; // Check if any error occurred during writing/closing
}

*/
