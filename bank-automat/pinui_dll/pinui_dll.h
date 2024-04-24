#ifndef PINUI_DLL_H
#define PINUI_DLL_H

#include "pinuidll_global.h"
#include <QDialog>
#include <QDebug>
#include <QTimer>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class PINUI_DLL_EXPORT Pinui_dll;

}

class PINUI_DLL_EXPORT Pinui_dll : public QDialog
{
    Q_OBJECT
public:
    explicit Pinui_dll(QWidget *parent = nullptr);
    ~Pinui_dll();

signals:
    void sendNumberToMainWindow(QString);

private slots:
    void handleClick();
    void clearClicked();
    void numberClickedHandler();

private:
    Ui::Pinui_dll *ui;
    QTimer *timer;
};

#endif // PINUI_DLL_H
