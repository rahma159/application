/////////////////////////////////////////////////////////////////////////////
// createditinvoicedialog.cpp - Intégrant les corrections pour QDateTime/QDate
/////////////////////////////////////////////////////////////////////////////

#include "createeditinvoicedialog.h"
#include "ui_createeditinvoicedialog.h"
#include "invoices.h"          // Inclut la classe Invoices (avec due_date en QDateTime)
#include "invoicelineitem.h"   // Inclut la classe InvoiceLineItem

// Standard C++ and Qt Includes
#include <cmath>
#include <algorithm>
#include <vector>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLocale>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVariant>
#include <QDateTime> // <-- NÉCESSAIRE pour QDateTime
#include <QTime>

#include <limits>
// --- Constructor ---
// Assurez-vous que le constructeur de Invoices dans invoices.cpp gère correctement
// l'initialisation de due_date (QDateTime) depuis un paramètre QDate si nécessaire.
CreateEditInvoiceDialog::CreateEditInvoiceDialog(QDialog *parent) : // Utiliser QDialog* comme type de parent standard pour QDialog
    QDialog(parent),
    ui(new Ui::CreateEditInvoiceDialog),
    currentInvoiceId(-1)
{
    qDebug() << "CreateEditInvoiceDialog CONSTRUCTOR";
    ui->setupUi(this);
    setupLineItemsTable();
    populateClientComboBox();
    setupConnections();
    prepareForNewInvoice(); // Initialise l'interface pour une nouvelle facture
    ui->dueDateEdit->setCalendarPopup(true);
}

// --- Destructor ---
CreateEditInvoiceDialog::~CreateEditInvoiceDialog()
{
    qDebug() << "CreateEditInvoiceDialog DESTRUCTOR";
    delete ui;
}

// --- Public Methods ---

// --- prepareForNewInvoice ---
// Initialise les champs de l'UI pour une nouvelle facture.
void CreateEditInvoiceDialog::prepareForNewInvoice() {
    qDebug() << "prepareForNewInvoice() called";
    currentInvoiceId = -1; // Pas d'ID pour une nouvelle facture
    setWindowTitle(tr("Create New Invoice"));
    ui->invoiceNumberLineEdit->clear();
    ui->clientSelectComboBox->setCurrentIndex(0); // Sélectionner "-- Select Client --"
    if (ui->clientDetailsTextEdit) ui->clientDetailsTextEdit->clear();
    ui->issueDateEdit->setDate(QDate::currentDate()); // Date d'émission par défaut
    // Initialiser dueDateEdit (supposé être un QDateEdit)
    // Mettre une date d'échéance par défaut, par ex. +30 jours
    QDateTime defaultDueDateTime = QDateTime::currentDateTime().addDays(30);
    ui->dueDateEdit->setDateTime(defaultDueDateTime);

    ui->paymentTermsLineEdit->clear();
    ui->notesTextEdit->clear();
    ui->lineItemsTableWidget->setRowCount(0); // Vider le tableau des lignes
    calculateAndDisplayTotals(); // Mettre les totaux à zéro
    // updateDueDate(); // Pas nécessaire ici si on initialise déjà dueDateEdit
    ui->invoiceNumberLineEdit->setFocus();
}

// --- loadInvoiceForEditing ---
// Charge les données d'une facture existante dans l'UI.
// ATTENTION: Dépend de l'implémentation de Invoices::loadById dans invoices.cpp.
bool CreateEditInvoiceDialog::loadInvoiceForEditing(int invoiceId) {
    qDebug() << "loadInvoiceForEditing() called for ID:" << invoiceId;
    if (invoiceId <= 0) {
        qWarning() << "Invalid invoice ID passed to loadInvoiceForEditing:" << invoiceId;
        prepareForNewInvoice();
        return false;
    }

    qWarning() << "Note: loadInvoiceForEditing relies on a potentially simplified Invoices::loadById implementation.";

    QSqlDatabase db = QSqlDatabase::database(); // Récupérer la connexion par défaut
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Cannot load invoice: Database connection is not open."));
        prepareForNewInvoice();
        return false;
    }

    bool loadOk = false;
    // Appel à la méthode statique (supposée) pour charger la facture
    Invoices loadedInvoice = Invoices::loadById(invoiceId, db, &loadOk);

    if (loadOk) {
        populateUiFromInvoice(loadedInvoice); // Remplir l'UI avec les données chargées
        currentInvoiceId = invoiceId; // Stocker l'ID de la facture en cours d'édition
        setWindowTitle(tr("Edit Invoice %1").arg(loadedInvoice.getInvoiceNumber()));
        qDebug() << "Invoice loaded successfully (line items might be missing if loadById is simplified).";
        return true;
    } else {
        QSqlError error = loadedInvoice.lastDbError(); // Récupérer l'erreur depuis l'objet (si loadById la définit)
        qDebug() << "Failed to load invoice ID" << invoiceId << "Error:" << error.text();
        QMessageBox::critical(this, tr("Load Error"), tr("Failed to load invoice data for ID %1.\n%2")
                                                          .arg(invoiceId)
                                                          .arg(error.text()));
        prepareForNewInvoice(); // Réinitialiser l'UI en cas d'échec
        return false;
    }
}


