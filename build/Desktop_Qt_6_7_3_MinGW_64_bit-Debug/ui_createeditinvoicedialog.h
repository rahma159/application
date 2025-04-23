/********************************************************************************
** Form generated from reading UI file 'createeditinvoicedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEDITINVOICEDIALOG_H
#define UI_CREATEEDITINVOICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateEditInvoiceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *mainDialogLayout;
    QGroupBox *clientGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *clientLayout;
    QComboBox *clientSelectComboBox;
    QLabel *clientSelectLabel;
    QLabel *clientDetailsLabel;
    QTextEdit *clientDetailsTextEdit;
    QGroupBox *detailsGroupBox;
    QHBoxLayout *horizontalLayout;
    QGridLayout *detailsLayout;
    QLabel *invoiceNumberLabel;
    QLabel *IssueDateLabel;
    QLabel *paymentTermsLabel;
    QLabel *dueDateLabel;
    QLineEdit *invoiceNumberLineEdit;
    QDateEdit *issueDateEdit;
    QLineEdit *paymentTermsLineEdit;
    QDateEdit *dueDateEdit;
    QGroupBox *lineItemsGroupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *lineItemsLayout;
    QTableWidget *lineItemsTableWidget;
    QHBoxLayout *lineItemActionsLayout;
    QPushButton *removeLineItemButton;
    QPushButton *addLineItemButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *notesAndTotalsLayout;
    QGroupBox *notesGroupBox;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *notesLayout;
    QLabel *notesLabel;
    QTextEdit *notesTextEdit;
    QGroupBox *totalsGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QFormLayout *totalsFormLayout;
    QLabel *subtotalLabel;
    QLabel *subtotalValueLabel;
    QLabel *totalVATLabel;
    QLabel *totalVatValueLabel;
    QLabel *grandTotalLabel;
    QLabel *grandTotalValueLabel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveDraftButton;
    QPushButton *saveAndSendButton;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelInvoiceButton;
    QPushButton *previewButton;

    void setupUi(QDialog *CreateEditInvoiceDialog)
    {
        if (CreateEditInvoiceDialog->objectName().isEmpty())
            CreateEditInvoiceDialog->setObjectName("CreateEditInvoiceDialog");
        CreateEditInvoiceDialog->resize(928, 997);
        verticalLayout_2 = new QVBoxLayout(CreateEditInvoiceDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        scrollArea = new QScrollArea(CreateEditInvoiceDialog);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 908, 977));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName("verticalLayout_3");
        mainDialogLayout = new QVBoxLayout();
        mainDialogLayout->setObjectName("mainDialogLayout");
        clientGroupBox = new QGroupBox(scrollAreaWidgetContents);
        clientGroupBox->setObjectName("clientGroupBox");
        horizontalLayout_2 = new QHBoxLayout(clientGroupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        clientLayout = new QGridLayout();
        clientLayout->setObjectName("clientLayout");
        clientSelectComboBox = new QComboBox(clientGroupBox);
        clientSelectComboBox->addItem(QString());
        clientSelectComboBox->addItem(QString());
        clientSelectComboBox->setObjectName("clientSelectComboBox");

        clientLayout->addWidget(clientSelectComboBox, 0, 1, 1, 1);

        clientSelectLabel = new QLabel(clientGroupBox);
        clientSelectLabel->setObjectName("clientSelectLabel");

        clientLayout->addWidget(clientSelectLabel, 0, 0, 1, 1);

        clientDetailsLabel = new QLabel(clientGroupBox);
        clientDetailsLabel->setObjectName("clientDetailsLabel");

        clientLayout->addWidget(clientDetailsLabel, 1, 0, 1, 1);

        clientDetailsTextEdit = new QTextEdit(clientGroupBox);
        clientDetailsTextEdit->setObjectName("clientDetailsTextEdit");

        clientLayout->addWidget(clientDetailsTextEdit, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(clientLayout);


        mainDialogLayout->addWidget(clientGroupBox);

        detailsGroupBox = new QGroupBox(scrollAreaWidgetContents);
        detailsGroupBox->setObjectName("detailsGroupBox");
        horizontalLayout = new QHBoxLayout(detailsGroupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        detailsLayout = new QGridLayout();
        detailsLayout->setObjectName("detailsLayout");
        invoiceNumberLabel = new QLabel(detailsGroupBox);
        invoiceNumberLabel->setObjectName("invoiceNumberLabel");

        detailsLayout->addWidget(invoiceNumberLabel, 0, 0, 1, 1);

        IssueDateLabel = new QLabel(detailsGroupBox);
        IssueDateLabel->setObjectName("IssueDateLabel");

        detailsLayout->addWidget(IssueDateLabel, 1, 0, 1, 1);

        paymentTermsLabel = new QLabel(detailsGroupBox);
        paymentTermsLabel->setObjectName("paymentTermsLabel");

        detailsLayout->addWidget(paymentTermsLabel, 2, 0, 1, 1);

        dueDateLabel = new QLabel(detailsGroupBox);
        dueDateLabel->setObjectName("dueDateLabel");

        detailsLayout->addWidget(dueDateLabel, 3, 0, 1, 1);

        invoiceNumberLineEdit = new QLineEdit(detailsGroupBox);
        invoiceNumberLineEdit->setObjectName("invoiceNumberLineEdit");

        detailsLayout->addWidget(invoiceNumberLineEdit, 0, 1, 1, 1);

        issueDateEdit = new QDateEdit(detailsGroupBox);
        issueDateEdit->setObjectName("issueDateEdit");

        detailsLayout->addWidget(issueDateEdit, 1, 1, 1, 1);

        paymentTermsLineEdit = new QLineEdit(detailsGroupBox);
        paymentTermsLineEdit->setObjectName("paymentTermsLineEdit");

        detailsLayout->addWidget(paymentTermsLineEdit, 2, 1, 1, 1);

        dueDateEdit = new QDateEdit(detailsGroupBox);
        dueDateEdit->setObjectName("dueDateEdit");

        detailsLayout->addWidget(dueDateEdit, 3, 1, 1, 1);


        horizontalLayout->addLayout(detailsLayout);


        mainDialogLayout->addWidget(detailsGroupBox);

        lineItemsGroupBox = new QGroupBox(scrollAreaWidgetContents);
        lineItemsGroupBox->setObjectName("lineItemsGroupBox");
        verticalLayout_4 = new QVBoxLayout(lineItemsGroupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        lineItemsLayout = new QVBoxLayout();
        lineItemsLayout->setObjectName("lineItemsLayout");
        lineItemsTableWidget = new QTableWidget(lineItemsGroupBox);
        if (lineItemsTableWidget->columnCount() < 5)
            lineItemsTableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        lineItemsTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        lineItemsTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        lineItemsTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        lineItemsTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        lineItemsTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        lineItemsTableWidget->setObjectName("lineItemsTableWidget");
        lineItemsTableWidget->setTabletTracking(false);
        lineItemsTableWidget->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        lineItemsTableWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        lineItemsTableWidget->setAutoFillBackground(false);
        lineItemsTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        lineItemsTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        lineItemsTableWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        lineItemsTableWidget->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);

        lineItemsLayout->addWidget(lineItemsTableWidget);

        lineItemActionsLayout = new QHBoxLayout();
        lineItemActionsLayout->setObjectName("lineItemActionsLayout");
        removeLineItemButton = new QPushButton(lineItemsGroupBox);
        removeLineItemButton->setObjectName("removeLineItemButton");

        lineItemActionsLayout->addWidget(removeLineItemButton);

        addLineItemButton = new QPushButton(lineItemsGroupBox);
        addLineItemButton->setObjectName("addLineItemButton");

        lineItemActionsLayout->addWidget(addLineItemButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        lineItemActionsLayout->addItem(horizontalSpacer);


        lineItemsLayout->addLayout(lineItemActionsLayout);


        verticalLayout_4->addLayout(lineItemsLayout);


        mainDialogLayout->addWidget(lineItemsGroupBox);

        notesAndTotalsLayout = new QHBoxLayout();
        notesAndTotalsLayout->setObjectName("notesAndTotalsLayout");
        notesGroupBox = new QGroupBox(scrollAreaWidgetContents);
        notesGroupBox->setObjectName("notesGroupBox");
        verticalLayout = new QVBoxLayout(notesGroupBox);
        verticalLayout->setObjectName("verticalLayout");
        notesLayout = new QVBoxLayout();
        notesLayout->setObjectName("notesLayout");
        notesLabel = new QLabel(notesGroupBox);
        notesLabel->setObjectName("notesLabel");

        notesLayout->addWidget(notesLabel);

        notesTextEdit = new QTextEdit(notesGroupBox);
        notesTextEdit->setObjectName("notesTextEdit");

        notesLayout->addWidget(notesTextEdit);


        verticalLayout->addLayout(notesLayout);


        notesAndTotalsLayout->addWidget(notesGroupBox);


        mainDialogLayout->addLayout(notesAndTotalsLayout);

        totalsGroupBox = new QGroupBox(scrollAreaWidgetContents);
        totalsGroupBox->setObjectName("totalsGroupBox");
        horizontalLayout_4 = new QHBoxLayout(totalsGroupBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        totalsFormLayout = new QFormLayout();
        totalsFormLayout->setObjectName("totalsFormLayout");
        subtotalLabel = new QLabel(totalsGroupBox);
        subtotalLabel->setObjectName("subtotalLabel");

        totalsFormLayout->setWidget(0, QFormLayout::LabelRole, subtotalLabel);

        subtotalValueLabel = new QLabel(totalsGroupBox);
        subtotalValueLabel->setObjectName("subtotalValueLabel");

        totalsFormLayout->setWidget(0, QFormLayout::FieldRole, subtotalValueLabel);

        totalVATLabel = new QLabel(totalsGroupBox);
        totalVATLabel->setObjectName("totalVATLabel");

        totalsFormLayout->setWidget(1, QFormLayout::LabelRole, totalVATLabel);

        totalVatValueLabel = new QLabel(totalsGroupBox);
        totalVatValueLabel->setObjectName("totalVatValueLabel");

        totalsFormLayout->setWidget(1, QFormLayout::FieldRole, totalVatValueLabel);

        grandTotalLabel = new QLabel(totalsGroupBox);
        grandTotalLabel->setObjectName("grandTotalLabel");

        totalsFormLayout->setWidget(2, QFormLayout::LabelRole, grandTotalLabel);

        grandTotalValueLabel = new QLabel(totalsGroupBox);
        grandTotalValueLabel->setObjectName("grandTotalValueLabel");

        totalsFormLayout->setWidget(2, QFormLayout::FieldRole, grandTotalValueLabel);


        horizontalLayout_4->addLayout(totalsFormLayout);


        mainDialogLayout->addWidget(totalsGroupBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        saveDraftButton = new QPushButton(scrollAreaWidgetContents);
        saveDraftButton->setObjectName("saveDraftButton");

        horizontalLayout_5->addWidget(saveDraftButton);

        saveAndSendButton = new QPushButton(scrollAreaWidgetContents);
        saveAndSendButton->setObjectName("saveAndSendButton");

        horizontalLayout_5->addWidget(saveAndSendButton);


        mainDialogLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        cancelInvoiceButton = new QPushButton(scrollAreaWidgetContents);
        cancelInvoiceButton->setObjectName("cancelInvoiceButton");

        horizontalLayout_6->addWidget(cancelInvoiceButton);

        previewButton = new QPushButton(scrollAreaWidgetContents);
        previewButton->setObjectName("previewButton");

        horizontalLayout_6->addWidget(previewButton);


        mainDialogLayout->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(mainDialogLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(CreateEditInvoiceDialog);

        QMetaObject::connectSlotsByName(CreateEditInvoiceDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateEditInvoiceDialog)
    {
        CreateEditInvoiceDialog->setWindowTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Creat/Edit  New Invoice", nullptr));
        clientGroupBox->setTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Client Section", nullptr));
        clientSelectComboBox->setItemText(0, QCoreApplication::translate("CreateEditInvoiceDialog", "Editable", nullptr));
        clientSelectComboBox->setItemText(1, QCoreApplication::translate("CreateEditInvoiceDialog", "Searchable", nullptr));

        clientSelectLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Client Select:", nullptr));
        clientDetailsLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Client Details:", nullptr));
        detailsGroupBox->setTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Invoice Details Section", nullptr));
        invoiceNumberLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Invoice Number:", nullptr));
        IssueDateLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Issue Date:", nullptr));
        paymentTermsLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Payment Terms:", nullptr));
        dueDateLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Due Date:", nullptr));
        lineItemsGroupBox->setTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Line Items Section", nullptr));
        QTableWidgetItem *___qtablewidgetitem = lineItemsTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = lineItemsTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Quantity", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = lineItemsTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Unit Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = lineItemsTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "VAT%", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = lineItemsTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Total", nullptr));
        removeLineItemButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Remove Line Item", nullptr));
        addLineItemButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Add Line Item", nullptr));
        notesGroupBox->setTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Notes Section", nullptr));
        notesLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Notes:", nullptr));
        totalsGroupBox->setTitle(QCoreApplication::translate("CreateEditInvoiceDialog", "Totals Section", nullptr));
        subtotalLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Subtotal:", nullptr));
        subtotalValueLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "SubtotalValue", nullptr));
        totalVATLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Total VAT:", nullptr));
        totalVatValueLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "TotalVATValue", nullptr));
        grandTotalLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Grand Total:", nullptr));
        grandTotalValueLabel->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "GrandTotalValue", nullptr));
        saveDraftButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Save Draft", nullptr));
        saveAndSendButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Save And Send", nullptr));
        cancelInvoiceButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Cancel", nullptr));
        previewButton->setText(QCoreApplication::translate("CreateEditInvoiceDialog", "Preview", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateEditInvoiceDialog: public Ui_CreateEditInvoiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEDITINVOICEDIALOG_H
