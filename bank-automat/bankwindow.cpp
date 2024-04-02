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
