#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QSqlDatabase>
// Déclaration anticipée pour QSqlDatabase si elle n'est pas incluse ici
// mais généralement, il est plus simple d'inclure <QSqlDatabase> si nécessaire.
// class QSqlDatabase;

// Utilisation d'un enum class pour une meilleure portée et type-safety
enum class ConnectionType {
    DSN,
    ConnectionString,
    None // Utile pour suivre l'état initial ou l'échec de la dernière tentative
};

class Connection
{
public:
    Connection();
    ~Connection();


    // Permet de spécifier le type de connexion.
    // Si aucun type n'est spécifié, DSN est utilisé par défaut.
    bool createConnection(ConnectionType type = ConnectionType::DSN);
    void closeConnection();

    // Tente de s'assurer que la connexion est ouverte,
    // en utilisant la dernière méthode de connexion réussie ou DSN par défaut.
    bool updateConnection();

private:
    // Méthodes privées pour gérer les types de connexion spécifiques
    bool createDSNConnection();
    bool createConnectionStringConnection();

    // Membre pour se souvenir du dernier type de connexion qui a réussi
    ConnectionType m_lastSuccessfulConnectionType;

    // Constantes pour les détails de connexion.
    // Il est fortement recommandé de les charger depuis un fichier de configuration
    // ou des variables d'environnement plutôt que de les coder en dur,
    // surtout pour les identifiants.
    const QString DSN_NAME = "Source_Projet2A";
    const QString USERNAME = "consultiq";
    const QString PASSWORD = "hexacore"; // ATTENTION: Mot de passe en clair dans le code source!
    const QString CONNECT_OPTIONS = "SQL_ATTR_NOSCAN=1"; // Options de connexion ODBC spécifiques si nécessaires

    // Nom de connexion utilisé par Qt. QSqlDatabase::defaultConnection est une chaîne vide
    // et désigne la connexion par défaut de Qt.
    const QString QT_CONNECTION_NAME = QSqlDatabase::defaultConnection;
};

#endif // CONNECTION_H
