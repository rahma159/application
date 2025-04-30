/////////////////////////////////////////////////////////////////////////////
// clientpaymentwidget.cpp
/////////////////////////////////////////////////////////////////////////////

#include "clientpaymentwidget.h"
#include "ui_clientpaymentwidget.h" // The generated UI header from Qt Designer

// --- Standard Qt Includes ---
#include <QSettings>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QRegularExpression>
#include <QDate>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QDir>
#include <QPushButton>
#include <QRadioButton> // Include for radio button connect
#include <QTextDocument>
#include <QPrinter>
#include <QPagedPaintDevice> // Includes QPageSize
#include <QPainter>
#include <QLocale>
#include <QMarginsF> // Explicit include might be needed
#include <QPageLayout>


namespace { // Anonymous namespace for helpers

QString configFilePath() { return "config.ini"; } // Example path
const char* COMPANY_DETAILS_GROUP = "CompanyDetails";
const char* COMPANY_NAME_KEY = "Name";
const char* COMPANY_ADDRESS_KEY = "Address";

// Add other company keys as needed
const QString BANK_DETAILS_GROUP = "BankDetails";
const QString BANK_NAME_KEY = "BankName";
const QString ACCOUNT_HOLDER_KEY = "AccountHolder";
const QString IBAN_KEY = "IBAN";
const QString BIC_KEY = "BIC";
} //  end anonymous namespace


// --- Constructor ---
ClientPaymentWidget::ClientPaymentWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientPaymentWidget) // Create the UI instance from Designer
{
    ui->setupUi(this); // Setup UI elements defined in the .ui file

    // --- Load Bank Details from Settings ---
    QSettings settings(configFilePath(), QSettings::IniFormat);
    settings.beginGroup(BANK_DETAILS_GROUP);
    m_bankName = settings.value(BANK_NAME_KEY, "[Bank Name Not Set]").toString();
    m_accountHolder = settings.value(ACCOUNT_HOLDER_KEY, "[Account Holder Not Set]").toString();
    m_iban = settings.value(IBAN_KEY, "[IBAN Not Set]").toString();
    m_bic = settings.value(BIC_KEY, "[BIC Not Set]").toString();
    settings.endGroup();
    qDebug() << "Loaded bank details from" << settings.fileName();
    // --- End Load Bank Details ---

    // --- Initial UI State Configuration ---
    setWindowTitle(tr("Invoice Payment"));
    ui->payByCardRadio->setChecked(true);
    ui->paymentDetailsStack->setCurrentWidget(ui->cardPaymentPage);
    ui->paymentProgressBar->setVisible(false);
    ui->paymentProgressBar->setValue(0);
    ui->paymentProgressBar->setAlignment(Qt::AlignCenter);
    ui->errorMessageLabel->clear();
    ui->errorMessageLabel->setVisible(false);
    ui->errorMessageLabel->setStyleSheet("color: red; padding: 5px; background-color: #ffeeee; border: 1px solid red; border-radius: 3px;");
    ui->cardNumberInput->setPlaceholderText(tr("Enter 16-digit card number"));
    ui->expiryDateInput->setPlaceholderText(tr("MM/YY"));
    ui->cVVInput->setPlaceholderText(tr("CVV"));
    ui->cardholderNameInput->setPlaceholderText(tr("Name as it appears on card"));
    if(ui->bankInfoDisplay) { ui->bankInfoDisplay->setReadOnly(true); }
    else { qWarning() << "UI element 'bankInfoDisplay' not found."; }
    if(ui->bankDetailsEditGroup) { ui->bankDetailsEditGroup->setVisible(false); }
    else { qWarning() << "UI element 'bankDetailsEditGroup' not found."; }
    // --- End Initial UI State ---

    // --- Connections ---
    // Relying on auto-connection (on_...) for most buttons defined in the UI file.
    // Explicitly connect radio buttons and bank detail buttons for clarity/robustness.
    if (ui->payByPayPalRadio) connect(ui->payByPayPalRadio, &QRadioButton::toggled, this, &ClientPaymentWidget::on_payByPayPalRadio_toggled);
    if (ui->payByCardRadio) connect(ui->payByCardRadio, &QRadioButton::toggled, this, &ClientPaymentWidget::on_payByCardRadio_toggled);
    if (ui->payByBankTransferRadio) connect(ui->payByBankTransferRadio, &QRadioButton::toggled, this, &ClientPaymentWidget::on_payByBankTransferRadio_toggled);
    if (ui->editBankDetailsButton) connect(ui->editBankDetailsButton, &QPushButton::clicked, this, &ClientPaymentWidget::on_editBankDetailsButton_clicked);
    if (ui->saveBankDetailsButton) connect(ui->saveBankDetailsButton, &QPushButton::clicked, this, &ClientPaymentWidget::on_saveBankDetailsButton_clicked);
    if (ui->cancelEditBankDetailsButton) connect(ui->cancelEditBankDetailsButton, &QPushButton::clicked, this, &ClientPaymentWidget::on_cancelEditBankDetailsButton_clicked);
    if (ui->payPalPayButton) connect(ui->payPalPayButton, &QPushButton::clicked, this, &ClientPaymentWidget::on_payPalPayButton_clicked);

    // Auto-connection should handle:
    // on_proceedToPaymentButton_clicked()
    // on_downloadPdfButton_clicked()
    // --- End Connections ---

} // End Constructor


