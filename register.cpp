#include "register.h"
#include "qsqlquery.h"
#include "ui_register.h"
#include "login.h"
Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);

    qmodel = new QSqlQueryModel();
    qmodel->setQuery("select * from userinfo order by username");
    ui->tableView->setModel(qmodel);
    qmodel->setHeaderData(0,Qt::Horizontal,"学号");
    qmodel->setHeaderData(1,Qt::Horizontal,"密码");
    qmodel->setHeaderData(2,Qt::Horizontal,"姓名");
    qmodel->setHeaderData(3,Qt::Horizontal,"班级");
    qmodel->setHeaderData(4,Qt::Horizontal,"电话");
    qmodel->setHeaderData(5,Qt::Horizontal,"生日");
    qmodel->setHeaderData(6,Qt::Horizontal,"住址");
}

Register::~Register()
{
    delete ui;
}

void Register::on_pbregister_clicked()
{
    alt = 0;del = 0;
    ui->pbalter->setStyleSheet("background-color: white; color: black;");
    ui->pbdelete->setStyleSheet("background-color: white; color: black;");
    regstu.show();
}


void Register::on_pbalter_clicked()
{
    alt = 1;del = 0;
    ui->pbalter->setStyleSheet("background-color: black; color: white;");
    ui->pbdelete->setStyleSheet("background-color: white; color: black;");

}


void Register::on_pbdelete_clicked()
{
    alt = 0;del = 1;

    ui->pbdelete->setStyleSheet("background-color: black; color: white;");
    ui->pbalter->setStyleSheet("background-color: white; color: black;");

}


void Register::on_pbconfirm_clicked()
{
    if(1 == 0){
        QString username = ui->leusername->text();
        QString password = ui->lepassword->text();

        query->prepare("select 1 from userinfo where username = :username limit 1");
        query->bindValue(":username",username);
        if(query->exec()){
            if(ui->leusername->text().isEmpty() || ui->lepassword->text().isEmpty()){
                QMessageBox::information(this,"帳號或密碼未填寫","帳號或密碼未填寫");
            }else if(query->next()){
                QMessageBox::information(this,"帳號已存在","帳號已存在");
            }else{
                query->exec("insert into userinfo(username,password) values('" + username + "','" + password + "')");
                QMessageBox::information(this,"註冊成功","註冊成功");
                qmodel->setQuery("select * from userinfo order by username");
            }
        }else{
            qDebug()<<"Something wrong";
        }
    }else if(alt == 1){
        QString username = ui->tableView->currentIndex().siblingAtColumn(0).data().toString();
        QString password = ui->lepassword->text();
        QString alter1 = "update userinfo set password = '" + password +"'where username = '" + username + "'";
        query->exec(alter1);
        qmodel->setQuery("select * from userinfo order by username");
    }else{
        QString username = ui->leusername->text();
        QString del = "delete from userinfo where username = '" + username + "'";
        query->exec(del);
        qmodel->setQuery("select * from userinfo order by username");
    }
}


void Register::on_tableView_clicked(const QModelIndex &index)
{
    QString username = index.siblingAtColumn(0).data().toString();
    QString password = index.siblingAtColumn(1).data().toString();
    ui->leusername->setText(username);
    ui->lepassword->setText(password);
    currentIndexModel = index;
}


void Register::on_pbfindusername_clicked()
{
    QString username = ui->leusername->text();
    qmodel->setQuery("select * from userinfo where username like '%" +username + "%' order by username");
}


void Register::on_pb_logout_clicked()
{
    login* lgn;
    lgn = new login();
    lgn->show();
    this->close();
    lgn->exec();
}

