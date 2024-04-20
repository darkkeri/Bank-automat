#ifndef PIN_UI_DLL_H
#define PIN_UI_DLL_H

#include <QDialog>
#include <QDebug>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

#include "PIN_UI_DLL_global.h"
#include "ui_pinui.h"

namespace Ui {
class PIN_UI_DLL;
}

class PIN_UI_DLL_EXPORT PIN_UI_DLL : public QDialog
{
    Q_OBJECT
public:
    PIN_UI_DLL(QWidget *parent = nullptr);
    ~PIN_UI_DLL();

signals:
    void sendNumberToMainWindow(QString);

private slots:
    void handleClick();
    void clearClicked();
    void numberClickedHandler();

private:
    Ui::pinUI *ui;
    QTimer *timer;
};

#endif // PIN_UI_DLL_H
