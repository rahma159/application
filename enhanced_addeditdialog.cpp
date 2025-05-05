#include "enhanced_addeditdialog.h"
#include "ui_enhanced_addeditdialog.h"

#include <QFileDialog>
#include <QSqlRecord>
#include <QDebug>

EnhancedAddEditDialog::EnhancedAddEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnhancedAddEditDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->pushButtonUploadPhoto, &QPushButton::clicked, this, &EnhancedAddEditDialog::on_pushButtonUploadPhoto_clicked);
    connect(ui->pushButtonUploadDoc, &QPushButton::clicked, this, &EnhancedAddEditDialog::on_pushButtonUploadDoc_clicked);
}

EnhancedAddEditDialog::~EnhancedAddEditDialog()
{
    delete ui;
}

void EnhancedAddEditDialog::on_pushButtonUploadPhoto_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Photo", QString(), "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        ui->labelPhotoPath->setText(fileName);
        qDebug() << "Selected photo:" << fileName;
    }
}

void EnhancedAddEditDialog::on_pushButtonUploadDoc_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Document", QString(), "Documents (*.pdf *.doc *.docx *.txt)");
    if (!fileName.isEmpty()) {
        ui->labelDocPath->setText(fileName);
        qDebug() << "Selected document:" << fileName;
    }
}

void EnhancedAddEditDialog::setRecord(const QSqlRecord &record)
{
    ui->lineEditName->setText(record.value("name").toString());
    ui->lineEditEmail->setText(record.value("email").toString());
    ui->lineEditPhone->setText(record.value("phone").toString());
    ui->comboBoxRole->setCurrentText(record.value("role").toString());
    ui->comboBoxExpertise->setCurrentText(record.value("expertise").toString());
    ui->doubleSpinBoxRate->setValue(record.value("rate").toDouble());
    ui->comboBoxAvailability->setCurrentText(record.value("availability").toString());
    ui->labelPhotoPath->setText(record.value("photo").toString());
    ui->lineEditLeaveNotes->setText(record.value("leave_note").toString());
    ui->calendarWorkingDays->setSelectedDate(record.value("calendar").toDate());
    ui->labelDocPath->setText(record.value("document").toString());
}

void EnhancedAddEditDialog::fillRecord(QSqlRecord &record) const
{
    record.setValue("name", ui->lineEditName->text());
    record.setValue("email", ui->lineEditEmail->text());
    record.setValue("phone", ui->lineEditPhone->text());
    record.setValue("role", ui->comboBoxRole->currentText());
    record.setValue("expertise", ui->comboBoxExpertise->currentText());
    record.setValue("rate", ui->doubleSpinBoxRate->value());
    record.setValue("availability", ui->comboBoxAvailability->currentText());
    record.setValue("photo", ui->labelPhotoPath->text());
    record.setValue("leave_note", ui->lineEditLeaveNotes->text());
    record.setValue("calendar", ui->calendarWorkingDays->selectedDate());
    record.setValue("document", ui->labelDocPath->text());
}
