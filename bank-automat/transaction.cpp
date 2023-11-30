#include "transaction.h"
#include "ui_transaction.h"

transaction::transaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transaction)
{
    ui->setupUi(this);

    connect(ui->btn1,SIGNAL(clicked(bool)),this,SLOT(automat::numberClickedHandler()));
    connect(ui->btn2,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn3,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn4,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn5,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn6,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn7,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn8,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn9,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btn0,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
    connect(ui->btnback, SIGNAL(clicked(bool)), this, SLOT(backspacehandler()));
    connect(ui->btnenter, SIGNAL(clicked(bool)), this, SLOT(enterhandler()));
    connect(ui->btncancel, &QPushButton::clicked, this, &transaction::onbtncancelClicked);

}


transaction::~transaction()
{
    delete ui;
}
void transaction::setAccountID(const QString &newAccountID)
{
    qDebug() << "Account received in transaction UI:" << newAccountID;
    accountID = newAccountID;
}
void transaction::setToken(const QByteArray &newToken)
{
    qDebug() << "Token received in transaction UI:" << newToken;
    token=newToken;
}


void transaction::on_nosto_2_clicked()
{

}
void transaction::waitingforentry() {


}

void transaction::nostoSlot(QNetworkReply *reply)
{
     ui->stackedWidget->setCurrentIndex(10);
     ui->tekstiakkuna2->setText("Määrä: \nKuvaus:");
     double amount = ui->tekstiakkuna2->text().toDouble();
    //if (amount != 0.0)
     QJsonObject jsonObj;
     jsonObj.insert("amount", amount);
      QString site_url="http://localhost:3000/transactions/withdraw";
      QNetworkRequest request((site_url));
      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
           request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU

      postManager = new QNetworkAccessManager(this);
      connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
        response_data=reply->readAll();
        qDebug()<<response_data;
        reply->deleteLater();
        postManager->deleteLater();
}

void transaction::backspacehandler()
{

    QString nyykyneteksti = ui->tekstiakkuna2->text();
    if (!nyykyneteksti.isEmpty()){
        nyykyneteksti.chop(1);

    }
    ui->tekstiakkuna2->setText(nyykyneteksti);
}

/*void transaction::enterhandler()
{
    QString nyykyneteksti = ui ->tekstiakkuna2->text();
    if ()
}*/
void transaction::numberClickedHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    if(button)
    {
        QString numero = button->text();
        if(numero == "btnback"){

            backspacehandler();

        } else
        {
            ui->tekstiakkuna2->setText(numero);

        }
        qDebug() <<"Button name:"<< button;
    }
}
void transaction::onbtncancelClicked() {
    this->hide();
    emit closetransactionWindow();
}
