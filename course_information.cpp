#include "course_information.h"
#include "ui_course_information.h"

course_information::course_information(QString course_number,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::course_information),course_number(course_number)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    qmodel = new QSqlQueryModel();
    QString queryset="select username,name,class from userinfo where username in (select student_username from enrollment where course_number = '"+course_number + "')";
    qDebug()<<queryset;
    qmodel->setQuery(queryset);
    ui->tableView->setModel(qmodel);
    qmodel->setHeaderData(0,Qt::Horizontal,"学号");
    qmodel->setHeaderData(1,Qt::Horizontal,"姓名");
    qmodel->setHeaderData(2,Qt::Horizontal,"班级");
}

course_information::~course_information()
{
    delete ui;
}
