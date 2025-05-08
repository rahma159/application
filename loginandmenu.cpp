#include<QProcess>
#include "loginandmenu.h"
#include "ui_loginandmenu.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QIcon>
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invoicemanagementwidget.h"
#include "settingsdialog.h"
#include "clientmanager.h"

LoginAndMenu::LoginAndMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginAndMenu)
    , invoiceWidget(nullptr)
    , m_settingsDialog(nullptr)
{
    ui->setupUi(this); // KEEP THIS FIRST (after initializer list)

    qDebug() << "--- LoginAndMenu Constructor Start ---";

    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QMessageBox::information(this,
                                 tr("Database Connection"),
                                 tr("Database connected successfully!"));
        qDebug() << "LoginAndMenu: Confirmed database connection is open.";
    } else {
        QMessageBox::critical(this, tr("Database Error"),
                              tr("CRITICAL: Database connection failed or was lost. Please check configuration or restart."));
        qDebug() << "LoginAndMenu: CRITICAL - database connection found closed or invalid.";
    }
    // --- ADD THIS SECTION BACK ---
    // --- Load Stylesheet ---
    QFile styleFile(":/styles/style.qss"); // Path from resource file (check prefix and name in Resources.qrc)
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        QString styleSheet = stream.readAll();
        this->setStyleSheet(styleSheet); // Apply stylesheet to the main window and its children
        styleFile.close();
        qDebug() << "Stylesheet ':/styles/style.qss' loaded successfully.";
    } else {
        // Warning if the file couldn't be opened from resources
        qWarning() << "Could not load stylesheet ':/styles/style.qss'. Check path/prefix in Resources.qrc.";
    }
    // --- END OF STYLESHEET SECTION ---


    // --- ADD THIS SECTION BACK (for icons) ---
    // --- Configure Login Page Input Fields ---
    if (ui->usernameLineEdit) {
        ui->usernameLineEdit->setPlaceholderText("Email or username");
        QIcon userIcon(":/user_icon.png"); // Ensure 'user_icon.png' is in Resources.qrc
        if (!userIcon.isNull()) {
            ui->usernameLineEdit->addAction(userIcon, QLineEdit::LeadingPosition);
            qDebug() << "User icon set for usernameLineEdit.";
        } else { qWarning() << "Could not load user icon ':/user_icon.png'"; }
    } else { qWarning() << "UI object 'usernameLineEdit' not found!"; }

    if (ui->passwordLineEdit) {
        ui->passwordLineEdit->setPlaceholderText("Password");
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
        QIcon lockIcon(":/lock_icon.png"); // Ensure 'lock_icon.png' is in Resources.qrc
        if (!lockIcon.isNull()) {
            ui->passwordLineEdit->addAction(lockIcon, QLineEdit::LeadingPosition);
            qDebug() << "Lock icon set for passwordLineEdit.";
        } else { qWarning() << "Could not load lock icon ':/lock_icon.png'"; }
    } else { qWarning() << "UI object 'passwordLineEdit' not found!"; }

    // --- Configure Forgot Password Page Input Field ---
    if (ui->usernameLineEdit_2) { // Using corrected name
        ui->usernameLineEdit_2->setPlaceholderText("Enter your username or email");
        QIcon emailIcon(":/user_icon.png"); // Re-use user/email icon
        if (!emailIcon.isNull()) {
            ui->usernameLineEdit_2->addAction(emailIcon, QLineEdit::LeadingPosition);
            qDebug() << "Email icon set for usernameLineEdit_2.";
        } else { qWarning() << "Could not load user icon ':/user_icon.png' for recovery field."; }
    } else { qWarning() << "UI object 'usernameLineEdit_2' not found!"; }
    // --- END OF ICON SECTION ---


    // --- Initial Setup: Set Starting Page ---
    qDebug() << "Setting initial page...";
    if (ui->stackedWidget && ui->loginPage) {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
        qDebug() << "Set initial page to loginPage";
    } else {
        qWarning() << "Error: Could not set initial page. stackedWidget or loginPage not found!";
        // ... (fallback logic remains the same) ...
        if(ui->stackedWidget) { ui->stackedWidget->setCurrentIndex(0); }
        else { qCritical() << "CRITICAL: stackedWidget is NULL!"; }
    }

    setWindowTitle("ConsultIQ");
    qDebug() << "--- LoginAndMenu Constructor End ---";


    // Client Management Button
    if (ui->clientManagementButton) {
        QIcon iconClient(":/icon/client_management.png"); // Use your actual icon path
        if (!iconClient.isNull()) {
            ui->clientManagementButton->setIcon(iconClient);
            // Optional: Set size explicitly if QSS doesn't handle it sufficiently
            // ui->clientManagementButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for clientManagementButton";
        } else {
            qWarning() << "Could not load icon for clientManagementButton at ':/icons/client_management.png'";
        }
    } else { qWarning() << "UI object 'clientManagementButton' not found!"; }

    // Appointment Scheduling Button
    if (ui->appointmentSchedulingButton) {
        QIcon iconAppointment(":/icon/appointment_scheduling.png"); // Use your actual icon path
        if (!iconAppointment.isNull()) {
            ui->appointmentSchedulingButton->setIcon(iconAppointment);
            // ui->appointmentSchedulingButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for appointmentSchedulingButton";
        } else {
            qWarning() << "Could not load icon for appointmentSchedulingButton at ':/icons/appointment_scheduling.png'";
        }
    } else { qWarning() << "UI object 'appointmentSchedulingButton' not found!"; }

    // Task Management Button
    if (ui->taskManagementButton) {
        QIcon iconTask(":/icon/task_management.png"); // Use your actual icon path
        if (!iconTask.isNull()) {
            ui->taskManagementButton->setIcon(iconTask);
            // ui->taskManagementButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for taskManagementButton";
        } else {
            qWarning() << "Could not load icon for taskManagementButton at ':/icons/task_management.png'";
        }
    } else { qWarning() << "UI object 'taskManagementButton' not found!"; }

    // Payment & Invoicing Button
    if (ui->paymentInvoicingButton) {
        QIcon iconPayment(":/icon/payment_invoicing.png"); // Use your actual icon path
        if (!iconPayment.isNull()) {
            ui->paymentInvoicingButton->setIcon(iconPayment);
            // ui->paymentInvoicingButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for paymentInvoicingButton";
        } else {
            qWarning() << "Could not load icon for paymentInvoicingButton at ':/icons/payment_invoicing.png'";
        }
    } else { qWarning() << "UI object 'paymentInvoicingButton' not found!"; }

    // Consultant Management Button
    if (ui->consultantManagementButton) {
        QIcon iconConsultant(":/icon/consultant_management.png"); // Use your actual icon path
        if (!iconConsultant.isNull()) {
            ui->consultantManagementButton->setIcon(iconConsultant);
            // ui->consultantManagementButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for consultantManagementButton";
        } else {
            qWarning() << "Could not load icon for consultantManagementButton at ':/icons/consultant_management.png'";
        }
    } else { qWarning() << "UI object 'consultantManagementButton' not found!"; }

    // Analytics Button
    if (ui->analyticsButton) {
        QIcon iconAnalytics(":/icon/analytics.png"); // Use your actual icon path
        if (!iconAnalytics.isNull()) {
            ui->analyticsButton->setIcon(iconAnalytics);
            // ui->analyticsButton->setIconSize(QSize(48, 48));
            qDebug() << "Icon set for analyticsButton";
        } else {
            qWarning() << "Could not load icon for analyticsButton at ':/icons/analytics.png'";
        }
    } else { qWarning() << "UI object 'analyticsButton' not found!"; }

}
void LoginAndMenu::onInvoiceWidgetDestroyed()
{
    qDebug() << "InvoiceManagementWidget destroyed, resetting pointer.";
    invoiceWidget = nullptr;
}

