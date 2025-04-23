/********************************************************************************
** Form generated from reading UI file 'clientpaymentwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTPAYMENTWIDGET_H
#define UI_CLIENTPAYMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientPaymentWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainPaymentLayout;
    QHBoxLayout *headerLayout;
    QLabel *companyLogoLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *welcomeClientLabel;
    QGroupBox *summaryGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *summaryLayout;
    QLabel *invoiceNumberDisplay;
    QLabel *paymentAmountDueLabel;
    QLabel *paymentIssueDateLabel;
    QLabel *dueDateDisplay;
    QLabel *amountDueDisplay;
    QLabel *issueDateDisplay;
    QLabel *paymentDueDateLabel;
    QLabel *paymentInvoiceNumberLabel;
    QPushButton *downloadPDFButton;
    QGroupBox *paymentMethodGroupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *paymentMethodLayout;
    QLabel *chooseMethodLabel;
    QRadioButton *payByPayPalRadio;
    QRadioButton *payByCardRadio;
    QRadioButton *payByBankTransferRadio;
    QStackedWidget *paymentDetailsStack;
    QWidget *PayPalPage;
    QGridLayout *gridLayout;
    QLabel *payPalInfoLabel;
    QPushButton *payPalPayButton;
    QWidget *CardPaymentPage;
    QHBoxLayout *horizontalLayout_3;
    QFormLayout *formLayout;
    QLabel *cardNumberLabel;
    QLineEdit *cardNumberInput;
    QLabel *expiryDateLabel;
    QLineEdit *expiryDateInput;
    QLabel *cVVLabel;
    QLineEdit *cVVInput;
    QLabel *cardholderNameLabel;
    QLineEdit *cardholderNameInput;
    QWidget *BankTransferPage;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *bankInfoLayout;
    QTextEdit *bankInfoDisplay;
    QHBoxLayout *actionLayout;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *paymentProgressBar;
    QLabel *errorMessageLabel;
    QPushButton *proceedToPaymentButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *ClientPaymentWidget)
    {
        if (ClientPaymentWidget->objectName().isEmpty())
            ClientPaymentWidget->setObjectName("ClientPaymentWidget");
        ClientPaymentWidget->resize(610, 652);
        horizontalLayout_2 = new QHBoxLayout(ClientPaymentWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        mainPaymentLayout = new QVBoxLayout();
        mainPaymentLayout->setObjectName("mainPaymentLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        companyLogoLabel = new QLabel(ClientPaymentWidget);
        companyLogoLabel->setObjectName("companyLogoLabel");
        companyLogoLabel->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        headerLayout->addWidget(companyLogoLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        welcomeClientLabel = new QLabel(ClientPaymentWidget);
        welcomeClientLabel->setObjectName("welcomeClientLabel");

        headerLayout->addWidget(welcomeClientLabel);


        mainPaymentLayout->addLayout(headerLayout);

        summaryGroupBox = new QGroupBox(ClientPaymentWidget);
        summaryGroupBox->setObjectName("summaryGroupBox");
        horizontalLayout_4 = new QHBoxLayout(summaryGroupBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        summaryLayout = new QGridLayout();
        summaryLayout->setObjectName("summaryLayout");
        invoiceNumberDisplay = new QLabel(summaryGroupBox);
        invoiceNumberDisplay->setObjectName("invoiceNumberDisplay");

        summaryLayout->addWidget(invoiceNumberDisplay, 0, 1, 1, 1);

        paymentAmountDueLabel = new QLabel(summaryGroupBox);
        paymentAmountDueLabel->setObjectName("paymentAmountDueLabel");

        summaryLayout->addWidget(paymentAmountDueLabel, 1, 0, 1, 1);

        paymentIssueDateLabel = new QLabel(summaryGroupBox);
        paymentIssueDateLabel->setObjectName("paymentIssueDateLabel");

        summaryLayout->addWidget(paymentIssueDateLabel, 2, 0, 1, 1);

        dueDateDisplay = new QLabel(summaryGroupBox);
        dueDateDisplay->setObjectName("dueDateDisplay");

        summaryLayout->addWidget(dueDateDisplay, 3, 1, 1, 1);

        amountDueDisplay = new QLabel(summaryGroupBox);
        amountDueDisplay->setObjectName("amountDueDisplay");

        summaryLayout->addWidget(amountDueDisplay, 1, 1, 1, 1);

        issueDateDisplay = new QLabel(summaryGroupBox);
        issueDateDisplay->setObjectName("issueDateDisplay");

        summaryLayout->addWidget(issueDateDisplay, 2, 1, 1, 1);

        paymentDueDateLabel = new QLabel(summaryGroupBox);
        paymentDueDateLabel->setObjectName("paymentDueDateLabel");

        summaryLayout->addWidget(paymentDueDateLabel, 3, 0, 1, 1);

        paymentInvoiceNumberLabel = new QLabel(summaryGroupBox);
        paymentInvoiceNumberLabel->setObjectName("paymentInvoiceNumberLabel");

        summaryLayout->addWidget(paymentInvoiceNumberLabel, 0, 0, 1, 1);

        downloadPDFButton = new QPushButton(summaryGroupBox);
        downloadPDFButton->setObjectName("downloadPDFButton");

        summaryLayout->addWidget(downloadPDFButton, 4, 1, 1, 1);


        horizontalLayout_4->addLayout(summaryLayout);


        mainPaymentLayout->addWidget(summaryGroupBox);

        paymentMethodGroupBox = new QGroupBox(ClientPaymentWidget);
        paymentMethodGroupBox->setObjectName("paymentMethodGroupBox");
        verticalLayout = new QVBoxLayout(paymentMethodGroupBox);
        verticalLayout->setObjectName("verticalLayout");
        paymentMethodLayout = new QVBoxLayout();
        paymentMethodLayout->setObjectName("paymentMethodLayout");
        chooseMethodLabel = new QLabel(paymentMethodGroupBox);
        chooseMethodLabel->setObjectName("chooseMethodLabel");

        paymentMethodLayout->addWidget(chooseMethodLabel);

        payByPayPalRadio = new QRadioButton(paymentMethodGroupBox);
        payByPayPalRadio->setObjectName("payByPayPalRadio");

        paymentMethodLayout->addWidget(payByPayPalRadio);

        payByCardRadio = new QRadioButton(paymentMethodGroupBox);
        payByCardRadio->setObjectName("payByCardRadio");

        paymentMethodLayout->addWidget(payByCardRadio);

        payByBankTransferRadio = new QRadioButton(paymentMethodGroupBox);
        payByBankTransferRadio->setObjectName("payByBankTransferRadio");

        paymentMethodLayout->addWidget(payByBankTransferRadio);


        verticalLayout->addLayout(paymentMethodLayout);

        paymentDetailsStack = new QStackedWidget(paymentMethodGroupBox);
        paymentDetailsStack->setObjectName("paymentDetailsStack");
        PayPalPage = new QWidget();
        PayPalPage->setObjectName("PayPalPage");
        gridLayout = new QGridLayout(PayPalPage);
        gridLayout->setObjectName("gridLayout");
        payPalInfoLabel = new QLabel(PayPalPage);
        payPalInfoLabel->setObjectName("payPalInfoLabel");

        gridLayout->addWidget(payPalInfoLabel, 0, 0, 1, 1);

        payPalPayButton = new QPushButton(PayPalPage);
        payPalPayButton->setObjectName("payPalPayButton");

        gridLayout->addWidget(payPalPayButton, 1, 1, 1, 1);

        paymentDetailsStack->addWidget(PayPalPage);
        CardPaymentPage = new QWidget();
        CardPaymentPage->setObjectName("CardPaymentPage");
        horizontalLayout_3 = new QHBoxLayout(CardPaymentPage);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        cardNumberLabel = new QLabel(CardPaymentPage);
        cardNumberLabel->setObjectName("cardNumberLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, cardNumberLabel);

        cardNumberInput = new QLineEdit(CardPaymentPage);
        cardNumberInput->setObjectName("cardNumberInput");

        formLayout->setWidget(0, QFormLayout::FieldRole, cardNumberInput);

        expiryDateLabel = new QLabel(CardPaymentPage);
        expiryDateLabel->setObjectName("expiryDateLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, expiryDateLabel);

        expiryDateInput = new QLineEdit(CardPaymentPage);
        expiryDateInput->setObjectName("expiryDateInput");

        formLayout->setWidget(1, QFormLayout::FieldRole, expiryDateInput);

        cVVLabel = new QLabel(CardPaymentPage);
        cVVLabel->setObjectName("cVVLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, cVVLabel);

        cVVInput = new QLineEdit(CardPaymentPage);
        cVVInput->setObjectName("cVVInput");

        formLayout->setWidget(2, QFormLayout::FieldRole, cVVInput);

        cardholderNameLabel = new QLabel(CardPaymentPage);
        cardholderNameLabel->setObjectName("cardholderNameLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, cardholderNameLabel);

        cardholderNameInput = new QLineEdit(CardPaymentPage);
        cardholderNameInput->setObjectName("cardholderNameInput");

        formLayout->setWidget(3, QFormLayout::FieldRole, cardholderNameInput);


        horizontalLayout_3->addLayout(formLayout);

        paymentDetailsStack->addWidget(CardPaymentPage);
        BankTransferPage = new QWidget();
        BankTransferPage->setObjectName("BankTransferPage");
        horizontalLayout = new QHBoxLayout(BankTransferPage);
        horizontalLayout->setObjectName("horizontalLayout");
        bankInfoLayout = new QVBoxLayout();
        bankInfoLayout->setObjectName("bankInfoLayout");
        bankInfoDisplay = new QTextEdit(BankTransferPage);
        bankInfoDisplay->setObjectName("bankInfoDisplay");

        bankInfoLayout->addWidget(bankInfoDisplay);


        horizontalLayout->addLayout(bankInfoLayout);

        paymentDetailsStack->addWidget(BankTransferPage);

        verticalLayout->addWidget(paymentDetailsStack);


        mainPaymentLayout->addWidget(paymentMethodGroupBox);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        actionLayout->addItem(horizontalSpacer_2);

        paymentProgressBar = new QProgressBar(ClientPaymentWidget);
        paymentProgressBar->setObjectName("paymentProgressBar");
        paymentProgressBar->setValue(24);

        actionLayout->addWidget(paymentProgressBar);

        errorMessageLabel = new QLabel(ClientPaymentWidget);
        errorMessageLabel->setObjectName("errorMessageLabel");

        actionLayout->addWidget(errorMessageLabel);

        proceedToPaymentButton = new QPushButton(ClientPaymentWidget);
        proceedToPaymentButton->setObjectName("proceedToPaymentButton");

        actionLayout->addWidget(proceedToPaymentButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        actionLayout->addItem(horizontalSpacer_3);


        mainPaymentLayout->addLayout(actionLayout);


        horizontalLayout_2->addLayout(mainPaymentLayout);


        retranslateUi(ClientPaymentWidget);

        paymentDetailsStack->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ClientPaymentWidget);
    } // setupUi

    void retranslateUi(QDialog *ClientPaymentWidget)
    {
        ClientPaymentWidget->setWindowTitle(QCoreApplication::translate("ClientPaymentWidget", "Dialog", nullptr));
        companyLogoLabel->setText(QString());
        welcomeClientLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Welcome Client", nullptr));
        summaryGroupBox->setTitle(QCoreApplication::translate("ClientPaymentWidget", "Invoice Summary Area", nullptr));
        invoiceNumberDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "InvoiceNumberDisplay", nullptr));
        paymentAmountDueLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Amount Due:", nullptr));
        paymentIssueDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Issue Date:", nullptr));
        dueDateDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "DueDateDisplay", nullptr));
        amountDueDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "AmountDueDisplay", nullptr));
        issueDateDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "IssueDateDisplay", nullptr));
        paymentDueDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Due Date:", nullptr));
        paymentInvoiceNumberLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Invoice Number:", nullptr));
        downloadPDFButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Download PDF", nullptr));
        paymentMethodGroupBox->setTitle(QCoreApplication::translate("ClientPaymentWidget", "Payment Method Section", nullptr));
        chooseMethodLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Choose Method:", nullptr));
        payByPayPalRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "PayPal", nullptr));
        payByCardRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "Credit Card", nullptr));
        payByBankTransferRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "Bank Transfer", nullptr));
        payPalInfoLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "PayPal Info", nullptr));
        payPalPayButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Pay WithPalPay", nullptr));
        cardNumberLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Card Number:", nullptr));
        expiryDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Expiry Date:", nullptr));
        cVVLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "CVV:", nullptr));
        cardholderNameLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Cardholder Name:", nullptr));
        errorMessageLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "........", nullptr));
        proceedToPaymentButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Proceed To Payment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientPaymentWidget: public Ui_ClientPaymentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTPAYMENTWIDGET_H
