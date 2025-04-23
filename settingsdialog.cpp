#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include <QTableWidgetItem>
#include <QItemSelectionModel>
#include <QStringList>
#include <algorithm>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // --- Configure widgets using CORRECT camelCase names ---
    ui->VATRatesTable->setColumnCount(1); // Assuming VATRatesTable is correct name
    ui->VATRatesTable->setHorizontalHeaderLabels({"Rate (%)"});
    ui->VATRatesTable->horizontalHeader()->setStretchLastSection(true);
    ui->VATRatesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->VATRatesTable->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->stripeApiKeyInput->setEchoMode(QLineEdit::Password); // Correct name
    ui->payPalSecretInput->setEchoMode(QLineEdit::Password); // Correct name

    setupConnections();
    loadSettings();

    updatePaymentGatewayState();
    updateReminderState();
    updateIotState();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setupConnections()
{
    // Use CORRECT camelCase name for table
    connect(ui->VATRatesTable->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this](){
        // Use CORRECT camelCase name for button
        ui->removeVatRateButton->setEnabled(ui->VATRatesTable->selectionModel()->hasSelection());
    });
    // Auto-connections will handle slots matching on_camelCaseWidgetName_signalName
}

void SettingsDialog::loadSettings()
{
    qDebug() << "Loading settings...";
    QSettings settings("YourCompany", "SmartConsultingOffice");

    // --- Load values using CORRECT camelCase names ---
    ui->companyNameInput->setText(settings.value("Company/Name").toString()); // Corrected
    ui->companyAddressInput->setText(settings.value("Company/Address").toString()); // Corrected
    ui->companyVATIDInput->setText(settings.value("Company/VATID").toString()); // Corrected
    ui->companyLogoPathInput->setText(settings.value("Company/LogoPath").toString()); // Corrected

    ui->numberPrefixInput->setText(settings.value("Invoice/Prefix", "INV-").toString()); // Corrected
    ui->nextNumberSpinBox->setValue(settings.value("Invoice/NextNumber", 1).toInt()); // Corrected
    ui->defaultTermsComboBox->setCurrentText(settings.value("Invoice/DefaultTerms", "Net 30").toString()); // Corrected
    populateVatRatesTable();

    ui->enableRemindersCheckBox->setChecked(settings.value("Reminders/Enabled", false).toBool());
    ui->daysBeforeDueSpinBox->setValue(settings.value("Reminders/DaysBefore", 3).toInt());
    ui->daysAfterDueSpinBox_2->setValue(settings.value("Reminders/DaysAfter", 7).toInt());
    ui->enableOverdueIoTAlertCheckBox->setChecked(settings.value("IoT/Enabled", false).toBool());
    ui->ioTAlertDaysSpinBox->setValue(settings.value("IoT/AlertDays", 14).toInt());
    ui->ioTDeviceAddressInput->setText(settings.value("IoT/DeviceAddress").toString());

    // Use CORRECT camelCase name for combo box
    ui->templateSelectComboBox->clear();
    ui->templateSelectComboBox->addItem("New Invoice Email", "new_invoice");
    ui->templateSelectComboBox->addItem("Reminder Email", "reminder");
    ui->templateSelectComboBox->addItem("Overdue Notice Email", "overdue");
    if (ui->templateSelectComboBox->count() > 0) {
        loadEmailTemplate(0);
    }
    // Use CORRECT camelCase name for label
    ui->placeholdersInfoLabel->setText("Available: [ClientName], [InvoiceNumber], [DueDate], [AmountDue], [PaymentLink], [CompanyName]");

    ui->stripeEnableCheckBox->setChecked(settings.value("Payment/StripeEnabled", false).toBool());
    ui->stripeApiKeyInput->setText(settings.value("Payment/StripeApiKey").toString());
    ui->payPalEnableCheckBox->setChecked(settings.value("Payment/PayPalEnabled", false).toBool());
    ui->payPalClientIdInput->setText(settings.value("Payment/PayPalClientID").toString()); // Corrected
    ui->payPalSecretInput->setText(settings.value("Payment/PayPalSecret").toString());

    // Use CORRECT camelCase name for button
    ui->removeVatRateButton->setEnabled(false);
}

