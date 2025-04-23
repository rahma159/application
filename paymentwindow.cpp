#include "paymentwindow.h"
#include "ui_paymentwindow.h"

#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QString>
#include <QDebug>     // For printing messages
#include <QStyle>     // For standard icons
#include <QButtonGroup> // Include if using QButtonGroup
#include <QMessageBox>// For warnings/info
#include <QRegularExpressionValidator> // For input validation
#include <QRegularExpression>
#include <QTimer>     // For simulating delay

PaymentWindow::PaymentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentWindow),
    paymentMethodGroup(nullptr), // Initialize pointer
    m_amount(0.0) // Initialize amount
{
    ui->setupUi(this);
    this->setWindowTitle("Appointment Payment");

    loadStyleSheet(); // Apply specific styles if not globally applied
    addIcons();       // Add icons to buttons

    // --- Input Validation Example (Email) ---
    // Requires QRegularExpression include
    QRegularExpression emailRegex("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,}\\b", QRegularExpression::CaseInsensitiveOption);
    QValidator *emailValidator = new QRegularExpressionValidator(emailRegex, this);
    ui->lineEditEmail->setValidator(emailValidator);
    // Add validators for phone, card numbers, etc. as needed

    // --- Setup Payment Method Radio Group (Optional but recommended) ---
    paymentMethodGroup = new QButtonGroup(this);
    paymentMethodGroup->addButton(ui->radioButtonPayPal);
    paymentMethodGroup->addButton(ui->radioButtonCreditCard);
    paymentMethodGroup->addButton(ui->radioButtonBankTransfer);
    // paymentMethodGroup->setExclusive(true); // Default for radio buttons in designer

    // --- Set initial state ---
    ui->stackedWidget->setCurrentWidget(ui->pageBooking); // Start on the first page



    // Inside PaymentWindow constructor:
    QGraphicsDropShadowEffect* shadowEffectPersonalInfo = new QGraphicsDropShadowEffect(this);
    shadowEffectPersonalInfo->setBlurRadius(15);
    shadowEffectPersonalInfo->setColor(QColor(0, 0, 0, 70)); // Adjust color/opacity
    shadowEffectPersonalInfo->setOffset(0, 2); // Slight vertical offset
    ui->groupBoxPersonalInfo->setGraphicsEffect(shadowEffectPersonalInfo); // Apply to the specific groupbox

    QGraphicsDropShadowEffect* shadowEffectApptDetails = new QGraphicsDropShadowEffect(this);
    shadowEffectApptDetails->setBlurRadius(15);
    shadowEffectApptDetails->setColor(QColor(0, 0, 0, 70));
    shadowEffectApptDetails->setOffset(0, 2);
    ui->groupBoxAppointmentDetails->setGraphicsEffect(shadowEffectApptDetails);

    // Repeat for: groupBoxSummary, groupBoxPaymentMethod, groupBoxCreditCardInput,
    //             groupBoxBankDetails, groupBoxTransactionSummary
    // Create a new effect instance for each widget you apply it to!
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
    // paymentMethodGroup is deleted automatically due to parent 'this'
}

// --- Helper Functions ---

void PaymentWindow::loadStyleSheet()
{
    // Apply stylesheet specifically to this window if not applied globally in main.cpp
    QFile styleSheetFile(":/Styles/style.qss");
    if (styleSheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        this->setStyleSheet(styleSheet);
        styleSheetFile.close();
    } else {
        qWarning("Could not open paymentwindow stylesheet file!");
    }
}

