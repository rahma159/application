#ifndef CLIENTPAYMENTWIDGET_H
#define CLIENTPAYMENTWIDGET_H

#include <QDialog>
#include <QString> // Include QString

// Forward declaration of the UI class
namespace Ui {
class ClientPaymentWidget;
}

class ClientPaymentWidget : public QDialog
{
    Q_OBJECT // Essential for signals/slots

public:
    // Enum defined within the class scope (or outside if preferred)
    // Enum to represent the selected payment method internally
    enum PaymentMethod {
        Unknown,
        PayPal,
        CreditCard,
        BankTransfer
    };

    explicit ClientPaymentWidget(QWidget *parent = nullptr);
    ~ClientPaymentWidget();

    // --- Public Methods to Set Data ---
    // Sets the invoice details displayed in the summary section
    void setInvoiceDetails(const QString& invoiceNumber, const QString& amountDue,
                           const QString& issueDate, const QString& dueDate);
    // Sets the personalized welcome message
    void setWelcomeMessage(const QString& clientName);


private slots:
    // --- Slots for UI elements (Auto-connected via on_ObjectName_SignalName) ---

    // Triggered when the main "Proceed To Payment" button is clicked
    void on_proceedToPaymentButton_clicked();

    // Triggered when the "Download PDF" button is clicked
    void on_downloadPdfButton_clicked();

    // Triggered when the PayPal radio button state changes
    void on_payByPayPalRadio_toggled(bool checked);

    // Triggered when the Credit Card radio button state changes
    void on_payByCardRadio_toggled(bool checked);

    // Triggered when the Bank Transfer radio button state changes
    void on_payByBankTransferRadio_toggled(bool checked);

    void on_payPalPayButton_clicked();
    void on_editBankDetailsButton_clicked();
    void on_saveBankDetailsButton_clicked();
    void on_cancelEditBankDetailsButton_clicked();

private:
    QString m_bankName;
    QString m_accountHolder;
    QString m_iban;
    QString m_bic;

    void updateBankTransferInfoDisplay();
    // Validates the input fields on the credit card form
    bool validateCardDetails();
    // Central method to handle the payment flow based on selected method
    void handlePaymentProcessing();
    // Contains logic specific to PayPal payment (simulation/integration)
    void processPayPalPayment();
    // Contains logic specific to Credit Card payment (validation/simulation/integration)
    void processCreditCardPayment();
    // Contains logic specific to Bank Transfer instructions/confirmation
    void processBankTransfer();
    // Displays an error message in the designated label
    void showError(const QString &message);
    // Clears any currently displayed error message
    void clearError();
    // Resets the progress bar and re-enables the payment button
    void resetPaymentUiState();
    bool simulateBackendPayPalOrderCreation(QString& approvalUrl, QString& errorMsg);
    // --- Member Variables ---
    Ui::ClientPaymentWidget *ui; // Pointer to the UI elements created in Qt Designer

    // Store invoice details for potential use in payment processing (e.g., reference)
    QString m_invoiceNumber;
    QString m_amountDueStr; // Store amount string for potential gateway use

    void loadBankDetailsToEditFields();
};

#endif // CLIENTPAYMENTWIDGET_H
