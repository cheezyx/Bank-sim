#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "automat.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectautomat=new automat(this);
    tiliobjekti = new Tilinvalinta(this);

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

       // qDebug() << "RAW DATA: " << response_data;
           QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
           QJsonArray json_array = json_doc.array();
           QString accID;

           foreach (const QJsonValue &value, json_array) {
             QJsonObject json_obj = value.toObject();
             accID+= QString::number(json_obj ["account_id"].toInt())+",";

            }
               qDebug()<<accID;

               QStringList accIDList = accID.split(",", Qt::SkipEmptyParts);

                   if (accIDList.size() >= 2) {
                        ekaTili = accIDList.at(0);  // ekan tilin numero
                        tokaTili = accIDList.at(1); // tokan tilin numero

                       // nyt voidaan käyttää ekan ja tokan tilin numeroa
                       qDebug() << "Ensimmäinen numero: " << ekaTili;
                       qDebug() << "Toinen numero: " << tokaTili;

                       //tiliobjekti = new Tilinvalinta(this);

                       tiliobjekti->naytaTilit(accID);

                       objectautomat->setTokaTili(tokaTili);
                       objectautomat->setEkaTili(ekaTili);

                      // tiliobjekti->setEkaTili(ekaTili);
                     //  tiliobjekti->setTokaTili(tokaTili);
                       tiliobjekti->show();

                   } else {
                       //tiliobjekti = new Tilinvalinta(this);


                       objectautomat->setSoloTili(accID);

                       qDebug() << "numeroi"<<accID;


                       qDebug() << "vain yksitili";
                   }

           reply2->deleteLater();
           getManager->deleteLater();



}
