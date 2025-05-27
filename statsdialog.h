#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include "rendezvous.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StatsDialog;
}
QT_END_NAMESPACE

class StatsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StatsDialog(Rendezvous *rdv, QWidget *parent = nullptr);
    ~StatsDialog();

public slots:
    void refreshStats(); // Add this slot

private slots:
    void handleSliceHovered(bool hovered);

private:
    Ui::StatsDialog *ui;
    Rendezvous *rdv;
    QChart *m_statsChart;
    QPieSeries *m_statsSeries;
    void setupChart();
    void updateStatsDisplay();
};

#endif // STATSDIALOG_H
