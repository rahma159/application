#ifndef CALENDRIERDIALOG_H
#define CALENDRIERDIALOG_H

#include <QDialog>
#include <QDate>
#include <QList>
#include <QListWidgetItem> // Include QListWidgetItem header
#include "rendezvous.h"    // Include Rendezvous class definition

namespace Ui
{
    class CalendrierDialog;
}

class CalendrierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendrierDialog(Rendezvous *rdvManager, QWidget *parent = nullptr); // Pass Rendezvous manager
    ~CalendrierDialog();
    void refreshAppointments(); // Public method to refresh

signals:
    void dataChanged(); // Signal emitted when data is modified

private slots:
    void on_calendarWidget_selectionChanged();
    void on_pushButton_AjouterCal_clicked();
    void on_pushButton_ModifierCal_clicked();
    void on_pushButton_SupprimerCal_clicked();
    void on_listWidget_Appointments_itemClicked(QListWidgetItem *item);

private:
    void loadAppointmentsForDate(const QDate &date);
    void highlightDatesWithAppointments();
    void clearInputFields();

    Ui::CalendrierDialog *ui;
    Rendezvous *m_rdvManager; // Pointer to the main Rendezvous object
    QDate m_selectedDate;
    int m_selectedRdvId; // To store the ID of the selected appointment in the list
};

#endif // CALENDRIERDIALOG_H
