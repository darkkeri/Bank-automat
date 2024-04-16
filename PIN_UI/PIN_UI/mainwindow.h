#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rfidcardreader.h"
#include "pinui.h"
#include <QTimer>
#include "popup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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



private:
    Ui::MainWindow *ui;
    rfidCardReader * reader;
    pinUI * pinReader;
    popup * messageWindow;


    short cardNumber,pinNumber,attemptsLeft=3;
    short correctNumber=1234;
    short correctPin = 1111;
};
#endif // MAINWINDOW_H
