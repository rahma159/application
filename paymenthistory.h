#ifndef PAYMENTHISTORY_H
#define PAYMENTHISTORY_H

#include <QDialog>

namespace Ui {
class paymentHistory;
}

class paymentHistory : public QDialog
{
    Q_OBJECT

public:
    explicit paymentHistory(QWidget *parent = nullptr);
    ~paymentHistory();

private:
    Ui::paymentHistory *ui;
};

#endif // PAYMENTHISTORY_H
