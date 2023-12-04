#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QCursor>


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
    void nostoWait();


public slots:
    void onbtncancelClicked();

private slots:
    void nostoSlot(QNetworkReply *reply);
    void numberClickedHandler();
    void backspacehandler();
    void on_nostoEnter_clicked();

    void on_talletus_clicked();
    void depositFinished(QNetworkReply *reply);

signals:
    void opentransactionWindow();
    void closetransactionWindow();

private:
    Ui::transaction *ui;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // TRANSACTION_H
