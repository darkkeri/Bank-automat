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
        qDebug()<<"Kohta 1.";
        while (COMPORT->bytesAvailable())
        {
            qDebug()<<"Kohta 2.";
            // ALKUPERÄINEN alla uus.. Data_From_SerialPort += COMPORT->readAll();
            auto cardNumber = COMPORT->readAll();
            ui->listBox->addItem(QString(cardNumber));
            qDebug()<<"Syötetyn kortin numero on "<<cardNumber<<". Onko tämä syöttämäsi kortti?";
            pinUiPtr = new pinUI(this);
            pinUiPtr->show();
        }

//    Testikoodia
    //     if (Data_From_SerialPort.at(Data_From_SerialPort.length() - 1) == char (10))
    //     {
    //             qDebug()<<"Kohta 3.";
    //             IS_Data_Recieved = true;
    //     }
    // }
    //     if (IS_Data_Recieved == true)
    //     {
    //     qDebug()<<"Kohta 4.";
    //     qDebug()<<"Data From Serial Port :"<< Data_From_SerialPort;
    //         Data_From_SerialPort = "";
    //         IS_Data_Recieved = false;
    //     }
    }
}




