#include "register_student.h"
#include "ui_register_student.h"

Register_student::Register_student(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register_student)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);

}

Register_student::~Register_student()
{
    delete ui;
}

void Register_student::on_pbregiser_student_clicked()
{
    QString username = ui->leusername->text(),password = ui->lepassword->text(),name = ui->lename->text()
        ,telephone = ui->letel->text()
        ,clase = ui->leclass->text(),living_place = ui->lelive->text();
    QString birthdate = ui->dateEdit->text();
    if(username.isEmpty() || password.isEmpty() || name.isEmpty() || telephone.isEmpty() || birthdate.isEmpty() || clase.isEmpty() || living_place.isEmpty()){
        //有资料未填写
        QMessageBox::information(this,"注册失败","注册栏含未填写项");
    }else{
        query->prepare("select 1 from userinfo where username = :username limit 1");//判断是否被注册过
        query->bindValue(":username",username);
        if(query->exec()){
            if(query->next()){
                QMessageBox::information(this,"注册失败","此学号已被注册过");
            }else{
                query->prepare("insert into userinfo values(:username,:password,:name,:clase,:telephone,:birthdate,:living_place)");
                query->bindValue(":username", username);
                query->bindValue(":password", password);
                query->bindValue(":name", name);
                query->bindValue(":clase", clase);
                query->bindValue(":telephone", telephone);
                query->bindValue(":birthdate", birthdate);
                query->bindValue(":living_place", living_place);
                if(query->exec()){
                    QMessageBox::information(this,"注册成功","注册成功！");
                }else{
                    QMessageBox::information(this,"注册失败","未知错误");
                }
            }
        }else{
            qDebug()<<"executed failed";
        }

    }
}

