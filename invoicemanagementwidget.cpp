#include "invoicemanagementwidget.h"
#include "ui_invoicemanagementwidget.h"
#include "createeditinvoicedialog.h" // Include the dialog header
#include "deleteinvoicedialog.h"
#include "statisticsdialog.h"
#include "invoices.h"
#include "clientpaymentwidget.h"
#include "invoicelineitem.h"
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
#include <QFileDialog>
#include <QPrinter>    // <<< UNCOMMENT/ADD THIS for PDF output
#include <QPainter>    // <<< UNCOMMENT/ADD THIS for drawing
#include <QFile>       // <<< UNCOMMENT/ADD THIS for file existence check
#include <QPageSize>   // <<< ADD THIS for page size definitions
#include <QMarginsF>
#include <QAbstractItemModel>
#include <QPageLayout>
#include <QRegularExpression>
#include <QFontMetrics>
#include <algorithm> // For std::max if used
#include <QLocale>
#include <QFontMetricsF>
#include <QTextDocument> // Alternative for complex layout, but QPainter is fine here
#include <QRectF>
#include <QMarginsF>
#include <QPen>
#include <QFontInfo>
#include <QTextStream>
#include <QStringConverter>
#include <QDesktopServices> // <<< ADDED for auto-open
#include <QUrl>
#include <QLabel>
#include <QToolTip>
#include <QProcess>
#include <QTimer>

// --- Constructor ---
// --- Inline Delegate Class Definition (WITH DEBUGGING) ---
const int SORT_DEFAULT_ISSUE_DESC = 0;
const int SORT_CLIENT_ASC = 1;
const int SORT_CLIENT_DESC = 2;
const int SORT_DUE_DATE_ASC = 3;
const int SORT_DUE_DATE_DESC = 4;
const int SORT_AMOUNT_ASC = 5;
const int SORT_AMOUNT_DESC = 6;


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
    model(nullptr),
    // --- MATCH THIS ORDER TO YOUR .h FILE ---
    m_currentFilterClause(""),        // Line 58?
    reminderTimer(nullptr),           // Line 59? (Must come before m_sortOrder)
    m_currentOrderByClause("ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC"), // Line 61? (Must come before m_sortColumn)
    m_sortColumn(3),                  // Line 62?
    m_sortOrder(Qt::DescendingOrder)
                                     // Initialized fifth?
// --- END REORDER ---
{
    // ** Step 1: UI Setup - MUST BE CALLED FIRST **
    ui->setupUi(this);

    // ** Now you can safely access ui elements **
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // ... other table setup if needed ...

    // Step 2: Signal/Slot Connections
    setupConnections();

    // Step 3: Populate Client Dropdown (DB Query)
    populateFilterComboBoxes();

    // Step 4: Populate Sort Dropdown (No DB)
    populateSortComboBox();

    // Step 5: Set Dates (Corrected)
    ui->startDateEdit->setDate(QDate::currentDate().addMonths(-3));
    ui->endDateEdit->setDate(QDate::currentDate());

    // Step 6: Load Initial Data (DB Queries!)
    refreshInvoiceList();

    // Step 7: Setup the timer (call the function)
    setupReminderTimer();
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
    //on_tableView_selectionChanged(QItemSelection(), QItemSelection());
}


// Connect signals/slots
// Inside InvoiceManagementWidget::setupConnections()

void InvoiceManagementWidget::setupConnections() {
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &InvoiceManagementWidget::on_tableView_selectionChanged);
    qDebug() << "Connected tableView selectionChanged to on_tableView_selectionChanged slot.";

    // *** REMOVED: Connection for Header Click ***
    // connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, ...);

    // --- ADD CONNECTION FOR SORT COMBOBOX ---
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &InvoiceManagementWidget::on_sortComboBox_currentIndexChanged);
    qDebug() << "Connected sortComboBox currentIndexChanged.";
    // --- END ---

    // Connect table cell click (if needed, e.g., for button states)
    connect(ui->tableView, &QAbstractItemView::clicked, this,
            [this](const QModelIndex &index){
                Q_UNUSED(index);
                this->on_tableView_selectionChanged(QItemSelection(), QItemSelection());
            });
    qDebug() << "Connected tableView clicked to lambda -> on_tableView_selectionChanged.";

    /*connect(ui->viewStatisticsButton, &QPushButton::clicked,
            this, &InvoiceManagementWidget::on_viewStatisticsButton_clicked);
    qDebug() << "Connected viewStatisticsButton clicked.";
    // Buttons (Ensure names match your UI file exactly, or connect explicitly)
    // Filter Buttons
    connect(ui->applyFiltersButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_applyFiltersButton_clicked);
    connect(ui->clearFiltersButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_clearFiltersButton_clicked);
    // Action Buttons
    connect(ui->newInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_newInvoiceButton_clicked);
    connect(ui->editInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_editInvoiceButton_clicked);
    connect(ui->deleteInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_deleteInvoiceButton_clicked);
    connect(ui->sendInvoiceButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_sendInvoiceButton_clicked);
    // Export Buttons
    connect(ui->exportInvoiceListPdfButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_exportInvoiceListPdfButton_clicked);*/
    connect(ui->exportFecbutton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_exportFecButton_clicked); // Check name: is it still FEC or generic TSV?

    qDebug() << "Standard button connections attempted.";
}

void InvoiceManagementWidget::on_viewStatisticsButton_clicked()
{
    qDebug() << "View Statistics button clicked.";
    // Create and show the dialog modally
    StatisticsDialog statsDialog(this); // Pass 'this' as parent
    statsDialog.exec(); // Show the dialog and wait until it's closed
}

void InvoiceManagementWidget::on_sortComboBox_currentIndexChanged(int index)
{
    if (index < 0) return; // Ignore invalid index

    int sortData = ui->sortComboBox->itemData(index).toInt();
    qDebug() << "Sort ComboBox index changed to:" << index << " Sort Data:" << sortData;

    QString newOrderBy;
    int newSortColumn = m_sortColumn; // Keep previous column if data is invalid
    Qt::SortOrder newSortOrder = m_sortOrder;

    // !! CHECK THESE INDICES against your final SELECT query order in loadInvoices !!
    // Current SELECT order: ID(0), Num(1), Client(2), Issue(3), Due(4), Amount(5), Status(6)
    switch(sortData) {
    case SORT_DEFAULT_ISSUE_DESC:
        newOrderBy = "ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC";
        newSortColumn = 3; newSortOrder = Qt::DescendingOrder; break;
    case SORT_CLIENT_ASC:
        newOrderBy = "ORDER BY CLIENT_FULL_NAME ASC, i.INVOICE_ID ASC";
        newSortColumn = 2; newSortOrder = Qt::AscendingOrder; break;
    case SORT_CLIENT_DESC:
        newOrderBy = "ORDER BY CLIENT_FULL_NAME DESC, i.INVOICE_ID DESC";
        newSortColumn = 2; newSortOrder = Qt::DescendingOrder; break;
    case SORT_DUE_DATE_ASC:
        newOrderBy = "ORDER BY i.DUE_DATE ASC, i.INVOICE_ID ASC";
        newSortColumn = 4; newSortOrder = Qt::AscendingOrder; break; // Index 4 for Due Date
    case SORT_DUE_DATE_DESC:
        newOrderBy = "ORDER BY i.DUE_DATE DESC, i.INVOICE_ID DESC";
        newSortColumn = 4; newSortOrder = Qt::DescendingOrder; break; // Index 4 for Due Date
    case SORT_AMOUNT_ASC:
        newOrderBy = "ORDER BY i.TOTAL_AMOUNT ASC, i.INVOICE_ID ASC";
        newSortColumn = 5; newSortOrder = Qt::AscendingOrder; break; // Index 5 for Amount
    case SORT_AMOUNT_DESC:
        newOrderBy = "ORDER BY i.TOTAL_AMOUNT DESC, i.INVOICE_ID DESC";
        newSortColumn = 5; newSortOrder = Qt::DescendingOrder; break; // Index 5 for Amount
    default:
        qWarning() << "Unknown sort data from combobox:" << sortData;
        return;
    }

    // Update member variables only if the effective order changed
    if (m_currentOrderByClause != newOrderBy) {
        m_currentOrderByClause = newOrderBy;
        m_sortColumn = newSortColumn;
        m_sortOrder = newSortOrder;
        qDebug() << "ComboBox changed OrderBy clause to:" << m_currentOrderByClause;

        // Reload data using the current filter and the NEW sort order
        loadInvoices(m_currentFilterClause);
        updateSummaryLabels(m_currentFilterClause); // Update summaries too
        // No need to update sort indicator here, loadInvoices does it
    } else {
        qDebug() << "Sort ComboBox selection didn't change effective sort order.";
    }
}

