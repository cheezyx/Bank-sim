#include "transaction.h"
#include "ui_transaction.h"

transaction::transaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transaction)
{
    ui->setupUi(this);

    // Assuming you have these elements in your form (if not, add them)
    toAccountTextEdit = ui->tekstiAkkuna;
    amountTextEdit = ui->tekstiAkkuna;
    transferButton = ui->btnenter;

    // Rest of your setup...
    networkManager = new QNetworkAccessManager(this);
    connect(transferButton, &QPushButton::clicked, this, &transaction::onTransferButtonClicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &transaction::onNetworkReply);
}

transaction::~transaction()
{
    delete ui;
}
void transaction::onbtncancelClicked() {
    this->hide();
    emit closetransactionWindow();
}
void transaction::onTransferButtonClicked() {
    sendTransferRequest();
}
void transaction::sendTransferRequest() {
    QJsonObject json;
    json["to_account_id"] = toAccountTextEdit->toPlainText().trimmed();
    json["amount"] = amountTextEdit->toPlainText().trimmed().toDouble();
    json["description"] = "Maksettu automaatista";

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl("http://localhost:3000/transactions/transfer"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager->post(request, data);
}
void transaction::onNetworkReply(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Error:" << reply->errorString();
        return;
    }

    QString response = reply->readAll();
    qDebug() << "Response:" << response;
}
