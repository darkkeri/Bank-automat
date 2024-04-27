#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include <QList>
#include <QStandardItem>
#include <QString>
#include "RestDLL/restdll.h"
#include "logs.h"
#include "pinuidll.h"

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
    void setCardType(QString);
    void startTimer();

private slots:
    void on_Button1_clicked();

    void on_Button2_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();

    void on_Button5_clicked();

    void on_Button6_clicked();

    void logsHandler(QString rawlogs);
    void balanceHandler(QString);
    void cardsHandler(QString);
    void withdrawHandler(QString);
    void customWithdrawHandler(QString);
    void closeWindow();


private:
    Ui::bankwindow *ui;

    RestDLL *ptr_restb;

    short buttonMode = 0; //Changes mode of mainmenu
    QString cardType;

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

    QList<Logs> logList;

    void modeChange(short);
    void manageLogTable(short);

    int logStage;
    QTimer closeTimer;
    PINUIDLL *ptr_wdUI;
signals:
    void restartSignal();
};

#endif // BANKWINDOW_H
