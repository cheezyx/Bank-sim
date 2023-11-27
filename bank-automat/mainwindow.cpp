#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "automat.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objectautomat=new automat(this);
    connect(objectautomat, SIGNAL(logOutSignal()), this, SLOT(logoutSlot()));
}

MainWindow::~MainWindow()
{
    disconnect(objectautomat, SIGNAL(logOutSignal()), this, SLOT(logoutSlot()));
    delete ui;
}


void MainWindow::on_btnLogin_clicked()
{

    cardID=ui->TextCardID->text();
    QString cardPIN=ui->TextPin->text();
    QJsonObject jsonObj;
    jsonObj.insert("card_id",cardID);
    jsonObj.insert("pin_hashed",cardPIN);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());



}


void MainWindow::loginSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    //qDebug()<<response_data;
    if (response_data.length() < 2)
        {
            qDebug() << "Server did not respond";
            ui->labelInfo->setText("Serveri ei vastaa");
        }
        else
        {
            if (response_data != "false")
            {
                qDebug() << "Login successful";
                // Antaa tokenin
                token = "Bearer "+response_data;


                objectautomat->setToken(token);
                objectautomat->setCard_id(cardID);
                objectautomat->fetchAndDisplayUserName();
                objectautomat->showCardID();
                objectautomat->show();
                this->hide();

                QString site_url2 = "http://localhost:3000/card_privileges/" + cardID;
                   QNetworkRequest request2(site_url2);
                   request2.setRawHeader(QByteArray("Authorization"), (token));

                   getManager = new QNetworkAccessManager(this);
                   connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accountSlot(QNetworkReply*)));

                   reply2 = getManager->get(request2);
            }
            else
            {
                qDebug() << "Incorrect PIN or user does not exist";
                ui->labelInfo->setText("Tunnus tai PIN väärin");
                ui->TextCardID->clear();
                ui->TextPin->clear();
            }
        }
    reply->deleteLater();
    postManager->deleteLater();
}
void MainWindow::logoutSlot()
{
    this->show();
    ui->TextCardID->clear();
    ui->TextPin->clear();
    ui->labelInfo->setText("Kirjauduttu ulos");
    token.clear();
}

void MainWindow::accountSlot(QNetworkReply *reply2)
{

    response_data=reply2->readAll();

        qDebug() << "RAW DATA: " << response_data;
           QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
           QJsonArray json_array = json_doc.array();
           QString aAccounts;
           QString aAccounts2;

           foreach (const QJsonValue &value, json_array) {
               QJsonObject json_obj = value.toObject();
               aAccounts+=QString::number(json_obj["account_id"].toInt())+",";
               aAccounts2+=QString::number(json_obj["card_id"].toInt())+",";
           }

           qDebug()<<aAccounts;//account_IDs
           qDebug()<<aAccounts2;//card_id


          // ui->textEditResults->setText(aAccounts);
                    QString testi = aAccounts;
                    QStringList numerot = aAccounts.split(',');

                    if (numerot.size() >= 2) {
                         accountID1 = numerot[0].toInt();
                         accountID2 = numerot[1].toInt();

                               qDebug()<<accountID1;//accountID1
                               qDebug()<<accountID2;//accountID2


                              }  else {
                                   qDebug()<<"vituiks meni";

             }
           reply2->deleteLater();
           getManager->deleteLater();



}


