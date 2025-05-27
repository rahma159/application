#include "rendezvous.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QMap>
#include <utility> // Include for std::move

// Default Constructor
Rendezvous::Rendezvous() : id_rdv(0), date(QDate::currentDate()), heure(QTime::currentTime()), objet(""), statut("En attente"), type_rdv("") {}

// Parameterized Constructor
Rendezvous::Rendezvous(int id, QDate d, QTime h, QString obj, QString stat, QString type)
{
    id_rdv = id;
    date = d;
    heure = h;
    objet = obj;
    statut = stat;
    type_rdv = type;
}

// Getters
int Rendezvous::getId() const { return id_rdv; }
QDate Rendezvous::getDate() const { return date; }
QTime Rendezvous::getHeure() const { return heure; }
QString Rendezvous::getObjet() const { return objet; }
QString Rendezvous::getStatut() const { return statut; }
QString Rendezvous::getType() const { return type_rdv; }

// Setters
void Rendezvous::setId(int id) { id_rdv = id; }
void Rendezvous::setDate(QDate d) { date = d; }
void Rendezvous::setHeure(QTime h) { heure = h; }
void Rendezvous::setObjet(QString obj) { objet = obj; }
void Rendezvous::setStatut(QString stat) { statut = stat; }
void Rendezvous::setType(QString type) { type_rdv = type; }

// Ajouter un rendez-vous
bool Rendezvous::ajouter()
{
    QSqlQuery query;
    // Use TO_TIMESTAMP for both date and time consistently if HEURE is TIMESTAMP
    query.prepare("INSERT INTO rendezvous (ID_RDV, DATERDV, HEURE, OBJET, STATUT, TYPE) "
                  "VALUES (:id, :daterdv, :heure, :objet, :statut, :type)");

    // Combine date and time into a QDateTime for Oracle TIMESTAMP
    QDateTime dateTimeRdv(date, heure);

    query.bindValue(":id", id_rdv);
    // Bind QDateTime directly if the column type supports it, or format appropriately
    query.bindValue(":daterdv", dateTimeRdv); // Assuming DATERDV is DATE or TIMESTAMP
    query.bindValue(":heure", dateTimeRdv);   // Assuming HEURE is TIMESTAMP
    query.bindValue(":objet", objet);
    query.bindValue(":statut", statut);
    query.bindValue(":type", type_rdv);

    bool success = query.exec();
    if (!success)
    {
        qDebug() << "Erreur ajout:" << query.lastError().text();
    }
    return success;
}

// Supprimer un rendez-vous
bool Rendezvous::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM rendezvous WHERE ID_RDV = :id");
    query.bindValue(":id", id);
    bool success = query.exec();
    if (!success)
    {
        qDebug() << "Erreur suppression:" << query.lastError().text();
    }
    return success;
}

// Modifier un rendez-vous
bool Rendezvous::modifier()
{
    QSqlQuery query;
    // Use TO_TIMESTAMP for both date and time consistently if HEURE is TIMESTAMP
    query.prepare("UPDATE rendezvous SET DATERDV=:daterdv, HEURE=:heure, "
                  "OBJET=:objet, STATUT=:statut, TYPE=:type WHERE ID_RDV=:id");

    // Combine date and time into a QDateTime for Oracle TIMESTAMP
    QDateTime dateTimeRdv(date, heure);

    query.bindValue(":id", id_rdv);
    // Bind QDateTime directly if the column type supports it, or format appropriately
    query.bindValue(":daterdv", dateTimeRdv); // Assuming DATERDV is DATE or TIMESTAMP
    query.bindValue(":heure", dateTimeRdv);   // Assuming HEURE is TIMESTAMP
    query.bindValue(":objet", objet);
    query.bindValue(":statut", statut);
    query.bindValue(":type", type_rdv);

    bool success = query.exec();
    if (!success)
    {
        qDebug() << "Erreur modification:" << query.lastError().text();
    }
    return success;
}

// Afficher tous les rendez-vous
QSqlQueryModel *Rendezvous::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    // Explicitly cast HEURE to VARCHAR for display if needed, or handle QDateTime in the view
    model->setQuery("SELECT ID_RDV, DATERDV, TO_CHAR(HEURE, 'HH24:MI:SS') AS HEURE_STR, OBJET, STATUT, TYPE FROM rendezvous");
    if (model->lastError().isValid())
    {
        qDebug() << "Erreur affichage:" << model->lastError().text();
    }
    // Set headers for the model to match the query
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure")); // Matches HEURE_STR alias
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Objet"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

// Afficher les rendez-vous triés
QSqlQueryModel *Rendezvous::afficherTri(const QString &critere)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryString = QString("SELECT ID_RDV, DATERDV, TO_CHAR(HEURE, 'HH24:MI:SS') AS HEURE_STR, OBJET, STATUT, TYPE FROM rendezvous ORDER BY %1").arg(critere);
    model->setQuery(queryString);
    if (model->lastError().isValid())
    {
        qDebug() << "Erreur tri:" << model->lastError().text() << "Query:" << queryString;
    }
    // Set headers for the model to match the query
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Objet"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

// Rechercher des rendez-vous
QSqlQueryModel *Rendezvous::rechercher(const QString &critere, const QString &texte)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryString;
    QSqlQuery query;

    // Use UPPER for case-insensitive search on string fields
    if (critere == "ID_RDV")
    {
        queryString = "SELECT ID_RDV, DATERDV, TO_CHAR(HEURE, 'HH24:MI:SS') AS HEURE_STR, OBJET, STATUT, TYPE FROM rendezvous WHERE ID_RDV = :texte";
        query.prepare(queryString);
        query.bindValue(":texte", texte.toInt());
    }
    else
    { // Assuming other criteria are strings
        queryString = QString("SELECT ID_RDV, DATERDV, TO_CHAR(HEURE, 'HH24:MI:SS') AS HEURE_STR, OBJET, STATUT, TYPE FROM rendezvous WHERE UPPER(%1) LIKE UPPER(:texte)").arg(critere);
        query.prepare(queryString);
        query.bindValue(":texte", "%" + texte + "%");
    }

    if (!query.exec())
    {
        qDebug() << "Erreur recherche:" << query.lastError().text() << "Query:" << queryString;
        delete model; // Clean up model if query fails
        return nullptr;
    }

    model->setQuery(std::move(query)); // Use std::move here
    if (model->lastError().isValid())
    {
        qDebug() << "Erreur recherche (setQuery):" << model->lastError().text();
    }
    // Set headers for the model to match the query
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RDV"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Heure"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Objet"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Type"));
    return model;
}

// Calculer les statistiques par objet
QMap<QString, int> Rendezvous::calculerStatistiquesObjet()
{
    QMap<QString, int> stats;
    QSqlQuery query;
    query.prepare("SELECT TYPE, COUNT(*) FROM rendezvous GROUP BY TYPE");

    if (query.exec())
    {
        while (query.next())
        {
            stats.insert(query.value(0).toString(), query.value(1).toInt());
        }
    }
    else
    {
        qDebug() << "Erreur calcul statistiques:" << query.lastError().text();
    }
    return stats;
}
