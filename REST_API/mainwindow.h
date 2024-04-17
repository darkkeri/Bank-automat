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
    void get_Handler(QString);

    void on_btnGet_clicked();
    void on_BtnLogin_clicked();

private:
    Ui::MainWindow *ui;
    RestDLL *ptr_dll;
};
#endif // MAINWINDOW_H
