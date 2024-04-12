#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "restdll.h"

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

    void get_Click_Handler();
    void post_Click_Handler();
    void get_Handler(QString);

private:
    Ui::MainWindow *ui;

    RestDLL *ptr_dll;
};
#endif // MAINWINDOW_H
