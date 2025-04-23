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
    enum PaymentMethod {
        Unknown,
        PayPal,
        CreditCard,
        BankTransfer
    };

    explicit ClientPaymentWidget(QWidget *parent = nullptr);
    ~ClientPaymentWidget();

    // --- Public Methods to Set Data ---
    void setInvoiceDetails(const QString& invoiceNumber, const QString& amountDue,
                           const QString& issueDate, const QString& dueDate);
    void setWelcomeMessage(const QString& clientName);
    // Removed setBankTransferInfo as it's now handled internally


private slots:
    // --- Slots for UI elements (Auto-connected or manually connected) ---
    void on_proceedToPaymentButton_clicked();
    void on_downloadPdfButton_clicked(); // <<< ADDED DECLARATION
    void on_payByPayPalRadio_toggled(bool checked); // <<< ADDED DECLARATION
    void on_payByCardRadio_toggled(bool checked); // <<< ADDED DECLARATION
    void on_payByBankTransferRadio_toggled(bool checked); // <<< ADDED DECLARATION

    // Optional slot for custom PayPal button if you add one
    // void initiatePayPalPayment(); // Renamed from on_payPalPayButton_clicked

private:
    // --- Helper Methods (Declarations) ---
    void updateBankTransferInfoDisplay();
    bool validateCardDetails();
    void handlePaymentProcessing();
    void processPayPalPayment();        // <<< ADDED DECLARATION
    void processCreditCardPayment();    // <<< ADDED DECLARATION
    void processBankTransfer();         // <<< ADDED DECLARATION
    void showError(const QString &message); // <<< ADDED DECLARATION
    void clearError();                  // <<< ADDED DECLARATION
    void resetPaymentUiState();         // <<< ADDED DECLARATION

    // --- Member Variables ---
    Ui::ClientPaymentWidget *ui; // Pointer to UI elements

    QString m_invoiceNumber;    // <<< ADDED DECLARATION
    QString m_amountDueStr;     // <<< ADDED DECLARATION

    // int currentInvoiceId; // Removed if not needed for loadInvoiceDetails pattern
};

#endif // CLIENTPAYMENTWIDGET_H
