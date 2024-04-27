#ifndef PINUIDLL_H
#define PINUIDLL_H

#include "PINUIDLL_global.h"
#include <QDialog>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class PINUIDLL;

}

class PINUIDLL : public QDialog
{
    Q_OBJECT
public:
    explicit PINUIDLL(QWidget *parent = nullptr);
    ~PINUIDLL();
    void startTimer();
    void wrongPin(QString);
    void withdrawUI();

public slots:
    void closePin();
    void clearClicked();
signals:
    void sendNumberToMainWindow(QString);
    void sendNumberToBankWindow(QString);

private slots:
    void handleClick();
    void numberClickedHandler();

private:
    Ui::PINUIDLL *ui;
    QTimer *timer;
    QMessageBox *pinmsg;
    bool withdrawMode = false;
};

#endif // PINUIDLL_H
