QT += core
QT -= gui

CONFIG += c++11

TARGET = exer16_2
CONFIG += console
CONFIG -= app_bundle

LIBS	+= -lXfixes -lpthread -ldl -lfltk_images -lfltk_jpeg -lfltk -lX11 -lXext

#LIBS	+= -lXfixes -lpthread -ldl -lfltk -lfltk_images -lXinerama
#LIBS    += -lpng -ljpeg -lX11 -lXext -lz -lm -lXcursor -lXrender -lfontconfig -lXft
INCLUDEPATH += /usr/local/include/

TEMPLATE = app

SOURCES += main.cpp \
    ../../../bstroustrup_code/Window.cpp \
    ../../../bstroustrup_code/GUI.cpp \
    ../../../bstroustrup_code/Simple_window.cpp \
    ../../../bstroustrup_code/Graph.cpp \
    ../../exercise16_1/exer16_1/my_window.cpp \
    chess_window.cpp

HEADERS += \
    ../../../bstroustrup_code/Point.h \
    ../../../bstroustrup_code/Simple_window.h \
    ../../../bstroustrup_code/fltk.h \
    ../../../bstroustrup_code/Window.h \
    ../../../bstroustrup_code/Gui.h \
    ../../../bstroustrup_code/GUI.h \
    ../../../bstroustrup_code/std_lib_facilities.h \
    ../../../bstroustrup_code/Graph.h \
    ../../exercise16_1/exer16_1/my_window.h \
    chess_window.h
