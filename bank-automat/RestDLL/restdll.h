#ifndef RESTDLL_H
#define RESTDLL_H
#include <QObject>
#include "RestDLL_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QMessageBox>


class RESTDLL_EXPORT RestDLL : public QObject
{
    Q_OBJECT
public:
    RestDLL(QObject *parent);
    ~RestDLL();

signals:
    void getResult(QString);
public slots:

    void get_Clicked(int id,int switchCase);
    void post_Clicked();
    void checkPin(QString idCard, QString pincode);
    void pinCompare();
private slots:
    QString getBalance(QNetworkReply *reply);
    void checkBalance(float nostomaara);
    void postSlot(QNetworkReply *reply);
    void getCards(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void getAccount(QNetworkReply *reply);

    void getLogs(QNetworkReply *reply);

    void postLogs(QString date, QString event, float amount, int idAccount);
    QString data_seperator(QString data);


private:

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QString columnName[10];


};

#endif // RESTDLL_H
