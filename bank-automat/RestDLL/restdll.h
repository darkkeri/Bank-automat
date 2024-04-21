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
    void getResult(QString); //need to delete someday, only used in test or other stuff but code wont build without it
    void getBalanceSignal(QString);
    void getLogsSignal(QString);
    void getAccountSignal(QString);//Not in use but Arttu said it works
    void getCardsSignal(QString);//Not in use but Arttu said it works

    void pinCheckSignal(bool); //WORKS, need to add webtoken later
public slots:

    void setupGetConnection(int switchCase);
    void post_Clicked();
    void checkPin(QString idCard, QString pincode);
    void pinCompare();
    void getAccountID(QString cardID, QString accountType);
    void checkBalance(float nostomaara,int id);
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
