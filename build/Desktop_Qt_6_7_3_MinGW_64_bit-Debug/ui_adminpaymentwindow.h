/********************************************************************************
** Form generated from reading UI file 'adminpaymentwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPAYMENTWINDOW_H
#define UI_ADMINPAYMENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lineEditSearchInvoices
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *logoLabel;
    QLabel *labelDashboardTitle;
    QSpacerItem *horizontalSpacer;
    QLabel *adminNameLabel;
    QPushButton *settingButton;
    QPushButton *logoutButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditSearchInvoices_2;
    QPushButton *pushButtonFilterAll;
    QPushButton *pushButtonFilterDraft;
    QPushButton *pushButtonFilterSent;
    QPushButton *pushButtonFilterPaid;
    QPushButton *pushButtonFilterOverdue;
    QPushButton *pushButtonNewInvoice;
    QPushButton *pushButtonExportFEC;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QTableView *tableViewInvoices;
    QVBoxLayout *verticalLayout_4;
    QDateEdit *dateEdit;
    QComboBox *comboBox;
    QGroupBox *groupBoxStats;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTotalDueValue;
    QLabel *labelOverdueValue;
    QLabel *labelPaidMonthValue;
    QLabel *labelAvgPaymentValue;
    QLabel *labelFinancialHealthValue;
    QGroupBox *chartViewRevenue;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineEdit;
    QGroupBox *groupBoxQuickActions;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonRecordPaymentSidebar;
    QPushButton *buttonDuplicateSidebar;
    QPushButton *buttonDownloadPdfSidebar;
    QPushButton *buttonSendReminderSidebar;

    void setupUi(QDialog *lineEditSearchInvoices)
    {
        if (lineEditSearchInvoices->objectName().isEmpty())
            lineEditSearchInvoices->setObjectName("lineEditSearchInvoices");
        lineEditSearchInvoices->resize(1018, 965);
        lineEditSearchInvoices->setStyleSheet(QString::fromUtf8("/* ~~~~~~~~~~~~~~~~~~ General Styles ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QWidget {\n"
"    /* White base background for content areas */\n"
"    background-color: #FFFFFF;\n"
"    color: #212529; /* Dark text */\n"
"    font-family: Segoe UI, Roboto, Oxygen, Ubuntu, Cantarell, 'Open Sans', 'Helvetica Neue', sans-serif;\n"
"}\n"
"\n"
"/* Style the main window/dialog if needed */\n"
"PaymentWindow, MainWindow { /* Use the actual class names */\n"
"     background-color: #F8F9FA; /* Light off-white for window background */\n"
"}\n"
"\n"
"\n"
"/* Apply general padding/margins to the pages */\n"
"QWidget#pageBooking,\n"
"QWidget#pageConfirmation,\n"
"QWidget#pageCreditCard,\n"
"QWidget#pagePayPal,\n"
"QWidget#pageBankTransfer,\n"
"QWidget#pageProcessing,\n"
"QWidget#pageStatus {\n"
"    padding: 20px;\n"
"    background-color: #FFFFFF; /* Ensure page background is white */\n"
"    border: none; /* Remove any residual borders */\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ Header Area (Logo + Title) ~~~~~~~~~~~~~~~~~~ */\n"
""
                        "\n"
"QLabel[objectName^=\"logoLabel\"] {\n"
"    margin: 10px 10px 5px 15px;\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    padding: 0px;\n"
"}\n"
"\n"
"/* Ensure this objectName is set correctly in Designer! */\n"
"QLabel#labelPageTitle {\n"
"    font-size: 18pt;\n"
"    font-weight: 600; /* Semibold */\n"
"    color: #003366; /* Dark Navy Blue */\n"
"    margin: 0px 15px 30px 15px;\n"
"    padding-bottom: 10px;\n"
"    border-bottom: 2px solid #5CACEE; /* Medium Sky Blue */\n"
"    background-color: transparent;\n"
"    qproperty-alignment: 'AlignLeft | AlignVCenter';\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ GroupBoxes ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QGroupBox {\n"
"    background-color: #FFFFFF; /* White */\n"
"    border: 1px solid #A8D8FF; /* Light Sky Blue border */\n"
"    border-radius: 8px;\n"
"    margin-top: 18px;\n"
"    padding: 30px 20px 20px 20px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 5px"
                        " 15px;\n"
