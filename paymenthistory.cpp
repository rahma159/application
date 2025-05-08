#include "paymenthistory.h"
#include "ui_paymenthistory.h"

paymentHistory::paymentHistory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::paymentHistory)
{
    ui->setupUi(this);
}

paymentHistory::~paymentHistory()
{
    delete ui;
}
