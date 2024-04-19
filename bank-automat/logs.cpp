#include "logs.h"

Logs::Logs()
{

}

QString Logs::getType() const
{
    return type;
}

void Logs::setType(const QString &newType)
{
    type = newType;
}

QString Logs::getAmount() const
{
    return amount;
}

void Logs::setAmount(const QString &newAmount)
{
    amount = newAmount;
}

QString Logs::getDate() const
{
    return date;
}

void Logs::setDate(const QString &newDate)
{
    date = newDate;
}
