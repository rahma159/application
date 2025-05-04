#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVBoxLayout>  // Add this include

namespace Ui {
class StatisticsDialog;
}

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(const QMap<QString, int>& statusData,
                              const QMap<QString, double>& amountData,
                              QWidget *parent = nullptr);
    ~StatisticsDialog();

private:
    Ui::StatisticsDialog *ui;
    void setupCharts(const QMap<QString, int>& statusData,
                     const QMap<QString, double>& amountData);
    void createPieChart(const QMap<QString, int>& data, QVBoxLayout *layout);
    void createBarChart(const QMap<QString, double>& data, QVBoxLayout *layout);
};

#endif // STATISTICSDIALOG_H
