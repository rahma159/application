#include "invoicemanagementwidget.h"
#include "ui_invoicemanagementwidget.h"
#include "createeditinvoicedialog.h" // Include the dialog header
#include "deleteinvoicedialog.h"
#include "statisticsdialog.h"
#include "settingsdialog.h"
#include "clientpaymentwidget.h"
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

#include <stdexcept>
#include <cmath>   // For isnan, isinf
#include <limits>  // For infinity
#include <QMapIterator>
#include <QString>
#include <QTimeZone>
#include <QToolButton>
#include <QMenu>


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


// --- Add this new Delegate Class Definition ---
class StatusEmojiDelegate : public QStyledItemDelegate
{
public:
    explicit StatusEmojiDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        qDebug() << "StatusEmojiDelegate created.";
    }

    // Override the function that controls the display text
    QString displayText(const QVariant &value, const QLocale &locale) const override
    {
        Q_UNUSED(locale); // Locale not used here for simple emoji prepending

        QString status = value.toString(); // Get the raw status text from the model
        QString emoji;

        // Determine emoji based on status (case-insensitive comparison is safer)
        if (status.compare("paid", Qt::CaseInsensitive) == 0) {
            emoji = "✅ ";
        } else if (status.compare("unpaid", Qt::CaseInsensitive) == 0) {
            emoji = "🟡 ";
        } else if (status.compare("overdue", Qt::CaseInsensitive) == 0) {
            emoji = "⏰ ";
        } else if (status.compare("draft", Qt::CaseInsensitive) == 0) {
            emoji = "📝 ";
        } else if (status.compare("sent", Qt::CaseInsensitive) == 0) {
            emoji = "📤 ";
        } else if (status.compare("cancelled", Qt::CaseInsensitive) == 0) {
            emoji = "❌ ";
        } else {
            // Optional: Handle unknown statuses or just return the original text
            qWarning() << "StatusEmojiDelegate: Unknown status received:" << status;
            return status; // Return original status if unknown
        }

        // Return the emoji followed by the original status text
        return emoji + status;
    }
};
// --- End of StatusEmojiDelegate Class Definition ---



InvoiceManagementWidget::InvoiceManagementWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvoiceManagementWidget),
    model(nullptr),
    // --- MATCH THIS ORDER TO YOUR .h FILE ---
    m_currentFilterClause(""),        // Line 58?
    reminderTimer(nullptr),           // Line 59? (Must come before m_sortOrder)
    m_currentOrderByClause("ORDER BY i.ISSUE_DATE DESC, i.INVOICE_ID DESC"), // Line 61? (Must come before m_sortColumn)
    m_sortColumn(3),                  // Line 62?
    m_sortOrder(Qt::DescendingOrder),
    m_emailService(new EmailService(this))


                                     // Initialized fifth?
// --- END REORDER ---
{
    // ** Step 1: UI Setup - MUST BE CALLED FIRST **
    ui->setupUi(this);

    // In InvoiceManagementWidget constructor
    QTimer::singleShot(3000, this, [this]() {
        qDebug() << "=== MANUAL REMINDER TRIGGER ===";
        checkAndSendReminders(); // Calls the real reminder logic
    });


    setupActionsMenu();
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
    QTimer *reminderTimer = new QTimer(this);
    connect(reminderTimer, &QTimer::timeout, this, &InvoiceManagementWidget::checkAndSendReminders);
   // reminderTimer->start(24 * 60 * 60 * 1000); // Check daily
    reminderTimer->start(60 * 1000);

    if (!m_emailService->isConfigured()) {
        qWarning() << "Email service is not properly configured! Reminders will not work.";
    }
    // Initial check
    checkAndSendReminders();
}


