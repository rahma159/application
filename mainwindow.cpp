#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QSqlError>
#include <QDebug>
#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QVBoxLayout>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ptrNewClient(new NewClient(this)) // Pass MainWindow as parent
    , ptrModClient(new ModClient(this)) // Pass MainWindow as parent
    , ptrHistory(new history(this))
    , model(new QSqlQueryModel(this))

{
    ui->setupUi(this);

    refreshTable();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ptrNewClient, &NewClient::clientAdded, this, &MainWindow::refreshTable);
    connect(ui->searchBar, &QLineEdit::textChanged, this, &MainWindow::onFilterClient);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onFilterClient);
    connect(ui->btnStats, &QPushButton::clicked, this, &MainWindow::on_btnStats_clicked);
    connect(ptrModClient, &ModClient::clientModified, this, &MainWindow::refreshTable);
    connect(ui->btnHistory, &QPushButton::clicked, this, &MainWindow::on_btnHistory_clicked);


}


MainWindow::~MainWindow()
{
    delete ui;
    delete ptrNewClient;
    delete ptrModClient;
    delete ptrHistory;
}


//refresh
void MainWindow::refreshTable()
{
    // Fetch and display the updated data
    QSqlQueryModel *model = Etmp.afficher();
    if (model) {
        ui->tableView->setModel(model);
        qDebug() << "Table refreshed successfully.";
    } else {
        qDebug() << "Error refreshing table.";
    }
}


//add page
void MainWindow::on_pushButton_clicked()
{
    ptrNewClient->exec();
}


//delete

void MainWindow::on_btnDelete_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    if (!selectionModel->hasSelection())
    {
        QMessageBox::warning(this,
                             tr("No Selection"),
                             tr("Please select a client to delete."),
                             QMessageBox::Ok);
        return;
    }

    QModelIndex selectedIndex = selectionModel->selectedRows(0).first(); // Assuming the ID is in the first column
    int id = selectedIndex.data().toInt();

    bool test = Etmp.supprimer(id);

    if (test)
    {
        QMessageBox::information(this,
                                 tr("Success"),
                                 tr("The client was successfully deleted."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Failed to delete the client. Please try again."),
                              QMessageBox::Ok);
    }

    refreshTable(); // Refresh the table view
}


//generate exel file

void MainWindow::on_btnGenerate_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV File", "", "CSV Files (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Unable to open file for writing");
        return;
    }

    QTextStream stream(&file);

    // Get the model from the table view
    QAbstractItemModel *tableModel = ui->tableView->model();
    if (!tableModel) {
        QMessageBox::warning(this, "Error", "No data to export");
        return;
    }

    // Write header row
    QStringList headers;
    for (int column = 0; column < tableModel->columnCount(); ++column) {
        headers << tableModel->headerData(column, Qt::Horizontal).toString();
    }
    stream << headers.join(",") << "\n";

    // Write data rows
    for (int row = 0; row < tableModel->rowCount(); ++row) {
        QStringList rowData;
        for (int column = 0; column < tableModel->columnCount(); ++column) {
            rowData << tableModel->data(tableModel->index(row, column)).toString();
        }
        stream << rowData.join(",") << "\n";
    }

    file.close();

    QMessageBox::information(this, "Success", "CSV file generated successfully!");
}

//search client
void MainWindow::onFilterClient()
{
    QString filterText = ui->searchBar->text();
    QString filterBy = ui->comboBox->currentText();
    QString filterColumn;

    // Determine the column to filter by
    if (filterBy == "ID") {
        filterColumn = "id";
    } else if (filterBy == "First Name") {
        filterColumn = "first_name";
    } else if (filterBy == "Last Name") {
        filterColumn = "last_name";
    } else if (filterBy == "Email") {
        filterColumn = "email";
    } else if (filterBy == "Contact number") {
        filterColumn = "contact";
    } else if (filterBy == "Occupation") {
        filterColumn = "occupation";
    } else if (filterBy == "Country") {
        filterColumn = "country";
    }

    QSqlQuery query;
    query.prepare(QString("SELECT * FROM CLIENT WHERE %1 LIKE :filterText").arg(filterColumn));
    query.bindValue(":filterText", "%" + filterText + "%");

    if (!query.exec()) {
        qDebug() << "Filter query failed:" << query.lastError();
        return;
    }

    QSqlQueryModel *filterModel = new QSqlQueryModel();
    filterModel->setQuery(std::move(query));

    if (filterModel->rowCount() == 0) {
        qDebug() << "No results found.";
    }

    ui->tableView->setModel(filterModel);
}



//stats
void MainWindow::on_btnStats_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT TO_CHAR(date_inscription, 'YYYY-MM') AS MonthYear, COUNT(*) AS Total "
                  "FROM CLIENT "
                  "GROUP BY TO_CHAR(date_inscription, 'YYYY-MM') "
                  "ORDER BY TO_CHAR(date_inscription, 'YYYY-MM')");

    if (!query.exec()) {
        qDebug() << "Error executing query for statistics:" << query.lastError();
        QMessageBox::critical(this, "Database Error", "Failed to retrieve statistics.");
        return;
    }

    QBarSet *barSet = new QBarSet("Number of Clients");
    QStringList categories;
    int maxValue = 0;

    while (query.next()) {
        QString monthYear = query.value(0).toString();
        int count = query.value(1).toInt();

        *barSet << count;
        categories << monthYear;

        if (count > maxValue) {
            maxValue = count;
        }
    }

    QBarSeries *series = new QBarSeries();
    series->append(barSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Monthly Client Registrations");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // X-axis: categories = months
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Month-Year");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y-axis: values = number of clients
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of Clients");
    axisY->setLabelFormat("%d");
    axisY->setRange(0, maxValue + 1);
    axisY->applyNiceNumbers();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Show in dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Client Registration Statistics");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setLayout(layout);
    dialog->resize(800, 600);
    dialog->exec();
}


//modify
void MainWindow::on_btnMod_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    if (!selectionModel->hasSelection()) {
        QMessageBox::warning(this, "No Selection", "Please select a client to modify.");
        return;
    }

    QModelIndex selectedIndex = selectionModel->selectedRows(0).first(); // Assuming the ID is in the first column
    int id = selectedIndex.data().toInt();

    // Fetch client details from the database
    QSqlQuery query;
    query.prepare("SELECT first_name, last_name, email, contact, occupation, country FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch client details.");
        return;
    }

    QString firstName = query.value(0).toString();
    QString lastName = query.value(1).toString();
    QString email = query.value(2).toString();
    QString contact = query.value(3).toString();
    QString occupation = query.value(4).toString();
    QString country = query.value(5).toString();

    // Show the modification dialog
    ModClient modDialog(this);
    modDialog.setClientData(id, firstName, lastName, email, contact, occupation, country);

    if (modDialog.exec() == QDialog::Accepted) {
        refreshTable(); // Refresh table after modification
    }
}



void MainWindow::on_btnHistory_clicked()
{
    ptrHistory->exec();

}

