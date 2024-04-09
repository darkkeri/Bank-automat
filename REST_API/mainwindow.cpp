#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_get_clicked()
{
    QString site_url="http://localhost:3000/account";
    QNetworkRequest request((site_url));
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getSlot(QNetworkReply*)));

    reply = getManager->get(request);
}


void MainWindow::on_post_clicked()
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

void MainWindow::postSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
}

void MainWindow::getSlot(QNetworkReply *reply)
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