// --- Private Helper Methods ---

// --- setupConnections ---
// Connecte les signaux des widgets UI aux slots de ce dialogue.
void CreateEditInvoiceDialog::setupConnections() {
    qDebug() << "CreateEditInvoiceDialog::setupConnections CALLED";
   /* connect(ui->saveDraftButton, &QPushButton::clicked, this, &CreateEditInvoiceDialog::on_saveDraftButton_clicked);
    connect(ui->saveAndSendButton, &QPushButton::clicked, this, &CreateEditInvoiceDialog::on_saveAndSendButton_clicked);
    connect(ui->removeLineItemButton, &QPushButton::clicked, this, &CreateEditInvoiceDialog::on_removeLineItemButton_clicked);*/
    connect(ui->clientSelectComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CreateEditInvoiceDialog::on_clientSelectComboBox_currentIndexChanged);
    connect(ui->issueDateEdit, &QDateEdit::dateChanged, this, &CreateEditInvoiceDialog::on_issueDateEdit_dateChanged);
    connect(ui->dueDateEdit, &QDateTimeEdit::dateTimeChanged, this, &CreateEditInvoiceDialog::on_dueDateEdit_dateTimeChanged);
    connect(ui->paymentTermsLineEdit, &QLineEdit::textChanged, this, &CreateEditInvoiceDialog::on_paymentTermsLineEdit_textChanged);
    // Connecter la modification des cellules importantes pour recalculer les totaux
    connect(ui->lineItemsTableWidget, &QTableWidget::cellChanged, this, &CreateEditInvoiceDialog::on_lineItemsTableWidget_cellChanged);
    // Connecter les boutons Annuler et Aperçu (si implémentés)
    connect(ui->cancelInvoiceButton, &QPushButton::clicked, this, &CreateEditInvoiceDialog::reject); // Ferme le dialogue sans succès
    connect(ui->previewButton, &QPushButton::clicked, this, &CreateEditInvoiceDialog::on_previewButton_clicked);
}

// --- setupLineItemsTable ---
// Configure l'apparence initiale du tableau des lignes de facture.
void CreateEditInvoiceDialog::setupLineItemsTable() {
    ui->lineItemsTableWidget->setColumnCount(5); // Description, Quantité, Prix Unit., TVA%, Total
    QStringList headers = {tr("Description"), tr("Quantity"), tr("Unit Price"), tr("VAT%"), tr("Total")};
    ui->lineItemsTableWidget->setHorizontalHeaderLabels(headers);
    // Ajuster les largeurs de colonnes
    ui->lineItemsTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch); // Description prend l'espace restant
    ui->lineItemsTableWidget->setColumnWidth(1, 100);  // Quantité
    ui->lineItemsTableWidget->setColumnWidth(2, 120); // Prix Unit.
    ui->lineItemsTableWidget->setColumnWidth(3, 80);  // TVA%
    ui->lineItemsTableWidget->setColumnWidth(4, 120); // Total Ligne
    // Autres configurations possibles : alignement, etc.
}

