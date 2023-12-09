#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QCursor>
#include <QTimer>

namespace Ui {
class transaction;
}

class transaction : public QDialog
{
    Q_OBJECT

public:
    explicit transaction(QWidget *parent = nullptr);
    ~transaction();

    QByteArray token;
    int accountID;
    void setToken(const QByteArray &newToken);
    void setAccountID(const int &newAccountID);
    void nostoFUNKTIO(float);
    float amount;
    void waitforUser();
    float SiirtoSumma;
    int toAccountID;
    void aloitaSiirto();


public slots:
    void onbtncancelClicked();
    void hyvaksySiirto();

private slots:
    void nostoSlot(QNetworkReply *reply);
    void numberClickedHandler();
    void backspacehandler();
    void on_nosto_4_clicked();
    void on_talletus_clicked();
    void depositFinished(QNetworkReply *reply);
    void SiirtoClicked();
    void vastaanottaja();
    void SiirtoSummaSlot();
    void siirtoSuoritettu(QNetworkReply *reply);
    void aloitaKello();
signals:
    void opentransactionWindow();
    void closetransactionWindow();

private:
    Ui::transaction *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QTimer *NollausKello;
    int ajastin;
    void nollaaSiirto();

};

#endif // TRANSACTION_H
