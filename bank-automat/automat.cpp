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
    QList<QPushButton*> numberButtons ={
    ui->btn1, ui->btn2, ui->btn3, ui->btn4, ui->btn5,
    ui->btn6, ui->btn7, ui->btn8, ui->btn9, ui->btn0
    };

    foreach (QPushButton* näppäin, numberButtons) {
        connect(näppäin, SIGNAL(clicked(bool)), this, SLOT(numberClickedHandler()));
        näppäin->setStyleSheet(
            "QPushButton:disabled {"
            "   background-color: rgba(255, 0, 0, 128);"
            "   color: rgba(255, 255, 255, 255);"
            "}"
        );
        näppäin->setStyleSheet(
            "QPushButton:enabled {"
            "   background-color: rgb(42, 55, 67);;"
            "   color: rgb(255, 255, 255);"
            "}"
        );
    }
    QList<QPushButton*> widgetit ={
    ui->siirto, ui->talletus, ui->nosto,
    ui->saldo, ui->tilitapahtumat
    };
    foreach (QPushButton* widgetiti, widgetit){
    widgetiti->setStyleSheet(
        "QPushButton:disabled {"
        "   background-color: rgba(255, 0, 0, 128);"
        "   color: rgba(255, 255, 255, 255);"
        "}"
    );
    widgetiti->setStyleSheet(
        "QPushButton:enabled {"
        "   background-color: rgb(42, 55, 67);;"
        "   color: rgb(255, 255, 255);"
        "}"
    );
}
    //connect(ui->btnback, SIGNAL(clicked(bool)), this, SLOT(backspacehandler()));
    connect(ui->siirto, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(ui->talletus, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(ui->nosto, &QPushButton::clicked, this, &automat::opentransactionWindow);
    connect(transactionWindow, &transaction::closetransactionWindow, this, &automat::show);
    connect(ui->btnenter,SIGNAL(clicked(bool)),this,SLOT(on_nextPageButton_clicked()));
    connect(ui->btnback,SIGNAL(clicked(bool)),this,SLOT(on_previousPageButton_clicked()));
    ui->btnback->setStyleSheet( "QPushButton:disabled {"
                                "   background-color:  rgba(255, 0, 0, 128);"   // Väri, kun näppäin on disabloitu
                                "   color: rgba(255, 255, 255, 255);;"
                                "}");
    ui->btnenter->setStyleSheet( "QPushButton:disabled {"
                                 "   background-color: gray;"   // Väri, kun näppäin on disabloitu
                                 "   color: gray;"
                                 "}");
    ui->btnback->setStyleSheet( "QPushButton:enabled {"
                                "   background-color:  rgb(42, 55, 67);"   // Väri, kun näppäin on enabled
                                "   color: rgb(255, 255, 255);;"
                                "}");
    ui->btnenter->setStyleSheet( "QPushButton:enabled {"
                                 "   background-color: rgb(42, 55, 67);"   // Väri, kun näppäin on enabled
                                 "   color: rgb(255, 255, 255)"
                                 "}");

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
    QString site_url = "http://localhost:3000/accounts/" + QString::number(accountID);
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
    foreach (const QJsonValue &value, accountsArray){

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
    qDebug() <<"accountID: " << accountID;
    int offset = (currentPage - 1) * itemsPerPage;
    qDebug() << "offest" << offset;
    qDebug() << "items" << itemsPerPage;
        automat::tapahtumienMaara();

    QString site_url = "http://localhost:3000/transactions/transfers/" + QString::number(accountID) + "/" + QString::number(itemsPerPage) + "/" + QString::number(offset);
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tilitapahtumatSlot(QNetworkReply*)));

    reply = getManager->get(request);
    ui->btnback->setDisabled(false);
    ui->btnenter->setDisabled(false);

    ui->stackedWidget->setCurrentIndex(5);
}
void automat::tapahtumienMaara()
{
    qDebug() <<"accountID2: " << accountID;

    QString site_url = "http://localhost:3000/transactions/transaction_count/" + QString::number(accountID);
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(tapahtumaMaaraSLot(QNetworkReply*)));

    reply = getManager->get(request);

}

