#include "restdll.h"

#include "environment.h"

RestDLL::RestDLL(QObject *parent):QObject(parent)
{
    qDebug()<<"DLL luotu";
}

RestDLL::~RestDLL()
{
    qDebug()<<"RESTDLL RÄJÄHTI";
}

void RestDLL::setupGetConnection(int switchCase, int id)
{

    QString urlAddress = "/logs/";
    QString stringID = QString::number(accountID);
    if(accountID == 0) stringID="";
    switch (switchCase){
    case 1:
        urlAddress = "/logs/";
        break;
    case 2:
        urlAddress = "/cards/";
        break;
    case 3:
        urlAddress = "/account/";
        break;
    case 4:
        urlAddress = "/account/";
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
                this, SLOT(getLogs(QNetworkReply*)));
        qDebug()<<"getLogs!";
        break;
    case 2:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getCards(QNetworkReply*)));
        qDebug()<<"getCards!";
        break;
    case 3:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getAccount(QNetworkReply*)));
        qDebug()<<"getAccount!";
        break;
    case 4:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getBalance(QNetworkReply*)));
        qDebug()<<"getBalance!";
        break;
    default:
        qDebug()<<"Error";
        break;
    }
    reply = getManager->get(request);
}

void RestDLL::pinCompare()
{
    QString site_url=Environment::getBaseURL()+"/cards";
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

void RestDLL::test()
{
    QString urlAddress = "/logs/";
    QString site_url=Environment::getBaseURL()+urlAddress;
    qDebug()<<site_url;
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);
    reply = getManager->get(request);
    columnName[0]="idLogs";
    columnName[1]="date";
    columnName[2]="event";
    columnName[3]="amount";
    columnName[4]="idAccount";
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+json_obj[columnName[1]].toString()+" | "+json_obj[columnName[2]].toString()+
               " | "+json_obj[columnName[3]].toString()+" | "+QString::number(json_obj[columnName[4]].toInt())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

    reply->deleteLater();
    getManager->deleteLater();



}

void RestDLL::getBalance(QNetworkReply *reply)
{
    qDebug()<<"GETBALANCESSA!";
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance=json_obj["balance"].toString();
    qDebug()<<balance;
    //get qstring menee get_handleriin exessä:
    emit getResult(balance);
    reply->deleteLater();
    getManager->deleteLater();

}




void RestDLL::checkBalance(float nostomaara, int id)
{
    setupGetConnection(4,id);


}


void RestDLL::getCards(QNetworkReply *reply)
{
    columnName[0]="idCards";
    columnName[1]="cardnumber";
    columnName[2]="pincode";
    columnName[3]="type";
    columnName[4]="tries";
    columnName[5]="active";
    columnName[6]="creditlimit";
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString cardData=json_obj["cardnumber"].toString()+" | "+json_obj["pincode"].toString()+" | "+json_obj["type"].toString()+
                       " | "+QString::number(json_obj["tries"].toInt())+" | "+QString::number(json_obj["active"].toInt());

    qDebug()<<cardData;
    //get qstring menee get_handleriin exessä:
    emit getResult(cardData);

    reply->deleteLater();
    getManager->deleteLater();
}

void RestDLL::post_Clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert(columnName[1],"943857348957");
    jsonObj.insert(columnName[2],"7654");
    jsonObj.insert(columnName[3],"1");
    jsonObj.insert(columnName[4],0);
    jsonObj.insert(columnName[5],1);
    jsonObj.insert(columnName[6],"52345");

    QString site_url=Environment::getBaseURL()+"/cards";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(postSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}
void RestDLL::getLogs(QNetworkReply *reply){
    columnName[0]="idLogs";
    columnName[1]="date";
    columnName[2]="event";
    columnName[3]="amount";
    columnName[4]="idAccount";
    response_data=reply->readAll();
    //qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+json_obj[columnName[1]].toString()+" | "+json_obj[columnName[2]].toString()+
               " | "+json_obj[columnName[3]].toString()+" | "+QString::number(json_obj[columnName[4]].toInt())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

    reply->deleteLater();
    getManager->deleteLater();
}




void RestDLL::postLogs(QString date, QString event, float amount, int idAccount)
{
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

QString RestDLL::data_seperator(QString data)
{

}

void RestDLL::postSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    emit getResult(response_data);
    reply->deleteLater();
    postManager->deleteLater();
}

void RestDLL::getAccount(QNetworkReply *reply)
{
    columnName[0]="idAccount";
    columnName[1]="balance";
    columnName[2]="accountnumber";
    columnName[3]="accounttype";
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString accountData = json_obj["balance"].toString()+" | "+json_obj["accountnumber"].toString()+
                          " | "+QString::number(json_obj["accounttype"].toInt());



    // foreach(const QJsonValue &value, json_array) {
    //     QJsonObject json_obj = value.toObject();
    //     get+=QString::number(json_obj[columnName[0]].toInt())+" | "+json_obj[columnName[1]].toString()+
    //            " | "+json_obj[columnName[2]].toString()+" | "+QString::number(json_obj[columnName[3]].toInt())+"\r";
    // }
    qDebug()<<accountData;
    //get qstring menee get_handleriin exessä:
    emit getResult(accountData);

    reply->deleteLater();
    getManager->deleteLater();
}


void RestDLL::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void RestDLL::checkPin(QString cardnumber, QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("cardnumber", cardnumber);
    jsonObj.insert("pincode", pincode);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

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
            //Tähän true signaali mainiin

            setWebToken(response_data);

        }
        else {
            //Tähän false signaali mainiin
            //msgBox.setText("Väärä pinkoodi");
            //msgBox.exec();
        }
    }
}
