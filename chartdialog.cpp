#include "chartdialog.h"
#include "clientmanager.h" // Include full ClientManager header for Client struct definition

#include <QVBoxLayout>
#include <QMapIterator> // Keep this if needed elsewhere, otherwise check if necessary
#include <QPainter>
#include <QtMath> // <<< ADDED for qCeil
#include <QDebug> // Added for diagnostics

// Include specific Qt Charts headers instead of the umbrella <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLegend> // Include for QLegend configuration


// Constructor (Modified for window title)
ChartDialog::ChartDialog(QWidget *parent) :
    QDialog(parent),
    m_chartView_base(new QChartView(this)), // Initialize with 'this' as parent
    m_chart_base(new QChart())             // Initialize (no parent needed here, set later)
{
    QChartView *chartView = qobject_cast<QChartView*>(m_chartView_base);
    QChart *chart = qobject_cast<QChart*>(m_chart_base);

    if (!chartView || !chart) {
        qCritical() << "Failed to create chart objects!";
        // Consider adding a message box or disabling functionality
        return;
    }

    // Basic dialog setup
    setWindowTitle("Client Analysis by Domain"); // <<< Translated Title
    setMinimumSize(600, 400);

    chartView->setChart(chart); // Associate chart with the view
    chartView->setRenderHint(QPainter::Antialiasing); // Improve rendering quality

    QVBoxLayout *layout = new QVBoxLayout(this); // Set 'this' as parent for the layout
    layout->addWidget(chartView); // Add the chart view to the layout
    // setLayout(layout); // This is done automatically by QVBoxLayout(this)
    qDebug() << "ChartDialog constructed.";
}

// Destructor
ChartDialog::~ChartDialog()
{
    qDebug() << "ChartDialog destroyed.";
    // Qt's parent-child mechanism handles deletion of m_chartView_base and m_chart_base
    // because 'this' was passed as parent to QChartView.
    // QChart is associated with QChartView, check Qt docs if explicit deletion is needed,
    // but usually setting the chart on the view manages ownership.
}


// Function to generate the "Clients per Domain" bar chart (Renamed and modified previously)
void ChartDialog::generateClientsPerDomainChart(const QMap<QString, ClientData>& clients)
{
    QChart *chart = qobject_cast<QChart*>(m_chart_base);
    if (!chart) {
        qWarning() << "Chart object is invalid in generateClientsPerDomainChart";
        return;
    }
    qDebug() << "Generating 'Clients per Domain' chart for" << clients.count() << "clients.";

    // --- 1. Process Data ---
    QMap<QString, int> clientsPerDomain; // Map Domain -> Count
    for (const auto& client : clients) {
        // Ensure the fix from the previous step is applied here:
        QString domain = client.domain; // <<< Use client.domain (the renamed member)
        if (domain.isEmpty()) {
            domain = "(Unspecified)"; // <<< Translated label for empty domain
        }
        clientsPerDomain[domain]++; // Count by domain
    }
    qDebug() << "Domains found:" << clientsPerDomain.keys();

    // --- 2. Create Chart Series ---
    QBarSeries *series = new QBarSeries(chart); // Parent is the chart
    QStringList categories;

    // Iterate over clientsPerDomain
    for (auto it = clientsPerDomain.constBegin(); it != clientsPerDomain.constEnd(); ++it) {
        QString domainName = it.key(); // Domain name
        int count = it.value();
        QBarSet *set = new QBarSet(domainName); // Label of the set = domain name
        *set << count;
        series->append(set);
        categories << domainName; // Category = domain name
    }

    // --- 3. Configure Chart ---
    chart->removeAllSeries(); // Clear previous series if any
    chart->addSeries(series); // Add the new series
    chart->setTitle("Number of Clients per Domain"); // <<< Translated chart title
    chart->setAnimationOptions(QChart::SeriesAnimations); // Enable animations

    // --- 4. Configure Axes ---
    // Dispose of old axes if they exist before creating new ones
    qDeleteAll(chart->axes());

    QBarCategoryAxis *axisX = new QBarCategoryAxis(chart); // Parent is the chart
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom); // Add axis to the chart
    series->attachAxis(axisX); // Attach series to the axis

    QValueAxis *axisY = new QValueAxis(chart); // Parent is the chart
    axisY->setTitleText("Number of Clients"); // <<< Axis title (already English)
    axisY->setLabelFormat("%d"); // Integer format for labels

    // Calculate max value for Y-axis range
    int maxCount = 0;
    // Iterate over the values of clientsPerDomain
    for(int count : clientsPerDomain.values()) { // Use .values() for efficiency
        if (count > maxCount) {
            maxCount = count;
        }
    }
    // Set a slightly larger range than max value, handle case of 0 clients
    axisY->setRange(0, maxCount > 0 ? maxCount + qCeil(maxCount * 0.1) : 5); // Add 10% margin or min 5
    // Adjust tick count based on max value for readability
    axisY->setTickCount(qMin(maxCount + 2, 11)); // Max 11 ticks, ensure 0 and max are shown

    chart->addAxis(axisY, Qt::AlignLeft); // Add axis to the chart
    series->attachAxis(axisY); // Attach series to the axis


    // --- 5. Legend ---
    chart->legend()->setVisible(true); // Show the legend
    chart->legend()->setAlignment(Qt::AlignBottom); // Position the legend

    qDebug() << "Chart generation complete.";
} // End of generateClientsPerDomainChart function
