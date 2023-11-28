#include "tilinvalinta.h"
#include "ui_tilinvalinta.h"

Tilinvalinta::Tilinvalinta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tilinvalinta)
{
    ui->setupUi(this);
}

Tilinvalinta::~Tilinvalinta()
{
    delete ui;
}


void Tilinvalinta::on_tiliYksiBtn_clicked()
{

    //this->hide();
    qDebug() << "Tili 1 valittu: " << accountID1;


}


void Tilinvalinta::on_tiliKaksiBtn_clicked()
{
    //this->hide();

    qDebug() << "Tili 2 valittu: " << accountID2;


}
void Tilinvalinta::näytäAccountit()
{

    ui->tilinValintamenu->setText(accountID1);
    ui->tilinValintamenu->setText(accountID2);

}



