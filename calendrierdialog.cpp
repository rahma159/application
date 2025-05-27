#include "calendrierdialog.h"
#include "ui_calendrierdialog.h"
#include "rendezvous.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QTextCharFormat> // For highlighting dates
#include <QListWidgetItem>
#include <QSqlError> // Include QSqlError header

CalendrierDialog::CalendrierDialog(Rendezvous *rdvManager, QWidget *parent) : QDialog(parent),
                                                                              ui(new Ui::CalendrierDialog),
                                                                              m_rdvManager(rdvManager), // Store the pointer
                                                                              m_selectedRdvId(-1)       // Initialize selected ID
{
    ui->setupUi(this);
    this->setWindowTitle("Calendrier des Rendez-vous");

    // Set initial selected date and load appointments
    m_selectedDate = ui->calendarWidget->selectedDate();
    ui->label_SelectedDate->setText(m_selectedDate.toString("dd MMMM yyyy"));
    loadAppointmentsForDate(m_selectedDate);
    highlightDatesWithAppointments();

    // Connect calendar selection change
    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &CalendrierDialog::on_calendarWidget_selectionChanged);
}

CalendrierDialog::~CalendrierDialog()
{
    delete ui;
}

// Public method to refresh data (e.g., when dialog is shown)
void CalendrierDialog::refreshAppointments()
{
    highlightDatesWithAppointments();
    loadAppointmentsForDate(ui->calendarWidget->selectedDate()); // Reload for current date
}

// Slot for calendar date selection change
void CalendrierDialog::on_calendarWidget_selectionChanged()
{
    m_selectedDate = ui->calendarWidget->selectedDate();
    ui->label_SelectedDate->setText(m_selectedDate.toString("dd MMMM yyyy"));
    loadAppointmentsForDate(m_selectedDate);
    clearInputFields();   // Clear fields when date changes
    m_selectedRdvId = -1; // Reset selected ID
}

// Load appointments for the given date into the list widget
void CalendrierDialog::loadAppointmentsForDate(const QDate &date)
{
    ui->listWidget_Appointments->clear();
    QSqlQuery query;
    // Query appointments for the selected date
    query.prepare("SELECT ID_RDV, TO_CHAR(HEURE, 'HH24:MI') AS HEURE_STR, OBJET, STATUT, TYPE "
                  "FROM rendezvous WHERE TRUNC(DATERDV) = :date ORDER BY HEURE");
    query.bindValue(":date", date);

    if (query.exec())
    {
        while (query.next())
        {
            int id = query.value("ID_RDV").toInt();
            QString timeStr = query.value("HEURE_STR").toString();
            QString objet = query.value("OBJET").toString();
            QString statut = query.value("STATUT").toString();
            QString type = query.value("TYPE").toString();

            // Create a display string for the list item
            QString displayText = QString("%1 - %2 (%3, %4)")
                                      .arg(timeStr)
                                      .arg(objet)
                                      .arg(statut)
                                      .arg(type);

            QListWidgetItem *item = new QListWidgetItem(displayText);
            item->setData(Qt::UserRole, id); // Store the ID in the item's data
            ui->listWidget_Appointments->addItem(item);
        }
    }
    else
    {
        qDebug() << "Error loading appointments for date:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de charger les rendez-vous pour cette date.");
    }
}

// Highlight dates in the calendar that have appointments
void CalendrierDialog::highlightDatesWithAppointments()
{
    QSqlQuery query("SELECT DISTINCT TRUNC(DATERDV) FROM rendezvous");
    QTextCharFormat format;
    format.setBackground(Qt::yellow);  // Highlight with yellow background
    format.setFontWeight(QFont::Bold); // Make text bold

    if (query.exec())
    {
        while (query.next())
        {
            QDate date = query.value(0).toDate();
            ui->calendarWidget->setDateTextFormat(date, format);
        }
    }
    else
    {
        qDebug() << "Error fetching distinct appointment dates:" << query.lastError().text();
    }
    // Reset format for dates without appointments (optional, might be needed if appointments are deleted)
    // You might need a more sophisticated way to manage formats if removing highlights is required.
}

// Slot when an item in the appointment list is clicked
void CalendrierDialog::on_listWidget_Appointments_itemClicked(QListWidgetItem *item)
{
    m_selectedRdvId = item->data(Qt::UserRole).toInt(); // Get the stored ID

    // Fetch full details for the selected appointment to populate fields
    QSqlQuery query;
    query.prepare("SELECT HEURE, OBJET, STATUT, TYPE FROM rendezvous WHERE ID_RDV = :id");
    query.bindValue(":id", m_selectedRdvId);

    if (query.exec() && query.next())
    {
        // QDateTime heureDateTime = query.value("HEURE").toDateTime(); // Get as QDateTime
        // ui->timeEdit_HeureCal->setTime(heureDateTime.time()); // Set time
        // Handle potential conversion issues if HEURE is not directly convertible to QDateTime
        QTime heure = QTime::fromString(query.value("HEURE").toString(), Qt::ISODate); // Adjust format if needed
        if (!heure.isValid())
        {
            // Fallback or alternative parsing if HEURE is stored differently
            // For example, if it's just HH24:MI:SS
            heure = QTime::fromString(query.value("HEURE").toString(), "HH:mm:ss");
        }
        ui->timeEdit_HeureCal->setTime(heure);

        ui->lineEdit_ObjetCal->setText(query.value("OBJET").toString());
        ui->comboBox_StatutCal->setCurrentText(query.value("STATUT").toString()); // Assuming combo box has the text
        ui->comboBox_TypeCal->setCurrentText(query.value("TYPE").toString());     // <-- ici
        ui->lineEdit_IdCal->setText(QString::number(m_selectedRdvId));            // Show ID
        ui->lineEdit_IdCal->setReadOnly(true);                                    // Make ID read-only when modifying
    }
    else
    {
        qDebug() << "Error fetching details for RDV ID:" << m_selectedRdvId << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de charger les détails du rendez-vous.");
        clearInputFields();
        m_selectedRdvId = -1;
    }
}