LoginAndMenu::~LoginAndMenu()
{
    delete ui;
}

// --- Slot Implementations ---

// Uses loginButton - Matches screenshot
void LoginAndMenu::on_loginButton_clicked()
{
    qDebug() << "Login button clicked";

    QString entered_username; // Variable to store username from UI
    QString entered_password; // Variable to store password from UI

    // --- 1. GET the text the user actually typed into the fields ---
    if (!ui->usernameLineEdit) {
        QMessageBox::critical(this, "UI Error", "Username input field is missing.");
        qWarning() << "Login attempt failed: usernameLineEdit is null.";
        return;
    }
    entered_username = ui->usernameLineEdit->text().trimmed(); // Get text from UI and remove whitespace

    if (!ui->passwordLineEdit) {
        QMessageBox::critical(this, "UI Error", "Password input field is missing.");
        qWarning() << "Login attempt failed: passwordLineEdit is null.";
        return;
    }
    entered_password = ui->passwordLineEdit->text(); // Get text from UI

    // --- 2. Check if the user left either field empty ---
    if (entered_username.isEmpty() || entered_password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username/email and password.");
        return; // Stop processing
    }

    // --- 3. DEFINE the correct credentials you want to check against ---
    // IMPORTANT: For real applications, NEVER store passwords like this.
    // Use a database with hashed passwords. This is just for testing.
    const QString correct_username = "admin";
    const QString correct_password = "0000"; // Set the correct password here

    qDebug() << "Attempting login for user entered:" << entered_username;

    // --- 4. COMPARE the entered credentials against the correct credentials ---
    bool loginSuccessful = (entered_username == correct_username && entered_password == correct_password);

    // --- 5. Handle Success or Failure ---
    if (loginSuccessful) {
        // User entered the correct username AND correct password
        qDebug() << "Login successful, switching to menu page.";
        if (ui->stackedWidget && ui->menuPage) {
            ui->stackedWidget->setCurrentWidget(ui->menuPage);
            // Optionally clear fields after successful login
            ui->usernameLineEdit->clear();
            ui->passwordLineEdit->clear();
        } else {
            qWarning() << "Error: Could not switch to menu page. stackedWidget or menuPage not found!";
            QMessageBox::critical(this, "Navigation Error", "The menu page could not be loaded.");
        }
    } else {
        // User entered incorrect username OR incorrect password (or both)
        qDebug() << "Login failed for user entered:" << entered_username;
        QMessageBox::warning(this, "Login Failed", "Invalid username/email or password.");
        if(ui->passwordLineEdit) {
            ui->passwordLineEdit->clear(); // Clear only password on failure for convenience
        }
    }
}

