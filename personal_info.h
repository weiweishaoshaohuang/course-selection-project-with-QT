#ifndef PERSONAL_INFO_H
#define PERSONAL_INFO_H

#include <QWidget>
#include <DatabaseManger.h>
#include <QString>
#include <QMessageBox>
namespace Ui {
class Personal_info;
}

class Personal_info : public QDialog
{
    Q_OBJECT

public:
    explicit Personal_info(QString username,QWidget *parent = nullptr);
    ~Personal_info();

private slots:
    void on_pb_reset_clicked();

    void on_pb_logout_clicked();

private:
    Ui::Personal_info *ui;
    QSqlDatabase db = DatabaseManger::instance().getDatabase();
    QSqlQuery *query;
    QString username;
};

#endif // PERSONAL_INFO_H
