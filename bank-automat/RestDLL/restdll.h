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

    void setAccountBalance(int newAccountBalance);

    int getAccountID() const;

signals:
    void cardTypeSignal(QString); //multicard
    void getResult(QString);  //need to delete someday, only used in test or other stuff but code wont build without it
    void getBalanceSignal(QString); //OK
    void getLogsSignal(QString); //OK
    void pinCheckSignal(bool); //OK, need to add webtoken later
    void getWithdrawSignal(QString);


    void getAccountSignal(QString);//Not in use but Arttu said it works
    void getCardsSignal(QString);//Not in use but Arttu said it works
    void getCreditlimitSignal(QString);
    void getTriesSignal(QString);
public slots:

    void setupGetConnection(int switchCase);
    void getBalance();
    void checkPin(QString pincode);
    void nosto(QString amount);
    void getCardID(QString cardnumber);
    void accountIDbyType(QString accountType);

    void getCreditlimit();
    void getTries();
private slots:
    void getBalanceSlot(QNetworkReply *reply);

    void getCardsSlot(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void getAccountSlot(QNetworkReply *reply);
    void multicardCheckSlot(QNetworkReply *reply);
    void getLogsSlot(QNetworkReply *reply);
    void nostoSlot(QNetworkReply *reply);

    void cardsIdSlot(QNetworkReply *reply);
    void accountIdSlot(QNetworkReply *reply);

    void getCreditlimitSlot(QNetworkReply *reply);
    void getTriesSlot(QNetworkReply *reply);
private:
    // toinen singleton juttu
    static RestDLL* instance;
    QString name;
    //
    int accountID = 0;
    int cardsID = 0;
    int accountBalance;
    int triesamount;

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *cardsIDManager;
    QNetworkAccessManager *nostoManager;

    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *creditlimitManager;
    QNetworkAccessManager *triesManager;

    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray webToken;
    QMessageBox msgBox;

    QString columnName[10];

};

#endif // RESTDLL_H
