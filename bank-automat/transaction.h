#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "automat.h"

#include <QDialog>

namespace Ui {
class transaction;
}

class transaction : public QDialog
{
    Q_OBJECT

public:
    explicit transaction(QWidget *parent = nullptr);
    ~transaction();

private slots:
    void siirtoSlot();

private:
    Ui::transaction *ui;
};

#endif // TRANSACTION_H
