#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMapIterator>
#include <QFileInfo>

// Constants for settings keys
namespace {
// Company Info
const QString KEY_COMPANY_NAME = QStringLiteral("CompanyInfo/Name");
const QString KEY_COMPANY_ADDRESS = QStringLiteral("CompanyInfo/Address");
const QString KEY_COMPANY_VATID = QStringLiteral("CompanyInfo/VATID");
const QString KEY_COMPANY_LOGO_PATH = QStringLiteral("CompanyInfo/LogoPath");

// Invoice Options
const QString KEY_INVOICE_PREFIX = QStringLiteral("InvoiceOptions/NumberPrefix");
const QString KEY_INVOICE_NEXT_NUMBER = QStringLiteral("InvoiceOptions/NextNumber");
const QString KEY_INVOICE_DEFAULT_TERMS = QStringLiteral("InvoiceOptions/DefaultTerms");
const QString KEY_INVOICE_VAT_RATES_JSON = QStringLiteral("InvoiceOptions/VATRatesJSON");
const QString KEY_INVOICE_REMINDERS_BEFORE_DUE = QStringLiteral("InvoiceOptions/RemindersBeforeDue");
const QString KEY_INVOICE_REMINDERS_AFTER_DUE = QStringLiteral("InvoiceOptions/RemindersAfterDue");
const QString KEY_INVOICE_ENABLE_REMINDERS = QStringLiteral("InvoiceOptions/EnableReminders");
const QString KEY_INVOICE_ALERT_DAYS = QStringLiteral("InvoiceOptions/IoTAlertDays");
const QString KEY_INVOICE_ENABLE_IOT_ALERT = QStringLiteral("InvoiceOptions/EnableIoTAlert");
const QString KEY_INVOICE_IOT_DEVICE_ADDRESS = QStringLiteral("InvoiceOptions/IoTDeviceAddress");

// Payment Gateways
const QString KEY_PAYMENT_STRIPE_ENABLE = QStringLiteral("PaymentGateways/StripeEnable");
const QString KEY_PAYMENT_STRIPE_API_KEY = QStringLiteral("PaymentGateways/StripeApiKey");
const QString KEY_PAYMENT_PAYPAL_ENABLE = QStringLiteral("PaymentGateways/PayPalEnable");
const QString KEY_PAYMENT_PAYPAL_CLIENT_ID = QStringLiteral("PaymentGateways/PayPalClientID");
const QString KEY_PAYMENT_PAYPAL_SECRET = QStringLiteral("PaymentGateways/PayPalSecret");

// Email Templates
const QString KEY_EMAIL_TEMPLATE_PREFIX = QStringLiteral("EmailTemplates/");
}

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    m_previousTemplateIndex(-1),
    m_loadingSettings(false)
{
    ui->setupUi(this);
    setWindowTitle(tr("Application Settings"));

    // Load stylesheet
    QFile styleFile(":/styles/settings_style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        setStyleSheet(styleFile.readAll());
    }

    // Configure VAT rates table
    ui->VATRatesTable->setColumnCount(2);
    ui->VATRatesTable->setHorizontalHeaderLabels({tr("Description"), tr("Rate (%)")});
    ui->VATRatesTable->horizontalHeader()->setSectionResizeMode(VAT_DESCRIPTION_COL, QHeaderView::Stretch);
    ui->VATRatesTable->horizontalHeader()->setSectionResizeMode(VAT_RATE_COL, QHeaderView::ResizeToContents);

    // Setup templates combo box
    ui->templateSelectComboBox->clear();
    ui->templateSelectComboBox->addItem(tr("New Invoice"), QStringLiteral("NewInvoice"));
    ui->templateSelectComboBox->addItem(tr("Payment Reminder"), QStringLiteral("PaymentReminder"));
    ui->templateSelectComboBox->addItem(tr("Overdue Notice"), QStringLiteral("OverdueNotice"));
    ui->templateSelectComboBox->addItem(tr("Payment Confirmation"), QStringLiteral("PaymentConfirmation"));

    // Setup default terms
    ui->defaultTermsComboBox->clear();
    ui->defaultTermsComboBox->addItems({tr("Net 30"), tr("Net 15"), tr("Due on Receipt"), tr("Custom")});

    // Connect signals
    connect(ui->templateSelectComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SettingsDialog::on_templateSelectComboBox_currentIndexChanged);

    // Load settings
    loadSettingsFromDb();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

// Static methods implementation
QString SettingsDialog::getSetting(const QString& key, const QString& defaultValue)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database not open for key:" << key;
        return defaultValue;
    }

    QSqlQuery query(db);
    query.prepare("SELECT SETTING_VALUE FROM APPLICATION_SETTINGS WHERE SETTING_KEY = :key");
    query.bindValue(":key", key);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    if (query.lastError().isValid()) {
        qWarning() << "Query failed for key" << key << ":" << query.lastError().text();
    }

    return defaultValue;
}

