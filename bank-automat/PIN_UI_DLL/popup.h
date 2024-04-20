#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class popup;
}

class popup : public QDialog
{
    Q_OBJECT

public:
    explicit popup(QWidget *parent = nullptr);
    ~popup();
    void setText(const QString &text);

private slots:
    void on_btn_Close_clicked();

private:
    Ui::popup *ui;
};

#endif // POPUP_H
