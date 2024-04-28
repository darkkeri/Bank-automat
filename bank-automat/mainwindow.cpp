#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->creditButton->setVisible(false);
    ui->debitButton->setVisible(false);

    ptr_rfid = new RFID_DLL(this);
    ptr_pinui = new PINUIDLL(this);
    ptr_rest = RestDLL::getInstance();
    secWindow = new bankwindow(this);

    connect(secWindow,SIGNAL(restartSignal()), this,SLOT(restart())); //Connection from bankview to mainview for resetting mainview
    connect(ptr_rfid,SIGNAL(signalCard(QString&)), this,SLOT(cardHandler(QString&))); //Connection from RFID to main
    connect(ptr_pinui,SIGNAL(sendNumberToMainWindow(QString)), this,SLOT(pinHandler(QString))); //Connection from PINUI to main
    connect(ptr_rest,SIGNAL(pinCheckSignal(bool)), this,SLOT(pinCheckHandler(bool)));
    connect(ptr_rest,SIGNAL(cardTypeSignal(QString)), this,SLOT(CardCheckHandler(QString)));
    connect(ptr_rest,SIGNAL(getTriesSignal(QString)), this,SLOT(triesHandler(QString)));


    ptr_rfid->Read_Data();//Setup for RFID


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::secondViewOpen(){
    qDebug()<< "secondviewopen ran";
        hide();
        if(bviewflag == false){
            secWindow->startTimer();
            bviewflag = true;
            secWindow->exec();
        } else {
            secWindow->openWindow();
        }
}

void MainWindow::cardHandler(QString& card)
{
    qDebug()<< "cardHandler ran";
        ptr_rest->getCardID(card);
        ptr_pinui->startTimer();
        ptr_pinui->exec();
}

void MainWindow::pinHandler(QString pin) //Gets signal from PIN_UI DLL with inputted pincode
{
    ptr_rest->checkPin(pin);
    qDebug()<< "pinHandler ran"<<pin;
}

void MainWindow::pinCheckHandler(bool pinCheck)
{
    qDebug()<<"pincheckhandler ran";
    if(pinCheck == true){
        qDebug()<< "pin is correct";
        ptr_pinui->closePin();
        ptr_rest->putTries(false);
        if(cardType == "multicard") {
            ui->startStatuslabel->setText("Valitse kaksoiskortin tila");
            ui->creditButton->setVisible(true);
            ui->debitButton->setVisible(true);
        } else if (cardType == "debit"){
            ptr_rest->accountIDbyType("0");
            secondViewOpen();
        } else if (cardType == "credit"){
            ptr_rest->accountIDbyType("1");
            secondViewOpen();
        }
    } else {
        qDebug()<< "pin is incorrect";
        ptr_rest->putTries(true);
        ptr_rest->getTries();
    }
}

void MainWindow::CardCheckHandler(QString checkresult)
{
    qDebug()<< "cardcheckHandler ran";
    cardType = checkresult;
    secWindow->setCardType(cardType);
}

void MainWindow::triesHandler(QString wrongTries)
{
    int actualTries = 3 - wrongTries.toInt();
    tries = QString::number(actualTries);
    ptr_pinui->wrongPin(tries);
}

void MainWindow::on_debitButton_clicked()
{
    qDebug()<< "multicard debit chosen";
    cardType = "debit";
    secWindow->setCardType(cardType);
    ptr_rest->accountIDbyType("0");
    secondViewOpen();
}

void MainWindow::on_creditButton_clicked()
{
    qDebug()<< "multicard credit chosen";
    cardType = "credit";
    secWindow->setCardType(cardType);
    ptr_rest->accountIDbyType("1");
    secondViewOpen();
}

void MainWindow::restart()
{
    qDebug()<< "restart ran";
    show();
    ui->startStatuslabel->setText("Syötä kortti");
    ui->creditButton->setVisible(false);
    ui->debitButton->setVisible(false);
}

void MainWindow::on_OFFButton_clicked()
{
    QApplication::quit();
}