// --- populateClientComboBox ---
// Remplit la liste déroulante des clients depuis la base de données.
void CreateEditInvoiceDialog::populateClientComboBox() {
    qDebug() << "Populating client combo box...";
    ui->clientSelectComboBox->clear();
    ui->clientSelectComboBox->addItem(tr("-- Select Client --"), -1); // Item par défaut

    QSqlQuery query; // Utilise la connexion par défaut
    if (query.exec("SELECT CLIENT_ID, CLIENT_NAME FROM CLIENTS ORDER BY CLIENT_NAME")) {
        while (query.next()) {
            // Ajoute le nom du client (texte affiché) et l'ID du client (donnée cachée)
            ui->clientSelectComboBox->addItem(query.value("CLIENT_NAME").toString(),
                                              query.value("CLIENT_ID").toInt());
        }
        qDebug() << ui->clientSelectComboBox->count() -1 << "clients loaded into combo box.";
    } else {
        QMessageBox::critical(this, tr("Database Query Error"), tr("Failed to load client list:\n%1").arg(query.lastError().text()));
        qDebug() << "Client query failed:" << query.lastError();
    }
}

// --- displayClientDetails ---
// Affiche les détails du client sélectionné dans la zone de texte.
void CreateEditInvoiceDialog::displayClientDetails(int clientId) {
    if (!ui->clientDetailsTextEdit) return; // Vérifier si le widget existe

    if (clientId <= 0) {
        ui->clientDetailsTextEdit->clear(); // Effacer si aucun client n'est sélectionné
        return;
    }

    QSqlQuery query; // Utilise la connexion par défaut
    query.prepare("SELECT ADDRESS, EMAIL, VAT_ID FROM CLIENTS WHERE CLIENT_ID = :id");
    query.bindValue(":id", clientId);
    if (query.exec() && query.next()) {
        // Formatage simple des détails
        QString details = tr("Address: %1\nEmail: %2\nVAT ID: %3")
                              .arg(query.value("ADDRESS").toString())
                              .arg(query.value("EMAIL").toString())
                              .arg(query.value("VAT_ID").toString());
        ui->clientDetailsTextEdit->setText(details);
    } else {
        ui->clientDetailsTextEdit->setText(tr("Client details not found."));
        qDebug() << "Failed query client details. ID:" << clientId << "Err:" << query.lastError().text();
    }
}

// --- calculateAndDisplayTotals ---
// Calcule les totaux (sous-total, TVA, total général) à partir du tableau UI et met à jour les labels.
void CreateEditInvoiceDialog::calculateAndDisplayTotals() {
    // ... (Keep existing implementation - it only reads from UI table) ...
    // This function remains necessary to update the display labels.
    double runningSubtotal = 0.0;
    double runningVatTotal = 0.0;
    QLocale locale = QLocale::system();
    ui->lineItemsTableWidget->blockSignals(true);
    for (int row = 0; row < ui->lineItemsTableWidget->rowCount(); row++) {
        QTableWidgetItem* qtyItem = ui->lineItemsTableWidget->item(row, 1);
        QTableWidgetItem* priceItem = ui->lineItemsTableWidget->item(row, 2);
        QTableWidgetItem* vatItem = ui->lineItemsTableWidget->item(row, 3);
        QTableWidgetItem* totalItem = ui->lineItemsTableWidget->item(row, 4);
        bool okQty = false, okPrice = false, okVat = false;
        double qty = qtyItem ? locale.toDouble(qtyItem->text(), &okQty) : 0.0;
        double price = priceItem ? locale.toDouble(priceItem->text(), &okPrice) : 0.0;
        double vatPercent = vatItem ? locale.toDouble(vatItem->text(), &okVat) : 0.0;
        double lineSubtotal = 0.0;
        double lineVatAmount = 0.0;
        double lineTotal = 0.0;
        if (okQty && okPrice) {
            lineSubtotal = qty * price;
            if (okVat && vatPercent > 0) { lineVatAmount = lineSubtotal * (vatPercent / 100.0); }
            lineTotal = lineSubtotal + lineVatAmount;
        }
        runningSubtotal += lineSubtotal;
        runningVatTotal += lineVatAmount;
        if (!totalItem) {
            totalItem = new QTableWidgetItem();
            totalItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
            ui->lineItemsTableWidget->setItem(row, 4, totalItem);
        }
        totalItem->setText(locale.toString(lineTotal, 'f', 2));
    }
    ui->lineItemsTableWidget->blockSignals(false);
    double grandTotal = runningSubtotal + runningVatTotal;
    QString currencySymbol = locale.currencySymbol();
    ui->subtotalValueLabel->setText(currencySymbol + locale.toString(runningSubtotal, 'f', 2));
    ui->totalVatValueLabel->setText(currencySymbol + locale.toString(runningVatTotal, 'f', 2));
    ui->grandTotalValueLabel->setText(currencySymbol + locale.toString(grandTotal, 'f', 2));
}
// --- updateDueDate ---
// Met à jour la date d'échéance en fonction de la date d'émission et des termes de paiement.
void CreateEditInvoiceDialog::updateDueDate() {
    QDate issueDate = ui->issueDateEdit->date();
    QString terms = ui->paymentTermsLineEdit->text().trimmed().toLower();
    QTime currentTimePart = ui->dueDateEdit->time(); // <<< Get the current time from the widget

    QDate newDueDatePart = issueDate; // Start with issue date

    // Calculate the new date part based on terms
    if (terms.contains("net 30") || terms.contains("30 days")) {
        newDueDatePart = issueDate.addDays(30);
    } else if (terms.contains("net 15") || terms.contains("15 days")) {
        newDueDatePart = issueDate.addDays(15);
    } else if (terms.contains("net 60") || terms.contains("60 days")) {
        newDueDatePart = issueDate.addDays(60);
    }
    // ... other terms ...

    // Combine the newly calculated date part with the preserved time part
    QDateTime newDueDateTime(newDueDatePart, currentTimePart);

    // Update the QDateTimeEdit widget
    ui->dueDateEdit->setDateTime(newDueDateTime);
}

