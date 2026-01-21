#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QMessageBox>
#include "DatabaseManger.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QModelIndex>
#include "register_student.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pbregister_clicked();

    void on_pbalter_clicked();

    void on_pbdelete_clicked();

    void on_pbconfirm_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pbfindusername_clicked();

    void on_pb_logout_clicked();

private:
    Ui::Register *ui;
    QSqlDatabase& db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QSqlQueryModel *qmodel;
    QModelIndex currentIndexModel;
    Register_student regstu;
    bool alt = 0,del = 0;
};

#endif // REGISTER_H
