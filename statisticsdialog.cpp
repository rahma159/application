#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QVBoxLayout>

// NO: using namespace QtCharts;

StatisticsDialog::StatisticsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);
    setupCharts();
}

StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}

void StatisticsDialog::setupCharts()
{
    QMap<QString, int> appointmentData;
    appointmentData["Completed"] = 40;
    appointmentData["Pending"] = 20;
    appointmentData["Cancelled"] = 10;

    int totalAppointments = 70;

    QVBoxLayout *pieLayout = new QVBoxLayout(ui->pieChartFrame);
    QVBoxLayout *barLayout = new QVBoxLayout(ui->barChartFrame);

    createPieChart(appointmentData, totalAppointments, pieLayout);
    createBarChart(appointmentData, barLayout);
}

void StatisticsDialog::createPieChart(const QMap<QString, int> &data, int /*total*/, QVBoxLayout *layout)
{
    QPieSeries *series = new QPieSeries();

    for (auto it = data.begin(); it != data.end(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        series->append(label, it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Appointment Status Distribution");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}

void StatisticsDialog::createBarChart(const QMap<QString, int> &data, QVBoxLayout *layout)
{
    QBarSet *set = new QBarSet("Appointments");

    QStringList categories;
    for (auto it = data.begin(); it != data.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Appointments by Status");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}
