#ifndef ENHANCED_MAINWINDOW_H
#define ENHANCED_MAINWINDOW_H

#include "qpieslice.h"
#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QChartView;
QT_END_NAMESPACE

namespace Ui {
class EnhancedMainWindow;
}

class EnhancedMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EnhancedMainWindow(QWidget *parent = nullptr);
    ~EnhancedMainWindow();

private slots:
    void handleTableClick(const QModelIndex &index);
    void filterTextChanged(const QString &text);
    void onFilterFieldChanged(int index);
    void onAddClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onExportClicked();

    // 🔵 New sorting slots (added)
    void sortByName();
    void sortByID();
    void sortByRate();

private:
    void updateTotalCount();
    void renderCharts();  // 📊 Adds charts for hourly rate and role

    Ui::EnhancedMainWindow *ui;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxyModel;
    int currentFilterColumn;
    QPieSlice* lastClickedSlice = nullptr;
    int lastClickedBarIndex = -1;

};

#endif // ENHANCED_MAINWINDOW_H
