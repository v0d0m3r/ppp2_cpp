QT += core
QT -= gui

CONFIG += c++11
TARGET = exam
CONFIG += console
CONFIG -= app_bundle

LIBS	+= -lXfixes -lpthread -ldl -lfltk_images -lfltk_jpeg -lfltk -lX11 -lXext

#LIBS	+= -lXfixes -lpthread -ldl -lfltk -lfltk_images -lXinerama
#LIBS    += -lpng -ljpeg -lX11 -lXext -lz -lm -lXcursor -lXrender -lfontconfig -lXft
INCLUDEPATH += /usr/local/include/

TEMPLATE = app

SOURCES += main.cpp \
    Graph.cpp

HEADERS += \    
    Graph.h \
    ../../../bstroustrup_code/std_lib_facilities.h \
    ../../../bstroustrup_code/Point.h \
    ../../../bstroustrup_code/fltk.h
