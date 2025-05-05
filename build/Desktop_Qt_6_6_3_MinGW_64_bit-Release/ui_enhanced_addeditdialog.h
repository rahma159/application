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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_EnhancedAddEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QLabel *labelRole;
    QComboBox *comboBoxRole;
    QLabel *labelExpertise;
    QLineEdit *lineEditExpertise;
    QLabel *labelRate;
    QDoubleSpinBox *doubleSpinBoxRate;
    QLabel *labelAvailability;
    QComboBox *comboBoxAvailability;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonUploadDoc;
    QLabel *labelDocPath;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EnhancedAddEditDialog)
    {
        if (EnhancedAddEditDialog->objectName().isEmpty())
            EnhancedAddEditDialog->setObjectName("EnhancedAddEditDialog");
        EnhancedAddEditDialog->resize(159, 249);
        verticalLayout = new QVBoxLayout(EnhancedAddEditDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelName = new QLabel(EnhancedAddEditDialog);
        labelName->setObjectName("labelName");

        verticalLayout->addWidget(labelName);

        lineEditName = new QLineEdit(EnhancedAddEditDialog);
        lineEditName->setObjectName("lineEditName");

        verticalLayout->addWidget(lineEditName);

        labelRole = new QLabel(EnhancedAddEditDialog);
        labelRole->setObjectName("labelRole");

        verticalLayout->addWidget(labelRole);

        comboBoxRole = new QComboBox(EnhancedAddEditDialog);
        comboBoxRole->addItem(QString());
        comboBoxRole->addItem(QString());
        comboBoxRole->setObjectName("comboBoxRole");

        verticalLayout->addWidget(comboBoxRole);

        labelExpertise = new QLabel(EnhancedAddEditDialog);
        labelExpertise->setObjectName("labelExpertise");

        verticalLayout->addWidget(labelExpertise);

        lineEditExpertise = new QLineEdit(EnhancedAddEditDialog);
        lineEditExpertise->setObjectName("lineEditExpertise");

        verticalLayout->addWidget(lineEditExpertise);

        labelRate = new QLabel(EnhancedAddEditDialog);
        labelRate->setObjectName("labelRate");

        verticalLayout->addWidget(labelRate);

        doubleSpinBoxRate = new QDoubleSpinBox(EnhancedAddEditDialog);
        doubleSpinBoxRate->setObjectName("doubleSpinBoxRate");
        doubleSpinBoxRate->setEnabled(true);
        doubleSpinBoxRate->setFrame(true);
        doubleSpinBoxRate->setDecimals(2);
        doubleSpinBoxRate->setMaximum(1000.000000000000000);
        doubleSpinBoxRate->setValue(75.000000000000000);

        verticalLayout->addWidget(doubleSpinBoxRate);

        labelAvailability = new QLabel(EnhancedAddEditDialog);
        labelAvailability->setObjectName("labelAvailability");

        verticalLayout->addWidget(labelAvailability);

        comboBoxAvailability = new QComboBox(EnhancedAddEditDialog);
        comboBoxAvailability->addItem(QString());
        comboBoxAvailability->addItem(QString());
        comboBoxAvailability->setObjectName("comboBoxAvailability");

        verticalLayout->addWidget(comboBoxAvailability);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButtonUploadDoc = new QPushButton(EnhancedAddEditDialog);
        pushButtonUploadDoc->setObjectName("pushButtonUploadDoc");

        horizontalLayout->addWidget(pushButtonUploadDoc);

        labelDocPath = new QLabel(EnhancedAddEditDialog);
        labelDocPath->setObjectName("labelDocPath");

        horizontalLayout->addWidget(labelDocPath);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(EnhancedAddEditDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setAcceptDrops(false);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(EnhancedAddEditDialog);

        QMetaObject::connectSlotsByName(EnhancedAddEditDialog);
    } // setupUi

    void retranslateUi(QDialog *EnhancedAddEditDialog)
    {
        labelName->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Full Name", nullptr));
        lineEditName->setText(QCoreApplication::translate("EnhancedAddEditDialog", "john doe", nullptr));
        labelRole->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Role", nullptr));
        comboBoxRole->setItemText(0, QCoreApplication::translate("EnhancedAddEditDialog", "Consultant", nullptr));
        comboBoxRole->setItemText(1, QCoreApplication::translate("EnhancedAddEditDialog", "Employee", nullptr));

        labelExpertise->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Expertise", nullptr));
        lineEditExpertise->setText(QCoreApplication::translate("EnhancedAddEditDialog", "doctor", nullptr));
        labelRate->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Hourly Rate", nullptr));
        labelAvailability->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Availability", nullptr));
        comboBoxAvailability->setItemText(0, QCoreApplication::translate("EnhancedAddEditDialog", "Available", nullptr));
        comboBoxAvailability->setItemText(1, QCoreApplication::translate("EnhancedAddEditDialog", "Unavailable", nullptr));

        pushButtonUploadDoc->setText(QCoreApplication::translate("EnhancedAddEditDialog", "Upload Document", nullptr));
        labelDocPath->setText(QCoreApplication::translate("EnhancedAddEditDialog", "No file selected", nullptr));
        (void)EnhancedAddEditDialog;
    } // retranslateUi

};

namespace Ui {
    class EnhancedAddEditDialog: public Ui_EnhancedAddEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENHANCED_ADDEDITDIALOG_H