void SettingsDialog::saveSettings()
{
    qDebug() << "Saving settings...";
    QSettings settings("YourCompany", "SmartConsultingOffice");

    // --- Save values using CORRECT camelCase names ---
    settings.setValue("Company/Name", ui->companyNameInput->text()); // Corrected
    settings.setValue("Company/Address", ui->companyAddressInput->text()); // Corrected
    settings.setValue("Company/VATID", ui->companyVATIDInput->text()); // Corrected
    settings.setValue("Company/LogoPath", ui->companyLogoPathInput->text()); // Corrected

    settings.setValue("Invoice/Prefix", ui->numberPrefixInput->text()); // Corrected
    settings.setValue("Invoice/NextNumber", ui->nextNumberSpinBox->value()); // Corrected
    settings.setValue("Invoice/DefaultTerms", ui->defaultTermsComboBox->currentText()); // Corrected
    QStringList vatList;
    for(int row = 0; row < ui->VATRatesTable->rowCount(); ++row) {
        QTableWidgetItem *item = ui->VATRatesTable->item(row, 0);
        if (item) { vatList << item->text(); }
    }
    settings.setValue("Invoice/VATRates", vatList.join(','));

    settings.setValue("Reminders/Enabled", ui->enableRemindersCheckBox->isChecked());
    settings.setValue("Reminders/DaysBefore", ui->daysBeforeDueSpinBox->value());
    settings.setValue("Reminders/DaysAfter", ui->daysAfterDueSpinBox_2->value());
    settings.setValue("IoT/Enabled", ui->enableOverdueIoTAlertCheckBox->isChecked());
    settings.setValue("IoT/AlertDays", ui->ioTAlertDaysSpinBox->value());
    settings.setValue("IoT/DeviceAddress", ui->ioTDeviceAddressInput->text());

    // Use CORRECT camelCase name for combo box
    saveEmailTemplate(ui->templateSelectComboBox->currentIndex());

    settings.setValue("Payment/StripeEnabled", ui->stripeEnableCheckBox->isChecked());
    settings.setValue("Payment/StripeApiKey", ui->stripeApiKeyInput->text());
    settings.setValue("Payment/PayPalEnabled", ui->payPalEnableCheckBox->isChecked());
    settings.setValue("Payment/PayPalClientID", ui->payPalClientIdInput->text()); // Corrected
    settings.setValue("Payment/PayPalSecret", ui->payPalSecretInput->text());

    qDebug() << "Settings saved.";
}

void SettingsDialog::updatePaymentGatewayState()
{
    // Use CORRECT camelCase names
    ui->stripeApiKeyInput->setEnabled(ui->stripeEnableCheckBox->isChecked());
    ui->payPalClientIdInput->setEnabled(ui->payPalEnableCheckBox->isChecked()); // Corrected
    ui->payPalSecretInput->setEnabled(ui->payPalEnableCheckBox->isChecked());
}

void SettingsDialog::updateReminderState()
{
    // Use CORRECT camelCase names
    bool enabled = ui->enableRemindersCheckBox->isChecked();
    ui->daysBeforeDueSpinBox->setEnabled(enabled);
    ui->daysAfterDueSpinBox_2->setEnabled(enabled);
}

void SettingsDialog::updateIotState()
{
    // Use CORRECT camelCase names
    bool enabled = ui->enableOverdueIoTAlertCheckBox->isChecked();
    ui->ioTAlertDaysSpinBox->setEnabled(enabled);
    ui->ioTDeviceAddressInput->setEnabled(enabled);
}

