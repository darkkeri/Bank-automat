#ifndef RFIDCARDREADER_H
#define RFIDCARDREADER_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class rfidCardReader;
}

class rfidCardReader : public QDialog
{
    Q_OBJECT

public:
    explicit rfidCardReader(QWidget *parent = nullptr);
    ~rfidCardReader();

signals:
    void sendNumberToMainWindow(short);

private slots:
    void handleClick();

private:
    Ui::rfidCardReader *ui;
};

#endif // RFIDCARDREADER_H
