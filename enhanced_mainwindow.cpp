#include "enhanced_mainwindow.h"
#include "ui_enhanced_mainwindow.h"
#include "enhanced_addeditdialog.h"
#include "imagepreviewdialog.h"
#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>


QT_USE_NAMESPACE

EnhancedMainWindow::EnhancedMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnhancedMainWindow),
    currentFilterColumn(-1)
{
    ui->setupUi(this);
    // Create menu for the sort button
    QMenu *sortMenu = new QMenu(this);
    sortMenu->addAction("📋 Sort by Name (A→Z)", this, &EnhancedMainWindow::sortByName);
    sortMenu->addAction("🔢 Sort by ID (ascending)", this, &EnhancedMainWindow::sortByID);
    sortMenu->addAction("💵 Sort by Hourly Rate (ascending)", this, &EnhancedMainWindow::sortByRate);
    ui->toolButtonSort->setMinimumHeight(ui->lineEditSearch->height()); // Match Search height
    ui->toolButtonSort->setMinimumWidth(60);
    // Attach the menu to the tool button
    ui->toolButtonSort->setMenu(sortMenu);
    ui->toolButtonSort->setPopupMode(QToolButton::InstantPopup); // Show the menu immediately on click
    sortMenu->setStyleSheet(R"(
    QMenu { background-color: white; color: #000000; font-weight: bold; }
    QMenu::item:selected { background-color: #E0F7FF; }
    )");
    ui->toolButtonSort->setStyleSheet(R"(
    QToolButton {
        background-color: #0095E0;
        color: white;
        border-radius: 4px;
        border: 2px solid white; /* ✅ White border */
        padding: 4px 8px;
        font-weight: bold;
    }
    QToolButton:hover {
        background-color: #007AB8;
        border: 1px solid white;
    }
)");

    ui->lineEditSearch->setPlaceholderText("🔍Search...");
    QPixmap logo(":/images/consultiq_logo.png");
    ui->labelLogo->setPixmap(logo.scaled(140, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    this->setStyleSheet(R"(
        #EnhancedMainWindow { background-color: #00AEFF; }
        QTableView { background-color: white; border: 1px solid #0095E0;
            alternate-background-color: #E0F7FF; gridline-color: #0095E0; }
        QPushButton { background-color: #0095E0; color: white;
            border-radius: 6px; padding: 6px 12px; font-weight: bold; }
        QPushButton:hover { background-color: #007AB8; }
        QLineEdit { background-color: white; border: 1px solid #0095E0;
            border-radius: 4px; padding: 4px; }
        QLabel { color: #1A80B9; font-weight: bold; }
    )");

    model = new QSqlTableModel(this);
    model->setTable("CONSULTANTS");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setStyleSheet("QTableView::item:hover { background-color: #d0eaff; }");

    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &EnhancedMainWindow::filterTextChanged);
    connect(ui->comboBoxFilterBy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &EnhancedMainWindow::onFilterFieldChanged);
    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &EnhancedMainWindow::onAddClicked);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &EnhancedMainWindow::onEditClicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &EnhancedMainWindow::onDeleteClicked);
    connect(ui->pushButtonExportCSV, &QPushButton::clicked, this, &EnhancedMainWindow::onExportClicked);
    connect(ui->tableView, &QTableView::clicked, this, &EnhancedMainWindow::handleTableClick);

    updateTotalCount();
    renderCharts();
}

EnhancedMainWindow::~EnhancedMainWindow() {
    delete ui;
}

void EnhancedMainWindow::filterTextChanged(const QString &text) {
    if (currentFilterColumn == -1)
        proxyModel->setFilterKeyColumn(-1);
    else
        proxyModel->setFilterKeyColumn(currentFilterColumn);
    proxyModel->setFilterFixedString(text);
    updateTotalCount();
}

void EnhancedMainWindow::onFilterFieldChanged(int index) {
    currentFilterColumn = index == 0 ? -1 : model->fieldIndex(ui->comboBoxFilterBy->itemData(index).toString());
    filterTextChanged(ui->lineEditSearch->text());
}

void EnhancedMainWindow::onAddClicked() {
    EnhancedAddEditDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QSqlRecord newRecord = model->record();
        dialog.fillRecord(newRecord);
        if (!model->insertRecord(-1, newRecord) || !model->submitAll())
            QMessageBox::warning(this, "Error", model->lastError().text());
        updateTotalCount();
        renderCharts();
    }
}

void EnhancedMainWindow::onEditClicked() {
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.size() != 1) {
        QMessageBox::warning(this, "Edit", "Please select a row to edit.");
        return;
    }
    int row = proxyModel->mapToSource(selection.first()).row();
    QSqlRecord rec = model->record(row);
    EnhancedAddEditDialog dialog(this);
    dialog.setRecord(rec);
    if (dialog.exec() == QDialog::Accepted) {
        dialog.fillRecord(rec);
        if (!model->setRecord(row, rec) || !model->submitAll())
            QMessageBox::warning(this, "Update Error", model->lastError().text());
        renderCharts();
    }
}

void EnhancedMainWindow::onDeleteClicked() {
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    for (const QModelIndex &index : selected)
        model->removeRow(proxyModel->mapToSource(index).row());
    model->submitAll();
    updateTotalCount();
    renderCharts();
}

void EnhancedMainWindow::onExportClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export CSV", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Export Failed", "Could not open file for writing.");
        return;
    }
    QTextStream stream(&file);
    for (int i = 0; i < model->columnCount(); ++i)
        stream << model->headerData(i, Qt::Horizontal).toString() << (i < model->columnCount() - 1 ? "," : "\n");
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col)
            stream << model->data(model->index(row, col)).toString() << (col < model->columnCount() - 1 ? "," : "\n");
    }
    file.close();
    QMessageBox::information(this, "Export Successful", "CSV file saved successfully.");
}

