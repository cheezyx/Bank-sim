#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
<<<<<<< HEAD
#include <QtWidgets>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
=======
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QCursor>

>>>>>>> main

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


public slots:
    void onbtncancelClicked();

private slots:
<<<<<<< HEAD
    void onTransferButtonClicked();
    void onNetworkReply(QNetworkReply *reply);
=======
    void nostoSlot(QNetworkReply *reply);
    void numberClickedHandler();
    void backspacehandler();
    void on_nosto_4_clicked();
    void on_talletus_clicked();
    void depositFinished(QNetworkReply *reply);



>>>>>>> main
signals:
    void opentransactionWindow();
    void closetransactionWindow();

private:
    Ui::transaction *ui;
<<<<<<< HEAD
    QTextEdit *toAccountTextEdit;
    QTextEdit *amountTextEdit;
    QPushButton *transferButton;
    QNetworkAccessManager *networkManager;
    void sendTransferRequest();
=======
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
>>>>>>> main
};

#endif // TRANSACTION_H