void InvoiceManagementWidget::populateSortComboBox() {
    // Block signals temporarily to prevent triggering slot during population
    bool wasBlocked = ui->sortComboBox->blockSignals(true);
    ui->sortComboBox->clear();
    // Add items with user-friendly text and integer data representing the sort
    ui->sortComboBox->addItem(tr("Default (Issue Date Newest)"), SORT_DEFAULT_ISSUE_DESC);
    ui->sortComboBox->addItem(tr("Client Name (A-Z)"), SORT_CLIENT_ASC);
    ui->sortComboBox->addItem(tr("Client Name (Z-A)"), SORT_CLIENT_DESC);
    ui->sortComboBox->addItem(tr("Due Date (Oldest First)"), SORT_DUE_DATE_ASC);
    ui->sortComboBox->addItem(tr("Due Date (Newest First)"), SORT_DUE_DATE_DESC);
    ui->sortComboBox->addItem(tr("Amount (Low to High)"), SORT_AMOUNT_ASC);
    ui->sortComboBox->addItem(tr("Amount (High to Low)"), SORT_AMOUNT_DESC);
    ui->sortComboBox->blockSignals(wasBlocked); // Restore signal state

    updateSortComboBoxSelection(); // Set initial index based on default sort state
    qDebug() << "Populated sortComboBox.";
}
void InvoiceManagementWidget::updateSortComboBoxSelection() {
    int targetData = -1;
    // Determine which sort constant matches the current m_sortColumn and m_sortOrder
    // !! CHECK THESE INDICES against your final SELECT query order in loadInvoices !!
    // Current SELECT order: ID(0), Num(1), Client(2), Issue(3), Due(4), Amount(5), Status(6)
    if (m_sortColumn == 3 && m_sortOrder == Qt::DescendingOrder) targetData = SORT_DEFAULT_ISSUE_DESC; // Issue Date Desc (Index 3)
    else if (m_sortColumn == 2 && m_sortOrder == Qt::AscendingOrder) targetData = SORT_CLIENT_ASC; // Client Asc (Index 2)
    else if (m_sortColumn == 2 && m_sortOrder == Qt::DescendingOrder) targetData = SORT_CLIENT_DESC; // Client Desc (Index 2)
    else if (m_sortColumn == 4 && m_sortOrder == Qt::AscendingOrder) targetData = SORT_DUE_DATE_ASC; // Due Date Asc (Index 4)
    else if (m_sortColumn == 4 && m_sortOrder == Qt::DescendingOrder) targetData = SORT_DUE_DATE_DESC; // Due Date Desc (Index 4)
    else if (m_sortColumn == 5 && m_sortOrder == Qt::AscendingOrder) targetData = SORT_AMOUNT_ASC; // Amount Asc (Index 5)
    else if (m_sortColumn == 5 && m_sortOrder == Qt::DescendingOrder) targetData = SORT_AMOUNT_DESC; // Amount Desc (Index 5)

    int indexToSelect = ui->sortComboBox->findData(targetData);
    if (indexToSelect == -1) {
        indexToSelect = ui->sortComboBox->findData(SORT_DEFAULT_ISSUE_DESC); // Fallback
        qWarning() << "Could not find matching sort data in combobox, falling back to default.";
    }

    // Set the current index without triggering the currentIndexChanged signal again
    bool wasBlocked = ui->sortComboBox->blockSignals(true);
    ui->sortComboBox->setCurrentIndex(indexToSelect);
    ui->sortComboBox->blockSignals(wasBlocked);
    qDebug() << "Synced sortComboBox selection to index:" << indexToSelect << "for sort data:" << targetData;
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
    ui->clientFilterComboBox->addItem(tr("All"), -1);
    QSqlQuery clientQuery;
    // **** Querying NEW CLIENT Table ****
    const QString clientSql = "SELECT ID, FIRST_NAME, LAST_NAME FROM CLIENT ORDER BY LAST_NAME, FIRST_NAME";
    qDebug() << "Populating client filter with query:" << clientSql;
    if (clientQuery.exec(clientSql)) {
        while(clientQuery.next()) {
            // **** Extracting NEW Columns and combining name ****
            int clientId = clientQuery.value(0).toInt();
            QString firstName = clientQuery.value(1).toString();
            QString lastName = clientQuery.value(2).toString();
            QString fullName = (firstName + " " + lastName).trimmed();

            ui->clientFilterComboBox->addItem(fullName, clientId); // Add combined name and ID
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
    if (selectedRows.isEmpty()) {
        // Maybe try current index if row selection is empty
        QModelIndex currentIdx = ui->tableView->currentIndex();
        if (!currentIdx.isValid()) return -1;
        selectedRows.append(currentIdx); // Use the row of the current cell
    }
    if (selectedRows.isEmpty()) { return -1; } // Still empty? Give up.

    // Assuming Invoice ID is ALWAYS column 0 in the SELECT statement
    QModelIndex invoiceIdIndex = model->index(selectedRows.first().row(), 0);
    if (!invoiceIdIndex.isValid()) {
        qWarning() << "Could not get valid model index for ID column (0) at row" << selectedRows.first().row();
        return -1;
    }
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
    if (!db.isOpen()) { /* ... error handling ... */ return; }

    if (!model) { model = new QSqlQueryModel(this); }

    m_currentFilterClause = filterClause; // Store filter

    // Define the SELECT statement consistently
    // Order: ID(0), Num(1), Client(2), Issue(3), Due(4), Amount(5), Status(6)
    QString baseQueryString =
        "SELECT "
        "  i.INVOICE_ID, i.INVOICE_NUMBER, "
        "  (c.FIRST_NAME || ' ' || c.LAST_NAME) AS CLIENT_FULL_NAME, "
        "  i.ISSUE_DATE, i.DUE_DATE, i.TOTAL_AMOUNT, i.STATUS " // Correct order
        "FROM INVOICES i "
        "LEFT JOIN CLIENT c ON i.CLIENT_ID = c.ID ";

    QString finalQueryString = baseQueryString;
    if (!m_currentFilterClause.isEmpty()) {
        finalQueryString += " WHERE " + m_currentFilterClause;
    }

    // Append dynamic sort order from member variable
    if (!m_currentOrderByClause.isEmpty()) {
        finalQueryString += " " + m_currentOrderByClause;
    } else {
        finalQueryString += " ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC"; // Default
    }

    qDebug() << "Executing query:" << finalQueryString;
    model->setQuery(finalQueryString, db);

    if (model->lastError().isValid()) {
        /* ... error handling ... */
    } else {
        qDebug() << "Query successful, rows loaded:" << model->rowCount();
        // Set Headers (Match SELECT order)
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Invoice Number"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Client Name"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Issue Date"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Due Date"));     // Index 4
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Total Amount")); // Index 5
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Status"));       // Index 6

        ui->tableView->setModel(model);

        // Apply Delegate (If needed - e.g., InlineDateDelegate)
        InlineDateDelegate *dateDelegate = new InlineDateDelegate(ui->tableView);
        ui->tableView->setItemDelegateForColumn(3, dateDelegate); // Issue Date at index 3
        ui->tableView->setItemDelegateForColumn(4, dateDelegate); // Due Date at index 4

        // Table View Setup
        ui->tableView->setColumnHidden(0, true);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

        // *** REMOVED: setSortIndicator here, let the table handle it via setSortingEnabled(false) ***
        // Although header click is disabled, visually showing the sort state is good.
        // But let's disable it to fully remove header interaction influence.
        // If you *do* want the arrow, uncomment the line below.
        // ui->tableView->horizontalHeader()->setSortIndicator(m_sortColumn, m_sortOrder);


        ui->tableView->clearSelection();
        on_tableView_selectionChanged(QItemSelection(), QItemSelection());
    }
}
// Reloads data using current filters
void InvoiceManagementWidget::refreshInvoiceList() {
    on_applyFiltersButton_clicked(); // Easiest way is to re-apply filters
}


// --- SLOTS IMPLEMENTATIONS ---

