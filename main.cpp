#include "loginandmenu.h"
// #include "enhanced_mainwindow.h" // Décommentez si cette fenêtre est utilisée comme point d'entrée principal
#include "connection.h"       // Pour la classe Connection
// #include "clientmanager.h" // Inclure une seule fois si ClientManager est utilisé dans main.cpp

#include <QApplication>
#include <QStyleFactory>
#include <QMessageBox>
// #include <QSqlDatabase> // N'est plus nécessaire ici, car Connection.h l'inclut et gère QSqlDatabase
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Si ClientManager est réellement utilisé globalement ou dans main, incluez son en-tête une seule fois.
// S'il n'est pas utilisé ici, cette inclusion peut être supprimée.
// #include "clientmanager.h" // Assurez-vous qu'il n'y a pas de doublon d'inclusion

// TODO: Vérifiez le nom de votre fichier de ressources .qrc.
// Si votre fichier est "resources.qrc", alors ce devrait être Q_INIT_RESOURCE(resources);
// Si c'est "Resources.qrc", alors Q_INIT_RESOURCE(Resources); est correct.
// Décommentez et ajustez cette ligne si vous utilisez un fichier de ressources Qt.
// Q_INIT_RESOURCE(Resources);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Appliquer un style global à l'application (par exemple, "Fusion")
    app.setStyle(QStyleFactory::create("Fusion"));

    // --- Appliquer la feuille de style ---
    // Assurez-vous que le chemin d'accès à la ressource est correct (commence par ":/")
    QFile styleFile(":/styles/style.qss");
    if (styleFile.exists()) { // Vérifier d'abord si le fichier existe dans les ressources
        if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&styleFile);
            QString styleSheet = stream.readAll();
            styleFile.close();
            app.setStyleSheet(styleSheet);
            qInfo() << "Feuille de style appliquée avec succès depuis:" << styleFile.fileName();
        } else {
            qWarning() << "Échec de l'ouverture du fichier de feuille de style (raison: " << styleFile.errorString() << "). Chemin:" << styleFile.fileName();
        }
    } else {
        qWarning() << "Fichier de feuille de style non trouvé à l'emplacement des ressources:" << styleFile.fileName();
        qWarning() << "Vérifiez que le fichier .qrc est correctement configuré, compilé et que le chemin d'alias est correct.";
    }

    // Initialisation des ressources (décommentez et ajustez si nécessaire)
    // Exemple: si votre fichier .qrc s'appelle "myresources.qrc", utilisez Q_INIT_RESOURCE(myresources);
    // Q_INIT_RESOURCE(Resources); // Assurez-vous que "Resources" est le nom correct de votre fichier .qrc

    // --- Établissement de la connexion à la base de données ---
    Connection dbConnection; // Crée une instance de votre classe Connection
    bool connectionEstablished = false;

    qInfo() << "Tentative de connexion à la base de données via DSN...";
    // Utilisation correcte de l'énumérateur avec son scope de classe enum
    if (dbConnection.createConnection(ConnectionType::DSN)) {
        qInfo() << "Connexion à la base de données via DSN réussie.";
        connectionEstablished = true;
    } else {
        qWarning() << "La connexion via DSN a échoué. Tentative via chaîne de connexion...";
        // Tentative de secours avec la chaîne de connexion
        if (dbConnection.createConnection(ConnectionType::ConnectionString)) {
            qInfo() << "Connexion à la base de données via chaîne de connexion réussie.";
            connectionEstablished = true;
        } else {
            // Les deux méthodes ont échoué
            qCritical() << "Échec de la connexion à la base de données par toutes les méthodes disponibles.";
            QMessageBox::critical(nullptr, "Erreur Critique de Connexion",
                                  "Impossible de se connecter à la base de données.\n"
                                  "L'application ne peut pas continuer sans connexion à la base de données.\n"
                                  "Veuillez vérifier la configuration du DSN ('Source_Projet2A'), "
                                  "les identifiants, et l'état du serveur de base de données.\n\n"
                                  "L'application va maintenant se fermer.");
            return 1; // Quitter l'application car la connexion est essentielle
        }
    }

    // Si la connexion est établie, on continue avec l'interface utilisateur
    if (connectionEstablished) {
        qInfo() << "La connexion à la base de données est établie. Lancement de l'interface utilisateur principale...";

        LoginAndMenu w; // Crée l'instance de votre fenêtre de login/menu principal
        w.show();       // Affiche la fenêtre

        // Si vous avez une autre fenêtre principale comme EnhancedMainWindow et que LoginAndMenu
        // la lance après une connexion réussie, cette structure est correcte.
        // Si EnhancedMainWindow est la fenêtre principale à lancer directement ici,
        // commentez LoginAndMenu et décommentez ce qui suit :
        // EnhancedMainWindow mainWindow;
        // mainWindow.show();

        return app.exec(); // Démarrer la boucle d'événements principale de Qt
    } else {
        // Ce bloc ne devrait théoriquement pas être atteint à cause du 'return 1;' plus haut
        // si connectionEstablished reste false, mais c'est une sécurité.
        qCritical() << "La connexion à la base de données n'a pas pu être établie. Fermeture de l'application.";
        return 1; // Assurer la sortie si, pour une raison quelconque, ce point est atteint sans connexion
    }
}
