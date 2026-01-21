#ifndef REGISTER_STUDENT_H
#define REGISTER_STUDENT_H

#include <QWidget>
#include "DatabaseManger.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Register_student;
}

class Register_student : public QWidget
{
    Q_OBJECT

public:
    explicit Register_student(QWidget *parent = nullptr);
    ~Register_student();

private slots:
    void on_pbregiser_student_clicked();

private:
    Ui::Register_student *ui;
    QSqlDatabase& db = DatabaseManger::instance().getDatabase();
    QSqlQuery* query;
};

#endif // REGISTER_STUDENT_H
