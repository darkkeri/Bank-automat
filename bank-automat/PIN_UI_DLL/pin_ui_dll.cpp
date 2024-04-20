#include "pin_ui_dll.h"

PIN_UI_DLL::PIN_UI_DLL(QWidget *parent):
    QDialog(parent),
    ui(new Ui::pinUI)
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
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QWidget::close);
    timer->start(10000);
}

PIN_UI_DLL::~PIN_UI_DLL()
{
    delete ui;
}

void PIN_UI_DLL::handleClick()
{
    QString number = ui->lineEdit->text();
    emit sendNumberToMainWindow(number);
    //number.toUShort()
}

void PIN_UI_DLL::clearClicked()
{
    ui->lineEdit->clear();
}

void PIN_UI_DLL::numberClickedHandler()
{
    QPushButton *button = (QPushButton *) sender();
    QString number = button->text();
    ui->lineEdit->setText(ui->lineEdit->text() + number);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    timer->start(10000);
}



