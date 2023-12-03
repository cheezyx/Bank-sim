#include "automat.h"
#include "ui_automat.h"
#include "transaction.h"
automat::automat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::automat)
{


    ui->setupUi(this);
    transactionWindow = new transaction(this);
    ui->stackedWidget->setCurrentIndex(0);
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
    connect(ui->siirto, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(ui->talletus, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(ui->nosto, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(transactionWindow, &transaction::closetransactionWindow, this, &automat::show);
}

automat::~automat()
{
    delete ui;
}

void automat::setCard_id(const QString &newCardID)
{
    cardID = newCardID;
}
void automat::showCardID()
{
    ui->IDLabelcard->setText(cardID);
}
void automat::setAccountID(const int &newAccountID)
{

    accountID = newAccountID;
    qDebug()<<"AcCounTID"<<accountID;
}

void automat::setSoloTili(const int &newSoloTili)
{
    soloTili = newSoloTili;
    ui->Tili2->hide();
    ui->Tili1->hide();
    accountID = soloTili;
    qDebug()<<"solo"<<soloTili;
}

void automat::setTokaTili(const int &newTokaTili)
{
    tokaTili = newTokaTili;

    //accountID = tokaTili;
    qDebug()<<"toka"<<tokaTili;
}

void automat::setEkaTili(const int &newEkaTili)
{
    ekaTili = newEkaTili;
   // accountID = ekaTili;
    qDebug()<<"eka"<<ekaTili;
}


void automat::on_saldo_clicked()
{
    QString site_url = "http://localhost:3000/cards/accountinf/" + cardID;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"), (token));

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));

    reply = getManager->get(request);
    ui->stackedWidget->setCurrentIndex(4);
}
void automat::saldoSlot(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray accountsArray = json_doc.array();

    QString saldoInfo;
    foreach (const QJsonValue &value, accountsArray) {
        QJsonObject account = value.toObject();
        int accountId = account["account_id"].toInt();
        QString balance = account["balance"].toString();
        QString accountType = account["account_type"].toString();
        QString creditLimit = account["credit_limit"].toString();

        saldoInfo += "Tilin ID: " + QString::number(accountId) +
                     "\rSaldo: " + balance +
                     "\rTilin tyyppi: " + accountType +
                     "\rLuottoraja: " + creditLimit + "\r\n";
    }

    qDebug() << saldoInfo;
    ui->tekstiAkkuna->setText(saldoInfo); // Asetetaan tilitiedot tekstiAkkunaan

    reply->deleteLater();
    getManager->deleteLater();
}

void automat::on_tilitapahtumat_clicked()
{
    //qDebug() <<"accountID: " << accountID;
    QString site_url="http://localhost:3000/transactions/last_five_transactions/"+QString::number(accountID);
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tilitapahtumatSlot(QNetworkReply*)));

    reply = getManager->get(request);

    ui->stackedWidget->setCurrentIndex(5);
}
void automat::tilitapahtumatSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();

   // qDebug() << "RAW DATA: " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
       QJsonArray json_array = json_doc.array();
       QString tTapahtumat;
       QString transaction_id;

       foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           int transactionId = json_obj["transaction_id"].toInt();
            int fromAccountId = json_obj["from_account_id"].toInt();
             int toAccountId = json_obj["to_account_id"].toInt();
              QString amount = json_obj["amount"].toString();
               QString dateTime = json_obj["date_time"].toString();
                QString description = json_obj["description"].toString();
                 QString transactionType = json_obj["transaction_type"].toString();
                 tTapahtumat += "Tapahtuman ID: " + QString::number(transactionId) +
                                           "\rKäyttäjältä " + QString::number(fromAccountId) +
                                           " käyttäjälle " + QString::number(toAccountId) +
                                           "\rMäärä: " + amount +
                                           "\rPäivämäärä: " + dateTime +
                                           "\rSelite: " + description +
                                           "\rTilitapahtuman tyyppi: " + transactionType + "\r";


         /*  qDebug() << "Tapahtuman ID: " << transactionId;
                      qDebug() << "Käyttäjältä " << fromAccountId << " käyttäjälle " << toAccountId;
                      qDebug() << "Määrä: " << amount;
                     qDebug() << "Päivämäärä: " << dateTime;
                      qDebug() << "Selite: " << description;
                      qDebug() << "Tilitapahtuman tyyppi: " << transactionType;
*/
                 ui->tekstiAkkuna->setText(tTapahtumat);
       }
    reply->deleteLater();
    getManager->deleteLater();
}
void automat::on_logout_clicked()
{
    this->hide();
    emit logOutSignal();
    ui->Tili2->show();
    ui->Tili1->show();
    ui->Tili2->setDisabled(false);
    ui->Tili1->setDisabled(false);
    ui->tekstiAkkuna->clear();
    ui->stackedWidget->setCurrentWidget(0);

    accountID = 0;

    qDebug()<<"Logging out";

}
void automat::on_btncancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tekstiAkkuna->clear();
}
void automat::setToken(const QByteArray &newToken)
{
    token = newToken;
   // qDebug()<<token;
}
void automat::naytaTapahtumat(QString value)
{
    ui->tekstiAkkuna->setText(value);
}
void automat::fetchAndDisplayUserName() {
    QString site_url = "http://localhost:3000/cards/owner/" + cardID;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));

    QNetworkAccessManager *getManager = new QNetworkAccessManager(this);
    connect(getManager, &QNetworkAccessManager::finished, this, &automat::updateGreetingLabel);

    getManager->get(request);
}

