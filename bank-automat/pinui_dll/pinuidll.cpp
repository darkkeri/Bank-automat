#include "pinuidll.h"
#include "ui_pinuidll.h"

PINUIDLL::PINUIDLL(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PINUIDLL)
{

    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(handleClick()));
    connect(ui->btn_0,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_1,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_2,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_3,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_4,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_5,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_6,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_7,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_8,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_9,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn_clear,SIGNAL(clicked(bool)),this,SLOT(clearClicked()));

    pinmsg = new QMessageBox(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this,SLOT(closePin()), Qt::UniqueConnection);
}

PINUIDLL::~PINUIDLL()
{
    delete ui;
}

void PINUIDLL::startTimer()
{
    timer->start(15000);
}

void PINUIDLL::wrongPin(QString tries)
{
    if(tries.toInt() == 3){
        pinmsg->setText("PIN-koodi meni väärin");
        pinmsg->setInformativeText("Liian monta yritystä, kortti lukittu");
        pinmsg->setInformativeText("Ota yhteyttä pankkiisi");
        pinmsg->exec();
    } else {
        pinmsg->setText("PIN-koodi meni väärin");
        pinmsg->setInformativeText("Yrityksiä jäljellä: "+tries);
        pinmsg->exec();
    }
}

void PINUIDLL::withdrawUI()
{
    withdrawMode = true;
    ui->label->setText("Syötä nostosumma");
    startTimer();
    this->exec();
}

void PINUIDLL::handleClick()
{
    QString number = ui->lineEdit->text();
        if(withdrawMode == false){
            emit sendNumberToMainWindow(number);
            closePin();
        } else if(withdrawMode == true){
            if(number.toInt() % 10 == 0){
                withdrawMode = false;
                emit sendNumberToBankWindow(number);
                closePin();
            } else {
                pinmsg->setText("Nosto epäonnistui");
                pinmsg->setInformativeText("Syöttämäsi summa ei ole jaollinen kymmenellä");
                pinmsg->exec();
            }
        }
    ui->lineEdit->clear();
    //number.toUShort()
}

void PINUIDLL::clearClicked()
{
    ui->lineEdit->clear();
    startTimer();
}

void PINUIDLL::numberClickedHandler()
{
    QPushButton *button = (QPushButton *) sender();
    QString number = button->text();
    ui->lineEdit->setText(ui->lineEdit->text() + number);
    if(withdrawMode == false){
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
    startTimer();
}

void PINUIDLL::closePin()
{
    close();
}
