#include "popup.h"
#include "ui_popup.h"

popup::popup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::popup)
{
    ui->setupUi(this);
}

popup::~popup()
{
    delete ui;
}

void popup::on_btn_Close_clicked()
{
    this->close();
}

void popup::setText(const QString &text)
{
    ui->label->setText(text);
}
