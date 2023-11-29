#include "tilinvalinta.h"
#include "ui_tilinvalinta.h"


Tilinvalinta::Tilinvalinta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tilinvalinta)
{



    ui->setupUi(this);
    objectAuto = new automat(this);
   // connect(ui->tiliYksiBtn,SIGNAL(clicked()),this,SLOT(on_tiliYksiBtn_clicked()));
    //connect(ui->tiliKaksiBtn,SIGNAL(clicked()),this,SLOT(on_tiliKaksiBtn_clicked()));
}

//testi

Tilinvalinta::~Tilinvalinta()
{
    delete ui;
}

void Tilinvalinta::on_tiliYksiBtn_clicked()
{


    objectAuto->setAccountID(ekaTili);

    accountID=ekaTili;
    qDebug()<<"mitätäälläon"<< ekaTili;
    qDebug()<<accountID;

    this->hide();


}


void Tilinvalinta::on_tiliKaksiBtn_clicked()
{


    objectAuto->setAccountID(tokaTili);
   // accountID=tokaTili;
    qDebug()<<accountID;
    this->hide();


}

void Tilinvalinta::näytäTilit(QString value)
{
    ui->tilinValintamenu_2->setText("valitse tileistä");

    ui->tilinValintamenu->setText(value);

}

void Tilinvalinta::setAccountID(const QString &newAccountID)
{

    accountID=newAccountID;

}