void InvoiceManagementWidget::setupActionsMenu()
{
    QToolButton *actionsBtn = new QToolButton(this);
    actionsBtn->setText(tr("Actions ▼"));
    actionsBtn->setIcon(QIcon(":/icons/menu.png")); // Add your menu icon
    actionsBtn->setIconSize(QSize(16, 16));
    actionsBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    actionsBtn->setPopupMode(QToolButton::InstantPopup);
    actionsBtn->setObjectName("actionsButton");

    // Create the dropdown menu
    QMenu *actionsMenu = new QMenu(this);


    m_newInvoiceAction = new QAction(QIcon(":/icons/add.png"), tr("➕New Invoice"), this);
    m_editInvoiceAction = new QAction(QIcon(":/icons/edit.png"), tr("✏️Edit Invoice"), this);
    m_deleteInvoiceAction = new QAction(QIcon(":/icons/delete.png"), tr("🗑️Delete Invoice"), this);
    m_payInvoiceAction = new QAction(QIcon(":/icons/payment.png"), tr("💳Pay Invoice"), this);
    m_sendInvoiceAction = new QAction(QIcon(":/icons/send.png"), tr("✉️Send Invoice"), this);
    m_markPaidAction = new QAction(QIcon(":/icons/check.png"), tr("✅Mark As Paid"), this);

    // Add actions to menu
    actionsMenu->addAction(m_newInvoiceAction);
    actionsMenu->addAction(m_editInvoiceAction);
    actionsMenu->addAction(m_deleteInvoiceAction);
    actionsMenu->addSeparator();
    actionsMenu->addAction(m_payInvoiceAction);
    actionsMenu->addAction(m_sendInvoiceAction);
    actionsMenu->addAction(m_markPaidAction);
    actionsMenu->addSeparator();

    connect(m_newInvoiceAction, &QAction::triggered, this, &InvoiceManagementWidget::on_newInvoiceButton_clicked);
    connect(m_editInvoiceAction, &QAction::triggered, this, &InvoiceManagementWidget::on_editInvoiceButton_clicked);
    connect(m_deleteInvoiceAction, &QAction::triggered, this, &InvoiceManagementWidget::on_deleteInvoiceButton_clicked);
    connect(m_payInvoiceAction, &QAction::triggered, this, &InvoiceManagementWidget::on_payInvoiceButton_clicked);
    connect(m_sendInvoiceAction, &QAction::triggered, this, &InvoiceManagementWidget::on_sendInvoiceButton_clicked);
    connect(m_markPaidAction, &QAction::triggered, this, &InvoiceManagementWidget::on_markAsPaidButton_clicked);

    // Set initial enabled states

    actionsBtn->setMenu(actionsMenu);
    m_editInvoiceAction->setEnabled(false);
    m_deleteInvoiceAction->setEnabled(false);

    ui->horizontalLayout->insertWidget(0, actionsBtn);

    // Apply styling
    actionsBtn->setStyleSheet(R"(
        QToolButton {
            padding: 6px 12px;
            border: 1px solid #d0d0d0;
            border-radius: 4px;
            background-color: #f8f8f8;
            color: #333;
            font-weight: normal;
        }
        QToolButton:hover {
            background-color: #e8e8e8;
            border-color: #c0c0c0;
        }
        QToolButton:pressed {
            background-color: #d8d8d8;
        }
        QToolButton::menu-indicator {
            image: none;
            width: 0;
        }
    )");

    actionsMenu->setStyleSheet(R"(
        QMenu {
            background-color: white;
            border: 1px solid #d0d0d0;
            padding: 4px;
        }
        QMenu::item {
            padding: 6px 24px 6px 12px;
        }
        QMenu::item:selected {
            background-color: #e0e0e0;
        }
        QMenu::separator {
            height: 1px;
            background: #e0e0e0;
            margin: 4px 0;
        }
    )");
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
    on_tableView_selectionChanged(QItemSelection(), QItemSelection());
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
    connect(ui->manualTestButton, &QPushButton::clicked,
            this, &InvoiceManagementWidget::manualTestReminder);
    /*connect(ui->exportInvoiceListPdfButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_exportInvoiceListPdfButton_clicked);
    connect(ui->exportFecButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_exportFecButton_clicked);
    connect(ui->viewStatisticsButton, &QPushButton::clicked, this, &InvoiceManagementWidget::on_viewStatisticsButton_clicked);

*/

    QPushButton *forceReminderBtn = new QPushButton("Force Send Reminders", this);
    connect(forceReminderBtn, &QPushButton::clicked, this, &InvoiceManagementWidget::forceSendTestReminders);

    ui->verticalLayout->addWidget(forceReminderBtn);
}

