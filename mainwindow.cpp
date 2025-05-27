#include "mainwindow.h"
#include "ui_mainwindow.h" // Include the UI definition header
#include "rendezvous.h"
#include "calendrierdialog.h" // Include calendar dialog
#include "statsdialog.h"      // Add this include
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QMap>
#include <QDate>       // Include QDate for PDF filename
#include <QPageSize>   // Include for QPageSize
#include <QHeaderView> // Include for horizontalHeader

// Include chart components
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),  // Now Ui::MainWindow is defined
      calendarDialog(nullptr), // Initialize calendar dialog pointer
      statsDialog(nullptr)     // Initialize stats dialog pointer
{
    ui->setupUi(this); // 'ui' is now correctly initialized and usable

    // Initialize System Tray Icon
    trayIcon = new QSystemTrayIcon(this);
    // Use direct path for the icon
    trayIcon->setIcon(QIcon("C:/Users/PC/Downloads/QT__ (1)/QT__ (1)/QT__/notif.png"));
    trayIcon->setVisible(true); // Make it visible if you want an icon in the tray

    // Check if system tray is available
    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::warning(this, "Warning", "System tray notifications are not available on this system.");
        // Optionally disable notification calls or tray icon visibility
        // trayIcon->setVisible(false);
    }

    // Connect UI buttons to slots
    connect(ui->submit_ajouter, &QPushButton::clicked, this, &MainWindow::ajouterRendezvous);
    connect(ui->pushButton_Supprimer, &QPushButton::clicked, this, &MainWindow::supprimerRendezvous);
    connect(ui->pushButton_Modifier, &QPushButton::clicked, this, &MainWindow::modifierRendezvous);
    connect(ui->comboBox_Tri, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_Tri_currentIndexChanged(int)));
    connect(ui->pushButton_Recherche, &QPushButton::clicked, this, &MainWindow::on_pushButton_Recherche_clicked);
    connect(ui->pushButton_PDF, &QPushButton::clicked, this, &MainWindow::on_pushButton_PDF_clicked);
    connect(ui->pushButton_Stats, &QPushButton::clicked, this, &MainWindow::on_pushButton_Stats_clicked);
    connect(ui->pushButton_Calendrier, &QPushButton::clicked, this, &MainWindow::on_pushButton_Calendrier_clicked);

    // Remove/hide the chart view in the main window
    ui->statsChartView->setVisible(false);

    // Initial data load
    refreshTableView(); // Load initial data

    // Notification: check at startup and every minute
    checkUpcomingRendezvous();
    QTimer *notifTimer = new QTimer(this);
    connect(notifTimer, &QTimer::timeout, this, &MainWindow::checkUpcomingRendezvous);
    notifTimer->start(60 * 1000); // 1 minute
}

MainWindow::~MainWindow()
{
    delete ui; // 'ui' is correctly deleted
    // trayIcon is a child of MainWindow, automatically deleted
    // calendarDialog might need explicit deletion if not parented or managed differently
    // Chart objects are children of the chart view or managed manually, ensure proper cleanup if needed
    // If m_statsChart is added directly to chartView, it's managed by it.
    // If series is added to chart, it's managed by chart.
}

// Helper function to show system notifications
void MainWindow::showNotification(const QString &title, const QString &message, QSystemTrayIcon::MessageIcon icon)
{
    // Only show if tray is available and icon is visible
    if (QSystemTrayIcon::isSystemTrayAvailable() && trayIcon->isVisible())
    {
        // Check if the icon loaded successfully (optional but good practice)
        if (trayIcon->icon().isNull())
        {
            qDebug() << "Notification icon failed to load from path.";
            // Optionally show a message box or log this error
        }
        trayIcon->showMessage(title, message, icon, 3000); // Show for 3 seconds
    }
    else
    {
        qDebug() << "System tray not available or icon not visible. Notification skipped:" << title << message;
        // Optionally show a QMessageBox as a fallback
        // if (icon == QSystemTrayIcon::Critical) {
        //     QMessageBox::critical(this, title, message);
        // } else {
        //     QMessageBox::information(this, title, message);
        // }
    }
}