// Uses forgotPasswordButton - Matches screenshot
void LoginAndMenu::on_forgotPasswordButton_clicked()
{
    qDebug() << "Forgot Password button clicked, switching page.";
    if (ui->stackedWidget && ui->forgotPasswordPage) { // forgotPasswordPage name matches screenshot
        ui->stackedWidget->setCurrentWidget(ui->forgotPasswordPage);
    } else {
        qWarning() << "Error: Could not switch to forgot password page. stackedWidget or forgotPasswordPage not found!";
        QMessageBox::critical(this, "Navigation Error", "The password reset page could not be loaded.");
    }
}

// Uses backToLoginButton - Matches screenshot
void LoginAndMenu::on_backToLoginButton_clicked()
{
    qDebug() << "Back to Login button clicked, switching page.";
    if (ui->stackedWidget && ui->loginPage) { // loginPage name matches screenshot
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
        // Clear the recovery field when going back - using CORRECTED NAME
        if(ui->usernameLineEdit_2) { // ***** CORRECTED NAME *****
            ui->usernameLineEdit_2->clear();
        } else {
            qWarning() << "Could not clear usernameLineEdit_2: widget not found.";
        }
    } else {
        qWarning() << "Error: Could not switch back to login page. stackedWidget or loginPage not found!";
        QMessageBox::critical(this, "Navigation Error", "The login page could not be loaded.");
    }
}

// Uses recoveryUsernameButton - Matches screenshot
void LoginAndMenu::on_recoveryUsernameButton_clicked()
{
    qDebug() << "Send Reset Link (recoveryUsernameButton) button clicked.";

    QString recoveryUser = "";

    // Safely get recovery username/email - using CORRECTED NAME
    if (!ui->usernameLineEdit_2) { // ***** CORRECTED NAME *****
        QMessageBox::critical(this, "UI Error", "Recovery username input field is missing.");
        qWarning() << "Password reset failed: usernameLineEdit_2 is null.";
        return;
    }
    recoveryUser = ui->usernameLineEdit_2->text().trimmed(); // ***** CORRECTED NAME *****


    if (recoveryUser.isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please enter your username or email to reset the password.");
        return;
    }

    // --- TODO: Add actual password reset link sending logic here ---
    qDebug() << "Password reset requested for:" << recoveryUser << " (Actual sending logic needs implementation)";

    QMessageBox::information(this, "Password Reset Request", "If an account matching that username or email exists, instructions for resetting your password have been sent.");

    // Switch back to the login page
    if (ui->stackedWidget && ui->loginPage) {
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
        // Clear the input field - using CORRECTED NAME
        if(ui->usernameLineEdit_2) { // ***** CORRECTED NAME *****
            ui->usernameLineEdit_2->clear();
        }
    } else {
        qWarning() << "Error: Could not switch back to login page after password reset request.";
        QMessageBox::critical(this, "Navigation Error", "The login page could not be loaded.");
    }
}


