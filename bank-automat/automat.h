#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>





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
    void näytäTapahtumat(QString value);
    void fetchAndDisplayUserName();
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


private slots:
    void on_siirto_clicked();
    void on_talletus_clicked();
    void on_nosto_clicked();
    void on_saldo_clicked();
    void on_tilitapahtumat_clicked();
    void on_logout_clicked();
    //void on_btnenter_clicked();
    void on_btnback_clicked();
    void tilitapahtumatSlot (QNetworkReply *reply);
    void saldoSlot (QNetworkReply *reply);

    void on_Tili2_clicked();

    void on_tili1_clicked();

    void on_btn1_clicked();
    void numberClickedHandler();
    void backspacehandler();

signals:
    void logOutSignal();



private:


    QString cardID;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
    //automat *objectTilitapahtuma;
    QString tapahtuma;



};

#endif // AUTOMAT_H
