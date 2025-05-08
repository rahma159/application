/********************************************************************************
** Form generated from reading UI file 'deleteinvoicedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETEINVOICEDIALOG_H
#define UI_DELETEINVOICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DeleteInvoiceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *invoiceIdLineEdit;
    QLabel *label_3;
    QLineEdit *invoiceNumberLineEdit;
    QPushButton *cancelButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *deleteButton;

    void setupUi(QDialog *DeleteInvoiceDialog)
    {
        if (DeleteInvoiceDialog->objectName().isEmpty())
            DeleteInvoiceDialog->setObjectName("DeleteInvoiceDialog");
        DeleteInvoiceDialog->resize(348, 149);
        verticalLayout = new QVBoxLayout(DeleteInvoiceDialog);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(DeleteInvoiceDialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        verticalLayout->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(DeleteInvoiceDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        invoiceIdLineEdit = new QLineEdit(DeleteInvoiceDialog);
        invoiceIdLineEdit->setObjectName("invoiceIdLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, invoiceIdLineEdit);

        label_3 = new QLabel(DeleteInvoiceDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        invoiceNumberLineEdit = new QLineEdit(DeleteInvoiceDialog);
        invoiceNumberLineEdit->setObjectName("invoiceNumberLineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, invoiceNumberLineEdit);

        cancelButton = new QPushButton(DeleteInvoiceDialog);
        cancelButton->setObjectName("cancelButton");

        formLayout->setWidget(2, QFormLayout::LabelRole, cancelButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        deleteButton = new QPushButton(DeleteInvoiceDialog);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout->addWidget(deleteButton);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout->addLayout(formLayout);


        retranslateUi(DeleteInvoiceDialog);

        QMetaObject::connectSlotsByName(DeleteInvoiceDialog);
    } // setupUi

    void retranslateUi(QDialog *DeleteInvoiceDialog)
    {
        DeleteInvoiceDialog->setWindowTitle(QCoreApplication::translate("DeleteInvoiceDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DeleteInvoiceDialog", "Are you sure you want to delete this invoice?", nullptr));
        label_2->setText(QCoreApplication::translate("DeleteInvoiceDialog", "Invoice ID:", nullptr));
        label_3->setText(QCoreApplication::translate("DeleteInvoiceDialog", "Invoice Number:", nullptr));
        cancelButton->setText(QCoreApplication::translate("DeleteInvoiceDialog", "\342\235\214Cancel", nullptr));
        deleteButton->setText(QCoreApplication::translate("DeleteInvoiceDialog", " \360\237\227\221\357\270\217Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteInvoiceDialog: public Ui_DeleteInvoiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETEINVOICEDIALOG_H