// --- Destructor ---
ClientPaymentWidget::~ClientPaymentWidget()
{
    delete ui;
}

// --- Public Methods ---
void ClientPaymentWidget::setInvoiceDetails(const QString& invoiceNumber, const QString& amountDue,
                                            const QString& issueDate, const QString& dueDate)
{
    m_invoiceNumber = invoiceNumber;
    m_amountDueStr = amountDue;
    ui->invoiceNumberDisplay->setText(invoiceNumber);
    ui->amountDueDisplay->setText(amountDue);
    ui->issueDateDisplay->setText(issueDate);
    ui->dueDateDisplay->setText(dueDate);
    updateBankTransferInfoDisplay(); // Update display now that invoice number is known
}

void ClientPaymentWidget::setWelcomeMessage(const QString& clientName)
{
    if (!clientName.trimmed().isEmpty()) {
        ui->welcomeClientLabel->setText(tr("Welcome, %1").arg(clientName));
    } else {
        ui->welcomeClientLabel->setText(tr("Welcome Client"));
    }
}


// --- Private Helper Methods ---

void ClientPaymentWidget::updateBankTransferInfoDisplay()
{
    QString bankInfo = tr("Please transfer the amount due to:\n\n"
                          "Bank Name: %1\n"
                          "Account Holder: %2\n"
                          "IBAN: %3\n"
                          "BIC/SWIFT: %4\n\n"
                          "**Reference: Invoice %5**")
                           .arg(m_bankName.isEmpty() ? tr("[Not Configured]") : m_bankName)
                           .arg(m_accountHolder.isEmpty() ? tr("[Not Configured]") : m_accountHolder)
                           .arg(m_iban.isEmpty() ? tr("[Not Configured]") : m_iban)
                           .arg(m_bic.isEmpty() ? tr("[Not Configured]") : m_bic)
                           .arg(m_invoiceNumber.isEmpty() ? tr("[Invoice# N/A]") : m_invoiceNumber);
    if(ui->bankInfoDisplay) ui->bankInfoDisplay->setPlainText(bankInfo);
}

bool ClientPaymentWidget::validateCardDetails()
{
    clearError();
    QString errors;
    QRegularExpression expiryRegex(R"(^(0[1-9]|1[0-2])\/?([0-9]{2})$)");
    QRegularExpression cvvRegex(R"(^[0-9]{3,4}$)");
    QRegularExpression numbersOnlyRegex(R"(^[0-9]+$)");

    if (ui->cardholderNameInput->text().trimmed().isEmpty()) errors += tr("Cardholder Name is required.\n");
    QString cardNumber = ui->cardNumberInput->text().remove(' ').remove('-');
    if (cardNumber.isEmpty()) errors += tr("Card Number is required.\n");
    else if (!numbersOnlyRegex.match(cardNumber).hasMatch()) errors += tr("Card Number must contain only digits.\n");
    else if (cardNumber.length() < 13 || cardNumber.length() > 19) errors += tr("Card Number length appears invalid (must be 13-19 digits).\n");
    QString expiryStr = ui->expiryDateInput->text();
    if (expiryStr.isEmpty()) errors += tr("Expiry Date is required.\n");
    else {
        QRegularExpressionMatch expiryMatch = expiryRegex.match(expiryStr);
        if (!expiryMatch.hasMatch()) errors += tr("Expiry Date format must be MM/YY.\n");
        else {
            bool okMM, okYY; int expMonth = expiryMatch.captured(1).toInt(&okMM); int expYear = expiryMatch.captured(2).toInt(&okYY);
            if (okMM && okYY) {
                QDate expiryTestDate(2000 + expYear, expMonth, 1);
                if (!expiryTestDate.isValid()) errors += tr("Expiry Date is invalid (e.g., month > 12).\n");
                else { QDate lastDayOfExpiryMonth = expiryTestDate.addMonths(1).addDays(-1); if (lastDayOfExpiryMonth < QDate::currentDate()) errors += tr("Card has expired.\n"); }
            } else errors += tr("Expiry Date contains non-numeric values.\n");
        }
    }
    QString cvv = ui->cVVInput->text();
    if (cvv.isEmpty()) errors += tr("CVV is required.\n");
    else if (!cvvRegex.match(cvv).hasMatch()) errors += tr("CVV must be 3 or 4 digits.\n");

    if (!errors.isEmpty()) { showError(errors.trimmed()); return false; }
    qDebug() << "Card validation passed."; return true;
}