void InvoiceManagementWidget::on_viewStatisticsButton_clicked()
{
    qDebug() << "View Statistics button clicked.";

    // Collect invoice status data
    QMap<QString, int> statusData;
    QMap<QString, double> amountData;

    // Get data from the model
    if (model) {
        for (int row = 0; row < model->rowCount(); ++row) {
            // Get status (assuming status is column 6)
            QString status = model->data(model->index(row, 6)).toString();
            statusData[status] = statusData.value(status, 0) + 1;

            // Get amount (assuming amount is column 5)
            double amount = model->data(model->index(row, 5)).toDouble();

            // Group amounts by month (or another category)
            QDateTime issueDate = model->data(model->index(row, 3)).toDateTime();
            QString monthYear = issueDate.toString("MMM yyyy");
            amountData[monthYear] = amountData.value(monthYear, 0.0) + amount;
        }
    }

    // Create and show the dialog with real data
    StatisticsDialog statsDialog(statusData, amountData, this);
    statsDialog.exec();
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

        // Apply Date Delegate (Existing code)
        InlineDateDelegate *dateDelegate = new InlineDateDelegate(ui->tableView);
        ui->tableView->setItemDelegateForColumn(3, dateDelegate); // Issue Date at index 3
        ui->tableView->setItemDelegateForColumn(4, dateDelegate); // Due Date at index 4

        // ***** ADD THIS SECTION *****
        // Apply Status Emoji Delegate
        StatusEmojiDelegate *statusDelegate = new StatusEmojiDelegate(ui->tableView);
        // Set it for the Status column (index 6 based on your SELECT query)
        ui->tableView->setItemDelegateForColumn(6, statusDelegate);
        qDebug() << "Applied StatusEmojiDelegate to column 6.";
        // ***** END OF ADDED SECTION *****

        // Table View Setup
        ui->tableView->setColumnHidden(0, true);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

        // ... (rest of existing code: clearSelection, on_tableView_selectionChanged) ...
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


    // --- Attempt 1: Use selectedIndexes() count ---
    // Sometimes more reliable immediately after model changes than hasSelection()
    bool selectionExists = !selectionModel->selectedIndexes().isEmpty();
    qDebug() << "Check 1: selectedIndexes().isEmpty() is" << !selectionExists;


    // --- Attempt 2: Check selectedRows() count (what you were using) ---
    // Let's log its count directly
    int selectedRowCount = selectionModel->selectedRows().count();
    qDebug() << "Check 2: selectedRows().count() is" << selectedRowCount;

    bool enableButtons = ui->tableView->selectionModel()->hasSelection();

    // Enable/disable menu actions
    if (m_editInvoiceAction) m_editInvoiceAction->setEnabled(enableButtons);
    if (m_deleteInvoiceAction) m_deleteInvoiceAction->setEnabled(enableButtons);
    qDebug() << "Selection changed - actions enabled:" << enableButtons;
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
    // Your existing payment marking logic
    if (Invoices::markAsPaidStatic(invoiceId)) {
        sendPaymentVerification(invoiceId); // Send verification email
        refreshInvoiceList();
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
    if (!m_emailService) {
        qWarning() << "Email service not initialized";
        return false;
    }
    QString subject;
    QString body = m_emailService->generateReminderContent(
        (reminderType == "overdue") ? EmailService::OverdueReminder :
            (reminderType == "due") ? EmailService::DueDateReminder : EmailService::PreDueReminder,
        clientName,
        invoiceNumber,
        dueDate,
        amount
        );

    if (reminderType == "overdue") {
        subject = QString("Overdue Invoice #%1").arg(invoiceNumber);
    } else if (reminderType == "due") {
        subject = QString("Payment Due Today for Invoice #%1").arg(invoiceNumber);
    } else {
        subject = QString("Upcoming Payment for Invoice #%1").arg(invoiceNumber);
    }

    return m_emailService->sendEmail(recipientEmail, subject, body);
}

void InvoiceManagementWidget::checkAndSendReminders()
{
    if (!m_emailService || !m_emailService->isConfigured()) {
        qDebug() << "Email service not configured - skipping reminder check";
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database not open for reminder check";
        return;
    }

    QDate today = QDate::currentDate();
    qDebug() << "Starting reminder check for date:" << today;

    // 1. Pre-due reminders (3 days before due date)
    checkPreDueReminders(db, today);

    // 2. Due date reminders
    checkDueDateReminders(db, today);

    // 3. Overdue reminders
    checkOverdueReminders(db, today);

    qDebug() << "Reminder check completed for date:" << today;
}

void InvoiceManagementWidget::checkPreDueReminders(QSqlDatabase& db, const QDate& today) {
    int daysBeforeDue = SettingsDialog::getSettingInt("InvoiceOptions/RemindersBeforeDue", 5);
    QDate reminderDate = today.addDays(daysBeforeDue);

    qDebug() << "Pre-due check: Today =" << today
             << "| ReminderDate =" << reminderDate
             << "| DaysBeforeDue =" << daysBeforeDue;

    QSqlQuery query(db);
    query.prepare(
        "SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
        "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
        "FROM INVOICES i "
        "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        "WHERE i.STATUS IN ('sent', 'unpaid') "
        "AND TRUNC(i.DUE_DATE) = TRUNC(:reminderDate) "
        "AND (i.LAST_REMINDER_DATE IS NULL OR TRUNC(i.LAST_REMINDER_DATE) != TRUNC(:today))"
        );

    query.bindValue(":reminderDate", reminderDate);
    query.bindValue(":today", today);

    if (query.exec()) {
        while (query.next()) {
            QString email = query.value("EMAIL").toString();
            if (email.isEmpty()) continue;

            processReminder(query, EmailService::PreDueReminder, today);
        }
    }
}

void InvoiceManagementWidget::checkDueDateReminders(QSqlDatabase& db, const QDate& today)
{
    QSqlQuery query(db);
    query.prepare(
        "SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
        "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
        "FROM INVOICES i "
        "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        "WHERE i.STATUS IN ('sent', 'unpaid') "
        "AND TRUNC(i.DUE_DATE) = TRUNC(:today) "
        "AND (i.LAST_REMINDER_DATE IS NULL OR TRUNC(i.LAST_REMINDER_DATE) != TRUNC(:today))"
        );
    query.bindValue(":today", today);

    if (query.exec()) {
        while (query.next()) {
            QString email = query.value("EMAIL").toString();
            if (email.isEmpty()) continue;

            processReminder(query, EmailService::DueDateReminder, today);
        }
    }
}

void InvoiceManagementWidget::checkOverdueReminders(QSqlDatabase& db, const QDate& today)
{
    QSqlQuery query(db);
    query.prepare(
        "SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
        "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
        "FROM INVOICES i "
        "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        "WHERE i.STATUS IN ('sent', 'unpaid') "
        "AND TRUNC(i.DUE_DATE) < TRUNC(:today) "
        "AND (i.LAST_REMINDER_DATE IS NULL OR TRUNC(i.LAST_REMINDER_DATE) != TRUNC(:today))"
        );
    query.bindValue(":today", today);

    if (query.exec()) {
        while (query.next()) {
            QString email = query.value("EMAIL").toString();
            if (email.isEmpty()) continue;

            int daysOverdue = query.value("DUE_DATE").toDate().daysTo(today);
            processReminder(query, EmailService::OverdueReminder, today, daysOverdue);
        }
    }
}
// Place this entire function definition within your invoicemanagementwidget.cpp file

void InvoiceManagementWidget::processReminder(QSqlQuery& query, EmailService::ReminderType type,
                                              const QDate& today, int daysOverdue)
{
    // --- 1. Extract Data from Query ---
    int invoiceId = query.value("INVOICE_ID").toInt();
    QString invoiceNumber = query.value("INVOICE_NUMBER").toString();
    QDate dueDate = query.value("DUE_DATE").toDate();
    double amount = query.value("TOTAL_AMOUNT").toDouble();
    QString firstName = query.value("FIRST_NAME").toString();
    QString lastName = query.value("LAST_NAME").toString();
    QString email = query.value("EMAIL").toString(); // Client's email
    QString clientName = QString("%1 %2").arg(firstName, lastName).trimmed();

    qDebug() << "  [ProcessReminder] Processing ID:" << invoiceId << "Type:" << type << "Client:" << clientName << "Email:" << email;

    if (email.isEmpty()) {
        qWarning() << "  [ProcessReminder] Skipping ID:" << invoiceId << "because client email is empty.";
        return; // Cannot send email without an address
    }

    // --- 2. Define Default Subject/Body and Determine Template Key Parts ---
    QString subjectKeyBase = "EmailTemplates/";
    QString bodyKeyBase = "EmailTemplates/";
    const char* templateNameKeyPartCStr; // Use const char* for result of ternary/switch
    QString defaultSubject; // Default subject defined within scope
    QString defaultBody;    // Default body defined within scope

    switch(type) {
    case EmailService::PreDueReminder:
        templateNameKeyPartCStr = "PaymentReminder"; // Key for SettingsDialog
        defaultSubject = QString("Upcoming Payment: Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "This is a friendly reminder that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is due on {invoice_due_date}.\n\n"
                              "Please ensure payment is submitted by the due date.\n\n"
                              "Thank you,\n{company_name}"); // Added company name placeholder
        break;
    case EmailService::DueDateReminder:
        templateNameKeyPartCStr = "OverdueNotice"; // Using Overdue template for Due Date reminder too, adjust if needed
        defaultSubject = QString("Payment Due Today: Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "This is a reminder that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is due today ({invoice_due_date}).\n\n"
                              "Please submit your payment at your earliest convenience.\n\n"
                              "Thank you,\n{company_name}");
        break;
    case EmailService::OverdueReminder:
        templateNameKeyPartCStr = "OverdueNotice"; // Key for SettingsDialog
        defaultSubject = QString("Overdue Payment: Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "Our records indicate that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is overdue by {days_overdue} days (due date: {invoice_due_date}).\n\n"
                              "Please submit payment immediately to avoid any late fees or "
                              "service interruptions.\n\n"
                              "Thank you,\n{company_name}");
        break;
    case EmailService::PaymentVerification:
        templateNameKeyPartCStr = "PaymentConfirmation"; // Key for SettingsDialog
        defaultSubject = QString("Payment Received: Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "We have received your payment of {invoice_total_amount} for invoice #{invoice_number}.\n\n"
                              "Thank you for your prompt payment!\n\n"
                              "Sincerely,\n{company_name}");
        break;
    default:
        templateNameKeyPartCStr = "Unknown"; // Should ideally not happen
        defaultSubject = QString("Notification for Invoice #%1").arg(invoiceNumber);
        defaultBody = "Dear {client_name},\n\nThis is a notification regarding invoice #{invoice_number}.\n\nThank you,\n{company_name}";
        qWarning() << "  [ProcessReminder] Encountered unknown reminder type:" << type << "for Invoice ID:" << invoiceId;
        break;
    }
    // --- End Define Defaults ---

    // --- 3. Construct Full Keys and Fetch Templates from Settings ---
    QString bodySettingKey = (templateNameKeyPartCStr != "Unknown") ? (QString(bodyKeyBase) + templateNameKeyPartCStr + QString("/Body")) : QString();
    QString subjectSettingKey = (templateNameKeyPartCStr != "Unknown") ? (QString(subjectKeyBase) + templateNameKeyPartCStr + QString("/Subject")) : QString();

    qDebug() << "    Using Body Template Key:" << (bodySettingKey.isEmpty() ? "N/A (Using Default)" : bodySettingKey);
    qDebug() << "    Using Subject Template Key:" << (subjectSettingKey.isEmpty() ? "N/A (Using Default)" : subjectSettingKey);

    // Fetch Body from SettingsDialog using the constructed key and the defined defaultBody
    QString fetchedBodyTemplate = defaultBody; // Start with default
    if (!bodySettingKey.isEmpty()) {
        fetchedBodyTemplate = SettingsDialog::getSetting(bodySettingKey, defaultBody);
    }

    // Fetch Subject from SettingsDialog using the constructed key and the defined defaultSubject
    QString actualSubject = defaultSubject; // Start with default
    if (!subjectSettingKey.isEmpty()) {
        actualSubject = SettingsDialog::getSetting(subjectSettingKey, defaultSubject);
    }

    // --- 4. Replace Placeholders ---
    QString companyNameFromSettings = SettingsDialog::getSetting("CompanyInfo/Name", "Our Company"); // Fetch company name once

    // Replace placeholders in Body
    QString finalBody = fetchedBodyTemplate;
    finalBody.replace("{client_name}", clientName, Qt::CaseInsensitive);
    finalBody.replace("{invoice_number}", invoiceNumber, Qt::CaseInsensitive);
    finalBody.replace("{invoice_due_date}", dueDate.isValid() ? dueDate.toString("MMMM d, yyyy") : "N/A", Qt::CaseInsensitive);
    finalBody.replace("{invoice_total_amount}", QLocale().toCurrencyString(amount), Qt::CaseInsensitive); // Format amount as currency
    if (type == EmailService::OverdueReminder) {
        finalBody.replace("{days_overdue}", QString::number(daysOverdue), Qt::CaseInsensitive);
    }
    finalBody.replace("{company_name}", companyNameFromSettings, Qt::CaseInsensitive);
    // Add any other placeholders you might use in the body

    // Replace placeholders in Subject
    actualSubject.replace("{client_name}", clientName, Qt::CaseInsensitive);
    actualSubject.replace("{invoice_number}", invoiceNumber, Qt::CaseInsensitive);
    actualSubject.replace("{company_name}", companyNameFromSettings, Qt::CaseInsensitive);
    // Add any other placeholders you might use in the subject

    qDebug() << "    Final Subject:" << actualSubject;
    // qDebug() << "    Final Body:\n" << finalBody; // Can be verbose, uncomment if needed

    // --- 5. Attempt to Send Email ---
    qDebug() << "    Attempting to send email via EmailService...";
    if (m_emailService->sendEmail(email, actualSubject, finalBody)) {
        qDebug() << "    [ProcessReminder] SUCCESS sending email for Invoice ID" << invoiceId << "(Type:" << type << "). Attempting DB update.";

        // --- 6. Update Database on Success ---
        QSqlQuery updateQuery(QSqlDatabase::database());
        updateQuery.prepare(
            "UPDATE INVOICES SET "
            "  LAST_REMINDER_DATE = :todayDate, " // Use placeholder
            "  REMINDER_COUNT = NVL(REMINDER_COUNT, 0) + 1 " // Safely increment count
            "WHERE INVOICE_ID = :invoiceIdParam" // Use placeholder
            );
        updateQuery.bindValue(":todayDate", today); // Bind QDate directly
        updateQuery.bindValue(":invoiceIdParam", invoiceId);

        if (!updateQuery.exec()) {
            qWarning() << "    [ProcessReminder] FAILED to update reminder info for invoice ID" << invoiceId << ":" << updateQuery.lastError().text();
            // Consider: Should failure to update DB invalidate the operation? Maybe log only.
        } else {
            if (updateQuery.numRowsAffected() > 0) {
                qDebug() << "    [ProcessReminder] Successfully updated reminder info for invoice ID" << invoiceId;
            } else {
                qWarning() << "    [ProcessReminder] DB update executed but no rows affected for invoice ID" << invoiceId << ". Invoice might have been deleted.";
            }
        }

    } else {
        qWarning() << "  [ProcessReminder] FAILED to send reminder email via EmailService for Invoice ID" << invoiceId << "(Type:" << type << ")";
        // Log failure, but typically don't stop processing other reminders
    }

    qDebug() << "  [ProcessReminder] Finished processing ID:" << invoiceId;
} // --- End of processReminder ---
void InvoiceManagementWidget::sendPaymentVerification(int invoiceId)
{
    qDebug() << "[Payment Verify] Checking if verification needed for ID:" << invoiceId;
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "[Payment Verify] DB not open.";
        return;
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT i.INVOICE_NUMBER, i.TOTAL_AMOUNT, "
        "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
        "FROM INVOICES i "
        "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
        "WHERE i.INVOICE_ID = :invoiceId "
        // Check if verification already sent (assuming 0 = not sent, 1 = sent)
        // Make sure PAYMENT_VERIFICATION_SENT column exists and is NUMBER(1,0)
        "AND NVL(i.PAYMENT_VERIFICATION_SENT, 0) = 0"
        );
    query.bindValue(":invoiceId", invoiceId);

    if (query.exec()) {
        if (query.next()) {
            qDebug() << "  [Payment Verify] Found invoice needing verification.";
            QString invoiceNumber = query.value(0).toString();
            double amount = query.value(1).toDouble();
            QString firstName = query.value(2).toString();
            QString lastName = query.value(3).toString();
            QString email = query.value(4).toString();
            QString clientName = QString("%1 %2").arg(firstName, lastName).trimmed();

            // Generate Body
            QString body = m_emailService->generateReminderContent(
                EmailService::PaymentVerification, clientName, invoiceNumber, QDate(), amount); // Pass invalid QDate

            // Generate Subject
            QString subjectSettingKey = "EmailTemplates/PaymentConfirmation/Subject";
            QString defaultSubject = QString("Payment Received for Invoice #%1").arg(invoiceNumber);
            QString actualSubject = SettingsDialog::getSetting(subjectSettingKey, defaultSubject);
            actualSubject.replace("{client_name}", clientName, Qt::CaseInsensitive);
            actualSubject.replace("{invoice_number}", invoiceNumber, Qt::CaseInsensitive);
            actualSubject.replace("{company_name}", SettingsDialog::getSetting("CompanyInfo/Name", "Our Company"), Qt::CaseInsensitive);
            actualSubject.replace("{invoice_total_amount}", QString::number(amount,'f',2), Qt::CaseInsensitive); // Add amount if needed


            qDebug() << "    Attempting to send payment verification email...";
            if (m_emailService->sendEmail(email, actualSubject, body)) {
                qDebug() << "    [Payment Verify] SUCCESS sending email for Invoice ID" << invoiceId << ". Attempting DB update.";
                // Mark as sent
                QSqlQuery updateQuery(db);
                updateQuery.prepare(
                    "UPDATE INVOICES SET PAYMENT_VERIFICATION_SENT = 1 "
                    "WHERE INVOICE_ID = :invoiceIdParam"
                    );
                updateQuery.bindValue(":invoiceIdParam", invoiceId);
                if (!updateQuery.exec()) {
                    qWarning() << "    [Payment Verify] FAILED to update PAYMENT_VERIFICATION_SENT for invoice ID" << invoiceId << ":" << updateQuery.lastError().text();
                } else {
                    qDebug() << "    [Payment Verify] Successfully updated PAYMENT_VERIFICATION_SENT for invoice ID" << invoiceId;
                }
            } else {
                qWarning() << "  [Payment Verify] FAILED to send verification email via EmailService for Invoice ID" << invoiceId;
            }
        } else {
            qDebug() << "  [Payment Verify] No verification needed or invoice not found for ID:" << invoiceId;
        }
    } else {
        qWarning() << "[Payment Verify] Query failed for ID:" << invoiceId << "Error:" << query.lastError().text();
    }
}


