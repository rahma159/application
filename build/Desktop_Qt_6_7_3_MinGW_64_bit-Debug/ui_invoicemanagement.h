/********************************************************************************
** Form generated from reading UI file 'invoicemanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEMANAGEMENT_H
#define UI_INVOICEMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvoiceManagementWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *newInvoiceButton;
    QPushButton *editInvoiceButton;
    QPushButton *deleteInvoiceButton;
    QPushButton *markAsPaidButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *sendInvoiceButton;
    QPushButton *exportPDFButton;
    QPushButton *exportFECButton;
    QGridLayout *gridLayout;
    QLabel *statusFilterLabel;
    QLabel *endDateLabel;
    QDateEdit *endDatePicker;
    QLabel *searchInvoiceLabel;
    QComboBox *statusFilterComboBox;
    QLineEdit *searchInvoiceInput;
    QLabel *clientFilterLabel;
    QLabel *startDateLabel;
    QDateEdit *startDatePicker;
    QComboBox *clientFilterComboBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyFiltersButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearFiltersButton;
    QTableView *invoiceTableView;
    QHBoxLayout *summaryLayout;
    QLabel *totalInvoicesLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *totalDueLabel;
    QLabel *totalOverdueLabel;
    QLabel *averagePaymentTimeLabel;
    QLabel *financialHealthLabel;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *InvoiceManagementWidget)
    {
        if (InvoiceManagementWidget->objectName().isEmpty())
            InvoiceManagementWidget->setObjectName("InvoiceManagementWidget");
        InvoiceManagementWidget->resize(805, 581);
        InvoiceManagementWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(242, 103, 255);\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(51, 0, 138);"));
        verticalLayoutWidget = new QWidget(InvoiceManagementWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 40, 760, 501));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        newInvoiceButton = new QPushButton(verticalLayoutWidget);
        newInvoiceButton->setObjectName("newInvoiceButton");

        horizontalLayout->addWidget(newInvoiceButton);

        editInvoiceButton = new QPushButton(verticalLayoutWidget);
        editInvoiceButton->setObjectName("editInvoiceButton");

        horizontalLayout->addWidget(editInvoiceButton);

        deleteInvoiceButton = new QPushButton(verticalLayoutWidget);
        deleteInvoiceButton->setObjectName("deleteInvoiceButton");

        horizontalLayout->addWidget(deleteInvoiceButton);

        markAsPaidButton = new QPushButton(verticalLayoutWidget);
        markAsPaidButton->setObjectName("markAsPaidButton");

        horizontalLayout->addWidget(markAsPaidButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        sendInvoiceButton = new QPushButton(verticalLayoutWidget);
        sendInvoiceButton->setObjectName("sendInvoiceButton");

        horizontalLayout->addWidget(sendInvoiceButton);

        exportPDFButton = new QPushButton(verticalLayoutWidget);
        exportPDFButton->setObjectName("exportPDFButton");

        horizontalLayout->addWidget(exportPDFButton);

        exportFECButton = new QPushButton(verticalLayoutWidget);
        exportFECButton->setObjectName("exportFECButton");

        horizontalLayout->addWidget(exportFECButton);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        statusFilterLabel = new QLabel(verticalLayoutWidget);
        statusFilterLabel->setObjectName("statusFilterLabel");

        gridLayout->addWidget(statusFilterLabel, 1, 0, 1, 1);

        endDateLabel = new QLabel(verticalLayoutWidget);
        endDateLabel->setObjectName("endDateLabel");

        gridLayout->addWidget(endDateLabel, 4, 0, 1, 1);

        endDatePicker = new QDateEdit(verticalLayoutWidget);
        endDatePicker->setObjectName("endDatePicker");

        gridLayout->addWidget(endDatePicker, 4, 1, 1, 1);

        searchInvoiceLabel = new QLabel(verticalLayoutWidget);
        searchInvoiceLabel->setObjectName("searchInvoiceLabel");

        gridLayout->addWidget(searchInvoiceLabel, 0, 0, 1, 1);

        statusFilterComboBox = new QComboBox(verticalLayoutWidget);
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->setObjectName("statusFilterComboBox");

        gridLayout->addWidget(statusFilterComboBox, 1, 1, 1, 1);

        searchInvoiceInput = new QLineEdit(verticalLayoutWidget);
        searchInvoiceInput->setObjectName("searchInvoiceInput");

        gridLayout->addWidget(searchInvoiceInput, 0, 1, 1, 1);

        clientFilterLabel = new QLabel(verticalLayoutWidget);
        clientFilterLabel->setObjectName("clientFilterLabel");

        gridLayout->addWidget(clientFilterLabel, 2, 0, 1, 1);

        startDateLabel = new QLabel(verticalLayoutWidget);
        startDateLabel->setObjectName("startDateLabel");

        gridLayout->addWidget(startDateLabel, 3, 0, 1, 1);

        startDatePicker = new QDateEdit(verticalLayoutWidget);
        startDatePicker->setObjectName("startDatePicker");

        gridLayout->addWidget(startDatePicker, 3, 1, 1, 1);

        clientFilterComboBox = new QComboBox(verticalLayoutWidget);
        clientFilterComboBox->setObjectName("clientFilterComboBox");

        gridLayout->addWidget(clientFilterComboBox, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        applyFiltersButton = new QPushButton(verticalLayoutWidget);
        applyFiltersButton->setObjectName("applyFiltersButton");

        horizontalLayout_2->addWidget(applyFiltersButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        clearFiltersButton = new QPushButton(verticalLayoutWidget);
        clearFiltersButton->setObjectName("clearFiltersButton");

        horizontalLayout_2->addWidget(clearFiltersButton);


        gridLayout->addLayout(horizontalLayout_2, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        invoiceTableView = new QTableView(verticalLayoutWidget);
        invoiceTableView->setObjectName("invoiceTableView");

        verticalLayout->addWidget(invoiceTableView);

        summaryLayout = new QHBoxLayout();
        summaryLayout->setObjectName("summaryLayout");
        totalInvoicesLabel = new QLabel(verticalLayoutWidget);
        totalInvoicesLabel->setObjectName("totalInvoicesLabel");

        summaryLayout->addWidget(totalInvoicesLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_2);

        totalDueLabel = new QLabel(verticalLayoutWidget);
        totalDueLabel->setObjectName("totalDueLabel");

        summaryLayout->addWidget(totalDueLabel);

        totalOverdueLabel = new QLabel(verticalLayoutWidget);
        totalOverdueLabel->setObjectName("totalOverdueLabel");

        summaryLayout->addWidget(totalOverdueLabel);

        averagePaymentTimeLabel = new QLabel(verticalLayoutWidget);
        averagePaymentTimeLabel->setObjectName("averagePaymentTimeLabel");

        summaryLayout->addWidget(averagePaymentTimeLabel);

        financialHealthLabel = new QLabel(verticalLayoutWidget);
        financialHealthLabel->setObjectName("financialHealthLabel");

        summaryLayout->addWidget(financialHealthLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(summaryLayout);


        retranslateUi(InvoiceManagementWidget);

        QMetaObject::connectSlotsByName(InvoiceManagementWidget);
    } // setupUi

    void retranslateUi(QDialog *InvoiceManagementWidget)
    {
        InvoiceManagementWidget->setWindowTitle(QCoreApplication::translate("InvoiceManagementWidget", "Invoice Management - Smart Consulting Office", nullptr));
        newInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "New Invoice", nullptr));
        editInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Edit Invoice", nullptr));
        deleteInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Delete Invoice", nullptr));
        markAsPaidButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Mark As Paid", nullptr));
        sendInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Send Invoice", nullptr));
        exportPDFButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Export PDF", nullptr));
        exportFECButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Export FEC", nullptr));
        statusFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Status Filter:", nullptr));
        endDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "End Date:", nullptr));
        searchInvoiceLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Search Invoice:", nullptr));
        statusFilterComboBox->setItemText(0, QCoreApplication::translate("InvoiceManagementWidget", "All", nullptr));
        statusFilterComboBox->setItemText(1, QCoreApplication::translate("InvoiceManagementWidget", "Draft", nullptr));
        statusFilterComboBox->setItemText(2, QCoreApplication::translate("InvoiceManagementWidget", "Sent", nullptr));
        statusFilterComboBox->setItemText(3, QCoreApplication::translate("InvoiceManagementWidget", "Paid", nullptr));
        statusFilterComboBox->setItemText(4, QCoreApplication::translate("InvoiceManagementWidget", "Overdue", nullptr));
        statusFilterComboBox->setItemText(5, QCoreApplication::translate("InvoiceManagementWidget", "Partially Paid", nullptr));

        searchInvoiceInput->setText(QString());
        clientFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Client Filter:", nullptr));
        startDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Start Date:", nullptr));
        applyFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Apply Filters", nullptr));
        clearFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Clear Filters", nullptr));
        totalInvoicesLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Invoices", nullptr));
        totalDueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Due", nullptr));
        totalOverdueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Overdue", nullptr));
        averagePaymentTimeLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Average Payment Time", nullptr));
        financialHealthLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Financial Health", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InvoiceManagementWidget: public Ui_InvoiceManagementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEMANAGEMENT_H
