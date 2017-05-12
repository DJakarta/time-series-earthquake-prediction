#-------------------------------------------------
#
# Project created by QtCreator 2017-02-03T00:42:08
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = earthquake
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


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    datahandler.cpp \
    event.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    datahandler.h \
    event.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../build-earthquake-Desktop_Qt_5_8_0_MinGW_32bit-Debug/events.xml \
    1-43,5-48,5-20-30.png \
    event.png
