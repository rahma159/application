#include "adminpanelwidget.h"
#include "ui_adminpanelwidget.h"

AdminPanelWidget::AdminPanelWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanelWidget)
{
    ui->setupUi(this);
}

AdminPanelWidget::~AdminPanelWidget()
{
    delete ui;
}
