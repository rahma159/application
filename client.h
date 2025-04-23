#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class Client
{
    QString name, surname, email, contact, occupation, country;
    int id;

public:
    // Constructors
    Client() {}
    Client(int, QString, QString, QString, QString, QString, QString);

    // Getters
    QString getName() { return name; }
    QString getSurname() { return surname; }
    QString getEmail() { return email; }
    QString getContact() { return contact; }
    QString getOccupation() { return occupation; }
    QString getCountry() { return country; }
    int getID() { return id; }

    // Setters
    void setName(QString n) { name = n; }
    void setSurname(QString s) { surname = s; }
    void setEmail(QString e) { email = e; }
    void setContact(QString c) { contact = c; }
    void setOccupation(QString o) { occupation = o; }
    void setCountry(QString cn) { country = cn; }
    void setID(int i) { id = i; }

    // Base functionalities related to the Client entity
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
};

#endif // CLIENT_H