void EnhancedMainWindow::handleTableClick(const QModelIndex &index) {
    QModelIndex sourceIndex = proxyModel->mapToSource(index);
    if (!index.isValid()) return;
    if (sourceIndex.column() == model->fieldIndex("photo")) {
        QString imagePath = model->data(sourceIndex).toString();
        if (!imagePath.isEmpty()) {
            ImagePreviewDialog *preview = new ImagePreviewDialog(imagePath, this);
            preview->exec();
        }
    } else if (sourceIndex.column() == model->fieldIndex("document")) {
        QString docPath = model->data(sourceIndex).toString();
        if (!docPath.isEmpty() && QFile::exists(docPath))
            QDesktopServices::openUrl(QUrl::fromLocalFile(docPath));
        else
            QMessageBox::warning(this, "File Not Found", "The file could not be found: " + docPath);
    }
}

void EnhancedMainWindow::updateTotalCount() {
    ui->labelTotalEntries->setText("Total Entries: " + QString::number(proxyModel->rowCount()));
}

void EnhancedMainWindow::renderCharts() {
    // 1. Clear old charts
    QLayoutItem *child;
    while ((child = ui->chartContainer->layout() ? ui->chartContainer->layout()->takeAt(0) : nullptr)) {
        delete child->widget();
        delete child;
    }
    if (!ui->chartContainer->layout())
        ui->chartContainer->setLayout(new QHBoxLayout);

    // 2. Create the PIE CHART (Hourly Rates)
    QPieSeries *rateSeries = new QPieSeries();
    QMap<QString, int> rateDistribution;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString rate = model->data(model->index(row, model->fieldIndex("rate"))).toString();
        rateDistribution[rate]++;
    }

    for (auto it = rateDistribution.begin(); it != rateDistribution.end(); ++it) {
        QPieSlice *slice = rateSeries->append("Rate " + it.key(), it.value());
        connect(slice, &QPieSlice::clicked, this, [this, slice]() {
            QString rate = slice->label().split(" ").last();
            ui->comboBoxFilterBy->setCurrentText("RATE");
            ui->lineEditSearch->setText(rate);

            // Highlight clicked slice
            if (lastClickedSlice && lastClickedSlice != slice) {
                lastClickedSlice->setExploded(false);
                lastClickedSlice->setLabelVisible(false);
            }
            slice->setExploded(true);
            slice->setLabelVisible(true);
            lastClickedSlice = slice;
        });
    }


    QChart *rateChart = new QChart();
    rateChart->addSeries(rateSeries);
    rateChart->setTitle("Hourly Rate Distribution");
    rateChart->legend()->setAlignment(Qt::AlignBottom);  // Move legend below the pie
    rateChart->setBackgroundVisible(true); // Cleaner background

    QChartView *rateView = new QChartView(rateChart);
    rateView->setRenderHint(QPainter::Antialiasing);
    rateView->setMinimumHeight(350);
    rateView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rateSeries->setPieSize(0.9); // 🍰 Bigger pie size

    // 3. Create the BAR CHART (Roles)
    QBarSeries *roleSeries = new QBarSeries();
    QBarSet *roleSet = new QBarSet("Roles");
    QStringList roleLabels;
    QMap<QString, int> roleCounts;
    for (int row = 0; row < model->rowCount(); ++row) {
        QString role = model->data(model->index(row, model->fieldIndex("role"))).toString();
        roleCounts[role]++;
    }
    for (auto it = roleCounts.begin(); it != roleCounts.end(); ++it) {
        *roleSet << it.value();
        roleLabels << it.key();
    }

    roleSeries->append(roleSet);

    QChart *roleChart = new QChart();
    roleChart->addSeries(roleSeries);
    roleChart->setTitle("Consultants by Role");

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(roleLabels);
    roleChart->addAxis(axisX, Qt::AlignBottom);
    roleSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    roleChart->addAxis(axisY, Qt::AlignLeft);
    roleSeries->attachAxis(axisY);

    QChartView *roleView = new QChartView(roleChart);
    roleView->setRenderHint(QPainter::Antialiasing);
    roleView->setMinimumHeight(250);
    roleView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 4. 📦 Add BOTH views together at the end
    ui->chartContainer->layout()->addWidget(rateView);
    ui->chartContainer->layout()->addWidget(roleView);
}
void EnhancedMainWindow::sortByName()
{
    ui->tableView->sortByColumn(model->fieldIndex("name"), Qt::AscendingOrder);
}

void EnhancedMainWindow::sortByID()
{
    ui->tableView->sortByColumn(model->fieldIndex("id"), Qt::AscendingOrder);
}

void EnhancedMainWindow::sortByRate()
{
    ui->tableView->sortByColumn(model->fieldIndex("rate"), Qt::AscendingOrder);
}

