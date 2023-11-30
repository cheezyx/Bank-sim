#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include "transaction.h"




namespace Ui {
class automat;
}

class automat : public QDialog
{
    Q_OBJECT

public:

    Ui::automat *ui;
    explicit automat(QWidget *parent = nullptr);
    ~automat();
    void setCard_id(const QString &newCard_id);
    void showCardID();
    void setToken(const QByteArray &newToken);
    QByteArray token;
    void  startLogoutTimer();
    void naytaTapahtumat(QString value);
    void fetchAndDisplayUserName();
    void nollaa();
    void updateGreetingLabel(QNetworkReply *reply);
    void setAccountID(const QString &newAccountID);
    QString accountID;
    QString ekaTili;
    QString tokaTili;
    QString soloTili;
    void setEkaTili(const QString &newEkaTili);
    void setTokaTili(const QString &newTokaTili);
    void setSoloTili(const QString &newSoloTili);

public slots:
     void opentransactionWindow();

private slots:
    void on_siirto_clicked();
    void on_talletus_clicked();
    void on_nosto_clicked();
    void on_saldo_clicked();
    void on_tilitapahtumat_clicked();
    void on_logout_clicked();
    //void on_btnenter_clicked();
    //void on_btnback_clicked();
    void on_btncancel_clicked();
    void tilitapahtumatSlot (QNetworkReply *reply);
    void saldoSlot (QNetworkReply *reply);

    void numberClickedHandler();
    void backspacehandler();

    void on_Tili1_clicked();

    void on_Tili2_clicked();

signals:
    void logOutSignal();
    void siirtoSignal();
    void nostoSignal();


private:


    QString cardID;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
    //automat *objectTilitapahtuma;
    QString tapahtuma;
    transaction *transactionWindow;


};

#endif // AUTOMAT_H