void ClientPaymentWidget::handlePaymentProcessing()
{
    clearError(); ui->paymentProgressBar->setValue(0); ui->paymentProgressBar->setVisible(true);
    if(ui->proceedToPaymentButton) ui->proceedToPaymentButton->setEnabled(false);
    if(ui->payPalPayButton) ui->payPalPayButton->setEnabled(false);

    PaymentMethod selectedMethod = PaymentMethod::Unknown;
    if (ui->payByPayPalRadio->isChecked()) selectedMethod = PaymentMethod::PayPal;
    else if (ui->payByCardRadio->isChecked()) selectedMethod = PaymentMethod::CreditCard;
    else if (ui->payByBankTransferRadio->isChecked()) selectedMethod = PaymentMethod::BankTransfer;

    qDebug() << "Handling payment for method:" << selectedMethod;
    switch (selectedMethod) {
    case PaymentMethod::PayPal: processPayPalPayment(); break;
    case PaymentMethod::CreditCard: processCreditCardPayment(); break;
    case PaymentMethod::BankTransfer: processBankTransfer(); break;
    default: qWarning() << "No valid payment method selected."; showError(tr("Please select a payment method.")); resetPaymentUiState(); break;
    }
}

void ClientPaymentWidget::processPayPalPayment()
{
    qDebug() << "Processing PayPal payment initiation (Invoice:" << m_invoiceNumber << ")";
    ui->paymentProgressBar->setValue(15); QString approvalUrl, backendErrorMsg;
    bool backendSuccess = simulateBackendPayPalOrderCreation(approvalUrl, backendErrorMsg);
    ui->paymentProgressBar->setValue(60);
    if (backendSuccess) {
        bool opened = QDesktopServices::openUrl(QUrl(approvalUrl)); ui->paymentProgressBar->setValue(90);
        if (opened) { QMessageBox::information(this, tr("Complete Payment via PayPal"), tr("You will now be directed to the PayPal website...").arg(m_invoiceNumber)); resetPaymentUiState(); }
        else { showError(tr("Could not open the PayPal page...")); resetPaymentUiState(); }
    } else { showError(tr("Failed to initiate PayPal payment.\nError: %1").arg(backendErrorMsg)); resetPaymentUiState(); }
    ui->paymentProgressBar->setValue(100);
}

bool ClientPaymentWidget::simulateBackendPayPalOrderCreation(QString& approvalUrl, QString& errorMsg)
{
    qDebug() << "  [Simulation] Backend: Request for invoice" << m_invoiceNumber << "amount" << m_amountDueStr;
    if (QRandomGenerator::global()->bounded(10) == 0) { errorMsg = tr("Simulated backend error."); return false; }
    approvalUrl = QString("https://www.sandbox.paypal.com/checkoutnow?token=SIM_%1_%2").arg(m_invoiceNumber.isEmpty() ? "NO_INV" : m_invoiceNumber).arg(QDateTime::currentMSecsSinceEpoch());
    errorMsg = ""; return true;
}

