#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr_dll = new RestDLL(this);
    //btnGet -> get_Clicked()
    //btnPost -> post_Clicked()
    connect(ui->btnPost,SIGNAL(clicked(bool)),
            ptr_dll,SLOT(post_Clicked()));
    //Kun emitataan getResult() qstring arvolla, kutsutaan get_handler()
    connect(ptr_dll,SIGNAL(getResult(QString)),
            this,SLOT(get_Handler(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Kun nappia btnGet painetaan, suoritetaan:


void MainWindow::get_Handler(QString n)
{
    ui->textEdit->setText(n);
}

void MainWindow::on_btnGet_clicked()
{
    int idvalue = ui->getByIdLineEdit->text().toInt();
    ptr_dll->setupGetConnection(idvalue);
}
void MainWindow::on_BtnLogin_clicked()
{
    ptr_dll->setupGetConnection(4);

    ptr_dll->checkBalance(2.22,1);
    QString cardnumber = ui->cardnumberLineEdit->text();
    QString pincode = ui->pincodeLineEdit->text();
    ptr_dll->checkPin(cardnumber,pincode);
}

