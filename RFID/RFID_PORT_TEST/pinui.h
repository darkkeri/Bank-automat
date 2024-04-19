#ifndef PINUI_H
#define PINUI_H

#include <QDialog>

namespace Ui {
class pinUI;
}

class pinUI : public QDialog
{
    Q_OBJECT

public:
    explicit pinUI(QWidget *parent = nullptr);
    ~pinUI();

private:
    Ui::pinUI *ui;
};

#endif // PINUI_H
