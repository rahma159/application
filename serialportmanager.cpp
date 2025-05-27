#include "SerialPortManager.h"

SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)) {
    connect(serial, &QSerialPort::readyRead, this, &SerialPortManager::handleReadyRead);
}

SerialPortManager::~SerialPortManager() {
    disconnect();
}

bool SerialPortManager::connect(const QString &portName, int baudRate) {
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);

    if (serial->open(QIODevice::ReadWrite)) {
        emit connectionChanged(true);
        return true;
    }
    return false;
}

void SerialPortManager::disconnect() {
    if (serial->isOpen()) {
        serial->close();
        emit connectionChanged(false);
    }
}

bool SerialPortManager::isConnected() const {
    return serial->isOpen();
}

QStringList SerialPortManager::availablePorts() const {
    QStringList ports;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        ports << info.portName();
    }
    return ports;
}

void SerialPortManager::handleReadyRead() {
    while (serial->canReadLine()) {
        QString line = QString::fromUtf8(serial->readLine()).trimmed();
        emit dataReceived(line);
    }
}
