/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *mainSettingsLayout;
    QTabWidget *SettingsTabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QFormLayout *companyInfoLayout;
    QLabel *companyNameLabel;
    QLineEdit *companyNameInput;
    QLabel *companyAddressLabel;
    QLineEdit *companyAddressInput;
    QLabel *companyVATIDLabel;
    QLineEdit *companyVATIDInput;
    QLineEdit *companyLogoPathInput;
    QPushButton *browseButton;
    QLabel *companyLogoLabel;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *invoiceOptionsLayout;
    QLabel *numberPrefixLabel;
    QLineEdit *numberPrefixInput;
    QLabel *nextNumberLabel;
    QSpinBox *nextNumberSpinBox;
    QLabel *defaultTermsLabel;
    QComboBox *defaultTermsComboBox;
    QLabel *VATRatesLabel;
    QTableWidget *VATRatesTable;
    QPushButton *removeVatRateButton;
    QPushButton *addVatRateButton;
    QCheckBox *enableRemindersCheckBox;
    QSpinBox *daysBeforeDueSpinBox;
    QLabel *daysBeforeDueLabel;
    QLabel *daysAfterDueLabel;
    QSpinBox *daysAfterDueSpinBox_2;
    QCheckBox *enableOverdueIoTAlertCheckBox;
    QLabel *ioTAlertDaysLabel;
    QSpinBox *ioTAlertDaysSpinBox;
    QLabel *ioTDeviceAddressLabel;
    QLineEdit *ioTDeviceAddressInput;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_4;
    QFormLayout *paymentGatewayLayout;
    QLabel *stripeApiKeyLabel;
    QLineEdit *stripeApiKeyInput;
    QLabel *payPalClientIdLabel;
    QLineEdit *payPalClientIdInput;
    QLabel *payPalSecretLabel;
    QLineEdit *payPalSecretInput;
    QCheckBox *stripeEnableCheckBox;
    QCheckBox *payPalEnableCheckBox;
    QLabel *stripeEnableLabel;
    QLabel *payPalEnableLabel;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *emailTemplateLayout;
    QComboBox *templateSelectComboBox;
    QLineEdit *subjectInput;
    QTextEdit *bodyInput;
    QLabel *placeholdersInfoLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(749, 568);
        horizontalLayout_5 = new QHBoxLayout(SettingsDialog);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        mainSettingsLayout = new QVBoxLayout();
        mainSettingsLayout->setObjectName("mainSettingsLayout");
        SettingsTabWidget = new QTabWidget(SettingsDialog);
        SettingsTabWidget->setObjectName("SettingsTabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setObjectName("horizontalLayout");
        companyInfoLayout = new QFormLayout();
        companyInfoLayout->setObjectName("companyInfoLayout");
        companyNameLabel = new QLabel(tab);
        companyNameLabel->setObjectName("companyNameLabel");

        companyInfoLayout->setWidget(0, QFormLayout::LabelRole, companyNameLabel);

        companyNameInput = new QLineEdit(tab);
        companyNameInput->setObjectName("companyNameInput");

        companyInfoLayout->setWidget(0, QFormLayout::FieldRole, companyNameInput);

        companyAddressLabel = new QLabel(tab);
        companyAddressLabel->setObjectName("companyAddressLabel");

        companyInfoLayout->setWidget(1, QFormLayout::LabelRole, companyAddressLabel);

        companyAddressInput = new QLineEdit(tab);
        companyAddressInput->setObjectName("companyAddressInput");

        companyInfoLayout->setWidget(1, QFormLayout::FieldRole, companyAddressInput);

        companyVATIDLabel = new QLabel(tab);
        companyVATIDLabel->setObjectName("companyVATIDLabel");

        companyInfoLayout->setWidget(2, QFormLayout::LabelRole, companyVATIDLabel);

        companyVATIDInput = new QLineEdit(tab);
        companyVATIDInput->setObjectName("companyVATIDInput");

        companyInfoLayout->setWidget(2, QFormLayout::FieldRole, companyVATIDInput);

        companyLogoPathInput = new QLineEdit(tab);
        companyLogoPathInput->setObjectName("companyLogoPathInput");

        companyInfoLayout->setWidget(3, QFormLayout::FieldRole, companyLogoPathInput);

        browseButton = new QPushButton(tab);
        browseButton->setObjectName("browseButton");

        companyInfoLayout->setWidget(4, QFormLayout::FieldRole, browseButton);

        companyLogoLabel = new QLabel(tab);
        companyLogoLabel->setObjectName("companyLogoLabel");

        companyInfoLayout->setWidget(3, QFormLayout::LabelRole, companyLogoLabel);


        horizontalLayout->addLayout(companyInfoLayout);

        SettingsTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        invoiceOptionsLayout = new QFormLayout();
        invoiceOptionsLayout->setObjectName("invoiceOptionsLayout");
        numberPrefixLabel = new QLabel(tab_2);
        numberPrefixLabel->setObjectName("numberPrefixLabel");

        invoiceOptionsLayout->setWidget(0, QFormLayout::LabelRole, numberPrefixLabel);

        numberPrefixInput = new QLineEdit(tab_2);
        numberPrefixInput->setObjectName("numberPrefixInput");

        invoiceOptionsLayout->setWidget(0, QFormLayout::FieldRole, numberPrefixInput);

        nextNumberLabel = new QLabel(tab_2);
        nextNumberLabel->setObjectName("nextNumberLabel");

        invoiceOptionsLayout->setWidget(1, QFormLayout::LabelRole, nextNumberLabel);

        nextNumberSpinBox = new QSpinBox(tab_2);
        nextNumberSpinBox->setObjectName("nextNumberSpinBox");

        invoiceOptionsLayout->setWidget(1, QFormLayout::FieldRole, nextNumberSpinBox);

        defaultTermsLabel = new QLabel(tab_2);
        defaultTermsLabel->setObjectName("defaultTermsLabel");

        invoiceOptionsLayout->setWidget(2, QFormLayout::LabelRole, defaultTermsLabel);

        defaultTermsComboBox = new QComboBox(tab_2);
        defaultTermsComboBox->setObjectName("defaultTermsComboBox");

        invoiceOptionsLayout->setWidget(2, QFormLayout::FieldRole, defaultTermsComboBox);

        VATRatesLabel = new QLabel(tab_2);
        VATRatesLabel->setObjectName("VATRatesLabel");

        invoiceOptionsLayout->setWidget(3, QFormLayout::LabelRole, VATRatesLabel);

        VATRatesTable = new QTableWidget(tab_2);
        VATRatesTable->setObjectName("VATRatesTable");

        invoiceOptionsLayout->setWidget(3, QFormLayout::FieldRole, VATRatesTable);

        removeVatRateButton = new QPushButton(tab_2);
        removeVatRateButton->setObjectName("removeVatRateButton");

        invoiceOptionsLayout->setWidget(5, QFormLayout::FieldRole, removeVatRateButton);

        addVatRateButton = new QPushButton(tab_2);
        addVatRateButton->setObjectName("addVatRateButton");

        invoiceOptionsLayout->setWidget(4, QFormLayout::FieldRole, addVatRateButton);

        enableRemindersCheckBox = new QCheckBox(tab_2);
        enableRemindersCheckBox->setObjectName("enableRemindersCheckBox");

        invoiceOptionsLayout->setWidget(6, QFormLayout::FieldRole, enableRemindersCheckBox);

        daysBeforeDueSpinBox = new QSpinBox(tab_2);
        daysBeforeDueSpinBox->setObjectName("daysBeforeDueSpinBox");

        invoiceOptionsLayout->setWidget(7, QFormLayout::FieldRole, daysBeforeDueSpinBox);

        daysBeforeDueLabel = new QLabel(tab_2);
        daysBeforeDueLabel->setObjectName("daysBeforeDueLabel");

        invoiceOptionsLayout->setWidget(7, QFormLayout::LabelRole, daysBeforeDueLabel);

        daysAfterDueLabel = new QLabel(tab_2);
        daysAfterDueLabel->setObjectName("daysAfterDueLabel");

        invoiceOptionsLayout->setWidget(8, QFormLayout::LabelRole, daysAfterDueLabel);

        daysAfterDueSpinBox_2 = new QSpinBox(tab_2);
        daysAfterDueSpinBox_2->setObjectName("daysAfterDueSpinBox_2");

        invoiceOptionsLayout->setWidget(8, QFormLayout::FieldRole, daysAfterDueSpinBox_2);

        enableOverdueIoTAlertCheckBox = new QCheckBox(tab_2);
        enableOverdueIoTAlertCheckBox->setObjectName("enableOverdueIoTAlertCheckBox");

        invoiceOptionsLayout->setWidget(9, QFormLayout::FieldRole, enableOverdueIoTAlertCheckBox);

        ioTAlertDaysLabel = new QLabel(tab_2);
        ioTAlertDaysLabel->setObjectName("ioTAlertDaysLabel");

        invoiceOptionsLayout->setWidget(10, QFormLayout::LabelRole, ioTAlertDaysLabel);

        ioTAlertDaysSpinBox = new QSpinBox(tab_2);
        ioTAlertDaysSpinBox->setObjectName("ioTAlertDaysSpinBox");

        invoiceOptionsLayout->setWidget(10, QFormLayout::FieldRole, ioTAlertDaysSpinBox);

        ioTDeviceAddressLabel = new QLabel(tab_2);
        ioTDeviceAddressLabel->setObjectName("ioTDeviceAddressLabel");

        invoiceOptionsLayout->setWidget(11, QFormLayout::LabelRole, ioTDeviceAddressLabel);

        ioTDeviceAddressInput = new QLineEdit(tab_2);
        ioTDeviceAddressInput->setObjectName("ioTDeviceAddressInput");

        invoiceOptionsLayout->setWidget(11, QFormLayout::FieldRole, ioTDeviceAddressInput);


        verticalLayout_2->addLayout(invoiceOptionsLayout);

        SettingsTabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        horizontalLayout_4 = new QHBoxLayout(tab_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        paymentGatewayLayout = new QFormLayout();
        paymentGatewayLayout->setObjectName("paymentGatewayLayout");
        stripeApiKeyLabel = new QLabel(tab_4);
        stripeApiKeyLabel->setObjectName("stripeApiKeyLabel");

        paymentGatewayLayout->setWidget(1, QFormLayout::LabelRole, stripeApiKeyLabel);

        stripeApiKeyInput = new QLineEdit(tab_4);
        stripeApiKeyInput->setObjectName("stripeApiKeyInput");

        paymentGatewayLayout->setWidget(1, QFormLayout::FieldRole, stripeApiKeyInput);

        payPalClientIdLabel = new QLabel(tab_4);
        payPalClientIdLabel->setObjectName("payPalClientIdLabel");

        paymentGatewayLayout->setWidget(3, QFormLayout::LabelRole, payPalClientIdLabel);

        payPalClientIdInput = new QLineEdit(tab_4);
        payPalClientIdInput->setObjectName("payPalClientIdInput");

        paymentGatewayLayout->setWidget(3, QFormLayout::FieldRole, payPalClientIdInput);

        payPalSecretLabel = new QLabel(tab_4);
        payPalSecretLabel->setObjectName("payPalSecretLabel");

        paymentGatewayLayout->setWidget(4, QFormLayout::LabelRole, payPalSecretLabel);

        payPalSecretInput = new QLineEdit(tab_4);
        payPalSecretInput->setObjectName("payPalSecretInput");

        paymentGatewayLayout->setWidget(4, QFormLayout::FieldRole, payPalSecretInput);

        stripeEnableCheckBox = new QCheckBox(tab_4);
        stripeEnableCheckBox->setObjectName("stripeEnableCheckBox");

        paymentGatewayLayout->setWidget(0, QFormLayout::FieldRole, stripeEnableCheckBox);

        payPalEnableCheckBox = new QCheckBox(tab_4);
        payPalEnableCheckBox->setObjectName("payPalEnableCheckBox");

        paymentGatewayLayout->setWidget(2, QFormLayout::FieldRole, payPalEnableCheckBox);

        stripeEnableLabel = new QLabel(tab_4);
        stripeEnableLabel->setObjectName("stripeEnableLabel");

        paymentGatewayLayout->setWidget(0, QFormLayout::LabelRole, stripeEnableLabel);

        payPalEnableLabel = new QLabel(tab_4);
        payPalEnableLabel->setObjectName("payPalEnableLabel");

        paymentGatewayLayout->setWidget(2, QFormLayout::LabelRole, payPalEnableLabel);


        horizontalLayout_4->addLayout(paymentGatewayLayout);

        SettingsTabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        horizontalLayout_3 = new QHBoxLayout(tab_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        emailTemplateLayout = new QVBoxLayout();
        emailTemplateLayout->setObjectName("emailTemplateLayout");
        templateSelectComboBox = new QComboBox(tab_3);
        templateSelectComboBox->addItem(QString());
        templateSelectComboBox->addItem(QString());
        templateSelectComboBox->addItem(QString());
        templateSelectComboBox->setObjectName("templateSelectComboBox");

        emailTemplateLayout->addWidget(templateSelectComboBox);

        subjectInput = new QLineEdit(tab_3);
        subjectInput->setObjectName("subjectInput");

        emailTemplateLayout->addWidget(subjectInput);

        bodyInput = new QTextEdit(tab_3);
        bodyInput->setObjectName("bodyInput");

        emailTemplateLayout->addWidget(bodyInput);

        placeholdersInfoLabel = new QLabel(tab_3);
        placeholdersInfoLabel->setObjectName("placeholdersInfoLabel");

        emailTemplateLayout->addWidget(placeholdersInfoLabel);


        horizontalLayout_3->addLayout(emailTemplateLayout);

        SettingsTabWidget->addTab(tab_3, QString());

        mainSettingsLayout->addWidget(SettingsTabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        saveButton = new QPushButton(SettingsDialog);
        saveButton->setObjectName("saveButton");

        horizontalLayout_2->addWidget(saveButton);

        cancelButton = new QPushButton(SettingsDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout_2->addWidget(cancelButton);


        mainSettingsLayout->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(mainSettingsLayout);


        retranslateUi(SettingsDialog);

        SettingsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        companyNameLabel->setText(QCoreApplication::translate("SettingsDialog", "Company Name:", nullptr));
        companyAddressLabel->setText(QCoreApplication::translate("SettingsDialog", "Company Address:", nullptr));
        companyVATIDLabel->setText(QCoreApplication::translate("SettingsDialog", "Company VATID:", nullptr));
        browseButton->setText(QCoreApplication::translate("SettingsDialog", "Browse", nullptr));
        companyLogoLabel->setText(QCoreApplication::translate("SettingsDialog", "Company Logo:", nullptr));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(tab), QCoreApplication::translate("SettingsDialog", "Company Info", nullptr));
        numberPrefixLabel->setText(QCoreApplication::translate("SettingsDialog", "Number Prefix:", nullptr));
        nextNumberLabel->setText(QCoreApplication::translate("SettingsDialog", "Next Number:", nullptr));
        defaultTermsLabel->setText(QCoreApplication::translate("SettingsDialog", "Default Terms:", nullptr));
        VATRatesLabel->setText(QCoreApplication::translate("SettingsDialog", "VAT Rates:", nullptr));
        removeVatRateButton->setText(QCoreApplication::translate("SettingsDialog", "remove Vat Rate", nullptr));
        addVatRateButton->setText(QCoreApplication::translate("SettingsDialog", "Add Vat Rate", nullptr));
        enableRemindersCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Enable Reminders Check", nullptr));
        daysBeforeDueLabel->setText(QCoreApplication::translate("SettingsDialog", "Before Due:", nullptr));
        daysAfterDueLabel->setText(QCoreApplication::translate("SettingsDialog", "After Due:", nullptr));
        enableOverdueIoTAlertCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Enable Overdue IoT Alert Check", nullptr));
        ioTAlertDaysLabel->setText(QCoreApplication::translate("SettingsDialog", "Alert Days:", nullptr));
        ioTDeviceAddressLabel->setText(QCoreApplication::translate("SettingsDialog", "IoT Device Address:", nullptr));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(tab_2), QCoreApplication::translate("SettingsDialog", "Invoice Options", nullptr));
        stripeApiKeyLabel->setText(QCoreApplication::translate("SettingsDialog", "Stripe Api Key:", nullptr));
        payPalClientIdLabel->setText(QCoreApplication::translate("SettingsDialog", "PayPal Client ID:", nullptr));
        payPalSecretLabel->setText(QCoreApplication::translate("SettingsDialog", "PayPal Secret:", nullptr));
        stripeEnableCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Stripe Enable Check", nullptr));
        payPalEnableCheckBox->setText(QCoreApplication::translate("SettingsDialog", "PayPal Enable Check", nullptr));
        stripeEnableLabel->setText(QCoreApplication::translate("SettingsDialog", "Enable Stripe:", nullptr));
        payPalEnableLabel->setText(QCoreApplication::translate("SettingsDialog", "Enable PayPal:", nullptr));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(tab_4), QCoreApplication::translate("SettingsDialog", "Payment Gateways", nullptr));
        templateSelectComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "New Invoice", nullptr));
        templateSelectComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "Reminder", nullptr));
        templateSelectComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "etc", nullptr));

        subjectInput->setText(QCoreApplication::translate("SettingsDialog", "Subject ", nullptr));
        bodyInput->setHtml(QCoreApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'monospace'; font-size:13px; color:#768390; background-color:#242629;\">Body</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'monospace'; font-size:13px; color:#768390;\"><br /></p></body></html>", nullptr));
        placeholdersInfoLabel->setText(QCoreApplication::translate("SettingsDialog", "Placeholders Info:", nullptr));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(tab_3), QCoreApplication::translate("SettingsDialog", "Email Templates", nullptr));
        saveButton->setText(QCoreApplication::translate("SettingsDialog", "Save", nullptr));
        cancelButton->setText(QCoreApplication::translate("SettingsDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
