#ifndef PINUIDLL_H
#define PINUIDLL_H

#include "PINUIDLL_global.h"
#include <QDialog>
#include <QDebug>
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
    void wrongPin();

public slots:
    void closePin();
signals:
    void sendNumberToMainWindow(QString);

private slots:
    void handleClick();
    void clearClicked();
    void numberClickedHandler();

private:
    Ui::PINUIDLL *ui;
    QTimer *timer;
    QMessageBox *pinmsg;
};

#endif // PINUIDLL_H
