#include "automat.h"
#include "ui_automat.h"

automat::automat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::automat)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
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


void automat::on_siirto_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void automat::on_talletus_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void automat::on_nosto_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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
    QString site_url="http://localhost:3000/transactions/last_five_transactions/6";
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

    qDebug() << "RAW DATA: " << response_data;
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


           qDebug() << "Tapahtuman ID: " << transactionId;
                      qDebug() << "Käyttäjältä " << fromAccountId << " käyttäjälle " << toAccountId;
                      qDebug() << "Määrä: " << amount;
                      qDebug() << "Päivämäärä: " << dateTime;
                      qDebug() << "Selite: " << description;
                      qDebug() << "Tilitapahtuman tyyppi: " << transactionType;

                      objectTilitapahtuma=new automat(this);
                      objectTilitapahtuma->näytäTapahtumat(tTapahtumat);
                      objectTilitapahtuma->show();
       }



       //ui->textEditResults->setText(tTapahtumat);


    reply->deleteLater();
    getManager->deleteLater();
}
void automat::on_logout_clicked()
{
    this->hide();
    emit logOutSignal();
    qDebug()<<"Logging out";

}

void automat::on_btnback_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void automat::setToken(const QByteArray &newToken)
{
    token = newToken;
    qDebug()<<token;
}

void automat::näytäTapahtumat(QString value)
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
