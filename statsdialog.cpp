#include "statsdialog.h"
#include "ui_statsdialog.h"
#include <QMap>
#include <QDebug>

StatsDialog::StatsDialog(Rendezvous *rdv, QWidget *parent)
    : QDialog(parent), ui(new Ui::StatsDialog), rdv(rdv), m_statsChart(nullptr), m_statsSeries(nullptr)
{
    ui->setupUi(this);
    setupChart();
    updateStatsDisplay();
}

StatsDialog::~StatsDialog()
{
    delete ui;
}

void StatsDialog::setupChart()
{
    m_statsChart = new QChart();
    m_statsChart->setTitle("Statistiques par Type");
    m_statsChart->setAnimationOptions(QChart::SeriesAnimations);
    m_statsChart->legend()->setVisible(true);
    m_statsChart->legend()->setAlignment(Qt::AlignBottom);

    ui->chartView->setChart(m_statsChart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void StatsDialog::updateStatsDisplay()
{
    QMap<QString, int> stats = rdv->calculerStatistiquesObjet();

    if (m_statsSeries)
    {
        m_statsChart->removeSeries(m_statsSeries);
        delete m_statsSeries;
        m_statsSeries = nullptr;
    }

    m_statsSeries = new QPieSeries();
    m_statsSeries->setName("RDV par Type");

    if (stats.isEmpty())
    {
        m_statsChart->setTitle("Statistiques par Type (Aucune donnée)");
    }
    else
    {
        m_statsChart->setTitle("Statistiques par Type");
        QMapIterator<QString, int> i(stats);
        while (i.hasNext())
        {
            i.next();
            QPieSlice *slice = m_statsSeries->append(QString("%1 (%2)").arg(i.key()).arg(i.value()), i.value());
            slice->setLabelVisible();
        }
        connect(m_statsSeries, &QPieSeries::hovered, this, &StatsDialog::handleSliceHovered);
    }

    m_statsChart->addSeries(m_statsSeries);
    m_statsChart->legend()->update();
}

void StatsDialog::handleSliceHovered(bool hovered)
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (slice)
    {
        slice->setExploded(hovered);
        slice->setLabelVisible(hovered);
        QFont font = slice->labelFont();
        font.setBold(hovered);
        slice->setLabelFont(font);
    }
}

void StatsDialog::refreshStats()
{
    updateStatsDisplay();
}