int SettingsDialog::getSettingInt(const QString& key, int defaultValue)
{
    bool ok;
    int val = getSetting(key, QString::number(defaultValue)).toInt(&ok);
    return ok ? val : defaultValue;
}

bool SettingsDialog::getSettingBool(const QString& key, bool defaultValue)
{
    QString valStr = getSetting(key, defaultValue ? "true" : "false").toLower();
    return (valStr == "true" || valStr == "1");
}

bool SettingsDialog::setSetting(const QString& key, const QVariant& value)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qWarning() << "Database not open for key:" << key;
        return false;
    }

    // Check if key exists
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM APPLICATION_SETTINGS WHERE SETTING_KEY = :key");
    checkQuery.bindValue(":key", key);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qWarning() << "Failed check query for key" << key << ":" << checkQuery.lastError().text();
        return false;
    }

    bool exists = checkQuery.value(0).toInt() > 0;
    QSqlQuery query(db);

    if (exists) {
        query.prepare("UPDATE APPLICATION_SETTINGS SET SETTING_VALUE = :value WHERE SETTING_KEY = :key");
    } else {
        query.prepare("INSERT INTO APPLICATION_SETTINGS (SETTING_KEY, SETTING_VALUE) VALUES (:key, :value)");
    }

    query.bindValue(":key", key);
    query.bindValue(":value", value.toString());

    if (!query.exec()) {
        qWarning() << "Failed to" << (exists ? "UPDATE" : "INSERT") << "setting" << key << ":" << query.lastError().text();
        return false;
    }

    return true;
}

void SettingsDialog::loadSettingsFromDb()
{
    m_loadingSettings = true;

    // Load simple fields
    ui->companyNameInput->setText(getSetting(KEY_COMPANY_NAME));
    ui->companyAddressInput->setText(getSetting(KEY_COMPANY_ADDRESS));
    ui->companyVATIDInput->setText(getSetting(KEY_COMPANY_VATID));
    ui->companyLogoPathInput->setText(getSetting(KEY_COMPANY_LOGO_PATH));
    ui->numberPrefixInput->setText(getSetting(KEY_INVOICE_PREFIX, "INV-"));
    ui->nextNumberSpinBox->setValue(getSettingInt(KEY_INVOICE_NEXT_NUMBER, 1));
    ui->defaultTermsComboBox->setCurrentText(getSetting(KEY_INVOICE_DEFAULT_TERMS, tr("Net 30")));
    ui->daysBeforeDueSpinBox->setValue(getSettingInt(KEY_INVOICE_REMINDERS_BEFORE_DUE, 3));
    ui->daysAfterDueSpinBox_2->setValue(getSettingInt(KEY_INVOICE_REMINDERS_AFTER_DUE, 7));
    ui->enableRemindersCheckBox->setChecked(getSettingBool(KEY_INVOICE_ENABLE_REMINDERS, false));
    ui->enableOverdueIoTAlertCheckBox->setChecked(getSettingBool(KEY_INVOICE_ENABLE_IOT_ALERT, false));
    ui->ioTAlertDaysSpinBox->setValue(getSettingInt(KEY_INVOICE_ALERT_DAYS, 15));
    ui->ioTDeviceAddressInput->setText(getSetting(KEY_INVOICE_IOT_DEVICE_ADDRESS));
    ui->stripeEnableCheckBox->setChecked(getSettingBool(KEY_PAYMENT_STRIPE_ENABLE, false));
    ui->stripeApiKeyInput->setText(getSetting(KEY_PAYMENT_STRIPE_API_KEY));
    ui->payPalEnableCheckBox->setChecked(getSettingBool(KEY_PAYMENT_PAYPAL_ENABLE, false));
    ui->payPalClientIdInput->setText(getSetting(KEY_PAYMENT_PAYPAL_CLIENT_ID));
    ui->payPalSecretInput->setText(getSetting(KEY_PAYMENT_PAYPAL_SECRET));

    // Load complex data
    loadVatRatesFromDb();
    loadAllEmailTemplatesFromDb();

    // Initialize template UI
    if (ui->templateSelectComboBox->count() > 0) {
        ui->templateSelectComboBox->setCurrentIndex(0);
        loadTemplateFromMapToUiByKey(ui->templateSelectComboBox->itemData(0).toString());
        m_previousTemplateIndex = 0;
    }

    m_loadingSettings = false;
}

