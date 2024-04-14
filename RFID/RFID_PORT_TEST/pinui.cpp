#include "pinui.h"
#include "ui_pinui.h"

#include <QDebug>

pinUI::pinUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pinUI)
{
    ui->setupUi(this);
}

pinUI::~pinUI()
{
    qDebug()<<"Pin UI Dekonstruktor";
    delete ui;
}
