/********************************************************************************
** Form generated from reading UI file 'calendrierdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDRIERDIALOG_H
#define UI_CALENDRIERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CalendrierDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendarWidget;
    QFrame *frame_details;
    QVBoxLayout *verticalLayout;
    QLabel *label_SelectedDate;
    QLabel *label_Appointments;
    QListWidget *listWidget_Appointments;
    QFrame *line;
    QLabel *label_Details;
    QFormLayout *formLayout;
    QLabel *label_IdCal;
    QLineEdit *lineEdit_IdCal;
    QLabel *label_HeureCal;
    QTimeEdit *timeEdit_HeureCal;
    QLabel *label_ObjetCal;
    QLineEdit *lineEdit_ObjetCal;
    QLabel *label_StatutCal;
    QComboBox *comboBox_StatutCal;
    QLabel *label_TypeCal;
    QComboBox *comboBox_TypeCal;
    QHBoxLayout *horizontalLayout_buttons;
    QPushButton *pushButton_AjouterCal;
    QPushButton *pushButton_ModifierCal;
    QPushButton *pushButton_SupprimerCal;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CalendrierDialog)
    {
        if (CalendrierDialog->objectName().isEmpty())
            CalendrierDialog->setObjectName("CalendrierDialog");
        CalendrierDialog->resize(750, 550);
        CalendrierDialog->setStyleSheet(QString::fromUtf8("/* Basic Styling - Enhance as needed */\n"
"QDialog {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #e0eafc, stop:1 #cfdef3); /* Light blue gradient */\n"
"}\n"
"\n"
"QLabel {\n"
"    font-family: 'Segoe UI', sans-serif;\n"
"    font-size: 10pt;\n"
"    color: #333;\n"
"}\n"
"\n"
"QLineEdit, QTimeEdit, QComboBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #9B59B6; /* Purple */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    padding: 8px 15px;\n"
"    font-size: 10pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #8E44AD; /* Darker Purple */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #70308f;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar {\n"
"    background-color: #9B59B6; /* Purple */\n"
"}\n"
"QCalendarWidg"
                        "et QToolButton {\n"