void automat::tapahtumaMaaraSLot(QNetworkReply *reply)
{

    response_data = reply->readAll();
    maxPage = response_data; //16
    int testi = maxPage.toInt();
    laskettuMaxPage = ceil(static_cast<double>(testi) / itemsPerPage);

     qDebug() << "RAAKAA DATAAA: " << response_data;
     qDebug() << "vittu jees: " << laskettuMaxPage;

}
void automat::tilitapahtumatSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();

   // qDebug() << "RAW DATA: " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
       QJsonArray json_array = json_doc.array();
       QString tTapahtumat;
       QString transaction_id;

       foreach (const QJsonValue &value, json_array){
           QJsonObject json_obj = value.toObject();
           int transactionId = json_obj["transaction_id"].toInt();
            int fromAccountId = json_obj["from_account_id"].toInt();
             int toAccountId = json_obj["to_account_id"].toInt();
              QString amount = json_obj["amount"].toString();
             QString dateTime = json_obj["date_time"].toString();
             QDateTime formattedDateTime = QDateTime::fromString(dateTime, Qt::ISODate);
             QString formattedDateTimeString = formattedDateTime.toString("dd.MM.yyyy hh:mm");
                QString description = json_obj["description"].toString();
                 QString transactionType = json_obj["transaction_type"].toString();
                tTapahtumat += "Tapahtuman ID: " + QString::number(transactionId) + "\n"
                               + "Käyttäjältä: " + QString::number(fromAccountId) + "\n"
                               + "Käyttäjälle: " + QString::number(toAccountId) + "\n"
                               + "Määrä: " + amount + "\n"
                               + "Päivämäärä: " + formattedDateTimeString + "\n"
                               + "Selite: " + description + "\n"
                               + "Tilitapahtuman tyyppi: " + transactionType + "\n\n";

/*
           qDebug() << "Tapahtuman ID: " << transactionId;
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
void automat::handleNextPage()
{
    if (currentPage < laskettuMaxPage)
    currentPage++;
    on_tilitapahtumat_clicked();
}

void automat::handlePreviousPage()
{
    if (currentPage > 1) {
        currentPage--;
        on_tilitapahtumat_clicked();
    }
}

void automat::disablointi()
{

    ui->stackedWidget->setDisabled(true);

}
void automat::on_nextPageButton_clicked()
{
    handleNextPage();
}

void automat::on_previousPageButton_clicked()
{
    handlePreviousPage();
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
    ui->Tili1->setStyleSheet("background-color: green; color: white;");
    ui->Tili2->setStyleSheet("background-color: green; color: white;");
    ui->stackedWidget->setCurrentWidget(0);

    accountID = 0;

    qDebug()<<"Logging out";

}
void automat::on_btncancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->tekstiAkkuna->clear();
    ui->btnback->setDisabled(true);
    ui->btnenter->setDisabled(true);
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
    //ui->Tili2->setDisabled(true);
    ui->Tili2->show();
    //ui->Tili1->hide();
    ui->Tili1->setStyleSheet("background-color: green; color: white;");
    ui->Tili2->setStyleSheet("background-color: red; color: white;");
    ui->tekstiAkkuna->setText("Credit-tili valittu");
    ui->stackedWidget->setDisabled(false);
    qDebug()<<"tili1 accountID"<<accountID;


}
void automat::on_Tili2_clicked()
{
    accountID=tokaTili;
   // ui->Tili1->setDisabled(true);
    //ui->Tili2->hide();
    ui->Tili1->show();
    ui->Tili2->setStyleSheet("background-color: green; color: white;");
    ui->Tili1->setStyleSheet("background-color: red; color: white;");
    ui->tekstiAkkuna->setText("Debit-tili valittu");
    ui->stackedWidget->setDisabled(false);

    qDebug()<<"tili2 accountID"<<accountID;

}
void automat::napittoimiitaiei()
{
    ui->btnback->setDisabled(true);
    ui->btnenter->setDisabled(true);
    ui->btn0->setDisabled(true);
    ui->btn1->setDisabled(true);
    ui->btn2->setDisabled(true);
    ui->btn3->setDisabled(true);
    ui->btn4->setDisabled(true);
    ui->btn5->setDisabled(true);
    ui->btn6->setDisabled(true);
    ui->btn7->setDisabled(true);
    ui->btn8->setDisabled(true);
    ui->btn9->setDisabled(true);


 ui->btn0->setDisabled(true);
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
    transactionWindow->waitforUser();
}
void automat::on_nosto_clicked()
{
    this->hide();
    transactionWindow->show();
    transactionWindow->waitforUser();
}

void automat::opentransactionWindow()
{
    this->hide();
    transactionWindow->show();
    transactionWindow->setToken(token);
    transactionWindow->setAccountID(accountID);

}
