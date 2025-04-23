#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations are good practice if full definition isn't needed in header
class InvoiceManagementWidget;
class ClientPaymentWidget; // Forward declare

// Include necessary headers if types are used directly (e.g., member pointers)
#include "invoicemanagementwidget.h" // Needed for InvoiceManagementWidget* invoiceWidget;
#include "clientpaymentwidget.h"

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

    // Slot for the client payment button
    void on_clientPaymentsButton_clicked();

    // Slot connected to the destroyed() signal of InvoiceManagementWidget
    void onInvoiceWidgetDestroyed();

    // Removed: void onClientWidgetDestroyed(); // Not needed for the dialog approach

private:
    Ui::MainWindow *ui; // Pointer to the UI elements
    InvoiceManagementWidget *invoiceWidget; // Pointer to manage the invoice widget instance

    // Removed: ClientPaymentWidget *clientWidget; // Not needed for the dialog approach

    // Removed status bar related members/methods if they are truly gone
    // QLabel *dbStatusLabel;
    // void updateDatabaseStatusIndicator();
};

#endif // MAINWINDOW_H
