#include "clientpaymentwidget.h"
#include "ui_clientpaymentwidget.h" // The generated UI header

// --- Standard Qt Includes ---
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices> // For opening URLs (like PayPal)
#include <QUrl>
#include <QRegularExpression> // For basic validation examples
#include <QDate>             // For date validation examples

// --- Constants (Consider moving to a config file or settings class) ---
namespace PaymentConfig {
// Example: Replace with your actual PayPal URL generation logic if needed
const QString PAYPAL_REDIRECT_URL_TEMPLATE = "https://www.sandbox.paypal.com/checkoutnow?token=%1";
// Example: Replace with actual bank details (better loaded from secure config)
const QString BANK_TRANSFER_INFO_TEMPLATE =
    "Please transfer the amount due to:\n\n"
    "Bank Name: [Your Bank Name Here]\n"
    "IBAN: [Your IBAN Here]\n"
    "BIC/SWIFT: [Your BIC Here]\n\n"
    "Reference: Invoice %1"; // %1 will be replaced with Invoice Number
}


ClientPaymentWidget::ClientPaymentWidget(QWidget *parent) :
    QDialog(parent), // Use QDialog for accept()/reject() and modal behavior
    ui(new Ui::ClientPaymentWidget)
{
    ui->setupUi(this);

    // --- Initial UI State Configuration ---
    setWindowTitle(tr("Invoice Payment")); // Set a clear window title

    // Assume Card Payment is the default (or change as needed)
    ui->payByCardRadio->setChecked(true); // Set default radio button
    ui->paymentDetailsStack->setCurrentWidget(ui->cardPaymentPage); // Set default visible page

    ui->paymentProgressBar->setVisible(false); // Hide progress bar initially
    ui->paymentProgressBar->setValue(0);
    ui->paymentProgressBar->setAlignment(Qt::AlignCenter); // Center progress text

    ui->errorMessageLabel->clear();          // Ensure error label is empty
    ui->errorMessageLabel->setVisible(false); // Hide error label initially
    ui->errorMessageLabel->setStyleSheet("color: red;"); // Style error message

    // Set Placeholder Text for inputs (Good UI practice)
    ui->cardNumberInput->setPlaceholderText(tr("Enter 16-digit card number"));
    ui->expiryDateInput->setPlaceholderText(tr("MM/YY"));
    ui->cVVInput->setPlaceholderText(tr("CVV"));
    ui->cardholderNameInput->setPlaceholderText(tr("Name as it appears on card"));

    // (Optional) Add a dedicated PayPal button if needed in the UI for payPalPage
    // QPushButton *payPalButton = ui->payPalPage->findChild<QPushButton*>("payPalPayButton");
    // if (payPalButton) {
    //     connect(payPalButton, &QPushButton::clicked, this, &ClientPaymentWidget::initiatePayPalPayment);
    // }

    // No need to call setupConnections() if using auto-connection (on_..._signal())
}

ClientPaymentWidget::~ClientPaymentWidget()
{
    delete ui;
}

// --- Public Methods to Populate Data ---

void ClientPaymentWidget::setInvoiceDetails(const QString& invoiceNumber, const QString& amountDue,
                                            const QString& issueDate, const QString& dueDate)
{
    // Store for later use if needed (e.g., bank transfer reference)
    m_invoiceNumber = invoiceNumber;
    m_amountDueStr = amountDue; // Store amount if needed for payment logic

    ui->invoiceNumberDisplay->setText(invoiceNumber);
    ui->amountDueDisplay->setText(amountDue); // Consider locale-specific currency formatting
    ui->issueDateDisplay->setText(issueDate);   // Consider QLocale formatting for dates
    ui->dueDateDisplay->setText(dueDate);

    // Update Bank Transfer Info automatically if it depends on the invoice number
    updateBankTransferInfoDisplay();
}

void ClientPaymentWidget::setWelcomeMessage(const QString& clientName)
{
    if (!clientName.isEmpty()) {
        ui->welcomeClientLabel->setText(tr("Welcome, %1").arg(clientName));
    } else {
        ui->welcomeClientLabel->setText(tr("Welcome Client")); // Default
    }
}

