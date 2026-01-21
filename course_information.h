#ifndef COURSE_INFORMATION_H
#define COURSE_INFORMATION_H

#include <QWidget>
#include "DatabaseManger.h"
#include <QDebug>
#include <QSqlQueryModel>
namespace Ui {
class course_information;
}

class course_information : public QWidget
{
    Q_OBJECT

public:
    explicit course_information(QString course_number,QWidget *parent = nullptr);
    ~course_information();

private:
    Ui::course_information *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QSqlQueryModel *qmodel;
    QString course_number;
};

#endif // COURSE_INFORMATION_H