// --- populateUiFromInvoice ---
// Remplit les champs de l'UI à partir d'un objet Invoices chargé.
void CreateEditInvoiceDialog::populateUiFromInvoice(const Invoices& invoice) {
    qDebug() << "populateUiFromInvoice called for Invoice ID:" << invoice.getInvoiceId();

    // Remplir les champs de l'en-tête
    ui->invoiceNumberLineEdit->setText(invoice.getInvoiceNumber());
    // Trouver et sélectionner le client dans la ComboBox
    int clientIndex = ui->clientSelectComboBox->findData(invoice.getClientId());
    ui->clientSelectComboBox->setCurrentIndex(clientIndex >= 0 ? clientIndex : 0);
    // Afficher les détails du client sélectionné (lance l'appel à displayClientDetails via le signal)
    // displayClientDetails(invoice.getClientId()); // Normalement pas nécessaire si setCurrentIndex émet le signal

    ui->issueDateEdit->setDate(invoice.getIssueDate().date());
    ui->paymentTermsLineEdit->setText(invoice.getPaymentTerms());
    ui->notesTextEdit->setPlainText(invoice.getNotes());


    ui->dueDateEdit->setDateTime(invoice.getDueDate());
    // Remplir le tableau des lignes de facture
    ui->lineItemsTableWidget->setRowCount(0); // Vider le tableau avant de remplir
    const QList<InvoiceLineItem>& items = invoice.getLineItems();
    qDebug() << "Number of line items received from loaded invoice:" << items.count();

    // Bloquer les signaux pendant le remplissage pour la performance
    bool signalsBlocked = ui->lineItemsTableWidget->signalsBlocked();
    ui->lineItemsTableWidget->blockSignals(true);
    QLocale locale = this->locale(); // Utiliser la locale pour le formatage

    for (const auto& item : items) {
        int row = ui->lineItemsTableWidget->rowCount();
        ui->lineItemsTableWidget->insertRow(row);

        // Remplir les cellules avec les données de l'item
        ui->lineItemsTableWidget->setItem(row, 0, new QTableWidgetItem(item.getDescription()));
        // Formater les nombres selon la locale
        ui->lineItemsTableWidget->setItem(row, 1, new QTableWidgetItem(locale.toString(item.getQuantity(), 'f', 2)));
        ui->lineItemsTableWidget->setItem(row, 2, new QTableWidgetItem(locale.toString(item.getUnitPrice(), 'f', 2)));
        // Note: VAT% n'est pas stocké dans InvoiceLineItem dans cet exemple, mettre 0 ?
        ui->lineItemsTableWidget->setItem(row, 3, new QTableWidgetItem(locale.toString(0.0, 'f', 1))); // Mettre à 0 ou lire si stocké

        // Créer et formater la cellule du total (non éditable)
        QTableWidgetItem *totalItem = new QTableWidgetItem();
        totalItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable); // Non éditable
        // totalItem->setText(locale.toString(item.getAmount(), 'f', 2)); // Utiliser item.getAmount() si disponible
        ui->lineItemsTableWidget->setItem(row, 4, totalItem); // Le total sera recalculé ci-dessous
    }

    ui->lineItemsTableWidget->blockSignals(signalsBlocked); // Restaurer les signaux

    // Recalculer et afficher tous les totaux après avoir rempli le tableau
    calculateAndDisplayTotals();
    qDebug() << "Finished populating UI from invoice.";
}

