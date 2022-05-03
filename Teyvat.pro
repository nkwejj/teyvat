#-------------------------------------------------
#
# Project created by QtCreator 2022-03-20T18:54:19
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets
#QT       += sql
CONFIG+=resources_big



#DEFINES += QT_NO_DEBUG_OUTPUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Teyvat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        teyvat.cpp \
    login.cpp \
    gamemodel.cpp \
    mainwindow.cpp \
    levelchoose.cpp \
    mainwindow2.cpp \
    mainwindow3.cpp \
    gamemodel2.cpp \
    gamemodel3.cpp \
    constcl.cpp


HEADERS += \
        teyvat.h \
    login.h \
    gamemodel.h \
    mainwindow.h \
    levelchoose.h \
    gamemodel2.h \
    gamemodel3.h \
    mainwindow2.h \
    mainwindow3.h \
    constcl.h


FORMS += \
        teyvat.ui \
    mainwindow.ui \
    levelchoose.ui \
    mainwindow2.ui \
    mainwindow3.ui

RESOURCES += \
    teyvat.qrc

#win32:LIBS += -LD:/MySQL/MySQL-Server-8.0/lib -llibmysql

#INCLUDEPATH += D:/MySQL/MySQL-Server-8.0/include

#DEPENDPATH += D:/MySQL/MySQL-Server-8.0/include
