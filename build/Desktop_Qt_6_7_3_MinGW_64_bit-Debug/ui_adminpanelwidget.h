/********************************************************************************
** Form generated from reading UI file 'adminpanelwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANELWIDGET_H
#define UI_ADMINPANELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainHorizontalLayout
{
public:
    QHBoxLayout *horizontalLayout_2;
    QListWidget *navigationListWidget;
    QStackedWidget *dashboardPageWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *statsGroupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *statsGridLayout;
    QLabel *totalOverdueLabel_2;
    QLabel *totalDueLabel;
    QLabel *appointmentsTodayLabel;
    QLabel *totalDueValueLabel;
    QLabel *totalOverdueValueLabel;
    QLabel *appointmentsTodayValueLabel;
    QGroupBox *activityGroupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *activityVerticalLayout;
    QListWidget *recentActivityListWidget;
    QTableWidget *tableWidget;
    QWidget *page_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *mainHorizontalLayout)
    {
        if (mainHorizontalLayout->objectName().isEmpty())
            mainHorizontalLayout->setObjectName("mainHorizontalLayout");
        mainHorizontalLayout->resize(924, 416);
        horizontalLayout_2 = new QHBoxLayout(mainHorizontalLayout);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        navigationListWidget = new QListWidget(mainHorizontalLayout);
        navigationListWidget->setObjectName("navigationListWidget");

        horizontalLayout_2->addWidget(navigationListWidget);

        dashboardPageWidget = new QStackedWidget(mainHorizontalLayout);
        dashboardPageWidget->setObjectName("dashboardPageWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName("verticalLayout_2");
        statsGroupBox = new QGroupBox(page);
        statsGroupBox->setObjectName("statsGroupBox");
        gridLayoutWidget = new QWidget(statsGroupBox);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 40, 246, 101));
        statsGridLayout = new QGridLayout(gridLayoutWidget);
        statsGridLayout->setObjectName("statsGridLayout");
        statsGridLayout->setContentsMargins(0, 0, 0, 0);
        totalOverdueLabel_2 = new QLabel(gridLayoutWidget);
        totalOverdueLabel_2->setObjectName("totalOverdueLabel_2");

        statsGridLayout->addWidget(totalOverdueLabel_2, 1, 0, 1, 1);

        totalDueLabel = new QLabel(gridLayoutWidget);
        totalDueLabel->setObjectName("totalDueLabel");

        statsGridLayout->addWidget(totalDueLabel, 0, 0, 1, 1);

        appointmentsTodayLabel = new QLabel(gridLayoutWidget);
        appointmentsTodayLabel->setObjectName("appointmentsTodayLabel");

        statsGridLayout->addWidget(appointmentsTodayLabel, 2, 0, 1, 1);

        totalDueValueLabel = new QLabel(gridLayoutWidget);
        totalDueValueLabel->setObjectName("totalDueValueLabel");

        statsGridLayout->addWidget(totalDueValueLabel, 0, 1, 1, 1);

        totalOverdueValueLabel = new QLabel(gridLayoutWidget);
        totalOverdueValueLabel->setObjectName("totalOverdueValueLabel");

        statsGridLayout->addWidget(totalOverdueValueLabel, 1, 1, 1, 1);

        appointmentsTodayValueLabel = new QLabel(gridLayoutWidget);
        appointmentsTodayValueLabel->setObjectName("appointmentsTodayValueLabel");

        statsGridLayout->addWidget(appointmentsTodayValueLabel, 2, 1, 1, 1);


        verticalLayout_2->addWidget(statsGroupBox);

        activityGroupBox = new QGroupBox(page);
        activityGroupBox->setObjectName("activityGroupBox");
        verticalLayoutWidget = new QWidget(activityGroupBox);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 30, 160, 148));
        activityVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
        activityVerticalLayout->setObjectName("activityVerticalLayout");
        activityVerticalLayout->setContentsMargins(0, 0, 0, 0);
        recentActivityListWidget = new QListWidget(verticalLayoutWidget);
        recentActivityListWidget->setObjectName("recentActivityListWidget");

        activityVerticalLayout->addWidget(recentActivityListWidget);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        tableWidget->setObjectName("tableWidget");

        activityVerticalLayout->addWidget(tableWidget);


        verticalLayout_2->addWidget(activityGroupBox);

        dashboardPageWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayoutWidget_2 = new QWidget(page_2);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 210, 311, 91));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_2 = new QTableWidget(verticalLayoutWidget_2);
        if (tableWidget_2->columnCount() < 13)
            tableWidget_2->setColumnCount(13);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setColumnCount(13);

        verticalLayout->addWidget(tableWidget_2);

        horizontalLayoutWidget = new QWidget(page_2);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 110, 371, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        dashboardPageWidget->addWidget(page_2);

        horizontalLayout_2->addWidget(dashboardPageWidget);


        retranslateUi(mainHorizontalLayout);

        dashboardPageWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(mainHorizontalLayout);
    } // setupUi

    void retranslateUi(QDialog *mainHorizontalLayout)
    {
        mainHorizontalLayout->setWindowTitle(QCoreApplication::translate("mainHorizontalLayout", "Dialog", nullptr));
        statsGroupBox->setTitle(QCoreApplication::translate("mainHorizontalLayout", "Key Statistics", nullptr));
        totalOverdueLabel_2->setText(QCoreApplication::translate("mainHorizontalLayout", "Total Overdue:", nullptr));
        totalDueLabel->setText(QCoreApplication::translate("mainHorizontalLayout", "Total Due:", nullptr));
        appointmentsTodayLabel->setText(QCoreApplication::translate("mainHorizontalLayout", "Appointments Today:", nullptr));
        totalDueValueLabel->setText(QCoreApplication::translate("mainHorizontalLayout", "totalDueValueLabel", nullptr));
        totalOverdueValueLabel->setText(QCoreApplication::translate("mainHorizontalLayout", "totalOverdueValueLabel", nullptr));
        appointmentsTodayValueLabel->setText(QCoreApplication::translate("mainHorizontalLayout", "TextLabel", nullptr));
        activityGroupBox->setTitle(QCoreApplication::translate("mainHorizontalLayout", "Recent Activity", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("mainHorizontalLayout", "Invoice #", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("mainHorizontalLayout", "Client", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("mainHorizontalLayout", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("mainHorizontalLayout", "Date Issued", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("mainHorizontalLayout", "Due Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("mainHorizontalLayout", "Amount", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("mainHorizontalLayout", "Status", nullptr));
        label->setText(QCoreApplication::translate("mainHorizontalLayout", "Search:", nullptr));
        label_2->setText(QCoreApplication::translate("mainHorizontalLayout", "Status:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("mainHorizontalLayout", "All", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("mainHorizontalLayout", "Draft", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("mainHorizontalLayout", "Sent", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("mainHorizontalLayout", "Paid", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("mainHorizontalLayout", "Overdue", nullptr));

        pushButton->setText(QCoreApplication::translate("mainHorizontalLayout", "New Invoice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainHorizontalLayout: public Ui_mainHorizontalLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANELWIDGET_H
