#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QMap>
#include <QtMath> // <<< ADDED for qCeil

// Forward declare Client struct (include clientmanager.h only in .cpp)
struct ClientData;

// Forward declare base classes, NOT chart classes
class QWidget;
class QObject; // QChart inherits QObject (indirectly via QGraphicsObject)

// NO Qt Charts includes or namespace macros here

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit ChartDialog(QWidget *parent = nullptr);
    ~ChartDialog();

    // Function to generate and display the chart based on client data (Renamed previously)
    void generateClientsPerDomainChart(const QMap<QString, ClientData>& clients);

private:
    // Use base class pointers to hide specific types from MOC
    QWidget *m_chartView_base; // Pointer to the view widget
    QObject *m_chart_base;     // Pointer to the chart object
};

#endif // CHARTDIALOG_H