// --- Constructors ---
Invoices::Invoices()
    : invoice_id(-1), client_id(-1), issue_date(QDateTime::currentDateTime()),
    due_date(QDateTime::currentDateTime().addDays(30)),
    subtotal(0.0), tax_amount(0.0), total_amount(0.0)
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
    payment_date(payment_date), notes(notes)
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
            "  PAYMENT_DATE, NOTES"
            ") VALUES ("
            "  :invoice_id, :invoice_number, :client_id, :client_name, :issue_date, :due_date, "
            "  :payment_terms, :subtotal, :tax_amount, :total_amount, :status, "
            "  :payment_date, :notes"
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


EmailService::EmailService(QObject *parent) : QObject(parent)
{
    m_smtpServer = SettingsDialog::getSetting("EmailSMTPServer", "smtp.example.com"); // Example key
    // bool okPort; // <<< COMMENT OUT or REMOVE this line
    // Just get the int, default handles non-convertible cases
    m_smtpPort = SettingsDialog::getSettingInt("EmailSMTPPort", 587);
    m_senderEmail = SettingsDialog::getSetting("EmailSenderAddress", "noreply@example.com");
    m_senderPassword = SettingsDialog::getSetting("EmailSenderPassword", "your_password");

    if (m_smtpServer.isEmpty()) m_smtpServer = "hassinerahma@gmail.com"; // Fallback
    if (m_smtpPort == 0) m_smtpPort = 587; // Fallback
    if (m_senderEmail.isEmpty()) m_senderEmail = "hassinerahma@gmail.com"; // Fallback
    if (m_senderPassword.isEmpty()) m_senderPassword = "123"; // Fallback



}
// In EmailService class, add this method:
bool EmailService::isConfigured() const
{
    return !m_smtpServer.isEmpty() &&
           m_smtpPort > 0 &&
           !m_senderEmail.isEmpty() &&
           !m_senderPassword.isEmpty();
}
bool EmailService::sendEmail(const QString &recipient, const QString &subject, const QString &body)
{
    // This is your existing placeholder or actual implementation.
    // If using a library, you'd configure it here with m_smtpServer, m_smtpPort etc.
    qDebug() << "EmailService: Sending email TO:" << recipient << "SUBJ:" << subject;
    qDebug() << "Body:\n" << body;
    qDebug() << "Using SMTP Server:" << m_smtpServer << "Port:" << m_smtpPort << "From:" << m_senderEmail;

    // Your QProcess mail command or SmtpClient logic would go here
    // For example, if still using QProcess 'mail':
    QProcess process;
    QStringList arguments;
    // The 'mail' command might not support complex SMTP auth with just these arguments.
    // For real SMTP, you'd use a Qt SMTP library or a different command-line tool
    // that supports authentication if your m_smtpServer needs it.
    arguments << "-s" << subject << recipient;

    process.start("mail", arguments); // 'mail' command needs to be in PATH
    if (!process.waitForStarted()) {
        qWarning() << "EmailService: Failed to start mail process";
        return false;
    }
    process.write(body.toUtf8());
    process.closeWriteChannel();
    if (!process.waitForFinished()) {
        qWarning() << "EmailService: Mail process failed to finish";
        return false;
    }
    if (process.exitCode() != 0) {
        qWarning() << "EmailService: Mail process failed with exit code:" << process.exitCode() << "Output:" << process.readAllStandardError();
        return false;
    }
    qDebug() << "EmailService: 'mail' process completed successfully.";
    return true;
}


