#ifndef SERIAL_PORT_MANAGER_H
#define SERIAL_PORT_MANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortManager : public QObject {
    Q_OBJECT
public:
    explicit SerialPortManager(QObject *parent = nullptr);
    ~SerialPortManager();

    bool connect(const QString &portName, int baudRate);
    void disconnect();
    bool isConnected() const;
    QStringList availablePorts() const;

signals:
    void dataReceived(const QString &data);
    void connectionChanged(bool connected);

private slots:
    void handleReadyRead();

private:
    QSerialPort *serial;
};

#endif#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

class SerialPortManager
{
public:
    SerialPortManager();
};

#endif // SERIALPORTMANAGER_H
