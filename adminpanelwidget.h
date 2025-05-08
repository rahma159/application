#ifndef ADMINPANELWIDGET_H
#define ADMINPANELWIDGET_H

#include <QDialog>

namespace Ui {
class AdminPanelWidget;
}

class AdminPanelWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanelWidget(QWidget *parent = nullptr);
    ~AdminPanelWidget();

private:
    Ui::AdminPanelWidget *ui;
};

#endif // ADMINPANELWIDGET_H