"    left: 15px;\n"
"    color: #003366; /* Dark Navy Blue text */\n"
"    font-weight: 600;\n"
"    /* Light blue gradient for title background */\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0F2FF, stop: 1 #C0E6FF);\n"
"    border: 1px solid #A8D8FF; /* Light Sky Blue border */\n"
"    border-bottom: 1px solid #A8D8FF; /* Need bottom border here */\n"
"    border-top-left-radius: 8px;\n"
"    border-top-right-radius: 8px;\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ Input Fields ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QLineEdit, QComboBox, QDateTimeEdit {\n"
"    border: 1px solid #A8D8FF; /* Light Sky Blue border */\n"
"    padding: 10px 12px;\n"
"    border-radius: 6px;\n"
"    background-color: #FFFFFF;\n"
"    min-height: 24px;\n"
"    font-size: 10pt;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QLineEdit:focus, QComboBox:focus, QDateTimeEdit:focus {\n"
"    border-color: #0056B3; /* Darker Blue focus border */\n"
"    border-width: 1.5px;\n"
"    padding: 9.25px 11.25px;\n"
""
                        "}\n"
"QLineEdit:disabled, QComboBox:disabled, QDateTimeEdit:disabled {\n"
"     background-color: #E9ECEF;\n"
"     color: #6C757D;\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ Buttons ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QPushButton {\n"
"    border-radius: 6px;\n"
"    padding: 10px 18px; /* Adjust padding as needed with icons */\n"
"    font-size: 10pt;\n"
"    font-weight: 500;\n"
"    min-width: 80px;\n"
"    border: 1px solid transparent;\n"
"}\n"
"\n"
"/* --- Primary Buttons (Blue Gradient) --- */\n"
"QPushButton[objectName^=\"pushButtonContinue\"],\n"
"QPushButton[objectName^=\"pushButtonProceed\"],\n"
"QPushButton[objectName^=\"pushButtonSubmit\"],\n"
"QPushButton[objectName^=\"pushButtonConfirm\"],\n"
"QPushButton[objectName^=\"pushButtonGenerate\"],\n"
"QPushButton[objectName^=\"pushButtonBook\"],\n"
"QPushButton[objectName^=\"pushButtonTry\"],\n"
"QPushButton[objectName^=\"pushButtonClose\"] {\n"
"    color: white;\n"
"    /* Blue Gradient */\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2"
                        ": 1, stop: 0 #007BFF, stop: 1 #0056B3);\n"
"    border-color: #0056B3; /* Match darker gradient stop */\n"
"}\n"
"\n"
"QPushButton[objectName^=\"pushButtonContinue\"]:hover, /* etc. apply to all primary types */\n"
"QPushButton[objectName^=\"pushButtonProceed\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonSubmit\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonConfirm\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonGenerate\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonBook\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonTry\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonClose\"]:hover {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0069D9, stop: 1 #004085);\n"
"    border-color: #004085;\n"
"}\n"
"\n"
"QPushButton[objectName^=\"pushButtonContinue\"]:pressed, /* etc. apply to all primary types */\n"
"QPushButton[objectName^=\"pushButtonProceed\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonSubmit\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonConfirm\"]"
                        ":pressed,\n"
"QPushButton[objectName^=\"pushButtonGenerate\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonBook\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonTry\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonClose\"]:pressed {\n"
"    background-color: #004085; /* Solid darkest blue */\n"
"    border-color: #003366;\n"
"}\n"
"\n"
"\n"
"/* --- Secondary Buttons (White/Light Gray with Blue text/border) --- */\n"
"QPushButton[objectName^=\"pushButtonCancel\"],\n"
"QPushButton[objectName^=\"pushButtonBack\"] {\n"
"    background-color: #FFFFFF; /* White background */\n"
"    color: #0056B3; /* Dark Blue text */\n"
"    border: 1px solid #A8D8FF; /* Light Sky Blue border */\n"
"    font-weight: normal;\n"
"}\n"
"\n"
"QPushButton[objectName^=\"pushButtonCancel\"]:hover,\n"
"QPushButton[objectName^=\"pushButtonBack\"]:hover {\n"
"    background-color: #E6F2FF; /* Very light blue hover */\n"
"    border-color: #5CACEE; /* Medium Sky Blue border */\n"
"    color: #003366;\n"
"}\n"
"\n"
"QPushButton[obje"
                        "ctName^=\"pushButtonCancel\"]:pressed,\n"
