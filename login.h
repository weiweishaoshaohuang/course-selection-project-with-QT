#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QDate>
#include "home.h"
#include "register.h"
#include "DatabaseManger.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "administration.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QDialog
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    Home* home;
    Register reg;
    Administration adm;
private slots:
    void on_pblogin_clicked();
    void show_time();

    void on_pbteacher_clicked();

    void on_pbstudent_clicked();

    void on_rb_student_clicked();

    void on_rb_jwc_clicked();

    void on_rb_fdy_clicked();

private:
    Ui::login *ui;
    QTimer *timer1;
    QSqlDatabase& db = DatabaseManger::instance().getDatabase();;
    QSqlQuery *query;
    QString f_username = "fd";
    QString f_password = "fd";
    QString j_username = "jw";
    QString j_password = "jw";
    int status;
};
#endif // LOGIN_H
