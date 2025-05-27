#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMap> // For statistics

class Rendezvous
{
private:
    int id_rdv;
    QDate date;
    QTime heure;
    QString objet;
    QString statut;
    QString type_rdv;

public:
    Rendezvous();
    Rendezvous(int id, QDate d, QTime h, QString obj, QString stat, QString type);

    // Getters
    int getId() const;
    QDate getDate() const;
    QTime getHeure() const;
    QString getObjet() const;
    QString getStatut() const;
    QString getType() const;

    // Setters
    void setId(int id);
    void setDate(QDate d);
    void setHeure(QTime h);
    void setObjet(QString obj);
    void setStatut(QString stat);
    void setType(QString type);

    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    QSqlQueryModel *afficher();

    // New Features
    QSqlQueryModel *afficherTri(const QString &critere);
    QSqlQueryModel *rechercher(const QString &critere, const QString &texte);
    QMap<QString, int> calculerStatistiquesObjet(); // Returns a map of Objet -> Count
};

#endif // RENDEZVOUS_H