// Apply Filters Button
void InvoiceManagementWidget::on_applyFiltersButton_clicked()
{
    // Debugging output for dates read from UI
    QDate startDateDbg = ui->startDateEdit->date(); // Read start date from UI
    QDate endDateDbg   = ui->endDateEdit->date();   // Read end date from UI
    qDebug() << "--- on_applyFiltersButton_clicked ---"; // Start marker
    qDebug() << "Start Date read (startDateEdit):" << startDateDbg;
    qDebug() << "End Date read (endDateEdit):" << endDateDbg;

    // --- Start of Filtering Logic ---

    QStringList conditions; // Declaration for the list of WHERE conditions

    // --- Get Filter Values from UI ---
    QString status = ui->statusFilterComboBox->currentText();
    QVariant clientData = ui->clientFilterComboBox->currentData(); // Get client ID (-1 for All)
    QString clientNameText = ui->clientFilterComboBox->currentText(); // Get display text
    QString searchTerm = ui->searchInvoiceLineEdit->text().trimmed();

    // --- Apply Status Filter ---
    if (status != tr("All") && !status.isEmpty()) {
        QString escapedStatus = status;
        escapedStatus.replace("'", "''"); // Escape single quotes
        conditions << QString("i.STATUS = '%1'").arg(escapedStatus);
        qDebug() << "Applying Status filter:" << escapedStatus;
    }

    // --- Apply Client Filter ---
    if (clientData.isValid() && clientData.toInt() > 0) {
        conditions << QString("i.CLIENT_ID = %1").arg(clientData.toInt());
        qDebug() << "Applying Client filter by ID:" << clientData.toInt();
    }
    else if (clientNameText != tr("All") && !clientNameText.isEmpty()) {
        QString escapedValue = clientNameText;
        escapedValue.replace("'", "''");
        qWarning() << "Filtering by client name text - may be slow:" << escapedValue;
        conditions << QString("UPPER(c.FIRST_NAME || ' ' || c.LAST_NAME) LIKE UPPER('%%%1%%')").arg(escapedValue);
    }

    // --- Apply Date Filter (Now on DUE_DATE) ---
    if (startDateDbg.isValid() && endDateDbg.isValid() && endDateDbg >= startDateDbg) {
        QString startDateStr = startDateDbg.toString("yyyy-MM-dd");
        QString endDateStr   = endDateDbg.toString("yyyy-MM-dd");
        qDebug() << "Applying DUE DATE filter: " << startDateStr << "to" << endDateStr; // Updated debug message

        // *** THIS LINE IS CHANGED TO USE i.DUE_DATE ***
        conditions << QString("(TRUNC(i.DUE_DATE) BETWEEN TO_DATE('%1', 'YYYY-MM-DD') AND TO_DATE('%2', 'YYYY-MM-DD'))")
                          .arg(startDateStr).arg(endDateStr);
    } else {
        qDebug() << "Date filter not applied (invalid range or dates).";
    }

    // --- Apply Search Term Filter ---
    if (!searchTerm.isEmpty()) {
        QString escapedTerm = searchTerm;
        escapedTerm.replace("'", "''");
        qDebug() << "Applying search term filter:" << escapedTerm;
        conditions << QString("(UPPER(i.INVOICE_NUMBER) LIKE UPPER('%%%1%%') OR UPPER(c.FIRST_NAME || ' ' || c.LAST_NAME) LIKE UPPER('%%%1%%'))")
                          .arg(escapedTerm);
    }

    // --- Build Final Filter Clause and Load Data ---
    QString finalFilter = conditions.join(" AND "); // Combine all conditions with AND
    qDebug() << "Final WHERE clause for loadInvoices:" << finalFilter;
    loadInvoices(finalFilter);
    updateSummaryLabels(finalFilter);
    qDebug() << "--- Fin on_applyFiltersButton_clicked ---";
}


// Clear Filters Button
void InvoiceManagementWidget::on_clearFiltersButton_clicked()
{
    qDebug() << "--- on_clearFiltersButton_clicked ---";
    // Reset UI filter controls
    ui->statusFilterComboBox->setCurrentIndex(0);
    ui->clientFilterComboBox->setCurrentIndex(0);
    if (ui->searchInvoiceLineEdit) ui->searchInvoiceLineEdit->clear();

    // Set date edits back to a default visual state
    ui->startDateEdit->setDate(QDate::currentDate().addMonths(-3));
    ui->endDateEdit->setDate(QDate::currentDate());

    m_sortColumn = 3; // Default: Issue Date (Adjust index)
    m_sortOrder = Qt::DescendingOrder;
    m_currentOrderByClause = "ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC";

    updateSortComboBoxSelection();
    // Load ALL invoices by passing an empty filter string
    loadInvoices(""); // Or simply loadInvoices(); if it handles empty string correctly
    updateSummaryLabels("");
    qDebug() << "Cleared filters and loaded all invoices.";
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
    qDebug() << "Edit Invoice button clicked."; // Optional: Add a debug message
    int invoiceIdToEdit = getSelectedInvoiceId();

    // --- ADDED CHECK AND MESSAGE BOX ---
    if (invoiceIdToEdit <= 0) {
        // Show the warning message if no valid invoice ID was retrieved
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice first."));
        qDebug() << "Edit Invoice aborted: No valid invoice selected."; // Optional debug message
        return; // Stop execution here
    }


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
    int invoiceId = getSelectedInvoiceId();

    // This check is already present and correct:
    if (invoiceId <= 0) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice first."));
        return;
    }


    QItemSelectionModel *select = ui->tableView->selectionModel();
    if (!model || !select || !select->hasSelection()) { // Should theoretically not happen if invoiceId > 0
        qWarning() << "Delete clicked logic inconsistency: Got valid ID but selection model issue found.";
        QMessageBox::warning(this, tr("Selection Error"), tr("Could not re-confirm selection. Please try again."));
        return;
    }
    QModelIndexList selectedRows = select->selectedRows();
    if (selectedRows.count() != 1) { // Should not happen if invoiceId > 0 and single selection mode
        QMessageBox::warning(this, tr("Selection Error"), tr("Please select only one invoice row."));
        return;
    }
    QModelIndex selectedIndex = selectedRows.first();
    int modelRow = selectedIndex.row();

    // Get Number (Column 1) - Find column index robustly
    QString invoiceNumber = "N/A";
    int numberCol = -1;
    for (int c = 0; c < model->columnCount(); ++c) {
        if (model->headerData(c, Qt::Horizontal).toString().compare(tr("Invoice Number"), Qt::CaseInsensitive) == 0) {
            numberCol = c;
            break;
        }
    }
    if(numberCol != -1) {
        invoiceNumber = model->data(model->index(modelRow, numberCol)).toString();
    } else {
        qWarning() << "Could not find 'Invoice Number' column for delete confirmation message.";
    }
    qDebug() << "Invoice selected for potential deletion - ID:" << invoiceId << "Number:" << invoiceNumber;


    // Create and Show the Confirmation Dialog
    DeleteInvoiceDialog deleteDialog(invoiceId, invoiceNumber, this); // Pass ID and Number
    int dialogResult = deleteDialog.exec(); // Show the dialog modally

    // Handle the Dialog's Result
    if (dialogResult == QDialog::Accepted) {
        qDebug() << "Delete dialog accepted (deletion successful). Refreshing list.";
        refreshInvoiceList(); // Refresh the main table view
    } else {
        qDebug() << "Delete dialog rejected or deletion failed within dialog.";
    }
}

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



void InvoiceManagementWidget::on_exportInvoiceListPdfButton_clicked() {
    qDebug() << "Export Invoice List PDF button clicked.";
    if (!model) {
        QMessageBox::critical(this, tr("Error"), tr("Table model is not initialized. Cannot export."));
        return;
    }
    if (model->rowCount() == 0) {
        QMessageBox::warning(this, tr("No Data"), tr("There are no invoices in the current view to export."));
        return;
    }
    qDebug() << "Model is valid and contains" << model->rowCount() << "rows.";

    // --- File Dialog ---
    QString suggestedFileName = QString("Invoice_List_%1.pdf").arg(QDate::currentDate().toString("yyyyMMdd"));
    // Store the chosen filename in a variable accessible later
    QString chosenFileName = QFileDialog::getSaveFileName(this, tr("Save Invoice List PDF"), suggestedFileName, tr("PDF Documents (*.pdf);;All Files (*)"));

    if (chosenFileName.isEmpty()) {
        qDebug() << "User cancelled save dialog.";
        return;
    }
    // Ensure .pdf extension
    if (!chosenFileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        chosenFileName += ".pdf";
    }

    // --- Generate PDF ---
    qDebug() << "Calling generateInvoiceListPdf for file:" << chosenFileName;
    // Pass the chosen filename to the generation function
    bool success = generateInvoiceListPdf(chosenFileName, model);

    // --- Handle Result ---
    if (success) {
        qDebug() << "PDF generation successful.";
        QMessageBox::information(this, tr("Export Successful"), tr("Invoice list successfully exported to:\n%1").arg(chosenFileName));

        // *** ADDED: Attempt to open the PDF file ***
        qDebug() << "Attempting to open exported PDF file:" << chosenFileName;
        bool opened = QDesktopServices::openUrl(QUrl::fromLocalFile(chosenFileName));
        if (!opened) {
            qWarning() << "Could not automatically open the exported PDF file. The default PDF viewer might not be set or the file path is invalid.";
            // Optional: Show a message box that it couldn't be opened automatically
            // QMessageBox::warning(this, tr("Auto-Open Failed"), tr("Could not automatically open the exported PDF file:\n%1\nPlease open it manually.").arg(chosenFileName));
        } else {
            qDebug() << "PDF file open command sent successfully.";
        }
        // --- End of Added Code ---

    } else {
        qDebug() << "PDF generation failed.";
        QMessageBox::critical(this, tr("Export Failed"), tr("Failed to generate the invoice list PDF.\nCheck application logs for details."));
    }
}

