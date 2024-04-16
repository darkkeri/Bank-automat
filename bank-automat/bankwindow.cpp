#include "bankwindow.h"
#include "ui_bankwindow.h"

bankwindow::bankwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::bankwindow)
{
    ui->setupUi(this);
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
        cardCheck();
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
        modeChange(2);
        break;

    case 1:
        //deduct chosen sum from balance
        cardCheck();
        break;

    case 2:
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
        modeChange(3);
        break;

    case 1:
        //input desired sum using pin_ui and then deduct
        cardCheck();
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
        cardCheck();
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
        cardCheck();
        break;

    case 2:
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
        //QApplication::quit();
        emit restartSignal();
        //close program
        break;

    case 1:
        modeChange(0);
        break;

    case 2:
        modeChange(0);
        break;

    case 3:
        modeChange(0);
        break;

    case 4:
        //QApplication::quit();
        emit restartSignal();
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
    ui->buttonLabel2->setText("50");
    ui->buttonLabel3->setText("Muu summa");
    ui->buttonLabel4->setText("80");
    ui->buttonLabel5->setText("100");
    ui->buttonLabel6->setText("Takaisin");
    break;

    case 2: //tilitapahtumat
    ui->statusLabel->setText("Tilitapahtumat");
    ui->buttonLabel1->setText("");
    ui->buttonLabel2->setText("Edelliset");
    ui->buttonLabel3->setText("");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("Seuraavat");
    ui->buttonLabel6->setText("Takaisin");
    ui->infoLabel1->setText("tapahtumia");
    ui->infoLabel2->setText("tapahtumia");
    ui->infoLabel3->setText("tapahtumia");
    ui->infoLabel4->setText("tapahtumia");
    ui->infoLabel5->setText("tapahtumia");
    break;

    case 3: //saldo
    ui->statusLabel->setText("Tilin tilanne");
    ui->buttonLabel1->setText("");
    ui->buttonLabel2->setText("");
    ui->buttonLabel3->setText("");
    ui->buttonLabel4->setText("");
    ui->buttonLabel5->setText("");
    ui->buttonLabel6->setText("Takaisin");
    ui->infoLabel1->setText("Tilin saldo"); //Add balance here
    ui->infoLabel2->setText("Kortin luottoraja");//Add if statement for credit card here
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

