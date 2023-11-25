#include "automat.h"
#include "ui_automat.h"

automat::automat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::automat)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

automat::~automat()
{
    delete ui;
}

void automat::setCard_id(const QString &newCardID)
{
    cardID = newCardID;
}
void automat::showCardID()
{
    ui->IDLabelcard->setText(cardID);
}


void automat::on_siirto_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void automat::on_talletus_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void automat::on_nosto_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
void automat::on_saldo_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void automat::on_tilitapahtumat_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void automat::on_logout_clicked()
{
    this->hide();
    emit logOutSignal();
    qDebug()<<"Logging out";

}

void automat::on_btnback_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->screenlabel->clear();
}

void automat::setToken(const QByteArray &newToken)
{
    token = newToken;
    qDebug()<<token;
}



