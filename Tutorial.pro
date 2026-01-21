QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administration.cpp \
    course_information.cpp \
    create_course.cpp \
    home.cpp \
    main.cpp \
    login.cpp \
    personal_info.cpp \
    register.cpp \
    register_student.cpp

HEADERS += \
    DatabaseManger.h \
    administration.h \
    course_information.h \
    create_course.h \
    home.h \
    login.h \
    personal_info.h \
    register.h \
    register_student.h

FORMS += \
    administration.ui \
    course_information.ui \
    create_course.ui \
    home.ui \
    login.ui \
    personal_info.ui \
    register.ui \
    register_student.ui

TRANSLATIONS += \
    Tutorial_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
