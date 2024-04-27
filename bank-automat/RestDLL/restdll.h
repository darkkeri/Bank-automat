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
    RestDLL();
    ~RestDLL();
    // singleton juttu
    static RestDLL* getInstance();
    QString getName() const;
    void setName(const QString &value);
    //
    void setWebToken(const QByteArray &newWebToken);

    int getAccountID() const;

signals:
    void cardTypeSignal(QString); //multicard
    void getBalanceSignal(QString); //OK
    void getLogsSignal(QString); //OK
    void pinCheckSignal(bool); //OK, need to add webtoken later
    void getWithdrawSignal(QString);
    void getCreditlimitSignal(QString);
    void getTriesSignal(QString);
public slots:

    void getLogs();
    void getBalance();
    void checkPin(QString pincode);
    void nosto(QString amount);
    void getCardID(QString cardnumber);
    void accountIDbyType(QString accountType);
    void checkCardType();
    void getCreditlimit();
    void getTries();
    void putTries(bool triesUnResettinator);             //Runnataan, kun käyttäjä on syöttänyt väärän pinkoodin.
                                                        // jos asetetaan true, lisätään yksi uusi yritys tietokantaan.
                                                        // muutoin resetoi tries-arvon nollaksi tietokannassa.

private slots:
    void getBalanceSlot(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void multicardCheckSlot(QNetworkReply *reply);
    void getLogsSlot(QNetworkReply *reply);
    void nostoSlot(QNetworkReply *reply);
    void cardsIdSlot(QNetworkReply *reply);
    void accountIdSlot(QNetworkReply *reply);
    void getCreditlimitSlot(QNetworkReply *reply);
    void getTriesSlot(QNetworkReply *reply);
    void putTriesSlot(QNetworkReply *reply);

private:
    // toinen singleton juttu
    static RestDLL* instance;
    QString name;
    //
    int accountID = 5;
    int cardsID;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *logsManager;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *cardsIDManager;
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *creditlimitManager;
    QNetworkAccessManager *getTriesManager;
    QNetworkAccessManager *putTriesManager;
    QNetworkAccessManager *cardTypeManager;


    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray webToken;
    QMessageBox msgBox;
};

#endif // RESTDLL_H
