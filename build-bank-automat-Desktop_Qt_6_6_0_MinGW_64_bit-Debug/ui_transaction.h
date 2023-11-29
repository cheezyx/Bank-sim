/********************************************************************************
** Form generated from reading UI file 'transaction.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTION_H
#define UI_TRANSACTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_transaction
{
public:
    QPushButton *btn0;
    QPushButton *btn6;
    QPushButton *btn8;
    QPushButton *btnenter;
    QPushButton *btn9;
    QPushButton *btn5;
    QPushButton *btnback;
    QPushButton *btn2;
    QPushButton *btn7;
    QPushButton *btn1;
    QPushButton *btn3;
    QPushButton *btn4;
    QStackedWidget *stackedWidget;
    QWidget *page_7;
    QPushButton *talletus_2;
    QPushButton *nosto_2;
    QPushButton *siirto_2;
    QWidget *page_8;
    QPushButton *siirto_4;
    QWidget *page_9;
    QPushButton *talletus_4;
    QWidget *page_10;
    QPushButton *nosto_4;
    QPushButton *logout;
    QTextEdit *tekstiAkkuna;
    QPushButton *btncancel;

    void setupUi(QDialog *transaction)
    {
        if (transaction->objectName().isEmpty())
            transaction->setObjectName("transaction");
        transaction->resize(603, 547);
        btn0 = new QPushButton(transaction);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(250, 430, 51, 51));
        QFont font;
        font.setPointSize(12);
        btn0->setFont(font);
        btn6 = new QPushButton(transaction);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(310, 310, 51, 51));
        btn6->setFont(font);
        btn8 = new QPushButton(transaction);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(250, 370, 51, 51));
        btn8->setFont(font);
        btnenter = new QPushButton(transaction);
        btnenter->setObjectName("btnenter");
        btnenter->setGeometry(QRect(310, 430, 51, 81));
        btn9 = new QPushButton(transaction);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(310, 370, 51, 51));
        btn9->setFont(font);
        btn5 = new QPushButton(transaction);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(250, 310, 51, 51));
        btn5->setFont(font);
        btnback = new QPushButton(transaction);
        btnback->setObjectName("btnback");
        btnback->setGeometry(QRect(190, 430, 51, 81));
        btn2 = new QPushButton(transaction);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(250, 250, 51, 51));
        btn2->setFont(font);
        btn7 = new QPushButton(transaction);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(190, 370, 51, 51));
        btn7->setFont(font);
        btn1 = new QPushButton(transaction);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(190, 250, 51, 51));
        btn1->setFont(font);
        btn3 = new QPushButton(transaction);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(310, 250, 51, 51));
        btn3->setFont(font);
        btn4 = new QPushButton(transaction);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(190, 310, 51, 51));
        btn4->setFont(font);
        stackedWidget = new QStackedWidget(transaction);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(390, 210, 211, 331));
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        talletus_2 = new QPushButton(page_7);
        talletus_2->setObjectName("talletus_2");
        talletus_2->setGeometry(QRect(30, 80, 151, 51));
        QFont font1;
        font1.setPointSize(14);
        talletus_2->setFont(font1);
        nosto_2 = new QPushButton(page_7);
        nosto_2->setObjectName("nosto_2");
        nosto_2->setGeometry(QRect(30, 140, 151, 51));
        nosto_2->setFont(font1);
        siirto_2 = new QPushButton(page_7);
        siirto_2->setObjectName("siirto_2");
        siirto_2->setGeometry(QRect(30, 20, 151, 51));
        siirto_2->setFont(font1);
        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName("page_8");
        siirto_4 = new QPushButton(page_8);
        siirto_4->setObjectName("siirto_4");
        siirto_4->setGeometry(QRect(30, 20, 151, 51));
        siirto_4->setFont(font1);
        stackedWidget->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName("page_9");
        talletus_4 = new QPushButton(page_9);
        talletus_4->setObjectName("talletus_4");
        talletus_4->setGeometry(QRect(30, 80, 151, 51));
        talletus_4->setFont(font1);
        stackedWidget->addWidget(page_9);
        page_10 = new QWidget();
        page_10->setObjectName("page_10");
        nosto_4 = new QPushButton(page_10);
        nosto_4->setObjectName("nosto_4");
        nosto_4->setGeometry(QRect(30, 140, 151, 51));
        nosto_4->setFont(font1);
        stackedWidget->addWidget(page_10);
        logout = new QPushButton(transaction);
        logout->setObjectName("logout");
        logout->setGeometry(QRect(20, 470, 151, 51));
        logout->setFont(font1);
        tekstiAkkuna = new QTextEdit(transaction);
        tekstiAkkuna->setObjectName("tekstiAkkuna");
        tekstiAkkuna->setGeometry(QRect(140, 60, 271, 181));
        btncancel = new QPushButton(transaction);
        btncancel->setObjectName("btncancel");
        btncancel->setGeometry(QRect(20, 410, 151, 51));
        btncancel->setFont(font1);

        retranslateUi(transaction);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(transaction);
    } // setupUi

    void retranslateUi(QDialog *transaction)
    {
        transaction->setWindowTitle(QCoreApplication::translate("transaction", "Dialog", nullptr));
        btn0->setText(QCoreApplication::translate("transaction", "0", nullptr));
        btn6->setText(QCoreApplication::translate("transaction", "6", nullptr));
        btn8->setText(QCoreApplication::translate("transaction", "8", nullptr));
        btnenter->setText(QCoreApplication::translate("transaction", "->", nullptr));
        btn9->setText(QCoreApplication::translate("transaction", "9", nullptr));
        btn5->setText(QCoreApplication::translate("transaction", "5", nullptr));
        btnback->setText(QCoreApplication::translate("transaction", "<-", nullptr));
        btn2->setText(QCoreApplication::translate("transaction", "2", nullptr));
        btn7->setText(QCoreApplication::translate("transaction", "7", nullptr));
        btn1->setText(QCoreApplication::translate("transaction", "1", nullptr));
        btn3->setText(QCoreApplication::translate("transaction", "3", nullptr));
        btn4->setText(QCoreApplication::translate("transaction", "4", nullptr));
        talletus_2->setText(QCoreApplication::translate("transaction", "Talletus", nullptr));
        nosto_2->setText(QCoreApplication::translate("transaction", "Nosto", nullptr));
        siirto_2->setText(QCoreApplication::translate("transaction", "Siirto", nullptr));
        siirto_4->setText(QCoreApplication::translate("transaction", "Siirto", nullptr));
        talletus_4->setText(QCoreApplication::translate("transaction", "Talletus", nullptr));
        nosto_4->setText(QCoreApplication::translate("transaction", "Nosto", nullptr));
        logout->setText(QCoreApplication::translate("transaction", "Kirjaudu ulos", nullptr));
        btncancel->setText(QCoreApplication::translate("transaction", "Takaisin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class transaction: public Ui_transaction {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTION_H
