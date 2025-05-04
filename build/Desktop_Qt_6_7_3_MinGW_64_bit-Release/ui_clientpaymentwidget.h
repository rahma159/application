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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientPaymentWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *mainPaymentLayout;
    QHBoxLayout *headerLayout;
    QSpacerItem *horizontalSpacer_6;
    QLabel *welcomeClientLabel;
    QSpacerItem *horizontalSpacer;
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
    QPushButton *downloadPdfButton;
    QGroupBox *paymentMethodGroupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *paymentMethodLayout;
    QLabel *chooseMethodLabel;
    QRadioButton *payByPayPalRadio;
    QRadioButton *payByCardRadio;
    QRadioButton *payByBankTransferRadio;
    QStackedWidget *paymentDetailsStack;
    QWidget *payPalPage;
    QGridLayout *gridLayout;
    QLabel *payPalInstructionsLabel;
    QPushButton *payPalPayButton;
    QLabel *payPalInfoLabel;
    QWidget *cardPaymentPage;
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
    QWidget *bankTransferPage;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *bankInfoDisplay;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *editBankDetailsButton;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *bankDetailsEditGroup;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *bankNameInput;
    QLineEdit *accountHolderInput;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *ibanInput;
    QLineEdit *bicInput;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cancelEditBankDetailsButton;
    QPushButton *saveBankDetailsButton;
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
        ClientPaymentWidget->resize(779, 745);
        verticalLayout_4 = new QVBoxLayout(ClientPaymentWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        scrollArea = new QScrollArea(ClientPaymentWidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 892, 711));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName("verticalLayout_5");
        mainPaymentLayout = new QVBoxLayout();
        mainPaymentLayout->setObjectName("mainPaymentLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer_6);

        welcomeClientLabel = new QLabel(scrollAreaWidgetContents);
        welcomeClientLabel->setObjectName("welcomeClientLabel");

        headerLayout->addWidget(welcomeClientLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        headerLayout->addItem(horizontalSpacer);


        mainPaymentLayout->addLayout(headerLayout);

        summaryGroupBox = new QGroupBox(scrollAreaWidgetContents);
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

        downloadPdfButton = new QPushButton(summaryGroupBox);
        downloadPdfButton->setObjectName("downloadPdfButton");

        summaryLayout->addWidget(downloadPdfButton, 4, 1, 1, 1);


        horizontalLayout_4->addLayout(summaryLayout);


        mainPaymentLayout->addWidget(summaryGroupBox);

        paymentMethodGroupBox = new QGroupBox(scrollAreaWidgetContents);
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
        payPalPage = new QWidget();
        payPalPage->setObjectName("payPalPage");
        gridLayout = new QGridLayout(payPalPage);
        gridLayout->setObjectName("gridLayout");
        payPalInstructionsLabel = new QLabel(payPalPage);
        payPalInstructionsLabel->setObjectName("payPalInstructionsLabel");

        gridLayout->addWidget(payPalInstructionsLabel, 1, 0, 1, 1);

        payPalPayButton = new QPushButton(payPalPage);
        payPalPayButton->setObjectName("payPalPayButton");

        gridLayout->addWidget(payPalPayButton, 2, 2, 1, 1);

        payPalInfoLabel = new QLabel(payPalPage);
        payPalInfoLabel->setObjectName("payPalInfoLabel");

        gridLayout->addWidget(payPalInfoLabel, 0, 0, 1, 1);

        paymentDetailsStack->addWidget(payPalPage);
        cardPaymentPage = new QWidget();
        cardPaymentPage->setObjectName("cardPaymentPage");
        horizontalLayout_3 = new QHBoxLayout(cardPaymentPage);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        cardNumberLabel = new QLabel(cardPaymentPage);
        cardNumberLabel->setObjectName("cardNumberLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, cardNumberLabel);

        cardNumberInput = new QLineEdit(cardPaymentPage);
        cardNumberInput->setObjectName("cardNumberInput");

        formLayout->setWidget(0, QFormLayout::FieldRole, cardNumberInput);

        expiryDateLabel = new QLabel(cardPaymentPage);
        expiryDateLabel->setObjectName("expiryDateLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, expiryDateLabel);

        expiryDateInput = new QLineEdit(cardPaymentPage);
        expiryDateInput->setObjectName("expiryDateInput");

        formLayout->setWidget(1, QFormLayout::FieldRole, expiryDateInput);

        cVVLabel = new QLabel(cardPaymentPage);
        cVVLabel->setObjectName("cVVLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, cVVLabel);

        cVVInput = new QLineEdit(cardPaymentPage);
        cVVInput->setObjectName("cVVInput");

        formLayout->setWidget(2, QFormLayout::FieldRole, cVVInput);

        cardholderNameLabel = new QLabel(cardPaymentPage);
        cardholderNameLabel->setObjectName("cardholderNameLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, cardholderNameLabel);

        cardholderNameInput = new QLineEdit(cardPaymentPage);
        cardholderNameInput->setObjectName("cardholderNameInput");

        formLayout->setWidget(3, QFormLayout::FieldRole, cardholderNameInput);


        horizontalLayout_3->addLayout(formLayout);

        paymentDetailsStack->addWidget(cardPaymentPage);
        bankTransferPage = new QWidget();
        bankTransferPage->setObjectName("bankTransferPage");
        verticalLayout_3 = new QVBoxLayout(bankTransferPage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        bankInfoDisplay = new QTextEdit(bankTransferPage);
        bankInfoDisplay->setObjectName("bankInfoDisplay");

        verticalLayout_3->addWidget(bankInfoDisplay);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        editBankDetailsButton = new QPushButton(bankTransferPage);
        editBankDetailsButton->setObjectName("editBankDetailsButton");

        horizontalLayout_5->addWidget(editBankDetailsButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_5);

        bankDetailsEditGroup = new QGroupBox(bankTransferPage);
        bankDetailsEditGroup->setObjectName("bankDetailsEditGroup");
        verticalLayout_2 = new QVBoxLayout(bankDetailsEditGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label = new QLabel(bankDetailsEditGroup);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        bankNameInput = new QLineEdit(bankDetailsEditGroup);
        bankNameInput->setObjectName("bankNameInput");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, bankNameInput);

        accountHolderInput = new QLineEdit(bankDetailsEditGroup);
        accountHolderInput->setObjectName("accountHolderInput");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, accountHolderInput);

        label_2 = new QLabel(bankDetailsEditGroup);
        label_2->setObjectName("label_2");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(bankDetailsEditGroup);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        ibanInput = new QLineEdit(bankDetailsEditGroup);
        ibanInput->setObjectName("ibanInput");

        formLayout_2->setWidget(2, QFormLayout::FieldRole, ibanInput);

        bicInput = new QLineEdit(bankDetailsEditGroup);
        bicInput->setObjectName("bicInput");

        formLayout_2->setWidget(3, QFormLayout::FieldRole, bicInput);

        label_4 = new QLabel(bankDetailsEditGroup);
        label_4->setObjectName("label_4");

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_4);


        verticalLayout_2->addLayout(formLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        cancelEditBankDetailsButton = new QPushButton(bankDetailsEditGroup);
        cancelEditBankDetailsButton->setObjectName("cancelEditBankDetailsButton");

        horizontalLayout->addWidget(cancelEditBankDetailsButton);

        saveBankDetailsButton = new QPushButton(bankDetailsEditGroup);
        saveBankDetailsButton->setObjectName("saveBankDetailsButton");

        horizontalLayout->addWidget(saveBankDetailsButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(bankDetailsEditGroup);

        paymentDetailsStack->addWidget(bankTransferPage);

        verticalLayout->addWidget(paymentDetailsStack);


        mainPaymentLayout->addWidget(paymentMethodGroupBox);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        actionLayout->addItem(horizontalSpacer_2);

        paymentProgressBar = new QProgressBar(scrollAreaWidgetContents);
        paymentProgressBar->setObjectName("paymentProgressBar");
        paymentProgressBar->setValue(0);

        actionLayout->addWidget(paymentProgressBar);

        errorMessageLabel = new QLabel(scrollAreaWidgetContents);
        errorMessageLabel->setObjectName("errorMessageLabel");

        actionLayout->addWidget(errorMessageLabel);

        proceedToPaymentButton = new QPushButton(scrollAreaWidgetContents);
        proceedToPaymentButton->setObjectName("proceedToPaymentButton");

        actionLayout->addWidget(proceedToPaymentButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        actionLayout->addItem(horizontalSpacer_3);


        mainPaymentLayout->addLayout(actionLayout);


        verticalLayout_5->addLayout(mainPaymentLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);


        retranslateUi(ClientPaymentWidget);

        paymentDetailsStack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientPaymentWidget);
    } // setupUi

    void retranslateUi(QDialog *ClientPaymentWidget)
    {
        ClientPaymentWidget->setWindowTitle(QCoreApplication::translate("ClientPaymentWidget", "Dialog", nullptr));
        welcomeClientLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Client", nullptr));
        summaryGroupBox->setTitle(QCoreApplication::translate("ClientPaymentWidget", "Invoice Summary Area", nullptr));
        invoiceNumberDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "InvoiceNumberDisplay", nullptr));
        paymentAmountDueLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Amount Due:", nullptr));
        paymentIssueDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Issue Date:", nullptr));
        dueDateDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "DueDateDisplay", nullptr));
        amountDueDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "AmountDueDisplay", nullptr));
        issueDateDisplay->setText(QCoreApplication::translate("ClientPaymentWidget", "IssueDateDisplay", nullptr));
        paymentDueDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Due Date:", nullptr));
        paymentInvoiceNumberLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Invoice Number:", nullptr));
        downloadPdfButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Download PDF", nullptr));
        paymentMethodGroupBox->setTitle(QCoreApplication::translate("ClientPaymentWidget", "Payment Method Section", nullptr));
        chooseMethodLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Choose Method:", nullptr));
        payByPayPalRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "PayPal", nullptr));
        payByCardRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "Credit Card", nullptr));
        payByBankTransferRadio->setText(QCoreApplication::translate("ClientPaymentWidget", "Bank Transfer", nullptr));
        payPalInstructionsLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "You will be redirected to the secure PayPal website to complete your payment. Click 'Pay With PayPal' or 'Proceed To Payment' to continue.", nullptr));
        payPalPayButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Pay WithPalPay", nullptr));
        payPalInfoLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "PayPal Info", nullptr));
        cardNumberLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Card Number:", nullptr));
        expiryDateLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Expiry Date:", nullptr));
        cVVLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "CVV:", nullptr));
        cardholderNameLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "Cardholder Name:", nullptr));
        editBankDetailsButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Configure Bank Details", nullptr));
        bankDetailsEditGroup->setTitle(QCoreApplication::translate("ClientPaymentWidget", "Bank Details", nullptr));
        label->setText(QCoreApplication::translate("ClientPaymentWidget", "Bank Name:", nullptr));
        bankNameInput->setText(QCoreApplication::translate("ClientPaymentWidget", "Enter bank name", nullptr));
        accountHolderInput->setText(QCoreApplication::translate("ClientPaymentWidget", "Enter account holder name", nullptr));
        label_2->setText(QCoreApplication::translate("ClientPaymentWidget", "Account Holder:", nullptr));
        label_3->setText(QCoreApplication::translate("ClientPaymentWidget", "IBAN:", nullptr));
        ibanInput->setText(QCoreApplication::translate("ClientPaymentWidget", "Enter IBAN", nullptr));
        bicInput->setText(QCoreApplication::translate("ClientPaymentWidget", "Enter BIC/SWIFT code", nullptr));
        label_4->setText(QCoreApplication::translate("ClientPaymentWidget", "BIC/SWIFT:", nullptr));
        cancelEditBankDetailsButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Cancel", nullptr));
        saveBankDetailsButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Save Details", nullptr));
        errorMessageLabel->setText(QCoreApplication::translate("ClientPaymentWidget", "........", nullptr));
        proceedToPaymentButton->setText(QCoreApplication::translate("ClientPaymentWidget", "Proceed To Payment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientPaymentWidget: public Ui_ClientPaymentWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTPAYMENTWIDGET_H
