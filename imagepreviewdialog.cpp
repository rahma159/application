#include "imagepreviewdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFileInfo>

ImagePreviewDialog::ImagePreviewDialog(const QString &imagePath, QWidget *parent)
    : QDialog(parent), imageLabel(new QLabel(this))
{
    setWindowTitle(QFileInfo(imagePath).fileName());
    QVBoxLayout *layout = new QVBoxLayout(this);
    imageLabel->setPixmap(QPixmap(imagePath).scaled(340, 340, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(imageLabel);
    setLayout(layout);
    setFixedSize(360, 380);
}
