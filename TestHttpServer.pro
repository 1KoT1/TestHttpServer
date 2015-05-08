#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T18:50:28
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TestHttpServer
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    httpserver.cpp

HEADERS += \
    httpserver.h
