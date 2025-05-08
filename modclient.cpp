#include "modclient.h"
#include "ui_modclient.h"

ModClient::ModClient(QWidget *parent):
    QDialog(parent),
    ui(new Ui::ModClient)
{
    ui->setupUi(this);
    ui->txtID->setReadOnly(true);

}

ModClient::~ModClient()
{
    delete ui;
}

void ModClient::setClientData(const int id, const QString &firstName, const QString &lastName, const QString &email,
                              const QString &contact, const QString &occupation, const QString &country)
{
    client.setID(id);
    client.setName(firstName);
    client.setSurname(lastName);
    client.setEmail(email);
    client.setContact(contact);
    client.setOccupation(occupation);
    client.setCountry(country);

    // Pre-fill the fields with existing client data
    ui->txtID->setText(QString::number(id));
    ui->txtFirstName->setText(firstName);
    ui->txtLastName->setText(lastName);
    ui->txtEmail->setText(email);
    ui->txtContact->setText(contact);
    ui->txtOccupation->setText(occupation);
    ui->txtCountry->setText(country);
}

void ModClient::on_btnSave_clicked()
{
    // Update client data with new values
    client.setName(ui->txtFirstName->text());
    client.setSurname(ui->txtLastName->text());
    client.setEmail(ui->txtEmail->text());
    client.setContact(ui->txtContact->text());
    client.setOccupation(ui->txtOccupation->text());
    client.setCountry(ui->txtCountry->text());

    if (!client.modifier()) {
        QMessageBox::critical(this, "Database Error", "Failed to modify the client.");
        return;
    }

    QMessageBox::information(this, "Success", "Client modified successfully.");
    accept(); // Close the dialog
}

