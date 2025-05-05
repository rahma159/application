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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EnhancedMainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditSearch;
    QTableView *tableView;
    QHBoxLayout *buttonLayout;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonDelete;

    void setupUi(QWidget *EnhancedMainWindow)
    {
        if (EnhancedMainWindow->objectName().isEmpty())
            EnhancedMainWindow->setObjectName("EnhancedMainWindow");
        EnhancedMainWindow->resize(268, 251);
        verticalLayout = new QVBoxLayout(EnhancedMainWindow);
        verticalLayout->setObjectName("verticalLayout");
        lineEditSearch = new QLineEdit(EnhancedMainWindow);
        lineEditSearch->setObjectName("lineEditSearch");

        verticalLayout->addWidget(lineEditSearch);

        tableView = new QTableView(EnhancedMainWindow);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

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


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(EnhancedMainWindow);

        QMetaObject::connectSlotsByName(EnhancedMainWindow);
    } // setupUi

    void retranslateUi(QWidget *EnhancedMainWindow)
    {
        lineEditSearch->setText(QString());
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("EnhancedMainWindow", "Search...", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("EnhancedMainWindow", "Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("EnhancedMainWindow", "Edit", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("EnhancedMainWindow", "Delete", nullptr));
        (void)EnhancedMainWindow;
    } // retranslateUi

};

namespace Ui {
    class EnhancedMainWindow: public Ui_EnhancedMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENHANCED_MAINWINDOW_H
