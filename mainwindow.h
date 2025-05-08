// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "invoicemanagementwidget.h" // Assuming this is already there
#include "settingsdialog.h"        // <<< ADD THIS INCLUDE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_manageInvoicesButton_clicked();
    void onInvoiceWidgetDestroyed();
    void on_settingsButton_clicked(); // <<< ADD THIS SLOT (adjust name if your button is different)
        // If your button is an action in a menu/toolbar, it might be on_actionSettings_triggered()

private:
    Ui::MainWindow *ui;
    InvoiceManagementWidget *invoiceWidget;
    SettingsDialog *m_settingsDialog; // <<< ADD THIS MEMBER
};
#endif // MAINWINDOW_H
