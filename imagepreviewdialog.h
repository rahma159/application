#ifndef IMAGEPREVIEWDIALOG_H
#define IMAGEPREVIEWDIALOG_H

#include <QDialog>

class QLabel;

class ImagePreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImagePreviewDialog(const QString &imagePath, QWidget *parent = nullptr);

private:
    QLabel *imageLabel;
};

#endif // IMAGEPREVIEWDIALOG_H
