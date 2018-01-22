TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS	+= -lfltk_images -lfltk

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../../bstroustrup_code/Window.cpp \
    ../../bstroustrup_code/GUI.cpp \
    ../../bstroustrup_code/Simple_window.cpp \
    ../../bstroustrup_code/Graph.cpp \
    ../../bstroustrup_code/Time.cpp \
    ../Query_window.cpp \
    ../exercise21_9/Order.cpp \
    ../exercise21_13/Clear_punctstream.cpp \
    ../../part11/exercise11_8/src/punctstream.cpp

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
    ../Query_window.hpp \
    ../exercise21_9/Order.hpp \
    ../exercise21_14/Finder.hpp \
    ../exercise21_13/Clear_punctstream.hpp \
    ../../part11/exercise11_8/src/punctstream.hpp
