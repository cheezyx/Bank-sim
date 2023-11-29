#include "transaction.h"
#include "ui_transaction.h"

transaction::transaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transaction)
{
    ui->setupUi(this);
    connect(ui->siirto, &QPushButton::clicked, this,SLOT(siirtoSlot);
    connect(ui->talletus, &QPushButton::clicked, this, &automat::on_talletus_clicked);
    connect(ui->nosto, &QPushButton::clicked, this, &automat::on_nosto_clicked);

}

transaction::~transaction()
{
    delete ui;
}