void automat::nollaa()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tekstiAkkuna->clear();
}
void automat::updateGreetingLabel(QNetworkReply *reply) {
    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    // Tarkista, onko vastaus taulukko
    if (json_doc.isArray()) {
        QJsonArray json_array = json_doc.array();

        // Tarkista, onko taulukossa ainakin yksi elementti
        if (!json_array.isEmpty()) {
            QJsonObject json_obj = json_array.first().toObject();
            QString firstName = json_obj["first_name"].toString();
            QString lastName = json_obj["last_name"].toString();

            if (!firstName.isEmpty() && !lastName.isEmpty()) {
                ui->lblGreeting->setText("Hei " + firstName + " " + lastName + "!");
            } else {
                ui->lblGreeting->setText("Nimeä ei saatu haettua");
            }
        } else {
            ui->lblGreeting->setText("Nimeä ei saatu haettua");
        }
    } else {
        ui->lblGreeting->setText("Nimeä ei saatu haettua");
    }

    reply->deleteLater();
}
void automat::on_Tili1_clicked()
{
    accountID=ekaTili;
    ui->Tili2->setDisabled(true);
    ui->Tili2->hide();
    ui->Tili1->hide();
    qDebug()<<"tili1 accountID"<<accountID;
}
void automat::on_Tili2_clicked()
{
    accountID=tokaTili;
    ui->Tili1->setDisabled(true);
    ui->Tili2->hide();
    ui->Tili1->hide();
    qDebug()<<"tili2 accountID"<<accountID;

}


void automat::numberClickedHandler()
{
  QPushButton * button = qobject_cast<QPushButton*>(sender());
   if(button)
 {
       QString numero = button->text();
       if(numero == "btnback"){
       backspacehandler();
       } else
       {       ui->tekstiAkkuna->insertPlainText(numero);

       }    qDebug() <<"Button name:"<< button;
      }
}
void automat::backspacehandler()
{
    QString nyykyneteksti = ui->tekstiAkkuna->toPlainText();
    if (!nyykyneteksti.isEmpty()){
        nyykyneteksti.chop(1);
    }
    ui->tekstiAkkuna->setPlainText(nyykyneteksti);
}

void automat::on_siirto_clicked()
{
    this->hide(); // Piilota automat-ikkuna
    transactionWindow->show(); // Näytä transactions-ikkuna
}

void automat::on_talletus_clicked()
{
    this->hide();
    transactionWindow->show();
}
void automat::on_nosto_clicked()
{
    this->hide();
    transactionWindow->show();
    transactionWindow->nostoWait();
}

void automat::opentransactionWindow()
{
    this->hide();
    transactionWindow->show();
    transactionWindow->setToken(token);
    transactionWindow->setAccountID(accountID);

}
