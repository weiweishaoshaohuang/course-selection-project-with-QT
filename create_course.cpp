#include "create_course.h"
#include "ui_create_course.h"

Create_course::Create_course(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Create_course)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
}

Create_course::~Create_course()
{
    delete ui;
}

void Create_course::on_pb_create_clicked()
{
    QString number = ui->le_number->text(),name = ui->le_name->text(),credit = ui->le_credit->text()
        ,term = ui->le_term->text(),clase = ui->le_clase->text(),score = ui->le_score->text();
    int max_people = ui->sb_max_pelple->text().toInt();
    if(max_people == 0 || number.isEmpty() || name.isEmpty() || credit.isEmpty() || term.isEmpty() || clase.isEmpty() || score.isEmpty()){
        QMessageBox::information(this,"建立失败","有资料未填写！");
    }else{
        query->prepare("select 1 from cusinfo where number = :number limit 1");//判断是否被注册过
        query->bindValue(":number",number);
        if(query->exec()){
            if(query->next()){
                QMessageBox::information(this,"建立失败","该课程已被建立过");
            }else{
                query->prepare("insert into cusinfo values(:number,:name,:credit,:term,:clase,:score,:max_people,0)");
                query->bindValue(":number", number);
                query->bindValue(":name", name);
                query->bindValue(":credit", credit);
                query->bindValue(":term", term);
                query->bindValue(":clase", clase);
                query->bindValue(":score", score);
                query->bindValue(":max_people",max_people);
                if(query->exec()){
                    QMessageBox::information(this,"建立成功","已添加新课堂至课表中！");
                    this->close();
                }else{
                    QMessageBox::information(this,"建立失败","原因未知");
                }
            }
        }
        else{
            qDebug()<<"created course failed";
        }
    }
}

