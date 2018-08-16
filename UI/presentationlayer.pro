#-------------------------------------------------
#
# Project created by QtCreator 2018-05-02T09:19:21
#
#-------------------------------------------------

QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = presentationlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    registerdevice.cpp \
    jsonmanager.cpp \
    deregisterdevice.cpp \
    connection.cpp \
    devicesettings.cpp \
    window.cpp \
    singledevicesettings.cpp

HEADERS  += mainwindow.h \
    registerdevice.h \
    jsonmanager.h \
    json.hpp \
    deregisterdevice.h \
    connection.h \
    devicesettings.h \
    window.h \
    singledevicesettings.h

FORMS    += mainwindow.ui \
    registerdevice.ui \
    deregisterdevice.ui \
    devicesettings.ui \
    singledevicesettings.ui

DISTFILES += \
    devices.json

INCLUDEPATH +=/usr/local/include/libusb-1.0
LIBS += -L/usr/local/lib -lusb-1.0


target.path = $$[QT_INSTALL_EXAMPLES]/dialogs/findfiles
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/dialogs/findfiles
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)
