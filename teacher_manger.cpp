#include "teacher_manger.h"
#include "ui_teacher_manger.h"

Teacher_manger::Teacher_manger(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Teacher_manger)
{
    ui->setupUi(this);
    ui->le_search->setPlaceholderText("请输入教师名称或工号...");
    ui->le_search->hide();
    query = new QSqlQuery(db);
    qmodel = new QSqlQueryModel();
    qmodel->setQuery("select id as ID,name as 名字 ,password as 密碼 from teacher order by id");
    ui->tableView->setModel(qmodel);
}

Teacher_manger::~Teacher_manger()
{
    delete ui;
}

void Teacher_manger::on_pushButton_clicked()
{
    create.show();
}


void Teacher_manger::on_pushButton_2_clicked()
{
    if(!query->exec("delete from teacher where id = " + QString::number(id)))
        QMessageBox::information(this,"删除失败","原因未知");
    qmodel->setQuery("select id as ID,name as 名字 from teacher order by id");
}


void Teacher_manger::on_tableView_clicked(const QModelIndex &index)
{
    currentModelIndex = index;
    id = currentModelIndex.siblingAtColumn(0).data().toInt();
}


void Teacher_manger::on_pushButton_3_clicked()
{
    ui->le_search->setVisible(!ui->le_search->isVisible());
    if(ui->le_search->isVisible()){
        ui->le_search->setFocus();
    }
}


void Teacher_manger::on_le_search_returnPressed()
{
    QString select_text = ui->le_search->text();
    qmodel->setQuery("select id as ID,name as 名字 from teacher where id like '%" + select_text + "%' OR  name like '%" + select_text +"%'order by id");
}

