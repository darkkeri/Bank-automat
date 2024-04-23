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
    QString urlAddress = "/logs/";
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
    case 4:
        //ACCOUNTIN balance sarake idAccountin perusteella
        urlAddress = "/account/";
        stringID = QString::number(accountID);      //getBalance
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
    case 4:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getBalanceSlot(QNetworkReply*)));
        qDebug()<<"getBalance!";
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


void RestDLL::getBalanceSlot(QNetworkReply *reply)      //Kutsutaan setupgetconnection(4)
{
    qDebug()<<"getBalanceSlot ran";
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance=json_obj["balance"].toString();
    qDebug()<<balance;
    //get qstring menee get_handleriin exessä:
    setAccountBalance(balance.toInt()); //Hmm.. en tiedä pitäskö muuttaa -Mikael
    emit getBalanceSignal(balance);
    reply->deleteLater();
    getManager->deleteLater();

}




void RestDLL::checkBalance(int id) // WIP tuleva saldon miinustus systeemi noston tapahtuessa
{                                   // (jos on järkevää toteuttaa proseduurin sijaan)
    qDebug()<<"fasfa";

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
    columnName[0]="idLogs";
    columnName[1]="date";
    columnName[2]="event";
    columnName[3]="amount";
    columnName[4]="idAccount";
    response_data=reply->readAll();
    qDebug()<<"getLogsSlot ran";
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+json_obj[columnName[1]].toString()+
               " | "+json_obj[columnName[2]].toString()+" | "+json_obj[columnName[3]].toString()+
               " | "+QString::number(json_obj[columnName[4]].toInt())+"\r";
    }
    //get qstring menee get_handleriin exessä:
    emit getLogsSignal(get);

    reply->deleteLater();
    getManager->deleteLater();
}




void RestDLL::postLogs(QString date, QString event, float amount, int idAccount) //kutsutaan mainista
{                                                                               // WIP: uuden login postaaminen tietokantaan
    QJsonObject jsonObj;
    jsonObj.insert(columnName[1],"2023-04-01 09:03:00");
    jsonObj.insert(columnName[2],"testinges");
    jsonObj.insert(columnName[3],"20.45");
    jsonObj.insert(columnName[4],2);
    QString site_url=Environment::getBaseURL()+"/logs";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(postSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::setAccountBalance(int newAccountBalance)
{
    accountBalance = newAccountBalance;
}

void RestDLL::postSlot(QNetworkReply *reply)    //turha, malli
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    emit getResult(response_data);
    reply->deleteLater();
    postManager->deleteLater();
}

void RestDLL::getAccountSlot(QNetworkReply *reply)
{
    columnName[0]="idAccount";
    columnName[1]="balance";
    columnName[2]="accountnumber";
    columnName[3]="accounttype";
    response_data=reply->readAll();
    qDebug()<<"getAccountSlot ran";
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString accountData = json_obj["balance"].toString()+" | "+json_obj["accountnumber"].toString()+
                          " | "+QString::number(json_obj["accounttype"].toInt());
    qDebug()<<accountData;
    //get qstring menee get_handleriin exessä:
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
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    qDebug()<<"getCardID ran";
    cardsIDManager = new QNetworkAccessManager(this);
    connect(cardsIDManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(cardsIdSlot(QNetworkReply*)));

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


void RestDLL::checkPin(QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardsID);
    jsonObj.insert("pincode", pincode);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*))
            , this, SLOT(loginSlot(QNetworkReply*)));

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
            //Tähän false signaali mainiin
            //msgBox.setText("Väärä pinkoodi");
            //msgBox.exec();
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}
