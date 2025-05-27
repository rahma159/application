/********************************************************************************
** Form generated from reading UI file 'statsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSDIALOG_H
#define UI_STATSDIALOG_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_StatsDialog
{
public:
    QChartView *chartView;

    void setupUi(QDialog *StatsDialog)
    {
        if (StatsDialog->objectName().isEmpty())
            StatsDialog->setObjectName("StatsDialog");
        StatsDialog->resize(500, 350);
        chartView = new QChartView(StatsDialog);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(10, 10, 480, 320));
        chartView->setRenderHints(QPainter::Antialiasing);

        retranslateUi(StatsDialog);

        QMetaObject::connectSlotsByName(StatsDialog);
    } // setupUi

    void retranslateUi(QDialog *StatsDialog)
    {
        StatsDialog->setWindowTitle(QCoreApplication::translate("StatsDialog", "Statistiques par Objet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsDialog: public Ui_StatsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSDIALOG_H