QString EmailService::generateReminderContent(EmailService::ReminderType type,
                                              const QString &clientName,
                                              const QString &invoiceNumber,
                                              const QDate &dueDate,
                                              double amount, int daysOverdue)
{
    QString subjectKeyBase = "EmailTemplates/";
    QString bodyKeyBase = "EmailTemplates/";
    QString templateNameKeyPart; // Will be "NewInvoice", "PaymentReminder", etc.

    QString defaultSubject = "Notification regarding Invoice #" + invoiceNumber;
    QString defaultBody = "Dear {client_name},\n\nThis is a notification regarding invoice #{invoice_number}.\n\nThank you.";

    switch(type) {
    case PreDueReminder:
        templateNameKeyPart = "PaymentReminder"; // Matches your SettingsDialog combobox itemData
        defaultSubject = QString("Upcoming Payment Due for Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "This is a friendly reminder that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is due on {invoice_due_date}.\n\n"
                              "Please ensure payment is submitted by the due date.\n\n"
                              "Thank you,\nYour Billing Team");
        break;

    case DueDateReminder:
        templateNameKeyPart = "OverdueNotice"; // Or a specific "DueDateNotice" if you have one
        defaultSubject = QString("Payment Due Today for Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "This is a reminder that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is due today ({invoice_due_date}).\n\n"
                              "Please submit your payment at your earliest convenience.\n\n"
                              "Thank you,\nYour Billing Team");
        break;

    case OverdueReminder:
        templateNameKeyPart = "OverdueNotice"; // Matches your SettingsDialog combobox itemData
        defaultSubject = QString("Overdue Payment for Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "Our records indicate that payment for invoice #{invoice_number} "
                              "in the amount of {invoice_total_amount} is overdue by {days_overdue} days (due date: {invoice_due_date}).\n\n"
                              "Please submit payment immediately to avoid any late fees or "
                              "service interruptions.\n\n"
                              "Thank you,\nYour Billing Team");
        break;

    case PaymentVerification:
        templateNameKeyPart = "PaymentConfirmation"; // Matches your SettingsDialog combobox itemData
        defaultSubject = QString("Payment Received for Invoice #%1").arg(invoiceNumber);
        defaultBody = QString("Dear {client_name},\n\n"
                              "We have received your payment of {invoice_total_amount} for invoice #{invoice_number}.\n\n"
                              "Thank you for your prompt payment!\n\n"
                              "Sincerely,\nYour Billing Team");
        break;
    default:
        qWarning() << "EmailService::generateReminderContent - Unknown reminder type:" << type;
        // Return a generic body or an empty string for unknown types
        return defaultBody.replace("{client_name}", clientName).replace("{invoice_number}", invoiceNumber);
    }

    // Construct the full keys for settings
    QString subjectSettingKey = subjectKeyBase + templateNameKeyPart + "/Subject";
    QString bodySettingKey = bodyKeyBase + templateNameKeyPart + "/Body";

    // Fetch from SettingsDialog using the constructed keys
    // QString fetchedSubjectTemplate = SettingsDialog::getSetting(subjectSettingKey, defaultSubject); // We return only body here
    QString fetchedBodyTemplate = SettingsDialog::getSetting(bodySettingKey, defaultBody);

    // Replace placeholders
    QString finalBody = fetchedBodyTemplate;
    finalBody.replace("{client_name}", clientName, Qt::CaseInsensitive);
    finalBody.replace("{invoice_number}", invoiceNumber, Qt::CaseInsensitive);
    finalBody.replace("{invoice_due_date}", dueDate.isValid() ? dueDate.toString("MMMM d, yyyy") : "N/A", Qt::CaseInsensitive);
    finalBody.replace("{invoice_total_amount}", QString::number(amount, 'f', 2), Qt::CaseInsensitive);
    if (type == OverdueReminder) {
        finalBody.replace("{days_overdue}", QString::number(daysOverdue), Qt::CaseInsensitive);
    }
    // Add other placeholders as needed, e.g., {company_name}
    finalBody.replace("{company_name}", SettingsDialog::getSetting("CompanyInfo/Name", "Our Company"), Qt::CaseInsensitive);


    qDebug() << "EmailService: Generated Body for type" << type << "using template key" << bodySettingKey;
    return finalBody;
}





