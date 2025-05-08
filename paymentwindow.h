#ifndef PAYMENTWINDOW_H
#define PAYMENTWINDOW_H

#include <QDialog>
#include <QString>
#include <QDateTime> // <--- ADD THIS LINE

// Forward declaration if using QButtonGroup in .cpp
class QButtonGroup;

namespace Ui {
class PaymentWindow;
}

class PaymentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentWindow(QWidget *parent = nullptr);
    ~PaymentWindow();

private slots:
    // --- Page 1: Booking ---
    void on_pushButtonContinue_clicked();
    void on_pushButtonCancelBooking_clicked();

    // --- Page 2: Confirmation ---
    void on_pushButtonProceedToPay_clicked();
    void on_pushButtonBackConfirm_clicked();

    // --- Page 3: Credit Card ---
    void on_pushButtonSubmitPayment_clicked();
    void on_pushButtonBackCard_clicked();

    // --- Page 4: PayPal ---
    void on_pushButtonProceedPayPal_clicked();
    void on_pushButtonBackPayPal_clicked();

    // --- Page 5: Bank Transfer ---
    void on_pushButtonConfirmTransfer_clicked();
    void on_pushButtonBackBank_clicked();

    // --- Page 7: Status ---
    void on_pushButtonGenerateInvoice_clicked();
    void on_pushButtonBookAnother_clicked();
    void on_pushButtonTryAgain_clicked();
    void on_pushButtonCloseStatus_clicked();

private:
    // Helper methods
    void loadStyleSheet();
    void addIcons();
    bool validateBookingInput();
    void populateConfirmationPage();
    void processPayment(const QString& method); // Simulate payment
    void handlePaymentResult(bool success); // Update Status page UI

    Ui::PaymentWindow *ui;
    QButtonGroup *paymentMethodGroup; // Optional, for easier radio button handling

    // Member variables to store data between pages
    QString m_fullName;
    QString m_email;
    QString m_phone;
    QString m_consultationType;
    double  m_amount;
    QDateTime m_appointmentDateTime; // Line 67 (now the compiler knows its definition)
    QString m_selectedPaymentMethod;
};

#endif // PAYMENTWINDOW_H
