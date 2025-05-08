#include "newclient.h"
#include "ui_newclient.h"
#include "mainwindow.h"

NewClient::NewClient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewClient)
{
    ui->setupUi(this);

}

NewClient::~NewClient()
{
    delete ui;
}

void NewClient::on_btnAdd_clicked()
{
    int id = ui->txtID->text().toInt(); // Convert the entered string to an integer since the id attribute is of type int
    QString name = ui->txtFirstName->text();
    QString surname = ui->txtLastName->text();
    QString email = ui->txtEmail->text();
    QString contact = ui->txtContact->text();
    QString occupation = ui->txtOccupation->text();
    QString country = ui->txtCountry->text();

    Client C(id, name, surname, email, contact, occupation, country);

    bool test = C.ajouter();

    if (test) // If the query executed successfully --> QMessageBox::information
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Addition successful\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        emit clientAdded();

        // Access the MainWindow instance and call refreshTable()
        MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
        if (mainWindow)
        {
            mainWindow->refreshTable();
        }
        else
        {
            qDebug() << "Parent cast to MainWindow failed.";
        }

        close();

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Addition unsuccessful.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }


}
