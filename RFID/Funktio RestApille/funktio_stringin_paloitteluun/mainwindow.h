#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
    QString alldata = "4 | 2022-01-01T06:00:00.000Z | testievent | 200 | 1 ";
    QString event;
    QString amount;
    QString dateStart;
    QString dateEnd;
    QString date1;
    QString date2;
    QString finalDate;
    QVector<QString> logDateVector;
    QVector<QString> logEventVector;
    QVector<QString> LogAmountVector;

    QList<log> logList;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
