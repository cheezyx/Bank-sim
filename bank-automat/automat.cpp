#include "automat.h"
#include "ui_automat.h"

automat::automat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::automat)
{
    ui->setupUi(this);
}

automat::~automat()
{
    delete ui;
}
