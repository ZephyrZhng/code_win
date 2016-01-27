#-------------------------------------------------
#
# Project created by QtCreator 2014-10-07T01:01:26
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gl
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

LIBS     += -lglut