// Keep your existing generateInvoiceListPdf function exactly as it was
bool InvoiceManagementWidget::generateInvoiceListPdf(const QString &filePath, QAbstractItemModel *invoiceModel)
{
    // ... (Your existing PDF generation code using QTextDocument goes here) ...
    // ... (No changes needed inside this function itself) ...

    // Make sure this function returns true on success and false on failure
    // based on the QPrinter state or file existence/size check, as you had before.

    qDebug() << "--- Starting generateInvoiceListPdf (QTextDocument Version - Modified) ---";
    qDebug() << "  Output File Path:" << filePath;

    if (!invoiceModel) { qWarning() << "!!! Null model provided."; return false; }
    int numRows = invoiceModel->rowCount();
    if (numRows == 0) { qWarning() << "!!! Model has no rows."; return false; }
    qDebug() << "  Generating PDF for" << numRows << "rows using QTextDocument.";

    // --- Define Columns (Match your SELECT query in loadInvoices) ---
    const int colInvoiceID  = 0;
    const int colInvoiceNum = 1;
    const int colClientName = 2;
    const int colIssueDate  = 3;
    const int colTotalAmount= 4;
    const int colStatus     = 5;

    // --- Build HTML String ---
    QString html;
    html += "<html><head><style>";
    html += "body { font-family: Arial, sans-serif; font-size: 9pt; }";
    html += "h1 { text-align: center; font-size: 16pt; margin-bottom: 10px; margin-top: 5px; }";
    html += ".gendate { text-align: left; font-size: 8pt; margin-bottom: 20px; color: grey; }";
    html += "table { width: 95%; border-collapse: collapse; margin-left: auto; margin-right: auto; margin-top: 25px; }";
    html += "th { background-color: #e0e0e0; border: 1px solid #a0a0a0; padding: 5px; text-align: left; font-weight: bold; font-size: 10pt; }";
    html += "td { border: 1px solid #c0c0c0; padding: 5px; vertical-align: top; }";
    html += ".amount { text-align: right; }";
    html += ".id { text-align: right; }";
    html += "</style></head><body>";
    html += QString("<p class='gendate'>Generated on: %1</p>").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    html += "<h1>Invoice List</h1>";
    html += "<table><thead><tr>";
    html += QString("<th class='id'>%1</th>").arg(invoiceModel->headerData(colInvoiceID, Qt::Horizontal).toString());
    html += QString("<th>%1</th>").arg(invoiceModel->headerData(colInvoiceNum, Qt::Horizontal).toString());
    html += QString("<th>%1</th>").arg(invoiceModel->headerData(colClientName, Qt::Horizontal).toString());
    html += QString("<th>%1</th>").arg(invoiceModel->headerData(colIssueDate, Qt::Horizontal).toString());
    html += QString("<th class='amount'>%1</th>").arg(invoiceModel->headerData(colTotalAmount, Qt::Horizontal).toString());
    html += QString("<th>%1</th>").arg(invoiceModel->headerData(colStatus, Qt::Horizontal).toString());
    html += "</tr></thead><tbody>";

    QLocale locale = QLocale::system();
    for (int row = 0; row < numRows; ++row) {
        html += "<tr>";
        QString invID = invoiceModel->data(invoiceModel->index(row, colInvoiceID)).toString().toHtmlEscaped();
        QString invNum = invoiceModel->data(invoiceModel->index(row, colInvoiceNum)).toString().toHtmlEscaped();
        QString client = invoiceModel->data(invoiceModel->index(row, colClientName)).toString().toHtmlEscaped();
        QVariant dateVariant = invoiceModel->data(invoiceModel->index(row, colIssueDate));
        QString issueDateStr;
        if (dateVariant.typeId() == QMetaType::QDateTime) { issueDateStr = dateVariant.toDateTime().toString("yyyy-MM-dd"); }
        else if (dateVariant.typeId() == QMetaType::QDate) { issueDateStr = dateVariant.toDate().toString("yyyy-MM-dd"); }
        else { issueDateStr = dateVariant.toString().toHtmlEscaped(); }
        double total = invoiceModel->data(invoiceModel->index(row, colTotalAmount)).toDouble();
        QString status = invoiceModel->data(invoiceModel->index(row, colStatus)).toString().toHtmlEscaped();
        QString totalStr = locale.toString(total, 'f', 2);

        html += QString("<td class='id'>%1</td>").arg(invID);
        html += QString("<td>%1</td>").arg(invNum);
        html += QString("<td>%1</td>").arg(client);
        html += QString("<td>%1</td>").arg(issueDateStr);
        html += QString("<td class='amount'>%1</td>").arg(totalStr);
        html += QString("<td>%1</td>").arg(status);
        html += "</tr>";
    }
    html += "</tbody></table></body></html>";
    qDebug() << "Generated HTML content (first 500 chars):" << html.left(500);

    // --- Create QTextDocument ---
    QTextDocument document;
    document.setDefaultFont(QFont("Arial", 9));
    document.setHtml(html);
    document.setPageSize(QPageSize(QPageSize::A4).size(QPageSize::Point));

    // --- Setup Printer ---
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath); // Use the passed filePath
    printer.setPageSize(QPageSize(QPageSize::A4));
    qreal marginMM = 15.0;
    printer.setPageMargins(QMarginsF(marginMM, marginMM, marginMM, marginMM), QPageLayout::Millimeter);
    qDebug() << "Printer configured for A4, PDF output to" << filePath;

    // --- Print the document ---
    qDebug() << "Attempting to print QTextDocument to PDF...";
    document.print(&printer);
    qDebug() << "QTextDocument::print() finished.";

    // --- Final Check ---
    if (printer.printerState() == QPrinter::Error) {
        qWarning() << "!!! QPrinter encountered an error state after document printing.";
        QFile file(filePath);
        if (!file.exists() || file.size() == 0) {
            qWarning() << "!!! Output PDF file might be missing or empty.";
        }
        return false; // Indicate failure
    }

    qDebug() << "--- generateInvoiceListPdf (QTextDocument Version - Modified) finished successfully ---";
    return true; // Indicate success
}




