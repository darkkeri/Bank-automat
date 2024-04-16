#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>

namespace Ui {
class bankwindow;
}

class bankwindow : public QDialog
{
    Q_OBJECT

public:
    explicit bankwindow(QWidget *parent = nullptr);
    ~bankwindow();

private slots:
    void on_Button1_clicked();

    void on_Button2_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();

    void on_Button5_clicked();

    void on_Button6_clicked();

private:
    Ui::bankwindow *ui;

    short buttonMode = 0;

    void modeChange(short);

    void cardCheck();

signals:
    void restartSignal();
};

#endif // BANKWINDOW_H