void PaymentWindow::addIcons()
{
    // Use standard Qt icons (copy code from previous answer here)
    ui->pushButtonContinue->setIcon(this->style()->standardIcon(QStyle::SP_ArrowRight));
    ui->pushButtonCancelBooking->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));
    ui->pushButtonProceedToPay->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->pushButtonBackConfirm->setIcon(this->style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->pushButtonSubmitPayment->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->pushButtonBackCard->setIcon(this->style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->pushButtonProceedPayPal->setIcon(this->style()->standardIcon(QStyle::SP_ArrowRight));
    ui->pushButtonBackPayPal->setIcon(this->style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->pushButtonConfirmTransfer->setIcon(this->style()->standardIcon(QStyle::SP_DialogApplyButton));
    ui->pushButtonBackBank->setIcon(this->style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->pushButtonGenerateInvoice->setIcon(this->style()->standardIcon(QStyle::SP_FileLinkIcon));
    ui->pushButtonBookAnother->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload)); // Changed icon
    ui->pushButtonTryAgain->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->pushButtonCloseStatus->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
}

bool PaymentWindow::validateBookingInput()
{
    bool valid = true;
    QString errorMsg;

    // Basic checks - enhance as needed
    if (ui->lineEditFullName->text().trimmed().isEmpty()) {
        errorMsg += "Full Name cannot be empty.\n";
        valid = false;
    }
    if (!ui->lineEditEmail->hasAcceptableInput()) {
        errorMsg += "Email address is not valid.\n";
        valid = false;
    }
    if (ui->lineEditPhone->text().trimmed().isEmpty()) { // Add more specific phone validation
        errorMsg += "Phone number cannot be empty.\n";
        valid = false;
    }
    if (ui->comboBoxConsultationType->currentIndex() < 0) { // Assuming first item isn't a placeholder
        errorMsg += "Please select a Consultation Type.\n";
        valid = false;
    }
    // Check if date/time is in the past?
    if (ui->dateTimeEditAppointment->dateTime() <= QDateTime::currentDateTime()) {
        errorMsg += "Appointment date must be in the future.\n";
        valid = false;
    }


    if (!valid) {
        QMessageBox::warning(this, "Input Error", errorMsg);
    }
    return valid;
}

void PaymentWindow::populateConfirmationPage()
{
    // Retrieve data from input fields and store in members
    m_fullName = ui->lineEditFullName->text().trimmed();
    m_email = ui->lineEditEmail->text().trimmed();
    m_phone = ui->lineEditPhone->text().trimmed();
    m_consultationType = ui->comboBoxConsultationType->currentText();
    m_appointmentDateTime = ui->dateTimeEditAppointment->dateTime();

    // --- Determine Amount (Example Logic) ---
    // Replace with your actual pricing logic
    if (m_consultationType == "Initial Consultation") {
        m_amount = 150.00;
    } else if (m_consultationType == "Follow-up") {
        m_amount = 75.00;
    } else if (m_consultationType == "Extended Session") {
        m_amount = 250.00;
    } else {
        m_amount = 0.00; // Default or handle error
    }

    // Set text on confirmation page labels
    ui->labelSummaryName->setText(m_fullName);
    ui->labelSummaryEmail->setText(m_email);
    ui->labelSummaryPhone->setText(m_phone);
    ui->labelSummaryConsultation->setText(m_consultationType);
    ui->labelSummaryDate->setText(m_appointmentDateTime.toString("yyyy-MM-dd hh:mm"));
    ui->labelSummaryAmount->setText(QString("£%1").arg(m_amount, 0, 'f', 2)); // Format as currency
}

// --- Slots for Button Clicks ---

// Page 1
void PaymentWindow::on_pushButtonContinue_clicked()
{
    if (validateBookingInput()) {
        populateConfirmationPage();
        ui->stackedWidget->setCurrentWidget(ui->pageConfirmation);
    }
}

void PaymentWindow::on_pushButtonCancelBooking_clicked()
{
    reject(); // Close the dialog indicating cancellation
}

// Page 2
void PaymentWindow::on_pushButtonProceedToPay_clicked()
{
    if (ui->radioButtonCreditCard->isChecked()) {
        m_selectedPaymentMethod = "Credit Card";
        ui->stackedWidget->setCurrentWidget(ui->pageCreditCard);
    } else if (ui->radioButtonPayPal->isChecked()) {
        m_selectedPaymentMethod = "PayPal";
        ui->stackedWidget->setCurrentWidget(ui->pagePayPal);
    } else if (ui->radioButtonBankTransfer->isChecked()) {
        m_selectedPaymentMethod = "Bank Transfer";
        // Populate the booking ID on the bank transfer page (example)
        ui->labelReferenceValue->setText("BOOKING_" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss")); // Example ID
        ui->stackedWidget->setCurrentWidget(ui->pageBankTransfer);
    } else {
        QMessageBox::warning(this, "Payment Method", "Please select a payment method.");
    }
}

void PaymentWindow::on_pushButtonBackConfirm_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageBooking);
}

// Page 3
void PaymentWindow::on_pushButtonSubmitPayment_clicked()
{
    // Add validation for credit card fields here!
    bool cardValid = true; // Placeholder
    if (!cardValid) {
        QMessageBox::warning(this, "Input Error", "Please check credit card details.");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->pageProcessing); // Show processing page
    QTimer::singleShot(1500, this, [this](){ processPayment("Credit Card"); }); // Simulate 1.5 sec delay
}

void PaymentWindow::on_pushButtonBackCard_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageConfirmation);
}

// Page 4
void PaymentWindow::on_pushButtonProceedPayPal_clicked()
{
    // Simulate redirection & processing
    ui->stackedWidget->setCurrentWidget(ui->pageProcessing);
    QTimer::singleShot(2000, this, [this](){ processPayment("PayPal"); }); // Simulate 2 sec delay
}

void PaymentWindow::on_pushButtonBackPayPal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageConfirmation);
}

// Page 5
void PaymentWindow::on_pushButtonConfirmTransfer_clicked()
{
    // This likely wouldn't trigger immediate success, maybe a "Pending" status
    QMessageBox::information(this, "Bank Transfer",
                             "Thank you. Your booking is pending until payment is confirmed.\n"
                             "Please ensure you use the provided reference.");
    // For this example, we'll simulate immediate success/failure after a short delay
    ui->stackedWidget->setCurrentWidget(ui->pageProcessing);
    QTimer::singleShot(500, this, [this](){ processPayment("Bank Transfer"); });
}