void ClientPaymentWidget::processCreditCardPayment()
{
    qDebug() << "Processing Credit Card payment (Invoice:" << m_invoiceNumber << ")";
    ui->paymentProgressBar->setValue(10); if (!validateCardDetails()) { resetPaymentUiState(); return; }
    ui->paymentProgressBar->setValue(30);
    // --- TODO: Real Gateway Integration ---
    qDebug() << "Simulating sending card details to gateway..."; ui->paymentProgressBar->setValue(80);
    bool paymentSuccess = true; // **** SIMULATED RESULT ****
    QString transactionId = "txn_SIM_" + QString::number(QDateTime::currentMSecsSinceEpoch());
    QString failureReason = "Insufficient funds";
    ui->paymentProgressBar->setValue(100);
    if (paymentSuccess) {
        QSqlQuery updateQuery(QSqlDatabase::database());
        updateQuery.prepare("UPDATE INVOICES SET STATUS = 'paid', PAYMENT_DATE = CURRENT_TIMESTAMP WHERE INVOICE_NUMBER = :invNum");
        updateQuery.bindValue(":invNum", m_invoiceNumber);
        if (!updateQuery.exec()) { qWarning() << "Failed DB status update:" << updateQuery.lastError().text(); QMessageBox::warning(this, tr("DB Warning"), tr("Payment OK, status update failed.")); }
        else { qDebug() << "Invoice" << m_invoiceNumber << "status updated to 'paid'"; }
        QMessageBox::information(this, tr("Payment Successful"), tr("Credit card payment successful for invoice %1.\nTxn ID: %2").arg(m_invoiceNumber).arg(transactionId));
        accept();
    } else { showError(tr("Card payment failed: %1").arg(failureReason)); resetPaymentUiState(); }
}

void ClientPaymentWidget::processBankTransfer()
{
    qDebug() << "Processing Bank Transfer (showing instructions for invoice:" << m_invoiceNumber << ")";
    ui->paymentProgressBar->setValue(100);
    QMessageBox bankInfoBox(this); bankInfoBox.setWindowTitle(tr("Bank Transfer Instructions"));
    bankInfoBox.setText(tr("Please use bank details shown... Reference: Invoice %1...").arg(m_invoiceNumber));
    bankInfoBox.setIcon(QMessageBox::Information); bankInfoBox.setStandardButtons(QMessageBox::Ok); bankInfoBox.exec();
    QSqlQuery updateQuery(QSqlDatabase::database());
    updateQuery.prepare("UPDATE INVOICES SET STATUS = 'pending_bank_transfer' WHERE INVOICE_NUMBER = :invNum");
    updateQuery.bindValue(":invNum", m_invoiceNumber);
    if (!updateQuery.exec()) { qWarning() << "Failed DB status update:" << updateQuery.lastError().text(); }
    else { qDebug() << "Invoice" << m_invoiceNumber << "status updated to 'pending_bank_transfer'"; }
    accept();
}

void ClientPaymentWidget::showError(const QString &message)
{
    ui->errorMessageLabel->setText(message); ui->errorMessageLabel->setVisible(true);
    qWarning() << "Payment Widget Error:" << message;
}

void ClientPaymentWidget::clearError()
{
    ui->errorMessageLabel->clear(); ui->errorMessageLabel->setVisible(false);
}

void ClientPaymentWidget::resetPaymentUiState()
{
    ui->paymentProgressBar->setVisible(false); ui->paymentProgressBar->setValue(0);
    if(ui->proceedToPaymentButton) ui->proceedToPaymentButton->setEnabled(true);
    if(ui->payPalPayButton) ui->payPalPayButton->setEnabled(true);
}

void ClientPaymentWidget::loadBankDetailsToEditFields()
{
    if(!ui->bankNameInput || !ui->accountHolderInput || !ui->ibanInput || !ui->bicInput) { qWarning() << "Cannot load bank details to edit fields - UI elements missing."; return; }
    qDebug() << "Loading current bank details into edit fields...";
    ui->bankNameInput->setText(m_bankName); ui->accountHolderInput->setText(m_accountHolder);
    ui->ibanInput->setText(m_iban); ui->bicInput->setText(m_bic);
}


// --- Slots ---

// Connected automatically if name matches: on_ObjectName_SignalName
void ClientPaymentWidget::on_proceedToPaymentButton_clicked()
{
    qDebug() << "'Proceed To Payment' button clicked.";
    handlePaymentProcessing();
}