bool InvoiceManagementWidget::testClientExists()
{
    QSqlQuery query;
    return query.exec("SELECT 1 FROM CLIENT WHERE EMAIL = 'test@example.com'") && query.next();
}

void InvoiceManagementWidget::createTestClient()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (FIRST_NAME, LAST_NAME, EMAIL) "
                  "VALUES ('Test', 'Client', 'hassinerahma7@gmail.com')");
    query.exec();
}

int InvoiceManagementWidget::ensureTestInvoiceExists()
{
    QSqlQuery query;
    query.prepare("SELECT INVOICE_ID FROM INVOICES WHERE INVOICE_NUMBER = 'TEST-001'");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }

    query.prepare("INSERT INTO INVOICES (INVOICE_NUMBER, CLIENT_ID, ISSUE_DATE, DUE_DATE, "
                  "STATUS, TOTAL_AMOUNT) VALUES ('TEST-001', "
                  "(SELECT ID FROM CLIENT WHERE EMAIL = 'hassinerahma7@gmail.com'), "
                  ":issueDate, :dueDate, 'sent', 100.00)");
    query.bindValue(":issueDate", QDate::currentDate());
    query.bindValue(":dueDate", QDate::currentDate().addDays(1));

    if (query.exec()) {
        return query.lastInsertId().toInt();
    }
    return -1;
}

