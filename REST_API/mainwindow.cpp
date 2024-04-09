#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RestDLL olio;
    //t(restdll, SIGNAL(get(QString),
    //this, SLOT(getSlot(QString))
}

MainWindow::~MainWindow()
{
    delete ui;
}


