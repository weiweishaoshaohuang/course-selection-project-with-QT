#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QDate>
#include "personal_info.h"
#include <QModelIndex>
#include <QSqlQueryModel>
#include "DatabaseManger.h"
namespace Ui {
class Home;
}

class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QString name,QWidget *parent = nullptr);
    ~Home();
    Personal_info* pinfo;

private:
    Ui::Home *ui;
    QTimer *timer;
    QString username;
    QString course_number;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QSqlQueryModel *qmodel;
    QSqlQueryModel *qmodel_l;
    QModelIndex currentIndexModel;
private slots:
    void show_time();
    void on_pb_inf_clicked();
    void on_tableView_right_clicked(const QModelIndex &index);
    void on_pb_select_clicked();
    void on_pb_Nselect_clicked();
    void on_tableView_left_clicked(const QModelIndex &index);
    void on_pb_logout_clicked();
};

#endif // HOME_H
