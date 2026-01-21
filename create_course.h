#ifndef CREATE_COURSE_H
#define CREATE_COURSE_H

#include <QWidget>
#include "DatabaseManger.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QModelIndex>

namespace Ui {
class Create_course;
}

class Create_course : public QWidget
{
    Q_OBJECT

public:
    explicit Create_course(QWidget *parent = nullptr);
    ~Create_course();

private slots:
    void on_pb_create_clicked();

private:
    Ui::Create_course *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
};

#endif // CREATE_COURSE_H
