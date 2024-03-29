#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <Automat.h>
#include <QTimer>
#include <QInputDialog>
#include <QLineEdit>
#include <QApplication>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showAccounts();
public slots:


private slots:
    void on_btnLogin_clicked();
    void loginSlot (QNetworkReply *reply);
    void logoutSlot();
    void accountSlot(QNetworkReply * reply);

private:
    QString ekaTili;
    QString tokaTili;
    Ui::MainWindow *ui;
    QNetworkAccessManager *postManager;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QNetworkReply *reply2;

    QByteArray response_data;
    automat *objectautomat;
    QString cardID;
    QByteArray token;

};
#endif // MAINWINDOW_H
