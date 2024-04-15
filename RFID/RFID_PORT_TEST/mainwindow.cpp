#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    connect(ui->listBox,SIGNAL(activated(QModelIndex)),
            this,SLOT(Read_Data()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (COMPORT->isOpen())
    {
        qDebug()<<"PushButtonClicked";
    }
}


void MainWindow::Read_Data()
{
    if (COMPORT->isOpen())
    {
        while (COMPORT->bytesAvailable())
        {

            auto cardNumber = COMPORT->readAll();
            ui->listBox->addItem(QString(cardNumber));
            emit cardNumber(QString(cardNumber));
            qDebug()<<"Syötetyn kortin numero on "<<cardNumber<<". Onko tämä syöttämäsi kortti?";
            pinUiPtr = new pinUI(this);
            pinUiPtr->show();
        }
    }
}


