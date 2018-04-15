#-----------------------------------------------------------------------------

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#-----------------------------------------------------------------------------

QMAKE_CXXFLAGS += -std=c++17 --pedantic
DESTDIR = ../bin

#-----------------------------------------------------------------------------

LIBS	+= -lfltk -lfltk_images
INCLUDEPATH += /usr/local/include/

#-----------------------------------------------------------------------------

SOURCES += main.cpp \
    ../../../bstroustrup_code/Window.cpp \
    ../../../bstroustrup_code/GUI.cpp \
    ../../../bstroustrup_code/Simple_window.cpp \
    ../../../bstroustrup_code/Graph.cpp \
    ../../bstroustrup_code/Time.cpp

#-----------------------------------------------------------------------------

HEADERS += \
    ../../../bstroustrup_code/Point.h \
    ../../../bstroustrup_code/Simple_window.h \
    ../../../bstroustrup_code/fltk.h \
    ../../../bstroustrup_code/Window.h \
    ../../../bstroustrup_code/Gui.h \
    ../../../bstroustrup_code/GUI.h \
    ../../../bstroustrup_code/std_lib_facilities.h \
    ../../../bstroustrup_code/Graph.h \
    ../../bstroustrup_code/Time.hpp

#-----------------------------------------------------------------------------
