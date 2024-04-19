#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QThread>
#include "bankwindow.h"
#include "RestDLL/restdll.h"
#include "RFID_DLL/rfid_dll.h"

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

private:
    Ui::MainWindow *ui;
    bool cardSignal;
    bool pinSignal;

    bankwindow *secWindow;
    RFID_DLL *ptr_rfid;

private slots:
    void cardSignalHandler(); //Delete after testing is done
    void on_OKButton_clicked(); //Delete after testing is done

    void secondViewOpen();
    void cardHandler(QString&);
    void pinHandler(QString&);
    void restart();

    void on_debitButton_clicked();

    void on_creditButton_clicked();

    void on_OFFButton_clicked();

signals:
    void secondViewOpenSignal();

};
#endif // MAINWINDOW_H
