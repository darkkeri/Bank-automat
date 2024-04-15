#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr_rfid = new RFID_DLL(this);


    connect(ui->cardSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    connect(ui->pinSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    connect(ptr_rfid,SIGNAL(signalCard(QString&)),
            this,SLOT(cardHandler(QString&)));
    ptr_rfid->Read_Data();
}

MainWindow::~MainWindow()
{
    delete ptr_rfid;
    delete ui;
}

void MainWindow::cardSignalHandler(){ //TEST
    qDebug()<< "cardSignalHandler ran";
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString name = clickedButton->objectName();
    if (name == "cardSimButton" || name == "ptr_rfid"){
        cardSignal = true;
        qDebug()<< "cardSignal value changed";
    } else if (name == "pinSimButton"){
        pinSignal = true;
        qDebug()<< "pinSignal value changed";
    }

}

void MainWindow::secondViewOpen(){
    if (cardSignal == true && pinSignal == true){
        bankwindow secWindow;
        secWindow.exec();
        cardSignal = false;
        pinSignal = false;
    }
}

void MainWindow::on_OKButton_clicked() //TEST
{
    hide();
    qDebug()<< "OK-button clicked";
    connect(this, SIGNAL(secondViewOpenSignal()), this, SLOT(secondViewOpen()));
    emit secondViewOpenSignal();
}

void MainWindow::cardHandler(QString& card)
{
    qDebug()<< "cardHandler ran";
        cardSignal = true;
        qDebug()<< "cardSignal value changed";
        //Open PIN_UI here
}

void MainWindow::pinHandler(QString& pin)
{
    qDebug()<< "pinHandler ran";
    /*
    bool pincheck = ptr_restapi->RESTAPIDLL_PIN_function(pin);

    if(pincheck = true){
        qDebug()<< "pin is correct";
        hide();
        bankwindow secWindow;
        secWindow.exec();
    }
    */
}



