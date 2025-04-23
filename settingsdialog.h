#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots: // <<< Make sure it's inside this section (or public/protected slots)
    // --- Slots matching objectNames from Object Inspector ---

    void on_saveButton_clicked();
    void on_cancelButton_clicked();

    // Company Info Tab
    void on_BrowseButton_clicked(); // <<< ADD THIS LINE HERE

    // Invoice Options Tab
    void on_addVatRateButton_clicked();
    void on_removeVatRateButton_clicked();

    // Payment Gateways Tab - Checkboxes
    void on_stripeEnableCheckBox_toggled(bool checked);
    void on_payPalEnableCheckBox_toggled(bool checked);

    // Email Templates Tab
    void on_templateSelectComboBox_currentIndexChanged(int index); // Corrected name

    // Reminders/IoT Checkboxes (Invoice Options Tab)
    void on_enableRemindersCheckBox_toggled(bool checked);
    void on_enableOverdueIoTAlertCheckBox_toggled(bool checked);

private:
    Ui::SettingsDialog *ui;

    // Helper functions
    void loadSettings();
    void saveSettings();
    void setupConnections();
    void updatePaymentGatewayState();
    void updateReminderState();
    void updateIotState();
    void loadEmailTemplate(int index);
    void saveEmailTemplate(int index);
    void populateVatRatesTable();
};

#endif // SETTINGSDIALOG_H
