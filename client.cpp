#include "client.h"

Client::Client(int id, QString name, QString surname, QString email, QString contact, QString occupation, QString country)
{
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->email = email;
    this->contact = contact;
    this->occupation = occupation;
    this->country = country;
}

bool Client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);

    // Prepare the SQL query
    query.prepare("INSERT INTO CLIENT (id, first_name, last_name, email, contact, occupation, country) "
                  "VALUES (:id, :name, :surname, :email, :contact, :occupation, :country)");

    // Bind the values
    query.bindValue(":id", res);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":email", email);
    query.bindValue(":contact", contact);
    query.bindValue(":occupation", occupation);
    query.bindValue(":country", country);

    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT id, first_name, last_name, email, contact, occupation, country FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Surname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Occupation"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Country"));

    return model;
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("DELETE FROM CLIENT WHERE id = :id");
    query.bindValue(":id", res);

    return query.exec();
}
