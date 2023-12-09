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
    connect(ui->btnTalletus, SIGNAL(clicked(bool)), this, SLOT(on_talletus_clicked()));
    connect(ui->siirto, SIGNAL(clicked(bool)), this, SLOT(SiirtoClicked()));
    connect(ui->btnenter, SIGNAL(clicked()), this, SLOT(vastaanottaja()));
    connect(ui->btnenter, SIGNAL(clicked()), this, SLOT(SiirtoSummaSlot()));
    connect(ui->siirto_2, SIGNAL(clicked()), this, SLOT(hyvaksySiirto()));
    NollausKello = new QTimer(this);
    connect(NollausKello, SIGNAL(timeout()), this, SLOT(aloitaKello()));
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
void transaction::waitforUser() {

    ui->tekstiAkkuna->setText("Anna määrä: ");
    ui->stackedWidget->setCurrentIndex(0);
}
void transaction::on_nosto_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    float amount = ui->numeroAkkuna->text().toFloat();
    qDebug()<<amount;
    this->nostoFUNKTIO(amount);
}


void transaction::nostoFUNKTIO(float _amount)
{
    //qDebug()<<accountID;
    //qDebug()<<_amount;
    QString nst = "Nosto.";
    QJsonObject jsonObj;
    jsonObj.insert("account_id", accountID);
    jsonObj.insert("amount", _amount);
    jsonObj.insert("description", nst);
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
    ui->statuslbl->clear();
    amount = 0;
    emit closetransactionWindow();

}

void transaction::on_talletus_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    double depositAmount = ui->numeroAkkuna->text().toDouble();

    if (depositAmount <= 0) {
        qDebug() << "Invalid deposit amount";
        // You may want to display an error message to the user
        return;
    }

    QString site_url = "http://localhost:3000/transactions/deposit";

    // Create a network request
    QNetworkRequest request(site_url);
    request.setRawHeader(QByteArray("Authorization"), token);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create JSON data for the deposit request
    QJsonObject depositData;
    depositData["account_id"] = accountID;
    depositData["amount"] = depositAmount;
    depositData["description"] = "Talletus tilille";

    // Create a network access manager for the deposit request
    QNetworkAccessManager* depositManager = new QNetworkAccessManager(this);
    connect(depositManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(depositFinished(QNetworkReply*)));

    // Send a POST request to deposit money
    QNetworkReply* depositReply = depositManager->post(request, QJsonDocument(depositData).toJson());

}

void transaction::depositFinished(QNetworkReply *reply)
{
    // Handle the response from the server here
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Deposit successful";
        ui->statuslbl->setText("Talletus onnistui.");
        // Maybe show a success message to the user
    } else {
        qDebug() << "Error depositing money:" << reply->errorString();
        ui->statuslbl->setText("Error.");
        // Maybe show an error message to the user
    }
    reply->deleteLater();
}
void transaction::aloitaSiirto() {
        SiirtoClicked();
    }
void transaction::SiirtoClicked() {

    ui->tekstiAkkuna->setText("Anna vastaanottajan tilinumero ja paina Enter");
    ui->stackedWidget->setCurrentIndex(0);
    disconnect(ui->btnenter, SIGNAL(clicked()), this, SLOT(SiirtoSummaSlot()));
    connect(ui->btnenter, SIGNAL(clicked()), this, SLOT(vastaanottaja()));
}

void transaction::vastaanottaja() {
    int vastTili = ui->numeroAkkuna->text().toInt();
    toAccountID = vastTili;
    ui->numeroAkkuna->clear();
    ui->tekstiAkkuna->setText("Anna summa ja paina Enter");
    disconnect(ui->btnenter, SIGNAL(clicked()), this, SLOT(vastaanottaja()));
    connect(ui->btnenter, SIGNAL(clicked()), this, SLOT(SiirtoSummaSlot()));
}
void transaction::SiirtoSummaSlot() {
    float summa = ui->numeroAkkuna->text().toFloat();
    SiirtoSumma = summa;
    ui->numeroAkkuna->clear();
    ui->stackedWidget->setCurrentIndex(1);
    ui->tekstiAkkuna->setText("Hyväksy siirto");
    disconnect(ui->btnenter, SIGNAL(clicked()), this, SLOT(SiirtoSummaSlot()));
    disconnect(ui->siirto_2, SIGNAL(clicked()), this, SLOT(hyvaksySiirto()));
    connect(ui->siirto_2, SIGNAL(clicked()), this, SLOT(hyvaksySiirto()));
}
void transaction::hyvaksySiirto() {

    QString viesti = "siirretty automaatista";
    QJsonObject jsonObj;
    jsonObj.insert("from_account_id", accountID);
    jsonObj.insert("to_account_id", toAccountID);
    jsonObj.insert("amount", SiirtoSumma);
    jsonObj.insert("description", viesti);
    QString site_url="http://localhost:3000/transactions/transfer";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"),(token));
    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(siirtoSuoritettu(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());

}
void transaction::siirtoSuoritettu(QNetworkReply *reply)
{

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Siirto onnistui";
        ui->statuslbl->setText("Siirto suoritettu.");
        ajastin = 5; // Start from 5 seconds
        NollausKello->start(1000);
    } else {
        qDebug() << "siirto hylatty:" << reply->errorString();
        ui->statuslbl->setText("Error.");

    }
    reply->deleteLater();
}
void transaction::aloitaKello() {
    if (ajastin > 0) {
        ui->statuslbl->setText("palataan alkuun: " + QString::number(ajastin));
        ajastin--;
    } else {
        NollausKello->stop();
        ui->statuslbl->clear();
        nollaaSiirto();
        aloitaSiirto();
    }
}
void transaction::nollaaSiirto() {

    toAccountID = 0;
    SiirtoSumma = 0.0;
    ui->numeroAkkuna->clear();

}
