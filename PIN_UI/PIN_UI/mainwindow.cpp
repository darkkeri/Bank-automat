#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_popup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(handleInsertCardClick()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInsertCardClick()
{
    reader = new rfidCardReader(this);
    connect(reader,SIGNAL(sendNumberToMainWindow(short)),this,SLOT(handleCardNumberRead(short)));
    reader->show();
}


void MainWindow::handleCardNumberRead(short num)
{
    ui->cardNumberLineEdit->setText(QString::number(num));
    qDebug()<<"Deleting reader object";
    delete reader;
    reader = nullptr;

    // Ja sitten luodaan pinUi olio
    pinReader = new pinUI(this);
    connect(pinReader,SIGNAL(sendNumberToMainWindow(short)),this,SLOT(handlePinNumberRead(short)));
    pinReader->show();
}

void MainWindow::handlePinNumberRead(short num)
{
    messageWindow = new popup(this);

    if (num == correctPin) {
        ui->pinNumberLineEdit->setText(QString::number(num));
        qDebug() << "Pin-koodi syötetty oikein. Suljetaan ikkuna.";
        messageWindow->setWindowTitle("PIN-koodi");
        messageWindow->setText("PIN-koodi meni oikein!");
        messageWindow->show();
        connect(messageWindow, SIGNAL(finished(int)), pinReader, SLOT(close()));
        // Näytä oikein syötetty pin-koodi pääikkunassa
    } else {
        qDebug() << "Pin-koodi väärin";
        attemptsLeft--;
        if (attemptsLeft > 0) {
            messageWindow->setWindowTitle("PIN-koodi");
            messageWindow->setText("PIN-koodi meni väärin. Yrityksiä jäljellä: " + QString::number(attemptsLeft));
            messageWindow->show();
            // Näytä virheviesti pin-koodin väärin menemisestä ja yritysten määrästä jäljellä
        } else {
            qDebug() << "Pin-koodi syötetty väärin kolme kertaa. Sulkemassa ikkunaa...";
            messageWindow->setWindowTitle("PIN-koodi");
            messageWindow->setText("PIN-koodi syötetty väärin 3 kertaa."
                                   " Suljetaan ikkuna");
            messageWindow->show();
            QTimer::singleShot(2000, pinReader, &QWidget::close); // Sulkee ikkunan 2 sekunnin kuluttua
        }
    }

    // Poista pinUI-olio vasta kun käyttäjä sulkee ikkunan
    QObject::connect(pinReader, &QObject::destroyed, this, []() {
        qDebug() << "pinUI-olio tuhottu";
    });
}


