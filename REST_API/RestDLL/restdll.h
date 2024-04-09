#ifndef RESTDLL_H
#define RESTDLL_H

#include "RestDLL_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class RESTDLL_EXPORT RestDLL : public QObject
{
public:
    RestDLL();
private slots:
    void on_get_clicked();

    void on_post_clicked();

    void postSlot(QNetworkReply *reply);
    void getSlot(QNetworkReply *reply);
private:
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;


};

#endif // RESTDLL_H
