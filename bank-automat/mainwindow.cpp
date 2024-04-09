#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cardSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
    connect(ui->pinSimButton, SIGNAL(clicked()), this, SLOT(cardSignalHandler()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cardSignalHandler(){
    qDebug()<< "cardSignalHandler ran";
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString name = clickedButton->objectName();
    if (name == "cardSimButton"){
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

void MainWindow::on_OKButton_clicked()
{
    qDebug()<< "OK-button clicked";
    connect(this, SIGNAL(secondViewOpenSignal()), this, SLOT(secondViewOpen()));
    emit secondViewOpenSignal();
}

