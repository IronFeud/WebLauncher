#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T21:36:26
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebLauncher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qwebserver.cpp \
    qmcl.cpp \
    webthread.cpp

HEADERS  += mainwindow.h \
    qwebserver.h \
    qmcl.h \
    qcomstring.h \
    webthread.h

FORMS    += mainwindow.ui
