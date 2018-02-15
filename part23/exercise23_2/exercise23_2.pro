TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../example23/Mail_file.cpp

HEADERS += \
    ../example23/Mail_file.hpp
