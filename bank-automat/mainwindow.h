#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QThread>
#include "bankwindow.h"

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

private slots:
    void cardSignalHandler();
    void secondViewOpen();

    void on_OKButton_clicked();

signals:
    void secondViewOpenSignal();

};
#endif // MAINWINDOW_H
