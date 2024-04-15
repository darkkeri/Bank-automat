#include "rfid_dll.h"




RFID_DLL::RFID_DLL(QObject *parent):QObject(parent)
{
    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM3");
    COMPORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);

    COMPORT->open(QIODevice::ReadWrite);


    if (COMPORT->isOpen())
    {
        qDebug()<<"SerialPort is connected.";
        qDebug()<<COMPORT->error();
    }
    else
    {
        qDebug()<<"Serial Port is not connected...";
        qDebug()<<COMPORT->error();
    }

    connect(COMPORT,SIGNAL(readyRead()),this,SLOT(Read_Data()));

}

void RFID_DLL::Read_Data()
{
    if (COMPORT->isOpen())
    {
        while (COMPORT->bytesAvailable())
        {

            QString cardNumber = COMPORT->readAll();
            emit signalCard(cardNumber);
            qDebug()<<"DLL kortti "<<cardNumber;
        }
    }
}
