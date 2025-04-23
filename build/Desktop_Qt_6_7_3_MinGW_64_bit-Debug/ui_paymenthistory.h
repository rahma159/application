/********************************************************************************
** Form generated from reading UI file 'paymenthistory.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAYMENTHISTORY_H
#define UI_PAYMENTHISTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>

QT_BEGIN_NAMESPACE

class Ui_paymentHistory
{
public:
    QGroupBox *groupBox_2;
    QSplitter *splitter;
    QListWidget *paymentHistoryList_2;
    QPushButton *exportHistoryButton1;

    void setupUi(QDialog *paymentHistory)
    {
        if (paymentHistory->objectName().isEmpty())
            paymentHistory->setObjectName("paymentHistory");
        paymentHistory->resize(1947, 763);
        paymentHistory->setStyleSheet(QString::fromUtf8("background-image: url(:/images/background_image.png);"));
        groupBox_2 = new QGroupBox(paymentHistory);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(160, 110, 391, 131));
        groupBox_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        splitter = new QSplitter(groupBox_2);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(20, 40, 341, 61));
        splitter->setOrientation(Qt::Orientation::Vertical);
        paymentHistoryList_2 = new QListWidget(splitter);
        paymentHistoryList_2->setObjectName("paymentHistoryList_2");
        splitter->addWidget(paymentHistoryList_2);
        exportHistoryButton1 = new QPushButton(splitter);
        exportHistoryButton1->setObjectName("exportHistoryButton1");
        splitter->addWidget(exportHistoryButton1);

        retranslateUi(paymentHistory);

        QMetaObject::connectSlotsByName(paymentHistory);
    } // setupUi

    void retranslateUi(QDialog *paymentHistory)
    {
        paymentHistory->setWindowTitle(QCoreApplication::translate("paymentHistory", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("paymentHistory", "Payment History", nullptr));
        exportHistoryButton1->setText(QCoreApplication::translate("paymentHistory", "Export History", nullptr));
    } // retranslateUi

};

namespace Ui {
    class paymentHistory: public Ui_paymentHistory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAYMENTHISTORY_H