"QPushButton[objectName^=\"pushButtonBack\"]:pressed {\n"
"    background-color: #D0E4FF; /* Slightly darker light blue pressed */\n"
"    border-color: #0056B3;\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ Radio Buttons ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QRadioButton {\n"
"    background-color: transparent;\n"
"    padding: 6px;\n"
"    spacing: 10px;\n"
"    font-size: 10pt;\n"
"    color: #212529;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 18px;\n"
"    height: 18px;\n"
"    border: 2px solid #A8D8FF; /* Light Sky Blue border */\n"
"    border-radius: 10px;\n"
"    background-color: #FFFFFF;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover {\n"
"    border: 2px solid #007BFF; /* Medium Blue */\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color: #007BFF; /* Fill with Medium Blue */\n"
"    border: 2px solid #0056B3; /* Darker Blue border */\n"
"}\n"
"QRadioButton::indicator:checked:hover {\n"
"     border: 2px solid #003366; /* Darkest Blue *"
                        "/\n"
"}\n"
"\n"
"\n"
"/* ~~~~~~~~~~~~~~~~~~ Status Page Specifics ~~~~~~~~~~~~~~~~~~ */\n"
"\n"
"QLabel#labelStatusMessage {\n"
"    font-size: 22pt;\n"
"    font-weight: 600;\n"
"    qproperty-alignment: 'AlignCenter';\n"
"    margin: 20px 10px 35px 10px;\n"
"    padding: 20px;\n"
"    border-radius: 8px;\n"
"    /* Colors/Backgrounds set dynamically in C++ based on success/fail */\n"
"    /* Example defaults (will be overridden) */\n"
"    color: #212529;\n"
"    background-color: #F8F9FA;\n"
"    border: 1px solid #DEE2E6;\n"
"}\n"
"\n"
"QLabel#labelProcessingText {\n"
"     font-size: 12pt;\n"
"     color: #6C757D;\n"
"     qproperty-alignment: 'AlignCenter';\n"
"     margin-top: 15px;\n"
"     background-color: transparent;\n"
"}\n"
"\n"
"QWidget#widgetTopButtons, QWidget#widgetBottomButtons {\n"
"     background-color: transparent;\n"
"     margin-top: 10px;\n"
"     border: none;\n"
"}\n"
""));
        tabWidget = new QTabWidget(lineEditSearchInvoices);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 310, 831, 291));
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabWidget->addTab(tab_4, QString());
        layoutWidget = new QWidget(lineEditSearchInvoices);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 696, 57));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        logoLabel = new QLabel(layoutWidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        horizontalLayout->addWidget(logoLabel);

        labelDashboardTitle = new QLabel(layoutWidget);
        labelDashboardTitle->setObjectName("labelDashboardTitle");

        horizontalLayout->addWidget(labelDashboardTitle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        adminNameLabel = new QLabel(layoutWidget);
        adminNameLabel->setObjectName("adminNameLabel");

        horizontalLayout->addWidget(adminNameLabel);

        settingButton = new QPushButton(layoutWidget);
        settingButton->setObjectName("settingButton");

        horizontalLayout->addWidget(settingButton);

        logoutButton = new QPushButton(layoutWidget);
        logoutButton->setObjectName("logoutButton");

        horizontalLayout->addWidget(logoutButton);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(lineEditSearchInvoices);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(-10, 60, 1002, 48));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEditSearchInvoices_2 = new QLineEdit(layoutWidget1);
        lineEditSearchInvoices_2->setObjectName("lineEditSearchInvoices_2");

        horizontalLayout_2->addWidget(lineEditSearchInvoices_2);

        pushButtonFilterAll = new QPushButton(layoutWidget1);
        pushButtonFilterAll->setObjectName("pushButtonFilterAll");

        horizontalLayout_2->addWidget(pushButtonFilterAll);

        pushButtonFilterDraft = new QPushButton(layoutWidget1);
        pushButtonFilterDraft->setObjectName("pushButtonFilterDraft");

        horizontalLayout_2->addWidget(pushButtonFilterDraft);

        pushButtonFilterSent = new QPushButton(layoutWidget1);
        pushButtonFilterSent->setObjectName("pushButtonFilterSent");

        horizontalLayout_2->addWidget(pushButtonFilterSent);

        pushButtonFilterPaid = new QPushButton(layoutWidget1);
        pushButtonFilterPaid->setObjectName("pushButtonFilterPaid");

        horizontalLayout_2->addWidget(pushButtonFilterPaid);

        pushButtonFilterOverdue = new QPushButton(layoutWidget1);
        pushButtonFilterOverdue->setObjectName("pushButtonFilterOverdue");

        horizontalLayout_2->addWidget(pushButtonFilterOverdue);

        pushButtonNewInvoice = new QPushButton(layoutWidget1);
        pushButtonNewInvoice->setObjectName("pushButtonNewInvoice");

        horizontalLayout_2->addWidget(pushButtonNewInvoice);

        pushButtonExportFEC = new QPushButton(layoutWidget1);
        pushButtonExportFEC->setObjectName("pushButtonExportFEC");

        horizontalLayout_2->addWidget(pushButtonExportFEC);

        layoutWidget2 = new QWidget(lineEditSearchInvoices);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(327, 131, 601, 111));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        checkBox_4 = new QCheckBox(layoutWidget2);
        checkBox_4->setObjectName("checkBox_4");

        verticalLayout_3->addWidget(checkBox_4);

        checkBox_2 = new QCheckBox(layoutWidget2);
        checkBox_2->setObjectName("checkBox_2");

        verticalLayout_3->addWidget(checkBox_2);

        checkBox = new QCheckBox(layoutWidget2);
        checkBox->setObjectName("checkBox");

        verticalLayout_3->addWidget(checkBox);

        checkBox_3 = new QCheckBox(layoutWidget2);
        checkBox_3->setObjectName("checkBox_3");

        verticalLayout_3->addWidget(checkBox_3);

        tableViewInvoices = new QTableView(layoutWidget2);
        tableViewInvoices->setObjectName("tableViewInvoices");

        verticalLayout_3->addWidget(tableViewInvoices);


        horizontalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        dateEdit = new QDateEdit(layoutWidget2);
        dateEdit->setObjectName("dateEdit");

        verticalLayout_4->addWidget(dateEdit);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->setObjectName("comboBox");

        verticalLayout_4->addWidget(comboBox);

        groupBoxStats = new QGroupBox(layoutWidget2);
        groupBoxStats->setObjectName("groupBoxStats");
        verticalLayout_7 = new QVBoxLayout(groupBoxStats);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        labelTotalDueValue = new QLabel(groupBoxStats);
        labelTotalDueValue->setObjectName("labelTotalDueValue");

        verticalLayout_2->addWidget(labelTotalDueValue);

        labelOverdueValue = new QLabel(groupBoxStats);
        labelOverdueValue->setObjectName("labelOverdueValue");

        verticalLayout_2->addWidget(labelOverdueValue);

        labelPaidMonthValue = new QLabel(groupBoxStats);
        labelPaidMonthValue->setObjectName("labelPaidMonthValue");

        verticalLayout_2->addWidget(labelPaidMonthValue);

        labelAvgPaymentValue = new QLabel(groupBoxStats);
        labelAvgPaymentValue->setObjectName("labelAvgPaymentValue");

        verticalLayout_2->addWidget(labelAvgPaymentValue);

        labelFinancialHealthValue = new QLabel(groupBoxStats);
        labelFinancialHealthValue->setObjectName("labelFinancialHealthValue");

        verticalLayout_2->addWidget(labelFinancialHealthValue);


        verticalLayout_7->addLayout(verticalLayout_2);

        chartViewRevenue = new QGroupBox(groupBoxStats);
        chartViewRevenue->setObjectName("chartViewRevenue");
        verticalLayout_5 = new QVBoxLayout(chartViewRevenue);
        verticalLayout_5->setObjectName("verticalLayout_5");
        lineEdit = new QLineEdit(chartViewRevenue);
        lineEdit->setObjectName("lineEdit");

        verticalLayout_5->addWidget(lineEdit);


        verticalLayout_7->addWidget(chartViewRevenue);

        groupBoxQuickActions = new QGroupBox(groupBoxStats);
        groupBoxQuickActions->setObjectName("groupBoxQuickActions");
        verticalLayout_6 = new QVBoxLayout(groupBoxQuickActions);
        verticalLayout_6->setObjectName("verticalLayout_6");
        lineEdit_2 = new QLineEdit(groupBoxQuickActions);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout_6->addWidget(lineEdit_2);


        verticalLayout_7->addWidget(groupBoxQuickActions);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        buttonRecordPaymentSidebar = new QPushButton(groupBoxStats);
        buttonRecordPaymentSidebar->setObjectName("buttonRecordPaymentSidebar");

        horizontalLayout_3->addWidget(buttonRecordPaymentSidebar);

        buttonDuplicateSidebar = new QPushButton(groupBoxStats);
        buttonDuplicateSidebar->setObjectName("buttonDuplicateSidebar");

        horizontalLayout_3->addWidget(buttonDuplicateSidebar);

        buttonDownloadPdfSidebar = new QPushButton(groupBoxStats);
        buttonDownloadPdfSidebar->setObjectName("buttonDownloadPdfSidebar");

        horizontalLayout_3->addWidget(buttonDownloadPdfSidebar);

        buttonSendReminderSidebar = new QPushButton(groupBoxStats);
        buttonSendReminderSidebar->setObjectName("buttonSendReminderSidebar");

        horizontalLayout_3->addWidget(buttonSendReminderSidebar);


        verticalLayout_7->addLayout(horizontalLayout_3);


        verticalLayout_4->addWidget(groupBoxStats);


        horizontalLayout_4->addLayout(verticalLayout_4);


        retranslateUi(lineEditSearchInvoices);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(lineEditSearchInvoices);
    } // setupUi

    void retranslateUi(QDialog *lineEditSearchInvoices)
    {
        lineEditSearchInvoices->setWindowTitle(QCoreApplication::translate("lineEditSearchInvoices", "Dialog", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("lineEditSearchInvoices", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("lineEditSearchInvoices", "Tab 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("lineEditSearchInvoices", "Page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("lineEditSearchInvoices", "Page", nullptr));
        logoLabel->setText(QString());
        labelDashboardTitle->setText(QCoreApplication::translate("lineEditSearchInvoices", "Admin Dashboard", nullptr));
        adminNameLabel->setText(QCoreApplication::translate("lineEditSearchInvoices", "Welcome, [Admin Name]", nullptr));
        settingButton->setText(QCoreApplication::translate("lineEditSearchInvoices", "Settings", nullptr));
        logoutButton->setText(QCoreApplication::translate("lineEditSearchInvoices", "Log out", nullptr));
        lineEditSearchInvoices_2->setText(QCoreApplication::translate("lineEditSearchInvoices", "Search Invoices", nullptr));
        pushButtonFilterAll->setText(QCoreApplication::translate("lineEditSearchInvoices", "All", nullptr));
        pushButtonFilterDraft->setText(QCoreApplication::translate("lineEditSearchInvoices", "Draft", nullptr));
        pushButtonFilterSent->setText(QCoreApplication::translate("lineEditSearchInvoices", "Sent", nullptr));
        pushButtonFilterPaid->setText(QCoreApplication::translate("lineEditSearchInvoices", "Paid", nullptr));
        pushButtonFilterOverdue->setText(QCoreApplication::translate("lineEditSearchInvoices", "Overdue", nullptr));
        pushButtonNewInvoice->setText(QCoreApplication::translate("lineEditSearchInvoices", "New Invoice", nullptr));
        pushButtonExportFEC->setText(QCoreApplication::translate("lineEditSearchInvoices", "Export FEC", nullptr));
        checkBox_4->setText(QCoreApplication::translate("lineEditSearchInvoices", "Delete Selected Drafts", nullptr));
        checkBox_2->setText(QCoreApplication::translate("lineEditSearchInvoices", "Send Reminders for Selected", nullptr));
        checkBox->setText(QCoreApplication::translate("lineEditSearchInvoices", "Mark Selected as Paid", nullptr));
        checkBox_3->setText(QCoreApplication::translate("lineEditSearchInvoices", "Export Selected", nullptr));
        groupBoxStats->setTitle(QCoreApplication::translate("lineEditSearchInvoices", "Stats", nullptr));
        labelTotalDueValue->setText(QCoreApplication::translate("lineEditSearchInvoices", "TotalDueValue", nullptr));
        labelOverdueValue->setText(QCoreApplication::translate("lineEditSearchInvoices", "OverdueValue", nullptr));
        labelPaidMonthValue->setText(QCoreApplication::translate("lineEditSearchInvoices", "PaidMonthValue", nullptr));
        labelAvgPaymentValue->setText(QCoreApplication::translate("lineEditSearchInvoices", "AvgPaymentValue", nullptr));
        labelFinancialHealthValue->setText(QCoreApplication::translate("lineEditSearchInvoices", "FinancialHealthValue", nullptr));
        chartViewRevenue->setTitle(QCoreApplication::translate("lineEditSearchInvoices", "Chart", nullptr));
        groupBoxQuickActions->setTitle(QCoreApplication::translate("lineEditSearchInvoices", "Quick Actions", nullptr));
        buttonRecordPaymentSidebar->setText(QCoreApplication::translate("lineEditSearchInvoices", "PaymentSidebar", nullptr));
        buttonDuplicateSidebar->setText(QCoreApplication::translate("lineEditSearchInvoices", "DuplicateSidebar", nullptr));
        buttonDownloadPdfSidebar->setText(QCoreApplication::translate("lineEditSearchInvoices", "DownloadPdfSidebar", nullptr));
        buttonSendReminderSidebar->setText(QCoreApplication::translate("lineEditSearchInvoices", "ReminderSidebar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lineEditSearchInvoices: public Ui_lineEditSearchInvoices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPAYMENTWINDOW_H
