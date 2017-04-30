TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++14 -Wextra --pedantic

SOURCES += main.cpp money.cpp

HEADERS += money.h
