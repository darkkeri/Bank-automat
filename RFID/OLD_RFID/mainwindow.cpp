#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _serialPort(nullptr)
{
    ui->setupUi(this);
     connect(ui->Button1,SIGNAL(clicked(bool)),
            this,SLOT(handleInsertCardClick()));

}

MainWindow::~MainWindow()
{
    if (_serialPort !=nullptr) {
        _serialPort->close();
        delete _serialPort;
    }
    delete ui;
}

void MainWindow::handleInsertCardClick()
{
    qDebug()<<"handleInsertCardClick funktiossa";
    readerPtr = new cardReader(this);
    readerPtr->show();
   // readerPtr->open();
    loadPorts();
}

void MainWindow::handleCardNumberRead(short)
{

}

void MainWindow::handlePinNumberRead(short)
{

}



void MainWindow::loadPorts()
{
    foreach (auto &port, QSerialPortInfo::availablePorts()){
        ui->cmbPorts->addItem(port.portName());
    }
}


void MainWindow::on_buttonPortsInfo_clicked()
{
    foreach (auto &port, QSerialPortInfo::availablePorts()){
        qDebug() << port.portName();
    }

}


void MainWindow::on_buttonOpenPort_clicked()
{
    if (_serialPort !=nullptr) {
        _serialPort->close();
        delete _serialPort;
    }
    _serialPort = new QSerialPort(this);
    _serialPort->setPortName("COM3");
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);



    if (_serialPort->open(QIODevice::ReadWrite)) {
        QMessageBox::information(this, "Result", "Port opened succesfully! :D");
        connect(_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    } else {
        QMessageBox::critical(this, "Port Errror", "Unable to open specified port :(...");
    }
}

void MainWindow::readData()
{
    if (_serialPort->isOpen()){
        QMessageBox::critical(this, "Port Errror", "No open :(...");
        return;
    }
    auto data = _serialPort->readAll();
    ui->kortinNumero->addItem(QString(data));
}

void MainWindow::on_buttonSend_clicked()
{
    if (_serialPort->isOpen()){
        QMessageBox::critical(this, "Port Errror", "No open :(...");
        return;
    }
    _serialPort->write(ui->lineMessage1->text().toUtf8());
}

