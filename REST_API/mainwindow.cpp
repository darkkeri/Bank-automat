#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr_dll = new RestDLL(this);
    //btnGet
    connect(ui->btnGet,SIGNAL(clicked(bool)),
            this,SLOT(get_Click_Handler()));
    //btnPost
    connect(ui->btnPost,SIGNAL(clicked(bool)),
            this,SLOT(post_Click_Handler()));
    //Kun emitataan getResult() qstring arvolla, kutsutaan get_handler()
    connect(ptr_dll,SIGNAL(getResult(QString)),
            this,SLOT(get_Handler(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Kun nappia btnGet painetaan, suoritetaan:
void MainWindow::get_Click_Handler()
{
    ptr_dll->get_Clicked();
}
void MainWindow::get_Handler(QString n)
{
    ui->textEdit->setText(n);
}

//Kun nappia btnPost painetaan, suoritetaan:
void MainWindow::post_Click_Handler()
{
    ptr_dll->post_Clicked();
}





