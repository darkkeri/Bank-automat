#include "restdll.h"

#include "environment.h"

RestDLL::RestDLL():QObject()
{
    qDebug()<<"DLL luotu";
}

RestDLL::~RestDLL()
{
    qDebug()<<"RESTDLL RÄJÄHTI";
}

RestDLL* RestDLL::instance = nullptr;

RestDLL* RestDLL::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RestDLL();
    }

    return instance;
}

QString RestDLL::getName() const
{
    return name;
}

void RestDLL::setName(const QString &value)
{
    name = value;
}
void RestDLL::getBalance()
{
    QString stringID = QString::number(accountID);
    QString site_url=Environment::getBaseURL()+"/account/"+stringID;
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    qDebug()<<site_url;
    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getBalanceSlot(QNetworkReply*)));
    reply = balanceManager->get(request);
}
void RestDLL::getBalanceSlot(QNetworkReply *reply)
{
    qDebug()<<"getBalanceSlot ran";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance=json_obj["balance"].toString();
    qDebug()<<balance;
    emit getBalanceSignal(balance);
    reply->deleteLater();
    balanceManager->deleteLater();
}

void RestDLL::getCreditlimit(){
    QString stringID = QString::number(cardsID);
    QString site_url=Environment::getBaseURL()+"/cards/"+stringID;
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    creditlimitManager = new QNetworkAccessManager(this);
    connect(creditlimitManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getCreditlimitSlot(QNetworkReply*)));
    reply = creditlimitManager->get(request);
}
void RestDLL::getCreditlimitSlot(QNetworkReply *reply)
{
    qDebug()<<"GetCreditLimitSlot ran";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString creditlimit=json_obj["creditlimit"].toString();
    qDebug()<<creditlimit;
    emit getCreditlimitSignal(creditlimit);
    reply->deleteLater();
    creditlimitManager->deleteLater();
}

void RestDLL::getTries()
{
    QString stringID = QString::number(cardsID);
    QString site_url=Environment::getBaseURL()+"/cardtries/"+stringID;
    QNetworkRequest request((site_url));
    getTriesManager = new QNetworkAccessManager(this);
    connect(getTriesManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getTriesSlot(QNetworkReply*)));
    reply = getTriesManager->get(request);
}
void RestDLL::getTriesSlot(QNetworkReply *reply)
{
    qDebug()<<"GetTriesSlot ran";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString tries=QString::number(json_obj["tries"].toInt());
    qDebug()<<tries;
    emit getTriesSignal(tries);
    reply->deleteLater();
    getTriesManager->deleteLater();
}

void RestDLL::putTries(bool triesUnResettinator)
{
    QJsonObject jsonObj;
    jsonObj.insert("triesUnResettinator", triesUnResettinator);

    QString site_url=Environment::getBaseURL()+"/cardtries/"+QString::number(cardsID);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    putTriesManager = new QNetworkAccessManager(this);
    connect(putTriesManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(putTriesSlot(QNetworkReply*)));

    reply = putTriesManager->post(request, QJsonDocument(jsonObj).toJson());

}

void RestDLL::putTriesSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    putTriesManager->deleteLater();


}

void RestDLL::checkCardType()
{
    QJsonObject jsonObj;
    QString site_url=Environment::getBaseURL()+"/cardtype/"+QString::number(cardsID);
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    cardTypeManager = new QNetworkAccessManager(this);
    connect(cardTypeManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(multicardCheckSlot(QNetworkReply*)));

    reply = cardTypeManager->get(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::multicardCheckSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"multicardCheckSlot ran: "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString cardTypeData=json_obj["type"].toString();
    qDebug()<<cardTypeData;
    emit cardTypeSignal(cardTypeData);

    reply->deleteLater();
    cardTypeManager->deleteLater();
}

void RestDLL::getLogs(){
    QString site_url=Environment::getBaseURL()+"/logs/"+QString::number(accountID);
    qDebug()<<site_url;
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    logsManager = new QNetworkAccessManager(this);
    connect(logsManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getLogsSlot(QNetworkReply*)));
    reply = logsManager->get(request);
}

void RestDLL::getLogsSlot(QNetworkReply *reply){
    response_data=reply->readAll();
    qDebug()<<"getLogsSlot ran";
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj["idLogs"].toInt())+" | "+json_obj["date"].toString()+
               " | "+json_obj["event"].toString()+" | "+json_obj["amount"].toString()+
               " | "+QString::number(json_obj["idAccount"].toInt())+"\r";
    }
    emit getLogsSignal(get);

    reply->deleteLater();
    logsManager->deleteLater();
}

void RestDLL::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void RestDLL::getCardID(QString cardnumber)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    QString site_url=Environment::getBaseURL()+"/cardsId";
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    qDebug()<<"getCardID ran";
    cardsIDManager = new QNetworkAccessManager(this);
    connect(cardsIDManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardsIdSlot(QNetworkReply*)));

    reply = cardsIDManager->get(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::cardsIdSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString cardsIdData;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        cardsIdData+=QString::number(json_obj["idCards"].toInt());
    }
    qDebug()<<"cardsIdSlot ran with:"<<cardsIdData;
    cardsID = cardsIdData.toInt();
    reply->deleteLater();
    cardsIDManager->deleteLater();

    checkCardType();
}

void RestDLL::accountIDbyType(QString accountType) //Gets accountid by cardID and accountType
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);
    jsonObj.insert("accounttype", accountType);

    QString site_url=Environment::getBaseURL()+"/accountId";
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accountIdSlot(QNetworkReply*)));

    reply = accountManager->get(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::accountIdSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    //set current account id here
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString cardsIdData;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        cardsIdData+=QString::number(json_obj["idAccount"].toInt());
    }
    accountID = cardsIdData.toInt();
    qDebug()<<"account id set to->"<<accountID;
    reply->deleteLater();
    accountManager->deleteLater();
}

int RestDLL::getAccountID() const
{
    return accountID;
}

void RestDLL::nosto(QString amount)
{
    QJsonObject jsonObj;
    jsonObj.insert("amount", amount);
    QString site_url=Environment::getBaseURL()+"/account/"+QString::number(accountID);
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    nostoManager = new QNetworkAccessManager(this);
    connect(nostoManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(nostoSlot(QNetworkReply*)));
    reply = nostoManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::nostoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QString check = response_data;
    emit getWithdrawSignal(check);
    reply->deleteLater();
    nostoManager->deleteLater();
}



void RestDLL::checkPin(QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);
    jsonObj.insert("pincode", pincode);

    QString site_url=Environment::getBaseURL()+"/login";
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    //qDebug()<<response_data;
    if(response_data=="-4078" || response_data=="") {
        //Virhe tietokantayhteydessä
    }
    else {
        if(response_data!="false") {
            //Kirjautuminen onnistui
            //Kortti ID
            qDebug()<<"checkPin ran";
            emit pinCheckSignal(true);//Tähän true signaali mainiin

            setWebToken(response_data);

        }
        else {
            emit pinCheckSignal(false);
            //Tähän false signaali mainiin
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}