void InvoiceManagementWidget::setTestInvoiceDueDate(QSqlDatabase& db, int invoiceId, const QDate& dueDate)
{
    QSqlQuery query(db);
    query.prepare("UPDATE INVOICES SET DUE_DATE = :dueDate WHERE INVOICE_ID = :invoiceId");
    query.bindValue(":dueDate", dueDate);
    query.bindValue(":invoiceId", invoiceId);
    query.exec();
}





void InvoiceManagementWidget::forceSendTestReminders()
{
    logReminderTest("=== FORCE SENDING TEST REMINDERS ===");

    createTestClientIfNeeded();
    int testInvoice = createTestInvoice(QDate::currentDate().addDays(1));

    if (testInvoice <= 0) {
        logReminderTest("!!! Failed to create test invoice");
        return;
    }

    // Directly call processReminder with test data
    QSqlQuery query;
    query.prepare("SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.TOTAL_AMOUNT, "
                  "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
                  "FROM INVOICES i "
                  "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
                  "WHERE i.INVOICE_ID = :invoiceId");
    query.bindValue(":invoiceId", testInvoice);

    if (query.exec() && query.next()) {
        processReminder(query, EmailService::PreDueReminder, QDate::currentDate());
        processReminder(query, EmailService::DueDateReminder, QDate::currentDate());
        processReminder(query, EmailService::OverdueReminder, QDate::currentDate(), 5);
    }

    logReminderTest("=== FORCE REMINDERS COMPLETE ===");
}

