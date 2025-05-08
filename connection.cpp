#include "connection.h" // Assurez-vous que connection.h est correctement défini
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDriver> // Inclus mais non directement utilisé dans les fonctions montrées, QSqlDatabase s'en charge.

// Supposons que connection.h contienne quelque chose comme :
/*
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>

// Déclaration anticipée pour éviter une dépendance cyclique si QSqlDatabase est utilisé dans l'en-tête
// class QSqlDatabase;

enum class ConnectionType {
    DSN,
    ConnectionString,
    None // Utile pour suivre l'état initial ou l'échec
};

class Connection
{
public:
    Connection();
    ~Connection();

    // Permet de spécifier le type, avec DSN par défaut
    bool createConnection(ConnectionType type = ConnectionType::DSN);
    void closeConnection();
    bool updateConnection(); // Tente de s'assurer que la connexion est ouverte

private:
    bool createDSNConnection();
    bool createConnectionStringConnection();

    // Pour se souvenir du dernier type de connexion réussi
    ConnectionType m_lastSuccessfulConnectionType;

    // Constantes pour les détails de connexion (meilleure pratique : les charger depuis un fichier de configuration)
    const QString DSN_NAME = "Source_Projet2A";
    const QString USERNAME = "consultiq";
    const QString PASSWORD = "hexacore"; // ATTENTION: Mots de passe en clair dans le code source
    const QString CONNECT_OPTIONS = "SQL_ATTR_NOSCAN=1";

    // Nom de connexion utilisé par Qt (ici, la connexion par défaut)
    // QSqlDatabase::defaultConnection est une chaîne vide, ce qui désigne la connexion par défaut.
    const QString QT_CONNECTION_NAME = QSqlDatabase::defaultConnection;
};

#endif // CONNECTION_H
*/


Connection::Connection() : m_lastSuccessfulConnectionType(ConnectionType::None) // Initialiser le membre
{
    qDebug() << "[Connection] Constructeur appelé.";
    // Vérification cruciale de la disponibilité du pilote ODBC
    if (!QSqlDatabase::isDriverAvailable("QODBC")) {
        qCritical() << "[Connection] ERREUR FATALE: Le pilote Qt ODBC (QODBC) n'est PAS disponible.";
        // Il est préférable d'éviter QMessageBox dans un constructeur si possible,
        // surtout si cela peut être instancié avant que la boucle d'événements principale ne soit prête.
        // Considérez de retourner un statut ou de lancer une exception.
        QMessageBox::critical(nullptr, "Erreur de Pilote", "Pilote Qt QODBC non trouvé. Les fonctionnalités de base de données seront indisponibles.");
    } else {
        qInfo() << "[Connection] Pilote Qt ODBC (QODBC) disponible.";
    }
}

Connection::~Connection()
{
    qDebug() << "[Connection] Destructeur appelé. Nettoyage de la connexion...";
    // Utiliser le nom de connexion constant défini dans la classe
    // si vous passez à une connexion nommée. Pour la connexion par défaut, QT_CONNECTION_NAME (vide) est correct.
    closeConnection(); // Appeler la méthode de fermeture pour centraliser la logique
}

bool Connection::createConnection(ConnectionType type)
{
    qInfo() << "[Connection] Tentative de création de connexion de type:" << (type == ConnectionType::DSN ? "DSN" : "ConnectionString");
    bool success = false;
    if (type == ConnectionType::DSN) {
        success = createDSNConnection();
    } else {
        success = createConnectionStringConnection();
    }

    if (success) {
        m_lastSuccessfulConnectionType = type; // Enregistrer le type en cas de succès
    } else {
        m_lastSuccessfulConnectionType = ConnectionType::None; // Réinitialiser en cas d'échec
    }
    return success;
}

bool Connection::createDSNConnection()
{
    qDebug() << "[Connection] Tentative de connexion DSN à" << DSN_NAME;

    // Gérer la connexion par défaut (identifiée par un nom vide)
    if (QSqlDatabase::contains(QT_CONNECTION_NAME)) {
        QSqlDatabase existingDb = QSqlDatabase::database(QT_CONNECTION_NAME, false); // false: ne pas ajouter si non trouvée
        if (existingDb.isValid() && existingDb.isOpen()) {
            qInfo() << "[Connection] Connexion DSN déjà établie et ouverte.";
            return true; // Déjà connecté
        }
        // Si elle existe mais n'est pas ouverte/valide, la supprimer avant d'en ajouter une nouvelle
        qDebug() << "[Connection] Suppression de la connexion DSN existante (mais non ouverte/valide).";
        QSqlDatabase::removeDatabase(QT_CONNECTION_NAME);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", QT_CONNECTION_NAME); // Ajoute comme connexion par défaut
    if (!db.isValid()) {
        qCritical() << "[Connection] ERREUR: Impossible d'obtenir un handle de base de données valide pour DSN.";
        // QMessageBox::critical(nullptr, "Erreur Interne", "Impossible d'initialiser la base de données (handle invalide).");
        return false;
    }

    // Utilisation du DSN avec les identifiants
    db.setDatabaseName(DSN_NAME); // C'est le nom du DSN configuré dans l'administrateur ODBC
    db.setUserName(USERNAME);
    db.setPassword(PASSWORD); // ATTENTION: Mot de passe en clair
    if(!CONNECT_OPTIONS.isEmpty()) {
        db.setConnectOptions(CONNECT_OPTIONS);
    }


    if (!db.open()) {
        qCritical() << "[Connection] Erreur de connexion DSN:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur de Connexion DSN",
                              QString("Échec de la connexion via DSN '%1'.\nErreur: %2")
                                  .arg(DSN_NAME)
                                  .arg(db.lastError().text()));
        return false;
    }

    qInfo() << "[Connection] Connexion DSN à" << DSN_NAME << "réussie.";
    return true;
}

