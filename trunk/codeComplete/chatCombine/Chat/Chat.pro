#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T01:07:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatText.cpp \
    chatVideo.cpp \
    text_client.cpp


HEADERS  += mainwindow.h \
    chatText.h \
    chatVideo.h \
    configIpAndPort.h

FORMS    += mainwindow.ui
