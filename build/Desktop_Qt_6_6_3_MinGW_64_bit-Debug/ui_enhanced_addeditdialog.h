/********************************************************************************
** Form generated from reading UI file 'enhanced_addeditdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENHANCED_ADDEDITDIALOG_H
#define UI_ENHANCED_ADDEDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EnhancedAddEditDialog
{
public:
    QVBoxLayout *mainLayout;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelEmail;
    QLineEdit *lineEditEmail;
    QLabel *labelPhone;
    QLineEdit *lineEditPhone;
    QLabel *labelPhoto;
    QHBoxLayout *hboxLayout;
    QPushButton *pushButtonUploadPhoto;
    QLabel *labelPhotoPath;
    QLabel *labelRole;
    QComboBox *comboBoxRole;
    QLabel *labelExpertise;
    QLineEdit *lineEditExpertise;
    QLabel *labelRate;
    QDoubleSpinBox *doubleSpinBoxRate;
    QLabel *labelAvailability;
    QComboBox *comboBoxAvailability;
    QLabel *labelCalendar;
    QCalendarWidget *calendarWorkingDays;
    QLabel *labelLeaveInfo;
    QLineEdit *lineEditLeaveNotes;
    QLabel *labelDocument;
    QHBoxLayout *hboxLayout1;
    QPushButton *pushButtonUploadDoc;
    QLabel *labelDocPath;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EnhancedAddEditDialog)
    {
        if (EnhancedAddEditDialog->objectName().isEmpty())
            EnhancedAddEditDialog->setObjectName("EnhancedAddEditDialog");
        mainLayout = new QVBoxLayout(EnhancedAddEditDialog);
        mainLayout->setObjectName("mainLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelName = new QLabel(EnhancedAddEditDialog);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelName);

        lineEditName = new QLineEdit(EnhancedAddEditDialog);
        lineEditName->setObjectName("lineEditName");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditName);

        labelEmail = new QLabel(EnhancedAddEditDialog);
        labelEmail->setObjectName("labelEmail");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelEmail);

        lineEditEmail = new QLineEdit(EnhancedAddEditDialog);
        lineEditEmail->setObjectName("lineEditEmail");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditEmail);

        labelPhone = new QLabel(EnhancedAddEditDialog);
        labelPhone->setObjectName("labelPhone");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelPhone);

        lineEditPhone = new QLineEdit(EnhancedAddEditDialog);
        lineEditPhone->setObjectName("lineEditPhone");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPhone);

        labelPhoto = new QLabel(EnhancedAddEditDialog);
        labelPhoto->setObjectName("labelPhoto");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelPhoto);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        pushButtonUploadPhoto = new QPushButton(EnhancedAddEditDialog);
        pushButtonUploadPhoto->setObjectName("pushButtonUploadPhoto");

        hboxLayout->addWidget(pushButtonUploadPhoto);

        labelPhotoPath = new QLabel(EnhancedAddEditDialog);
        labelPhotoPath->setObjectName("labelPhotoPath");

        hboxLayout->addWidget(labelPhotoPath);


        formLayout->setLayout(3, QFormLayout::FieldRole, hboxLayout);

        labelRole = new QLabel(EnhancedAddEditDialog);
        labelRole->setObjectName("labelRole");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelRole);

        comboBoxRole = new QComboBox(EnhancedAddEditDialog);
        comboBoxRole->addItem(QString());
        comboBoxRole->addItem(QString());
        comboBoxRole->setObjectName("comboBoxRole");

        formLayout->setWidget(4, QFormLayout::FieldRole, comboBoxRole);

        labelExpertise = new QLabel(EnhancedAddEditDialog);
        labelExpertise->setObjectName("labelExpertise");

        formLayout->setWidget(5, QFormLayout::LabelRole, labelExpertise);

        lineEditExpertise = new QLineEdit(EnhancedAddEditDialog);
        lineEditExpertise->setObjectName("lineEditExpertise");

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditExpertise);

        labelRate = new QLabel(EnhancedAddEditDialog);
        labelRate->setObjectName("labelRate");

        formLayout->setWidget(6, QFormLayout::LabelRole, labelRate);

        doubleSpinBoxRate = new QDoubleSpinBox(EnhancedAddEditDialog);
        doubleSpinBoxRate->setObjectName("doubleSpinBoxRate");
        doubleSpinBoxRate->setMinimum(10.000000000000000);
        doubleSpinBoxRate->setMaximum(1000.000000000000000);
        doubleSpinBoxRate->setValue(75.000000000000000);
        doubleSpinBoxRate->setDecimals(2);

        formLayout->setWidget(6, QFormLayout::FieldRole, doubleSpinBoxRate);

        labelAvailability = new QLabel(EnhancedAddEditDialog);
        labelAvailability->setObjectName("labelAvailability");

        formLayout->setWidget(7, QFormLayout::LabelRole, labelAvailability);

        comboBoxAvailability = new QComboBox(EnhancedAddEditDialog);
        comboBoxAvailability->addItem(QString());
        comboBoxAvailability->addItem(QString());
        comboBoxAvailability->setObjectName("comboBoxAvailability");

        formLayout->setWidget(7, QFormLayout::FieldRole, comboBoxAvailability);

        labelCalendar = new QLabel(EnhancedAddEditDialog);
        labelCalendar->setObjectName("labelCalendar");

        formLayout->setWidget(8, QFormLayout::LabelRole, labelCalendar);

        calendarWorkingDays = new QCalendarWidget(EnhancedAddEditDialog);
        calendarWorkingDays->setObjectName("calendarWorkingDays");

        formLayout->setWidget(8, QFormLayout::FieldRole, calendarWorkingDays);

        labelLeaveInfo = new QLabel(EnhancedAddEditDialog);
        labelLeaveInfo->setObjectName("labelLeaveInfo");

        formLayout->setWidget(9, QFormLayout::LabelRole, labelLeaveInfo);

        lineEditLeaveNotes = new QLineEdit(EnhancedAddEditDialog);
        lineEditLeaveNotes->setObjectName("lineEditLeaveNotes");

        formLayout->setWidget(9, QFormLayout::FieldRole, lineEditLeaveNotes);

        labelDocument = new QLabel(EnhancedAddEditDialog);
        labelDocument->setObjectName("labelDocument");

        formLayout->setWidget(10, QFormLayout::LabelRole, labelDocument);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        pushButtonUploadDoc = new QPushButton(EnhancedAddEditDialog);
        pushButtonUploadDoc->setObjectName("pushButtonUploadDoc");

        hboxLayout1->addWidget(pushButtonUploadDoc);

        labelDocPath = new QLabel(EnhancedAddEditDialog);
        labelDocPath->setObjectName("labelDocPath");

        hboxLayout1->addWidget(labelDocPath);


        formLayout->setLayout(10, QFormLayout::FieldRole, hboxLayout1);


        mainLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(EnhancedAddEditDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        mainLayout->addWidget(buttonBox);


        retranslateUi(EnhancedAddEditDialog);

        QMetaObject::connectSlotsByName(EnhancedAddEditDialog);
    } // setupUi

    void retranslateUi(QDialog *EnhancedAddEditDialog)
    {
        EnhancedAddEditDialog->setWindowTitle(QCoreApplication::translate("EnhancedAddEditDialog", "Add / Edit Consultant", nullptr));
        labelName->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Full Name", nullptr));
        lineEditName->setPlaceholderText(QCoreApplication::translate("EnhancedAddEditDialog", "Enter full name", nullptr));
        labelEmail->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Email", nullptr));
        lineEditEmail->setPlaceholderText(QCoreApplication::translate("EnhancedAddEditDialog", "e.g. name@example.com", nullptr));
        labelPhone->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Phone", nullptr));
        lineEditPhone->setPlaceholderText(QCoreApplication::translate("EnhancedAddEditDialog", "e.g. +971 50 123 4567", nullptr));
        labelPhoto->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Photo", nullptr));
        pushButtonUploadPhoto->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Upload Photo", nullptr));
        labelPhotoPath->setText(QCoreApplication::translate("EnhancedAddEditDialog", "No photo selected", nullptr));
        labelRole->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Role", nullptr));
        comboBoxRole->setItemText(0, QCoreApplication::translate("EnhancedAddEditDialog", "Consultant", nullptr));
        comboBoxRole->setItemText(1, QCoreApplication::translate("EnhancedAddEditDialog", "Employee", nullptr));

        labelExpertise->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Expertise", nullptr));
        lineEditExpertise->setPlaceholderText(QCoreApplication::translate("EnhancedAddEditDialog", "Enter area of expertise", nullptr));
        labelRate->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Hourly Rate ($)", nullptr));
        labelAvailability->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Availability", nullptr));
        comboBoxAvailability->setItemText(0, QCoreApplication::translate("EnhancedAddEditDialog", "Available", nullptr));
        comboBoxAvailability->setItemText(1, QCoreApplication::translate("EnhancedAddEditDialog", "Unavailable", nullptr));

        labelCalendar->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Working Days", nullptr));
        labelLeaveInfo->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Leave Notes", nullptr));
        lineEditLeaveNotes->setPlaceholderText(QCoreApplication::translate("EnhancedAddEditDialog", "e.g. Vacation from 12\342\200\22318 July", nullptr));
        labelDocument->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Document", nullptr));
        pushButtonUploadDoc->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Upload Document", nullptr));
        labelDocPath->setText(QCoreApplication::translate("EnhancedAddEditDialog", "No file selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnhancedAddEditDialog: public Ui_EnhancedAddEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENHANCED_ADDEDITDIALOG_H
