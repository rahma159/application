#ifndef ENHANCED_ADDEDITDIALOG_H
#define ENHANCED_ADDEDITDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class EnhancedAddEditDialog;
}

class EnhancedAddEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnhancedAddEditDialog(QWidget *parent = nullptr);
    ~EnhancedAddEditDialog();

    void setRecord(const QSqlRecord &record);
    void fillRecord(QSqlRecord &record) const;

private slots:
    void on_pushButtonUploadDoc_clicked();
    void on_pushButtonUploadPhoto_clicked();

private:
    Ui::EnhancedAddEditDialog *ui;
};

#endif // ENHANCED_ADDEDITDIALOG_H
