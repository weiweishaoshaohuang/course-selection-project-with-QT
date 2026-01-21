#ifndef CREATE_TEACHER_H
#define CREATE_TEACHER_H

#include <QWidget>
#include <DatabaseManger.h>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class Create_teacher;
}

class Create_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit Create_teacher(QWidget *parent = nullptr);
    ~Create_teacher();

private slots:
    void on_pb_add_clicked();

private:
    Ui::Create_teacher *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QString name;
    int id;
    QString password;
};

#endif // CREATE_TEACHER_H
