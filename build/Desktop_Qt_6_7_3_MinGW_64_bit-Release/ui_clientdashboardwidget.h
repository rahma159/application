/********************************************************************************
** Form generated from reading UI file 'clientdashboardwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTDASHBOARDWIDGET_H
#define UI_CLIENTDASHBOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ClientDashboardWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainLayout;
    QLabel *welcomeHeaderLabel;
    QTableView *clientInvoiceTable;
    QLabel *footerLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *viewDetailsButton;
    QPushButton *payNowButton;

    void setupUi(QDialog *ClientDashboardWidget)
    {
        if (ClientDashboardWidget->objectName().isEmpty())
            ClientDashboardWidget->setObjectName("ClientDashboardWidget");
        ClientDashboardWidget->resize(685, 449);
        horizontalLayout_2 = new QHBoxLayout(ClientDashboardWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        mainLayout = new QVBoxLayout();
        mainLayout->setObjectName("mainLayout");
        welcomeHeaderLabel = new QLabel(ClientDashboardWidget);
        welcomeHeaderLabel->setObjectName("welcomeHeaderLabel");

        mainLayout->addWidget(welcomeHeaderLabel);

        clientInvoiceTable = new QTableView(ClientDashboardWidget);
        clientInvoiceTable->setObjectName("clientInvoiceTable");

        mainLayout->addWidget(clientInvoiceTable);

        footerLabel = new QLabel(ClientDashboardWidget);
        footerLabel->setObjectName("footerLabel");

        mainLayout->addWidget(footerLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        viewDetailsButton = new QPushButton(ClientDashboardWidget);
        viewDetailsButton->setObjectName("viewDetailsButton");

        horizontalLayout->addWidget(viewDetailsButton);

        payNowButton = new QPushButton(ClientDashboardWidget);
        payNowButton->setObjectName("payNowButton");

        horizontalLayout->addWidget(payNowButton);


        mainLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(mainLayout);


        retranslateUi(ClientDashboardWidget);

        QMetaObject::connectSlotsByName(ClientDashboardWidget);
    } // setupUi

    void retranslateUi(QDialog *ClientDashboardWidget)
    {
        ClientDashboardWidget->setWindowTitle(QCoreApplication::translate("ClientDashboardWidget", "Dialog", nullptr));
        welcomeHeaderLabel->setText(QCoreApplication::translate("ClientDashboardWidget", "Your Invoices, [Client Name]", nullptr));
        footerLabel->setText(QCoreApplication::translate("ClientDashboardWidget", "Contact info, etc...", nullptr));
        viewDetailsButton->setText(QCoreApplication::translate("ClientDashboardWidget", "View Details", nullptr));
        payNowButton->setText(QCoreApplication::translate("ClientDashboardWidget", "Pay Now", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientDashboardWidget: public Ui_ClientDashboardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTDASHBOARDWIDGET_H
