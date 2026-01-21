#include "administration.h"
#include "ui_administration.h"
#include "login.h"
Administration::Administration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Administration)
{
    ui->setupUi(this);
    ui->le_searchline->setPlaceholderText("输入课程编号或课程名称...");
    ui->le_searchline->hide();

    ui->pb_TeacherManger->hide();//
    ui->pb_teacherCus->hide();//
    query = new QSqlQuery(db);
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("select * from cusinfo order by number");
    ui->tableView->setModel(qmodel);
    qmodel->setHeaderData(0,Qt::Horizontal,"课程编号");
    qmodel->setHeaderData(1,Qt::Horizontal,"课程名称");
    qmodel->setHeaderData(2,Qt::Horizontal,"学分");
    qmodel->setHeaderData(3,Qt::Horizontal,"学期");
    qmodel->setHeaderData(4,Qt::Horizontal,"教室");
    qmodel->setHeaderData(5,Qt::Horizontal,"成绩");
    qmodel->setHeaderData(6,Qt::Horizontal,"可选人数");
    qmodel->setHeaderData(7,Qt::Horizontal,"已选人数");
}

Administration::~Administration()
{
    delete ui;
}

void Administration::on_pb_add_clicked()
{
    cus.show();
}


void Administration::on_pb_search_clicked()
{
    ui->le_searchline->setVisible(!ui->le_searchline->isVisible());
    if(ui->le_searchline->isVisible()){
        ui->le_searchline->setFocus();
    }
}


void Administration::on_pb_refresh_clicked()
{
    qmodel->setQuery("select * from cusinfo order by number");
}


void Administration::on_pb_del_clicked()
{
    QString del = "delete from cusinfo where number = '" + currentIndexModel.siblingAtColumn(0).data().toString() + "'";
    if(query->exec(del)){
        QMessageBox::information(this,"删除成功","删除成功！");
    }else
        QMessageBox::information(this,"删除失败","发生错误");

    qmodel->setQuery("select * from cusinfo order by number");
}


void Administration::on_tableView_clicked(const QModelIndex &index)
{
    QString number = index.siblingAtColumn(0).data().toString();
    currentIndexModel = index;
}





void Administration::on_le_searchline_returnPressed()
{
    QString select_text = ui->le_searchline->text();
    qmodel->setQuery("select * from cusinfo where number like '%" + select_text + "%' OR  name like '%" + select_text +"%'order by number");
}




void Administration::on_pb_selectON_clicked()
{
    QMessageBox::about(this,"系统提示","选课\退课系统已\"开放\"");
    DatabaseManger::setSystemStatus(1);
    qDebug()<<DatabaseManger::isSystemOpen();
}


void Administration::on_pb_selectOFF_clicked()
{
    QMessageBox::about(this,"系统提示","选课\退课系统已\"关闭\"");
    DatabaseManger::setSystemStatus(0);
    qDebug()<<DatabaseManger::isSystemOpen();
}


void Administration::on_pb_logout_clicked()
{
    login* lgn;
    lgn = new login();
    lgn->show();
    this->close();
    lgn->exec();
}


void Administration::on_pb_view_clicked()
{
    cus_info = new course_information(currentIndexModel.siblingAtColumn(0).data().toString());
    cus_info->show();
}