void SettingsDialog::loadEmailTemplate(int index)
{
    // Use CORRECT camelCase name for combo box
    if (index < 0 || index >= ui->templateSelectComboBox->count()) return;
    QString templateKey = ui->templateSelectComboBox->itemData(index).toString();
    if (templateKey.isEmpty()) return;

    qDebug() << "Loading email template for key:" << templateKey;
    QSettings settings("YourCompany", "SmartConsultingOffice");
    // Use CORRECT camelCase names for Subject/Body inputs
    ui->subjectInput->setText(settings.value(QString("Email/%1/Subject").arg(templateKey), "Default Subject").toString()); // Corrected
    ui->bodyInput->setPlainText(settings.value(QString("Email/%1/Body").arg(templateKey), "Default email body.").toString()); // Corrected
}

void SettingsDialog::saveEmailTemplate(int index)
{
    // Use CORRECT camelCase name for combo box
    if (index < 0 || index >= ui->templateSelectComboBox->count()) return;
    QString templateKey = ui->templateSelectComboBox->itemData(index).toString();
    if (templateKey.isEmpty()) return;

    qDebug() << "Saving email template for key:" << templateKey;
    QSettings settings("YourCompany", "SmartConsultingOffice");
    // Use CORRECT camelCase names for Subject/Body inputs
    settings.setValue(QString("Email/%1/Subject").arg(templateKey), ui->subjectInput->text()); // Corrected
    settings.setValue(QString("Email/%1/Body").arg(templateKey), ui->bodyInput->toPlainText()); // Corrected
}

void SettingsDialog::populateVatRatesTable()
{
    ui->VATRatesTable->setRowCount(0); // Clear existing
    QSettings settings("YourCompany", "SmartConsultingOffice");
    QStringList vatList = settings.value("Invoice/VATRates").toString().split(',', Qt::SkipEmptyParts);
    for(const QString& rate : vatList) {
        int newRow = ui->VATRatesTable->rowCount();
        ui->VATRatesTable->insertRow(newRow);
        ui->VATRatesTable->setItem(newRow, 0, new QTableWidgetItem(rate));
    }
}

// --- Slots Implementation (using camelCase names where needed) ---

void SettingsDialog::on_saveButton_clicked()
{
    saveSettings();
    accept();
}

void SettingsDialog::on_cancelButton_clicked()
{
    reject();
}

void SettingsDialog::on_BrowseButton_clicked() // Assuming PascalCase name is correct here
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Select Logo Image",
        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!filePath.isEmpty()) {
        ui->companyLogoPathInput->setText(filePath); // Use CORRECT camelCase name
    }
}

void SettingsDialog::on_addVatRateButton_clicked()
{
    int newRow = ui->VATRatesTable->rowCount();
    ui->VATRatesTable->insertRow(newRow);
    ui->VATRatesTable->setItem(newRow, 0, new QTableWidgetItem("0.0"));
    ui->VATRatesTable->editItem(ui->VATRatesTable->item(newRow, 0));
}

void SettingsDialog::on_removeVatRateButton_clicked()
{
    QModelIndexList selectedRows = ui->VATRatesTable->selectionModel()->selectedRows();
    std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex& a, const QModelIndex& b) {
        return a.row() > b.row();
    });
    for (const QModelIndex &index : selectedRows) {
        ui->VATRatesTable->removeRow(index.row());
    }
}

// Slots matching camelCase object names
void SettingsDialog::on_stripeEnableCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    updatePaymentGatewayState();
}

void SettingsDialog::on_payPalEnableCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    updatePaymentGatewayState();
}

void SettingsDialog::on_enableRemindersCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    updateReminderState();
}

void SettingsDialog::on_enableOverdueIoTAlertCheckBox_toggled(bool checked)
{
    Q_UNUSED(checked);
    updateIotState();
}

// Slot matching camelCase object name
void SettingsDialog::on_templateSelectComboBox_currentIndexChanged(int index)
{
    loadEmailTemplate(index);
}
