#include "cardreader.h"
#include "ui_cardreader.h"
#include <QDebug>

cardReader::cardReader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cardReader)
{
    ui->setupUi(this);
}

cardReader::~cardReader()
{
    qDebug()<<"Tuhoutui automaattisesti";
    delete ui;
}
