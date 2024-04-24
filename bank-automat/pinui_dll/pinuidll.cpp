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

void PINUIDLL::wrongPin()
{
    pinmsg->setText("PIN-koodi meni vaarin. Yrityksia jaljella: ");
    pinmsg->setInformativeText("Yrityksia jaljella: ");
    pinmsg->setText("Yrityksia jaljella: ");
    pinmsg->exec();
}

void PINUIDLL::handleClick()
{
    QString number = ui->lineEdit->text();
    emit sendNumberToMainWindow(number);
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
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    startTimer();
}

void PINUIDLL::closePin()
{
    close();
}
