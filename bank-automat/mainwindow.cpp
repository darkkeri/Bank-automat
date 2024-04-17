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
    secWindow = new bankwindow(this);

    //TEST
    connect(ui->cardSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    connect(ui->pinSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    //TEST
    connect(secWindow,SIGNAL(restartSignal()), this,SLOT(restart()));
    connect(ptr_rfid,SIGNAL(signalCard(QString&)), this,SLOT(cardHandler(QString&)));
    ptr_rfid->Read_Data();
}

MainWindow::~MainWindow()
{
    //delete ptr_rfid;
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

void MainWindow::on_OKButton_clicked() //TEST
{
    qDebug()<< "OK-button clicked";
    connect(this, SIGNAL(secondViewOpenSignal()), this, SLOT(secondViewOpen()));
    emit secondViewOpenSignal();
}

void MainWindow::secondViewOpen(){
    if (cardSignal == true && pinSignal == true){
        hide();
        secWindow->exec();
        cardSignal = false;
        pinSignal = false;
    }
}

void MainWindow::cardHandler(QString& card)
{
    qDebug()<< "cardHandler ran";
        cardSignal = true;
        qDebug()<< "cardSignal value changed";
        //Open PIN_UI here
        QString testPIN = "1234"; //TEST
        pinSignal = true; //TEST
        pinHandler(testPIN); //TEST
}

void MainWindow::pinHandler(QString& pin) //Gets signal from PIN_UI DLL with inputted pincode
{
    qDebug()<< "pinHandler ran";

    bool pincheck = true; //TEST
    bool mcardCheck = true; //TEST
    //bool pincheck = ptr_restapi->RESTAPIDLL_PIN_function(pin);
    //bool mcardcheck = ptr_restapi->RESTAPIDLL_multiCardCheck_function();

    if(pincheck == true){
        qDebug()<< "pin is correct";
        if(mcardCheck == true) {
            ui->startStatuslabel->setText("Valitse kaksoiskortin tila");
            ui->creditButton->setVisible(true);
            ui->debitButton->setVisible(true);
        } else {
            secondViewOpen();
        }
    } else {
    qDebug()<< "pin is incorrect";
    //Give some type of error message in PIN_UI and let the user try again (No idea how to do this, need to test)
    }

}

void MainWindow::on_debitButton_clicked() //credit and debit maybe could be one single function with manual connections?
{
    //RESTAPI Credit or Debit function that takes true or false as a variable to choose right account and returns nothing
    qDebug()<< "multicard debit chosen";
    secondViewOpen();
}

void MainWindow::on_creditButton_clicked()
{
    //RESTAPI Credit or Debit function that takes true or false as a variable to choose right account and returns nothing
    qDebug()<< "multicard credit chosen";
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

