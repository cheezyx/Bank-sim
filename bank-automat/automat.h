#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <QDialog>

namespace Ui {
class automat;
}

class automat : public QDialog
{
    Q_OBJECT

public:
    explicit automat(QWidget *parent = nullptr);
    ~automat();

private:
    Ui::automat *ui;
};

#endif // AUTOMAT_H