// --- populateInvoiceObjectFromUi ---
// Récupère les données depuis l'UI et remplit les objets C++ Invoices et InvoiceLineItem.
void CreateEditInvoiceDialog::populateInvoiceObjectFromUi(Invoices& invoiceToPopulate, QList<InvoiceLineItem>& itemsToPopulate) {
    qDebug() << "Running populateInvoiceObjectFromUi...";
    QLocale locale = this->locale();

    // Remplir l'objet Invoices (en-tête)
    invoiceToPopulate.setInvoiceNumber(ui->invoiceNumberLineEdit->text().trimmed());
    invoiceToPopulate.setClientId(ui->clientSelectComboBox->currentData().toInt());
    invoiceToPopulate.setClientName(ui->clientSelectComboBox->currentText());
    invoiceToPopulate.setIssueDate(ui->issueDateEdit->dateTime()); // IssueDate est QDate

    invoiceToPopulate.setDueDate(ui->dueDateEdit->dateTime());

    invoiceToPopulate.setPaymentTerms(ui->paymentTermsLineEdit->text().trimmed());
    invoiceToPopulate.setNotes(ui->notesTextEdit->toPlainText().trimmed());

    // Recalculer pour s'assurer que les labels sont à jour avant lecture
    calculateAndDisplayTotals();

    // Lire les totaux depuis les labels (avec gestion des erreurs de conversion)
    bool okSub, okTax, okTotal;
    QString subTextRaw = ui->subtotalValueLabel->text();
    QString taxTextRaw = ui->totalVatValueLabel->text();
    QString totalTextRaw = ui->grandTotalValueLabel->text();
    // Nettoyer les chaînes (enlever symbole monétaire, séparateur de milliers)
    QString subClean = subTextRaw; subClean.remove(locale.currencySymbol()).remove(locale.groupSeparator());
    QString taxClean = taxTextRaw; taxClean.remove(locale.currencySymbol()).remove(locale.groupSeparator());
    QString totalClean = totalTextRaw; totalClean.remove(locale.currencySymbol()).remove(locale.groupSeparator());
    // Convertir en double
    double subtotal = locale.toDouble(subClean, &okSub);
    double taxAmount = locale.toDouble(taxClean, &okTax);
    double totalAmount = locale.toDouble(totalClean, &okTotal);
    // Vérifier les conversions et mettre à 0 si invalide
    if (!okSub || std::isnan(subtotal) || std::isinf(subtotal)) { subtotal = 0.0; qWarning("Subtotal conversion failed!"); }
    if (!okTax || std::isnan(taxAmount) || std::isinf(taxAmount)) { taxAmount = 0.0; qWarning("Tax amount conversion failed!"); }
    if (!okTotal || std::isnan(totalAmount) || std::isinf(totalAmount)){ totalAmount = 0.0; qWarning("Total amount conversion failed!"); }
    invoiceToPopulate.setSubtotal(subtotal);
    invoiceToPopulate.setTaxAmount(taxAmount);
    invoiceToPopulate.setTotalAmount(totalAmount);

    // Remplir la liste des InvoiceLineItem depuis le tableau UI
    itemsToPopulate.clear(); // Vider la liste existante
    double calculatedSubtotal = 0.0;
    // double calculatedTax = 0.0; // Add if you store/calculate tax per line

    for (int row = 0; row < ui->lineItemsTableWidget->rowCount(); ++row) {
        InvoiceLineItem lineItem;
        bool rowIsValid = true; // Flag pour savoir si la ligne est valide

        // Lire la description
        QTableWidgetItem* descItem = ui->lineItemsTableWidget->item(row, 0);
        QString description;
        if (descItem && !descItem->text().trimmed().isEmpty()) {
            description = descItem->text().trimmed();
            lineItem.setDescription(description);
        } else {
            rowIsValid = false; // Description obligatoire
        }

        // Lire la quantité
        QTableWidgetItem* qtyItem = ui->lineItemsTableWidget->item(row, 1);
        double quantity = 0.0; bool okQty = false;
        if (qtyItem && rowIsValid) {
            QString qtyClean = qtyItem->text().trimmed(); // Trim whitespace
            qtyClean.remove(locale.groupSeparator());    // Remove group sep
            // Replace decimal sep if needed? Usually locale.toDouble handles this.
            quantity = locale.toDouble(qtyClean, &okQty);
            if (!okQty || std::isnan(quantity) || std::isinf(quantity) || quantity <= 0) {
                qWarning() << "Invalid quantity at row" << row << ":" << (qtyItem ? qtyItem->text() : "<null>");
                rowIsValid = false;
            }
        } else if (rowIsValid) { rowIsValid = false; }

        // Lire le prix unitaire
        QTableWidgetItem* priceItem = ui->lineItemsTableWidget->item(row, 2);
        double unitPrice = 0.0; bool okPrice = false;
        if (priceItem && rowIsValid) {
            QString priceClean = priceItem->text().trimmed(); // Trim whitespace
            priceClean.remove(locale.currencySymbol());       // Remove currency symbol
            priceClean.remove(locale.groupSeparator());       // Remove group sep
            unitPrice = locale.toDouble(priceClean, &okPrice);
            if (!okPrice || std::isnan(unitPrice) || std::isinf(unitPrice) || unitPrice < 0) {
                qWarning() << "Invalid unit price at row" << row << ":" << (priceItem ? priceItem->text() : "<null>");
                rowIsValid = false;
            }
        } else if (rowIsValid) { rowIsValid = false; }

        // Si toutes les données lues sont valides, configurer et ajouter l'item
        if (rowIsValid) {
            lineItem.setQuantity(quantity);
            lineItem.setUnitPrice(unitPrice);
            double lineAmount = quantity * unitPrice; // Simple amount calculation
            // double lineTax = lineAmount * (vatPercent / 100.0); // If using VAT per line
            lineItem.setAmount(lineAmount); // Use the calculated amount
            itemsToPopulate.append(lineItem);

            // Accumulate totals *directly* from validated numbers
            calculatedSubtotal += lineAmount;
            // calculatedTax += lineTax; // If using VAT per line
        } else {
            qWarning() << "Skipping invalid line item data at row:" << row;
        }
    }
    qDebug() << "Finished collecting line items. Valid count:" << itemsToPopulate.count();
    qDebug() << "Calculated Subtotal directly:" << calculatedSubtotal;
}

