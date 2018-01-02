TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1z --pedantic

DESTDIR = ../bin

SOURCES += main.cpp \
    ../exercise21_9/Order.cpp

HEADERS += \
    ../exercise21_9/Order.hpp
