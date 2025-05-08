#include "ajoutreclamationdialog.h"
#include "ui_ajoutreclamationdialog.h" // Includes the header generated from the .ui file
#include <QDate>
#include <QDebug> // Added for potential debugging

// Constructor for ADDING
AjoutReclamationDialog::AjoutReclamationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutReclamationDialog)
{
    ui->setupUi(this);
    initializeComboBoxes();
    ui->dateEditReclamation->setDate(QDate::currentDate());
    setWindowTitle("Add Claim"); // Translated title
    // Client ID is editable in add mode
    ui->lineEditClientId->setReadOnly(false);
    qDebug() << "Add/Edit Claim Dialog opened in ADD mode.";
}

// New Constructor for MODIFYING
AjoutReclamationDialog::AjoutReclamationDialog(const Reclamation& dataToEdit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutReclamationDialog)
{
    ui->setupUi(this);
    initializeComboBoxes();
    populateFields(dataToEdit); // Fill fields with existing data
    setWindowTitle("Modify Claim"); // Translated title
    m_editingId = dataToEdit.id; // Save the ID being edited
    // Make Client ID non-editable in edit mode (usually)
    ui->lineEditClientId->setReadOnly(true);
    ui->lineEditClientId->setStyleSheet("background-color: #eee;"); // Visual style for read-only
    qDebug() << "Add/Edit Claim Dialog opened in EDIT mode for ID:" << m_editingId;
}


AjoutReclamationDialog::~AjoutReclamationDialog()
{
    delete ui;
}

// Helper function to initialize ComboBoxes
void AjoutReclamationDialog::initializeComboBoxes() {
    // Importance
    ui->comboBoxImportance->clear();
    // Corrected "Meduim" to "Medium"
    ui->comboBoxImportance->addItems({"Weak", "Medium", "High", "Critical"}); // Use English terms if desired
    // Status
    ui->comboBoxStatut->clear();
    ui->comboBoxStatut->addItems({"Opened", "In Progress", "Resolved"}); // Use English terms if desired
}

// Helper function to fill fields (used by the edit constructor)
void AjoutReclamationDialog::populateFields(const Reclamation& data) { // Uses Claim struct if renamed
    ui->lineEditClientId->setText(data.clientId);
    ui->dateEditReclamation->setDate(data.date);
    ui->comboBoxImportance->setCurrentText(data.importance);
    ui->comboBoxStatut->setCurrentText(data.statut);
    ui->textEditDescription->setPlainText(data.description);
}


// Retrieve data entered by the user
Reclamation AjoutReclamationDialog::getReclamationData() const // Returns Claim struct if renamed
{
    Reclamation data; // Use Claim struct if renamed
    data.id = m_editingId; // Returns the original ID if editing, otherwise ""
    data.clientId = ui->lineEditClientId->text().trimmed();
    data.date = ui->dateEditReclamation->date();
    data.importance = ui->comboBoxImportance->currentText();
    data.statut = ui->comboBoxStatut->currentText();
    data.description = ui->textEditDescription->toPlainText().trimmed();
    return data;
}
