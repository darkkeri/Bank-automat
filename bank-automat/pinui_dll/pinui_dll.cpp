#include "pinui_dll.h"
#include "ui_pinui_dll.h"

Pinui_dll::Pinui_dll(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Pinui_dll)
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
    //    timer = new QTimer(this);
    //    connect(timer, &QTimer::timeout, this, &QWidget::close);
    //    timer->start(10000);


}

Pinui_dll::~Pinui_dll()
{
    delete ui;
}

void Pinui_dll::handleClick()
{
    QString number = ui->lineEdit->text();
    emit sendNumberToMainWindow(number);
    //number.toUShort()
}

void Pinui_dll::clearClicked()
{
    ui->lineEdit->clear();
}

void Pinui_dll::numberClickedHandler()
{
    QPushButton *button = (QPushButton *) sender();
    QString number = button->text();
    ui->lineEdit->setText(ui->lineEdit->text() + number);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    //    timer->start(10000);
}