void PaymentWindow::on_pushButtonBackBank_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageConfirmation);
}

// --- Payment Processing Simulation ---

void PaymentWindow::processPayment(const QString& method)
{
    qDebug() << "Processing payment via:" << method;
    // Simulate success/failure (e.g., 80% success rate)
    bool success = (rand() % 10) < 8; // Simple random success

    // Add more realistic simulation if needed (e.g., fail specific card numbers)

    handlePaymentResult(success);
}

// --- Update Status Page UI ---

void PaymentWindow::handlePaymentResult(bool success)
{
    ui->stackedWidget->setCurrentWidget(ui->pageStatus); // Go to status page

    QString transactionId = "TXN" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"); // Example ID


    // Inside handlePaymentResult(bool success) in paymentwindow.cpp
    if (success) {
        ui->labelStatusMessage->setText("Payment Successful!");
        // Success: Green text on light green background
        ui->labelStatusMessage->setStyleSheet(
            "color: #155724;"             // Dark Green Text
            "background-color: #D4EDDA;" // Light Green Background
            "border: 1px solid #C3E6CB;" // Matching border
            "font-size: 22pt; font-weight: 600; border-radius: 8px; padding: 20px;" // Keep other styles
            );
        ui->labelStatusMessage->setText("Payment Successful!");
        ui->labelStatusMessage->setStyleSheet("color: #4CAF50; font-size: 18pt; font-weight: bold; background-color: transparent;"); // Green

        // Populate details
        ui->labelTransactionIdValue->setText(transactionId);
        ui->labelPaymentMethodValue->setText(m_selectedPaymentMethod);
        ui->labelAmountPaidValue->setText(QString("£%1").arg(m_amount, 0, 'f', 2));
        ui->labelTransactionTimestampValue->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        // Show/Hide Success buttons/info
        ui->groupBoxTransactionSummary->setVisible(true);
        ui->pushButtonGenerateInvoice->setVisible(true);
        ui->pushButtonBookAnother->setVisible(true);
        ui->pushButtonCloseStatus->setVisible(true);
        ui->pushButtonTryAgain->setVisible(false); // Hide Try Again
        // ... rest of success logic ...
    } else {
        ui->labelStatusMessage->setText("Payment Failed!");
        // Failure: Red text on light red background
        ui->labelStatusMessage->setStyleSheet(
            "color: #721C24;"             // Dark Red Text
            "background-color: #F8D7DA;" // Light Red Background
            "border: 1px solid #F5C6CB;" // Matching border
            "font-size: 22pt; font-weight: 600; border-radius: 8px; padding: 20px;" // Keep other styles
            );
            // ... rest of failure logic ...
        ui->labelStatusMessage->setText("Payment Failed!");
        ui->labelStatusMessage->setStyleSheet("color: #F44336; font-size: 18pt; font-weight: bold; background-color: transparent;"); // Red

        // Show/Hide Failure buttons/info
        ui->groupBoxTransactionSummary->setVisible(false); // Hide details on failure
        ui->pushButtonGenerateInvoice->setVisible(false); // Hide Invoice
        // Decide if booking another makes sense on failure
        ui->pushButtonBookAnother->setVisible(false); // Example: Hide book another
        ui->pushButtonCloseStatus->setVisible(true); // Still allow closing
        ui->pushButtonTryAgain->setVisible(true); // Show Try Again
    }


}

// Page 7 Buttons
void PaymentWindow::on_pushButtonGenerateInvoice_clicked()
{
    QMessageBox::information(this, "Invoice", "Invoice generation is not implemented yet.");
    // Add actual invoice generation logic here (e.g., create PDF)
}

void PaymentWindow::on_pushButtonBookAnother_clicked()
{
    // Reset relevant fields on page 1 and go back
    ui->lineEditFullName->clear();
    ui->lineEditEmail->clear();
    ui->lineEditPhone->clear();
    ui->comboBoxConsultationType->setCurrentIndex(-1); // Or 0 if you have a placeholder
    ui->dateTimeEditAppointment->setDateTime(QDateTime::currentDateTime().addDays(1)); // Default to tomorrow
    ui->stackedWidget->setCurrentWidget(ui->pageBooking);
}

void PaymentWindow::on_pushButtonTryAgain_clicked()
{
    // Go back to the confirmation page to allow selecting method again
    // or potentially back to the specific payment page if you stored which one failed
    ui->stackedWidget->setCurrentWidget(ui->pageConfirmation);
}

void PaymentWindow::on_pushButtonCloseStatus_clicked()
{
    if(ui->pushButtonGenerateInvoice->isVisible()) { // Crude check for success state
        accept(); // Indicate success / completion
    } else {
        reject(); // Indicate failure / cancellation from status page
    }
}
