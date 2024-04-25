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
    //TEST
    connect(ui->cardSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    connect(ui->pinSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    //TEST
    connect(secWindow,SIGNAL(restartSignal()), this,SLOT(restart())); //Connection from bankview to mainview for resetting mainview
    connect(ptr_rfid,SIGNAL(signalCard(QString&)), this,SLOT(cardHandler(QString&))); //Connection from RFID to main
    connect(ptr_pinui,SIGNAL(sendNumberToMainWindow(QString)), this,SLOT(pinHandler(QString))); //Connection from PINUI to main
    connect(ptr_rest,SIGNAL(pinCheckSignal(bool)), this,SLOT(pinCheckHandler(bool)));
    connect(ptr_rest,SIGNAL(cardTypeSignal(QString)), this,SLOT(CardCheckHandler(QString)));


    ptr_rfid->Read_Data();//Setup for RFID


}

MainWindow::~MainWindow()
{
    //delete ptr_rfid;
    delete ui;
}

//***********************************************************************TEST
void MainWindow::cardSignalHandler(){ //TEST
    qDebug()<< "cardSignalHandler ran";
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString name = clickedButton->objectName();
    if (name == "cardSimButton" || name == "ptr_rfid"){
        cardSignal = true;
        ptr_pinui->exec();
        qDebug()<< "cardSignal value changed";
    } else if (name == "pinSimButton"){
        pinSignal = true;
        qDebug()<< "pinSignal value changed";
    }
}

void MainWindow::on_OKButton_clicked() //TEST
{
    qDebug()<< "OK-button clicked";
    connect(this, SIGNAL(secondViewOpenSignal()), this, SLOT(secondViewOpen()));
    emit secondViewOpenSignal();
}
//***********************************************************************

void MainWindow::secondViewOpen(){
    qDebug()<< "secondviewopen ran";
    if (cardSignal == true && pinSignal == true){
        hide();
        if(bviewflag == false){
            secWindow->startTimer();
            bviewflag = true;
            secWindow->exec();
        } else {
            secWindow->openWindow();
        }
        cardSignal = false;
        pinSignal = false;
    }
}

void MainWindow::cardHandler(QString& card)
{
    qDebug()<< "cardHandler ran";
        //*******************************************TEST
        cardSignal = true; //TEST
        pinSignal = true; //TEST
        qDebug()<< "Test login possible: press ok";
        //*******************************************

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
        ptr_pinui->wrongPin();
        //pinmsg.setText("Pin-koodi syötetty väärin kolme kertaa. Kortti on lukittu. Ota yhteyttä pankkiisi");
        //Give some type of error message in PIN_UI and let the user try again (No idea how to do this, need to test)
        ptr_pinui->exec();
    }
}

void MainWindow::CardCheckHandler(QString checkresult)
{
    qDebug()<< "cardcheckHandler ran";
    cardType = checkresult;
    secWindow->setCardType(cardType);
}

void MainWindow::on_debitButton_clicked() //credit and debit maybe could be one single function with manual connections?
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
    ui->startStatuslabel->setText("Syötä pankkikortti kortinlukijaan");
    ui->creditButton->setVisible(false);
    ui->debitButton->setVisible(false);
}

void MainWindow::on_OFFButton_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btnLogin_clicked() //TEST
{
    //QString cardsID = ui->cardnumberLineEdit->text();
    //QString accountType = ui->pincodeLineEdit->text();
    ptr_rest->putTries();


}
