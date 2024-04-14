#ifndef RFID_DLL_H
#define RFID_DLL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>


#include "RFID_DLL_global.h"

class RFID_DLL_EXPORT RFID_DLL : public QObject
{
    Q_OBJECT
public:
    RFID_DLL(QObject *parent);

public slots:
    void Read_Data();

private:
    QSerialPort* COMPORT;

private slots:


signals:
    void signalCard(QString&);

};

#endif // RFID_DLL_H
