/********************************************************************************
** Form generated from reading UI file 'automat.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMAT_H
#define UI_AUTOMAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_automat
{
public:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn9;
    QPushButton *btn0;
    QPushButton *logout;
    QPushButton *btnenter;
    QPushButton *btnback;
    QLabel *label;
    QLabel *IDLabelcard;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *tilitapahtumat;
    QPushButton *talletus;
    QPushButton *nosto;
    QPushButton *saldo;
    QPushButton *siirto;
    QWidget *page_2;
    QPushButton *siirto_3;
    QWidget *page_3;
    QPushButton *talletus_3;
    QWidget *page_4;
    QPushButton *nosto_3;
    QWidget *page_5;
    QPushButton *saldo_3;
    QWidget *page_6;
    QPushButton *tilitapahtumat_3;
    QTextEdit *tekstiAkkuna;
    QLabel *lblGreeting;
    QPushButton *tili1;
    QPushButton *Tili2;
    QPushButton *btncancel;

    void setupUi(QDialog *automat)
    {
        if (automat->objectName().isEmpty())
            automat->setObjectName("automat");
        automat->resize(732, 644);
        automat->setAutoFillBackground(true);
        btn1 = new QPushButton(automat);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(270, 350, 51, 51));
        QFont font;
        font.setPointSize(12);
        btn1->setFont(font);
        btn2 = new QPushButton(automat);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(330, 350, 51, 51));
        btn2->setFont(font);
        btn3 = new QPushButton(automat);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(390, 350, 51, 51));
        btn3->setFont(font);
        btn4 = new QPushButton(automat);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(270, 410, 51, 51));
        btn4->setFont(font);
        btn5 = new QPushButton(automat);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(330, 410, 51, 51));
        btn5->setFont(font);
        btn6 = new QPushButton(automat);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(390, 410, 51, 51));
        btn6->setFont(font);
        btn7 = new QPushButton(automat);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(270, 470, 51, 51));
        btn7->setFont(font);
        btn8 = new QPushButton(automat);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(330, 470, 51, 51));
        btn8->setFont(font);
        btn9 = new QPushButton(automat);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(390, 470, 51, 51));
        btn9->setFont(font);
        btn0 = new QPushButton(automat);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(330, 530, 51, 51));
        btn0->setFont(font);
        logout = new QPushButton(automat);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(40, 520, 151, 51));
        QFont font1;
        font1.setPointSize(14);
        logout->setFont(font1);
        btnenter = new QPushButton(automat);
        btnenter->setObjectName("btnenter");
        btnenter->setGeometry(QRect(390, 530, 51, 81));
        btnback = new QPushButton(automat);
        btnback->setObjectName("btnback");
        btnback->setGeometry(QRect(270, 530, 51, 81));
        label = new QLabel(automat);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 70, 101, 61));
        QFont font2;
        font2.setPointSize(20);
        label->setFont(font2);
        IDLabelcard = new QLabel(automat);
        IDLabelcard->setObjectName("IDLabelcard");
        IDLabelcard->setGeometry(QRect(150, 70, 131, 61));
        IDLabelcard->setFont(font2);
        stackedWidget = new QStackedWidget(automat);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(480, 270, 211, 331));
        page = new QWidget();
        page->setObjectName("page");
        tilitapahtumat = new QPushButton(page);
        tilitapahtumat->setObjectName("tilitapahtumat");
        tilitapahtumat->setGeometry(QRect(30, 260, 151, 51));
        tilitapahtumat->setFont(font1);
        talletus = new QPushButton(page);
        talletus->setObjectName("talletus");
        talletus->setGeometry(QRect(30, 80, 151, 51));
        talletus->setFont(font1);
        nosto = new QPushButton(page);
        nosto->setObjectName("nosto");
        nosto->setGeometry(QRect(30, 140, 151, 51));
        nosto->setFont(font1);
        saldo = new QPushButton(page);
        saldo->setObjectName("saldo");
        saldo->setGeometry(QRect(30, 200, 151, 51));
        saldo->setFont(font1);
        siirto = new QPushButton(page);
        siirto->setObjectName("siirto");
        siirto->setGeometry(QRect(30, 20, 151, 51));
        siirto->setFont(font1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        siirto_3 = new QPushButton(page_2);
        siirto_3->setObjectName("siirto_3");
        siirto_3->setGeometry(QRect(30, 20, 151, 51));
        siirto_3->setFont(font1);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        talletus_3 = new QPushButton(page_3);
        talletus_3->setObjectName("talletus_3");
        talletus_3->setGeometry(QRect(30, 80, 151, 51));
        talletus_3->setFont(font1);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        nosto_3 = new QPushButton(page_4);
        nosto_3->setObjectName("nosto_3");
        nosto_3->setGeometry(QRect(30, 140, 151, 51));
        nosto_3->setFont(font1);
        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        saldo_3 = new QPushButton(page_5);
        saldo_3->setObjectName("saldo_3");
        saldo_3->setGeometry(QRect(30, 200, 151, 51));
        saldo_3->setFont(font1);
        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        tilitapahtumat_3 = new QPushButton(page_6);
        tilitapahtumat_3->setObjectName("tilitapahtumat_3");
        tilitapahtumat_3->setGeometry(QRect(30, 260, 151, 51));
        tilitapahtumat_3->setFont(font1);
        stackedWidget->addWidget(page_6);
        tekstiAkkuna = new QTextEdit(automat);
        tekstiAkkuna->setObjectName("tekstiAkkuna");
        tekstiAkkuna->setGeometry(QRect(210, 150, 271, 181));
        lblGreeting = new QLabel(automat);
        lblGreeting->setObjectName("lblGreeting");
        lblGreeting->setGeometry(QRect(160, 10, 381, 51));
        lblGreeting->setFont(font2);
        lblGreeting->setAlignment(Qt::AlignCenter);
        tili1 = new QPushButton(automat);
        tili1->setObjectName("tili1");
        tili1->setGeometry(QRect(500, 120, 71, 61));
        Tili2 = new QPushButton(automat);
        Tili2->setObjectName("Tili2");
        Tili2->setGeometry(QRect(590, 120, 75, 61));
        btncancel = new QPushButton(automat);
        btncancel->setObjectName("btncancel");
        btncancel->setGeometry(QRect(40, 460, 151, 51));
        btncancel->setFont(font1);

        retranslateUi(automat);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(automat);
    } // setupUi

    void retranslateUi(QDialog *automat)
    {
        automat->setWindowTitle(QCoreApplication::translate("automat", "Dialog", nullptr));
        btn1->setText(QCoreApplication::translate("automat", "1", nullptr));
        btn2->setText(QCoreApplication::translate("automat", "2", nullptr));
        btn3->setText(QCoreApplication::translate("automat", "3", nullptr));
        btn4->setText(QCoreApplication::translate("automat", "4", nullptr));
        btn5->setText(QCoreApplication::translate("automat", "5", nullptr));
        btn6->setText(QCoreApplication::translate("automat", "6", nullptr));
        btn7->setText(QCoreApplication::translate("automat", "7", nullptr));
        btn8->setText(QCoreApplication::translate("automat", "8", nullptr));
        btn9->setText(QCoreApplication::translate("automat", "9", nullptr));
        btn0->setText(QCoreApplication::translate("automat", "0", nullptr));
        logout->setText(QCoreApplication::translate("automat", "Kirjaudu ulos", nullptr));
        btnenter->setText(QCoreApplication::translate("automat", "->", nullptr));
        btnback->setText(QCoreApplication::translate("automat", "<-", nullptr));
        label->setText(QCoreApplication::translate("automat", "Card id:", nullptr));
        IDLabelcard->setText(QString());
        tilitapahtumat->setText(QCoreApplication::translate("automat", "Tilitapahtumat", nullptr));
        talletus->setText(QCoreApplication::translate("automat", "Talletus", nullptr));
        nosto->setText(QCoreApplication::translate("automat", "Nosto", nullptr));
        saldo->setText(QCoreApplication::translate("automat", "Tarkista saldo", nullptr));
        siirto->setText(QCoreApplication::translate("automat", "Siirto", nullptr));
        siirto_3->setText(QCoreApplication::translate("automat", "Siirto", nullptr));
        talletus_3->setText(QCoreApplication::translate("automat", "Talletus", nullptr));
        nosto_3->setText(QCoreApplication::translate("automat", "Nosto", nullptr));
        saldo_3->setText(QCoreApplication::translate("automat", "Tarkista saldo", nullptr));
        tilitapahtumat_3->setText(QCoreApplication::translate("automat", "Tilitapahtumat", nullptr));
        lblGreeting->setText(QCoreApplication::translate("automat", "<html><head/><body><p><span style=\" font-size:20pt;\">TextLabel</span></p></body></html>", nullptr));
        tili1->setText(QCoreApplication::translate("automat", "Tili1", nullptr));
        Tili2->setText(QCoreApplication::translate("automat", "Tili2", nullptr));
        btncancel->setText(QCoreApplication::translate("automat", "Takaisin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class automat: public Ui_automat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMAT_H
