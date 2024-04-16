#include "rfidcardreader.h"
#include "ui_rfidcardreader.h"

rfidCardReader::rfidCardReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rfidCardReader)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(handleClick()));
}

rfidCardReader::~rfidCardReader()
{
    //delete ui;
    qDebug()<<"Deleting automatically rfidCardReader object";
}

void rfidCardReader::handleClick()
{
    QString number = ui->lineEdit->text();
    emit sendNumberToMainWindow(number.toUShort());
}
