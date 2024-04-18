#include "restdll.h"

#include "environment.h"

RestDLL::RestDLL(QObject *parent):QObject(parent)
{
    qDebug()<<"DLL luotu";
}

RestDLL::~RestDLL()
{
    qDebug()<<"DLL RÄJÄHTI";
}

void RestDLL::get_Clicked(int id, int switchCase)
{
    qDebug()<<id;
    QString urlAddress = "/logs/";
    QString stringID = QString::number(id);
    if(id == 0) stringID="";
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
    getManager = new QNetworkAccessManager(this);
    switch (switchCase){
    case 1:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getLogs(QNetworkReply*)));
        qDebug()<<"YKKÖNEN";
        break;
    case 2:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getCards(QNetworkReply*)));
        qDebug()<<"KAKKONEN!";
        break;
    case 3:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getAccount(QNetworkReply*)));
        qDebug()<<"KOLMONEN!";
        break;
    case 4:
        connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getBalance(QNetworkReply*)));
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

QString RestDLL::getBalance(QNetworkReply *reply)
{
    columnName[0]="idAccount";
    columnName[1]="balance";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+QString::number(json_obj[columnName[1]].toDouble())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

    reply->deleteLater();
    getManager->deleteLater();
    return get;
}

void RestDLL::checkBalance(float nostomaara)
{

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
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+json_obj[columnName[1]].toString()+" | "+json_obj[columnName[2]].toString()+
               " | "+QString::number(json_obj[columnName[3]].toInt())+" | "+QString::number(json_obj[columnName[4]].toInt())+
               " | "+QString::number(json_obj[columnName[5]].toInt())+" | "+QString::number(json_obj[columnName[6]].toInt())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

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
        " | "+QString::number(json_obj[columnName[3]].toDouble())+" | "+QString::number(json_obj[columnName[4]].toInt())+"\r";
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

void RestDLL::checkPin(QString cardnumber, QString pincode)
{
    QJsonObject jsonObj;
    jsonObj.insert("idCards", cardnumber);
    jsonObj.insert("pincode", pincode);

    QString site_url="http://localhost:3000/cards";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

}

void RestDLL::getAccount(QNetworkReply *reply)
{
    columnName[0]="idAccount";
    columnName[1]="balance";
    columnName[2]="accountnumber";
    columnName[3]="accounttype";
    response_data=reply->readAll();
    //qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj[columnName[0]].toInt())+" | "+QString::number(json_obj[columnName[1]].toDouble())+
               " | "+json_obj[columnName[2]].toString()+" | "+QString::number(json_obj[columnName[3]].toInt())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

    reply->deleteLater();
    getManager->deleteLater();
}
