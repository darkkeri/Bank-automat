#ifndef CARDREADER_H
#define CARDREADER_H

#include <QDialog>

namespace Ui {
class cardReader;
}

class cardReader : public QDialog
{
    Q_OBJECT

public:
    explicit cardReader(QWidget *parent = nullptr);
    ~cardReader();

private:
    Ui::cardReader *ui;
};

#endif // CARDREADER_H