void MainWindow::ajouterRendezvous()
{
    // ... (Get values from UI as before) ...
    int id = ui->lineEdit_ID_RDV->text().toInt();
    QDate date = ui->dateEdit_DATE->date();
    QTime time = ui->timeEdit_HEURE->time();
    QString objet = ui->lineEdit_OBJET->text();
    QString statut = ui->comboBox_STATUT->currentText();
    QString type = ui->comboBox_TYPE_RDV->currentText();

    // Basic validation
    if (id <= 0 || objet.isEmpty() || type.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "ID, Objet, and Type cannot be empty and ID must be positive.");
        return;
    }

    rdv.setId(id);
    rdv.setDate(date);
    rdv.setHeure(time);
    rdv.setObjet(objet);
    rdv.setStatut(statut);
    rdv.setType(type);

    if (rdv.ajouter())
    {
        showNotification("Success", "Appointment successfully added!", QSystemTrayIcon::Information);
        refreshTableView(); // Refresh table view
        // Clear input fields
        ui->lineEdit_ID_RDV->clear();
        ui->dateEdit_DATE->setDate(QDate::currentDate());
        ui->timeEdit_HEURE->setTime(QTime::currentTime());
        ui->lineEdit_OBJET->clear();
        ui->comboBox_STATUT->setCurrentIndex(0);   // Reset combo box if needed
        ui->comboBox_TYPE_RDV->setCurrentIndex(0); // Reset type combo box
        if (statsDialog && statsDialog->isVisible())
            statsDialog->refreshStats(); // Refresh stats dialog if open
    }
    else
    {
        showNotification("Erreur", "Failed to add appointment.", QSystemTrayIcon::Critical);
        QMessageBox::critical(this, "Error", "Failed to add appointment");
    }
    if (statsDialog && statsDialog->isVisible())
        statsDialog->refreshStats();
}

void MainWindow::supprimerRendezvous()
{
    int id = ui->lineEdit_ID_RDV_Supprimer->text().toInt();
    if (id <= 0)
    {
        QMessageBox::warning(this, "Input Error", "Please enter a valid ID to delete.");
        return;
    }

    // Optional: Confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", QString("Are you sure you want to delete Event ID %1?").arg(id),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        return;
    }

    if (rdv.supprimer(id))
    {
        showNotification("Success", "Event was deleted!", QSystemTrayIcon::Information);
        refreshTableView();                     // Refresh table view
        ui->lineEdit_ID_RDV_Supprimer->clear(); // Clear the input field
        if (statsDialog && statsDialog->isVisible())
            statsDialog->refreshStats(); // Refresh stats dialog if open
    }
    else
    {
        showNotification("Error", "Deletion failed!", QSystemTrayIcon::Critical);
        QMessageBox::critical(this, "Error", "Deletion failed! Please check the ID.");
    }
    statsDialog->refreshStats();
}

void MainWindow::modifierRendezvous()
{
    // ... (Get updated values from UI as before) ...
    int id = ui->lineEdit_ID_RDV_Modifier->text().toInt();
    QDate date = ui->dateEdit_DATE_Modifier->date();
    QTime time = ui->timeEdit_HEURE_Modifier->time();
    QString objet = ui->lineEdit_OBJET_Modifier->text();
    QString statut = ui->comboBox_STATUT_Modifier->currentText();
    QString type = ui->comboBox_TYPE_RDV_Modifier->currentText();

    // Basic validation
    if (id <= 0 || objet.isEmpty() || type.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "ID, Objet, and Type cannot be empty and ID must be positive.");
        return;
    }

    rdv.setId(id);
    rdv.setDate(date);
    rdv.setHeure(time);
    rdv.setObjet(objet);
    rdv.setStatut(statut);
    rdv.setType(type);

    if (rdv.modifier())
    {
        showNotification("Success", "Event modified!", QSystemTrayIcon::Information);
        refreshTableView(); // Refresh table view
        if (statsDialog && statsDialog->isVisible())
            statsDialog->refreshStats(); // Refresh stats dialog if open
    }
    else
    {
        showNotification("Error", "Failed to update!", QSystemTrayIcon::Critical);
        QMessageBox::critical(this, "Error", "Update failed! Please check the ID.");
    }
    statsDialog->refreshStats();
}

