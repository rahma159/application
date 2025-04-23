#ifndef CLIENTDASHBOARDWIDGET_H
#define CLIENTDASHBOARDWIDGET_H

#include <QDialog> // Or QWidget if preferred

namespace Ui {
class ClientDashboardWidget;
}

class QStandardItemModel; // Or your invoice model type

class ClientDashboardWidget : public QDialog // Or QWidget
{
    Q_OBJECT

public:
    // Pass client ID or name to know whose dashboard to show
    explicit ClientDashboardWidget(int clientId, QWidget *parent = nullptr);
    ~ClientDashboardWidget();

private slots:
               // Add slots here if you add buttons like "View Details" or "Pay Now"
               // void on_viewDetailsButton_clicked();
               // void on_payNowButton_clicked();
               // void on_clientInvoiceTable_doubleClicked(const QModelIndex &index);

private:
    Ui::ClientDashboardWidget *ui;
    int currentClientId;
    QStandardItemModel *clientInvoiceModel; // Example model

    void loadDashboardData();
    void setupInvoiceTable();
    void setupConnections();
    // void updateActionButtonsState(); // If buttons are added
};

#endif // CLIENTDASHBOARDWIDGET_H
