/********************************************************************************
** Form generated from reading UI file 'enhanced_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENHANCED_MAINWINDOW_H
#define UI_ENHANCED_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnhancedMainWindow
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEditSearch;
    QLabel *labelTotalEntries;
    QTableView *tableView;
    QHBoxLayout *buttonLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonExportCSV;

    void setupUi(QWidget *EnhancedMainWindow)
    {
        if (EnhancedMainWindow->objectName().isEmpty())
            EnhancedMainWindow->setObjectName("EnhancedMainWindow");
        EnhancedMainWindow->resize(800, 500);
        gridLayout = new QGridLayout(EnhancedMainWindow);
        gridLayout->setObjectName("gridLayout");
        lineEditSearch = new QLineEdit(EnhancedMainWindow);
        lineEditSearch->setObjectName("lineEditSearch");

        gridLayout->addWidget(lineEditSearch, 0, 0, 1, 1);

        labelTotalEntries = new QLabel(EnhancedMainWindow);
        labelTotalEntries->setObjectName("labelTotalEntries");
        labelTotalEntries->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"color: rgb(38, 78, 255);"));

        gridLayout->addWidget(labelTotalEntries, 1, 0, 1, 1);

        tableView = new QTableView(EnhancedMainWindow);
        tableView->setObjectName("tableView");
        tableView->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));

        gridLayout->addWidget(tableView, 2, 0, 1, 1);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        pushButtonAdd = new QPushButton(EnhancedMainWindow);
        pushButtonAdd->setObjectName("pushButtonAdd");

        buttonLayout->addWidget(pushButtonAdd);

        pushButtonEdit = new QPushButton(EnhancedMainWindow);
        pushButtonEdit->setObjectName("pushButtonEdit");

        buttonLayout->addWidget(pushButtonEdit);

        pushButtonDelete = new QPushButton(EnhancedMainWindow);
        pushButtonDelete->setObjectName("pushButtonDelete");

        buttonLayout->addWidget(pushButtonDelete);


        gridLayout->addLayout(buttonLayout, 3, 0, 1, 1);

        pushButtonExportCSV = new QPushButton(EnhancedMainWindow);
        pushButtonExportCSV->setObjectName("pushButtonExportCSV");

        gridLayout->addWidget(pushButtonExportCSV, 4, 0, 1, 1);


        retranslateUi(EnhancedMainWindow);

        QMetaObject::connectSlotsByName(EnhancedMainWindow);
    } // setupUi

    void retranslateUi(QWidget *EnhancedMainWindow)
    {
        EnhancedMainWindow->setWindowTitle(QCoreApplication::translate("EnhancedMainWindow", "Consultant Management", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("EnhancedMainWindow", "Search...", nullptr));
        labelTotalEntries->setText(QCoreApplication::translate("EnhancedMainWindow", "Total Entries: 0", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EnhancedMainWindow", "\342\234\217\357\270\217 Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("EnhancedMainWindow", "\342\236\225 Edit", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EnhancedMainWindow", "\360\237\227\221 Delete", nullptr));
        pushButtonExportCSV->setText(QCoreApplication::translate("EnhancedMainWindow", "\360\237\223\244 Export to CSV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnhancedMainWindow: public Ui_EnhancedMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENHANCED_MAINWINDOW_H
