#ifndef TEACHER_MANGER_H
#define TEACHER_MANGER_H

#include <QWidget>
#include "DatabaseManger.h"
#include "create_teacher.h"
#include <QSqlQueryModel>
#include <QModelIndex>
namespace Ui {
class Teacher_manger;
}

class Teacher_manger : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher_manger(QWidget *parent = nullptr);
    ~Teacher_manger();
    Create_teacher create;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_le_search_returnPressed();

private:
    Ui::Teacher_manger *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QSqlQueryModel *qmodel;
    QModelIndex currentModelIndex;
    int id;
};

#endif // TEACHER_MANGER_H