// --- saveInvoice ---
// Fonction principale pour sauvegarder (nouvelle ou existante) la facture.
#include <QMessageBox> // Ensure QMessageBox is included
#include <QString>
#include <QSqlError>
#include <QDebug>
#include "invoices.h" // Assuming your class definitions are here
#include "invoicelineitem.h" // Assuming your class definitions are here
#include "ui_createeditinvoicedialog.h" // Assuming Qt UI class

// ... (rest of your includes and class definition) ...

void CreateEditInvoiceDialog::saveInvoice(const QString& status) {
    qDebug() << "==== saveInvoice FUNCTION ENTERED (Status: " << status << ") ====";

    // 1. Validation (Keep your existing validation)
    if ((ui->clientSelectComboBox->currentData().toInt() <= 0) || (ui->invoiceNumberLineEdit->text().trimmed().isEmpty()) || ((ui->lineItemsTableWidget->rowCount() == 0))) {
        // Use tr() for translatable strings in UI messages
        QMessageBox::warning(this, tr("Validation Error"), tr("Please select a valid client, enter an invoice number, and add at least one line item."));
        return;
    }

    // 2. Prepare data objects
    calculateAndDisplayTotals();
    Invoices invoiceToSave;
    QList<InvoiceLineItem> lineItemsToSave;
    populateInvoiceObjectFromUi(invoiceToSave, lineItemsToSave);
    invoiceToSave.setLineItems(lineItemsToSave);
    invoiceToSave.setStatus(status);

    qDebug() << "[saveInvoice] Prepared Invoice Object: ID=" << invoiceToSave.getInvoiceId() // Will be -1 if new
             << " Number=" << invoiceToSave.getInvoiceNumber() << " ClientID=" << invoiceToSave.getClientId()
             << " Status=" << invoiceToSave.getStatus() << " Total=" << invoiceToSave.getTotalAmount()
             << " LineItems=" << invoiceToSave.getLineItems().count();

    // 3. Execute Save or Update
    bool success = false;
    bool isUpdateOperation = (currentInvoiceId > 0); // <--- Determine context HERE

    if (!isUpdateOperation) { // It's a NEW invoice
        qDebug() << "Calling Invoices::save() for new invoice header and lines...";
        success = invoiceToSave.save(); // save() handles header and lines
        if (success) {
            qDebug() << "Invoice::save() successful. New Invoice ID:" << invoiceToSave.getInvoiceId();
            currentInvoiceId = invoiceToSave.getInvoiceId(); // Update current ID
        }
    } else { // It's an UPDATE
        qDebug() << "Calling Invoices::update() for existing Invoice ID:" << currentInvoiceId;
        invoiceToSave.setInvoiceId(currentInvoiceId); // Set ID for update
        success = invoiceToSave.update(); // update() handles header and lines sync
        if (success) {
            qDebug() << "Invoice::update() successful for Invoice ID:" << currentInvoiceId;
            // No need to update currentInvoiceId, it's already correct
        }
    }

    // 5. Handle the result (SUCCESS or FAILURE)
    if (success) {
        // --- MODIFIED SUCCESS MESSAGE ---
        QString successMessage;
        if (isUpdateOperation) {
            successMessage = QString(tr("Invoice (ID: %1) successfully updated with status '%2'." ))
            .arg(currentInvoiceId) // Use the known ID for update
                .arg(status);
        } else {
            successMessage = QString(tr("Invoice (ID: %1) successfully saved with status '%2'." ))
            .arg(invoiceToSave.getInvoiceId()) // Use the new ID from save()
                .arg(status);
        }
        QMessageBox::information(this, tr("Success"), successMessage);
        // --- END OF MODIFICATION ---

        accept(); // Close dialog on success

    } else {
        // Error handling
        QSqlError error = invoiceToSave.lastDbError();
        qWarning() << "Invoice " << (isUpdateOperation ? "update" : "save") << " failed. DB Error:" << error.databaseText() << "| Driver Error:" << error.driverText();

        // --- MODIFIED ERROR MESSAGE (Optional but good) ---
        QMessageBox::critical(this, tr("Operation Failed"), // Changed title slightly
                              tr("Could not %1 the invoice.\n\nError: %2")
                                  .arg(isUpdateOperation ? tr("update") : tr("save")) // Use correct verb
                                  .arg(error.text()));
        // --- END OF MODIFICATION ---
        // Do not close dialog on failure
    }
    qDebug() << "==== saveInvoice FUNCTION EXITING ====";
}