// Removed setBankTransferInfo - now handled internally by setInvoiceDetails
// If bank info is entirely static, it could be set in the constructor or via another method.

// --- Private Helper Methods ---

void ClientPaymentWidget::updateBankTransferInfoDisplay()
{
    // Populate fixed bank info using the template and current invoice number
    QString bankInfo = PaymentConfig::BANK_TRANSFER_INFO_TEMPLATE.arg(m_invoiceNumber);
    ui->bankInfoDisplay->setPlainText(bankInfo);
    ui->bankInfoDisplay->setReadOnly(true);
}

bool ClientPaymentWidget::validateCardDetails()
{
    ui->errorMessageLabel->clear();
    ui->errorMessageLabel->setVisible(false);

    QString errors;
    QRegularExpression expiryRegex(R"(^(0[1-9]|1[0-2])\/?([0-9]{2})$)"); // MM/YY
    QRegularExpression cvvRegex(R"(^[0-9]{3,4}$)");                     // 3 or 4 digits
    QRegularExpression numbersOnlyRegex(R"(^[0-9]+$)");

    // 1. Card Number (Basic Checks: Not empty, numbers only, basic length)
    QString cardNumber = ui->cardNumberInput->text().remove(' ').remove('-'); // Remove spaces/dashes
    if (cardNumber.isEmpty() || !numbersOnlyRegex.match(cardNumber).hasMatch() || cardNumber.length() < 13 || cardNumber.length() > 19) {
        errors += tr("Card Number appears invalid.\n");
        // TODO: Implement Luhn algorithm check for better validation
    }

    // 2. Expiry Date (Format MM/YY, must be in the future)
    QString expiryStr = ui->expiryDateInput->text();
    QRegularExpressionMatch expiryMatch = expiryRegex.match(expiryStr);
    if (!expiryMatch.hasMatch()) {
        errors += tr("Expiry Date format must be MM/YY.\n");
    } else {
        bool okMM, okYY;
        int expMonth = expiryMatch.captured(1).toInt(&okMM);
        int expYear = expiryMatch.captured(2).toInt(&okYY);
        if (okMM && okYY) {
            // QDate expects year >= 1900, so add 2000
            QDate expiryDate(2000 + expYear, expMonth, 1);
            // Get last day of expiry month
            expiryDate = expiryDate.addMonths(1).addDays(-1);
            if (expiryDate < QDate::currentDate()) {
                errors += tr("Card has expired.\n");
            }
        } else {
            errors += tr("Expiry Date contains invalid numbers.\n"); // Should not happen with regex
        }
    }

    // 3. CVV (Format: 3 or 4 digits)
    QString cvv = ui->cVVInput->text();
    if (!cvvRegex.match(cvv).hasMatch()) {
        errors += tr("CVV must be 3 or 4 digits.\n");
    }

    // 4. Cardholder Name (Basic Check: Not empty)
    if (ui->cardholderNameInput->text().trimmed().isEmpty()) {
        errors += tr("Cardholder Name cannot be empty.\n");
    }

    // --- Display Errors ---
    if (!errors.isEmpty()) {
        ui->errorMessageLabel->setText(errors.trimmed());
        ui->errorMessageLabel->setVisible(true);
        return false;
    }

    return true;
}


void ClientPaymentWidget::handlePaymentProcessing()
{
    qDebug() << "Initiating payment processing...";
    clearError();
    ui->paymentProgressBar->setValue(0);
    ui->paymentProgressBar->setVisible(true);
    // Disable button to prevent double-clicks during processing
    ui->proceedToPaymentButton->setEnabled(false);

    // --- Determine Payment Method ---
    PaymentMethod method = PaymentMethod::Unknown;
    if (ui->payByPayPalRadio->isChecked()) {
        method = PaymentMethod::PayPal;
    } else if (ui->payByCardRadio->isChecked()) {
        method = PaymentMethod::CreditCard;
    } else if (ui->payByBankTransferRadio->isChecked()) {
        method = PaymentMethod::BankTransfer;
    }

    // --- Process Based on Method ---
    switch (method) {
    case PaymentMethod::PayPal:
        processPayPalPayment();
        break;

    case PaymentMethod::CreditCard:
        processCreditCardPayment();
        break;

    case PaymentMethod::BankTransfer:
        processBankTransfer();
        break;

    default:
        showError(tr("Please select a valid payment method."));
        resetPaymentUiState(); // Re-enable button, hide progress
        break;
    }
    // Note: Re-enabling the button and hiding progress is handled within
    // the specific process_ methods or resetPaymentUiState() on failure.
}

