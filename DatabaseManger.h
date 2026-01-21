#ifndef DATABASEMANGER_H
#define DATABASEMANGER_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

class DatabaseManger{
public:
    static DatabaseManger& instance(){
        static DatabaseManger instance;//懶漢式單例,第一次訪問時創建
        return instance;
    }
    // 禁止拷贝构造和赋值操作
    DatabaseManger(const DatabaseManger&) = delete;
    void operator=(const DatabaseManger&) = delete;
    //初始化資料庫
    static void setSystemStatus(bool isOpen) {
        QSqlQuery query;
        query.prepare("UPDATE system_status SET is_open = :isOpen WHERE id = 1");
        query.bindValue(":isOpen", isOpen ? 1 : 0);
        if (!query.exec()) {
            qDebug() << "Failed to update system";
        }
    }

    static bool isSystemOpen() {
        QSqlQuery query("SELECT is_open FROM system_status WHERE id = 1");
        if (query.next()) {
            return query.value(0).toInt() == 1;
        } else {
            qDebug() << "Failed to retrieve system ";
            return false;
        }
    }

    bool initDatabase(const QString dbName = "hsw.db"){
        if(db.isOpen()){
            return true;
        }

        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
        if(!db.open()){
            qDebug()<<"Database doesn't work";
            return false;
        }
        return true;
    }
    QSqlDatabase& getDatabase(){//返回引用，使得操作是直接在db上，而不是拷貝上
        return db;
    }

private:
    QSqlDatabase db;
    //私有化構造函數，防止外部構造實例
    DatabaseManger(){}
};

#endif // DATABASEMANGER_H

