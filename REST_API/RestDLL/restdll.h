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

    void get_Clicked();
    void post_Clicked();
signals:
    void getResult(QString);
public slots:



private slots:

    void postSlot(QNetworkReply *reply);
    void getSlot(QNetworkReply *reply);

private:

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // RESTDLL_H