// You also need the implementations for:
// void CreateEditInvoiceDialog::calculateAndDisplayTotals();
// void CreateEditInvoiceDialog::populateInvoiceObjectFromUi(Invoices& invoice, QList<InvoiceLineItem>& items);
// Assuming these exist elsewhere in your code.

// --- SLOTS IMPLEMENTATIONS ---

// --- Slot pour le bouton "Save Draft" ---
void CreateEditInvoiceDialog::on_saveDraftButton_clicked() {
    qDebug() << "++++ on_saveDraftButton_clicked SLOT ENTERED ++++";
    // Le statut "unpaid" est souvent utilisé pour les brouillons ou factures envoyées non payées.
    // Choisissez le statut qui convient le mieux à votre logique métier pour un brouillon.
    saveInvoice("draft"); // ou "draft" si vous utilisez ce statut
}

// --- Slot pour le bouton "Save and Send" ---
void CreateEditInvoiceDialog::on_saveAndSendButton_clicked() {
    qDebug() << "++++ on_saveAndSendButton_clicked SLOT ENTERED ++++";
    // Le statut "sent" indique généralement que la facture a été finalisée et envoyée.
    saveInvoice("sent");
}

// --- Slot pour ajouter une ligne ---
// Modifie uniquement l'UI, n'interagit pas avec la base de données ici.
void CreateEditInvoiceDialog::on_addLineItemButton_clicked() {
    int row = ui->lineItemsTableWidget->rowCount(); // Récupère le nombre actuel de lignes
    ui->lineItemsTableWidget->insertRow(row);      // <<< Insère UNE SEULE nouvelle ligne à la fin

    // --- Ajoute les items par défaut à cette nouvelle ligne ---
    QLocale locale = this->locale();
    ui->lineItemsTableWidget->setItem(row, 0, new QTableWidgetItem("")); // Description vide
    ui->lineItemsTableWidget->setItem(row, 1, new QTableWidgetItem(locale.toString(1.0, 'f', 2))); // Qté 1
    ui->lineItemsTableWidget->setItem(row, 2, new QTableWidgetItem(locale.toString(0.0, 'f', 2))); // Prix 0
    ui->lineItemsTableWidget->setItem(row, 3, new QTableWidgetItem(locale.toString(0.0, 'f', 1))); // TVA 0
    // Total (non éditable)
    QTableWidgetItem *totalItem = new QTableWidgetItem(locale.toString(0.0, 'f', 2));
    totalItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    totalItem->setFlags(totalItem->flags() & ~Qt::ItemIsEditable);
    ui->lineItemsTableWidget->setItem(row, 4, totalItem);
    // --- Fin de l'ajout des items ---

    ui->lineItemsTableWidget->scrollToBottom(); // Faire défiler
    ui->lineItemsTableWidget->editItem(ui->lineItemsTableWidget->item(row, 0)); // Focus sur description
}

