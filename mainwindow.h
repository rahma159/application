
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QApplication>

// Forward declarations are good practice if full definition isn't needed in header
class InvoiceManagementWidget;
class ClientPaymentWidget; // Forward declare

// Include necessary headers if types are used directly (e.g., member pointers)
#include "invoicemanagementwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT // Must be first or near the top inside the class definition

public:
    explicit MainWindow(QWidget *parent = nullptr); // Add explicit keyword
    ~MainWindow();

private slots:
    // Slot for the manage invoices button
    void on_manageInvoicesButton_clicked();


    // Slot connected to the destroyed() signal of InvoiceManagementWidget
    void onInvoiceWidgetDestroyed();

    // Removed: void onClientWidgetDestroyed(); // Not needed for the dialog approach

private:
    Ui::MainWindow *ui; // Pointer to the UI elements
    InvoiceManagementWidget *invoiceWidget;
};

#endif // MAINWINDOW_H
