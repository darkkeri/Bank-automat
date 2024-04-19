#ifndef LOGS_H
#define LOGS_H

#include <QString>


class Logs
{
public:
    Logs();

    QString getType() const;
    void setType(const QString &newType);

    QString getAmount() const;
    void setAmount(const QString &newAmount);

    QString getDate() const;
    void setDate(const QString &newDate);

private:
    QString type;
    QString amount;
    QString date;
};

#endif // LOGS_H