void InvoiceManagementWidget::on_exportFecButton_clicked() // Keep name or rename button/slot
{
    qDebug() << "Enhanced Export button clicked.";

    // --- 1. Get Date Range (Keep for filtering) ---
    QDate startDate = ui->startDateEdit->date();
    QDate endDate = ui->endDateEdit->date();

    if (!startDate.isValid() || !endDate.isValid() || startDate > endDate) {
        QMessageBox::warning(this, tr("Invalid Date Range"), tr("Please select a valid start and end date range for the export."));
        return;
    }
    QString startDateStr = startDate.toString("yyyy-MM-dd");
    QString endDateStr = endDate.toString("yyyy-MM-dd");
    qDebug() << "Export Range:" << startDateStr << "to" << endDateStr;

    // --- 2. Choose Output File ---
    QString defaultFileName = QString("Invoice_Export_%1.tsv").arg(QDate::currentDate().toString("yyyyMMdd")); // Renamed slightly
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Invoice Export"), defaultFileName, tr("Tab Separated Values (*.tsv);;All Files (*)"));

    if (fileName.isEmpty()) {
        qDebug() << "User cancelled save dialog.";
        return;
    }
    if (!fileName.endsWith(".tsv", Qt::CaseInsensitive)) {
        fileName += ".tsv";
    }

    // --- 3. Open File & Text Stream ---
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("File Error"), tr("Could not open file for writing:\n%1\nError: %2").arg(fileName).arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Encoding::Utf8); // Or out.setCodec("UTF-8"); for Qt 5
    out.setFieldAlignment(QTextStream::AlignLeft);

    // --- 4. Write Enhanced Header ---
    // *** ADDED Client ID, Email, Payment Terms, Payment Date, Notes ***
    QStringList header = {
        tr("Invoice Number"), tr("Client ID"), tr("Client Name"), tr("Client Email"),
        tr("Issue Date"), tr("Due Date"), tr("Payment Date"), // Added Payment Date
        tr("Status"), tr("Payment Terms"), // Added Payment Terms
        tr("Subtotal"), tr("Tax Amount"), tr("Total Amount"),
        tr("Notes") // Added Notes
    };
    out << header.join("\t") << "\n";

    // --- 5. Query Database for Relevant Invoices ---
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Database connection is closed. Cannot export list."));
        file.close();
        return;
    }

    QSqlQuery query(db);
    // *** ADDED columns to SELECT statement ***
    QString sql =
        "SELECT "
        "  i.INVOICE_NUMBER, i.ISSUE_DATE, i.DUE_DATE, i.PAYMENT_DATE, " // Added PAYMENT_DATE
        "  i.SUBTOTAL, i.TAX_AMOUNT, i.TOTAL_AMOUNT, i.STATUS, "
        "  i.CLIENT_ID, i.PAYMENT_TERMS, i.NOTES, " // Added CLIENT_ID, PAYMENT_TERMS, NOTES
        "  c.EMAIL AS CLIENT_EMAIL, (c.FIRST_NAME || ' ' || c.LAST_NAME) AS CLIENT_FULL_NAME " // Added EMAIL
        "FROM INVOICES i "
        "LEFT JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        // Keep filters or adjust as needed for this export
        "WHERE i.STATUS IN ('paid', 'sent', 'unpaid', 'draft', 'overdue') "
        "  AND TRUNC(i.ISSUE_DATE) BETWEEN TO_DATE(:startDate, 'YYYY-MM-DD') AND TO_DATE(:endDate, 'YYYY-MM-DD') "
        "ORDER BY i.ISSUE_DATE, i.INVOICE_NUMBER";

    query.prepare(sql);
    query.bindValue(":startDate", startDateStr);
    query.bindValue(":endDate", endDateStr);

    qDebug() << "Executing enhanced export data query...";
    if (!query.exec()) {
        qCritical() << "Export Query Error:" << query.lastError().text();
        qCritical() << "Executed Query was:" << query.executedQuery(); // Log executed query on error
        QMessageBox::critical(this, tr("Query Error"), "Failed to retrieve invoice data for export: " + query.lastError().text());
        file.close();
        return;
    }

    qDebug() << "Export Query successful. Processing rows...";

    // --- 6. Process Query Results and Write Enhanced Lines ---
    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::OmitGroupSeparator);

    int invoicesExported = 0;
    while (query.next()) {
        // --- Extract data including new columns ---
        QString invoiceNumber = query.value("INVOICE_NUMBER").toString();
        QString clientId = query.value("CLIENT_ID").toString(); // Get Client ID
        QString clientName = query.value("CLIENT_FULL_NAME").toString().simplified();
        QString clientEmail = query.value("CLIENT_EMAIL").toString(); // Get Client Email
        QDateTime issueDateTime = query.value("ISSUE_DATE").toDateTime();
        QDateTime dueDateTime = query.value("DUE_DATE").toDateTime();
        QVariant paymentDateVar = query.value("PAYMENT_DATE"); // Get Payment Date (might be null)
        QString status = query.value("STATUS").toString();
        QString paymentTerms = query.value("PAYMENT_TERMS").toString(); // Get Payment Terms
        double subtotal = query.value("SUBTOTAL").toDouble();
        double taxAmount = query.value("TAX_AMOUNT").toDouble();
        double totalAmount = query.value("TOTAL_AMOUNT").toDouble();
        QString notes = query.value("NOTES").toString(); // Get Notes

        // --- Format dates (DD/MM/YYYY), handle null payment date ---
        QString issueDateStrExport = issueDateTime.toString("dd/MM/yyyy");
        QString dueDateStrExport = dueDateTime.toString("dd/MM/yyyy");
        QString paymentDateStrExport = ""; // Default to empty
        if (!paymentDateVar.isNull() && paymentDateVar.toDate().isValid()) {
            paymentDateStrExport = paymentDateVar.toDate().toString("dd/MM/yyyy");
        }


        // --- Format amounts ---
        QString subtotalStr = locale.toString(subtotal, 'f', 2);
        QString taxAmountStr = locale.toString(taxAmount, 'f', 2);
        QString totalAmountStr = locale.toString(totalAmount, 'f', 2);

        // --- Create ONE line for this invoice with the specific columns ---
        // Ensure order matches the header defined above
        QStringList lineData = {
            invoiceNumber, clientId, clientName, clientEmail,
            issueDateStrExport, dueDateStrExport, paymentDateStrExport,
            status, paymentTerms,
            subtotalStr, taxAmountStr, totalAmountStr,
            notes
        };
        out << lineData.join("\t") << "\n";
        invoicesExported++;

    } // End while loop

    // --- 7. Finalize and Report ---
    file.close(); // IMPORTANT: Close file BEFORE trying to open it

    if (query.lastError().isValid() && query.lastError().type() != QSqlError::NoError) {
        qCritical() << "Error after processing export data:" << query.lastError().text();
        QMessageBox::critical(this, tr("Export Error"), tr("An error occurred while processing invoice data:\n%1").arg(query.lastError().text()));
    } else if (invoicesExported == 0) {
        qDebug() << "No relevant invoice data found for the selected period/status for export.";
        QMessageBox::information(this, tr("Export"), tr("No invoice data found matching the selected criteria for the export.\nAn empty file (with header) was created:\n%1").arg(fileName));
    }
    else {
        qDebug() << "Successfully wrote" << invoicesExported << "invoices to" << fileName;
        QMessageBox::information(this, tr("Export Successful"), tr("Invoice list successfully exported with %1 invoices to:\n%2").arg(invoicesExported).arg(fileName));

        // *** ADDED: Attempt to open the file ***
        qDebug() << "Attempting to open exported file:" << fileName;
        bool opened = QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        if (!opened) {
            qWarning() << "Could not automatically open the exported file. The default application might not be set or the file path is invalid.";
            // Optional: Show a message box that it couldn't be opened automatically
            // QMessageBox::warning(this, tr("Auto-Open Failed"), tr("Could not automatically open the exported file:\n%1\nPlease open it manually.").arg(fileName));
        } else {
            qDebug() << "File open command sent successfully.";
        }
    }
}



