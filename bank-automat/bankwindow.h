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

private:
    Ui::bankwindow *ui;
};

#endif // BANKWINDOW_H
