#include "transaction.h"
#include "ui_transaction.h"

transaction::transaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transaction)
{
    ui->setupUi(this);

    connect(ui->btn1,SIGNAL(clicked(bool)),this,SLOT(numberClickedHandler()));
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
    connect(ui->btncancel, &QPushButton::clicked, this, &transaction::onbtncancelClicked);

}


transaction::~transaction()
{
    delete ui;
}
void transaction::setAccountID(const int &newAccountID)
{
    qDebug() << "Account received in transaction UI:" << newAccountID;
    accountID = newAccountID;
}
void transaction::setToken(const QByteArray &newToken)
{
    qDebug() << "Token received in transaction UI:" << newToken;
    token=newToken;
}
void transaction::nostoWait() {

    ui->stackedEnter->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(9);
    ui->tekstiAkkuna->setText("Nostettava määrä: ");
}
void transaction::on_nostoEnter_clicked()
{
    float amount = ui->numeroAkkuna->text().toFloat();
    qDebug()<<amount;
    this->nostoFUNKTIO(amount);
}
void transaction::nostoFUNKTIO(float _amount)
{
    //qDebug()<<accountID;
    //qDebug()<<_amount;
        QJsonObject jsonObj;
        jsonObj.insert("account_id", accountID);
        jsonObj.insert("amount", _amount);
        QString site_url="http://localhost:3000/transactions/withdraw";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader(QByteArray("Authorization"),(token));
        postManager = new QNetworkAccessManager(this);
        connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));

        reply = postManager->post(request, QJsonDocument(jsonObj).toJson());

}
void transaction::nostoSlot(QNetworkReply *reply)
{
        response_data=reply->readAll();
        qDebug()<<response_data;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);

        // Check if the response contains the expected message
        if (jsonResponse.isObject())
            {
            QJsonObject jsonObject = jsonResponse.object();
            if (jsonObject.contains("message"))
                {
                QString message = jsonObject.value("message").toString();

                // Update status label based on the message
                if (message == "Withdrawal successful")
                    {
                    ui->statuslbl->setText("Nosto onnistui.");

                    }
                else
                    {
                    ui->statuslbl->setText("Tilillä ei ole katetta.");
                    }
                }
            }
        reply->deleteLater();
            postManager->deleteLater();
}

void transaction::numberClickedHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());

    if(button)
    {
        QString numero = button->text();
        if(numero == "btnback"){
            backspacehandler();
        } else
        {       ui->numeroAkkuna->insert(numero);

        }    //qDebug() <<"Button name:"<< button;
    }
}
void transaction::backspacehandler()
{
    QString nyykyneteksti = ui->numeroAkkuna->text();
    if (!nyykyneteksti.isEmpty()){
        nyykyneteksti.chop(1);
    }
    ui->numeroAkkuna->setText(nyykyneteksti);
}
void transaction::onbtncancelClicked() {

    this->hide();
    ui->tekstiAkkuna->clear();
    ui->numeroAkkuna->clear();
    amount = 0;
    emit closetransactionWindow();

}

