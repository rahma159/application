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
#include <QtWidgets/QFrame>
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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *exportInvoiceListPdfButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *exportFecButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *viewStatisticsButton;
    QSpacerItem *horizontalSpacer_13;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QLabel *startDateLabel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyFiltersButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearFiltersButton;
    QDateEdit *endDateEdit;
    QDateEdit *startDateEdit;
    QComboBox *statusFilterComboBox;
    QLabel *endDateLabel;
    QLineEdit *searchInvoiceLineEdit;
    QLabel *searchInvoiceLabel;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *clientFilterComboBox;
    QLabel *clientFilterLabel;
    QLabel *statusFilterLabel;
    QSpacerItem *horizontalSpacer_8;
    QFrame *line_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *sortComboBox;
    QSpacerItem *horizontalSpacer_5;
    QTableView *tableView;
    QSpacerItem *horizontalSpacer_10;
    QFrame *line;
    QHBoxLayout *summaryLayout;
    QSpacerItem *horizontalSpacer_11;
    QLabel *totalInvoicesLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *totalDueLabel;
    QSpacerItem *horizontalSpacer_15;
    QLabel *totalOverdueLabel;
    QSpacerItem *horizontalSpacer_16;
    QLabel *avgPaymentTimeLabel;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *manualTestButton;
    QLabel *financialHealthLabel;
    QSpacerItem *horizontalSpacer_12;

    void setupUi(QDialog *InvoiceManagementWidget)
    {
        if (InvoiceManagementWidget->objectName().isEmpty())
            InvoiceManagementWidget->setObjectName("InvoiceManagementWidget");
        InvoiceManagementWidget->resize(1000, 645);
        InvoiceManagementWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 127);"));
        verticalLayout = new QVBoxLayout(InvoiceManagementWidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        exportInvoiceListPdfButton = new QPushButton(InvoiceManagementWidget);
        exportInvoiceListPdfButton->setObjectName("exportInvoiceListPdfButton");

        horizontalLayout->addWidget(exportInvoiceListPdfButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        exportFecButton = new QPushButton(InvoiceManagementWidget);
        exportFecButton->setObjectName("exportFecButton");

        horizontalLayout->addWidget(exportFecButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        viewStatisticsButton = new QPushButton(InvoiceManagementWidget);
        viewStatisticsButton->setObjectName("viewStatisticsButton");

        horizontalLayout->addWidget(viewStatisticsButton);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);


        verticalLayout->addLayout(horizontalLayout);

        line_3 = new QFrame(InvoiceManagementWidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        startDateLabel = new QLabel(InvoiceManagementWidget);
        startDateLabel->setObjectName("startDateLabel");

        gridLayout->addWidget(startDateLabel, 3, 1, 1, 1);

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


        gridLayout->addLayout(horizontalLayout_2, 5, 2, 1, 1);

        endDateEdit = new QDateEdit(InvoiceManagementWidget);
        endDateEdit->setObjectName("endDateEdit");

        gridLayout->addWidget(endDateEdit, 4, 2, 1, 1);

        startDateEdit = new QDateEdit(InvoiceManagementWidget);
        startDateEdit->setObjectName("startDateEdit");

        gridLayout->addWidget(startDateEdit, 3, 2, 1, 1);

        statusFilterComboBox = new QComboBox(InvoiceManagementWidget);
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->addItem(QString());
        statusFilterComboBox->setObjectName("statusFilterComboBox");

        gridLayout->addWidget(statusFilterComboBox, 1, 2, 1, 1);

        endDateLabel = new QLabel(InvoiceManagementWidget);
        endDateLabel->setObjectName("endDateLabel");

        gridLayout->addWidget(endDateLabel, 4, 1, 1, 1);

        searchInvoiceLineEdit = new QLineEdit(InvoiceManagementWidget);
        searchInvoiceLineEdit->setObjectName("searchInvoiceLineEdit");

        gridLayout->addWidget(searchInvoiceLineEdit, 0, 2, 1, 1);

        searchInvoiceLabel = new QLabel(InvoiceManagementWidget);
        searchInvoiceLabel->setObjectName("searchInvoiceLabel");

        gridLayout->addWidget(searchInvoiceLabel, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 2, 0, 1, 1);

        clientFilterComboBox = new QComboBox(InvoiceManagementWidget);
        clientFilterComboBox->setObjectName("clientFilterComboBox");

        gridLayout->addWidget(clientFilterComboBox, 2, 2, 1, 1);

        clientFilterLabel = new QLabel(InvoiceManagementWidget);
        clientFilterLabel->setObjectName("clientFilterLabel");

        gridLayout->addWidget(clientFilterLabel, 2, 1, 1, 1);

        statusFilterLabel = new QLabel(InvoiceManagementWidget);
        statusFilterLabel->setObjectName("statusFilterLabel");

        gridLayout->addWidget(statusFilterLabel, 1, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        line_2 = new QFrame(InvoiceManagementWidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(InvoiceManagementWidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        sortComboBox = new QComboBox(InvoiceManagementWidget);
        sortComboBox->setObjectName("sortComboBox");

        horizontalLayout_3->addWidget(sortComboBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        tableView = new QTableView(InvoiceManagementWidget);
        tableView->setObjectName("tableView");

        gridLayout_2->addWidget(tableView, 1, 1, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        line = new QFrame(InvoiceManagementWidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        summaryLayout = new QHBoxLayout();
        summaryLayout->setObjectName("summaryLayout");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_11);

        totalInvoicesLabel = new QLabel(InvoiceManagementWidget);
        totalInvoicesLabel->setObjectName("totalInvoicesLabel");

        summaryLayout->addWidget(totalInvoicesLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_2);

        totalDueLabel = new QLabel(InvoiceManagementWidget);
        totalDueLabel->setObjectName("totalDueLabel");

        summaryLayout->addWidget(totalDueLabel);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_15);

        totalOverdueLabel = new QLabel(InvoiceManagementWidget);
        totalOverdueLabel->setObjectName("totalOverdueLabel");

        summaryLayout->addWidget(totalOverdueLabel);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_16);

        avgPaymentTimeLabel = new QLabel(InvoiceManagementWidget);
        avgPaymentTimeLabel->setObjectName("avgPaymentTimeLabel");

        summaryLayout->addWidget(avgPaymentTimeLabel);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_14);

        manualTestButton = new QPushButton(InvoiceManagementWidget);
        manualTestButton->setObjectName("manualTestButton");

        summaryLayout->addWidget(manualTestButton);

        financialHealthLabel = new QLabel(InvoiceManagementWidget);
        financialHealthLabel->setObjectName("financialHealthLabel");

        summaryLayout->addWidget(financialHealthLabel);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        summaryLayout->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(summaryLayout);


        retranslateUi(InvoiceManagementWidget);

        QMetaObject::connectSlotsByName(InvoiceManagementWidget);
    } // setupUi

    void retranslateUi(QDialog *InvoiceManagementWidget)
    {
        InvoiceManagementWidget->setWindowTitle(QCoreApplication::translate("InvoiceManagementWidget", "Dialog", nullptr));
        exportInvoiceListPdfButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "\360\237\223\204Export invoice list as PDF", nullptr));
        exportFecButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "\360\237\223\212Export in FEC format", nullptr));
        viewStatisticsButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "\360\237\223\211View invoice statistics", nullptr));
        startDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Start Date:", nullptr));
        applyFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "\342\234\205Apply Filters", nullptr));
        clearFiltersButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "\360\237\247\271Clear Filters", nullptr));
        statusFilterComboBox->setItemText(0, QCoreApplication::translate("InvoiceManagementWidget", "All", nullptr));
        statusFilterComboBox->setItemText(1, QCoreApplication::translate("InvoiceManagementWidget", "Draft", nullptr));
        statusFilterComboBox->setItemText(2, QCoreApplication::translate("InvoiceManagementWidget", "Sent", nullptr));
        statusFilterComboBox->setItemText(3, QCoreApplication::translate("InvoiceManagementWidget", "Paid", nullptr));
        statusFilterComboBox->setItemText(4, QCoreApplication::translate("InvoiceManagementWidget", "Overdue", nullptr));
        statusFilterComboBox->setItemText(5, QCoreApplication::translate("InvoiceManagementWidget", "Partially Paid", nullptr));

        endDateLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "End Date:", nullptr));
        searchInvoiceLineEdit->setText(QString());
        searchInvoiceLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "\360\237\224\215Search Invoice:", nullptr));
        clientFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Client Filter:", nullptr));
        statusFilterLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Status Filter:", nullptr));
        label->setText(QCoreApplication::translate("InvoiceManagementWidget", "\342\254\206\357\270\217\342\254\207\357\270\217Sort by:", nullptr));
        totalInvoicesLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Invoices", nullptr));
        totalDueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Due", nullptr));
        totalOverdueLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Total Overdue", nullptr));
        avgPaymentTimeLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Average Payment Time", nullptr));
        manualTestButton->setText(QCoreApplication::translate("InvoiceManagementWidget", "test", nullptr));
        financialHealthLabel->setText(QCoreApplication::translate("InvoiceManagementWidget", "Financial Health", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InvoiceManagementWidget: public Ui_InvoiceManagementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVOICEMANAGEMENTWIDGET_H
