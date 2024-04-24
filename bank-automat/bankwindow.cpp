#include "bankwindow.h"
#include "ui_bankwindow.h"

bankwindow::bankwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bankwindow)
{
    ui->setupUi(this);
    ui->logsTableView->setVisible(false);
    ptr_restb = RestDLL::getInstance();
    connect(ptr_restb,SIGNAL(getLogsSignal(QString)), this,SLOT(logsHandler(QString)));
    connect(ptr_restb,SIGNAL(getBalanceSignal(QString)), this,SLOT(balanceHandler(QString)));
    connect(ptr_restb,SIGNAL(getCardsSignal(QString)), this,SLOT(cardsHandler(QString)));
    connect(ptr_restb,SIGNAL(getWithdrawSignal(QString)), this,SLOT(withdrawHandler(QString)));
}

bankwindow::~bankwindow()
{
    delete ui;
}

void bankwindow::on_Button1_clicked()
{
    switch(buttonMode){
    case 0:
        modeChange(1);
        break;

    case 1:
        //deduct chosen sum from balance
        ptr_restb->nosto("20");
        //cardCheck();
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;
    }
}


void bankwindow::on_Button2_clicked()
{
    switch(buttonMode){
    case 0:
        ptr_restb->setupGetConnection(1);
        modeChange(2);
        break;

    case 1:
        //deduct chosen sum from balance
        ptr_restb->nosto("40");
        //cardCheck();
        break;

    case 2:
        manageLogTable(1);
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        //valitse kortin debit ominaisuus jos multikortti
        modeChange(4);
        break;

    case 6:
        break;
    }
}


void bankwindow::on_Button3_clicked()
{
    switch(buttonMode){
    case 0:
        ptr_restb->getBalance(); //getBalance
        if(cardType == "credit"){
            ptr_restb->setupGetConnection(2); //getCards
        }
        modeChange(3);
        break;

    case 1:
        //input desired sum using pin_ui and then deduct
        //cardCheck();
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;
    }
}


void bankwindow::on_Button4_clicked()
{
    switch(buttonMode){
    case 0:
        break;

    case 1:
        //deduct chosen sum from balance
        ptr_restb->nosto("50");
        //cardCheck();
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;
    }
}


void bankwindow::on_Button5_clicked()
{
    switch(buttonMode){
    case 0:
        break;

    case 1:
        //deduct chosen sum from balance
        ptr_restb->nosto("100");
        //cardCheck();
        break;

    case 2:
        manageLogTable(2);
        break;

    case 3:
        break;

    case 4:

        break;

    case 5:
        //valitse kortin credit ominaisuus jos multikortti
        modeChange(4);
        break;

    case 6:

        break;
    }
}


void bankwindow::on_Button6_clicked()
{
    switch(buttonMode){
    case 0:
        closeWindow();
        break;

    case 1:
        modeChange(0);
        break;

    case 2:
        ui->logsTableView->setVisible(false);
        modeChange(0);
        break;

    case 3:
        modeChange(0);
        break;

    case 4:
        closeWindow();
        break;

    case 5:
        modeChange(0);
        break;

    case 6:
        break;
    }
}

void bankwindow::modeChange(short newmode)
{
    buttonMode = newmode;
    switch(buttonMode){
    case 0: //main
    ui->statusLabel->setText("Valitse");
    ui->buttonLabel1->setText("Nosto");
    ui->buttonLabel2->setText("Tilitapahtumat");
    ui->buttonLabel3->setText("Saldo");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("");
    ui->buttonLabel6->setText("Lopeta");
    ui->infoLabel1->setText("");
    ui->infoLabel2->setText("");
    ui->infoLabel3->setText("");
    ui->infoLabel4->setText("");
    ui->infoLabel5->setText("");
    break;

    case 1: //nosto
    ui->statusLabel->setText("Valitse nostosumma");
    ui->buttonLabel1->setText("20");
    ui->buttonLabel2->setText("40");
    ui->buttonLabel3->setText("Muu summa");
    ui->buttonLabel4->setText("50");
    ui->buttonLabel5->setText("100");
    ui->buttonLabel6->setText("Takaisin");
    break;

    case 2: //tilitapahtumat
    ui->logsTableView->setVisible(true);
    ui->statusLabel->setText("Tilitapahtumat");
    ui->buttonLabel1->setText("");
    ui->buttonLabel2->setText("Edelliset");
    ui->buttonLabel3->setText("");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("Seuraavat");
    ui->buttonLabel6->setText("Takaisin");
    ui->infoLabel1->setText("");
    ui->infoLabel2->setText("");
    ui->infoLabel3->setText("");
    ui->infoLabel4->setText("");
    ui->infoLabel5->setText("");
    break;

    case 3: //saldo
    ui->statusLabel->setText("Tilin tilanne");
    ui->buttonLabel1->setText("");
    ui->buttonLabel2->setText("");
    ui->buttonLabel3->setText("");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("");
    ui->buttonLabel6->setText("Takaisin");
    ui->infoLabel3->setText("");
    ui->infoLabel4->setText("");
    ui->infoLabel5->setText("");
    break;


    case 4: //ota rahat (maybe oma funktio)
    ui->statusLabel->setText("Ota rahat");
    ui->buttonLabel1->setText("");
    ui->buttonLabel2->setText("");
    ui->buttonLabel3->setText("");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("");
    ui->buttonLabel6->setText("Lopeta");
    ui->infoLabel1->setText("Tililtä nostettu 200 euroa");
    ui->infoLabel2->setText("");
    ui->infoLabel3->setText("");
    ui->infoLabel4->setText("");
    ui->infoLabel5->setText("");
    break;

    case 5: //credit vai debit
        ui->statusLabel->setText("Valitse credit tai debit");
        ui->buttonLabel1->setText("");
        ui->buttonLabel2->setText("Credit");
        ui->buttonLabel3->setText("");
        ui->buttonLabel4->setText("");
        ui->buttonLabel5->setText("Debit");
        ui->buttonLabel6->setText("Takaisin");
        ui->infoLabel1->setText("");
        ui->infoLabel2->setText("");
        ui->infoLabel3->setText("");
        ui->infoLabel4->setText("");
        ui->infoLabel5->setText("");
        break;
    }
}

void bankwindow::cardCheck(){
    bool cardtest = true;
    if(cardtest == true) {
        modeChange(5);
    } else {
        modeChange(4);
    }
}

void bankwindow::closeWindow(){
    hide();
    emit restartSignal();
}

void bankwindow::setCardType(QString mainCardType)
{
    cardType = mainCardType;
    qDebug()<<"bankwindow cardType is "<<cardType;
}

void bankwindow::manageLogTable(short modifier)
{
    switch(modifier){
    case 1: //takaisin 5
        if(logStage>5){
            for(int k = 0; k<=amountOfLogs; k++){
                ui->logsTableView->hideRow(k);
            }
            logStage = logStage-5;
            for(int k = logStage-4; k<=logStage; k++){
                ui->logsTableView->showRow(k);
            }
        }
        break;

    case 2: //seuraavat 5
        if(logStage<amountOfLogs){
            for(int k = 0; k<=amountOfLogs; k++){
                ui->logsTableView->hideRow(k);
            }
            if(logStage+5>amountOfLogs){
                logStage = logStage+5;
                for(int k = logStage-4; k<=amountOfLogs; k++){
                    ui->logsTableView->showRow(k);
                }
                } else {
                logStage = logStage+5;
                    qDebug()<<logStage;
                    for(int k = logStage-4; k<=logStage; k++){
                    ui->logsTableView->showRow(k);
                    }
                }
            }
        break;
        }
    }


void bankwindow::openWindow(){
    show();
    modeChange(0);
}