"    color: white;\n"
"    font-size: 12pt;\n"
"    icon-size: 18px, 18px;\n"
"    background-color: transparent;\n"
"}\n"
"QCalendarWidget QMenu {\n"
"    background-color: white;\n"
"    color: #333;\n"
"}\n"
"QCalendarWidget QSpinBox {\n"
"     color: white;\n"
"     background-color: transparent;\n"
"     selection-background-color: #8E44AD;\n"
"     selection-color: white;\n"
"}\n"
"QCalendarWidget QTableView {\n"
"    selection-background-color: #8E44AD; /* Darker Purple for selection */\n"
"    selection-color: white;\n"
"}\n"
"/* Highlighted dates (set in code) */\n"
"QCalendarWidget QTableView::item:selected {\n"
"     background-color: #8E44AD;\n"
"     color: white;\n"
"}\n"
"\n"
"QListWidget {\n"
"    background-color: #f8f8f8;\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 4px;\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(CalendrierDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        calendarWidget = new QCalendarWidget(CalendrierDialog);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setMinimumSize(QSize(350, 0));
        calendarWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(calendarWidget);

        frame_details = new QFrame(CalendrierDialog);
        frame_details->setObjectName("frame_details");
        frame_details->setFrameShape(QFrame::Shape::StyledPanel);
        frame_details->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame_details);
        verticalLayout->setObjectName("verticalLayout");
        label_SelectedDate = new QLabel(frame_details);
        label_SelectedDate->setObjectName("label_SelectedDate");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(10);
        font.setBold(true);
        label_SelectedDate->setFont(font);
        label_SelectedDate->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_SelectedDate);

        label_Appointments = new QLabel(frame_details);
        label_Appointments->setObjectName("label_Appointments");

        verticalLayout->addWidget(label_Appointments);

        listWidget_Appointments = new QListWidget(frame_details);
        listWidget_Appointments->setObjectName("listWidget_Appointments");
        listWidget_Appointments->setMaximumSize(QSize(16777215, 150));

        verticalLayout->addWidget(listWidget_Appointments);

        line = new QFrame(frame_details);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        label_Details = new QLabel(frame_details);
        label_Details->setObjectName("label_Details");

        verticalLayout->addWidget(label_Details);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_IdCal = new QLabel(frame_details);
        label_IdCal->setObjectName("label_IdCal");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_IdCal);

        lineEdit_IdCal = new QLineEdit(frame_details);
        lineEdit_IdCal->setObjectName("lineEdit_IdCal");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_IdCal);

        label_HeureCal = new QLabel(frame_details);
        label_HeureCal->setObjectName("label_HeureCal");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_HeureCal);

        timeEdit_HeureCal = new QTimeEdit(frame_details);
        timeEdit_HeureCal->setObjectName("timeEdit_HeureCal");

        formLayout->setWidget(1, QFormLayout::FieldRole, timeEdit_HeureCal);

        label_ObjetCal = new QLabel(frame_details);
        label_ObjetCal->setObjectName("label_ObjetCal");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_ObjetCal);

        lineEdit_ObjetCal = new QLineEdit(frame_details);
        lineEdit_ObjetCal->setObjectName("lineEdit_ObjetCal");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_ObjetCal);

        label_StatutCal = new QLabel(frame_details);
        label_StatutCal->setObjectName("label_StatutCal");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_StatutCal);

        comboBox_StatutCal = new QComboBox(frame_details);
        comboBox_StatutCal->addItem(QString());
        comboBox_StatutCal->addItem(QString());
        comboBox_StatutCal->addItem(QString());
        comboBox_StatutCal->addItem(QString());
        comboBox_StatutCal->setObjectName("comboBox_StatutCal");

        formLayout->setWidget(3, QFormLayout::FieldRole, comboBox_StatutCal);

        label_TypeCal = new QLabel(frame_details);
        label_TypeCal->setObjectName("label_TypeCal");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_TypeCal);

        comboBox_TypeCal = new QComboBox(frame_details);
        comboBox_TypeCal->addItem(QString());
        comboBox_TypeCal->addItem(QString());
        comboBox_TypeCal->setObjectName("comboBox_TypeCal");

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBox_TypeCal);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setObjectName("horizontalLayout_buttons");
        pushButton_AjouterCal = new QPushButton(frame_details);
        pushButton_AjouterCal->setObjectName("pushButton_AjouterCal");

        horizontalLayout_buttons->addWidget(pushButton_AjouterCal);

        pushButton_ModifierCal = new QPushButton(frame_details);
        pushButton_ModifierCal->setObjectName("pushButton_ModifierCal");

        horizontalLayout_buttons->addWidget(pushButton_ModifierCal);

        pushButton_SupprimerCal = new QPushButton(frame_details);
        pushButton_SupprimerCal->setObjectName("pushButton_SupprimerCal");

        horizontalLayout_buttons->addWidget(pushButton_SupprimerCal);


        verticalLayout->addLayout(horizontalLayout_buttons);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame_details);


        retranslateUi(CalendrierDialog);

        QMetaObject::connectSlotsByName(CalendrierDialog);
    } // setupUi

    void retranslateUi(QDialog *CalendrierDialog)
    {
        CalendrierDialog->setWindowTitle(QCoreApplication::translate("CalendrierDialog", "Calendrier", nullptr));
        label_SelectedDate->setText(QCoreApplication::translate("CalendrierDialog", "Selected Date", nullptr));
        label_Appointments->setText(QCoreApplication::translate("CalendrierDialog", "Events for this day:", nullptr));
        label_Details->setText(QCoreApplication::translate("CalendrierDialog", "Details / New EVENT:\n"
"\n"
"", nullptr));
        label_IdCal->setText(QCoreApplication::translate("CalendrierDialog", "EVENT ID:", nullptr));
        label_HeureCal->setText(QCoreApplication::translate("CalendrierDialog", "Time:", nullptr));
        timeEdit_HeureCal->setDisplayFormat(QCoreApplication::translate("CalendrierDialog", "HH:mm", nullptr));
        label_ObjetCal->setText(QCoreApplication::translate("CalendrierDialog", "Subject:", nullptr));
        label_StatutCal->setText(QCoreApplication::translate("CalendrierDialog", "Status:", nullptr));
        comboBox_StatutCal->setItemText(0, QCoreApplication::translate("CalendrierDialog", "Pending", nullptr));
        comboBox_StatutCal->setItemText(1, QCoreApplication::translate("CalendrierDialog", "Confirmed", nullptr));
        comboBox_StatutCal->setItemText(2, QCoreApplication::translate("CalendrierDialog", "Cancelled", nullptr));
        comboBox_StatutCal->setItemText(3, QCoreApplication::translate("CalendrierDialog", "Done", nullptr));

        label_TypeCal->setText(QCoreApplication::translate("CalendrierDialog", "Type :", nullptr));
        comboBox_TypeCal->setItemText(0, QCoreApplication::translate("CalendrierDialog", "onsite", nullptr));
        comboBox_TypeCal->setItemText(1, QCoreApplication::translate("CalendrierDialog", "online", nullptr));

        pushButton_AjouterCal->setText(QCoreApplication::translate("CalendrierDialog", "Ajouter", nullptr));
        pushButton_ModifierCal->setText(QCoreApplication::translate("CalendrierDialog", "Modifier", nullptr));
        pushButton_SupprimerCal->setText(QCoreApplication::translate("CalendrierDialog", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalendrierDialog: public Ui_CalendrierDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDRIERDIALOG_H
