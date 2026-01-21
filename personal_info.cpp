#include "personal_info.h"
#include "login.h"
#include "ui_personal_info.h"

Personal_info::Personal_info(QString username,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Personal_info),username(username)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    query->prepare("select username,password,name,class,tel,bd,live from userinfo where username = :username");
    query->bindValue(":username",username);
    if(!query->exec()){
        qDebug()<<"query execution failed";
    }
    while(query->next()){
        ui->lb_username->setText(username);
        ui->le_password->setText(query->value(1).toString());
        ui->lb_name->setText(query->value(2).toString());
        ui->lb_clase->setText(query->value(3).toString());
        ui->lb_tel->setText(query->value(4).toString());
        ui->lb_bd->setText(query->value(5).toString());
        ui->lb_live->setText(query->value(6).toString());
    }
}

Personal_info::~Personal_info()
{
    delete ui;
}

void Personal_info::on_pb_reset_clicked()
{
    QString password = ui->le_password->text();
    if(password.isEmpty()){
        QMessageBox::information(this,"更改失败","请输入密码");
    }else{
        query->prepare("update userinfo set password = :password where username = '" + username + "'");
        query->bindValue(":password",password);
        if(query->exec()){
            QMessageBox::about(this,"更改成功","更改成功");
        }else{
        QMessageBox::information(this,"更改失败","未知错误");
        }
    }
}


void Personal_info::on_pb_logout_clicked()
{
    login lgn;
    lgn.show();
    this->close();
    lgn.exec();
}