bool SettingsDialog::saveSettingsToDb()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Cannot save settings: Database not connected."));
        return false;
    }

    if (!db.transaction()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Failed to start database transaction."));
        return false;
    }

    // Save current template edits
    int currentIndex = ui->templateSelectComboBox->currentIndex();
    if (currentIndex >= 0) {
        QString currentKey = ui->templateSelectComboBox->itemData(currentIndex).toString();
        saveUiContentToMap(currentKey);
    }

    bool allOk = true;
    auto saveField = [&](const QString& key, const QVariant& value) {
        if (!setSetting(key, value)) {
            allOk = false;
        }
    };

    // Save simple fields
    saveField(KEY_COMPANY_NAME, ui->companyNameInput->text());
    saveField(KEY_COMPANY_ADDRESS, ui->companyAddressInput->text());
    saveField(KEY_COMPANY_VATID, ui->companyVATIDInput->text());
    saveField(KEY_COMPANY_LOGO_PATH, ui->companyLogoPathInput->text());
    saveField(KEY_INVOICE_PREFIX, ui->numberPrefixInput->text());
    saveField(KEY_INVOICE_NEXT_NUMBER, ui->nextNumberSpinBox->value());
    saveField(KEY_INVOICE_DEFAULT_TERMS, ui->defaultTermsComboBox->currentText());
    saveField(KEY_INVOICE_REMINDERS_BEFORE_DUE, ui->daysBeforeDueSpinBox->value());
    saveField(KEY_INVOICE_REMINDERS_AFTER_DUE, ui->daysAfterDueSpinBox_2->value());
    saveField(KEY_INVOICE_ENABLE_REMINDERS, ui->enableRemindersCheckBox->isChecked());
    saveField(KEY_INVOICE_ENABLE_IOT_ALERT, ui->enableOverdueIoTAlertCheckBox->isChecked());
    saveField(KEY_INVOICE_ALERT_DAYS, ui->ioTAlertDaysSpinBox->value());
    saveField(KEY_INVOICE_IOT_DEVICE_ADDRESS, ui->ioTDeviceAddressInput->text());
    saveField(KEY_PAYMENT_STRIPE_ENABLE, ui->stripeEnableCheckBox->isChecked());
    saveField(KEY_PAYMENT_STRIPE_API_KEY, ui->stripeApiKeyInput->text());
    saveField(KEY_PAYMENT_PAYPAL_ENABLE, ui->payPalEnableCheckBox->isChecked());
    saveField(KEY_PAYMENT_PAYPAL_CLIENT_ID, ui->payPalClientIdInput->text());
    saveField(KEY_PAYMENT_PAYPAL_SECRET, ui->payPalSecretInput->text());

    // Save complex data
    allOk = saveVatRatesToDb() && allOk;
    allOk = saveAllEmailTemplatesToDb() && allOk;

    if (allOk) {
        if (!db.commit()) {
            QMessageBox::critical(this, tr("Database Error"),
                                  tr("Failed to commit settings: %1").arg(db.lastError().text()));
            db.rollback();
            return false;
        }
        QMessageBox::information(this, tr("Success"), tr("Settings saved successfully."));
        return true;
    } else {
        db.rollback();
        QMessageBox::warning(this, tr("Error"), tr("Some settings failed to save."));
        return false;
    }
}
// VAT Rates Handling
void SettingsDialog::loadVatRatesFromDb()
{
    ui->VATRatesTable->setRowCount(0);
    QString vatRatesJsonString = getSetting(KEY_INVOICE_VAT_RATES_JSON);

    if (vatRatesJsonString.isEmpty()) {
        return;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(vatRatesJsonString.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isArray()) {
        qWarning() << "Invalid VAT rates JSON format";
        return;
    }

    QJsonArray array = doc.array();
    ui->VATRatesTable->setRowCount(array.size());

    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        ui->VATRatesTable->setItem(i, VAT_DESCRIPTION_COL,
                                   new QTableWidgetItem(obj.value("description").toString()));
        ui->VATRatesTable->setItem(i, VAT_RATE_COL,
                                   new QTableWidgetItem(obj.value("rate").toString()));
    }
}

bool SettingsDialog::saveVatRatesToDb()
{
    QJsonArray vatArray;

    for (int i = 0; i < ui->VATRatesTable->rowCount(); ++i) {
        QJsonObject vatObject;
        vatObject["description"] = ui->VATRatesTable->item(i, VAT_DESCRIPTION_COL)->text();
        vatObject["rate"] = ui->VATRatesTable->item(i, VAT_RATE_COL)->text();
        vatArray.append(vatObject);
    }

    QJsonDocument doc(vatArray);
    return setSetting(KEY_INVOICE_VAT_RATES_JSON, QString::fromUtf8(doc.toJson()));
}

