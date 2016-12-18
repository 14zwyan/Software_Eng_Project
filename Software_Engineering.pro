#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T17:37:57
#
#-------------------------------------------------

QT       += core gui\
        network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Software_Engineering
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    QuestionGetter.cpp

HEADERS  += MainWindow.h \
    QuestionGetter.h

FORMS    += MainWindow.ui
