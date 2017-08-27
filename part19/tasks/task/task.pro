TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14 --pedantic -O0

SOURCES += main.cpp

HEADERS += \
    Task.hpp
