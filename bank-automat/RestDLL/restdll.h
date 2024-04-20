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

    void setWebToken(const QByteArray &newWebToken);

    void setAccountID(int newAccountID);

    void setAccountBalance(int newAccountBalance);

signals:
    void getResult(QString);
    void pinCheckSignal(bool);
public slots:

    void setupGetConnection(int switchCase, int id);
    void post_Clicked();
    void checkPin(QString idCard, QString pincode);
    void pinCompare();
<<<<<<< HEAD
    void setAccountID(QString cardID, QString accountType);
=======
    void getAccountID(QString cardID, QString accountType);
    void test();
    void checkBalance(float nostomaara,int id);
>>>>>>> abf009fd28fcd2ac1e9e94130abb42f16e05a57e
private slots:
    void getBalance(QNetworkReply *reply);

    void postSlot(QNetworkReply *reply);
    void getCards(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void getAccount(QNetworkReply *reply);

    void getLogs(QNetworkReply *reply);

    void postLogs(QString date, QString event, float amount, int idAccount);
    QString data_seperator(QString data);


    void accountIdSlot(QNetworkReply *reply);
private:

    int accountID = 3;
    int cardsID = 1;
    int accountBalance;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *accountManager;

    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray webToken;
    QMessageBox msgBox;

    QString columnName[10];


};

#endif // RESTDLL_H
