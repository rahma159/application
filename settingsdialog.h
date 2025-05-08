#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QPair>

// Forward declare UI class
namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    // Static methods for external access to settings
    static QString getSetting(const QString& key, const QString& defaultValue = "");
    static int getSettingInt(const QString& key, int defaultValue = 0);
    static bool getSettingBool(const QString& key, bool defaultValue = false);
    static bool setSetting(const QString& key, const QVariant& value);

private slots:
    // UI interaction slots
    void on_saveButton_clicked();
    void on_cancelButton_clicked();
    void on_browseButton_clicked();
    void on_addVatRateButton_clicked();
    void on_removeVatRateButton_clicked();
    void on_templateSelectComboBox_currentIndexChanged(int index);

private:
    Ui::SettingsDialog *ui;

    // Constants for VAT table columns
    enum VatTableColumns {
        VAT_DESCRIPTION_COL = 0,
        VAT_RATE_COL = 1
    };

    // Email template data storage
    QMap<QString, QPair<QString, QString>> m_emailTemplateData;
    int m_previousTemplateIndex;
    bool m_loadingSettings;

    // Core methods
    void loadSettingsFromDb();
    bool saveSettingsToDb();

    // VAT rates handling
    void loadVatRatesFromDb();
    bool saveVatRatesToDb();

    // Email templates handling
    void loadAllEmailTemplatesFromDb();
    bool saveAllEmailTemplatesToDb();

    // Template UI helpers
    void saveUiContentToMap(const QString& templateKey);
    void loadTemplateFromMapToUiByKey(const QString& templateKey);

    // Utility methods
    bool validateVatRates() const;
    bool validatePaymentSettings() const;
};
#endif // SETTINGSDIALOG_H
