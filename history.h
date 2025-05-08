
#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlRecord>

namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

    // Function to load and display the history
    void loadHistory();

private slots:
    void on_filterComboBox_currentIndexChanged(int index);
    void on_dateEdit_dateChanged(const QDate &date);
    void on_clearButton_clicked();

private:
    Ui::history *ui;
    void populateListWidget(QSqlQuery &query);
};

#endif // HISTORY_H
