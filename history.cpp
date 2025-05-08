#include "history.h"
#include "ui_history.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDate>

history::history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);

    // Populate the filter dropdown
    ui->comboBox->addItems({"All", "Added", "Deleted", "Modified"});

    // Connect signals for filtering
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &history::on_filterComboBox_currentIndexChanged);
    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &history::on_dateEdit_dateChanged);

    // Load the history data when the dialog is opened
    loadHistory();
}

history::~history()
{
    delete ui;
}

void history::loadHistory()
{
    // Clear the list widget
    ui->listWidget->clear();

    // Fetch history from the database
    QString queryStr = "SELECT ACTION_TIMESTAMP, ACTION_TYPE, ACTION_DETAILS FROM CLIENT_HISTORY ORDER BY ACTION_TIMESTAMP DESC";
    QSqlQuery query(queryStr);

    // Populate the list widget with the query results
    populateListWidget(query);
}

void history::populateListWidget(QSqlQuery &query)
{
    while (query.next())
    {
        // Extract data from the query
        QString timestamp = query.value("ACTION_TIMESTAMP").toString();
        QString actionType = query.value("ACTION_TYPE").toString();
        QString details = query.value("ACTION_DETAILS").toString();

        // Create a custom widget for the list item
        QWidget *itemWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(itemWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        // Add labels for each part of the history
        QLabel *timestampLabel = new QLabel(timestamp);
        QLabel *actionLabel = new QLabel(actionType);
        QLabel *detailsLabel = new QLabel(details);

        // Style the labels
        QFont boldFont;
        boldFont.setBold(true);
        actionLabel->setFont(boldFont);

        timestampLabel->setStyleSheet("color: gray;");
        detailsLabel->setStyleSheet("color: black;");

        // Add the labels to the layout
        layout->addWidget(timestampLabel);
        layout->addWidget(actionLabel);
        layout->addWidget(detailsLabel);

        // Add the custom widget to the list
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(itemWidget->sizeHint());
        ui->listWidget->setItemWidget(item, itemWidget);
    }
}

void history::on_filterComboBox_currentIndexChanged(int index)
{
    // Get the selected filter
    QString filter = ui->comboBox->currentText();

    // Build the query string with the filter
    QString queryStr = "SELECT ACTION_TIMESTAMP, ACTION_TYPE, ACTION_DETAILS FROM CLIENT_HISTORY";
    if (filter != "All") {
        queryStr += " WHERE ACTION_TYPE = :filter";
    }
    queryStr += " ORDER BY ACTION_TIMESTAMP DESC";

    QSqlQuery query;
    query.prepare(queryStr);
    if (filter != "All") {
        query.bindValue(":filter", filter);
    }
    query.exec();

    // Populate the list widget with the filtered results
    ui->listWidget->clear();
    populateListWidget(query);
}

void history::on_dateEdit_dateChanged(const QDate &date)
{
    // Build the query string with the date filter
    QString queryStr = "SELECT ACTION_TIMESTAMP, ACTION_TYPE, ACTION_DETAILS FROM CLIENT_HISTORY WHERE ACTION_TIMESTAMP >= :dateStart AND ACTION_TIMESTAMP < :dateEnd ORDER BY ACTION_TIMESTAMP DESC";

    QDateTime startDateTime(date, QTime(0, 0, 0));
    QDateTime endDateTime(date.addDays(1), QTime(0, 0, 0));

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":dateStart", startDateTime.toString(Qt::ISODate));
    query.bindValue(":dateEnd", endDateTime.toString(Qt::ISODate));
    query.exec();

    // Populate the list widget with the filtered results
    ui->listWidget->clear();
    populateListWidget(query);
}

void history::on_clearButton_clicked()
{
    // Clear all history records from the database
    QSqlQuery query("DELETE FROM CLIENT_HISTORY");
    query.exec();

    // Clear the list widget
    ui->listWidget->clear();
}
