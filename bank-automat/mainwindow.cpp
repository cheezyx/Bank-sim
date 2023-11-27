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

