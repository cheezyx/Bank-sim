#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "automat.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectautomat=new automat(this);
    ui->TextPin->hide();

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

    bool ok;
    QString cardPIN = QInputDialog::getText(ui->TextPin, "Syötä salasana", "Salasana:", QLineEdit::Password, "", &ok);

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
                //objectautomat->showCardID();
                objectautomat->show();
                objectautomat->nollaa();
                objectautomat->napittoimiitaiei();

                this->hide();

                QString site_url2 = "http://localhost:3000/cards/accountinf/" + cardID;
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
    response_data = reply2->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    int creditTiliId = -1;
    int debitTiliId = -1;

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        int account_id = json_obj.value("account_id").toInt();
        QString accountType = json_obj.value("account_type").toString();

        if (accountType == "credit") {
            creditTiliId = account_id;
        } else if (accountType == "debit") {
            debitTiliId = account_id;
        }
    }

    if (creditTiliId != -1 && debitTiliId != -1) {
        objectautomat->setEkaTili(creditTiliId); // credit tili
        objectautomat->setTokaTili(debitTiliId); // debit tili
        objectautomat->disablointi();
        objectautomat->valitseTiliTeksti();
        qDebug() << "Credit tili = " << creditTiliId;
        qDebug() << "Debit tili = " << debitTiliId;
    } else if (creditTiliId != -1 || debitTiliId != -1) {
        int soloTiliId = (creditTiliId != -1) ? creditTiliId : debitTiliId;
        objectautomat->setSoloTili(soloTiliId);
        qDebug() << "Solo tili = " << soloTiliId;
    } else {
        qDebug() << "Ei löytynyt linkitettyjä tilejä";
    }

    reply2->deleteLater();
    getManager->deleteLater();
}
