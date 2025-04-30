#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class StatisticsDialog;
}
QT_END_NAMESPACE

class QVBoxLayout; // Forward declaration (fixes your previous error)

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = nullptr);
    ~StatisticsDialog();

private:
    Ui::StatisticsDialog *ui;

    void setupCharts();  // <--- You forgot this before

    void createPieChart(const QMap<QString, int> &statusCounts, int totalCount, QVBoxLayout *layout);
    void createBarChart(const QMap<QString, int> &statusCounts, QVBoxLayout *layout);

};

#endif // STATISTICSDIALOG_H
