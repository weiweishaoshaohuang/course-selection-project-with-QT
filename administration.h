#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <QWidget>
#include "DatabaseManger.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QModelIndex>
#include "create_course.h"
#include "course_information.h"
namespace Ui {
class Administration;
}

class Administration : public QWidget
{
    Q_OBJECT

public:
    explicit Administration(QWidget *parent = nullptr);
    ~Administration();
    Create_course cus;
    course_information* cus_info;
private slots:
    void on_pb_add_clicked();

    void on_pb_search_clicked();

    void on_pb_refresh_clicked();

    void on_pb_del_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_le_searchline_returnPressed();


    void on_pb_selectON_clicked();

    void on_pb_selectOFF_clicked();

    void on_pb_logout_clicked();

    void on_pb_view_clicked();

    void on_pb_TeacherManger_clicked();

private:
    Ui::Administration *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QSqlQueryModel *qmodel;
    QModelIndex currentIndexModel;
};

#endif // ADMINISTRATION_H