bool Connection::createConnectionStringConnection()
{
    qDebug() << "[Connection] Tentative de connexion via chaîne de connexion (utilisant DSN" << DSN_NAME << ").";

    if (QSqlDatabase::contains(QT_CONNECTION_NAME)) {
        QSqlDatabase existingDb = QSqlDatabase::database(QT_CONNECTION_NAME, false);
        if (existingDb.isValid() && existingDb.isOpen()) {
            qInfo() << "[Connection] Connexion via chaîne de connexion déjà établie et ouverte.";
            return true;
        }
        qDebug() << "[Connection] Suppression de la connexion via chaîne de connexion existante (mais non ouverte/valide).";
        QSqlDatabase::removeDatabase(QT_CONNECTION_NAME);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", QT_CONNECTION_NAME);
    if (!db.isValid()) {
        qCritical() << "[Connection] ERREUR: Impossible d'obtenir un handle de base de données valide pour la chaîne de connexion.";
        // QMessageBox::critical(nullptr, "Erreur Interne", "Impossible d'initialiser la base de données (handle invalide).");
        return false;
    }

    // Chaîne de connexion qui pointe vers le même DSN.
    // Pour une véritable connexion sans DSN, la chaîne serait différente, ex:
    // "DRIVER={SQL Server Native Client 11.0};SERVER=your_server;DATABASE=your_db;UID=consultiq;PWD=hexacore;"
    // La chaîne actuelle dépend toujours de la configuration du DSN 'Source_Projet2A'.
    QString connectionString = QString("DSN=%1;UID=%2;PWD=%3;")
                                   .arg(DSN_NAME)
                                   .arg(USERNAME)
                                   .arg(PASSWORD);

    qDebug() << "[Connection] Chaîne de connexion utilisée:" << connectionString.replace(PASSWORD, "****"); // Masquer le mot de passe dans les logs

    db.setDatabaseName(connectionString); // Ici, setDatabaseName prend la chaîne de connexion complète pour ODBC.
    if(!CONNECT_OPTIONS.isEmpty()) {
        db.setConnectOptions(CONNECT_OPTIONS); // ex: "SQL_ATTR_ACCESS_MODE=SQL_MODE_READ_ONLY;SQL_ATTR_TRACE=SQL_OPT_TRACE_ON"
    }

    if (!db.open()) {
        qCritical() << "[Connection] Erreur de connexion via chaîne de connexion:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur de Connexion (Chaîne)",
                              QString("Échec de la connexion via la chaîne de connexion.\nErreur: %1").arg(db.lastError().text()));
        return false;
    }

    qInfo() << "[Connection] Connexion via chaîne de connexion (utilisant DSN" << DSN_NAME << ") réussie.";
    return true;
}

bool Connection::updateConnection()
{
    qDebug() << "[Connection] Vérification/Mise à jour de la connexion.";
    QSqlDatabase db = QSqlDatabase::database(QT_CONNECTION_NAME, false); // Obtenir la connexion par défaut

    if (db.isValid() && db.isOpen()) {
        qInfo() << "[Connection] La connexion est déjà ouverte et valide.";
        return true; // Déjà connectée et valide
    }

    qWarning() << "[Connection] La connexion n'est pas ouverte ou n'est pas valide. Tentative de reconnexion.";

    // Tenter de se reconnecter en utilisant le dernier type de connexion réussi
    if (m_lastSuccessfulConnectionType == ConnectionType::DSN) {
        qInfo() << "[Connection] Tentative de reconnexion via DSN.";
        return createDSNConnection();
    } else if (m_lastSuccessfulConnectionType == ConnectionType::ConnectionString) {
        qInfo() << "[Connection] Tentative de reconnexion via chaîne de connexion.";
        return createConnectionStringConnection();
    } else {
        qWarning() << "[Connection] Aucun type de connexion précédent réussi. Tentative de reconnexion via DSN par défaut.";
        // Par défaut, ou si aucune connexion n'a jamais été établie, essayer DSN (ou une autre stratégie par défaut)
        return createDSNConnection();
    }
}

void Connection::closeConnection()
{
    qDebug() << "[Connection] Fermeture de la connexion...";
    if (QSqlDatabase::contains(QT_CONNECTION_NAME)) {
        QSqlDatabase db = QSqlDatabase::database(QT_CONNECTION_NAME, false); // Obtenir la connexion par son nom (vide pour défaut)
        if (db.isValid() && db.isOpen()) { // Vérifier si elle est valide et ouverte avant de fermer
            db.close();
            qInfo() << "[Connection] Connexion à la base de données fermée.";
        } else {
            qDebug() << "[Connection] La connexion n'était pas ouverte ou n'était pas valide, rien à fermer explicitement.";
        }
        QSqlDatabase::removeDatabase(QT_CONNECTION_NAME); // Supprimer la configuration de la connexion
        qInfo() << "[Connection] Configuration de la connexion supprimée.";
    } else {
        qDebug() << "[Connection] Aucune connexion à fermer/supprimer (nom de connexion non trouvé).";
    }
    m_lastSuccessfulConnectionType = ConnectionType::None; // Réinitialiser l'état
}
