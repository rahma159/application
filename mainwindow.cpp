#include "MainWindow.h"
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), serialManager(new SerialPortManager(this)) {
    setupUI();

    // Populate COM ports
    comPortCombo->addItems(serialManager->availablePorts());

    // Set default baud rates
    baudRateCombo->addItems({"9600", "19200", "38400", "57600", "115200"});
    baudRateCombo->setCurrentText("9600");

    // Connect signals
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(disconnectButton, &QPushButton::clicked, this, &MainWindow::onDisconnectClicked);
    connect(serialManager, &SerialPortManager::dataReceived, this, &MainWindow::handleDataReceived);
    connect(serialManager, &SerialPortManager::connectionChanged, this, &MainWindow::handleConnectionChanged);

    // Initial state
    disconnectButton->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete serialManager;
}

void MainWindow::setupUI() {
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    // Connection Group
    connectionGroup = new QGroupBox("Serial Port Configuration", centralWidget);
    connectionLayout = new QHBoxLayout(connectionGroup);

    comPortCombo = new QComboBox(connectionGroup);
    baudRateCombo = new QComboBox(connectionGroup);
    connectButton = new QPushButton("Connect", connectionGroup);
    disconnectButton = new QPushButton("Disconnect", connectionGroup);

    connectionLayout->addWidget(new QLabel("COM Port:"));
    connectionLayout->addWidget(comPortCombo);
    connectionLayout->addWidget(new QLabel("Baud Rate:"));
    connectionLayout->addWidget(baudRateCombo);
    connectionLayout->addWidget(connectButton);
    connectionLayout->addWidget(disconnectButton);

    // Status Group
    statusGroup = new QGroupBox("Access Status", centralWidget);
    statusLayout = new QVBoxLayout(statusGroup);

    accessLabel = new QLabel("No scan yet", statusGroup);
    accessLabel->setAlignment(Qt::AlignCenter);
    accessLabel->setStyleSheet("font-size: 24px;");

    lastScanLabel = new QLabel("Last scan: Never", statusGroup);
    lastScanLabel->setAlignment(Qt::AlignCenter);

    statusLayout->addWidget(accessLabel);
    statusLayout->addWidget(lastScanLabel);

    // Log Group
    logGroup = new QGroupBox("Event Log", centralWidget);
    logLayout = new QVBoxLayout(logGroup);

    logTextEdit = new QTextEdit(logGroup);
    logTextEdit->setReadOnly(true);

    logLayout->addWidget(logTextEdit);

    // Assemble main layout
    mainLayout->addWidget(connectionGroup);
    mainLayout->addWidget(statusGroup);
    mainLayout->addWidget(logGroup);

    setCentralWidget(centralWidget);
    resize(600, 400);
    setWindowTitle("RFID Access Control");
}

void MainWindow::onConnectClicked() {
    if (serialManager->connect(comPortCombo->currentText(), baudRateCombo->currentText().toInt())) {
        addLogMessage("Connected to " + comPortCombo->currentText());
    } else {
        QMessageBox::critical(this, "Error", "Failed to connect to serial port");
    }
}

void MainWindow::onDisconnectClicked() {
    serialManager->disconnect();
    addLogMessage("Disconnected from " + comPortCombo->currentText());
}

void MainWindow::handleDataReceived(const QString &data) {
    if (data.startsWith("TAG:")) {
        QString tagId = data.mid(4);
        addLogMessage("RFID Tag detected: " + tagId);

        if (tagId == "C920D9A3") {
            accessLabel->setText("Access Granted");
            accessLabel->setStyleSheet("color: green; font-weight: bold; font-size: 24px;");
        } else {
            accessLabel->setText("Access Denied");
            accessLabel->setStyleSheet("color: red; font-weight: bold; font-size: 24px;");
        }

        lastScanLabel->setText("Last scan: " + QDateTime::currentDateTime().toString());
    }
}

void MainWindow::handleConnectionChanged(bool connected) {
    connectButton->setEnabled(!connected);
    disconnectButton->setEnabled(connected);
    comPortCombo->setEnabled(!connected);
    baudRateCombo->setEnabled(!connected);
}

void MainWindow::addLogMessage(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    logTextEdit->append(timestamp + message);
}
