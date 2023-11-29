#ifndef TILINVALINTA_H
#define TILINVALINTA_H

#include <QDialog>
#include <Automat.h>

namespace Ui {
class Tilinvalinta;
}

class Tilinvalinta : public QDialog
{
    Q_OBJECT

public:
    explicit Tilinvalinta(QWidget *parent = nullptr);
    ~Tilinvalinta();

    void näytäTilit(QString value);

    void setAccountID(const QString &newAccountID);
    QString getAccountID() ;
    QString accountID;

signals:
public slots:
    void on_tiliYksiBtn_clicked();
    void on_tiliKaksiBtn_clicked();

private slots:


private:
    Ui::Tilinvalinta *ui;
    QString ekaTili;
    QString tokaTili;
    automat *objectAuto;




};

#endif // TILINVALINTA_H