void ClientPaymentWidget::processPayPalPayment()
{
    qDebug() << "Processing PayPal...";
    ui->paymentProgressBar->setValue(25); // Indicate activity

    // --- TODO: Implement PayPal Integration ---
    // This is highly dependent on the PayPal API you use (REST API, etc.)
    // Option 1: Redirect to PayPal Checkout URL
    //   - You might need to make a backend call first to get a checkout token/URL
    //   - Store the token/order ID to verify payment later via webhook or polling
    QString payPalToken = "EXAMPLE_TOKEN_FROM_YOUR_BACKEND"; // Replace with actual token
    QString redirectUrl = PaymentConfig::PAYPAL_REDIRECT_URL_TEMPLATE.arg(payPalToken);
    qDebug() << "Redirecting to PayPal (simulated):" << redirectUrl;
    // QDesktopServices::openUrl(QUrl(redirectUrl)); // Uncomment to actually open browser

    ui->paymentProgressBar->setValue(100); // Simulate immediate action for redirect

    QMessageBox::information(this, tr("Redirecting to PayPal"),
                             tr("You will be redirected to the PayPal website to complete your payment.\n"
                                "(This is a simulation - no redirection occurred)."));

    // IMPORTANT: For redirect, you usually DON'T close the dialog (accept()) here.
    // You need a mechanism (backend webhook, polling) to know when PayPal confirms payment.
    // Only then would you update the invoice status and potentially close this dialog
    // or provide a success message here based on that confirmation.
    // For now, we just re-enable the UI.
    resetPaymentUiState(); // Re-enable button, hide progress
}


void ClientPaymentWidget::processCreditCardPayment()
{
    qDebug() << "Processing Credit Card...";
    ui->paymentProgressBar->setValue(10);

    if (!validateCardDetails()) {
        resetPaymentUiState(); // Validation failed, reset UI
        return;
    }

    ui->paymentProgressBar->setValue(30); // Validation passed

    // --- TODO: Implement Secure Payment Gateway Integration (e.g., Stripe, Braintree) ---
    // NEVER handle raw card details directly on your server unless you are fully PCI DSS compliant.
    // Use the gateway's SDK/API (often involves sending details directly from client to gateway,
    // or using tokenization).

    // 1. Get card details (example, use gateway's secure fields/methods in reality)
    QString cardNumber = ui->cardNumberInput->text().remove(' ').remove('-');
    QString expiry = ui->expiryDateInput->text(); // e.g., "MM/YY"
    QString cvv = ui->cVVInput->text();
    QString cardholderName = ui->cardholderNameInput->text().trimmed();
    QString amount = m_amountDueStr; // Get amount from stored details
    QString currency = "EUR"; // Or get from config/invoice

    qDebug() << "Simulating sending card details to payment gateway...";
    qDebug() << "Card (Last 4):" << cardNumber.right(4) << "Expiry:" << expiry << "CVV:" << cvv.length() << "digits";
    qDebug() << "Amount:" << amount << currency;

    // 2. Simulate API call to gateway
    // QThread::sleep(2); // NEVER use sleep in GUI thread! Use QTimer or signals for async ops.
    ui->paymentProgressBar->setValue(80); // Simulate processing time

    // 3. Simulate Response from Gateway
    bool paymentSuccess = true; // **** REPLACE WITH ACTUAL API CALL RESULT ****
    QString transactionId = "txn_123abc456def"; // Example response data
    QString failureReason = "Insufficient funds"; // Example failure reason

    ui->paymentProgressBar->setValue(100);

    // 4. Handle Response
    if (paymentSuccess) {
        qDebug() << "Payment successful. Transaction ID:" << transactionId;
        QMessageBox::information(this, tr("Payment Successful"),
                                 tr("Your credit card payment for invoice %1 was successful.\nTransaction ID: %2")
                                     .arg(m_invoiceNumber).arg(transactionId));
        // TODO: Update invoice status in your database/system to 'Paid'
        accept(); // Close the dialog successfully
    } else {
        qDebug() << "Payment failed. Reason:" << failureReason;
        showError(tr("Card payment failed: %1").arg(failureReason));
        resetPaymentUiState(); // Allow user to retry or change method
    }
}

