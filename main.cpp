#include "login.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "DatabaseManger.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QTranslator translator;
    // const QStringList uiLanguages = QLocale::system().uiLanguages();
    // for (const QString &locale : uiLanguages) {
    //     const QString baseName = "Tutorial_" + QLocale(locale).name();
    //     if (translator.load(":/i18n/" + baseName)) {
    //         a.installTranslator(&translator);
    //         break;
    //     }
    // }
    if(!DatabaseManger::instance().initDatabase()){
        return -1;  //初始化失敗，退出應用
    }
    login w;
    w.show();
    return a.exec();
}
