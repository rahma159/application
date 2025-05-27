#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "SerialPortManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onDisconnectClicked();
    void handleDataReceived(const QString &data);
    void handleConnectionChanged(bool connected);

private:
    void setupUI();
    void addLogMessage(const QString &message);

    SerialPortManager *serialManager;

    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    QGroupBox *connectionGroup;
    QHBoxLayout *connectionLayout;
    QComboBox *comPortCombo;
    QComboBox *baudRateCombo;
    QPushButton *connectButton;
    QPushButton *disconnectButton;

    QGroupBox *statusGroup;
    QVBoxLayout *statusLayout;
    QLabel *accessLabel;
    QLabel *lastScanLabel;

    QGroupBox *logGroup;
    QVBoxLayout *logLayout;
    QTextEdit *logTextEdit;
};
#endif
