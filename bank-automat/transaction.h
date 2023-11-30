#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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
    QString accountID;
    void setToken(const QByteArray &newToken);
    void setAccountID(const QString &newAccountID);

public slots:
    void onbtncancelClicked();

private slots:
    void on_nosto_2_clicked();
    void nostoSlot(QNetworkReply *reply);
    void numberClickedHandler();
    void backspacehandler();
    //void enterhandler();
    void waitingforentry();

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
