#include "client.h"
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Client::Client()
    : id(0), name(""), surname(""), email(""), contact(""), occupation(""), country("")
{}

Client::Client(int id, QString name, QString surname, QString email, QString contact, QString occupation, QString country)
    : id(id), name(name), surname(surname), email(email), contact(contact), occupation(occupation), country(country)
{}

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

    if (!query.exec()) {
        qDebug() << "Error adding client:" << query.lastError();
        return false;
    }
    return true;
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

    if (model->lastError().isValid()) {
        qDebug() << "Error displaying clients:" << model->lastError();
    }

    return model;
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("DELETE FROM CLIENT WHERE id = :id");
    query.bindValue(":id", res);

    if (!query.exec()) {
        qDebug() << "Error deleting client:" << query.lastError();
        return false;
    }
    return true;
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET first_name = :name, last_name = :surname, email = :email, "
                  "contact = :contact, occupation = :occupation, country = :country WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":email", email);
    query.bindValue(":contact", contact);
    query.bindValue(":occupation", occupation);
    query.bindValue(":country", country);

    if (!query.exec()) {
        qDebug() << "Error modifying client:" << query.lastError().text();
        return false;
    }

    qDebug() << "Client modified successfully. ID:" << id;
    return true;
}
