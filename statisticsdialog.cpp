#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QVBoxLayout>  // Add this include

StatisticsDialog::StatisticsDialog(const QMap<QString, int>& statusData,
                                   const QMap<QString, double>& amountData,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);
    setupCharts(statusData, amountData);
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::setupCharts(const QMap<QString, int>& statusData,
                                   const QMap<QString, double>& amountData)
{
    QVBoxLayout *pieLayout = new QVBoxLayout(ui->pieChartFrame);
    QVBoxLayout *barLayout = new QVBoxLayout(ui->barChartFrame);

    createPieChart(statusData, pieLayout);
    createBarChart(amountData, barLayout);
}

void StatisticsDialog::createPieChart(const QMap<QString, int>& data, QVBoxLayout *layout)
{
    QPieSeries *series = new QPieSeries();
    int totalInvoices = 0;

    // Calculate total for percentages
    for (auto it = data.begin(); it != data.end(); ++it) {
        totalInvoices += it.value();
    }

    // Create slices
    for (auto it = data.begin(); it != data.end(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        double percentage = (totalInvoices > 0) ? (it.value() * 100.0 / totalInvoices) : 0;
        QString percentageStr = QString::number(percentage, 'f', 1) + "%";

        QPieSlice *slice = series->append(label, it.value());
        slice->setLabelVisible();
        slice->setLabel(QString("%1\n%2").arg(label).arg(percentageStr));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Invoice Status Distribution");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}

void StatisticsDialog::createBarChart(const QMap<QString, double>& data, QVBoxLayout *layout)
{
    QBarSet *set = new QBarSet("Invoice Amounts");
    QStringList categories;

    for (auto it = data.begin(); it != data.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Invoice Amounts by Category");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Amount");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}
