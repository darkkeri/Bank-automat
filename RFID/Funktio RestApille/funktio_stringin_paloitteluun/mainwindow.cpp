#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

//    4 | 2022-01-01T06:00:00.000Z | testievent | 200 | 1

    do{
    //5 | 2022-01-01T06:00:00.000Z | testievent | 3000.45 | 2\r7 | 2023-04-01T06:03:00.000Z | testausEvent | 20040.00 | 2\r
    //Alla sijoitetaan jokainen sana jokaiselle tapahtumalle
    dateStart = data.section(" | ", 1, 1);
    dateEnd = data.section(" | ", 1, 1);
    event = data.section(" | ", 2, 2);
    amount = data.section(" | ", 3, 3);


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

    logDateVector.fill(finalDate);
    logEventVector.fill(event);
    logAmountVector.fill(amount);
    } while()

    qDebug()<<" finalDate ="<<finalDate<<"\n\ event = "<<event<<"\n\ amount = "<<amount;
}