void ClientPaymentWidget::on_downloadPdfButton_clicked()
{
    qDebug() << "*** Download PDF button clicked for Invoice Number:" << m_invoiceNumber << "***";

    if (m_invoiceNumber.isEmpty()) {
        QMessageBox::warning(this, tr("Download Failed"), tr("No invoice number available to generate PDF."));
        qWarning() << "Download aborted: m_invoiceNumber is empty.";
        return;
    }

    // --- 1. Fetch Data from Database ---
    qDebug() << "Step 1: Fetching data from database...";
    QSqlDatabase db = QSqlDatabase::database(); // Get default connection
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Database connection is not open. Cannot generate PDF."));
        qCritical() << "Database connection closed!";
        return;
    }
    qDebug() << "Database connection is open.";

    // --- Fetch Company Details ---
    qDebug() << "Fetching company details...";
    QSettings settings(configFilePath(), QSettings::IniFormat);
    settings.beginGroup(COMPANY_DETAILS_GROUP);
    QString companyName = settings.value(COMPANY_NAME_KEY, "ConsultIQ").toString();
    if (companyName.trimmed().isEmpty()) companyName = "ConsultIQ";
    QString companyAddress = settings.value(COMPANY_ADDRESS_KEY, "ConsultIQ Address...").toString();
    settings.endGroup();
    qDebug() << "Company Name:" << companyName << "| Address:" << companyAddress;
    // --- End Fetch Company Details ---

    // --- Fetch Invoice Details (including CLIENT_NAME directly) ---
    qDebug() << "Fetching main invoice details for Number:" << m_invoiceNumber;
    QSqlQuery invoiceQuery(db);
    int invoice_db_id = -1;
    int clientId = -1; // Keep clientId if needed for fetching address/email later
    QDateTime issueDate, dueDate;
    double subtotal = 0.0, taxAmount = 0.0, totalAmount = 0.0;
    QString notes, paymentTerms, invoiceStatus;
    QString clientName = tr("N/A"); // Default value if fetch fails or name is empty
    QString clientAddress = tr("N/A"); // Default - requires separate fetch if needed
    QString clientEmail = tr("N/A");   // Default - requires separate fetch if needed

    invoiceQuery.prepare("SELECT INVOICE_ID, CLIENT_ID, CLIENT_NAME, ISSUE_DATE, DUE_DATE, SUBTOTAL, TAX_AMOUNT, TOTAL_AMOUNT, NOTES, PAYMENT_TERMS, STATUS "
                         "FROM INVOICES WHERE INVOICE_NUMBER = :invNum");
    invoiceQuery.bindValue(":invNum", m_invoiceNumber);

    if (!invoiceQuery.exec()) {
        qWarning() << "!! FAILED to execute invoice details query for number:" << m_invoiceNumber << "Error:" << invoiceQuery.lastError().text();
        qWarning() << "   Query was:" << invoiceQuery.lastQuery();
        QMessageBox::critical(this, tr("Database Error"), tr("Could not execute query to retrieve details for invoice %1.").arg(m_invoiceNumber));
        return;
    }

    if (invoiceQuery.next()) {
        qDebug() << "Invoice details found for number:" << m_invoiceNumber;
        invoice_db_id = invoiceQuery.value("INVOICE_ID").toInt();
        clientId = invoiceQuery.value("CLIENT_ID").toInt();

        clientName = invoiceQuery.value("CLIENT_NAME").toString();
        if (clientName.trimmed().isEmpty()) {
            qWarning() << "Fetched CLIENT_NAME from INVOICES table is empty for invoice:" << m_invoiceNumber << ". Using default 'N/A'.";
            clientName = tr("N/A");
        } else {
            qDebug() << " Retrieved Client Name directly from INVOICES:" << clientName;
        }

        issueDate = invoiceQuery.value("ISSUE_DATE").toDateTime();
        dueDate = invoiceQuery.value("DUE_DATE").toDateTime();
        subtotal = invoiceQuery.value("SUBTOTAL").toDouble();
        taxAmount = invoiceQuery.value("TAX_AMOUNT").toDouble();
        totalAmount = invoiceQuery.value("TOTAL_AMOUNT").toDouble();
        notes = invoiceQuery.value("NOTES").toString();
        paymentTerms = invoiceQuery.value("PAYMENT_TERMS").toString();
        invoiceStatus = invoiceQuery.value("STATUS").toString();
        qDebug() << " Retrieved INVOICE_ID:" << invoice_db_id << "| Fetched CLIENT_ID:" << clientId;
    } else {
        qWarning() << "!! No invoice found in INVOICES table with INVOICE_NUMBER:" << m_invoiceNumber;
        QMessageBox::critical(this, tr("Data Error"), tr("Invoice number %1 not found in the database.").arg(m_invoiceNumber));
        return;
    }
    // --- End Fetch Invoice Details ---


    // --- OPTIONAL: Fetch Client Address/Email if needed ---
    // (Keep commented out unless you have a separate CLIENT table for this)
    /*
    if (clientId > 0) {
        // ... query for address/email ...
    }
    */
    // --- End Optional Fetch Client Address/Email ---


    // --- OMITTED: Fetch Line Items ---
    qDebug() << "Skipping line item fetch as per request.";
    // --- End OMITTED: Fetch Line Items ---


    // --- 2. Construct Enhanced HTML for PDF ---
    QLocale locale = QLocale::system();
    QString currencySymbol = "";

    QString htmlContent = QString(
                              "<html>"
                              "<head>"
                              "<style>" // Keep your CSS styles here
                              "body { font-family: 'Segoe UI', 'Helvetica Neue', Arial, sans-serif; font-size: 10pt; color: #333; line-height: 1.4; }"
                              "h1 { font-size: 18pt; color: #1a1a1a; border-bottom: 2px solid #555; padding-bottom: 8px; margin: 0 0 15px 0; font-weight: bold; text-transform: uppercase; letter-spacing: 1px; text-align: left; }"
                              "h2 { font-size: 14pt; color: #2a2a2a; margin-bottom: 2px; font-weight: bold; text-align: right; }"
                              ".header-container { width: 100%; margin-bottom: 35px; border-bottom: 1px solid #eee; padding-bottom: 15px; overflow: auto; } "
                              ".company-details { float: right; width: 55%; text-align: right; font-size: 9pt; line-height: 1.4; padding-left: 10px; box-sizing: border-box; } "
                              ".invoice-info { float: left; width: 45%; text-align: left; font-size: 10pt; line-height: 1.6; padding-right: 10px; box-sizing: border-box;} "
                              ".invoice-info b { display: inline-block; min-width: 75px; font-weight: bold; text-align: left; margin-right: 5px; } "
                              ".invoice-client-name { font-size: 11pt; font-weight: bold; margin-top: 10px; margin-bottom: 0px; display: block; text-align: left; } " // Reduced bottom margin maybe
                              ".client-details { clear: both; margin-top: 20px; margin-bottom: 30px; font-size: 10pt; line-height: 1.5; } "
                              ".client-details b { display: block; font-weight: bold; margin-bottom: 4px; } "
                              "table.totals { width: 45%; float: right; margin-top: 25px; border-collapse: collapse; font-size: 11pt; } "
                              "table.totals td { padding: 8px 10px; border: 1px solid #ccc; vertical-align: top; }"
                              "table.totals td.label { text-align: right; font-weight: bold; background-color: #f0f0f0; width: 55%; white-space: nowrap; }"
                              "table.totals td.value { text-align: right; width: 45%; }"
                              "table.totals tr:last-child td { font-size: 12pt; font-weight: bold; background-color: #e8e8e8; }"
                              ".notes-terms { margin-top: 40px; padding-top: 15px; font-size: 9pt; clear: both; line-height: 1.4; border-top: 1px solid #eee; } "
                              ".notes-terms b { display: block; margin-bottom: 3px; font-weight: bold; }"
                              ".footer { margin-top: 50px; text-align: center; font-size: 8pt; color: #888; border-top: 1px solid #eee; padding-top: 10px; }"
                              "</style>"
                              "</head>"
                              "<body>"
                              // --- Header Section ---
                              "<div class='header-container'>"
                              "<div class='company-details'>"
                              "<h2>%1</h2>"
                              "%2<br>"
                              "</div>"
                              "<div class='invoice-info'>"
                              "<h1>INVOICE</h1>"
                              // **** MODIFICATION ICI ****
                              "<div class='invoice-client-name'>%7</div><br>" // Ajout de <br> après la div du nom client
                              // **************************
                              "<b>Invoice #:</b> %3<br>"
                              "<b>Status:</b> %4<br>"
                              "<b>Issue Date:</b> %5<br>"
                              "<b>Due Date:</b> %6"
                              "</div>"
                              "</div>" // End header-container
                              // --- Client "Bill To" Address Block ---
                              "<div class='client-details'>"
                              "<b>Bill To:</b><br>"
                              "%8<br>"
                              "%9"
                              "</div>"
                              // --- Totals Table ---
                              "<table class='totals'>"
                              "<tr><td class='label'>Subtotal:</td><td class='value'>%15%10</td></tr>"
                              "<tr><td class='label'>Tax:</td><td class='value'>%15%11</td></tr>"
                              "<tr><td class='label'>Total Amount Due:</td><td class='value'>%15%12</td></tr>"
                              "</table>"
                              // --- Notes and Terms ---
                              "<div class='notes-terms'>"
                              "<b>Notes:</b><br>%13<br><br>"
                              "<b>Payment Terms:</b><br>%14"
                              "</div>"
                              // --- Footer ---
                              "<div class='footer'>Thank you for your business!</div>"
                              "</body></html>")
                              // --- Arguments for QString::arg ---
                              .arg(companyName.toHtmlEscaped())                               // %1
                              .arg(companyAddress.replace("\n", "<br>").toHtmlEscaped())     // %2
                              .arg(m_invoiceNumber.toHtmlEscaped())                          // %3
                              .arg(invoiceStatus.toHtmlEscaped())                            // %4
                              .arg(issueDate.toString("yyyy-MM-dd"))                         // %5
                              .arg(dueDate.toString("yyyy-MM-dd"))                           // %6
                              .arg(clientName.toHtmlEscaped())                               // %7
                              .arg(clientAddress) // Likely "N/A"
                              .arg(clientEmail.toHtmlEscaped()) // Likely "N/A"
                              .arg(locale.toString(subtotal, 'f', 2))                        // %10
                              .arg(locale.toString(taxAmount, 'f', 2))                       // %11
                              .arg(locale.toString(totalAmount, 'f', 2))                     // %12
                              .arg(notes.replace("\n", "<br>").toHtmlEscaped())              // %13
                              .arg(paymentTerms.replace("\n", "<br>").toHtmlEscaped())       // %14
                              .arg(currencySymbol);                                          // %15

    // --- End Construct HTML ---


    // --- 3. Get Save Filename from User ---
    QString suggestedFileName = QString("Invoice_%1.pdf").arg(m_invoiceNumber.isEmpty() ? "Details" : m_invoiceNumber);
    QString initialPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (initialPath.isEmpty() || !QFileInfo(initialPath).isWritable()) {
        initialPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    }
    initialPath += "/" + suggestedFileName;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Invoice PDF"), initialPath, tr("PDF Documents (*.pdf);;All Files (*)"));

    if (fileName.isEmpty()) {
        qDebug() << "User cancelled save dialog.";
        return;
    }
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }
    qDebug() << "User chose to save PDF to:" << fileName;
    // --- End Get Save Filename ---


    // --- 4. Generate PDF using QTextDocument ---
    QTextDocument document;
    document.setHtml(htmlContent);

    // --- 5. Setup Printer ---
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    // --- 6. Print to File ---
    qDebug() << "Printing QTextDocument to PDF file...";
    document.print(&printer);
    qDebug() << "Printing finished.";
    // --- End PDF Generation ---


    // --- 7. Check Result and Auto-Open ---
    QFile file(fileName);
    if (file.exists() && file.size() > 0) {
        qDebug() << "Successfully generated PDF:" << fileName << "Size:" << file.size() << "bytes";
        QMessageBox::information(this, tr("Download Successful"), tr("Invoice PDF saved successfully to:\n%1").arg(QDir::toNativeSeparators(fileName)));

        qDebug() << "Attempting to auto-open generated PDF...";
        bool opened = QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        if (!opened) {
            qWarning() << "Could not automatically open the PDF file:" << fileName << ". Please open it manually.";
            QMessageBox::warning(this, tr("Auto-Open Failed"), tr("Could not automatically open the saved PDF file:\n%1\nPlease open it manually from your documents folder.").arg(QDir::toNativeSeparators(fileName)));
        } else {
            qDebug() << "PDF open command sent successfully.";
        }

    } else {
        QString errorMsg = tr("Failed to generate or save the PDF file. ");
        if(printer.printerState() == QPrinter::Error) {
            errorMsg += tr("The print driver reported an error. ");
            qWarning() << "PDF generation failed. QPrinter error state detected.";
        } else if (!file.exists()) {
            errorMsg += tr("The file was not created. Check permissions for the save location. ");
            qWarning() << "PDF generation failed. File does not exist:" << fileName;
        } else if (file.size() == 0) {
            errorMsg += tr("The generated file is empty. ");
            qWarning() << "PDF generation resulted in an empty file:" << fileName;
        } else {
            qWarning() << "PDF generation failed or resulted in an invalid file:" << fileName;
        }
        errorMsg += tr("Please check application logs for more details.");
        QMessageBox::critical(this, tr("Save Error"), errorMsg);
    }
    // --- End Check ---

}
// Connected by name or explicitly
void ClientPaymentWidget::on_payByPayPalRadio_toggled(bool checked)
{
    if (checked && ui->paymentDetailsStack) { ui->paymentDetailsStack->setCurrentWidget(ui->payPalPage); clearError(); }
}
// Connected by name or explicitly
void ClientPaymentWidget::on_payByCardRadio_toggled(bool checked)
{
    if (checked && ui->paymentDetailsStack) { ui->paymentDetailsStack->setCurrentWidget(ui->cardPaymentPage); clearError(); }
}
// Connected by name or explicitly - FIXED TYPO
void ClientPaymentWidget::on_payByBankTransferRadio_toggled(bool checked)
{
    if (checked && ui->paymentDetailsStack) { ui->paymentDetailsStack->setCurrentWidget(ui->bankTransferPage); clearError(); if(ui->bankDetailsEditGroup) ui->bankDetailsEditGroup->setVisible(false); }
}

