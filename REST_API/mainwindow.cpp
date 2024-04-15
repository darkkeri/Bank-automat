#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr_dll = new RestDLL(this);
    //btnGet -> get_Clicked()
    connect(ui->btnGet,SIGNAL(clicked(bool)),
            ptr_dll,SLOT(get_Clicked()));
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






