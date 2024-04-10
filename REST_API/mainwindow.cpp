#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptr_dll = new RestDLL(this);
    connect(ui->get,SIGNAL(clicked(bool)),
            this,SLOT(get_handler()));
    connect(ui->post,SIGNAL(clicked(bool)),
            this,SLOT(post_handler()));

    //t(restdll, SIGNAL(get(QString),
    //this, SLOT(getSlot(QString))
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::get_handler()
{
    ptr_dll->get_clicked();

    qDebug()<<"fasdfaf";
}

void MainWindow::post_handler()
{
    ptr_dll->on_post_clicked();

    qDebug()<<"jeejee hauskaa";
}


