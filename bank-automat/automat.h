#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QTimer>
#include <tilinvalinta.h>


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
    void setAccount_id(const QString &newAccount_id);

    void showCardID();
    void setToken(const QByteArray &newToken);
    QByteArray token;
    void  startLogoutTimer();
    void näytäTapahtumat(QString value);
    void fetchAndDisplayUserName();
    void updateGreetingLabel(QNetworkReply *reply);


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


signals:
    void logOutSignal();

private:

    QString cardID;
    QString accountID;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;
    QByteArray response_data;
    automat *objectTilitapahtuma;
    QString tapahtuma;
};

#endif // AUTOMAT_H
