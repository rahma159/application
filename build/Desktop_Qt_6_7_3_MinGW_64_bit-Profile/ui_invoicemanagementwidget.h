/********************************************************************************
** Form generated from reading UI file 'invoicemanagementwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVOICEMANAGEMENTWIDGET_H
#define UI_INVOICEMANAGEMENTWIDGET_H

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

QT_BEGIN_NAMESPACE

class Ui_InvoiceManagementWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *newInvoiceButton;
    QPushButton *editInvoiceButton;
    QPushButton *deleteInvoiceButton;
    QPushButton *markAsPaidButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *sendInvoiceButton;
    QPushButton *exportPdfButton;
    QPushButton *exportFecbutton;
    QGridLayout *gridLayout;
    QLabel *statusFilterLabel;
    QLabel *endDateLabel;
    QDateEdit *endDateEdit;
    QLabel *searchInvoiceLabel;
    QComboBox *statusFilterComboBox;
    QLineEdit *searchInvoiceLineEdit;
    QLabel *clientFilterLabel;
    QLabel *startDateLabel;
    QDateEdit *startDateEdit;
    QComboBox *clientFilterComboBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyFiltersButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearFiltersButton;
    QTableView *tableView;
    QHBoxLayout *summaryLayout;
    QLabel *totalInvoicesLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *totalDueLabel;
    QLabel *totalOverdueLabel;
    QLabel *avgPaymentTimeLabel;
    QLabel *financialHealthLabel;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *InvoiceManagementWidget)
    {
        if (InvoiceManagementWidget->objectName().isEmpty())
            InvoiceManagementWidget->setObjectName("InvoiceManagementWidget");
        InvoiceManagementWidget->resize(929, 601);
        InvoiceManagementWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 127);"));
        horizontalLayout_3 = new QHBoxLayout(InvoiceManagementWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        newInvoiceButton = new QPushButton(InvoiceManagementWidget);
        newInvoiceButton->setObjectName("newInvoiceButton");

        horizontalLayout->addWidget(newInvoiceButton);

        editInvoiceButton = new QPushButton(InvoiceManagementWidget);
        editInvoiceButton->setObjectName("editInvoiceButton");

        horizontalLayout->addWidget(editInvoiceButton);

        deleteInvoiceButton = new QPushButton(InvoiceManagementWidget);
        deleteInvoiceButton->setObjectName("deleteInvoiceButton");

        horizontalLayout->addWidget(deleteInvoiceButton);

        markAsPaidButton = new QPushButton(InvoiceManagementWidget);
        markAsPaidButton->setObjectName("markAsPaidButton");

        horizontalLayout->addWidget(markAsPaidButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        sendInvoiceButton = new QPushButton(InvoiceManagementWidget);
        sendInvoiceButton->setObjectName("sendInvoiceButton");

        horizontalLayout->addWidget(sendInvoiceButton);

        exportPdfButton = new QPushButton(InvoiceManagementWidget);
        exportPdfButton->setObjectName("exportPdfButton");

        horizontalLayout->addWidget(exportPdfButton);

        exportFecbutton = new QPushButton(InvoiceManagementWidget);
        exportFecbutton->setObjectName("exportFecbutton");

        horizontalLayout->addWidget(exportFecbutton);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        statusFilterLabel = new QLabel(InvoiceManagementWidget);
        statusFilterLabel->setObjectName("statusFilterLabel");

        gridLayout->addWidget(statusFilterLabel, 1, 0, 1, 1);

        endDateLabel = new QLabel(InvoiceManagementWidget);
        endDateLabel->setObjectName("endDateLabel");

        gridLayout->addWidget(endDateLabel, 4, 0, 1, 1);

        endDateEdit = new QDateEdit(InvoiceManagementWidget);
        endDateEdit->setObjectName("endDateEdit");

        gridLayout->addWidget(endDateEdit, 4, 1, 1, 1);

        searchInvoiceLabel = new QLabel(InvoiceManagementWidget);
        searchInvoiceLabel->setObjectName("searchInvoiceLabel");

        gridLayout->addWidget(searchInvoiceLabel, 0, 0, 1, 1);

        statusFilterComboBox = new QComboBox(InvoiceManagementWidget);
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->setObjectName("statusFilterComboBox");

        gridLayout->addWidget(statusFilterComboBox, 1, 1, 1, 1);

        searchInvoiceLineEdit = new QLineEdit(InvoiceManagementWidget);
        searchInvoiceLineEdit->setObjectName("searchInvoiceLineEdit");

        gridLayout->addWidget(searchInvoiceLineEdit, 0, 1, 1, 1);

        clientFilterLabel = new QLabel(InvoiceManagementWidget);
        clientFilterLabel->setObjectName("clientFilterLabel");

        gridLayout->addWidget(clientFilterLabel, 2, 0, 1, 1);

        startDateLabel = new QLabel(InvoiceManagementWidget);
        startDateLabel->setObjectName("startDateLabel");

        gridLayout->addWidget(startDateLabel, 3, 0, 1, 1);

        startDateEdit = new QDateEdit(InvoiceManagementWidget);
        startDateEdit->setObjectName("startDateEdit");

        gridLayout->addWidget(startDateEdit, 3, 1, 1, 1);

        clientFilterComboBox = new QComboBox(InvoiceManagementWidget);
        clientFilterComboBox->setObjectName("clientFilterComboBox");

        gridLayout->addWidget(clientFilterComboBox, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        applyFiltersButton = new QPushButton(InvoiceManagementWidget);
        applyFiltersButton->setObjectName("applyFiltersButton");

        horizontalLayout_2->addWidget(applyFiltersButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        clearFiltersButton = new QPushButton(InvoiceManagementWidget);
        clearFiltersButton->setObjectName("clearFiltersButton");

        horizontalLayout_2->addWidget(clearFiltersButton);


        gridLayout->addLayout(horizontalLayout_2, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        tableView = new QTableView(InvoiceManagementWidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        summaryLayout = new QHBoxLayout();
        summaryLayout->setObjectName("summaryLayout");
        totalInvoicesLabel = new QLabel(InvoiceManagementWidget);
        totalInvoicesLabel->setObjectName("totalInvoicesLabel");

        summaryLayout->addWidget(totalInvoicesLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_2);

        totalDueLabel = new QLabel(InvoiceManagementWidget);
        totalDueLabel->setObjectName("totalDueLabel");

        summaryLayout->addWidget(totalDueLabel);

        totalOverdueLabel = new QLabel(InvoiceManagementWidget);
        totalOverdueLabel->setObjectName("totalOverdueLabel");

        summaryLayout->addWidget(totalOverdueLabel);

        avgPaymentTimeLabel = new QLabel(InvoiceManagementWidget);
        avgPaymentTimeLabel->setObjectName("avgPaymentTimeLabel");

        summaryLayout->addWidget(avgPaymentTimeLabel);

        financialHealthLabel = new QLabel(InvoiceManagementWidget);
        financialHealthLabel->setObjectName("financialHealthLabel");

        summaryLayout->addWidget(financialHealthLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(summaryLayout);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(InvoiceManagementWidget);

        QMetaObject::connectSlotsByName(InvoiceManagementWidget);
    } // setupUi

    void retranslateUi(QDialog *InvoiceManagementWidget)
    {
        InvoiceManagementWidget->setWindowTitle(QCoreApplication::translate("InvoiceManagementWidget", "Dialog", nullptr));
        newInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "New Invoice", nullptr));
        editInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Edit Invoice", nullptr));
        deleteInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Delete Invoice", nullptr));
        markAsPaidButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Mark As Paid", nullptr));
        sendInvoiceButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Send Invoice", nullptr));
        exportPdfButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Export PDF", nullptr));
        exportFecbutton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Export FEC", nullptr));
        statusFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Status Filter:", nullptr));
        endDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "End Date:", nullptr));
        searchInvoiceLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Search Invoice:", nullptr));
        statusFilterComboBox->setItemText(0, QCoreApplication::translate("InvoiceManagementWidget", "All", nullptr));
        statusFilterComboBox->setItemText(1, QCoreApplication::translate("InvoiceManagementWidget", "Draft", nullptr));
        statusFilterComboBox->setItemText(2, QCoreApplication::translate("InvoiceManagementWidget", "Sent", nullptr));
        statusFilterComboBox->setItemText(3, QCoreApplication::translate("InvoiceManagementWidget", "Paid", nullptr));
        statusFilterComboBox->setItemText(4, QCoreApplication::translate("InvoiceManagementWidget", "Overdue", nullptr));
        statusFilterComboBox->setItemText(5, QCoreApplication::translate("InvoiceManagementWidget", "Partially Paid", nullptr));

        searchInvoiceLineEdit->setText(QString());
        clientFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Client Filter:", nullptr));
        startDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Start Date:", nullptr));
        applyFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Apply Filters", nullptr));
        clearFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "Clear Filters", nullptr));
        totalInvoicesLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Invoices", nullptr));
        totalDueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Due", nullptr));
        totalOverdueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Overdue", nullptr));
        avgPaymentTimeLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Average Payment Time", nullptr));
        financialHealthLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Financial Health", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InvoiceManagementWidget: public Ui_InvoiceManagementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEMANAGEMENTWIDGET_H
