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

void RestDLL::get_Clicked(int id)
{
    qDebug()<<id;
    QString urlAddress = "/logs/";
    QString site_url=Environment::getBaseURL()+urlAddress+QString::number(id);
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);
    if(urlAddress == "/logs/"){
    connect(getManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(getLogs(QNetworkReply*)));
    } else if (urlAddress == "/cards"){
    connect(getManager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(getSlot(QNetworkReply*)));
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
    //qDebug()<<"DATA : "+response_data;
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
        " | "+QString::number(json_obj[columnName[3]].toInt())+" | "+QString::number(json_obj[columnName[4]].toInt())+"\r";
    }
    qDebug()<<get;
    //get qstring menee get_handleriin exessä:
    emit getResult(get);

    reply->deleteLater();
    getManager->deleteLater();
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
    qDebug()<<response_data;
    if(response_data=="-4078"){

    }

}
