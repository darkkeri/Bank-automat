#ifndef PINUI_H
#define PINUI_H

#include <QDialog>
#include <QDebug>
#include <QTimer>

namespace Ui {
class pinUI;
}

class pinUI : public QDialog
{
    Q_OBJECT

public:
    explicit pinUI(QWidget *parent = nullptr);
    ~pinUI();

signals:
    void sendNumberToMainWindow(short);

private slots:
    void handleClick();
    void clearClicked();
    void numberClickedHandler();

private:
    Ui::pinUI *ui;
    QTimer *timer;
};

#endif // PINUI_H
