/********************************************************************************
** Form generated from reading UI file 'paymentwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYMENTWINDOW_H
#define UI_PAYMENTWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PaymentWindow
{
public:
    QGridLayout *gridLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *pageBooking;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *logoLabel_2;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_11;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxPersonalInfo;
    QFormLayout *formLayout;
    QLabel *labelFullNameStatic;
    QLineEdit *lineEditFullName;
    QLabel *labelEmailStatic;
    QLineEdit *lineEditEmail;
    QLabel *labelPhoneStatic;
    QLineEdit *lineEditPhone;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBoxAppointmentDetails;
    QFormLayout *formLayout_2;
    QLabel *labelConsultTypeStatic;
    QComboBox *comboBoxConsultationType;
    QLabel *labelApptDateStatic;
    QDateTimeEdit *dateTimeEditAppointment;
    QSpacerItem *verticalSpacer_13;
    QHBoxLayout *horizontalLayoutButtons_1;
    QPushButton *pushButtonCancelBooking;
    QSpacerItem *horizontalSpacer_1;
    QPushButton *pushButtonContinue;
    QWidget *pageConfirmation;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayoutPageConfirm;
    QGroupBox *groupBoxSummary;
    QFormLayout *formLayout_4;
    QLabel *labelSumNameStatic;
    QLabel *labelSummaryName;
    QLabel *labelSumEmailStatic;
    QLabel *labelSummaryEmail;
    QLabel *labelSumPhoneStatic;
    QLabel *labelSummaryPhone;
    QLabel *labelSumConsultStatic;
    QLabel *labelSummaryConsultation;
    QLabel *labelSumDateStatic;
    QLabel *labelSummaryDate;
    QLabel *labelSumAmountStatic;
    QLabel *labelSummaryAmount;
    QGroupBox *groupBoxPaymentMethod;
    QFormLayout *formLayout_3;
    QRadioButton *radioButtonPayPal;
    QRadioButton *radioButtonCreditCard;
    QRadioButton *radioButtonBankTransfer;
    QHBoxLayout *horizontalLayoutButtons_2;
    QPushButton *pushButtonBackConfirm;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonProceedToPay;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *logoLabel;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_4;
    QWidget *pageCreditCard;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *logoLabel_8;
    QLabel *label_9;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayoutPageCard;
    QGroupBox *groupBoxCreditCardInput;
    QFormLayout *formLayout_6;
    QLabel *labelCardNumberStatic;
    QLineEdit *lineEditCardNumber;
    QLabel *labelCardNameStatic;
    QLineEdit *lineEditCardName;
    QLabel *labelExpiryDateStatic;
    QLineEdit *lineEditExpiryDate;
    QLabel *labelCvvStatic;
    QLineEdit *lineEditCvv;
    QHBoxLayout *horizontalLayoutButtons_3;
    QPushButton *pushButtonBackCard;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonSubmitPayment;
    QSpacerItem *verticalSpacer_12;
    QWidget *pagePayPal;
    QVBoxLayout *verticalLayout_14;
    QVBoxLayout *verticalLayout_7;
    QLabel *logoLabel_9;
    QLabel *label_10;
    QSpacerItem *verticalSpacer_5;
    QVBoxLayout *verticalLayoutPagePayPal;
    QLabel *labelPayPalInfo;
    QSpacerItem *verticalSpacerPayPal;
    QHBoxLayout *horizontalLayoutButtons_4;
    QPushButton *pushButtonBackPayPal;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButtonProceedPayPal;
    QSpacerItem *verticalSpacer_14;
    QWidget *pageBankTransfer;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *logoLabel_10;
    QLabel *label_11;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayoutPageBank;
    QGroupBox *groupBoxBankDetails;
    QFormLayout *formLayout_7;
    QLabel *labelBankInfoIntro;
    QLabel *labelBankNameStatic;
    QLabel *labelBankNameValue;
    QLabel *labelAccountNumStatic;
    QLabel *labelAccountNumValue;
    QLabel *labelSortCodeStatic;
    QLabel *labelSortCodeValue;
    QLabel *labelReferenceInfo;
    QLabel *labelReferenceValue;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayoutButtons_5;
    QPushButton *pushButtonBackBank;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonConfirmTransfer;
    QSpacerItem *verticalSpacer_15;
    QWidget *pageProcessing;
    QVBoxLayout *verticalLayout_16;
    QVBoxLayout *verticalLayout_9;
    QLabel *logoLabel_11;
    QLabel *label_12;
    QSpacerItem *verticalSpacer_8;
    QVBoxLayout *verticalLayoutPageProcess;
    QSpacerItem *verticalSpacerTopProcessing;
    QLabel *labelProcessingAnimation;
    QLabel *labelProcessingText;
    QSpacerItem *verticalSpacerBotProcessing;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageStatus;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *logoLabel_12;
    QLabel *label_13;
    QVBoxLayout *verticalLayoutPageStatus;
    QWidget *widgetActionButtons;
    QVBoxLayout *verticalLayout_6;
    QLabel *labelStatusMessage;
    QGroupBox *groupBoxTransactionSummary;
    QFormLayout *formLayout_5;
    QLabel *labelTransIdStatic;
    QLabel *labelTransactionIdValue;
    QLabel *labelTransMethodStatic;
    QLabel *labelPaymentMethodValue;
    QLabel *labelTransAmountStatic;
    QLabel *labelAmountPaidValue;
    QLabel *labelTransTimestampStatic;
    QLabel *labelTransactionTimestampValue;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacerStatus;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButtonGenerateInvoice;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButtonCloseStatus;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonBookAnother;
    QPushButton *pushButtonTryAgain;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_16;
    QSpacerItem *verticalSpacer_17;
    QSpacerItem *verticalSpacer_18;

    void setupUi(QDialog *PaymentWindow)
    {
        if (PaymentWindow->objectName().isEmpty())
            PaymentWindow->setObjectName("PaymentWindow");
        PaymentWindow->resize(828, 724);
        PaymentWindow->setCursor(QCursor(Qt::CursorShape::BusyCursor));
        PaymentWindow->setAcceptDrops(false);
        PaymentWindow->setAutoFillBackground(false);
        PaymentWindow->setStyleSheet(QString::fromUtf8("/* ~~~~~~~~~~~~~~~~~~ General Styles ~~~~~~~~~~~~~~~~~~ */\n"
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
"}"));
        gridLayout_5 = new QGridLayout(PaymentWindow);
        gridLayout_5->setObjectName("gridLayout_5");
        stackedWidget = new QStackedWidget(PaymentWindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pageBooking = new QWidget();
        pageBooking->setObjectName("pageBooking");
        gridLayout_3 = new QGridLayout(pageBooking);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        logoLabel_2 = new QLabel(pageBooking);
        logoLabel_2->setObjectName("logoLabel_2");
        logoLabel_2->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout->addWidget(logoLabel_2);

        label_5 = new QLabel(pageBooking);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(label_5);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer_11, 1, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBoxPersonalInfo = new QGroupBox(pageBooking);
        groupBoxPersonalInfo->setObjectName("groupBoxPersonalInfo");
        formLayout = new QFormLayout(groupBoxPersonalInfo);
        formLayout->setObjectName("formLayout");
        labelFullNameStatic = new QLabel(groupBoxPersonalInfo);
        labelFullNameStatic->setObjectName("labelFullNameStatic");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelFullNameStatic);

        lineEditFullName = new QLineEdit(groupBoxPersonalInfo);
        lineEditFullName->setObjectName("lineEditFullName");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditFullName);

        labelEmailStatic = new QLabel(groupBoxPersonalInfo);
        labelEmailStatic->setObjectName("labelEmailStatic");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelEmailStatic);

        lineEditEmail = new QLineEdit(groupBoxPersonalInfo);
        lineEditEmail->setObjectName("lineEditEmail");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditEmail);

        labelPhoneStatic = new QLabel(groupBoxPersonalInfo);
        labelPhoneStatic->setObjectName("labelPhoneStatic");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelPhoneStatic);

        lineEditPhone = new QLineEdit(groupBoxPersonalInfo);
        lineEditPhone->setObjectName("lineEditPhone");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPhone);

        label = new QLabel(groupBoxPersonalInfo);
        label->setObjectName("label");

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBoxPersonalInfo);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::FieldRole, label_2);


        verticalLayout_5->addWidget(groupBoxPersonalInfo);

        groupBoxAppointmentDetails = new QGroupBox(pageBooking);
        groupBoxAppointmentDetails->setObjectName("groupBoxAppointmentDetails");
        formLayout_2 = new QFormLayout(groupBoxAppointmentDetails);
        formLayout_2->setObjectName("formLayout_2");
        labelConsultTypeStatic = new QLabel(groupBoxAppointmentDetails);
        labelConsultTypeStatic->setObjectName("labelConsultTypeStatic");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelConsultTypeStatic);

        comboBoxConsultationType = new QComboBox(groupBoxAppointmentDetails);
        comboBoxConsultationType->addItem(QString());
        comboBoxConsultationType->addItem(QString());
        comboBoxConsultationType->addItem(QString());
        comboBoxConsultationType->setObjectName("comboBoxConsultationType");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBoxConsultationType);

        labelApptDateStatic = new QLabel(groupBoxAppointmentDetails);
        labelApptDateStatic->setObjectName("labelApptDateStatic");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelApptDateStatic);

        dateTimeEditAppointment = new QDateTimeEdit(groupBoxAppointmentDetails);
        dateTimeEditAppointment->setObjectName("dateTimeEditAppointment");
        dateTimeEditAppointment->setMinimumDate(QDate(2025, 4, 1));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, dateTimeEditAppointment);


        verticalLayout_5->addWidget(groupBoxAppointmentDetails);


        gridLayout_3->addLayout(verticalLayout_5, 2, 0, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_3->addItem(verticalSpacer_13, 3, 0, 1, 1);

        horizontalLayoutButtons_1 = new QHBoxLayout();
        horizontalLayoutButtons_1->setObjectName("horizontalLayoutButtons_1");
        pushButtonCancelBooking = new QPushButton(pageBooking);
        pushButtonCancelBooking->setObjectName("pushButtonCancelBooking");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        pushButtonCancelBooking->setIcon(icon);

        horizontalLayoutButtons_1->addWidget(pushButtonCancelBooking);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons_1->addItem(horizontalSpacer_1);

        pushButtonContinue = new QPushButton(pageBooking);
        pushButtonContinue->setObjectName("pushButtonContinue");

        horizontalLayoutButtons_1->addWidget(pushButtonContinue);


        gridLayout_3->addLayout(horizontalLayoutButtons_1, 4, 0, 1, 1);

        stackedWidget->addWidget(pageBooking);
        pageConfirmation = new QWidget();
        pageConfirmation->setObjectName("pageConfirmation");
        gridLayout_2 = new QGridLayout(pageConfirmation);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayoutPageConfirm = new QVBoxLayout();
        verticalLayoutPageConfirm->setObjectName("verticalLayoutPageConfirm");
        groupBoxSummary = new QGroupBox(pageConfirmation);
        groupBoxSummary->setObjectName("groupBoxSummary");
        formLayout_4 = new QFormLayout(groupBoxSummary);
        formLayout_4->setObjectName("formLayout_4");
        labelSumNameStatic = new QLabel(groupBoxSummary);
        labelSumNameStatic->setObjectName("labelSumNameStatic");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, labelSumNameStatic);

        labelSummaryName = new QLabel(groupBoxSummary);
        labelSummaryName->setObjectName("labelSummaryName");

        formLayout_4->setWidget(0, QFormLayout::FieldRole, labelSummaryName);

        labelSumEmailStatic = new QLabel(groupBoxSummary);
        labelSumEmailStatic->setObjectName("labelSumEmailStatic");

        formLayout_4->setWidget(1, QFormLayout::LabelRole, labelSumEmailStatic);

        labelSummaryEmail = new QLabel(groupBoxSummary);
        labelSummaryEmail->setObjectName("labelSummaryEmail");

        formLayout_4->setWidget(1, QFormLayout::FieldRole, labelSummaryEmail);

        labelSumPhoneStatic = new QLabel(groupBoxSummary);
        labelSumPhoneStatic->setObjectName("labelSumPhoneStatic");

        formLayout_4->setWidget(2, QFormLayout::LabelRole, labelSumPhoneStatic);

        labelSummaryPhone = new QLabel(groupBoxSummary);
        labelSummaryPhone->setObjectName("labelSummaryPhone");

        formLayout_4->setWidget(2, QFormLayout::FieldRole, labelSummaryPhone);

        labelSumConsultStatic = new QLabel(groupBoxSummary);
        labelSumConsultStatic->setObjectName("labelSumConsultStatic");

        formLayout_4->setWidget(3, QFormLayout::LabelRole, labelSumConsultStatic);

        labelSummaryConsultation = new QLabel(groupBoxSummary);
        labelSummaryConsultation->setObjectName("labelSummaryConsultation");

        formLayout_4->setWidget(3, QFormLayout::FieldRole, labelSummaryConsultation);

        labelSumDateStatic = new QLabel(groupBoxSummary);
        labelSumDateStatic->setObjectName("labelSumDateStatic");

        formLayout_4->setWidget(4, QFormLayout::LabelRole, labelSumDateStatic);

        labelSummaryDate = new QLabel(groupBoxSummary);
        labelSummaryDate->setObjectName("labelSummaryDate");

        formLayout_4->setWidget(4, QFormLayout::FieldRole, labelSummaryDate);

        labelSumAmountStatic = new QLabel(groupBoxSummary);
        labelSumAmountStatic->setObjectName("labelSumAmountStatic");

        formLayout_4->setWidget(5, QFormLayout::LabelRole, labelSumAmountStatic);

        labelSummaryAmount = new QLabel(groupBoxSummary);
        labelSummaryAmount->setObjectName("labelSummaryAmount");

        formLayout_4->setWidget(5, QFormLayout::FieldRole, labelSummaryAmount);


        verticalLayoutPageConfirm->addWidget(groupBoxSummary);

        groupBoxPaymentMethod = new QGroupBox(pageConfirmation);
        groupBoxPaymentMethod->setObjectName("groupBoxPaymentMethod");
        formLayout_3 = new QFormLayout(groupBoxPaymentMethod);
        formLayout_3->setObjectName("formLayout_3");
        radioButtonPayPal = new QRadioButton(groupBoxPaymentMethod);
        radioButtonPayPal->setObjectName("radioButtonPayPal");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, radioButtonPayPal);

        radioButtonCreditCard = new QRadioButton(groupBoxPaymentMethod);
        radioButtonCreditCard->setObjectName("radioButtonCreditCard");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, radioButtonCreditCard);

        radioButtonBankTransfer = new QRadioButton(groupBoxPaymentMethod);
        radioButtonBankTransfer->setObjectName("radioButtonBankTransfer");

        formLayout_3->setWidget(2, QFormLayout::LabelRole, radioButtonBankTransfer);


        verticalLayoutPageConfirm->addWidget(groupBoxPaymentMethod);


        gridLayout_2->addLayout(verticalLayoutPageConfirm, 2, 0, 1, 1);

        horizontalLayoutButtons_2 = new QHBoxLayout();
        horizontalLayoutButtons_2->setObjectName("horizontalLayoutButtons_2");
        pushButtonBackConfirm = new QPushButton(pageConfirmation);
        pushButtonBackConfirm->setObjectName("pushButtonBackConfirm");

        horizontalLayoutButtons_2->addWidget(pushButtonBackConfirm);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons_2->addItem(horizontalSpacer_2);

        pushButtonProceedToPay = new QPushButton(pageConfirmation);
        pushButtonProceedToPay->setObjectName("pushButtonProceedToPay");

        horizontalLayoutButtons_2->addWidget(pushButtonProceedToPay);


        gridLayout_2->addLayout(horizontalLayoutButtons_2, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_2->addItem(verticalSpacer_3, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        logoLabel = new QLabel(pageConfirmation);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_3->addWidget(logoLabel);

        label_6 = new QLabel(pageConfirmation);
        label_6->setObjectName("label_6");
        label_6->setIndent(-1);

        verticalLayout_3->addWidget(label_6);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer_4, 3, 0, 1, 1);

        stackedWidget->addWidget(pageConfirmation);
        pageCreditCard = new QWidget();
        pageCreditCard->setObjectName("pageCreditCard");
        gridLayout = new QGridLayout(pageCreditCard);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        logoLabel_8 = new QLabel(pageCreditCard);
        logoLabel_8->setObjectName("logoLabel_8");
        logoLabel_8->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_4->addWidget(logoLabel_8);

        label_9 = new QLabel(pageCreditCard);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(label_9);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        verticalLayoutPageCard = new QVBoxLayout();
        verticalLayoutPageCard->setObjectName("verticalLayoutPageCard");
        groupBoxCreditCardInput = new QGroupBox(pageCreditCard);
        groupBoxCreditCardInput->setObjectName("groupBoxCreditCardInput");
        formLayout_6 = new QFormLayout(groupBoxCreditCardInput);
        formLayout_6->setObjectName("formLayout_6");
        labelCardNumberStatic = new QLabel(groupBoxCreditCardInput);
        labelCardNumberStatic->setObjectName("labelCardNumberStatic");

        formLayout_6->setWidget(0, QFormLayout::LabelRole, labelCardNumberStatic);

        lineEditCardNumber = new QLineEdit(groupBoxCreditCardInput);
        lineEditCardNumber->setObjectName("lineEditCardNumber");

        formLayout_6->setWidget(0, QFormLayout::FieldRole, lineEditCardNumber);

        labelCardNameStatic = new QLabel(groupBoxCreditCardInput);
        labelCardNameStatic->setObjectName("labelCardNameStatic");

        formLayout_6->setWidget(1, QFormLayout::LabelRole, labelCardNameStatic);

        lineEditCardName = new QLineEdit(groupBoxCreditCardInput);
        lineEditCardName->setObjectName("lineEditCardName");

        formLayout_6->setWidget(1, QFormLayout::FieldRole, lineEditCardName);

        labelExpiryDateStatic = new QLabel(groupBoxCreditCardInput);
        labelExpiryDateStatic->setObjectName("labelExpiryDateStatic");

        formLayout_6->setWidget(2, QFormLayout::LabelRole, labelExpiryDateStatic);

        lineEditExpiryDate = new QLineEdit(groupBoxCreditCardInput);
        lineEditExpiryDate->setObjectName("lineEditExpiryDate");

        formLayout_6->setWidget(2, QFormLayout::FieldRole, lineEditExpiryDate);

        labelCvvStatic = new QLabel(groupBoxCreditCardInput);
        labelCvvStatic->setObjectName("labelCvvStatic");

        formLayout_6->setWidget(3, QFormLayout::LabelRole, labelCvvStatic);

        lineEditCvv = new QLineEdit(groupBoxCreditCardInput);
        lineEditCvv->setObjectName("lineEditCvv");

        formLayout_6->setWidget(3, QFormLayout::FieldRole, lineEditCvv);


        verticalLayoutPageCard->addWidget(groupBoxCreditCardInput);

        horizontalLayoutButtons_3 = new QHBoxLayout();
        horizontalLayoutButtons_3->setObjectName("horizontalLayoutButtons_3");
        pushButtonBackCard = new QPushButton(pageCreditCard);
        pushButtonBackCard->setObjectName("pushButtonBackCard");

        horizontalLayoutButtons_3->addWidget(pushButtonBackCard);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons_3->addItem(horizontalSpacer_3);

        pushButtonSubmitPayment = new QPushButton(pageCreditCard);
        pushButtonSubmitPayment->setObjectName("pushButtonSubmitPayment");

        horizontalLayoutButtons_3->addWidget(pushButtonSubmitPayment);


        verticalLayoutPageCard->addLayout(horizontalLayoutButtons_3);


        gridLayout->addLayout(verticalLayoutPageCard, 2, 0, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        gridLayout->addItem(verticalSpacer_12, 3, 0, 1, 1);

        stackedWidget->addWidget(pageCreditCard);
        pagePayPal = new QWidget();
        pagePayPal->setObjectName("pagePayPal");
        verticalLayout_14 = new QVBoxLayout(pagePayPal);
        verticalLayout_14->setObjectName("verticalLayout_14");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        logoLabel_9 = new QLabel(pagePayPal);
        logoLabel_9->setObjectName("logoLabel_9");
        logoLabel_9->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_7->addWidget(logoLabel_9);

        label_10 = new QLabel(pagePayPal);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_7->addWidget(label_10);


        verticalLayout_14->addLayout(verticalLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_14->addItem(verticalSpacer_5);

        verticalLayoutPagePayPal = new QVBoxLayout();
        verticalLayoutPagePayPal->setObjectName("verticalLayoutPagePayPal");
        labelPayPalInfo = new QLabel(pagePayPal);
        labelPayPalInfo->setObjectName("labelPayPalInfo");

        verticalLayoutPagePayPal->addWidget(labelPayPalInfo);

        verticalSpacerPayPal = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutPagePayPal->addItem(verticalSpacerPayPal);

        horizontalLayoutButtons_4 = new QHBoxLayout();
        horizontalLayoutButtons_4->setObjectName("horizontalLayoutButtons_4");
        pushButtonBackPayPal = new QPushButton(pagePayPal);
        pushButtonBackPayPal->setObjectName("pushButtonBackPayPal");

        horizontalLayoutButtons_4->addWidget(pushButtonBackPayPal);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons_4->addItem(horizontalSpacer_4);

        pushButtonProceedPayPal = new QPushButton(pagePayPal);
        pushButtonProceedPayPal->setObjectName("pushButtonProceedPayPal");

        horizontalLayoutButtons_4->addWidget(pushButtonProceedPayPal);


        verticalLayoutPagePayPal->addLayout(horizontalLayoutButtons_4);


        verticalLayout_14->addLayout(verticalLayoutPagePayPal);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_14->addItem(verticalSpacer_14);

        stackedWidget->addWidget(pagePayPal);
        pageBankTransfer = new QWidget();
        pageBankTransfer->setObjectName("pageBankTransfer");
        verticalLayout_2 = new QVBoxLayout(pageBankTransfer);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        logoLabel_10 = new QLabel(pageBankTransfer);
        logoLabel_10->setObjectName("logoLabel_10");
        logoLabel_10->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_8->addWidget(logoLabel_10);

        label_11 = new QLabel(pageBankTransfer);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_8->addWidget(label_11);


        verticalLayout_2->addLayout(verticalLayout_8);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_2->addItem(verticalSpacer_6);

        verticalLayoutPageBank = new QVBoxLayout();
        verticalLayoutPageBank->setObjectName("verticalLayoutPageBank");
        groupBoxBankDetails = new QGroupBox(pageBankTransfer);
        groupBoxBankDetails->setObjectName("groupBoxBankDetails");
        formLayout_7 = new QFormLayout(groupBoxBankDetails);
        formLayout_7->setObjectName("formLayout_7");
        labelBankInfoIntro = new QLabel(groupBoxBankDetails);
        labelBankInfoIntro->setObjectName("labelBankInfoIntro");
        labelBankInfoIntro->setStyleSheet(QString::fromUtf8(""));

        formLayout_7->setWidget(0, QFormLayout::SpanningRole, labelBankInfoIntro);

        labelBankNameStatic = new QLabel(groupBoxBankDetails);
        labelBankNameStatic->setObjectName("labelBankNameStatic");

        formLayout_7->setWidget(1, QFormLayout::LabelRole, labelBankNameStatic);

        labelBankNameValue = new QLabel(groupBoxBankDetails);
        labelBankNameValue->setObjectName("labelBankNameValue");

        formLayout_7->setWidget(1, QFormLayout::FieldRole, labelBankNameValue);

        labelAccountNumStatic = new QLabel(groupBoxBankDetails);
        labelAccountNumStatic->setObjectName("labelAccountNumStatic");

        formLayout_7->setWidget(2, QFormLayout::LabelRole, labelAccountNumStatic);

        labelAccountNumValue = new QLabel(groupBoxBankDetails);
        labelAccountNumValue->setObjectName("labelAccountNumValue");

        formLayout_7->setWidget(2, QFormLayout::FieldRole, labelAccountNumValue);

        labelSortCodeStatic = new QLabel(groupBoxBankDetails);
        labelSortCodeStatic->setObjectName("labelSortCodeStatic");

        formLayout_7->setWidget(3, QFormLayout::LabelRole, labelSortCodeStatic);

        labelSortCodeValue = new QLabel(groupBoxBankDetails);
        labelSortCodeValue->setObjectName("labelSortCodeValue");

        formLayout_7->setWidget(3, QFormLayout::FieldRole, labelSortCodeValue);

        labelReferenceInfo = new QLabel(groupBoxBankDetails);
        labelReferenceInfo->setObjectName("labelReferenceInfo");

        formLayout_7->setWidget(4, QFormLayout::LabelRole, labelReferenceInfo);

        labelReferenceValue = new QLabel(groupBoxBankDetails);
        labelReferenceValue->setObjectName("labelReferenceValue");

        formLayout_7->setWidget(4, QFormLayout::FieldRole, labelReferenceValue);


        verticalLayoutPageBank->addWidget(groupBoxBankDetails);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayoutPageBank->addItem(verticalSpacer_7);

        horizontalLayoutButtons_5 = new QHBoxLayout();
        horizontalLayoutButtons_5->setObjectName("horizontalLayoutButtons_5");
        pushButtonBackBank = new QPushButton(pageBankTransfer);
        pushButtonBackBank->setObjectName("pushButtonBackBank");

        horizontalLayoutButtons_5->addWidget(pushButtonBackBank);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutButtons_5->addItem(horizontalSpacer_5);

        pushButtonConfirmTransfer = new QPushButton(pageBankTransfer);
        pushButtonConfirmTransfer->setObjectName("pushButtonConfirmTransfer");

        horizontalLayoutButtons_5->addWidget(pushButtonConfirmTransfer);


        verticalLayoutPageBank->addLayout(horizontalLayoutButtons_5);


        verticalLayout_2->addLayout(verticalLayoutPageBank);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_15);

        stackedWidget->addWidget(pageBankTransfer);
        pageProcessing = new QWidget();
        pageProcessing->setObjectName("pageProcessing");
        verticalLayout_16 = new QVBoxLayout(pageProcessing);
        verticalLayout_16->setObjectName("verticalLayout_16");
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        logoLabel_11 = new QLabel(pageProcessing);
        logoLabel_11->setObjectName("logoLabel_11");
        logoLabel_11->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_9->addWidget(logoLabel_11);

        label_12 = new QLabel(pageProcessing);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_9->addWidget(label_12);


        verticalLayout_16->addLayout(verticalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_16->addItem(verticalSpacer_8);

        verticalLayoutPageProcess = new QVBoxLayout();
        verticalLayoutPageProcess->setObjectName("verticalLayoutPageProcess");
        verticalSpacerTopProcessing = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutPageProcess->addItem(verticalSpacerTopProcessing);

        labelProcessingAnimation = new QLabel(pageProcessing);
        labelProcessingAnimation->setObjectName("labelProcessingAnimation");

        verticalLayoutPageProcess->addWidget(labelProcessingAnimation);

        labelProcessingText = new QLabel(pageProcessing);
        labelProcessingText->setObjectName("labelProcessingText");

        verticalLayoutPageProcess->addWidget(labelProcessingText);

        verticalSpacerBotProcessing = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutPageProcess->addItem(verticalSpacerBotProcessing);


        verticalLayout_16->addLayout(verticalLayoutPageProcess);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_2);

        stackedWidget->addWidget(pageProcessing);
        pageStatus = new QWidget();
        pageStatus->setObjectName("pageStatus");
        gridLayout_4 = new QGridLayout(pageStatus);
        gridLayout_4->setObjectName("gridLayout_4");
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        logoLabel_12 = new QLabel(pageStatus);
        logoLabel_12->setObjectName("logoLabel_12");
        logoLabel_12->setPixmap(QPixmap(QString::fromUtf8("C:/Users/LEVNOVO/Desktop/images/Image3.png")));

        verticalLayout_10->addWidget(logoLabel_12);

        label_13 = new QLabel(pageStatus);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_10->addWidget(label_13);


        gridLayout_4->addLayout(verticalLayout_10, 0, 0, 1, 1);

        verticalLayoutPageStatus = new QVBoxLayout();
        verticalLayoutPageStatus->setObjectName("verticalLayoutPageStatus");
        widgetActionButtons = new QWidget(pageStatus);
        widgetActionButtons->setObjectName("widgetActionButtons");
        verticalLayout_6 = new QVBoxLayout(widgetActionButtons);
        verticalLayout_6->setObjectName("verticalLayout_6");
        labelStatusMessage = new QLabel(widgetActionButtons);
        labelStatusMessage->setObjectName("labelStatusMessage");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelStatusMessage->sizePolicy().hasHeightForWidth());
        labelStatusMessage->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(labelStatusMessage);

        groupBoxTransactionSummary = new QGroupBox(widgetActionButtons);
        groupBoxTransactionSummary->setObjectName("groupBoxTransactionSummary");
        formLayout_5 = new QFormLayout(groupBoxTransactionSummary);
        formLayout_5->setObjectName("formLayout_5");
        labelTransIdStatic = new QLabel(groupBoxTransactionSummary);
        labelTransIdStatic->setObjectName("labelTransIdStatic");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, labelTransIdStatic);

        labelTransactionIdValue = new QLabel(groupBoxTransactionSummary);
        labelTransactionIdValue->setObjectName("labelTransactionIdValue");

        formLayout_5->setWidget(0, QFormLayout::FieldRole, labelTransactionIdValue);

        labelTransMethodStatic = new QLabel(groupBoxTransactionSummary);
        labelTransMethodStatic->setObjectName("labelTransMethodStatic");

        formLayout_5->setWidget(1, QFormLayout::LabelRole, labelTransMethodStatic);

        labelPaymentMethodValue = new QLabel(groupBoxTransactionSummary);
        labelPaymentMethodValue->setObjectName("labelPaymentMethodValue");

        formLayout_5->setWidget(1, QFormLayout::FieldRole, labelPaymentMethodValue);

        labelTransAmountStatic = new QLabel(groupBoxTransactionSummary);
        labelTransAmountStatic->setObjectName("labelTransAmountStatic");

        formLayout_5->setWidget(2, QFormLayout::LabelRole, labelTransAmountStatic);

        labelAmountPaidValue = new QLabel(groupBoxTransactionSummary);
        labelAmountPaidValue->setObjectName("labelAmountPaidValue");

        formLayout_5->setWidget(2, QFormLayout::FieldRole, labelAmountPaidValue);

        labelTransTimestampStatic = new QLabel(groupBoxTransactionSummary);
        labelTransTimestampStatic->setObjectName("labelTransTimestampStatic");

        formLayout_5->setWidget(3, QFormLayout::LabelRole, labelTransTimestampStatic);

        labelTransactionTimestampValue = new QLabel(groupBoxTransactionSummary);
        labelTransactionTimestampValue->setObjectName("labelTransactionTimestampValue");

        formLayout_5->setWidget(3, QFormLayout::FieldRole, labelTransactionTimestampValue);


        verticalLayout_6->addWidget(groupBoxTransactionSummary);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_10);

        verticalSpacerStatus = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_6->addItem(verticalSpacerStatus);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        pushButtonGenerateInvoice = new QPushButton(widgetActionButtons);
        pushButtonGenerateInvoice->setObjectName("pushButtonGenerateInvoice");

        horizontalLayout_7->addWidget(pushButtonGenerateInvoice);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        pushButtonCloseStatus = new QPushButton(widgetActionButtons);
        pushButtonCloseStatus->setObjectName("pushButtonCloseStatus");

        horizontalLayout_7->addWidget(pushButtonCloseStatus);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonBookAnother = new QPushButton(widgetActionButtons);
        pushButtonBookAnother->setObjectName("pushButtonBookAnother");

        horizontalLayout_3->addWidget(pushButtonBookAnother);

        pushButtonTryAgain = new QPushButton(widgetActionButtons);
        pushButtonTryAgain->setObjectName("pushButtonTryAgain");

        horizontalLayout_3->addWidget(pushButtonTryAgain);


        verticalLayout_6->addLayout(horizontalLayout_3);


        verticalLayoutPageStatus->addWidget(widgetActionButtons);


        gridLayout_4->addLayout(verticalLayoutPageStatus, 2, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_4->addItem(verticalSpacer_9, 1, 0, 1, 1);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_16, 3, 0, 1, 1);

        stackedWidget->addWidget(pageStatus);

        gridLayout_5->addWidget(stackedWidget, 0, 0, 1, 1);

        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_17, 2, 0, 1, 1);

        verticalSpacer_18 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_18, 1, 0, 1, 1);


        retranslateUi(PaymentWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PaymentWindow);
    } // setupUi

    void retranslateUi(QDialog *PaymentWindow)
    {
        PaymentWindow->setWindowTitle(QCoreApplication::translate("PaymentWindow", "Dialog", nullptr));
#if QT_CONFIG(whatsthis)
        PaymentWindow->setWhatsThis(QCoreApplication::translate("PaymentWindow", "<html><head/><body><p>this-&gt;setStyleSheet(R&quot;(</p><p>QWidget {</p><p>    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:1,</p><p>                                      stop:0 #e0f7ff, stop:1 #b3d9ff);</p><p>    font-family: 'Segoe UI';</p><p>    font-size: 14px;</p><p>    color: #003366;</p><p>}</p><p><br/></p><p>/* GroupBox for visual sections */</p><p>QGroupBox {</p><p>    border: 2px solid #6699cc;</p><p>    border-radius: 10px;</p><p>    margin-top: 10px;</p><p>    background-color: #d6ecff;</p><p>}</p><p>QGroupBox::title {</p><p>    subcontrol-origin: margin;</p><p>    left: 10px;</p><p>    padding: 0 5px;</p><p>    color: #003366;</p><p>    font-weight: bold;</p><p>}</p><p><br/></p><p>/* Buttons */</p><p>QPushButton {</p><p>    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,</p><p>                                      stop:0 #66b3ff, stop:1 #3399ff);</p><p>    color: white;</p><p>    border-radius: 8px;</p><p>    padding: 6px 12px;</p><p>}</p><p>QPushButton:hover {</p><p>    backg"
                        "round-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,</p><p>                                      stop:0 #3399ff, stop:1 #007acc);</p><p>}</p><p>QPushButton:pressed {</p><p>    background-color: #005c99;</p><p>}</p><p><br/></p><p>/* Text fields */</p><p>QLineEdit, QDateEdit, QComboBox, QSpinBox {</p><p>    background-color: #ffffff;</p><p>    border: 1px solid #99ccff;</p><p>    border-radius: 6px;</p><p>    padding: 4px;</p><p>}</p><p><br/></p><p>/* Radio buttons */</p><p>QRadioButton {</p><p>    spacing: 5px;</p><p>}</p><p>QRadioButton::indicator {</p><p>    width: 13px;</p><p>    height: 13px;</p><p>}</p><p>QRadioButton::indicator:checked {</p><p>    background-color: #3399ff;</p><p>    border: 2px solid #005c99;</p><p>}</p><p><br/></p><p>/* QTextEdit (Invoice Summary) */</p><p>QTextEdit {</p><p>    background-color: #f0faff;</p><p>    border: 1px solid #99ccff;</p><p>    border-radius: 6px;</p><p>    padding: 6px;</p><p>}</p><p><br/></p><p>/* ListWidget / Payment History */</p><p>QListWidget {</p><p>    bac"
                        "kground-color: #f2f9ff;</p><p>    border: 1px solid #aaccee;</p><p>    border-radius: 6px;</p><p>    padding: 4px;</p><p>}</p><p>)&quot;);</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        logoLabel_2->setText(QString());
        label_5->setText(QCoreApplication::translate("PaymentWindow", "Appointment ", nullptr));
        groupBoxPersonalInfo->setTitle(QCoreApplication::translate("PaymentWindow", "Personal Informations ", nullptr));
        labelFullNameStatic->setText(QCoreApplication::translate("PaymentWindow", "Full Name:", nullptr));
        lineEditFullName->setText(QString());
        labelEmailStatic->setText(QCoreApplication::translate("PaymentWindow", "Email:", nullptr));
        lineEditEmail->setText(QString());
        labelPhoneStatic->setText(QCoreApplication::translate("PaymentWindow", "Phone:", nullptr));
        lineEditPhone->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        groupBoxAppointmentDetails->setTitle(QCoreApplication::translate("PaymentWindow", "Appointment Details ", nullptr));
        labelConsultTypeStatic->setText(QCoreApplication::translate("PaymentWindow", "Consultation Type:", nullptr));
        comboBoxConsultationType->setItemText(0, QString());
        comboBoxConsultationType->setItemText(1, QCoreApplication::translate("PaymentWindow", "Initial", nullptr));
        comboBoxConsultationType->setItemText(2, QCoreApplication::translate("PaymentWindow", "Follow-up", nullptr));

        comboBoxConsultationType->setCurrentText(QString());
        labelApptDateStatic->setText(QCoreApplication::translate("PaymentWindow", "Appointment Date:", nullptr));
        pushButtonCancelBooking->setText(QCoreApplication::translate("PaymentWindow", "Cancel", nullptr));
        pushButtonContinue->setText(QCoreApplication::translate("PaymentWindow", "Continue", nullptr));
        groupBoxSummary->setTitle(QCoreApplication::translate("PaymentWindow", "Appointment Summary :", nullptr));
        labelSumNameStatic->setText(QCoreApplication::translate("PaymentWindow", "Name:", nullptr));
        labelSummaryName->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        labelSumEmailStatic->setText(QCoreApplication::translate("PaymentWindow", "Email:", nullptr));
        labelSummaryEmail->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        labelSumPhoneStatic->setText(QCoreApplication::translate("PaymentWindow", "Phone:", nullptr));
        labelSummaryPhone->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        labelSumConsultStatic->setText(QCoreApplication::translate("PaymentWindow", "Consultation:", nullptr));
        labelSummaryConsultation->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        labelSumDateStatic->setText(QCoreApplication::translate("PaymentWindow", "Date:", nullptr));
        labelSummaryDate->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        labelSumAmountStatic->setText(QCoreApplication::translate("PaymentWindow", "Amount:", nullptr));
        labelSummaryAmount->setText(QCoreApplication::translate("PaymentWindow", "TextLabel", nullptr));
        groupBoxPaymentMethod->setTitle(QCoreApplication::translate("PaymentWindow", "Payment Method :", nullptr));
        radioButtonPayPal->setText(QCoreApplication::translate("PaymentWindow", "PayPal", nullptr));
        radioButtonCreditCard->setText(QCoreApplication::translate("PaymentWindow", "Credit Card", nullptr));
        radioButtonBankTransfer->setText(QCoreApplication::translate("PaymentWindow", "Bank Transfer", nullptr));
        pushButtonBackConfirm->setText(QCoreApplication::translate("PaymentWindow", "Back", nullptr));
        pushButtonProceedToPay->setText(QCoreApplication::translate("PaymentWindow", "Proceed to Pay", nullptr));
        logoLabel->setText(QString());
        label_6->setText(QCoreApplication::translate("PaymentWindow", "Confirmation & Payment Method", nullptr));
        logoLabel_8->setText(QString());
        label_9->setText(QCoreApplication::translate("PaymentWindow", "Enter Credit Card Details", nullptr));
        groupBoxCreditCardInput->setTitle(QCoreApplication::translate("PaymentWindow", "Card Details", nullptr));
        labelCardNumberStatic->setText(QCoreApplication::translate("PaymentWindow", "Card Number:", nullptr));
        labelCardNameStatic->setText(QCoreApplication::translate("PaymentWindow", "Name on Card:", nullptr));
        labelExpiryDateStatic->setText(QCoreApplication::translate("PaymentWindow", "Expiry Date (MM/YY):", nullptr));
        labelCvvStatic->setText(QCoreApplication::translate("PaymentWindow", "CVV/CVC:", nullptr));
        pushButtonBackCard->setText(QCoreApplication::translate("PaymentWindow", "Back", nullptr));
        pushButtonSubmitPayment->setText(QCoreApplication::translate("PaymentWindow", "Submit Payment", nullptr));
        logoLabel_9->setText(QString());
        label_10->setText(QCoreApplication::translate("PaymentWindow", "PayPal Payment", nullptr));
        labelPayPalInfo->setText(QCoreApplication::translate("PaymentWindow", "PayPal Info", nullptr));
        pushButtonBackPayPal->setText(QCoreApplication::translate("PaymentWindow", "Back", nullptr));
        pushButtonProceedPayPal->setText(QCoreApplication::translate("PaymentWindow", "Proceed to PayPal", nullptr));
        logoLabel_10->setText(QString());
        label_11->setText(QCoreApplication::translate("PaymentWindow", "Bank Transfer Details", nullptr));
        groupBoxBankDetails->setTitle(QCoreApplication::translate("PaymentWindow", "BankDetails", nullptr));
        labelBankInfoIntro->setText(QCoreApplication::translate("PaymentWindow", "Please use the following details...", nullptr));
        labelBankNameStatic->setText(QCoreApplication::translate("PaymentWindow", "Bank Name:", nullptr));
        labelBankNameValue->setText(QCoreApplication::translate("PaymentWindow", "Your Bank Name", nullptr));
        labelAccountNumStatic->setText(QCoreApplication::translate("PaymentWindow", "Account Number:", nullptr));
        labelAccountNumValue->setText(QCoreApplication::translate("PaymentWindow", "Your Account Number", nullptr));
        labelSortCodeStatic->setText(QCoreApplication::translate("PaymentWindow", "Sort Code/IBAN:", nullptr));
        labelSortCodeValue->setText(QCoreApplication::translate("PaymentWindow", "Your Sort Code/IBAN", nullptr));
        labelReferenceInfo->setText(QCoreApplication::translate("PaymentWindow", "Important: Use your Booking ID as reference:", nullptr));
        labelReferenceValue->setText(QCoreApplication::translate("PaymentWindow", "Populated Booking ID", nullptr));
        pushButtonBackBank->setText(QCoreApplication::translate("PaymentWindow", "Back", nullptr));
        pushButtonConfirmTransfer->setText(QCoreApplication::translate("PaymentWindow", "Payment Sent / Confirm Later", nullptr));
        logoLabel_11->setText(QString());
        label_12->setText(QCoreApplication::translate("PaymentWindow", "Processing Payment", nullptr));
        labelProcessingAnimation->setText(QCoreApplication::translate("PaymentWindow", "Display loading GIF ", nullptr));
        labelProcessingText->setText(QCoreApplication::translate("PaymentWindow", "Processing Payment...", nullptr));
        logoLabel_12->setText(QString());
        label_13->setText(QCoreApplication::translate("PaymentWindow", "Payment Status", nullptr));
        labelStatusMessage->setText(QCoreApplication::translate("PaymentWindow", "Payment Successful! / Failed!", nullptr));
        groupBoxTransactionSummary->setTitle(QCoreApplication::translate("PaymentWindow", "Transaction Summary", nullptr));
        labelTransIdStatic->setText(QCoreApplication::translate("PaymentWindow", "Transaction ID:", nullptr));
        labelTransactionIdValue->setText(QCoreApplication::translate("PaymentWindow", "Populated ID", nullptr));
        labelTransMethodStatic->setText(QCoreApplication::translate("PaymentWindow", "Payment Method:", nullptr));
        labelPaymentMethodValue->setText(QCoreApplication::translate("PaymentWindow", "Populated Method", nullptr));
        labelTransAmountStatic->setText(QCoreApplication::translate("PaymentWindow", "Amount Paid:", nullptr));
        labelAmountPaidValue->setText(QCoreApplication::translate("PaymentWindow", "Populated Amount", nullptr));
        labelTransTimestampStatic->setText(QCoreApplication::translate("PaymentWindow", "Transaction Date/Time:", nullptr));
        labelTransactionTimestampValue->setText(QCoreApplication::translate("PaymentWindow", "Populated Timestamp", nullptr));
        pushButtonGenerateInvoice->setText(QCoreApplication::translate("PaymentWindow", "Generate Invoice", nullptr));
        pushButtonCloseStatus->setText(QCoreApplication::translate("PaymentWindow", "Close", nullptr));
        pushButtonBookAnother->setText(QCoreApplication::translate("PaymentWindow", "Book Another Appointment", nullptr));
        pushButtonTryAgain->setText(QCoreApplication::translate("PaymentWindow", "Try Again", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PaymentWindow: public Ui_PaymentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYMENTWINDOW_H