// --- Placeholder Slots for Menu Buttons (using names from screenshots) ---
void LoginAndMenu::on_clientManagementButton_clicked() {

    qDebug() << "Cleient Management button clicked";

    // Check DB connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available."));
        return;
    }

    // Create the clientMainWindow only if it doesn't already exist
    if (!clientMainWindow) {
        clientMainWindow = new MainWindow(nullptr);
        clientMainWindow->setAttribute(Qt::WA_DeleteOnClose);  // Auto-delete on close

        // When the window is closed, reset the pointer
        connect(clientMainWindow, &QObject::destroyed, this, [this]() {
            qDebug() << "clientMainWindow destroyed. Resetting pointer.";
            clientMainWindow = nullptr;
        });

        clientMainWindow->show();
        qDebug() << "clientMainWindow opened.";
    } else {
        // If already exists, bring it to front
        clientMainWindow->raise();
        clientMainWindow->activateWindow();
        qDebug() << "clientMainWindow already open. Bringing to front.";
    }

}

void LoginAndMenu::on_appointmentSchedulingButton_clicked() {
    qDebug() << "Appointment Scheduling button clicked";
    QMessageBox::information(this, "Menu", "Appointment Scheduling Clicked (Not Implemented)");
}

void LoginAndMenu::on_taskManagementButton_clicked() {
    qDebug() << "Task Management button clicked";
    QMessageBox::information(this, "Menu", "Task Management Clicked (Not Implemented)");
}

void LoginAndMenu::on_paymentInvoicingButton_clicked() {
    qDebug() << "Manage Invoices button clicked.";
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available. Cannot manage invoices."));
        qDebug() << "Manage Invoices aborted: Database connection lost.";
        return;
    }

    if (!invoiceWidget) {
        invoiceWidget = new InvoiceManagementWidget(this);
        invoiceWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(invoiceWidget, &QObject::destroyed, this, &LoginAndMenu::onInvoiceWidgetDestroyed);
        invoiceWidget->show();
    } else {
        invoiceWidget->raise();
        invoiceWidget->activateWindow();
    }
}

void LoginAndMenu::on_consultantManagementButton_clicked()
{
    qDebug() << "Consultant Management button clicked";

    // Check DB connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available."));
        return;
    }

    // Create the EnhancedMainWindow only if it doesn't already exist
    if (!enhancedMainWindow) {
        enhancedMainWindow = new EnhancedMainWindow(nullptr);
        enhancedMainWindow->setAttribute(Qt::WA_DeleteOnClose);  // Auto-delete on close

        // When the window is closed, reset the pointer
        connect(enhancedMainWindow, &QObject::destroyed, this, [this]() {
            qDebug() << "EnhancedMainWindow destroyed. Resetting pointer.";
            enhancedMainWindow = nullptr;
        });

        enhancedMainWindow->show();
        qDebug() << "EnhancedMainWindow opened.";
    } else {
        // If already exists, bring it to front
        enhancedMainWindow->raise();
        enhancedMainWindow->activateWindow();
        qDebug() << "EnhancedMainWindow already open. Bringing to front.";
    }
}

void LoginAndMenu::on_analyticsButton_clicked() {
    qDebug() << "Bouton Analytics (gestion de m_clientManager) cliqué.";


    // Check DB connection
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, tr("Database Error"),
                             tr("Database connection is not available."));
        return;
    }

    if (!m_clientManager) {
        m_clientManager = new ClientManager(nullptr);
        m_clientManager->setAttribute(Qt::WA_DeleteOnClose);  // Auto-delete on close

        // When the window is closed, reset the pointer
        connect(m_clientManager, &QObject::destroyed, this, [this]() {
            qDebug() << "clientManager destroyed. Resetting pointer.";
            m_clientManager = nullptr;
        });

        m_clientManager->show();
        qDebug() << "m_clientManager opened.";
    } else {
        // If already exists, bring it to front
        m_clientManager->raise();
        m_clientManager->activateWindow();
        qDebug() << "m_clientManager already open. Bringing to front.";
    }


}
