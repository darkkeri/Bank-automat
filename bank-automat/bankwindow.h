#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include <QList>
#include <QStandardItem>
#include <QString>
#include "RestDLL/restdll.h"
#include "logs.h"

namespace Ui {
class bankwindow;
}

class bankwindow : public QDialog
{
    Q_OBJECT

public:
    explicit bankwindow(QWidget *parent = nullptr);
    ~bankwindow();
    void openWindow();

private slots:
    void on_Button1_clicked();

    void on_Button2_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();

    void on_Button5_clicked();

    void on_Button6_clicked();

    void logsHandler(QString rawlogs);

    void on_pushButton_clicked();

private:
    Ui::bankwindow *ui;

    RestDLL *ptr_restb;

    short buttonMode = 0; //Changes mode of mainmenu

    //Logs editor
    int amountOfLogs;
    bool logFlag = false;
    QString oneLog;
    QString event;
    QString amount;
    QString dateStart;
    QString dateEnd;
    QString date1;
    QString date2;
    QString finalDate;
    //
    QVector<QString> oneLogVector;
    QVector<QString> logDateVector;
    QVector<QString> logEventVector;
    QVector<QString> logAmountVector;

    QList<Logs> logList;

    void modeChange(short);

    void cardCheck();

    void closeWindow();

    void manageLogTable(short);

    int logStage;
signals:
    void restartSignal();
};

#endif // BANKWINDOW_H
