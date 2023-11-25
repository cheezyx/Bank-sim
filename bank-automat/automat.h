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

private slots:

    void on_siirto_clicked();
    void on_talletus_clicked();
    void on_nosto_clicked();
    void on_saldo_clicked();
    void on_tilitapahtumat_clicked();
    void on_logout_clicked();
    //void on_btnenter_clicked();
    void on_btnback_clicked();

signals:
    void logOutSignal();

private:

    QString cardID;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // AUTOMAT_H
