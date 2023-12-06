#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>
#include <QtWidgets>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>

namespace Ui {
class transaction;
}

class transaction : public QDialog
{
    Q_OBJECT

public:
    explicit transaction(QWidget *parent = nullptr);
    ~transaction();
public slots:
    void onbtncancelClicked();
private slots:
    void onTransferButtonClicked();
    void onNetworkReply(QNetworkReply *reply);
signals:
    void opentransactionWindow();
    void closetransactionWindow();

private:
    Ui::transaction *ui;
    QTextEdit *toAccountTextEdit;
    QTextEdit *amountTextEdit;
    QPushButton *transferButton;
    QNetworkAccessManager *networkManager;
    void sendTransferRequest();
};

#endif // TRANSACTION_H
