/********************************************************************************
** Form generated from reading UI file 'tilinvalinta.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILINVALINTA_H
#define UI_TILINVALINTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Tilinvalinta
{
public:
    QPushButton *tiliYksiBtn;
    QPushButton *tiliKaksiBtn;
    QTextEdit *tilinValintamenu;
    QTextEdit *tilinValintamenu_2;

    void setupUi(QDialog *Tilinvalinta)
    {
        if (Tilinvalinta->objectName().isEmpty())
            Tilinvalinta->setObjectName("Tilinvalinta");
        Tilinvalinta->resize(402, 317);
        tiliYksiBtn = new QPushButton(Tilinvalinta);
        tiliYksiBtn->setObjectName("tiliYksiBtn");
        tiliYksiBtn->setGeometry(QRect(90, 140, 91, 51));
        tiliKaksiBtn = new QPushButton(Tilinvalinta);
        tiliKaksiBtn->setObjectName("tiliKaksiBtn");
        tiliKaksiBtn->setGeometry(QRect(200, 140, 91, 51));
        tilinValintamenu = new QTextEdit(Tilinvalinta);
        tilinValintamenu->setObjectName("tilinValintamenu");
        tilinValintamenu->setGeometry(QRect(110, 90, 161, 31));
        tilinValintamenu_2 = new QTextEdit(Tilinvalinta);
        tilinValintamenu_2->setObjectName("tilinValintamenu_2");
        tilinValintamenu_2->setGeometry(QRect(110, 60, 161, 31));

        retranslateUi(Tilinvalinta);

        QMetaObject::connectSlotsByName(Tilinvalinta);
    } // setupUi

    void retranslateUi(QDialog *Tilinvalinta)
    {
        Tilinvalinta->setWindowTitle(QCoreApplication::translate("Tilinvalinta", "Dialog", nullptr));
        tiliYksiBtn->setText(QCoreApplication::translate("Tilinvalinta", "Tili1", nullptr));
        tiliKaksiBtn->setText(QCoreApplication::translate("Tilinvalinta", "Tili2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tilinvalinta: public Ui_Tilinvalinta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILINVALINTA_H
