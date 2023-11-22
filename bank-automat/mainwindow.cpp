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


void MainWindow::on_btnLogin_clicked()
{
    QString cardID=ui->TextCardID->text();
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
    qDebug()<<response_data;
    if (response_data.length() < 2)
        {
            qDebug() << "Server did not respond";
        }
        else
        {
            if (response_data != "false")
            {
                qDebug() << "Login successful";
                // Process the token or other data received from the server
            }
            else
            {
                qDebug() << "Incorrect PIN or user does not exist";
                // Provide user feedback, e.g., show an error message
            }
        }
    reply->deleteLater();
    postManager->deleteLater();
}

