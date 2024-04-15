#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardreader.h"

#include <QDebug>
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleInsertCardClick();
    void handleCardNumberRead(short);
    void handlePinNumberRead(short);


    void on_buttonPortsInfo_clicked();

    void on_buttonOpenPort_clicked();

    void readData();

    void on_buttonSend_clicked();

private:
    Ui::MainWindow *ui;
    cardReader * readerPtr;

    QSerialPort *_serialPort;
    void loadPorts();
};
#endif // MAINWINDOW_H
