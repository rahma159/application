#ifndef MODCLIENT_H
#define MODCLIENT_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class ModClient;
}

class ModClient : public QDialog
{
    Q_OBJECT

public:
    explicit ModClient(QWidget *parent = nullptr);
    ~ModClient();

    void setClientData(int id, const QString &firstName, const QString &lastName, const QString &email,
                       const QString &contact, const QString &occupation, const QString &country);

private slots:
    void on_btnSave_clicked();

signals:
    void clientModified();


private:
    Ui::ModClient *ui;
    Client client; // Object to hold client data
};

#endif // MODCLIENT_H