// Connected explicitly or by name
void ClientPaymentWidget::on_editBankDetailsButton_clicked()
{
    // First, check if the pointer is valid.
    if (!ui->bankDetailsEditGroup) {
        qWarning() << "on_editBankDetailsButton_clicked: ui->bankDetailsEditGroup is null!";
        return; // If it's null, do nothing further.
    }

    // If the pointer is valid, proceed with loading and showing.
    loadBankDetailsToEditFields();
    ui->bankDetailsEditGroup->setVisible(true);
    // You might also want to hide the display group and show the edit group here.
    // Example:
    // if (ui->bankDetailsDisplayGroup) {
    //     ui->bankDetailsDisplayGroup->setVisible(false);
    // }
    // ui->bankDetailsEditGroup->setFocus(); // Maybe focus the first field
}
// Connected explicitly or by name
void ClientPaymentWidget::on_saveBankDetailsButton_clicked()
{
    if(!ui->bankDetailsEditGroup || !ui->bankNameInput || !ui->accountHolderInput || !ui->ibanInput || !ui->bicInput) return;
    // TODO: Validation
    QSettings settings(configFilePath(), QSettings::IniFormat); settings.beginGroup(BANK_DETAILS_GROUP);
    settings.setValue(BANK_NAME_KEY, ui->bankNameInput->text().trimmed()); settings.setValue(ACCOUNT_HOLDER_KEY, ui->accountHolderInput->text().trimmed());
    settings.setValue(IBAN_KEY, ui->ibanInput->text().trimmed()); settings.setValue(BIC_KEY, ui->bicInput->text().trimmed()); settings.endGroup();
    m_bankName = ui->bankNameInput->text().trimmed(); m_accountHolder = ui->accountHolderInput->text().trimmed(); m_iban = ui->ibanInput->text().trimmed(); m_bic = ui->bicInput->text().trimmed();
    updateBankTransferInfoDisplay(); ui->bankDetailsEditGroup->setVisible(false); QMessageBox::information(this, tr("Settings Saved"), tr("Bank details updated."));
}
// Connected explicitly or by name
void ClientPaymentWidget::on_cancelEditBankDetailsButton_clicked()
{
    if(ui->bankDetailsEditGroup) ui->bankDetailsEditGroup->setVisible(false);
}

// Connected explicitly or by name
void ClientPaymentWidget::on_payPalPayButton_clicked()
{
    if (!ui->payByPayPalRadio->isChecked()) ui->payByPayPalRadio->setChecked(true);
    clearError(); ui->paymentProgressBar->setValue(0); ui->paymentProgressBar->setVisible(true);
    if(ui->proceedToPaymentButton) ui->proceedToPaymentButton->setEnabled(false);
    if(ui->payPalPayButton) ui->payPalPayButton->setEnabled(false);
    processPayPalPayment();
}


/////////////////////////////////////////////////////////////////////////////
// End of clientpaymentwidget.cpp
/////////////////////////////////////////////////////////////////////////////
