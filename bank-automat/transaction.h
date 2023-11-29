#ifndef TRANSACTION_H
#define TRANSACTION_H

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
public slots:
    void onbtncancelClicked();
private slots:

signals:
    void opentransactionWindow();
    void closetransactionWindow();

private:
    Ui::transaction *ui;
};

#endif // TRANSACTION_H
