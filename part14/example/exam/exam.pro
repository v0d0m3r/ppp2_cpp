QT += core
QT -= gui

CONFIG += c++11

TARGET = exam
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    Graph.h \
    ../../../bstroustrup_code/Point.h \
    ../../../bstroustrup_code/fltk.h \
    ../../../bstroustrup_code/std_lib_facilities.h \