void ClientPaymentWidget::processBankTransfer()
{
    qDebug() << "Processing Bank Transfer (Manual Acknowledgment)";
    ui->paymentProgressBar->setValue(100);

    QMessageBox::information(this, tr("Bank Transfer Instructions"),
                             tr("Please use the provided bank details to complete your payment.\n"
                                "Use invoice number '%1' as the payment reference.\n\n"
                                "Your invoice will be marked as paid upon confirmation of receipt by our team.")
                                 .arg(m_invoiceNumber));

    // TODO: Optionally update invoice status in your database/system to 'Pending Confirmation'
    accept(); // Close the dialog as user action is external
}

void ClientPaymentWidget::showError(const QString &message)
{
    ui->errorMessageLabel->setText(message);
    ui->errorMessageLabel->setVisible(true);
    qWarning() << "Payment Error Displayed:" << message; // Log warning
}

void ClientPaymentWidget::clearError()
{
    ui->errorMessageLabel->clear();
    ui->errorMessageLabel->setVisible(false);
}

void ClientPaymentWidget::resetPaymentUiState()
{
    ui->paymentProgressBar->setVisible(false);
    ui->paymentProgressBar->setValue(0);
    ui->proceedToPaymentButton->setEnabled(true); // Re-enable button
}


// --- SLOTS (Connected via Auto-Connection: on_objectName_signalName) ---

void ClientPaymentWidget::on_proceedToPaymentButton_clicked()
{
    handlePaymentProcessing();
}

void ClientPaymentWidget::on_downloadPdfButton_clicked()
{
    qDebug() << "Download PDF button clicked for invoice:" << m_invoiceNumber;

    // --- TODO: Implement PDF Generation/Retrieval ---
    // 1. Get the PDF data (byte array?) based on m_invoiceNumber
    //    - Generate it on the fly using a PDF library (e.g., KDReports, external library)
    //    - Fetch it from a database BLOB
    //    - Read it from a file server/path
    // 2. Use QFileDialog::getSaveFileName to ask the user where to save it
    // 3. Write the fetched/generated QByteArray to the selected file using QFile

    QMessageBox::information(this, tr("Download PDF"), tr("PDF download functionality is not yet implemented."));
}

// Slots to change the visible payment details page

void ClientPaymentWidget::on_payByPayPalRadio_toggled(bool checked)
{
    if (checked) {
        qDebug() << "Payment method changed to PayPal";
        ui->paymentDetailsStack->setCurrentWidget(ui->payPalPage);
        clearError(); // Clear errors when switching method
    }
}

void ClientPaymentWidget::on_payByCardRadio_toggled(bool checked)
{
    if (checked) {
        qDebug() << "Payment method changed to Credit Card";
        ui->paymentDetailsStack->setCurrentWidget(ui->cardPaymentPage);
        clearError(); // Clear errors when switching method
    }
}

void ClientPaymentWidget::on_payByBankTransferRadio_toggled(bool checked)
{
    if (checked) {
        qDebug() << "Payment method changed to Bank Transfer";
        ui->paymentDetailsStack->setCurrentWidget(ui->bankTransferPage);
        clearError(); // Clear errors when switching method
    }
}

// Optional Slot for a dedicated PayPal Button within the PayPalPage QWidget
// void ClientPaymentWidget::initiatePayPalPayment() // Renamed from on_payPalPayButton_clicked
// {
//    qDebug() << "Dedicated PayPal button clicked";
//    // This might skip the main "Proceed" button and directly call PayPal processing
//    handlePaymentProcessing(); // Or call processPayPalPayment() directly if appropriate
// }
