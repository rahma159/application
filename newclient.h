#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class NewClient;
}

class NewClient : public QDialog
{
    Q_OBJECT

public:
    explicit NewClient(QWidget *parent = nullptr);
    ~NewClient();

private slots:
    void on_btnAdd_clicked();

signals:
    void clientAdded();


private:
    Ui::NewClient *ui;


};

#endif // NEWCLIENT_H
