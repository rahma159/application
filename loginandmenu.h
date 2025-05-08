#ifndef LOGINANDMENU_H
#define LOGINANDMENU_H

#include <QMainWindow>

#include "invoicemanagementwidget.h" // Assuming this is already there
#include "settingsdialog.h"        // <<< ADD THIS INCLUDE
#include "enhanced_mainwindow.h"
#include "enhanced_mainwindow.h"
#include "clientmanager.h"
class MainWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class LoginAndMenu; }
QT_END_NAMESPACE

class EnhancedMainWindow;
class ClientManager;
class LoginAndMenu : public QMainWindow
{
    Q_OBJECT

public:
    LoginAndMenu(QWidget *parent = nullptr);
    ~LoginAndMenu();

private slots:
    void onInvoiceWidgetDestroyed();
    void on_loginButton_clicked();
    void on_forgotPasswordButton_clicked();
    void on_backToLoginButton_clicked();
    void on_recoveryUsernameButton_clicked(); // Button on forgot password page

    // --- ADD THESE DECLARATIONS FOR MENU BUTTONS ---
    void on_clientManagementButton_clicked();
    void on_appointmentSchedulingButton_clicked();
    void on_taskManagementButton_clicked();
    void on_paymentInvoicingButton_clicked();
    void on_consultantManagementButton_clicked();
    void on_analyticsButton_clicked();
private:
    Ui::LoginAndMenu *ui;
    InvoiceManagementWidget *invoiceWidget;
    SettingsDialog *m_settingsDialog;
    EnhancedMainWindow* enhancedMainWindow = nullptr;
    MainWindow* clientMainWindow = nullptr;
    ClientManager *m_clientManager =nullptr ;

};
#endif // MAINWINDOW_H