// Email Templates Handling
void SettingsDialog::loadAllEmailTemplatesFromDb()
{
    m_emailTemplateData.clear();

    for (int i = 0; i < ui->templateSelectComboBox->count(); ++i) {
        QString templateKey = ui->templateSelectComboBox->itemData(i).toString();
        QString subjectKey = QString("%1%2/Subject").arg(KEY_EMAIL_TEMPLATE_PREFIX).arg(templateKey);
        QString bodyKey = QString("%1%2/Body").arg(KEY_EMAIL_TEMPLATE_PREFIX).arg(templateKey);

        // Load from DB or use defaults
        QString subject = getSetting(subjectKey,
                                     tr("Default %1 Subject").arg(ui->templateSelectComboBox->itemText(i)));
        QString body = getSetting(bodyKey,
                                  tr("Default %1 Body\n\nYou can use placeholders like {client_name}, {invoice_number}, etc.").arg(ui->templateSelectComboBox->itemText(i)));

        m_emailTemplateData[templateKey] = qMakePair(subject, body);
    }
}

bool SettingsDialog::saveAllEmailTemplatesToDb()
{
    bool success = true;
    QMapIterator<QString, QPair<QString, QString>> it(m_emailTemplateData);

    while (it.hasNext()) {
        it.next();
        QString templateKey = it.key();
        QString subjectKey = QString("%1%2/Subject").arg(KEY_EMAIL_TEMPLATE_PREFIX).arg(templateKey);
        QString bodyKey = QString("%1%2/Body").arg(KEY_EMAIL_TEMPLATE_PREFIX).arg(templateKey);

        if (!setSetting(subjectKey, it.value().first) || !setSetting(bodyKey, it.value().second)) {
            success = false;
        }
    }

    return success;
}

void SettingsDialog::loadTemplateFromMapToUiByKey(const QString& templateKey)
{
    if (m_emailTemplateData.contains(templateKey)) {
        ui->subjectInput->setText(m_emailTemplateData[templateKey].first);
        ui->bodyInput->setPlainText(m_emailTemplateData[templateKey].second);
    } else {
        ui->subjectInput->clear();
        ui->bodyInput->clear();
    }
}

void SettingsDialog::saveUiContentToMap(const QString& templateKey)
{
    if (!templateKey.isEmpty()) {
        m_emailTemplateData[templateKey] = qMakePair(
            ui->subjectInput->text(),
            ui->bodyInput->toPlainText()
            );
    }
}

// UI Button Handlers
void SettingsDialog::on_saveButton_clicked()
{
    if (saveSettingsToDb()) {
        accept();
    }
}

void SettingsDialog::on_cancelButton_clicked()
{
    reject();
}

void SettingsDialog::on_browseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Select Company Logo"),
                                                    ui->companyLogoPathInput->text(),
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    if (!filePath.isEmpty()) {
        ui->companyLogoPathInput->setText(filePath);
    }
}

void SettingsDialog::on_addVatRateButton_clicked()
{
    int newRow = ui->VATRatesTable->rowCount();
    ui->VATRatesTable->insertRow(newRow);
    ui->VATRatesTable->setItem(newRow, VAT_DESCRIPTION_COL, new QTableWidgetItem(tr("New VAT Rate")));
    ui->VATRatesTable->setItem(newRow, VAT_RATE_COL, new QTableWidgetItem("0.00"));
    ui->VATRatesTable->editItem(ui->VATRatesTable->item(newRow, VAT_DESCRIPTION_COL));
}

void SettingsDialog::on_removeVatRateButton_clicked()
{
    int currentRow = ui->VATRatesTable->currentRow();
    if (currentRow >= 0) {
        ui->VATRatesTable->removeRow(currentRow);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Please select a VAT rate to remove"));
    }
}

void SettingsDialog::on_templateSelectComboBox_currentIndexChanged(int index)
{
    if (m_loadingSettings) return;

    // Save current edits
    if (m_previousTemplateIndex >= 0) {
        QString prevKey = ui->templateSelectComboBox->itemData(m_previousTemplateIndex).toString();
        saveUiContentToMap(prevKey);
    }

    // Load new template
    if (index >= 0) {
        QString newKey = ui->templateSelectComboBox->itemData(index).toString();
        loadTemplateFromMapToUiByKey(newKey);
    }

    m_previousTemplateIndex = index;
}