// Clear input fields
void CalendrierDialog::clearInputFields()
{
    ui->lineEdit_IdCal->clear();
    ui->lineEdit_IdCal->setReadOnly(false);      // Allow editing ID for new entries
    ui->timeEdit_HeureCal->setTime(QTime(0, 0)); // Reset time
    ui->lineEdit_ObjetCal->clear();
    ui->comboBox_StatutCal->setCurrentIndex(0);    // Reset combo box
    ui->comboBox_TypeCal->setCurrentIndex(0);      // Reset type combo box
    m_selectedRdvId = -1;                          // Reset selected ID
    ui->listWidget_Appointments->clearSelection(); // Deselect item in list
}

// Slot for "Ajouter" button click
void CalendrierDialog::on_pushButton_AjouterCal_clicked()
{
    // Get data from fields
    int id = ui->lineEdit_IdCal->text().toInt(); // Get ID for new entry
    QTime heure = ui->timeEdit_HeureCal->time();
    QString objet = ui->lineEdit_ObjetCal->text();
    QString statut = ui->comboBox_StatutCal->currentText();
    QString type = ui->comboBox_TypeCal->currentText(); // <-- ici

    // Basic Validation
    if (id <= 0 || objet.isEmpty() || type.isEmpty())
    {
        QMessageBox::warning(this, "Erreur de saisie", "ID, Objet et Type sont requis. L'ID doit être positif.");
        return;
    }

    // Use the Rendezvous manager passed in the constructor
    m_rdvManager->setId(id);
    m_rdvManager->setDate(m_selectedDate); // Use the date selected in the calendar
    m_rdvManager->setHeure(heure);
    m_rdvManager->setObjet(objet);
    m_rdvManager->setStatut(statut);
    m_rdvManager->setType(type);

    if (m_rdvManager->ajouter())
    {
        QMessageBox::information(this, "Succès", "Rendez-vous ajouté avec succès.");
        loadAppointmentsForDate(m_selectedDate); // Refresh list for the current date
        highlightDatesWithAppointments();        // Re-highlight dates
        clearInputFields();
        emit dataChanged(); // Notify main window
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du rendez-vous. Vérifiez l'ID.");
    }
}

// Slot for "Modifier" button click
void CalendrierDialog::on_pushButton_ModifierCal_clicked()
{
    if (m_selectedRdvId <= 0)
    {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un rendez-vous dans la liste à modifier.");
        return;
    }

    // Get data from fields
    QTime heure = ui->timeEdit_HeureCal->time();
    QString objet = ui->lineEdit_ObjetCal->text();
    QString statut = ui->comboBox_StatutCal->currentText();
    QString type = ui->comboBox_TypeCal->currentText(); // <-- ici

    // Basic Validation
    if (objet.isEmpty() || type.isEmpty())
    {
        QMessageBox::warning(this, "Erreur de saisie", "Objet et Type sont requis.");
        return;
    }

    // Use the Rendezvous manager
    m_rdvManager->setId(m_selectedRdvId);  // Use the stored selected ID
    m_rdvManager->setDate(m_selectedDate); // Date might change if calendar selection changed, but usually modify on the same date
    m_rdvManager->setHeure(heure);
    m_rdvManager->setObjet(objet);
    m_rdvManager->setStatut(statut);
    m_rdvManager->setType(type);

    if (m_rdvManager->modifier())
    {
        QMessageBox::information(this, "Succès", "Appointment edited successfully");
        loadAppointmentsForDate(m_selectedDate); // Refresh list
        clearInputFields();
        emit dataChanged(); // Notify main window
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Failed to modify the event");
    }
}

// Slot for "Supprimer" button click
void CalendrierDialog::on_pushButton_SupprimerCal_clicked()
{
    if (m_selectedRdvId <= 0)
    {
        QMessageBox::warning(this, "Aucune sélection", "Veuillez sélectionner un rendez-vous dans la liste à supprimer.");
        return;
    }

    // Confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", QString("Êtes-vous sûr de vouloir supprimer le RDV ID %1?").arg(m_selectedRdvId),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        return;
    }

    // Use the Rendezvous manager
    if (m_rdvManager->supprimer(m_selectedRdvId))
    {
        QMessageBox::information(this, "Succès", "Event successfully deleted.");
        loadAppointmentsForDate(m_selectedDate); // Refresh list
        highlightDatesWithAppointments();        // Re-highlight dates (check if date still needs highlight)
        clearInputFields();
        emit dataChanged(); // Notify main window
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du rendez-vous.");
    }
}
