#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("登入畫面");
    ui->lepassword->setEchoMode(QLineEdit::Password);
    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(show_time()));
    timer1->start(1000);
    status = 1;
    query = new QSqlQuery(db);
    if(query->exec("create table userinfo(username,password,name,class,tel,bd,live)"))
        qDebug()<<"create userinfo";
    if(query->exec("create table cusinfo(number,name,credit,term,clase,scores,max_people int,how_many_people int default 0)")){
         qDebug()<<"create coursed_info";
    }
    if(query->exec("create table enrollment(id integer primary key AUTOINCREMENT,student_username,course_number,foreign key(student_username) REFERENCES userinfo(username),FOREIGN KEY(course_number) REFERENCES cusinfo(number),UNIQUE(student_username,course_number))"))
        qDebug()<<"create enrollment";
    if(query->exec("create table system_status(id integer primary key autoincrement,is_open integer not null default 0)")){
        qDebug()<<"create system_status";
        if(query->exec("insert into system_status(is_open) values(0)"))
            qDebug()<<"insert successfully";
    }
    // if(query->exec("create table teacher(id integer primary key)"))
    //     qDebug()<<"create teacher_table";
    // QString query_execute = "create table schedule(teacher_id,course_number, foreign key(teacher_id) REFERENCES teacher(id),foreign key(course_number) REFERENCES cusinfo(number),UNIQUE(teacher_id,course_number))";
    // if(query->exec(query_execute))
    //     qDebug()<<"create schedule";
}

login::~login()
{
    delete ui;
}

void login::on_pblogin_clicked()
{
    query->prepare("select 1 from userinfo where username = :username and password = :password LIMIT 1");
    QString username = ui->leusername->text();
    QString password = ui->lepassword->text();
    query->bindValue(":username",username);
    query->bindValue(":password",password);
    if(query->exec()){
        if(username == "" && password ==""){
            QMessageBox::about(this,"未輸入帳密","請輸入帳號密碼");
        }else if(username == f_username && password == f_password && status == 2){
            reg.show();
            this->close();

        }else if(username == j_username && password == j_password && status == 0){
            adm.show();
            this->close();

        }else if(query->next() && status == 1){
            qDebug()<<"登入成功";
            home = new Home(username);
            home->show();
            this->close();
        }else{
            QMessageBox::about(this,"登入失敗","帳號或密碼錯誤");
            ui->lepassword->setText("");
            ui->leusername->setText("");
            qDebug()<<"帳號或密碼錯誤";
        }
    }else{
        qDebug()<<"Database query failed";
    }
}

void login::show_time()
{
    QString curdate = QDate::currentDate().toString("yyyy,MM,dd");
    QString curtime = QTime::currentTime().toString("hh,mm,ss");
    ui->lbtime->setText("现在时间:" + curdate + " " + curtime);
}


//教务处按钮
void login::on_rb_jwc_clicked()
{
    status = 0;
}
//学生按钮
void login::on_rb_student_clicked()
{
    status = 1;
}
//辅导员按钮
void login::on_rb_fdy_clicked()
{
    status = 2;
}

