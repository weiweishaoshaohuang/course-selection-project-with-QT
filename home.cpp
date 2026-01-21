#include <ui_home.h>
#include "home.h"
#include "login.h"

Home::Home(QString name,QWidget *parent)
    : QWidget(parent), ui(new Ui::Home) , username(name)
{
    ui->setupUi(this);
    ui->pb_inf->setStyleSheet("background-color: transparent; border: none;");
    if(DatabaseManger::isSystemOpen())
        ui->lb_status->setText("系统开放选课中！");
    else
        ui->lb_status->setText("系统未开放选课！");
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(show_time()));
    timer->start(1000);
    query = new QSqlQuery(db);
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("SELECT * FROM cusinfo WHERE number NOT IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
    ui->tableView_right->setModel(qmodel);
    qmodel->setHeaderData(0,Qt::Horizontal,"课程编号");
    qmodel->setHeaderData(1,Qt::Horizontal,"课程名称");
    qmodel->setHeaderData(2,Qt::Horizontal,"学分");
    qmodel->setHeaderData(3,Qt::Horizontal,"学期");
    qmodel->setHeaderData(4,Qt::Horizontal,"教室");
    qmodel->setHeaderData(5,Qt::Horizontal,"成绩");
    qmodel->setHeaderData(6,Qt::Horizontal,"可选人数");
    qmodel->setHeaderData(7,Qt::Horizontal,"已选人数");
    qmodel_l = new QSqlQueryModel();
    qmodel_l->setQuery("SELECT * FROM cusinfo WHERE number IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
    ui->tableView_left->setModel(qmodel_l);
    qmodel_l->setHeaderData(0,Qt::Horizontal,"课程编号");
    qmodel_l->setHeaderData(1,Qt::Horizontal,"课程名称");
    qmodel_l->setHeaderData(2,Qt::Horizontal,"学分");
    qmodel_l->setHeaderData(3,Qt::Horizontal,"学期");
    qmodel_l->setHeaderData(4,Qt::Horizontal,"教室");
    qmodel_l->setHeaderData(5,Qt::Horizontal,"成绩");
    qmodel_l->setHeaderData(6,Qt::Horizontal,"可选人数");
    qmodel_l->setHeaderData(7,Qt::Horizontal,"已选人数");
}

Home::~Home()
{
    delete ui;
}

void Home::show_time()
{
    QString curdate = QDate::currentDate().toString("yyyy,MM,dd");
    QString curtime = QTime::currentTime().toString("hh,mm,ss");
    ui->lbtime->setText("現在時間: " + curdate + " " + curtime);
}


void Home::on_pb_inf_clicked()
{
    pinfo = new Personal_info(username);
    pinfo->show();
}


void Home::on_tableView_right_clicked(const QModelIndex &index)
{
    currentIndexModel = index;
    course_number = currentIndexModel.siblingAtColumn(0).data().toString();
}


void Home::on_pb_select_clicked()
{
    if(DatabaseManger::isSystemOpen()){
        QString sql = "insert into enrollment(student_username,course_number) values('" + username + "','" + course_number +"')";
        qDebug()<<sql;
        int max_people = currentIndexModel.siblingAtColumn(6).data().toInt();
        int cur_people = currentIndexModel.siblingAtColumn(7).data().toInt();
        qDebug()<<max_people;
        if(cur_people < max_people){
            if(!query->exec(sql)){
                QMessageBox::information(this,"添加课程失败","添加课程失败，原因未知");
            }else{
                qDebug()<<"添加成功";
                qmodel->setQuery("SELECT * FROM cusinfo WHERE number NOT IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
                qmodel_l->setQuery("SELECT * FROM cusinfo WHERE number IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
                if(!query->exec("update cusinfo set how_many_people = how_many_people + 1 where number = '" + course_number +"'"))
                    qDebug()<<"增加人数失败";
            }
        }else{
            QMessageBox::information(this,"课程已满","课程已满");
        }
    }else
        QMessageBox::information(this,"系统未开放选课\退课","系统未开放选课\退课");
    qmodel_l->setQuery("SELECT * FROM cusinfo WHERE number IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
    qmodel->setQuery("SELECT * FROM cusinfo WHERE number NOT IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
}


void Home::on_pb_Nselect_clicked()
{
    if(DatabaseManger::isSystemOpen()){
        QString sql = "delete from enrollment where student_username = '" + username + "' and course_number = '" + course_number + "'";
        qDebug()<<sql;
        if(!query->exec(sql)){
            QMessageBox::information(this,"退选课程失败","退选课程失败，原因未知");
        }else{
            qDebug()<<"退选成功";
            qmodel->setQuery("SELECT * FROM cusinfo WHERE number NOT IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
            qmodel_l->setQuery("SELECT * FROM cusinfo WHERE number IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
            if(!query->exec("update cusinfo set how_many_people = how_many_people - 1 where number = '" + course_number +"'"))
                qDebug()<<"减少人数失败";
        }
    }else
        QMessageBox::information(this,"系统未开放选课\退课","系统未开放选课\退课");
    qmodel_l->setQuery("SELECT * FROM cusinfo WHERE number IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
    qmodel->setQuery("SELECT * FROM cusinfo WHERE number NOT IN (SELECT course_number FROM enrollment WHERE student_username = '" + username + "') ORDER BY number");
}


void Home::on_tableView_left_clicked(const QModelIndex &index)
{
    currentIndexModel = index;
    course_number = currentIndexModel.siblingAtColumn(0).data().toString();
}


void Home::on_pb_logout_clicked()
{
    login* lgn;
    lgn = new login();
    lgn->show();
    this->close();
    lgn->exec();
}

