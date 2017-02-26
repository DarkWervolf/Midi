#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T18:41:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Midi
TEMPLATE = app

include(QMidi.pri)

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


