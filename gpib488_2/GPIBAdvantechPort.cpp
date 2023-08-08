#include "GPIBPort.h"
#include "gpib488.h"

GPIBPort::GPIBPort() {
    //MDEBUG_FUNCTION;
    _device = 0;
    setAddresses(0);
    _waitResponse = false;
}

bool GPIBPort::open() {
    //MDEBUG_FUNCTION;
//    MDEBUG << QString("board %1, pad %2, sad %3, tmo %4").arg(_board).arg(_pad).arg(_sad).arg(_tmo);
    _device = ibdev(_board, _pad, _sad, _tmo, 1, 0);
    _status = Ibsta();
//    MDEBUG << "status" << hex << _status;
    return ((_status & ERR) == 0);
}

bool GPIBPort::read(QByteArray &data) {
    //MDEBUG_FUNCTION;
    if(_waitResponse) {
        _waitResponse = false;
        ibrd(_device, _bytes, sizeof(_bytes));
        _status = Ibsta();
        //MDEBUG << "status" << hex << _status;
        if((_status & ERR) == 0) {
            data.setRawData(_bytes, Ibcnt());
            //MDEBUG << "data" << data.toHex();
            return true;
        }
    }
    return false;
}

void GPIBPort::write(const QByteArray &data) {
    //MDEBUG_FUNCTION;
    QByteArray command = data.simplified();
    if(command.size() > 1) {
        //MDEBUG << "data" << data.toHex();
        ibwrt(_device, data.constData(), data.size());
    }
    if(command.endsWith("?")) {
        _waitResponse = true;
    }
}

void GPIBPort::close() {
    //MDEBUG_FUNCTION;
}

void GPIBPort::setAddresses(int pad, int sad, int board, int tmo) {
    //MDEBUG_FUNCTION;
    _board = board;
    _pad = pad;
    _sad = sad;
    _tmo = tmo;
    //MDEBUG << QString("board %1, pad %2, sad %3, tmo %4").arg(_board).arg(_pad).arg(_sad).arg(_tmo);
}