// Renamed from afficherRendezvous to avoid confusion with the Rendezvous class method
void MainWindow::refreshTableView()
{
    QSqlQueryModel *model = rdv.afficher(); // Get the default unsorted view
    setupTableView(model);
}

// Helper to set model to table view and handle potential errors
void MainWindow::setupTableView(QSqlQueryModel *model)
{
    // Get the old model currently set on the view
    QAbstractItemModel *oldModel = ui->tableWidget_RDV->model();

    if (model)
    {
        ui->tableWidget_RDV->setModel(model); // Use setModel for QSqlQueryModel with QTableView
        // Optional: Adjust column widths, etc.
        ui->tableWidget_RDV->resizeColumnsToContents();
        ui->tableWidget_RDV->horizontalHeader()->setStretchLastSection(true);
    }
    else
    {
        qDebug() << "Error: Model is null.";
        // Clear the view if the model is null by setting an empty model or nullptr
        ui->tableWidget_RDV->setModel(nullptr); // Clear the model from the view
        QMessageBox::critical(this, "Error", "Failed to load data for the table.");
    }

    // Delete the old model *after* setting the new one
    if (oldModel && oldModel != model)
    {
        // Important: Ensure the old model is deleted to prevent memory leaks
        // QSqlQueryModel should be deleted when it's no longer needed.
        // The view does NOT take ownership by default.
        oldModel->deleteLater(); // Use deleteLater for safety
    }
}

void MainWindow::on_comboBox_Tri_currentIndexChanged(int index)
{
    if (index > 0)
    { // Ignore the placeholder "Trier par..."
        QString critere = ui->comboBox_Tri->currentText();
        QSqlQueryModel *model = rdv.afficherTri(critere);
        setupTableView(model);
    }
    else
    {
        refreshTableView(); // Reset to default view if "Trier par..." is selected
    }
}

void MainWindow::on_pushButton_Recherche_clicked()
{
    QString searchText = ui->lineEdit_Recherche->text().trimmed();
    int criteriaIndex = ui->comboBox_RechercheCritere->currentIndex();

    if (criteriaIndex > 0 && !searchText.isEmpty())
    {
        QString criteria = ui->comboBox_RechercheCritere->currentText();

        // Special handling for ID search
        if (criteria == "EVENT ID")
        {
            bool isNumeric;
            int id = searchText.toInt(&isNumeric);

            if (!isNumeric || id <= 0)
            {
                QMessageBox::warning(this, "Invalid ID",
                                     "Please enter a positive numeric ID");
                return;
            }
        }

        QSqlQueryModel *model = rdv.rechercher(criteria, searchText);
        setupTableView(model);

        if (!model || model->rowCount() == 0)
        {
            QMessageBox::information(this, "Search Results",
                                     QString("No appointments found matching:\n\"%1\" in %2")
                                         .arg(searchText, criteria));
        }
    }
    else if (searchText.isEmpty() && criteriaIndex > 0)
    {
        QMessageBox::warning(this, "Missing Search Term",
                             QString("Please enter a search term for %1")
                                 .arg(ui->comboBox_RechercheCritere->currentText()));
        ui->lineEdit_Recherche->setFocus();
    }
    else
    {
        refreshTableView();
    }
}

void MainWindow::on_pushButton_PDF_clicked()
{
    genererPDF();
}

