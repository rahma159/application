#pragma once

#include <QWidget>
#include <QMap>
#include <QDate>
#include <QStringList>
#include <QModelIndex>
#include <QList> // <<< ADDED: For the list of claims
#include "gestionreclam.h" // <<< ADDED: For the Reclamation structure (Consider renaming gestionreclam.h/cpp to e.g., claimmanagement.h/cpp)

// Forward declarations
class QTableWidgetItem;
namespace Ui { class ClientManager; } // Refers to the UI class generated from clientmanager.ui

// Client Structure
struct ClientData  {
    QString lastName;       // Renamed from nom
    QString firstName;      // Renamed from prenom
    QString domain;         // Renamed from domaine
    QDate dateAdded;        // Renamed from dateAjout
    int claimCount;         // Renamed from nbReclamations - Can be updated after loading claims
};

// Assuming Reclamation struct is defined in gestionreclam.h with members like:
// struct Reclamation {
//     QString id;
//     QString clientId;
//     QDate date;
//     QString description;
//     QString statut; // status
//     QString importance;
// };


class ClientManager : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();
    void refreshClientData();

private slots:
    // Slots renamed for English consistency
    void deleteClient();                // Renamed from supprimerClient
    void refreshTable();                // Renamed from rafraichirTable
    void checkAlerts();                 // Renamed from verifierAlertes
    void changeAlertThreshold();        // Renamed from changerSeuilAlerte
    void applyFilters();                // Renamed from appliquerFiltres
    void exportToCSV();                 // Renamed from exporterVersCSV
    void runPredictiveAnalysis();       // Renamed from lancerAnalysePredictive
    void incrementClaim();              // Renamed from incrementerReclamation
    void onTableSelectionChanged();     // Kept original name (already English)
    void exportToPPT();                 // Renamed from exporterVersPPT
    void showChart();                   // Renamed from afficherGraphique
    void viewClientClaims();            // Renamed from consulterClient
    void displaySelectedClientInfo();   // Renamed from afficherInfosClientSelectionne

private:
    Ui::ClientManager *ui;              // Pointer to the UI elements defined in the .ui file
    QMap<QString, ClientData > m_clients;    // Map storing client data (ID -> Client struct)
    int m_alertThreshold = 5;           // Renamed from m_seuilAlerte, default value set based on previous files
    QString m_selectedClientId = "";    // Renamed from m_idClientSelectionne

    // --- ADDITIONS for claim management ---
    QList<Reclamation> m_allClaims;     // Renamed from m_allReclamations - Stores all loaded claims
    void loadInitialDataFromDB();       // Function to load clients AND claims
    void updateClientClaimCounts();     // Renamed from updateClientReclamationCounts - Updates counts after loading
    // --- END ADDITIONS ---

    // Helper Functions
    QString generateUniqueID() const;   // Renamed from genererIDUnique - For clients (if reactivated)
    void showAlert(const QString& message); // Renamed from afficherAlerte
    int getRowIndexFromId(const QString& id) const; // Kept original name (already English)
    void clearInputFields();

};
#if !defined(CLIENT_INCLUDED) && !defined(CLIENTMANAGER_INCLUDED)
#define CLIENTMANAGER_INCLUDED
#include "clientmanager.h"
#endif
