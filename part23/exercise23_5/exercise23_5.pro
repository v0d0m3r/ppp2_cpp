TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../exercise23_4/Mail_file.cpp

HEADERS += \
    ../exercise23_4/Mail_file.hpp
