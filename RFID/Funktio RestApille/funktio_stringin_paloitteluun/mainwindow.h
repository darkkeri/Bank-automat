#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QString data = "4 | 2022-01-01T06:00:00.000Z | testievent | 200 | 1 ";
    QString event;
    QString amount;
    QString dateStart;
    QString dateEnd;
    QString date1;
    QString date2;
    QString finalDate;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
