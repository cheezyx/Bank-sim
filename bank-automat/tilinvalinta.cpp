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

  ui->tiliYksiBtn->click();

}


void Tilinvalinta::on_tiliKaksiBtn_clicked()
{



}




