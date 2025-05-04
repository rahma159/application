/********************************************************************************
** Form generated from reading UI file 'statisticsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICSDIALOG_H
#define UI_STATISTICSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticsDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *pieTab;
    QVBoxLayout *verticalLayout_3;
    QFrame *pieChartFrame;
    QWidget *barTab;
    QVBoxLayout *verticalLayout_4;
    QFrame *barChartFrame;

    void setupUi(QDialog *StatisticsDialog)
    {
        if (StatisticsDialog->objectName().isEmpty())
            StatisticsDialog->setObjectName("StatisticsDialog");
        StatisticsDialog->resize(500, 400);
        horizontalLayout = new QHBoxLayout(StatisticsDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        tabWidget = new QTabWidget(StatisticsDialog);
        tabWidget->setObjectName("tabWidget");
        pieTab = new QWidget();
        pieTab->setObjectName("pieTab");
        verticalLayout_3 = new QVBoxLayout(pieTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        pieChartFrame = new QFrame(pieTab);
        pieChartFrame->setObjectName("pieChartFrame");
        pieChartFrame->setFrameShape(QFrame::Shape::StyledPanel);
        pieChartFrame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_3->addWidget(pieChartFrame);

        tabWidget->addTab(pieTab, QString());
        barTab = new QWidget();
        barTab->setObjectName("barTab");
        verticalLayout_4 = new QVBoxLayout(barTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        barChartFrame = new QFrame(barTab);
        barChartFrame->setObjectName("barChartFrame");
        barChartFrame->setFrameShape(QFrame::Shape::StyledPanel);
        barChartFrame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_4->addWidget(barChartFrame);

        tabWidget->addTab(barTab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(StatisticsDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(StatisticsDialog);
    } // setupUi

    void retranslateUi(QDialog *StatisticsDialog)
    {
        StatisticsDialog->setWindowTitle(QCoreApplication::translate("StatisticsDialog", "Invoice Statistics", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(pieTab), QCoreApplication::translate("StatisticsDialog", "Pie Chart", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(barTab), QCoreApplication::translate("StatisticsDialog", "Bar Chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticsDialog: public Ui_StatisticsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICSDIALOG_H