void bankwindow::logsHandler(QString rawlogs){
    Logs logObj; //NEED TO ONLY CREATE ONCE
    logList.clear();
    qDebug()<<"logHandler ran"<<rawlogs;
    amountOfLogs = 0;

    while(logFlag == false){
    oneLog = rawlogs.section("\r", amountOfLogs, amountOfLogs);
        qDebug()<<amountOfLogs<<"section is this: "<<oneLog;
        if(oneLog == ""){
            logFlag = true;
            qDebug()<<"loop stopped vecause oneLog is empty";
        } else {
            qDebug()<<"Onelog is not empty so create item";
                //    4 | 2022-01-01T06:00:00.000Z | testievent | 200 | 1

            //QString data ="5 | 2022-01-01T06:00:00.000Z | testievent | 3000.45 | 2\r7 | 2023-04-01T06:03:00.000Z | testausEvent | 20040.00 | 2\r";

            //Alla sijoitetaan jokainen sana jokaiselle tapahtumalle
            dateStart = oneLog.section(" | ", 1, 1);
            dateEnd = oneLog.section(" | ", 1, 1);
            event = oneLog.section(" | ", 2, 2);
            amount = oneLog.section(" | ", 3, 3);


            //Lisätään amountin eteen "-" ja perään "€"
            amount.prepend("-");
            amount.append("€");


            //Rikotaan päivämäärä paloihin, joista palat on date1 = "2022-01-01" ja date2 = "06:00"
            date1 = dateStart.remove(10, 14);
            date2 = dateEnd.remove(0, 11);
            date2 = dateEnd.remove(5, 8);


            //Lisätään "06:00" perään väli eli = "06:00 ". Tämän jälkeen lisätään date 1 ja date 2 yhteen kokonaisuuteen = "06:00 2022-01-01"
            date2.append(" ");
            finalDate = date2 + date1;

            //qDebug()<<" finalDate ="<<finalDate<<"\n\ event = "<<event<<"\n\ amount = "<<amount;

            logObj.setType(event); logObj.setAmount(amount); logObj.setDate(finalDate); logList.append(logObj);
            amountOfLogs++;
        }
    }
    logFlag = false;

    QStandardItemModel *table_model = new QStandardItemModel(logList.size(),3);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Type"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Amount"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date & Time"));

    for (int row = 0; row < logList.size(); ++row) {
        QStandardItem *typei = new QStandardItem(logList[row].getType());
        table_model->setItem(row, 0, typei);
        QStandardItem *amounti = new QStandardItem(logList[row].getAmount());
        table_model->setItem(row, 1, amounti);
        QStandardItem *datei = new QStandardItem(logList[row].getDate());
        table_model->setItem(row, 2, datei);
    }
    ui->logsTableView->setModel(table_model);
    for(int k = 0; k<=amountOfLogs; k++){
        ui->logsTableView->hideRow(k);
    }
    logStage = 4;
    for(int k = logStage-5; k<=logStage; k++){
        ui->logsTableView->showRow(k);
    }
}

void bankwindow::balanceHandler(QString balance)
{
    ui->infoLabel1->setText("Tilin saldo: "+balance);
}

void bankwindow::cardsHandler(QString rawCards)
{
    qDebug()<<"cardsHandler:"<<rawCards;
    rawCards = rawCards.section(" | ", 6, 6);
    ui->infoLabel2->setText("Kortin luottoraja: "+rawCards);


}

void bankwindow::withdrawHandler(QString isWithdrawOK)
{
    qDebug()<<isWithdrawOK;
}

void bankwindow::on_pushButton_clicked() //DELETE THIS
{
    Logs logObj;

    logObj.setType("asdasdasdas"); logObj.setAmount("asdasd"); logObj.setDate("afgafgg"); logList.append(logObj);

    QStandardItemModel *table_model = new QStandardItemModel(logList.size(),3);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Type"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Amount"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date & Time"));

    for (int row = 0; row < logList.size(); ++row) {
        QStandardItem *typei = new QStandardItem(logList[row].getType());
        table_model->setItem(row, 0, typei);
        QStandardItem *amounti = new QStandardItem(logList[row].getAmount());
        table_model->setItem(row, 1, amounti);
        QStandardItem *datei = new QStandardItem(logList[row].getDate());
        table_model->setItem(row, 2, datei);
    }
    ui->logsTableView->setModel(table_model);
}