void MainWindow::genererPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter en PDF"), QString(), "*.pdf");
    if (fileName.isEmpty())
    {
        return; // User cancelled
    }

    QPdfWriter pdfWriter(fileName);
    QPageSize pageSize(QPageSize::PageSizeId::A4);
    pdfWriter.setPageSize(pageSize);
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30));

    QTextDocument doc;
    // Set the document's page size to match the PDF writer for better scaling
    QSizeF pagePointSize = pageSize.size(QPageSize::Point);
    doc.setPageSize(pagePointSize);
    doc.setDefaultFont(QFont("sans-serif", 12)); // Slightly larger font

    QString htmlContent = "<html><head><style>"
                          "body { font-family: sans-serif; font-size: 12pt; }"
                          "h1 { color: #8E44AD; text-align: center; font-size: 20pt; }"
                          "table { width: 100%; border-collapse: collapse; margin-top: 20px; font-size: 11pt; }"
                          "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }"
                          "th { background-color: #9B59B6; color: white; font-weight: bold; }"
                          "tr:nth-child(even) { background-color: #f2f2f2; }"
                          "</style></head><body>";

    htmlContent += "<h1>Liste des Rendez-vous</h1>";
    htmlContent += QString("<p>Généré le: %1</p>").arg(QDate::currentDate().toString("dd/MM/yyyy"));

    QAbstractItemModel *model = ui->tableWidget_RDV->model();
    if (!model)
    {
        QMessageBox::critical(this, "Erreur PDF", "Impossible de récupérer les données de la table.");
        return;
    }

    htmlContent += "<table><thead><tr>";
    for (int col = 0; col < model->columnCount(); ++col)
    {
        htmlContent += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    htmlContent += "</tr></thead><tbody>";

    for (int row = 0; row < model->rowCount(); ++row)
    {
        htmlContent += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col)
        {
            QVariant data = model->data(model->index(row, col));
            QString dataString;
            QString header = model->headerData(col, Qt::Horizontal).toString();
            if (header == "Date")
            {
                dataString = data.toDate().toString("dd/MM/yyyy");
            }
            else if (header == "Heure")
            {
                dataString = data.toString();
            }
            else
            {
                dataString = data.toString();
            }
            htmlContent += "<td>" + dataString + "</td>";
        }
        htmlContent += "</tr>";
    }

    htmlContent += "</tbody></table></body></html>";

    doc.setHtml(htmlContent);

    // Use doc.print for proper scaling
    doc.print(&pdfWriter);

    showNotification("Succès", "PDF file successfully generated!", QSystemTrayIcon::Information);
    QMessageBox::information(this, "PDF generated", "The PDF file has been saved:\n" + fileName);
}

void MainWindow::on_pushButton_Stats_clicked()
{
    if (!statsDialog)
        statsDialog = new StatsDialog(&rdv, this);
    statsDialog->show();
    statsDialog->raise();
    statsDialog->activateWindow();
}

void MainWindow::on_pushButton_Calendrier_clicked()
{
    if (!calendarDialog)
    {
        calendarDialog = new CalendrierDialog(&rdv, this); // Pass Rendezvous object, set parent
        // Connect a signal from the dialog to refresh the main window's table after changes
        connect(calendarDialog, &CalendrierDialog::dataChanged, this, &MainWindow::handleCalendarUpdate);
    }
    calendarDialog->refreshAppointments(); // Load/refresh appointments in calendar
    calendarDialog->show();
    calendarDialog->raise(); // Bring to front
    calendarDialog->activateWindow();
}

// Slot to handle updates from the calendar dialog
void MainWindow::handleCalendarUpdate()
{
    refreshTableView(); // Refresh the main table view
}

void MainWindow::checkUpcomingRendezvous()
{
    QSqlQuery query;
    QDateTime now = QDateTime::currentDateTime();
    QDateTime limit = now.addSecs(3 * 3600); // 3 hours from now

    // On récupère tous les rendez-vous et on filtre côté C++
    query.prepare("SELECT OBJET, DATERDV, HEURE FROM rendezvous");
    if (query.exec())
    {
        QStringList alerts;
        while (query.next())
        {
            QString objet = query.value(0).toString();
            QDate date = query.value(1).toDate();
            QTime heure = query.value(2).toTime();
            QDateTime dt(date, heure);
            int minutes = now.secsTo(dt) / 60;
            if (dt >= now && dt <= limit)
                alerts << QString("RDV '%1' à %2 (%3 min)").arg(objet).arg(dt.toString("dd/MM/yyyy HH:mm")).arg(minutes);
        }
        if (!alerts.isEmpty())
        {
            showNotification("Event reminder", "Event in less than 3h:" + alerts.join("\n"));
        }
    }
}
