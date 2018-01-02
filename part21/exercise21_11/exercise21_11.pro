TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS	+= -lXfixes -lpthread -ldl -lfltk_images -lfltk_jpeg -lfltk -lX11 -lXext
#LIBS	+= -lXfixes -lpthread -ldl -lfltk -lfltk_images -lXinerama
#LIBS    += -lpng -ljpeg -lX11 -lXext -lz -lm -lXcursor -lXrender -lfontconfig -lXft
INCLUDEPATH += /usr/local/include/

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../../bstroustrup_code/Window.cpp \
    ../../bstroustrup_code/GUI.cpp \
    ../../bstroustrup_code/Simple_window.cpp \
    ../../bstroustrup_code/Graph.cpp \
    ../../bstroustrup_code/Time.cpp \
    ../exercise21_9/Order.cpp \
    Input_orders_window.cpp

HEADERS += \
    ../../bstroustrup_code/Point.h \
    ../../bstroustrup_code/Simple_window.h \
    ../../bstroustrup_code/fltk.h \
    ../../bstroustrup_code/Window.h \
    ../../bstroustrup_code/Gui.h \
    ../../bstroustrup_code/GUI.h \
    ../../bstroustrup_code/std_lib_facilities.h \
    ../../bstroustrup_code/Graph.h \
    ../../bstroustrup_code/Time.hpp \
    ../exercise21_9/Order.hpp \
    Input_orders_window.hpp
