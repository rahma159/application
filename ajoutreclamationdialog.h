#ifndef AJOUTRECLAMATIONDIALOG_H
#define AJOUTRECLAMATIONDIALOG_H

#include <QDialog>
#include "gestionreclam.h" // For the Reclamation structure (Consider renaming gestionreclam.h -> claimmanagementdialog.h)

namespace Ui {
class AjoutReclamationDialog; // Consider renaming the .ui file and this class -> AddEditClaimDialog
}

class AjoutReclamationDialog : public QDialog // Consider renaming -> AddEditClaimDialog
{
    Q_OBJECT

public:
    // Constructor for adding (unchanged)
    explicit AjoutReclamationDialog(QWidget *parent = nullptr);
    // Constructor for modifying
    explicit AjoutReclamationDialog(const Reclamation& dataToEdit, QWidget *parent = nullptr); // Pass Claim struct if renamed
    ~AjoutReclamationDialog();

    // Function to retrieve data (unchanged)
    Reclamation getReclamationData() const; // Returns Claim struct if renamed

private:
    Ui::AjoutReclamationDialog *ui; // Refers to the UI class from the .ui file
    QString m_editingId = ""; // Stores the ID if in edit mode

    void initializeComboBoxes(); // Helper function to initialize combos
    void populateFields(const Reclamation& data); // Helper function to fill fields (Uses Claim struct if renamed)
};

#endif // AJOUTRECLAMATIONDIALOG_H
