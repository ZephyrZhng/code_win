#-------------------------------------------------
#
# Project created by QtCreator 2013-08-02T17:35:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    logindialog.cpp \
    markdialog.cpp

HEADERS  += widget.h \
    logindialog.h \
    markdialog.h

FORMS    += widget.ui \
    logindialog.ui \
    markdialog.ui
