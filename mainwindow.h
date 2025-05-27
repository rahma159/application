#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel> // Add this include
#include <QSystemTrayIcon>
#include <QMap>
#include <QTableView>

// Qt Charts headers
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

// Project headers
#include "rendezvous.h"
#include "calendrierdialog.h"

// Add forward declaration for the stats dialog
class StatsDialog;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ajouterRendezvous();
    void supprimerRendezvous();
    void modifierRendezvous();
    void refreshTableView();
    void on_comboBox_Tri_currentIndexChanged(int index);
    void on_pushButton_Recherche_clicked();
    void on_pushButton_PDF_clicked();
    void on_pushButton_Stats_clicked(); // Will open the stats dialog
    void on_pushButton_Calendrier_clicked();
    void handleCalendarUpdate();

private:
    void setupTableView(QSqlQueryModel *model); // Correct type
    void showNotification(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information);
    void genererPDF();
    void checkUpcomingRendezvous(); // Ajouté

    Ui::MainWindow *ui;
    Rendezvous rdv;
    QSystemTrayIcon *trayIcon;
    CalendrierDialog *calendarDialog;
    StatsDialog *statsDialog = nullptr; // Add pointer to stats dialog
};

#endif // MAINWINDOW_H