void InvoiceManagementWidget::createTestClientIfNeeded()
{
    QSqlQuery query;
    query.prepare("SELECT ID FROM CLIENT WHERE EMAIL = 'test@example.com'");
    if (query.exec() && query.next()) return; // Client exists

    query.prepare("INSERT INTO CLIENT (FIRST_NAME, LAST_NAME, EMAIL) "
                  "VALUES ('Test', 'Client', 'hassinerahma7@gmail.com')");
    if (!query.exec()) {
        logReminderTest("!!! Failed to create test client: " + query.lastError().text());
    }
}

int InvoiceManagementWidget::createTestInvoice(const QDate& dueDate)
{
    QSqlQuery query;
    query.prepare("INSERT INTO INVOICES (INVOICE_NUMBER, CLIENT_ID, ISSUE_DATE, DUE_DATE, "
                  "TOTAL_AMOUNT, STATUS, LAST_REMINDER_DATE, REMINDER_COUNT) "
                  "VALUES ('TEST-' || TO_CHAR(SYSDATE, 'YYYYMMDD-HH24MISS'), "
                  "(SELECT ID FROM CLIENT WHERE EMAIL = 'test@example.com'), "
                  "SYSDATE, :dueDate, 100.00, 'sent', NULL, 0) "
                  "RETURNING INVOICE_ID INTO :invoiceId");
    query.bindValue(":dueDate", dueDate);

    if (query.exec() && query.next()) {
        int invoiceId = query.value(0).toInt();
        logReminderTest(QString("Created test invoice #%1 due on %2")
                            .arg(invoiceId).arg(dueDate.toString("yyyy-MM-dd")));
        return invoiceId;
    }

    logReminderTest("!!! Failed to create test invoice: " + query.lastError().text());
    return -1;
}

void InvoiceManagementWidget::logReminderTest(const QString &message)
{
    qDebug() << "[REMINDER TEST]" << message;

    // Also log to a file
    QFile logFile("reminder_test.log");
    if (logFile.open(QIODevice::Append)) {
        QTextStream stream(&logFile);
        stream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
               << " - " << message << "\n";
        logFile.close();
    }
}


void InvoiceManagementWidget::manualTestReminder() {
    qDebug() << "=== MANUAL REMINDER TEST STARTED ===";

    // 1. Get a real invoice from the database
    QSqlQuery query;
    query.prepare("SELECT i.INVOICE_ID, i.INVOICE_NUMBER, i.DUE_DATE, i.STATUS, "
                  "c.FIRST_NAME, c.LAST_NAME, c.EMAIL "
                  "FROM INVOICES i "
                  "JOIN CLIENT c ON i.CLIENT_ID = c.ID "
                  "WHERE i.INVOICE_NUMBER = :number");
    query.bindValue(":number", "TEST-001"); // Use your test invoice number

    if (!query.exec() || !query.next()) {
        qDebug() << "Error: Invoice not found or query failed";
        return;
    }

    // 2. Extract data
    QString email = query.value("EMAIL").toString();
    QString clientName = query.value("FIRST_NAME").toString() + " " + query.value("LAST_NAME").toString();
    QString invoiceNumber = query.value("INVOICE_NUMBER").toString();
    QDate dueDate = query.value("DUE_DATE").toDate();
    double amount = 100.00; // Replace with query.value("TOTAL_AMOUNT") if available

    // 3. Manually send email
    qDebug() << "Attempting to send email to:" << email;
    bool emailSent = m_emailService->sendEmail(
        email,
        "TEST REMINDER for Invoice #" + invoiceNumber,
        QString("Dear %1,\n\nThis is a MANUAL TEST for invoice #%2 due on %3.\nAmount: %4\n\nIgnore if received.")
            .arg(clientName)
            .arg(invoiceNumber)
            .arg(dueDate.toString("dd-MM-yyyy"))
            .arg(amount)
        );

    // 4. Update database if email succeeds
    if (emailSent) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE INVOICES SET "
                            "LAST_REMINDER_DATE = SYSDATE, "
                            "REMINDER_COUNT = NVL(REMINDER_COUNT, 0) + 1 "
                            "WHERE INVOICE_NUMBER = :number");
        updateQuery.bindValue(":number", invoiceNumber);

        if (updateQuery.exec()) {
            qDebug() << "SUCCESS: Email sent and database updated";
        } else {
            qDebug() << "Email sent but DB update failed:" << updateQuery.lastError();
        }
    } else {
        qDebug() << "Email failed to send";
    }
}
