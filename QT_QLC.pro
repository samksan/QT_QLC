#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T09:44:53
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_QLC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database/netnumbers.cpp \
    Analysis/analysiscontrol.cpp \
    Analysis/analysisutils.cpp

HEADERS  += mainwindow.h \
    database/netnumbers.h \
    Analysis/analysiscontrol.h \
    Analysis/analysisutils.h

FORMS    += mainwindow.ui

RESOURCES += \
    myresources.qrc
