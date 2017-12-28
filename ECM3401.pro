#-------------------------------------------------
#
# Project created by QtCreator 2017-12-28T14:08:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECM3401
TEMPLATE = app

include(qtservice/src/qtservice.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    daemon.cpp \
    myservice.cpp

HEADERS  += mainwindow.h \
    daemon.h \
    myservice.h

FORMS    += mainwindow.ui
