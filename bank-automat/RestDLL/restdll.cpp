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

void RestDLL::setupGetConnection(int switchCase)
{
    qDebug()<<"setupGetConnection ran";
    QString urlAddress;
    QString stringID;

    switch (switchCase){
    case 1:
        //HAETAAN LOGIT idAccountin perusteella
        urlAddress = "/logs/";
        stringID = QString::number(accountID);  //getLogs
        if(accountID == 0) stringID="";
        break;
    case 2:
        //CARDS-TAULUN TIEDOT idCards perusteella
        urlAddress = "/cards/";
        stringID = QString::number(cardsID);        //getCards
        if(cardsID == 0) stringID="";
        break;
    case 3:
        //ACCOUNT TIEDOT idAccountin perusteella
        urlAddress = "/account/";
        stringID = QString::number(accountID);      //getAccount
        if(accountID == 0) stringID="";
        break;
    case 5:
        //CARDSin tyypin tarkistus: onko multicard (palauttaa bool)
        urlAddress = "/cards/";
        stringID = QString::number(cardsID);    //MulticardCheck
        if(cardsID == 0) stringID="";
        break;
    default: qDebug()<<"URL error"; break;
    }

    QString site_url=Environment::getBaseURL()+urlAddress+stringID;
    qDebug()<<site_url;
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    // hasu weebtoken??!?!?!?
    // QByteArray myToken="Bearer "+webToken;
    // request.setRawHeader(QByteArray("Authorization"),(myToken));

    getManager = new QNetworkAccessManager(this);
    switch (switchCase){
    case 1:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getLogsSlot(QNetworkReply*)));
        qDebug()<<"getLogs!";
        break;
    case 2:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getCardsSlot(QNetworkReply*)));
        qDebug()<<"getCards!";
        break;
    case 3:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getAccountSlot(QNetworkReply*)));
        qDebug()<<"getAccount!";
        break;
    case 5:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(multicardCheckSlot(QNetworkReply*)));
        qDebug()<<"multicardcheck!";
        break;
    default:
        qDebug()<<"Error";
        break;
    }
    reply = getManager->get(request);
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
    //get qstring menee get_handleriin exessä:
    setAccountBalance(balance.toInt()); //Hmm.. en tiedä pitäskö muuttaa -Mikael
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
    qDebug()<<site_url;
    creditlimitManager = new QNetworkAccessManager(this);
    connect(creditlimitManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getCreditlimitSlot(QNetworkReply*)));
    reply = creditlimitManager->get(request);
}
void RestDLL::getCreditlimitSlot(QNetworkReply *reply)
{
    qDebug()<<"GETCREDITLIMITSLOTISA";
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
    QString site_url=Environment::getBaseURL()+"/cards/"+stringID;
    QNetworkRequest request((site_url));
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));

    qDebug()<<site_url;
    getTriesManager = new QNetworkAccessManager(this);
    connect(getTriesManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getTriesSlot(QNetworkReply*)));
    reply = getTriesManager->get(request);
}
void RestDLL::getTriesSlot(QNetworkReply *reply)
{

    qDebug()<<"GetTriesSlot!";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString tries=QString::number(json_obj["tries"].toInt());
    qDebug()<<tries;

    emit getTriesSignal(tries);
    reply->deleteLater();
    getTriesManager->deleteLater();
}

void RestDLL::putTries()
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);

    QString site_url="http://localhost:3000/cards/1";
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

void RestDLL::getCardsSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString cardData=json_obj["cardnumber"].toString()+" | "+json_obj["pincode"].toString()+" | "+json_obj["type"].toString()+
                       " | "+QString::number(json_obj["tries"].toInt())+" | "+QString::number(json_obj["active"].toInt())+
                       " | "+json_obj["creditlimit"].toString();

    qDebug()<<cardData;
    //get qstring menee get_handleriin exessä:
    emit getCardsSignal(cardData);

    reply->deleteLater();
    getManager->deleteLater();
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
    getManager->deleteLater();
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
    //get qstring menee get_handleriin exessä:
    emit getLogsSignal(get);

    reply->deleteLater();
    getManager->deleteLater();
}

void RestDLL::setAccountBalance(int newAccountBalance)
{
    accountBalance = newAccountBalance;
}

void RestDLL::getAccountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"getAccountSlot ran";
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString accountData = json_obj["balance"].toString()+" | "+json_obj["accountnumber"].toString()+
                          " | "+QString::number(json_obj["accounttype"].toInt());
    qDebug()<<accountData;
    emit getAccountSignal(accountData);

    reply->deleteLater();
    getManager->deleteLater();
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
    QString site_url="http://localhost:3000/cardsId";
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
    foreach(const QJsonValue &value, json_array) {      //Ei toimi jostain syystä objektilla
        QJsonObject json_obj = value.toObject();        //joten arrayllä mennään
        cardsIdData+=QString::number(json_obj["idCards"].toInt());
    }
    qDebug()<<"cardsIdSlot ran with:"<<cardsIdData;
    cardsID = cardsIdData.toInt();
    reply->deleteLater();
    cardsIDManager->deleteLater();
    setupGetConnection(5); //cardtypecheck
}

void RestDLL::accountIDbyType(QString accountType) //Gets accountid by cardID and accountType
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);
    jsonObj.insert("accounttype", accountType);

    QString site_url="http://localhost:3000/accountId";
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
    foreach(const QJsonValue &value, json_array) {      //Ei toimi jostain syystä objektilla
        QJsonObject json_obj = value.toObject();        //joten arrayllä mennään
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

    QString site_url="http://localhost:3000/account/"+QString::number(accountID);
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

    reply->deleteLater();
    nostoManager->deleteLater();

}



void RestDLL::checkPin(QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);
    jsonObj.insert("pincode", pincode);

    QString site_url="http://localhost:3000/login";
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
        //msgBox.setText("Virhe tietokantayhteydessä");
        //msgBox.exec();
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
            //msgBox.setText("Väärä pinkoodi");
            //msgBox.exec();
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}
