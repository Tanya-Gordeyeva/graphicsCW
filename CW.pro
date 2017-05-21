#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T13:25:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui opengl \
                                        widgets

TARGET = Lab6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mywidget.cpp

HEADERS  += mainwindow.h \
    mywidget.h

LIBS += -lopengl32\

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    fragment_shader.fsh \
    vertex_shader.vsh

RESOURCES += \
    res.qrc

