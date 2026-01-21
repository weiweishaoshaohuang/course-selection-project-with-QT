#include "create_teacher.h"
#include "ui_create_teacher.h"

Create_teacher::Create_teacher(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Create_teacher)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);

}

Create_teacher::~Create_teacher()
{
    delete ui;
}

void Create_teacher::on_pb_add_clicked()
{
    name = ui->le_teacher_name->text();
    id = ui->le_id->text().toInt();
    password = ui->le_password->text();
    if(name.isEmpty() || id == 0 || password.isEmpty()){
        QMessageBox::information(this,"创建失败","有資料未填寫");
    }else{
        query->prepare("insert into teacher values(:id,:name,:password)");
        query->bindValue(":id",id);
        query->bindValue(":name",name);
        query->bindValue(":password",password);
        if(query->exec()){
            QMessageBox::about(this,"创建成功","创建成功");
        }else{
            QMessageBox::information(this,"创建失败","原因未知");
        }

    }
}

