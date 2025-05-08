#pragma once

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>

class Client
{
    int id;
    QString name, surname, email, contact, occupation, country;

public:
    // Constructors
    Client();
    Client(int id, QString name, QString surname, QString email, QString contact, QString occupation, QString country);

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
    bool modifier();
};

#if !defined(CLIENTMANAGER_INCLUDED) && !defined(CLIENT_INCLUDED)
#define CLIENT_INCLUDED
#include "client.h"
#endif