void InvoiceManagementWidget::updateSummaryLabels(const QString& currentFilterClause)
{
    qDebug() << "--- Updating Summary Labels ---";
    qDebug() << "Using filter clause:" << currentFilterClause;

    // Set default/loading text initially
    ui->totalInvoicesLabel->setText("...");
    ui->totalDueLabel->setText("...");
    ui->totalOverdueLabel->setText("...");
    ui->avgPaymentTimeLabel->setText("...");
    ui->financialHealthLabel->setText("...");

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database not open in updateSummaryLabels.";
        ui->totalInvoicesLabel->setText("DB Err");
        ui->totalDueLabel->setText("DB Err");
        ui->totalOverdueLabel->setText("DB Err");
        ui->avgPaymentTimeLabel->setText("DB Err");
        ui->financialHealthLabel->setText("DB Err");
        return;
    }

    // --- 1. Total Invoices ---
    int totalInvoicesCount = (model ? model->rowCount() : 0);
    // *** MODIFIED LINE: Append descriptive text ***
    ui->totalInvoicesLabel->setText(tr("Total Invoices: ") +QString::number(totalInvoicesCount));
    qDebug() << "Total Invoices (from model):" << totalInvoicesCount;

    // --- Common SQL Parts ---
    QString baseSql = "FROM INVOICES i LEFT JOIN CLIENT c ON i.CLIENT_ID = c.ID ";
    QString whereClause = "";
    if (!currentFilterClause.isEmpty()) {
        whereClause = "WHERE " + currentFilterClause;
    }

    // Define locale for currency formatting (adjust if needed)
    QLocale systemLocale = QLocale::system(); // Use system's locale
    QString currencySymbol = systemLocale.currencySymbol(); // Get currency symbol (shorter way)


    // --- 2. Total Due ---
    double totalDue = 0.0;
    { // Scope for query object
        QSqlQuery query(db);
        QString dueStatuses = "'sent', 'unpaid', 'overdue', 'draft'";
        QString dueCondition = QString("i.STATUS IN (%1)").arg(dueStatuses);

        QString finalWhere = whereClause;
        if (finalWhere.isEmpty()) { finalWhere = "WHERE " + dueCondition; }
        else { finalWhere += " AND " + dueCondition; }

        QString sql = "SELECT NVL(SUM(i.TOTAL_AMOUNT), 0) " + baseSql + finalWhere;
        qDebug() << "Total Due SQL:" << sql;

        if (query.exec(sql)) {
            if (query.next()) {
                totalDue = query.value(0).toDouble();
                // *** CORRECTED FORMATTING ***
                ui->totalDueLabel->setText(tr("Total Due: ") +currencySymbol + systemLocale.toString(totalDue, 'f', 2));
            } else { ui->totalDueLabel->setText("Calc Err"); }
        } else {
            qWarning() << "Total Due query failed:" << query.lastError().text();
            ui->totalDueLabel->setText("DB Err");
        }
        qDebug() << "Total Due Calculated:" << totalDue;
    } // End query scope


    // --- 3. Total Overdue ---
    double totalOverdue = 0.0;
    { // Scope for query object
        QSqlQuery query(db);
        QString overdueCondition = QString("( (i.STATUS IN ('sent', 'unpaid', 'overdue')) AND (TRUNC(i.DUE_DATE) < TRUNC(SYSDATE)) )");

        QString finalWhere = whereClause;
        if (finalWhere.isEmpty()) { finalWhere = "WHERE " + overdueCondition; }
        else { finalWhere += " AND " + overdueCondition; }

        QString sql = "SELECT NVL(SUM(i.TOTAL_AMOUNT), 0) " + baseSql + finalWhere;
        qDebug() << "Total Overdue SQL:" << sql;

        if (query.exec(sql)) {
            if (query.next()) {
                totalOverdue = query.value(0).toDouble();
                    // *** CORRECTED FORMATTING ***
                ui->totalOverdueLabel->setText(tr("Total Overdue: ") +currencySymbol + systemLocale.toString(totalOverdue, 'f', 2));
            } else { ui->totalOverdueLabel->setText("Calc Err"); }
        } else {
            qWarning() << "Total Overdue query failed:" << query.lastError().text();
            ui->totalOverdueLabel->setText("DB Err");
        }
        qDebug() << "Total Overdue Calculated:" << totalOverdue;
    } // End query scope


    // --- 4. Average Payment Time ---
    double avgDays = -1.0;
    { // Scope for query object
        QSqlQuery query(db);
        QString paidCondition = QString("(i.STATUS = 'paid' AND i.PAYMENT_DATE IS NOT NULL AND i.ISSUE_DATE IS NOT NULL)");

        QString finalWhere = whereClause;
        if (finalWhere.isEmpty()) { finalWhere = "WHERE " + paidCondition; }
        else { finalWhere += " AND " + paidCondition; }

        QString sql = "SELECT AVG(TRUNC(i.PAYMENT_DATE) - TRUNC(i.ISSUE_DATE)) " + baseSql + finalWhere;
        qDebug() << "Avg Payment Time SQL:" << sql;

        if (query.exec(sql)) {
            if (query.next()) {
                QVariant avgResult = query.value(0);
                if (!avgResult.isNull()) {
                    avgDays = avgResult.toDouble();
                    ui->avgPaymentTimeLabel->setText(tr("Average Payment Time: ") +QString::number(avgDays, 'f', 1) + tr(" days"));
                } else {
                    ui->avgPaymentTimeLabel->setText(tr("Average Payment Time: ") +tr("N/A"));
                }
            } else { ui->avgPaymentTimeLabel->setText("Calc Err"); }
        } else {
            qWarning() << "Avg Payment Time query failed:" << query.lastError().text();
            ui->avgPaymentTimeLabel->setText("DB Err");
        }
        qDebug() << "Avg Payment Time Calculated (days):" << avgDays;
    } // End query scope


    // --- 5. Financial Health ---
    QString healthStatus = tr("N/A");
    if (totalDue >= 0 && totalOverdue >= 0) {
        if (totalOverdue == 0.0) {
            healthStatus = tr("Good");
        } else if (totalDue > 0 && (totalOverdue / totalDue) > 0.25) {
            healthStatus = tr("Warning");
        } else if (totalDue > 0 && (totalOverdue / totalDue) > 0.50) {
            healthStatus = tr("Poor");
        }
        else {
            healthStatus = tr("Okay");
        }
    } else {
        healthStatus = tr("Unknown");
    }
    ui->financialHealthLabel->setText(tr("Finance Health: ") +healthStatus);
    qDebug() << "Financial Health Status:" << healthStatus;

    qDebug() << "--- Finished Updating Summary Labels ---";
}
void InvoiceManagementWidget::on_markAsPaidButton_clicked()
{
    qDebug() << "Mark As Paid button clicked.";
    int invoiceId = getSelectedInvoiceId();
    if (invoiceId <= 0) {
        QMessageBox::warning(this, tr("No Selection"), tr("Please select an invoice first."));
        return;
    }

    // Get current status and number for messages (handle potential column changes if needed)
    QString invoiceNumber = "N/A";
    QString currentStatus = "N/A";
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        int row = selectedRows.first().row();
        // Find columns by header name for robustness
        int numberCol = -1, statusCol = -1;
        for (int c = 0; c < model->columnCount(); ++c) {
            QString header = model->headerData(c, Qt::Horizontal).toString();
            if (header.compare(tr("Invoice Number"), Qt::CaseInsensitive) == 0) numberCol = c;
            else if (header.compare(tr("Status"), Qt::CaseInsensitive) == 0) statusCol = c;
        }
        if (numberCol != -1) invoiceNumber = model->data(model->index(row, numberCol)).toString();
        if (statusCol != -1) currentStatus = model->data(model->index(row, statusCol)).toString();
    }

    if (currentStatus.compare("paid", Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, tr("Already Paid"), tr("Invoice '%1' is already marked as paid.").arg(invoiceNumber));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Confirm Payment"),
                                  tr("Do you really want to mark invoice '%1' as paid?").arg(invoiceNumber),
                                  QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        bool updateSuccess = Invoices::markAsPaidStatic(invoiceId); // Uses ID only
        if (updateSuccess) {
            QMessageBox::information(this, tr("Success"), tr("Invoice '%1' successfully marked as paid.").arg(invoiceNumber));
            refreshInvoiceList();
        } else {
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


void InvoiceManagementWidget::on_payInvoiceButton_clicked()
{
    qDebug() << "Pay Invoice button clicked.";

    // --- Checks at the start (Keep these as they are good) ---
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();
    int invoiceId = -1;
    QString selectedStatus = "";
    bool canProceed = false;
    int selectedRow = -1; // Store the selected row index

    // 1. Check selection validity
    if (selectionModel && model && selectionModel->hasSelection() && !selectionModel->selectedRows().isEmpty())
    {
        if (selectionModel->selectedRows().count() == 1) {
            QModelIndex selectedIndex = selectionModel->selectedRows().first();
            selectedRow = selectedIndex.row(); // Store the row index

            // Get Invoice ID (assuming column 0 is ID)
            invoiceId = model->data(model->index(selectedRow, 0)).toInt();

            // Get Status (find column robustly)
            int statusCol = -1;
            for (int c = 0; c < model->columnCount(); ++c) {
                // Use case-insensitive compare for robustness
                if (model->headerData(c, Qt::Horizontal).toString().compare(tr("Status"), Qt::CaseInsensitive) == 0) {
                    statusCol = c;
                    break;
                }
            }

            if (statusCol != -1 && invoiceId > 0) {
                selectedStatus = model->data(model->index(selectedRow, statusCol)).toString().toLower();
                // 2. Check if status allows payment
                bool isPayableStatus = (selectedStatus == "unpaid" ||
                                        selectedStatus == "overdue" ||
                                        selectedStatus == "sent" ||
                                        selectedStatus == "pending_bank_transfer" || // Allow paying again if pending? Decide your logic.
                                        selectedStatus == "pending_paypal");        // Allow paying again if pending? Decide your logic.


                if (isPayableStatus) {
                    canProceed = true; // All checks passed
                } else {
                    QString reason;
                    if (selectedStatus == "paid") reason = tr("Invoice is already marked as paid.");
                    else if (selectedStatus == "draft") reason = tr("Invoice is a draft. Please send it first.");
                    else if (selectedStatus == "cancelled") reason = tr("Invoice has been cancelled and cannot be paid.");
                    else reason = tr("Invoice status ('%1') does not allow payment at this time.").arg(selectedStatus);
                    QMessageBox::warning(this, tr("Cannot Pay Invoice"), reason);
                }
            } else {
                if (invoiceId <= 0) QMessageBox::warning(this, tr("Cannot Pay Invoice"), tr("Could not retrieve a valid ID for the selected invoice."));
                else QMessageBox::warning(this, tr("Cannot Pay Invoice"), tr("Could not determine the status of the selected invoice (Status column not found?)."));
            }
        } else { // More than 1 row selected
            QMessageBox::warning(this, tr("Cannot Pay Invoice"), tr("Please select only one invoice to pay."));
        }
    } else { // No selection or model invalid
        if (!selectionModel || !model) QMessageBox::warning(this, tr("Cannot Pay Invoice"), tr("Table data is not available."));
        else QMessageBox::warning(this, tr("Cannot Pay Invoice"), tr("Please select an invoice first."));
    }

    // --- Proceed only if all checks passed ---
    if (!canProceed || selectedRow < 0) { // Also check if selectedRow was actually set
        qDebug() << "Payment process aborted due to failed checks or invalid row.";
        return; // Stop execution here
    }

    qDebug() << "Proceeding to open payment dialog for Invoice ID:" << invoiceId << "at row:" << selectedRow;

    // --- Retrieve Invoice Details needed for Payment Widget ---
    QString invoiceNumber, amountDueStr, clientName;
    // Define column indices based on your `loadInvoices` SELECT statement order
    // SELECT ID(0), Num(1), Client(2), Issue(3), Due(4), Amount(5), Status(6)
    const int numCol = 1, clientCol = 2, issueCol = 3, dueCol = 4, amountCol = 5;

    invoiceNumber = model->data(model->index(selectedRow, numCol)).toString();
    clientName = model->data(model->index(selectedRow, clientCol)).toString();

    // --- Retrieve and Format Amount ---
    double amountDue = model->data(model->index(selectedRow, amountCol)).toDouble();
    // Use system locale for currency formatting (consider setting a specific locale if needed)
    amountDueStr = QLocale().toCurrencyString(amountDue); // Example: "$1,234.56" or "€1.234,56"

    // --- Retrieve Date Variants ---
    QVariant issueVar = model->data(model->index(selectedRow, issueCol));
    QVariant dueVar = model->data(model->index(selectedRow, dueCol));

    // ***** FIX: Format Dates for Display *****
    QString issueDateStr_Display = "N/A"; // Default if invalid
    QString dueDateStr_Display = "N/A";   // Default if invalid

    // Choose your desired display format:
    QString displayFormat = "yyyy-MM-dd";  // Example: 2025-04-26
    // QString displayFormat = "dd/MM/yyyy"; // Example: 26/04/2025
    // QString displayFormat = QLocale().dateFormat(QLocale::ShortFormat); // Use system setting

    QDateTime issueDateTime = issueVar.toDateTime();
    if (issueDateTime.isValid()) {
        issueDateStr_Display = issueDateTime.toString(displayFormat);
    }

    QDateTime dueDateTime = dueVar.toDateTime();
    if (dueDateTime.isValid()) {
        dueDateStr_Display = dueDateTime.toString(displayFormat);
    }
    // ***** END FIX *****


    qDebug() << "Preparing Payment Widget for Invoice ID:" << invoiceId
             << " Num:" << invoiceNumber << " Amount:" << amountDueStr
             << " Issue (Display):" << issueDateStr_Display // Log the formatted string
             << " Due (Display):" << dueDateStr_Display     // Log the formatted string
             << " Client:" << clientName;

    // --- Create and Show the Payment Widget ---
    ClientPaymentWidget paymentDialog(this); // Pass parent
    paymentDialog.setWelcomeMessage(clientName);
    // Pass the *formatted* date strings to the payment dialog
    paymentDialog.setInvoiceDetails(invoiceNumber, amountDueStr, issueDateStr_Display, dueDateStr_Display);

    int result = paymentDialog.exec(); // Show dialog modally

    // --- Handle Payment Result ---
    // The payment dialog calls accept() if payment process completed (even if just instructions given)
    if (result == QDialog::Accepted) {
        qDebug() << "Payment dialog accepted for invoice" << invoiceNumber << ". Refreshing list to show status updates.";
        // Don't show generic "Payment Initiated" here - the dialog itself gives more specific feedback.
        // Simply refresh the list to reflect potential status changes made by the dialog.
        refreshInvoiceList(); // Reload data in the table view
    } else {
        qDebug() << "Payment dialog rejected or cancelled for invoice" << invoiceNumber;
        // No action needed usually if user cancels
    }
}



// --- Must exist in invoicemanagementwidget.cpp ---

void InvoiceManagementWidget::setupReminderTimer() {
    // ... (timer creation and connection) ...

    // --- Configure Timer Interval ---
    // int checkIntervalMs = 60 * 60 * 1000; // 1 hour (Normal)
   // int checkIntervalMs = 20 * 1000; // 20 seconds FOR TESTING <--- CHANGE THIS
   // qDebug() << "Setting up reminder timer with interval (ms):" << checkIntervalMs;

    //reminderTimer->start(checkIntervalMs);
    qDebug() << "Reminder timer started.";
}

bool InvoiceManagementWidget::sendReminderEmail(const QString &recipientEmail, const QString &clientName,
                                                const QString &invoiceNumber, const QDate &dueDate, double amount,
                                                const QString &reminderType)
{
    qDebug() << "Attempting to send REAL reminder email via PowerShell. Type:" << reminderType << "To:" << recipientEmail << "Invoice:" << invoiceNumber;
/*
// --- Platform Specific Implementation ---
#ifdef Q_OS_WIN // --- BEGIN WINDOWS POWERSHELL IMPLEMENTATION ---

    // --------------------------------------------------------------------
    // >> Configuration - !! REPLACE THESE PLACEHOLDERS !! <<
    // --------------------------------------------------------------------
    // IMPORTANT: Use an App Password if your provider requires it (Gmail, Outlook, etc.)
    // Consider loading these from a config file instead of hardcoding for security.
    QString senderAddress = "hassinerahma7@gmail.com"; // Your full email address used for sending
    QString smtpServer    = "smtp.example.com";               // e.g., smtp.gmail.com, smtp.office365.com
    int     smtpPort      = 587;                              // Common TLS port (587) or SSL (465) or unencrypted (25 - not recommended)
    QString smtpUser      = "hassinerahma7@gmail.com"; // Username for SMTP authentication (often same as senderAddress)
    QString smtpPassword  = "hassine112003";  // !! USE APP PASSWORD IF NEEDED !!
    bool useSsl = true;                                       // true for ports 587/465, false for 25 typically
    // --------------------------------------------------------------------

    // --- Validate Essential Config ---
    if (senderAddress.isEmpty() || smtpServer.isEmpty() || smtpUser.isEmpty() || smtpPassword.isEmpty() || recipientEmail.isEmpty() || !recipientEmail.contains('@')) {
        qWarning() << "Email configuration or recipient email is invalid. Aborting send.";
        qWarning() << "Sender:" << senderAddress << "Server:" << smtpServer << "User:" << smtpUser << "Recipient:" << recipientEmail;
        return false; // Indicate failure
    }

    // --- Construct Email Content based on Type ---
    QString subject;
    QString body;
    // Use system locale for formatting date and currency. Adjust locale if needed.
    QLocale systemLocale = QLocale::system();
    QString formattedDueDate = systemLocale.toString(dueDate, QLocale::LongFormat); // Format date nicely (e.g., "April 26, 2024")
    QString formattedAmount = systemLocale.toCurrencyString(amount);                 // Format currency (e.g., "$123.45", "€123,45")
    QString companyName = "Your Smart Consulting Office"; // Set your company name

    if (reminderType == "pre-due") {
        subject = QString("Invoice Due Soon Reminder: #%1").arg(invoiceNumber);
        body = QString("Dear %1,\n\n"
                       "This is a friendly reminder that invoice %2 for %3 is due on %4.\n\n"
                       "Please ensure payment is made on time.\n\n"
                       "Thank you,\n"
                       "%5") // Use company name variable
                   .arg(clientName.isEmpty() ? "Valued Client" : clientName) // Use client name, fallback if empty
                   .arg(invoiceNumber)
                   .arg(formattedAmount)
                   .arg(formattedDueDate)
                   .arg(companyName);
    } else if (reminderType == "overdue") {
        subject = QString("ACTION REQUIRED: Overdue Invoice #%1").arg(invoiceNumber);
        body = QString("Dear %1,\n\n"
                       "Our records indicate that invoice %2 for %3, which was due on %4, is now overdue.\n\n"
                       "Prompt payment is required. Please settle this invoice at your earliest convenience.\n\n"
                       "If you have already made the payment, please disregard this notice and accept our apologies.\n\n"
                       "Regards,\n"
                       "%5") // Use company name variable
                   .arg(clientName.isEmpty() ? "Valued Client" : clientName) // Use client name, fallback if empty
                   .arg(invoiceNumber)
                   .arg(formattedAmount)
                   .arg(formattedDueDate)
                   .arg(companyName);
    } else {
        qWarning() << "Unknown reminder type passed to sendReminderEmail:" << reminderType;
        return false; // Don't send if type is wrong
    }

    // --- Prepare and Execute PowerShell Command ---

    // Escape strings that might contain single quotes for PowerShell
    QString escapedPassword = smtpPassword; escapedPassword.replace("'", "''");
    QString escapedSubject = subject;       escapedSubject.replace("'", "''");
    QString escapedBody = body;             escapedBody.replace("'", "''");
    QString escapedSender = senderAddress;  escapedSender.replace("'", "''");
    QString escapedRecipient = recipientEmail; escapedRecipient.replace("'", "''");
    QString escapedUser = smtpUser;         escapedUser.replace("'", "''");


    // Construct the PowerShell command string
    // <<< This is the 'command' variable definition >>>
    QString command = QString(
                          "$SmtpServer = '%1';"
                          "$SmtpPort = %2;"
                          "$Username = '%3';"
                          "$Password = ConvertTo-SecureString '%4' -AsPlainText -Force;"
                          "$Credential = New-Object System.Management.Automation.PSCredential($Username, $Password);"
                          "$Subject = '%5';"
                          "$Body = '%6';"
                          "$From = '%7';"
                          "$To = '%8';"
                          "Send-MailMessage -SmtpServer $SmtpServer -Port $SmtpPort %9 -Credential $Credential -Subject $Subject -Body $Body -From $From -To $To -BodyAsHtml:$false;" // Send as plain text
                          )
                          .arg(smtpServer)                // %1
                          .arg(smtpPort)                  // %2
                          .arg(escapedUser)               // %3
                          .arg(escapedPassword)           // %4
                          .arg(escapedSubject)            // %5
                          .arg(escapedBody)               // %6
                          .arg(escapedSender)             // %7
                          .arg(escapedRecipient)          // %8
                          .arg(useSsl ? "-UseSsl" : "");  // %9 - Add -UseSsl flag conditionally

    // Declare the QProcess object
    // <<< This is the 'process' variable declaration >>>
    QProcess process;

    // Prepare arguments for powershell.exe
    QStringList args;
    // <<< This uses the 'command' variable >>>
    args << "-ExecutionPolicy" << "Bypass" << "-NoProfile" << "-Command" << command;

    qDebug() << "Starting PowerShell process for" << reminderType << "reminder...";
    // Optional: Log the full command for debugging (be careful with passwords in logs)
    // qDebug() << "Executing PowerShell command:" << command; // UNCOMMENT WITH CAUTION

    process.start("powershell.exe", args);

    // Wait for the process to finish (e.g., 30 seconds timeout)
    if (!process.waitForFinished(30000)) {
        qWarning() << "PowerShell Send-MailMessage timed out for" << reminderType << "reminder.";
        process.kill(); // Terminate the process if it times out
        return false; // Indicate failure
    }

    // Get the results from the process
    // <<< This uses the 'exitCode' variable >>>
    int exitCode = process.exitCode();
    QByteArray stdErr = process.readAllStandardError();
    QByteArray stdOut = process.readAllStandardOutput();

    // Check if the command executed successfully
    // <<< This uses exitCode and stdErr >>>
    if (exitCode == 0 && stdErr.isEmpty()) {
        qDebug() << "PowerShell Send-MailMessage completed successfully for" << reminderType << "reminder.";
        return true; // <<< Return true on success
    } else {
        qWarning() << "PowerShell Send-MailMessage failed for" << reminderType << "reminder. Exit code:" << exitCode;
        // Print Standard Error and Standard Output for detailed debugging
        qWarning() << "Stderr:" << QString::fromUtf8(stdErr); // Decode from UTF-8 for readability
        qWarning() << "Stdout:" << QString::fromUtf8(stdOut); // Decode from UTF-8 for readability
        return false; // <<< Return false on failure
    }

#else // --- BEGIN Non-Windows Section ---
    // Code for platforms other than Windows
    qWarning() << "Email sending via PowerShell is Windows-specific. Skipping send.";
    return false; // Indicate failure as email cannot be sent
#endif // --- END Platform Specific Blocks ---
*/
}
// The checkAndSendReminders slot implementation you already provided looks okay.

// --- New Slot: Check and Send Reminders ---
void InvoiceManagementWidget::checkAndSendReminders() {
    qDebug() << "--- Running scheduled reminder check ---" << QDateTime::currentDateTime();

  /*  QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Reminder check skipped: Database not open.";
        return;
    }

    int reminderDaysBefore = 3; // How many days before due date to send pre-due reminder
    int remindersSentThisRun = 0;

    // --- Scenario 1: Check for Pre-Due Reminders ---
    qDebug() << "Checking for PRE-DUE reminders...";
    { // Scope for pre-due query
        QSqlQuery preDueQuery(db);
        // Find invoices:
        // - Status allows reminding ('sent', 'unpaid')
        // - Due date is approaching (today up to 'reminderDaysBefore' days from now)
        // - Pre-due reminder has NOT been sent yet
        QString preDueSql =
            "SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
            "       c.EMAIL, c.FIRST_NAME, c.LAST_NAME "
            "FROM INVOICES i "
            "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
            "WHERE i.STATUS IN ('sent', 'unpaid') "           // Eligible statuses
            "  AND TRUNC(i.DUE_DATE) >= TRUNC(SYSDATE) "       // Due date is today or later
            "  AND TRUNC(i.DUE_DATE) <= TRUNC(SYSDATE) + :reminderDays " // Due within N days
            "  AND i.PRE_DUE_REMINDER_SENT_DATE IS NULL";     // Pre-due reminder not sent

        preDueQuery.prepare(preDueSql);
        preDueQuery.bindValue(":reminderDays", reminderDaysBefore);

        if (!preDueQuery.exec()) {
            qWarning() << "Failed to query for PRE-DUE reminders:" << preDueQuery.lastError().text();
        } else {
            while (preDueQuery.next()) {
                int invoiceId = preDueQuery.value(0).toInt();
                QString invoiceNumber = preDueQuery.value(1).toString();
                QDateTime dueDateTime = preDueQuery.value(2).toDateTime();
                double totalAmount = preDueQuery.value(3).toDouble();
                QString clientEmail = preDueQuery.value(4).toString();
                QString clientFirstName = preDueQuery.value(5).toString();
                QString clientLastName = preDueQuery.value(6).toString();
                QString clientFullName = (clientFirstName + " " + clientLastName).trimmed();

                qDebug() << " -> Found PRE-DUE candidate: ID" << invoiceId << "Num:" << invoiceNumber << "Client:" << clientFullName << "Email:" << clientEmail;

                if (clientEmail.isEmpty() || !clientEmail.contains('@')) {
                    qWarning() << "  -> Skipping PRE-DUE reminder for Invoice ID" << invoiceId << "- Invalid/missing email:" << clientEmail;
                    continue;
                }

                // Attempt to send the specific "Pre-Due" email
                bool emailSuccess = sendReminderEmail(clientEmail, clientFullName, invoiceNumber, dueDateTime.date(), totalAmount, "pre-due"); // Pass type

                if (emailSuccess) {
                    remindersSentThisRun++;
                    // Update ONLY the PRE_DUE reminder date in the database
                    QSqlQuery updateQuery(db);
                    updateQuery.prepare("UPDATE INVOICES SET PRE_DUE_REMINDER_SENT_DATE = SYSDATE WHERE INVOICE_ID = :id");
                    updateQuery.bindValue(":id", invoiceId);
                    if (!updateQuery.exec()) {
                        qWarning() << "  -> Failed to update PRE_DUE_REMINDER_SENT_DATE for Invoice ID" << invoiceId << ":" << updateQuery.lastError().text();
                    } else {
                        qDebug() << "  -> Successfully marked PRE-DUE reminder sent for Invoice ID" << invoiceId;
                    }
                } else {
                    qWarning() << "  -> Failed to send PRE-DUE reminder email for Invoice ID" << invoiceId;
                }
            } // end while preDueQuery.next()
        } // end else preDueQuery executed ok
    } // end scope for pre-due query

    // --- Scenario 2: Check for Overdue Reminders ---
    qDebug() << "Checking for OVERDUE reminders...";
    { // Scope for overdue query
        QSqlQuery overdueQuery(db);
        // Find invoices:
        // - Status indicates it might be unpaid ('sent', 'unpaid', 'overdue')
        // - Due date is IN THE PAST
        // - Overdue reminder has NOT been sent yet
        QString overdueSql =
            "SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
            "       c.EMAIL, c.FIRST_NAME, c.LAST_NAME "
            "FROM INVOICES i "
            "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
            "WHERE i.STATUS IN ('sent', 'unpaid', 'overdue') " // Eligible statuses
            "  AND TRUNC(i.DUE_DATE) < TRUNC(SYSDATE) "         // Due date is before today
            "  AND i.OVERDUE_REMINDER_SENT_DATE IS NULL";     // Overdue reminder not sent

        overdueQuery.prepare(overdueSql);
        // No parameters to bind for this specific query

        if (!overdueQuery.exec()) {
            qWarning() << "Failed to query for OVERDUE reminders:" << overdueQuery.lastError().text();
        } else {
            while (overdueQuery.next()) {
                int invoiceId = overdueQuery.value(0).toInt();
                QString invoiceNumber = overdueQuery.value(1).toString();
                QDateTime dueDateTime = overdueQuery.value(2).toDateTime();
                double totalAmount = overdueQuery.value(3).toDouble();
                QString clientEmail = overdueQuery.value(4).toString();
                QString clientFirstName = overdueQuery.value(5).toString();
                QString clientLastName = overdueQuery.value(6).toString();
                QString clientFullName = (clientFirstName + " " + clientLastName).trimmed();

                qDebug() << " -> Found OVERDUE candidate: ID" << invoiceId << "Num:" << invoiceNumber << "Client:" << clientFullName << "Email:" << clientEmail;

                if (clientEmail.isEmpty() || !clientEmail.contains('@')) {
                    qWarning() << "  -> Skipping OVERDUE reminder for Invoice ID" << invoiceId << "- Invalid/missing email:" << clientEmail;
                    continue;
                }

                // Attempt to send the specific "Overdue" email
                bool emailSuccess = sendReminderEmail(clientEmail, clientFullName, invoiceNumber, dueDateTime.date(), totalAmount, "overdue"); // Pass type

                if (emailSuccess) {
                    remindersSentThisRun++;
                    // Update ONLY the OVERDUE reminder date in the database
                    QSqlQuery updateQuery(db);
                    updateQuery.prepare("UPDATE INVOICES SET OVERDUE_REMINDER_SENT_DATE = SYSDATE WHERE INVOICE_ID = :id");
                    updateQuery.bindValue(":id", invoiceId);
                    if (!updateQuery.exec()) {
                        qWarning() << "  -> Failed to update OVERDUE_REMINDER_SENT_DATE for Invoice ID" << invoiceId << ":" << updateQuery.lastError().text();
                    } else {
                        qDebug() << "  -> Successfully marked OVERDUE reminder sent for Invoice ID" << invoiceId;
                    }
                } else {
                    qWarning() << "  -> Failed to send OVERDUE reminder email for Invoice ID" << invoiceId;
                }
            } // end while overdueQuery.next()
        } // end else overdueQuery executed ok
    } // end scope for overdue query


    // --- Final Summary Log ---
    if (remindersSentThisRun > 0) {
        qDebug() << "Reminder check finished. Sent" << remindersSentThisRun << "total reminders (pre-due + overdue).";
    } else {
        qDebug() << "Reminder check finished. No new reminders needed at this time.";
    }*/
    qDebug() << "--- End scheduled reminder check ---";
}

