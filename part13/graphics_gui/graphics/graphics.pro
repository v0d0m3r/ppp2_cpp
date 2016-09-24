QT += core
QT -= gui

CONFIG += c++11

TARGET = graphics
CONFIG += console
CONFIG -= app_bundle

LIBS	+= -lXfixes -lpthread -ldl -lfltk -lfltk_images -lXinerama
LIBS    += -lpng -ljpeg -lX11 -lXext -lz -lm -lXcursor -lXrender -lfontconfig -lXft
INCLUDEPATH += /usr/local/include/

TEMPLATE = app

SOURCES += main.cpp \
    Graph.cpp

HEADERS += \
    std_lib_facilities.h \
    fltk.h \
    Point.h \
    Graph.h