// --- Slot pour supprimer une ligne ---
// Modifie uniquement l'UI.
void CreateEditInvoiceDialog::on_removeLineItemButton_clicked() {
    QList<QTableWidgetItem*> selectedItems = ui->lineItemsTableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, tr("Remove Item"), tr("Please select a line item (or part of a row) to remove."));
        return;
    }

    // Récupérer les indices des lignes à supprimer (sans doublons)
    QList<int> rowsToRemoveList;
    for(QTableWidgetItem* item : selectedItems) {
        if (!rowsToRemoveList.contains(item->row())) {
            rowsToRemoveList.append(item->row());
        }
    }
    // Trier en ordre décroissant pour éviter les problèmes d'indices lors de la suppression
    std::sort(rowsToRemoveList.begin(), rowsToRemoveList.end(), std::greater<int>());

    // Supprimer les lignes
    for (int row : rowsToRemoveList) {
        ui->lineItemsTableWidget->removeRow(row);
    }

    // Recalculer les totaux après suppression
    calculateAndDisplayTotals();
}

// --- Slot pour l'aperçu ---
void CreateEditInvoiceDialog::on_previewButton_clicked() {
    // Implémentation future : Générer un aperçu PDF ou autre
    QMessageBox::information(this, tr("Preview"), tr("Preview functionality is not yet implemented."));
}

// --- Slot appelé quand le client change ---
void CreateEditInvoiceDialog::on_clientSelectComboBox_currentIndexChanged(int index) {
    Q_UNUSED(index); // On n'utilise pas l'index directement ici
    // Récupérer l'ID client depuis les données associées à l'item sélectionné
    displayClientDetails(ui->clientSelectComboBox->currentData().toInt());
}

// --- Slot appelé quand la date d'émission change ---
void CreateEditInvoiceDialog::on_issueDateEdit_dateChanged(const QDate &date) {
    Q_UNUSED(date); // Le paramètre 'date' n'est pas utilisé directement
    updateDueDate(); // Recalculer la date d'échéance
}

// --- Slot appelé quand les termes de paiement changent ---
void CreateEditInvoiceDialog::on_paymentTermsLineEdit_textChanged(const QString &arg1) {
    Q_UNUSED(arg1); // Le paramètre 'arg1' n'est pas utilisé directement
    updateDueDate(); // Recalculer la date d'échéance
}

// --- Slot appelé quand une cellule du tableau des lignes change ---
void CreateEditInvoiceDialog::on_lineItemsTableWidget_cellChanged(int row, int column) {
    // === CORRECTION pour unused parameter ===
    Q_UNUSED(row); // Marquer 'row' comme inutilisé si on ne s'en sert pas

    // Recalculer les totaux si Quantité (1), Prix Unit. (2), ou TVA% (3) changent
    if (column == 1 || column == 2 || column == 3 ) {
        calculateAndDisplayTotals();
    }
}
void CreateEditInvoiceDialog::on_dueDateEdit_dateTimeChanged(const QDateTime &dateTime)
{
    Q_UNUSED(dateTime);
    qDebug() << "Due date/time changed in UI to:" << ui->dueDateEdit->dateTime();
    // You could potentially add validation here if needed
    // Or trigger other UI updates if the specific time matters for display elsewhere
}
