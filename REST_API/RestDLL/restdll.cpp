#include "restdll.h"

RestDLL::RestDLL(QObject *parent):QObject(parent)
{
    qDebug()<<"DLL luotu";
}

RestDLL::~RestDLL()
{
    qDebug()<<"DLL RÄJÄHTI";
}

void RestDLL::get_clicked()
{
    qDebug()<<"sfadfadsf jejejejejejjejejjeje";
    QString site_url="http://localhost:3000/account";
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getSlot(QNetworkReply*)));

    reply = getManager->get(request);
}


void RestDLL::on_post_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("balance","38945");
    jsonObj.insert("accountnumber","FI23499942322");

    QString site_url="http://localhost:3000/account";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(postSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestDLL::postSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
}

void RestDLL::getSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString get;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        get+=QString::number(json_obj["idAccount"].toInt())+", "+json_obj["balance"].toString()+", "+json_obj["accountnumber"].toString()+"\r";
    }
    qDebug()<<get;
}
