#include "transaction.h"
#include "ui_transaction.h"

transaction::transaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transaction)
{
    ui->setupUi(this);
    connect(ui->btncancel, &QPushButton::clicked, this, &transaction::onbtncancelClicked);

}

transaction::~transaction()
{
    delete ui;
}
void transaction::onbtncancelClicked() {
    this->hide();
    emit closetransactionWindow();
}
