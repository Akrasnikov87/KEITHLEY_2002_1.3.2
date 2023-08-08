#ifndef GPIBPORT_H
#define GPIBPORT_H

#include <QtWidgets>

#define GPIB_BUFFER_SIZE 16384
#define GPIB_MAX_ADDRESS 30

#define MDEBUG qDebug()

class Port {
public:
    virtual ~Port() {}
    virtual bool open() = 0;
    virtual bool read(QByteArray &data) = 0;
    virtual void write(const QByteArray &data) = 0;
    virtual void close() = 0;
};

class GPIBPort : public Port {
public:
    GPIBPort();

    bool open();
    bool read(QByteArray &data);
    void write(const QByteArray &data);
    void close();

    QStringList addressList() {
        QStringList list;
        for(int i = 0; i <= GPIB_MAX_ADDRESS; i++) list.append(QString::number(i));
        return list;
    }

    void setAddresses(int pad, int sad = 0, int board = 0, int tmo = 9);
    int status() { return _status; }

protected:
    int _board;
    int _pad;
    int _sad;
    int _tmo;
    int _device;
    int _status;
    char _bytes[GPIB_BUFFER_SIZE];
    bool _waitResponse;
};

#endif // GPIBPORT_H
