#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "modclient.h"
#include "newclient.h"
#include "history.h"
#include <QSqlTableModel>
#include <QFileDialog>




QT_BEGIN_NAMESPACE
namespace Ui {
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
    void on_pushButton_clicked();
    void on_btnDelete_clicked(); // Slot for the delete button
    void on_btnGenerate_clicked();
    void onFilterClient(); // Slot for filter functionality
    void on_btnStats_clicked();
    void on_btnMod_clicked();
    void on_btnHistory_clicked();

public slots:
    void refreshTable();



private:
    Ui::MainWindow *ui;
    NewClient *ptrNewClient;
    ModClient *ptrModClient;
    history *ptrHistory;
    QSqlQueryModel *model; // Model to manage data in the QTableView
    Client Etmp;
};

#endif // MAINWINDOW_H
