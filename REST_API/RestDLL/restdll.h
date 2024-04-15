#ifndef RESTDLL_H
#define RESTDLL_H
#include <QObject>
#include "RestDLL_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>


class RESTDLL_EXPORT RestDLL : public QObject
{
    Q_OBJECT
public:
    RestDLL(QObject *parent);
    ~RestDLL();


signals:
    void getResult(QString);
public slots:

    void get_Clicked();
    void post_Clicked();

    void pinCompare();
private slots:

    void postSlot(QNetworkReply *reply);
    void getSlot(QNetworkReply *reply);

private:

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;


    QString columnName[10];


};

#endif // RESTDLL_H
