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

public:
    RestDLL(QObject *parent);
    ~RestDLL();
signals:

public slots:

    void get_clicked();

    void on_post_clicked();
    void postSlot(QNetworkReply *reply);
    void getSlot(QNetworkReply *reply);

private slots:

private:
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;


};

#endif // RESTDLL_H
