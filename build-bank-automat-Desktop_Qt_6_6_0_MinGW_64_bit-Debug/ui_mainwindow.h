/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnLogin;
    QLineEdit *TextCardID;
    QLineEdit *TextPin;
    QPushButton *btnLanguage;
    QLabel *labelInfo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(495, 357);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 50, 101, 61));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 120, 101, 61));
        label_2->setFont(font);
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(170, 180, 151, 51));
        btnLogin->setFont(font);
        TextCardID = new QLineEdit(centralwidget);
        TextCardID->setObjectName("TextCardID");
        TextCardID->setGeometry(QRect(180, 70, 131, 31));
        TextCardID->setFont(font);
        TextPin = new QLineEdit(centralwidget);
        TextPin->setObjectName("TextPin");
        TextPin->setGeometry(QRect(180, 130, 131, 31));
        TextPin->setFont(font);
        btnLanguage = new QPushButton(centralwidget);
        btnLanguage->setObjectName("btnLanguage");
        btnLanguage->setGeometry(QRect(20, 260, 121, 41));
        labelInfo = new QLabel(centralwidget);
        labelInfo->setObjectName("labelInfo");
        labelInfo->setGeometry(QRect(170, 260, 231, 41));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Kortin ID", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "PIN", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Kirjaudu", nullptr));
        btnLanguage->setText(QCoreApplication::translate("MainWindow", "Suomi/English", nullptr));
        labelInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
