#ifndef GESTIONRECLAM_H
#define GESTIONRECLAM_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QDate>

// Reclamation Structure (Consider renaming to Claim)
struct Reclamation { // Consider renaming -> Claim
    QString id;
    QString clientId;
    QDate date;
    QString description;
    QString statut; // status
    QString importance;
    Reclamation() = default; // Use default constructor
};

namespace Ui {
class GestionReclamationDialog; // Refers to the UI class from .ui file (Consider renaming -> ClaimManagementDialog)
}

class GestionReclamationDialog : public QDialog // Consider renaming -> ClaimManagementDialog
{
    Q_OBJECT

public:
    explicit GestionReclamationDialog(QWidget *parent = nullptr);
    ~GestionReclamationDialog();

    // Modified to potentially store the client filter
    // Uses Reclamation struct (change to Claim if renamed)
    void setReclamationsData(const QList<Reclamation>& reclamations, const QString& filterClientId = "");


private slots:
    void onReclamationSelectionChanged(); // Consider renaming -> onClaimSelectionChanged
    // Slots automatically connected by name convention (defined in .ui file)
    void on_btnAjouter_clicked();    // Consider renaming button in .ui -> btnAdd -> on_btnAdd_clicked
    void on_btnModifier_clicked();   // Consider renaming button in .ui -> btnModify -> on_btnModify_clicked
    void on_btnSupprimer_clicked();  // Consider renaming button in .ui -> btnDelete -> on_btnDelete_clicked
    // --- ADDED ---
    void refreshReclamationsTable(); // Slot or private function to refresh (Consider renaming -> refreshClaimsTable)

private:
    Ui::GestionReclamationDialog *ui; // Pointer to UI elements
    QList<Reclamation> m_reclamationsList; // Stores the currently displayed list (Consider renaming -> m_claimsList, uses Claim struct if renamed)
    QString m_filterClientId = ""; // Stores the client ID if the view is filtered

    void populateTable(); // Populates the table from m_reclamationsList
    // refreshReclamationsTable can be private if only called internally
};

#endif // GESTIONRECLAM_H
